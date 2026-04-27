#include "TODManager.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/PostProcessComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#if WITH_EDITOR
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

ATODManager::ATODManager()
{
	PrimaryActorTick.bCanEverTick = false;

	RuntimePPVComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("RuntimePPVComponent"));

	if (RootComponent)
	{
		RuntimePPVComponent->SetupAttachment(RootComponent);
	}
	else
	{
		RootComponent = RuntimePPVComponent;
	}

	RuntimePPVComponent->bUnbound = true;
	RuntimePPVComponent->Priority = 100;
}

// 🐛 Debug System
void ATODManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DebugTimerHandle, this, &ATODManager::PrintTODDebugInfo, DebugPrintInterval, true);
}

void ATODManager::PrintTODDebugInfo()
{
	if (!bEnableDebugPrint || !GEngine) return;

	FTODSunMoonSettings SunMoon;
	FTODSkyLightSettings Sky;
	FTODFogSettings Fog;
	FTODSkyAtmosphereSettings Atmos;
	GetTODSettingsAtTime(CurrentSystemTime, SunMoon, Sky, Fog, Atmos);

	float CurrentBloom = 0.0f;
	float CurrentExpMin = 0.0f;
	float CurrentTemp = 6500.0f;
	FVector4 CurrentSaturation = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

	if (IsValid(RuntimePPVComponent))
	{
		CurrentBloom = RuntimePPVComponent->Settings.BloomIntensity;
		CurrentExpMin = RuntimePPVComponent->Settings.AutoExposureMinBrightness;
		CurrentTemp = RuntimePPVComponent->Settings.WhiteTemp;
		CurrentSaturation = RuntimePPVComponent->Settings.ColorSaturation;
	}

	FString DebugMsg = FString::Printf(TEXT(
		"=== TOD System Debug ===\n"
		"Time: %.2f\n"
		"-------------------------\n"
		"[Sun/Moon] Intensity: %.2f / Angle: %.1f\n"
		"[SkyLight] Curve: %.2f\n"
		"[SkyIndirect] Curve: %.2f\n"
		"[Fog] Density: %.5f\n"
		"[Atmos] Rayleigh Scale: %.5f\n"
		"-------------------------\n"
		"[PPV] Bloom: %.2f | Exp Min: %.2f\n"
		"[PPV] White Temp: %.0fK\n"
		"[PPV] Saturation: (R:%.2f, G:%.2f, B:%.2f)"
	),
		CurrentSystemTime,
		SunMoon.Intensity, SunMoon.SourceAngle,
		Sky.Sky_Light_Intensity, 
		Sky.Sky_Indirect_Lighting_Intensity,
		Fog.Fog_Density,
		Atmos.Rayleigh_Scattering_Scale,
		CurrentBloom, CurrentExpMin,
		CurrentTemp,
		CurrentSaturation.X, CurrentSaturation.Y, CurrentSaturation.Z
	);

	// 화면 출력
	GEngine->AddOnScreenDebugMessage(1357, DebugPrintInterval + 0.1f, FColor::Yellow, DebugMsg);

}

// System
void ATODManager::SortTODDataArray()
{
	if (TOD_DataArray.Num() < 2) return;
	TOD_DataArray.Sort([](const FTODMasterData& A, const FTODMasterData& B) { return A.Time < B.Time; });
}

// Presets
void ATODManager::SaveToSinglePreset(int32 Index, UTODSinglePreset* Preset)
{
	if (!IsValid(Preset)) return;

	if (!TOD_DataArray.IsValidIndex(Index)) return;

	Preset->SavedData = TOD_DataArray[Index];
	Preset->MarkPackageDirty();
}

void ATODManager::LoadFromSinglePreset(UTODSinglePreset* Preset, int32 Index)
{
	if (!IsValid(Preset)) return;
	if (!TOD_DataArray.IsValidIndex(Index)) return;

	TOD_DataArray[Index] = Preset->SavedData;
}

void ATODManager::SaveToFullPreset(UTODPresetData* Preset)
{
	if (!IsValid(Preset)) return;

	Preset->TOD_DataArray = TOD_DataArray;
	Preset->MarkPackageDirty();
}

void ATODManager::LoadFromFullPreset(UTODPresetData* Preset)
{
	if (!IsValid(Preset)) return;

	TOD_DataArray = Preset->TOD_DataArray;

#if WITH_EDITOR
	BakeTODCurves();
#endif
}

