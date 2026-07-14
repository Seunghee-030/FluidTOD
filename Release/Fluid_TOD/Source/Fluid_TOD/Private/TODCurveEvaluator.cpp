#include "TODCurveEvaluator.h"
#include "TODManager.h"
#include "MyBlueprintFunctionLibrary.h"

#if WITH_EDITOR
#include "Editor.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

namespace
{
	constexpr float TODHours = 24.0f;
	constexpr float TODBoundaryTolerance = 0.001f;

	float NormalizeTODTimeForBake(float Time)
	{
		float SafeTime = FMath::Fmod(Time, TODHours);
		if (SafeTime < 0.0f)
		{
			SafeTime += TODHours;
		}

		if (FMath::IsNearlyEqual(SafeTime, TODHours, TODBoundaryTolerance) ||
			FMath::IsNearlyEqual(SafeTime, 0.0f, TODBoundaryTolerance))
		{
			return 0.0f;
		}

		return SafeTime;
	}

	bool IsTwentyFourBoundary(float Time)
	{
		return FMath::IsNearlyEqual(Time, TODHours, TODBoundaryTolerance);
	}

	TArray<FTODMasterData> BuildCanonicalTODData(
		const TArray<FTODMasterData>& SourceData,
		bool bRequireValidPPV)
	{
		struct FCanonicalEntry
		{
			FTODMasterData Data;
			bool bCameFromTwentyFour = false;
		};

		TArray<FCanonicalEntry> Entries;

		for (const FTODMasterData& Source : SourceData)
		{
			if (bRequireValidPPV && !IsValid(Source.PPV))
			{
				continue;
			}

			FTODMasterData Copy = Source;
			const bool bCameFromTwentyFour = IsTwentyFourBoundary(Copy.Time);
			Copy.Time = NormalizeTODTimeForBake(Copy.Time);

			const int32 ExistingIndex = Entries.IndexOfByPredicate(
				[&Copy](const FCanonicalEntry& Entry)
				{
					return FMath::IsNearlyEqual(Entry.Data.Time, Copy.Time, TODBoundaryTolerance);
				});

			if (ExistingIndex == INDEX_NONE)
			{
				FCanonicalEntry NewEntry;
				NewEntry.Data = Copy;
				NewEntry.bCameFromTwentyFour = bCameFromTwentyFour;
				Entries.Add(NewEntry);
			}
			else if (Entries[ExistingIndex].bCameFromTwentyFour && !bCameFromTwentyFour)
			{
				// 0h and 24h are the same instant. If both exist, 0h is the editable source of truth.
				Entries[ExistingIndex].Data = Copy;
				Entries[ExistingIndex].bCameFromTwentyFour = false;
			}
		}

		TArray<FTODMasterData> Result;
		for (const FCanonicalEntry& Entry : Entries)
		{
			Result.Add(Entry.Data);
		}

		Result.Sort([](const FTODMasterData& A, const FTODMasterData& B)
			{
				return A.Time < B.Time;
			});

		return Result;
	}

	void AddTwentyFourBoundaryFromZero(TArray<FTODMasterData>& DataArray)
	{
		const int32 ZeroIndex = DataArray.IndexOfByPredicate(
			[](const FTODMasterData& Data)
			{
				return FMath::IsNearlyEqual(Data.Time, 0.0f, TODBoundaryTolerance);
			});

		if (ZeroIndex == INDEX_NONE)
		{
			return;
		}

		FTODMasterData EndBoundary = DataArray[ZeroIndex];
		EndBoundary.Time = TODHours;
		DataArray.Add(EndBoundary);

		DataArray.Sort([](const FTODMasterData& A, const FTODMasterData& B)
			{
				return A.Time < B.Time;
			});
	}
}

