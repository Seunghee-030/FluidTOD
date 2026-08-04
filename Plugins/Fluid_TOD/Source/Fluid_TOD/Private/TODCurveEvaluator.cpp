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

	// 누락되었던 0시 데이터를 24시 경계값으로 복사해주는 헬퍼 함수 복구
	void AddTwentyFourBoundaryFromZero(TArray<FTODMasterData>& DataArray)
	{
		if (DataArray.Num() == 0) return;

		int32 ZeroIndex = DataArray.IndexOfByPredicate([](const FTODMasterData& Data) {
			return FMath::IsNearlyZero(Data.Time, TODBoundaryTolerance);
			});

		if (ZeroIndex != INDEX_NONE)
		{
			FTODMasterData BoundaryData = DataArray[ZeroIndex];
			BoundaryData.Time = TODHours;
			DataArray.Add(BoundaryData);
		}
	}

	TArray<FTODMasterData> BuildCanonicalTODData(
		const TArray<FTODMasterData>& SourceData,
		bool bRequireValidPPV,
		TArray<FString>* OutDroppedNames = nullptr)
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
				// 0h이 24h 자리를 대체
				Entries[ExistingIndex].Data = Copy;
				Entries[ExistingIndex].bCameFromTwentyFour = false;
			}
			else
			{
				// 예외
				if (OutDroppedNames)
				{
					OutDroppedNames->Add(Copy.Name.IsEmpty() ? TEXT("(Unnamed)") : Copy.Name);
				}
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
}

