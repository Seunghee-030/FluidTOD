#include "TODCurveEvaluator.h"
#include "TODManager.h"
#include "MyBlueprintFunctionLibrary.h"

void FTODCurveEvaluator::ApplyPPVBlending(ATODManager* Owner, float CurrentTime)
{
	if (!Owner || !IsValid(Owner->RuntimePPVComponent)) return;

	TArray<FTODMasterData> ValidPPVs;
	for (const FTODMasterData& Data : Owner->TOD_DataArray)
	{
		if (IsValid(Data.PPV))
			ValidPPVs.Add(Data);
	}

	const int32 Num = ValidPPVs.Num();

	if (Num == 0)
	{
		Owner->RuntimePPVComponent->bEnabled = false;
		Owner->RuntimePPVComponent->Settings = FPostProcessSettings();
		return;
	}

	Owner->RuntimePPVComponent->bEnabled = true;

	ValidPPVs.Sort([](const FTODMasterData& A, const FTODMasterData& B) {
		return A.Time < B.Time;
		});

	for (const FTODMasterData& Data : ValidPPVs)
	{
		Data.PPV->BlendWeight = 0.0f;
		Data.PPV->Priority = -10;
	}

	float SafeTime = CurrentTime;
	while (SafeTime >= 24.0f) SafeTime -= 24.0f;
	while (SafeTime < 0.0f) SafeTime += 24.0f;

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
	while (Range <= 0.0f) Range += 24.0f;

	float Elapsed = SafeTime - PrevTime;
	while (Elapsed < 0.0f) Elapsed += 24.0f;

	float Alpha = FMath::Clamp(Elapsed / Range, 0.0f, 1.0f);

	APostProcessVolume* PrevPPV = ValidPPVs[PrevIndex].PPV;
	APostProcessVolume* NextPPV = ValidPPVs[NextIndex].PPV;

	Owner->RuntimePPVComponent->bEnabled = true;
	Owner->RuntimePPVComponent->bUnbound = true;
	Owner->RuntimePPVComponent->Priority = 0;	// 고정된 PPV Priority
	Owner->RuntimePPVComponent->BlendWeight = 1.0f;

	// ---보간용 매크로

	// float
#define LERP_PPV(Prop) \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		Owner->RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

	// FVector4
#define LERP_VEC4_PPV(Prop) \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		Owner->RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

	// FLinearColor
#define LERP_COLOR_PPV(Prop) \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		Owner->RuntimePPVComponent->Settings.Prop = FLinearColor::LerpUsingHSV(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

// Exposure
	LERP_PPV(AutoExposureMinBrightness);
	LERP_PPV(AutoExposureMaxBrightness);
	LERP_PPV(AutoExposureBias);
	LERP_PPV(AutoExposureSpeedUp);
	LERP_PPV(AutoExposureSpeedDown);

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
#undef LERP_COLOR_PPV
}

void FTODCurveEvaluator::BakeTODCurves(ATODManager* Owner)
{
	Owner->FindComponents();

	if (Owner->TOD_DataArray.Num() == 0) return;

	TArray<FTODMasterData> SortedCopy = Owner->TOD_DataArray;
	SortedCopy.Sort([](const FTODMasterData& A, const FTODMasterData& B) {
		return A.Time < B.Time;
		});

	// 구조체 내부 커브 포인터 매핑
	TArray<FRuntimeFloatCurve*> FloatCurves = {
		&Owner->SunCurves.IntensityCurve, &Owner->SunCurves.SourceAngleCurve, &Owner->SunCurves.SourceSoftAngleCurve, & Owner->SunCurves.IndirectIntensityCurve,
		& Owner->MoonCurves.IntensityCurve, & Owner->MoonCurves.SourceAngleCurve, & Owner->MoonCurves.SourceSoftAngleCurve, & Owner->MoonCurves.SourceScaleCurve, &Owner->MoonCurves.SourceEmissiveIntensityCurve,
		& Owner->SkyLightCurves.IntensityCurve, & Owner->SkyLightCurves.IndirectIntensityCurve, & Owner->SkyLightCurves.VolumetricScatteringIntensityCurve, &Owner->SkyLightCurves.TextureEmissiveIntensityCurve,
		& Owner->FogCurves.DensityCurve, & Owner->FogCurves.HeightFalloffCurve,
		& Owner->SkyAtmosphereCurves.MieScatteringScaleCurve, & Owner->SkyAtmosphereCurves.RayleighScatteringScaleCurve, & Owner->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve
	};

	TArray<FRuntimeCurveLinearColor*> ColorCurves = {
		&Owner->SunCurves.ColorCurve, &Owner->MoonCurves.LightColorCurve, &Owner->SkyLightCurves.LightColorCurve, &Owner->FogCurves.InscatteringColorCurve, &Owner->FogCurves.DirectionalColorCurve,
		&Owner->SkyAtmosphereCurves.MieScatteringColorCurve, &Owner->SkyAtmosphereCurves.AbsorptionColorCurve, &Owner->SkyAtmosphereCurves.SkyLuminanceFactorCurve
	};

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeFloatCurve(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeColorCurve(*Curve); }

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
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->SunCurves.ColorCurve, T, Data.Sun_Settings.Light_Color, Owner->SunCurves.ColorInterpMode);

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

	float SafeTime = FMath::Fmod(InTime, 24.0f);
	if (SafeTime < 0.0f)
	{
		SafeTime += 24.0f;
	}

	// ===== Sun =====
	if (const FRichCurve* Curve = Owner->SunCurves.IntensityCurve.GetRichCurveConst())
		OutSun.Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SunCurves.SourceAngleCurve.GetRichCurveConst())
		OutSun.Source_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SunCurves.SourceSoftAngleCurve.GetRichCurveConst())
		OutSun.Source_Soft_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SunCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSun.Indirect_Light_Intensity = Curve->Eval(SafeTime);


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


	// ===== SkyLight =====
	if (const FRichCurve* Curve = Owner->SkyLightCurves.IntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Light_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyLightCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Indirect_Lighting_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyLightCurves.VolumetricScatteringIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Volumetric_Scattering_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyLightCurves.TextureEmissiveIntensityCurve.GetRichCurveConst())
		OutSkyLight.SkyDome_Texture_Emissive_Intensity = Curve->Eval(SafeTime);

	// ===== Fog =====
	if (const FRichCurve* Curve = Owner->FogCurves.DensityCurve.GetRichCurveConst())
		OutFog.Fog_Density = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->FogCurves.HeightFalloffCurve.GetRichCurveConst())
		OutFog.Fog_Height_Falloff = Curve->Eval(SafeTime);

	// ===== Atmosphere =====
	if (const FRichCurve* Curve = Owner->SkyAtmosphereCurves.MieScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Mie_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyAtmosphereCurves.RayleighScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Rayleigh_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Aerial_Perspective_Distance_Scale = Curve->Eval(SafeTime);
}