void FTODCurveEvaluator::ApplyPPVBlending(ATODManager* Owner, float CurrentTime)
{
	if (!Owner || !IsValid(Owner->RuntimePPVComponent)) return;

	TArray<FTODMasterData> ValidPPVs = BuildCanonicalTODData(Owner->TOD_DataArray, true);
	AddTwentyFourBoundaryFromZero(ValidPPVs);

	const int32 Num = ValidPPVs.Num();
	if (Num == 0) return;

	for (const FTODMasterData& Data : ValidPPVs)
	{
		if (!IsValid(Data.PPV)) continue;

		Data.PPV->bEnabled = true;
		Data.PPV->bUnbound = true;
		Data.PPV->Priority = 1.0f;
		Data.PPV->BlendWeight = 0.0f;
	}

	const float SafeTime = NormalizeTODTimeForBake(CurrentTime);

	int32 PrevIndex = Num - 1;
	int32 NextIndex = 0;

	for (int32 i = 0; i < Num; ++i)
	{
		if (SafeTime < ValidPPVs[i].Time)
		{
			NextIndex = i;
			PrevIndex = (i == 0) ? (Num - 1) : (i - 1);
			break;
		}
	}

	if (SafeTime >= ValidPPVs[Num - 1].Time)
	{
		PrevIndex = Num - 1;
		NextIndex = 0;
	}

	float PrevTime = ValidPPVs[PrevIndex].Time;
	float NextTime = ValidPPVs[NextIndex].Time;

	float Range = NextTime - PrevTime;
	while (Range <= 0.0f) Range += TODHours;

	float Elapsed = SafeTime - PrevTime;
	while (Elapsed < 0.0f) Elapsed += TODHours;

	const float RawAlpha = FMath::Clamp(Elapsed / Range, 0.0f, 1.0f);

	// PPV exposure is authored as exact time-profile values, so keep the blend
	// linear. SmoothStep can look like exposure is holding and then catching up
	// across short ranges such as 4.0h -> 4.5h.
	const float Alpha = RawAlpha;

	APostProcessVolume* PrevPPV = ValidPPVs[PrevIndex].PPV;
	APostProcessVolume* NextPPV = ValidPPVs[NextIndex].PPV;

	if (!IsValid(PrevPPV) || !IsValid(NextPPV)) return;

	Owner->RuntimePPVComponent->bEnabled = true;
	Owner->RuntimePPVComponent->bUnbound = true;
	Owner->RuntimePPVComponent->Priority = 1.0f;
	Owner->RuntimePPVComponent->BlendWeight = 1.0f;

	// Blend the listed PPV values continuously, but only enable the runtime override
	// when at least one source PPV actually overrides that property.
	// This keeps sparse PPV tracks smooth without reintroducing a hard 24h -> 0h seam.
#define LERP_PPV(Prop) \
	{ \
		const bool bPrevOverride = PrevPPV->Settings.bOverride_##Prop; \
		const bool bNextOverride = NextPPV->Settings.bOverride_##Prop; \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = bPrevOverride || bNextOverride; \
		if (bPrevOverride || bNextOverride) \
		{ \
			Owner->RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha); \
		} \
	}

#define LERP_VEC4_PPV(Prop) LERP_PPV(Prop)

	// Exposure values should always be driven by the runtime TOD PPV.
	// This restores the stable behavior of the older implementation without
	// modifying the source PostProcessVolumes every frame.
#define LERP_PPV_FORCE_OVERRIDE(Prop) \
	{ \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = true; \
		Owner->RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha); \
	}