void FTODCurveEvaluator::ApplyPPVBlending(ATODManager* Owner, float CurrentTime)
{
	if (!Owner || !IsValid(Owner->RuntimePPVComponent)) return;

	TArray<FTODMasterData> ValidPPVs = BuildCanonicalTODData(Owner->TOD_DataArray, true);
	AddTwentyFourBoundaryFromZero(ValidPPVs);

	const int32 Num = ValidPPVs.Num();
	if (Num == 0)
	{
		// TOD 데이터가 모두 삭제되면 런타임 PPV 리셋
		Owner->RuntimePPVComponent->bEnabled = false;
		Owner->RuntimePPVComponent->BlendWeight = 0.0f;
		Owner->RuntimePPVComponent->Settings = FPostProcessSettings();
		return;
	}

	for (const FTODMasterData& Data : ValidPPVs)
	{
		if (!IsValid(Data.PPV)) continue;

		Data.PPV->bEnabled = true;
		Data.PPV->bUnbound = true;
		Data.PPV->Priority = 1.0f;
		Data.PPV->BlendWeight = 0.0f;
	}

	// PPV 1개뿐 일 때.
	if (Num == 1)
	{
		APostProcessVolume* OnlyPPV = ValidPPVs[0].PPV;
		if (!IsValid(OnlyPPV)) return;

		Owner->RuntimePPVComponent->bEnabled = true;
		Owner->RuntimePPVComponent->bUnbound = true;
		Owner->RuntimePPVComponent->Priority = 1.0f;
		Owner->RuntimePPVComponent->BlendWeight = 1.0f;
		Owner->RuntimePPVComponent->Settings = OnlyPPV->Settings;
		return;
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

	const float Alpha = RawAlpha;

	APostProcessVolume* PrevPPV = ValidPPVs[PrevIndex].PPV;
	APostProcessVolume* NextPPV = ValidPPVs[NextIndex].PPV;

	if (!IsValid(PrevPPV) || !IsValid(NextPPV)) return;

	Owner->RuntimePPVComponent->bEnabled = true;
	Owner->RuntimePPVComponent->bUnbound = true;
	Owner->RuntimePPVComponent->Priority = 1.0f;
	Owner->RuntimePPVComponent->BlendWeight = 1.0f;

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
	if (!Owner || !Owner->CurveData)
	{
		return;
	}

	Owner->FindComponents();

	// 구조체 내부 커브 포인터 매핑
	TArray<FRuntimeFloatCurve*> FloatCurves = {
		&Owner->CurveData->SunCurves.IntensityCurve, &Owner->CurveData->SunCurves.SourceAngleCurve, &Owner->CurveData->SunCurves.SourceSoftAngleCurve, &Owner->CurveData->SunCurves.IndirectIntensityCurve,
		&Owner->CurveData->MoonCurves.IntensityCurve, &Owner->CurveData->MoonCurves.SourceAngleCurve, &Owner->CurveData->MoonCurves.SourceSoftAngleCurve, &Owner->CurveData->MoonCurves.SourceScaleCurve, &Owner->CurveData->MoonCurves.SourceEmissiveIntensityCurve,
		&Owner->CurveData->SkyLightCurves.IntensityCurve, &Owner->CurveData->SkyLightCurves.IndirectIntensityCurve, &Owner->CurveData->SkyLightCurves.VolumetricScatteringIntensityCurve, &Owner->CurveData->SkyLightCurves.TextureEmissiveIntensityCurve,
		&Owner->CurveData->FogCurves.DensityCurve, &Owner->CurveData->FogCurves.HeightFalloffCurve,
		&Owner->CurveData->SkyAtmosphereCurves.MieScatteringScaleCurve, &Owner->CurveData->SkyAtmosphereCurves.RayleighScatteringScaleCurve, &Owner->CurveData->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve
	};

	TArray<FRuntimeCurveLinearColor*> ColorCurves = {
		&Owner->CurveData->SunCurves.LightColorCurve, &Owner->CurveData->MoonCurves.LightColorCurve, &Owner->CurveData->SkyLightCurves.LightColorCurve, &Owner->CurveData->FogCurves.InscatteringColorCurve, &Owner->CurveData->FogCurves.DirectionalColorCurve,
		&Owner->CurveData->SkyAtmosphereCurves.MieScatteringColorCurve, &Owner->CurveData->SkyAtmosphereCurves.AbsorptionColorCurve, &Owner->CurveData->SkyAtmosphereCurves.SkyLuminanceFactorCurve
	};

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeFloatCurve(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeColorCurve(*Curve); }

	if (Owner->TOD_DataArray.Num() == 0) return;

	TArray<FString> DroppedNames;
	TArray<FTODMasterData> SortedCopy =
		BuildCanonicalTODData(Owner->TOD_DataArray, false, &DroppedNames);
	if (SortedCopy.Num() == 0) return;

	AddTwentyFourBoundaryFromZero(SortedCopy);

#if WITH_EDITOR
	if (DroppedNames.Num() > 0)
	{
		FNotificationInfo Info(FText::Format(
			FText::FromString(TEXT("The following items were ignored due to duplicate times: {0}")),
			FText::FromString(FString::Join(DroppedNames, TEXT(", ")))));
		Info.ExpireDuration = 5.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
#endif

	for (const FTODMasterData& Data : SortedCopy)
	{
		float T = Data.Time;

		float FinalSunIntensity = (Data.ActiveLightMode != ETODDirectionalLightType::MoonOnly) ? Data.Sun_Settings.Intensity : 0.0f;
		float FinalMoonIntensity = (Data.ActiveLightMode != ETODDirectionalLightType::SunOnly) ? Data.Moon_Settings.Intensity : 0.0f;

		// Sun
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.IntensityCurve, T, FinalSunIntensity, Owner->CurveData->SunCurves.IntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.SourceAngleCurve, T, Data.Sun_Settings.Source_Angle, Owner->CurveData->SunCurves.SourceAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.SourceSoftAngleCurve, T, Data.Sun_Settings.Source_Soft_Angle, Owner->CurveData->SunCurves.SourceSoftAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.IndirectIntensityCurve, T, Data.Sun_Settings.Indirect_Light_Intensity, Owner->CurveData->SunCurves.IndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SunCurves.LightColorCurve, T, Data.Sun_Settings.Light_Color, Owner->CurveData->SunCurves.ColorInterpMode);

		// Moon
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.IntensityCurve, T, FinalMoonIntensity, Owner->CurveData->MoonCurves.IntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceAngleCurve, T, Data.Moon_Settings.Source_Angle, Owner->CurveData->MoonCurves.SourceAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceSoftAngleCurve, T, Data.Moon_Settings.Source_Soft_Angle, Owner->CurveData->MoonCurves.SourceSoftAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.IndirectIntensityCurve, T, Data.Moon_Settings.Indirect_Light_Intensity, Owner->CurveData->MoonCurves.IndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->MoonCurves.LightColorCurve, T, Data.Moon_Settings.Light_Color, Owner->CurveData->MoonCurves.LightColorInterpMode);

		float TargetMoonScale = (Data.ActiveLightMode == ETODDirectionalLightType::SunOnly) ? 0.0f : Data.Moon_Settings.Moon_Source_Scale;
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceScaleCurve, T, TargetMoonScale, Owner->CurveData->MoonCurves.SourceScaleInterpMode);

		float TargetMoonEmissive = (Data.ActiveLightMode == ETODDirectionalLightType::SunOnly) ? 0.0f : Data.Moon_Settings.Moon_Source_Emissive_Intensity;
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceEmissiveIntensityCurve, T, TargetMoonEmissive, Owner->CurveData->MoonCurves.SourceEmissiveIntensityInterpMode);

		// SkyLight
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.IntensityCurve, T, Data.SkyLight_Settings.Sky_Light_Intensity, Owner->CurveData->SkyLightCurves.IntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.IndirectIntensityCurve, T, Data.SkyLight_Settings.Sky_Indirect_Lighting_Intensity, Owner->CurveData->SkyLightCurves.IndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.VolumetricScatteringIntensityCurve, T, Data.SkyLight_Settings.Sky_Volumetric_Scattering_Intensity, Owner->CurveData->SkyLightCurves.VolumetricScatteringInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyLightCurves.LightColorCurve, T, Data.SkyLight_Settings.Sky_Light_Color, Owner->CurveData->SkyLightCurves.LightColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.TextureEmissiveIntensityCurve, T, Data.SkyLight_Settings.SkyDome_Texture_Emissive_Intensity, Owner->CurveData->SkyLightCurves.TextureEmissiveIntensityInterpMode);

		// Fog
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->FogCurves.DensityCurve, T, Data.Fog_Settings.Fog_Density, Owner->CurveData->FogCurves.DensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->FogCurves.HeightFalloffCurve, T, Data.Fog_Settings.Fog_Height_Falloff, Owner->CurveData->FogCurves.HeightFalloffInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->FogCurves.InscatteringColorCurve, T, Data.Fog_Settings.Fog_Inscattering_Color, Owner->CurveData->FogCurves.InscatteringColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->FogCurves.DirectionalColorCurve, T, Data.Fog_Settings.Fog_Directional_Inscattering, Owner->CurveData->FogCurves.DirectionalColorInterpMode);

		// SkyAtmosphere
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyAtmosphereCurves.MieScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Scale, Owner->CurveData->SkyAtmosphereCurves.MieScatteringScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyAtmosphereCurves.RayleighScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Rayleigh_Scattering_Scale, Owner->CurveData->SkyAtmosphereCurves.RayleighScatteringScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve, T, Data.SkyAtmosphere_Settings.Aerial_Perspective_Distance_Scale, Owner->CurveData->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyAtmosphereCurves.MieScatteringColorCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Color, Owner->CurveData->SkyAtmosphereCurves.MieScatteringColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyAtmosphereCurves.AbsorptionColorCurve, T, Data.SkyAtmosphere_Settings.Absorption_Color, Owner->CurveData->SkyAtmosphereCurves.AbsorptionColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyAtmosphereCurves.SkyLuminanceFactorCurve, T, Data.SkyAtmosphere_Settings.Sky_Luminance_Factor, Owner->CurveData->SkyAtmosphereCurves.SkyLuminanceFactorInterpMode);
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
	if (!Owner || !Owner->CurveData) return;

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	// ===== Sun =====
	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.IntensityCurve.GetRichCurveConst())
		OutSun.Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.SourceAngleCurve.GetRichCurveConst())
		OutSun.Source_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.SourceSoftAngleCurve.GetRichCurveConst())
		OutSun.Source_Soft_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSun.Indirect_Light_Intensity = Curve->Eval(SafeTime);

	OutSun.Light_Color = Owner->CurveData->SunCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== Moon =====
	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.IntensityCurve.GetRichCurveConst())
		OutMoon.Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceAngleCurve.GetRichCurveConst())
		OutMoon.Source_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceSoftAngleCurve.GetRichCurveConst())
		OutMoon.Source_Soft_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutMoon.Indirect_Light_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceScaleCurve.GetRichCurveConst())
		OutMoon.Moon_Source_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceEmissiveIntensityCurve.GetRichCurveConst())
		OutMoon.Moon_Source_Emissive_Intensity = Curve->Eval(SafeTime);

	OutMoon.Light_Color = Owner->CurveData->MoonCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== SkyLight =====
	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.IntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Light_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Indirect_Lighting_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.VolumetricScatteringIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Volumetric_Scattering_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.TextureEmissiveIntensityCurve.GetRichCurveConst())
		OutSkyLight.SkyDome_Texture_Emissive_Intensity = Curve->Eval(SafeTime);

	OutSkyLight.Sky_Light_Color = Owner->CurveData->SkyLightCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== Fog =====
	if (const FRichCurve* Curve = Owner->CurveData->FogCurves.DensityCurve.GetRichCurveConst())
		OutFog.Fog_Density = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->FogCurves.HeightFalloffCurve.GetRichCurveConst())
		OutFog.Fog_Height_Falloff = Curve->Eval(SafeTime);

	OutFog.Fog_Inscattering_Color = Owner->CurveData->FogCurves.InscatteringColorCurve.GetLinearColorValue(SafeTime);
	OutFog.Fog_Directional_Inscattering = Owner->CurveData->FogCurves.DirectionalColorCurve.GetLinearColorValue(SafeTime);

	// ===== Atmosphere =====
	if (const FRichCurve* Curve = Owner->CurveData->SkyAtmosphereCurves.MieScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Mie_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyAtmosphereCurves.RayleighScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Rayleigh_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Aerial_Perspective_Distance_Scale = Curve->Eval(SafeTime);

	OutSkyAtmosphere.Mie_Scattering_Color = Owner->CurveData->SkyAtmosphereCurves.MieScatteringColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Absorption_Color = Owner->CurveData->SkyAtmosphereCurves.AbsorptionColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Sky_Luminance_Factor = Owner->CurveData->SkyAtmosphereCurves.SkyLuminanceFactorCurve.GetLinearColorValue(SafeTime);
}

float FTODCurveEvaluator::GetMoonSourceScaleAtTime(const ATODManager* Owner, float InTime) const
{
	if (!Owner || !Owner->CurveData)
	{
		return 0.0f;
	}

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceScaleCurve.GetRichCurveConst())
	{
		return Curve->Eval(SafeTime);
	}

	return 0.0f;
}

float FTODCurveEvaluator::GetMoonIntensity(const ATODManager* Owner, float InTime) const
{
	if (!Owner || !Owner->CurveData)
	{
		return 0.0f;
	}

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.IntensityCurve.GetRichCurveConst())
	{
		return Curve->Eval(SafeTime);
	}

	return 0.0f;
}

float FTODCurveEvaluator::GetSunIntensity(const ATODManager* Owner, float InTime) const
{
	if (!Owner || !Owner->CurveData)
	{
		return 0.0f;
	}

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.IntensityCurve.GetRichCurveConst())
	{
		return Curve->Eval(SafeTime);
	}

	return 0.0f;
}