// PPV
void ATODManager::GetTODInterpolationData(float CurrentTime, int32& OutPrevIndex, int32& OutNextIndex, float& OutAlpha)
{
	OutPrevIndex = 0; OutNextIndex = 0; OutAlpha = 0.0f;
	const int32 Num = TOD_DataArray.Num();
	if (Num < 2) return;

	float SafeTime = FMath::Fmod(CurrentTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	OutPrevIndex = Num - 1;
	for (int32 i = 0; i < Num - 1; ++i)
	{
		if (SafeTime >= TOD_DataArray[i].Time && SafeTime < TOD_DataArray[i + 1].Time)
		{
			OutPrevIndex = i;
			break;
		}
	}
	OutNextIndex = (OutPrevIndex + 1) % Num;

	float PrevTime = TOD_DataArray[OutPrevIndex].Time;
	float NextTime = TOD_DataArray[OutNextIndex].Time;
	float AdjustedCurrentTime = SafeTime;

	if (NextTime < PrevTime)
	{
		NextTime += 24.0f;
		if (AdjustedCurrentTime < TOD_DataArray[0].Time) AdjustedCurrentTime += 24.0f;
	}

	float TimeDiff = NextTime - PrevTime;
	if (TimeDiff > KINDA_SMALL_NUMBER)
	{
		OutAlpha = FMath::Clamp((AdjustedCurrentTime - PrevTime) / TimeDiff, 0.0f, 1.0f);
	}
}

void ATODManager::ApplyPPVBlending(float CurrentTime)
{
	if (!IsValid(RuntimePPVComponent)) return;

	TArray<FTODMasterData> ValidPPVs;
	for (const FTODMasterData& Data : TOD_DataArray)
	{
		if (IsValid(Data.PPV)) ValidPPVs.Add(Data);
	}

	const int32 Num = ValidPPVs.Num();
	if (Num == 0) return;

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

	RuntimePPVComponent->bEnabled = true;
	RuntimePPVComponent->bUnbound = true;
	RuntimePPVComponent->Priority = 0;
	RuntimePPVComponent->BlendWeight = 1.0f;

	// ---보간용 매크로

	// float
#define LERP_PPV(Prop) \
		RuntimePPVComponent->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

	// FVector4
#define LERP_VEC4_PPV(Prop) \
		RuntimePPVComponent->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

	// FLinearColor
#define LERP_COLOR_PPV(Prop) \
		RuntimePPVComponent->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		RuntimePPVComponent->Settings.Prop = FLinearColor::LerpUsingHSV(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

// Exposure
	LERP_PPV(AutoExposureMinBrightness);
	LERP_PPV(AutoExposureMaxBrightness);
	LERP_PPV(AutoExposureBias);
	LERP_PPV(AutoExposureSpeedUp);
	LERP_PPV(AutoExposureSpeedDown);
	LERP_PPV(AutoExposureApplyPhysicalCameraExposure);

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

void ATODManager::SaveNewPreset()
{
#if WITH_EDITOR
	FString Timestamp = FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S"));
	FString AssetName = FString::Printf(TEXT("TOD_Preset_%s"), *Timestamp);
	FString PackagePath = TEXT("/Game/TOD_Presets/");

	IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

	UTODPresetData* NewAsset = Cast<UTODPresetData>(AssetTools.CreateAsset(
		AssetName,
		PackagePath,
		UTODPresetData::StaticClass(),
		nullptr
	));

	if (NewAsset)
	{
		NewAsset->TOD_DataArray = TOD_DataArray;
		for (FTODMasterData& Data : NewAsset->TOD_DataArray) { Data.PPV = nullptr; }

		NewAsset->MarkPackageDirty();
		FAssetRegistryModule::AssetCreated(NewAsset);
		LoadPreset = NewAsset;

		FNotificationInfo Info(FText::Format(FText::FromString(TEXT("Created: {0}")), FText::FromString(AssetName)));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);

		UE_LOG(LogTemp, Log, TEXT("Fluid TOD: New preset created at %s/%s"), *PackagePath, *AssetName);
	}
#endif
}

void ATODManager::LoadSelectedPreset()
{
	if (!LoadPreset) return;
	if (LoadPreset->TOD_DataArray.Num() == 0) return;

	TOD_DataArray = LoadPreset->TOD_DataArray;
	MarkPackageDirty();

	UE_LOG(LogTemp, Warning, TEXT("Fluid_TOD: Preset '%s' loaded successfully!"), *LoadPreset->GetName());
}

void ATODManager::FindComponents()
{
	TArray<UDirectionalLightComponent*> Lights;
	GetComponents<UDirectionalLightComponent>(Lights);

	SunLightComponent = nullptr;
	MoonLightComponent = nullptr;

	for (UDirectionalLightComponent* Light : Lights)
	{
		// 이름에 Moon 들어가면 Moon으로 인식
		if (Light->GetName().Contains(TEXT("Moon"), ESearchCase::IgnoreCase))
		{
			MoonLightComponent = Light;
		}
		else
		{
			SunLightComponent = Light;
		}
	}

	SkyLightComponent = FindComponentByClass<USkyLightComponent>();
	FogComponent = FindComponentByClass<UExponentialHeightFogComponent>();
	SkyAtmosphereComponent = FindComponentByClass<USkyAtmosphereComponent>();
}

void ATODManager::BakeTODCurves()
{
	FindComponents();

	if (TOD_DataArray.Num() == 0) return;

	SortTODDataArray();

	TArray<FRuntimeFloatCurve*> FloatCurves = {
		&SunIntensityCurve, &SunSourceAngleCurve, &SunSourceSoftAngleCurve, &SunIndirectIntensityCurve,
		&SkyLightIntensityCurve, &SkyLightIndirectIntensityCurve, &SkyLightVolumetricScatteringIntensityCurve,
		&FogDensityCurve, &FogHeightFalloffCurve,
		&MieScatteringScaleCurve, &RayleighScatteringScaleCurve, &AerialPerspectiveDistanceScaleCurve
	};

	TArray<FRuntimeCurveLinearColor*> ColorCurves = {
		&SunColorCurve, &SkyColorCurve, &FogInscatteringColorCurve, &FogDirectionalColorCurve,
		&MieScatteringColorCurve, &AbsorptionColorCurve, &SkyLuminanceFactorCurve
	};

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeFloatCurve(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeColorCurve(*Curve); }

	for (const FTODMasterData& Data : TOD_DataArray)
	{
		float T = Data.Time;

		// Sun & Moon
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunIntensityCurve, T, Data.SunMoon_Settings.Intensity, SunIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunSourceAngleCurve, T, Data.SunMoon_Settings.SourceAngle, SunSourceAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunSourceSoftAngleCurve, T, Data.SunMoon_Settings.SourceSoftAngle, SunSourceSoftAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunIndirectIntensityCurve, T, Data.SunMoon_Settings.IndirectLightingIntensity, SunIndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(SunColorCurve, T, Data.SunMoon_Settings.Color, SunColorInterpMode);

		// SkyLight
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SkyLightIntensityCurve, T, Data.SkyLight_Settings.Sky_Light_Intensity, SkyLightIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SkyLightIndirectIntensityCurve, T, Data.SkyLight_Settings.Sky_Indirect_Lighting_Intensity, SkyLightIndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SkyLightVolumetricScatteringIntensityCurve, T, Data.SkyLight_Settings.Sky_Volumetric_Scattering_Intensity, SkyLightVolumetricScatteringInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(SkyColorCurve, T, Data.SkyLight_Settings.Sky_Light_Color, SkyColorInterpMode);

		// Fog
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(FogDensityCurve, T, Data.Fog_Settings.Fog_Density, FogDensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(FogHeightFalloffCurve, T, Data.Fog_Settings.Fog_Height_Falloff, FogHeightFalloffInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(FogInscatteringColorCurve, T, Data.Fog_Settings.Fog_Inscattering_Color, FogInscatteringColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(FogDirectionalColorCurve, T, Data.Fog_Settings.Fog_Directional_Inscattering, FogDirectionalColorInterpMode);

		// Sky Atmosphere
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(MieScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Scale, MieScatteringScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(RayleighScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Rayleigh_Scattering_Scale, RayleighScatteringScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(AerialPerspectiveDistanceScaleCurve, T, Data.SkyAtmosphere_Settings.Aerial_Perspective_Distance_Scale, AerialPerspectiveDistanceScaleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(MieScatteringColorCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Color, MieScatteringColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(AbsorptionColorCurve, T, Data.SkyAtmosphere_Settings.Absorption_Color, AbsorptionColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(SkyLuminanceFactorCurve, T, Data.SkyAtmosphere_Settings.Sky_Luminance_Factor, SkyLuminanceFactorInterpMode);
	}

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::SealTODCurveFor24Hours(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::SealColorCurveFor24Hours(*Curve); }
}

void ATODManager::GetTODSettingsAtTime(
	float InTime,
	FTODSunMoonSettings& OutSunMoon,
	FTODSkyLightSettings& OutSkyLight,
	FTODFogSettings& OutFog,
	FTODSkyAtmosphereSettings& OutSkyAtmosphere)
{
	float SafeTime = FMath::Fmod(InTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	if (const FRichCurve* Curve = SunIntensityCurve.GetRichCurveConst()) OutSunMoon.Intensity = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = SunSourceAngleCurve.GetRichCurveConst()) OutSunMoon.SourceAngle = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = SunSourceSoftAngleCurve.GetRichCurveConst()) OutSunMoon.SourceSoftAngle = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = SunIndirectIntensityCurve.GetRichCurveConst()) OutSunMoon.IndirectLightingIntensity = Curve->Eval(SafeTime);
	OutSunMoon.Color = SunColorCurve.GetLinearColorValue(SafeTime);
	OutSunMoon.bVisible = OutSunMoon.Intensity > 0.0f;

	if (const FRichCurve* Curve = SkyLightIntensityCurve.GetRichCurveConst()) OutSkyLight.Sky_Light_Intensity = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = SkyLightIndirectIntensityCurve.GetRichCurveConst()) OutSkyLight.Sky_Indirect_Lighting_Intensity = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = SkyLightVolumetricScatteringIntensityCurve.GetRichCurveConst()) OutSkyLight.Sky_Volumetric_Scattering_Intensity = Curve->Eval(SafeTime);
	OutSkyLight.Sky_Light_Color = SkyColorCurve.GetLinearColorValue(SafeTime);

	if (const FRichCurve* Curve = FogDensityCurve.GetRichCurveConst()) OutFog.Fog_Density = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = FogHeightFalloffCurve.GetRichCurveConst()) OutFog.Fog_Height_Falloff = Curve->Eval(SafeTime);
	OutFog.Fog_Inscattering_Color = FogInscatteringColorCurve.GetLinearColorValue(SafeTime);
	OutFog.Fog_Directional_Inscattering = FogDirectionalColorCurve.GetLinearColorValue(SafeTime);

	if (const FRichCurve* Curve = MieScatteringScaleCurve.GetRichCurveConst()) OutSkyAtmosphere.Mie_Scattering_Scale = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = RayleighScatteringScaleCurve.GetRichCurveConst()) OutSkyAtmosphere.Rayleigh_Scattering_Scale = Curve->Eval(SafeTime);
	if (const FRichCurve* Curve = AerialPerspectiveDistanceScaleCurve.GetRichCurveConst()) OutSkyAtmosphere.Aerial_Perspective_Distance_Scale = Curve->Eval(SafeTime);
	OutSkyAtmosphere.Mie_Scattering_Color = MieScatteringColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Absorption_Color = AbsorptionColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Sky_Luminance_Factor = SkyLuminanceFactorCurve.GetLinearColorValue(SafeTime);
}

void ATODManager::UpdateTOD(float CurrentTime)
{
	CurrentSystemTime = CurrentTime;

	if (TOD_DataArray.Num() == 0) return;

	if (!SkyLightComponent) FindComponents();

	int32 PrevIndex, NextIndex;
	float Alpha;
	GetTODInterpolationData(CurrentTime, PrevIndex, NextIndex, Alpha);

	// 런타임 PPV 사용
	ApplyPPVBlending(CurrentTime);

	FTODSunMoonSettings SunMoon;
	FTODSkyLightSettings Sky;
	FTODFogSettings Fog;
	FTODSkyAtmosphereSettings Atmos;
	GetTODSettingsAtTime(CurrentTime, SunMoon, Sky, Fog, Atmos);

	float NightAlpha = 0.0f;
	float SafeTime = FMath::Fmod(CurrentTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	if (SafeTime >= 18.0f)
	{
		NightAlpha = (SafeTime - 18.0f) / 6.0f;
	}
	else if (SafeTime <= 6.0f)
	{
		NightAlpha = 1.0f - (SafeTime / 6.0f);
	}

	// 컴포넌트 값 업데이트
	if (IsValid(SunLightComponent))
	{
		SunLightComponent->SetIntensity(SunMoon.Intensity);
		SunLightComponent->SetLightColor(SunMoon.Color);
		SunLightComponent->SetLightSourceAngle(SunMoon.SourceAngle);
		SunLightComponent->SetLightSourceSoftAngle(SunMoon.SourceSoftAngle);
		SunLightComponent->SetIndirectLightingIntensity(SunMoon.IndirectLightingIntensity);
		SunLightComponent->SetVisibility(SunMoon.bVisible);
	}


	// bAtmosphereSunLight 해제로 인한 부자연스러움,, 밤 일때 가중치 부여
	if (IsValid(MoonLightComponent))
	{
		if (MoonLightComponent->bAtmosphereSunLight)
		{
			MoonLightComponent->bAtmosphereSunLight = false;
		}

		// 지평선 보정 가중치 계산
		float MoonPitch = MoonLightComponent->GetComponentRotation().Pitch;
		float HorizonAlpha = FMath::Clamp(1.0f - (FMath::Abs(MoonPitch) / 20.0f), 0.0f, 1.0f);

		// 밤 보정 로직
		float FinalIntensity = SunMoon.Intensity * FMath::Lerp(1.0f, 0.8f, HorizonAlpha);
		FLinearColor SafeNightColor = FLinearColor(0.1f, 0.15f, 0.25f, 1.0f);
		FLinearColor FinalColor = FMath::Lerp(SunMoon.Color, SafeNightColor, HorizonAlpha * 0.3f);
		float FinalVolumetric = 1.0f * FMath::Lerp(1.0f, 2.5f, HorizonAlpha);

		float FinalIndirectIntensity = SunMoon.IndirectLightingIntensity * FMath::Lerp(1.0f, 3.0f, NightAlpha);

		MoonLightComponent->SetIntensity(FinalIntensity);
		MoonLightComponent->SetLightColor(FinalColor);
		MoonLightComponent->SetVolumetricScatteringIntensity(FinalVolumetric);
		MoonLightComponent->SetIndirectLightingIntensity(FinalIndirectIntensity);

		MoonLightComponent->SetLightSourceAngle(SunMoon.SourceAngle);
		MoonLightComponent->SetLightSourceSoftAngle(SunMoon.SourceSoftAngle);
		MoonLightComponent->SetVisibility(SunMoon.bVisible);
	}

	if (IsValid(SkyLightComponent))
	{
		float FinalSkyLightIntensity = Sky.Sky_Light_Intensity * FMath::Lerp(1.0f, 2.5f, NightAlpha);

		SkyLightComponent->SetIntensity(FinalSkyLightIntensity);
		SkyLightComponent->SetLightColor(Sky.Sky_Light_Color);
		SkyLightComponent->SetIndirectLightingIntensity(Sky.Sky_Indirect_Lighting_Intensity);
		SkyLightComponent->SetVolumetricScatteringIntensity(Sky.Sky_Volumetric_Scattering_Intensity);
	}

	if (IsValid(FogComponent))
	{
		FogComponent->SetFogDensity(Fog.Fog_Density);
		FogComponent->SetFogHeightFalloff(Fog.Fog_Height_Falloff);
		FogComponent->SetFogInscatteringColor(Fog.Fog_Inscattering_Color);
		FogComponent->SetDirectionalInscatteringColor(Fog.Fog_Directional_Inscattering);
	}

	if (IsValid(SkyAtmosphereComponent))
	{
		SkyAtmosphereComponent->SetMieScatteringScale(Atmos.Mie_Scattering_Scale);
		SkyAtmosphereComponent->SetMieScattering(Atmos.Mie_Scattering_Color);
		SkyAtmosphereComponent->SetOtherAbsorption(Atmos.Absorption_Color);
		SkyAtmosphereComponent->SetRayleighScatteringScale(Atmos.Rayleigh_Scattering_Scale);
		SkyAtmosphereComponent->SetAerialPespectiveViewDistanceScale(Atmos.Aerial_Perspective_Distance_Scale);
		SkyAtmosphereComponent->SetSkyLuminanceFactor(Atmos.Sky_Luminance_Factor);
	}

	OnUpdateCustomMaterials(CurrentTime);
}

#if WITH_EDITOR
void ATODManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, LoadPreset))
	{
		LoadSelectedPreset();
	}

	// 추가:PreviewTime 변경시 화면 갱신
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, StartTime) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, TOD_DataArray))
	{
		int32 Hours = FMath::FloorToInt(StartTime);
		int32 Minutes = FMath::FloorToInt((StartTime - Hours) * 60.0f);

		StartTimeDisplay = FString::Printf(TEXT("[ %02d : %02d ]"), Hours, Minutes);

		UpdateTOD(StartTime);
	}

	if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
	{
		BakeTODCurves();
	}
}

void ATODManager::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
	{
		BakeTODCurves();
	}
}
#endif