#define LERP_COLOR_PPV(Prop) \
	{ \
		const bool bPrevOverride = PrevPPV->Settings.bOverride_##Prop; \
		const bool bNextOverride = NextPPV->Settings.bOverride_##Prop; \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = bPrevOverride || bNextOverride; \
		if (bPrevOverride || bNextOverride) \
		{ \
			Owner->RuntimePPVComponent->Settings.Prop = FLinearColor::LerpUsingHSV(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha); \
		} \
	}

	// Exposure / EV100
	LERP_PPV_FORCE_OVERRIDE(AutoExposureMinBrightness);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureMaxBrightness);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureBias);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureSpeedUp);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureSpeedDown);

	// Bloom
	LERP_PPV(BloomIntensity);
	LERP_PPV(BloomThreshold);
	LERP_PPV(BloomSizeScale);
	LERP_PPV(BloomConvolutionIntensity);

	// White Balance
	LERP_PPV(WhiteTemp);
	LERP_PPV(WhiteTint);

	// Color Grading
	LERP_VEC4_PPV(ColorSaturation);
	LERP_VEC4_PPV(ColorContrast);
	LERP_VEC4_PPV(ColorGamma);
	LERP_VEC4_PPV(ColorGain);
	LERP_VEC4_PPV(ColorOffset);

	// Shadows
	LERP_VEC4_PPV(ColorSaturationShadows);
	LERP_VEC4_PPV(ColorContrastShadows);
	LERP_VEC4_PPV(ColorGammaShadows);
	LERP_VEC4_PPV(ColorGainShadows);
	LERP_VEC4_PPV(ColorOffsetShadows);

	// Midtones
	LERP_VEC4_PPV(ColorSaturationMidtones);
	LERP_VEC4_PPV(ColorContrastMidtones);
	LERP_VEC4_PPV(ColorGammaMidtones);
	LERP_VEC4_PPV(ColorGainMidtones);
	LERP_VEC4_PPV(ColorOffsetMidtones);

	// Highlights
	LERP_VEC4_PPV(ColorSaturationHighlights);
	LERP_VEC4_PPV(ColorContrastHighlights);
	LERP_VEC4_PPV(ColorGammaHighlights);
	LERP_VEC4_PPV(ColorGainHighlights);
	LERP_VEC4_PPV(ColorOffsetHighlights);

	// Lens & Effects
	LERP_PPV(VignetteIntensity);
	LERP_PPV(FilmGrainIntensity);
	LERP_PPV(FilmGrainTexelSize);
	LERP_PPV(SceneFringeIntensity);
	LERP_PPV(LensFlareIntensity);
	LERP_PPV(AmbientOcclusionIntensity);
	LERP_PPV(IndirectLightingIntensity);
	LERP_PPV(MotionBlurAmount);

	// Indirect Color
	LERP_COLOR_PPV(IndirectLightingColor);

	// Lumen
	LERP_PPV(LumenSceneLightingQuality);
	LERP_PPV(LumenSceneDetail);

#undef LERP_PPV
#undef LERP_VEC4_PPV
#undef LERP_PPV_FORCE_OVERRIDE
#undef LERP_COLOR_PPV
}

void FTODCurveEvaluator::BakeTODCurves(ATODManager* Owner)
{
	Owner->FindComponents();

	// 구조체 내부 커브 포인터 매핑
	TArray<FRuntimeFloatCurve*> FloatCurves = {
		&Owner->SunCurves.IntensityCurve, &Owner->SunCurves.SourceAngleCurve, &Owner->SunCurves.SourceSoftAngleCurve, &Owner->SunCurves.IndirectIntensityCurve,
		&Owner->MoonCurves.IntensityCurve, &Owner->MoonCurves.SourceAngleCurve, &Owner->MoonCurves.SourceSoftAngleCurve, &Owner->MoonCurves.SourceScaleCurve, &Owner->MoonCurves.SourceEmissiveIntensityCurve,
		&Owner->SkyLightCurves.IntensityCurve, &Owner->SkyLightCurves.IndirectIntensityCurve, &Owner->SkyLightCurves.VolumetricScatteringIntensityCurve, &Owner->SkyLightCurves.TextureEmissiveIntensityCurve,
		&Owner->FogCurves.DensityCurve, &Owner->FogCurves.HeightFalloffCurve,
		&Owner->SkyAtmosphereCurves.MieScatteringScaleCurve, &Owner->SkyAtmosphereCurves.RayleighScatteringScaleCurve, &Owner->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve
	};

	TArray<FRuntimeCurveLinearColor*> ColorCurves = {
		&Owner->SunCurves.LightColorCurve, &Owner->MoonCurves.LightColorCurve, &Owner->SkyLightCurves.LightColorCurve, &Owner->FogCurves.InscatteringColorCurve, &Owner->FogCurves.DirectionalColorCurve,
		&Owner->SkyAtmosphereCurves.MieScatteringColorCurve, &Owner->SkyAtmosphereCurves.AbsorptionColorCurve, &Owner->SkyAtmosphereCurves.SkyLuminanceFactorCurve
	};

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeFloatCurve(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeColorCurve(*Curve); }

	if (Owner->TOD_DataArray.Num() == 0) return;

	TArray<FTODMasterData> SortedCopy = BuildCanonicalTODData(Owner->TOD_DataArray, false);
	if (SortedCopy.Num() == 0) return;

	// If the artist authored 0h or 24h, bake both boundaries from the same full data.
	// This copies every hidden struct field, not only the visible/intensity fields.
	AddTwentyFourBoundaryFromZero(SortedCopy);

	for (const FTODMasterData& Data : SortedCopy)
	{
		float T = Data.Time;

		float FinalSunIntensity = (Data.ActiveLightMode != ETODDirectionalLightType::MoonOnly) ? Data.Sun_Settings.Intensity : 0.0f;
		float FinalMoonIntensity = (Data.ActiveLightMode != ETODDirectionalLightType::SunOnly) ? Data.Moon_Settings.Intensity : 0.0f;

		// Sun
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SunCurves.IntensityCurve, T, FinalSunIntensity, Owner->SunCurves.IntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SunCurves.SourceAngleCurve, T, Data.Sun_Settings.Source_Angle, Owner->SunCurves.SourceAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SunCurves.SourceSoftAngleCurve, T, Data.Sun_Settings.Source_Soft_Angle, Owner->SunCurves.SourceSoftAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SunCurves.IndirectIntensityCurve, T, Data.Sun_Settings.Indirect_Light_Intensity, Owner->SunCurves.IndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->SunCurves.LightColorCurve, T, Data.Sun_Settings.Light_Color, Owner->SunCurves.ColorInterpMode);

		// Moon
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->MoonCurves.IntensityCurve, T, FinalMoonIntensity, Owner->MoonCurves.IntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->MoonCurves.SourceAngleCurve, T, Data.Moon_Settings.Source_Angle, Owner->MoonCurves.SourceAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->MoonCurves.SourceSoftAngleCurve, T, Data.Moon_Settings.Source_Soft_Angle, Owner->MoonCurves.SourceSoftAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->MoonCurves.IndirectIntensityCurve, T, Data.Moon_Settings.Indirect_Light_Intensity, Owner->MoonCurves.IndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->MoonCurves.LightColorCurve, T, Data.Moon_Settings.Light_Color, Owner->MoonCurves.LightColorInterpMode);

		float TargetMoonScale = (Data.ActiveLightMode == ETODDirectionalLightType::SunOnly) ? 0.0f : Data.Moon_Settings.Moon_Source_Scale;
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->MoonCurves.SourceScaleCurve, T, TargetMoonScale, Owner->MoonCurves.SourceScaleInterpMode);

		float TargetMoonEmissive = (Data.ActiveLightMode == ETODDirectionalLightType::SunOnly) ? 0.0f : Data.Moon_Settings.Moon_Source_Emissive_Intensity;
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->MoonCurves.SourceEmissiveIntensityCurve, T, TargetMoonEmissive, Owner->MoonCurves.SourceEmissiveIntensityInterpMode);

		// SkyLight
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SkyLightCurves.IntensityCurve, T, Data.SkyLight_Settings.Sky_Light_Intensity, Owner->SkyLightCurves.IntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SkyLightCurves.IndirectIntensityCurve, T, Data.SkyLight_Settings.Sky_Indirect_Lighting_Intensity, Owner->SkyLightCurves.IndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SkyLightCurves.VolumetricScatteringIntensityCurve, T, Data.SkyLight_Settings.Sky_Volumetric_Scattering_Intensity, Owner->SkyLightCurves.VolumetricScatteringInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->SkyLightCurves.LightColorCurve, T, Data.SkyLight_Settings.Sky_Light_Color, Owner->SkyLightCurves.LightColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SkyLightCurves.TextureEmissiveIntensityCurve, T, Data.SkyLight_Settings.SkyDome_Texture_Emissive_Intensity, Owner->SkyLightCurves.TextureEmissiveIntensityInterpMode);

		// Fog
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->FogCurves.DensityCurve, T, Data.Fog_Settings.Fog_Density, Owner->FogCurves.DensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->FogCurves.HeightFalloffCurve, T, Data.Fog_Settings.Fog_Height_Falloff, Owner->FogCurves.HeightFalloffInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->FogCurves.InscatteringColorCurve, T, Data.Fog_Settings.Fog_Inscattering_Color, Owner->FogCurves.InscatteringColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->FogCurves.DirectionalColorCurve, T, Data.Fog_Settings.Fog_Directional_Inscattering, Owner->FogCurves.DirectionalColorInterpMode);

		// SkyAtmosphere
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SkyAtmosphereCurves.MieScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Scale, Owner->SkyAtmosphereCurves.MieScatteringScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SkyAtmosphereCurves.RayleighScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Rayleigh_Scattering_Scale, Owner->SkyAtmosphereCurves.RayleighScatteringScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve, T, Data.SkyAtmosphere_Settings.Aerial_Perspective_Distance_Scale, Owner->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->SkyAtmosphereCurves.MieScatteringColorCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Color, Owner->SkyAtmosphereCurves.MieScatteringColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->SkyAtmosphereCurves.AbsorptionColorCurve, T, Data.SkyAtmosphere_Settings.Absorption_Color, Owner->SkyAtmosphereCurves.AbsorptionColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->SkyAtmosphereCurves.SkyLuminanceFactorCurve, T, Data.SkyAtmosphere_Settings.Sky_Luminance_Factor, Owner->SkyAtmosphereCurves.SkyLuminanceFactorInterpMode);
	}

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::SealTODCurveFor24Hours(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::SealColorCurveFor24Hours(*Curve); }
}

void FTODCurveEvaluator::GetTODSettingsAtTime(
	ATODManager* Owner,
	float InTime,
	FTODSunMoonSettings& OutSun,
	FTODMoonSettings& OutMoon,
	FTODSkyLightSettings& OutSkyLight,
	FTODFogSettings& OutFog,
	FTODSkyAtmosphereSettings& OutSkyAtmosphere)
{
	if (!Owner) return;

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	// ===== Sun =====
	if (const FRichCurve* Curve = Owner->SunCurves.IntensityCurve.GetRichCurveConst())
		OutSun.Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SunCurves.SourceAngleCurve.GetRichCurveConst())
		OutSun.Source_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SunCurves.SourceSoftAngleCurve.GetRichCurveConst())
		OutSun.Source_Soft_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SunCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSun.Indirect_Light_Intensity = Curve->Eval(SafeTime);

	OutSun.Light_Color = Owner->SunCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== Moon =====
	if (const FRichCurve* Curve = Owner->MoonCurves.IntensityCurve.GetRichCurveConst())
		OutMoon.Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->MoonCurves.SourceAngleCurve.GetRichCurveConst())
		OutMoon.Source_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->MoonCurves.SourceSoftAngleCurve.GetRichCurveConst())
		OutMoon.Source_Soft_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->MoonCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutMoon.Indirect_Light_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->MoonCurves.SourceScaleCurve.GetRichCurveConst())
		OutMoon.Moon_Source_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->MoonCurves.SourceEmissiveIntensityCurve.GetRichCurveConst())
		OutMoon.Moon_Source_Emissive_Intensity = Curve->Eval(SafeTime);

	OutMoon.Light_Color = Owner->MoonCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== SkyLight =====
	if (const FRichCurve* Curve = Owner->SkyLightCurves.IntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Light_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyLightCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Indirect_Lighting_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyLightCurves.VolumetricScatteringIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Volumetric_Scattering_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyLightCurves.TextureEmissiveIntensityCurve.GetRichCurveConst())
		OutSkyLight.SkyDome_Texture_Emissive_Intensity = Curve->Eval(SafeTime);

	OutSkyLight.Sky_Light_Color = Owner->SkyLightCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== Fog =====
	if (const FRichCurve* Curve = Owner->FogCurves.DensityCurve.GetRichCurveConst())
		OutFog.Fog_Density = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->FogCurves.HeightFalloffCurve.GetRichCurveConst())
		OutFog.Fog_Height_Falloff = Curve->Eval(SafeTime);

	OutFog.Fog_Inscattering_Color = Owner->FogCurves.InscatteringColorCurve.GetLinearColorValue(SafeTime);
	OutFog.Fog_Directional_Inscattering = Owner->FogCurves.DirectionalColorCurve.GetLinearColorValue(SafeTime);

	// ===== Atmosphere =====
	if (const FRichCurve* Curve = Owner->SkyAtmosphereCurves.MieScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Mie_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyAtmosphereCurves.RayleighScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Rayleigh_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Aerial_Perspective_Distance_Scale = Curve->Eval(SafeTime);

	OutSkyAtmosphere.Mie_Scattering_Color = Owner->SkyAtmosphereCurves.MieScatteringColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Absorption_Color = Owner->SkyAtmosphereCurves.AbsorptionColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Sky_Luminance_Factor = Owner->SkyAtmosphereCurves.SkyLuminanceFactorCurve.GetLinearColorValue(SafeTime);
}