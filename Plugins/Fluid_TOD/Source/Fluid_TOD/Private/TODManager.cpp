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

// ======= System =========

// 게임 시작
void ATODManager::BeginPlay()
{
	Super::BeginPlay();

	SortTODDataArray();
	BakeTODCurves();

	UpdateTOD(StartTime);

	GetWorldTimerManager().SetTimer(DebugTimerHandle, this, &ATODManager::PrintTODDebugInfo, DebugPrintInterval, true);
}

// 디버그 출력
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
	float CurrentExpMax = 0.0f;
	float CurrentTemp = 6500.0f;
	FVector4 CurrentSaturation = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

	if (IsValid(RuntimePPVComponent))
	{
		CurrentBloom = RuntimePPVComponent->Settings.BloomIntensity;
		CurrentExpMin = RuntimePPVComponent->Settings.AutoExposureMinBrightness;
		CurrentExpMax = RuntimePPVComponent->Settings.AutoExposureMaxBrightness;
		CurrentTemp = RuntimePPVComponent->Settings.WhiteTemp;
		CurrentSaturation = RuntimePPVComponent->Settings.ColorSaturation;
	}

	FString DebugMsg = FString::Printf(TEXT(
		"============ TOD System Debug =============\n"
		"Time  %.2f\n"
		"-------------------------------------------\n"
		"[Sun/Moon] Intensity %.2f | Angle %.1f\n"
		"[SkyLight] %.2f\n"
		"[SkyIndirect] %.2f\n"
		"[Fog] Density %.5f\n"
		"[Atmos] Mie Scattering Scale %.5f\n"
		"-------------------------------------------\n"
		"[PPV] Bloom: %.2f\n"
		"[PPV] Min EV100: % .2f | Max EV100: % .2f\n"
		"[PPV] White Temp: %.0fK\n"
		"[PPV] Saturation: (R:%.2f, G:%.2f, B:%.2f)"
	),
		CurrentSystemTime,
		SunMoon.Intensity, SunMoon.SourceAngle,
		Sky.Sky_Light_Intensity, 
		Sky.Sky_Indirect_Lighting_Intensity,
		Fog.Fog_Density,
		Atmos.Mie_Scattering_Scale,
		CurrentBloom, 
		CurrentExpMin, CurrentExpMax,
		CurrentTemp,
		CurrentSaturation.X, CurrentSaturation.Y, CurrentSaturation.Z
	);

	// 화면 출력
	GEngine->AddOnScreenDebugMessage(1357, DebugPrintInterval + 0.1f, FColor::Yellow, DebugMsg);

}

// 정렬
void ATODManager::SortTODDataArray()
{
	if (TOD_DataArray.Num() < 2) return;
	TOD_DataArray.Sort([](const FTODMasterData& A, const FTODMasterData& B) { return A.Time < B.Time; });
}

// ======= Moon/Sun 분리 =========

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

// ======= PPV =========

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

// ======= Presets =========

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

// ======= TOD System Main =========

void ATODManager::BakeTODCurves()
{
	FindComponents();

	if (TOD_DataArray.Num() == 0) return;

	// 로컬 복사본 정렬
	TArray<FTODMasterData> SortedCopy = TOD_DataArray;
	SortedCopy.Sort([](const FTODMasterData& A, const FTODMasterData& B) {
		return A.Time < B.Time;
		});

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

	for (const FTODMasterData& Data : SortedCopy)
	{
		float T = Data.Time;

		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunIntensityCurve, T, Data.SunMoon_Settings.Intensity, SunIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunSourceAngleCurve, T, Data.SunMoon_Settings.SourceAngle, SunSourceAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunSourceSoftAngleCurve, T, Data.SunMoon_Settings.SourceSoftAngle, SunSourceSoftAngleInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SunIndirectIntensityCurve, T, Data.SunMoon_Settings.IndirectLightingIntensity, SunIndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(SunColorCurve, T, Data.SunMoon_Settings.Color, SunColorInterpMode);

		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SkyLightIntensityCurve, T, Data.SkyLight_Settings.Sky_Light_Intensity, SkyLightIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SkyLightIndirectIntensityCurve, T, Data.SkyLight_Settings.Sky_Indirect_Lighting_Intensity, SkyLightIndirectIntensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(SkyLightVolumetricScatteringIntensityCurve, T, Data.SkyLight_Settings.Sky_Volumetric_Scattering_Intensity, SkyLightVolumetricScatteringInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(SkyColorCurve, T, Data.SkyLight_Settings.Sky_Light_Color, SkyColorInterpMode);

		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(FogDensityCurve, T, Data.Fog_Settings.Fog_Density, FogDensityInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(FogHeightFalloffCurve, T, Data.Fog_Settings.Fog_Height_Falloff, FogHeightFalloffInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(FogInscatteringColorCurve, T, Data.Fog_Settings.Fog_Inscattering_Color, FogInscatteringColorInterpMode);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(FogDirectionalColorCurve, T, Data.Fog_Settings.Fog_Directional_Inscattering, FogDirectionalColorInterpMode);

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
	if (!IsValid(this) || IsActorBeingDestroyed() || TOD_DataArray.Num() == 0) return;

	CurrentSystemTime = CurrentTime;

	// 현재 State 업데이트
	UpdateState(CurrentTime);

	if (!SkyLightComponent) FindComponents();

	// 런타임 PPV 보간 적용
	ApplyPPVBlending(CurrentTime);

	FTODSunMoonSettings SunMoon;
	FTODSkyLightSettings Sky;
	FTODFogSettings Fog;
	FTODSkyAtmosphereSettings Atmos;
	GetTODSettingsAtTime(CurrentTime, SunMoon, Sky, Fog, Atmos);

	// NightAlpha 0.0 = 낮, 1.0 =  밤
	float NightAlpha = 0.0f;
	float SafeTime = FMath::Fmod(CurrentTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	// 새벽 전환 (밤 -> 낮): NightAlpha 1.0 -> 0.0
	if (SafeTime >= DayStartTime - TransitionDuration && SafeTime < DayStartTime) {
		NightAlpha = 1.0f - ((SafeTime - (DayStartTime - TransitionDuration)) / TransitionDuration);
	}
	// 노을 전환 (낮 -> 밤): NightAlpha 0.0 -> 1.0
	else if (SafeTime >= NightStartTime - TransitionDuration && SafeTime < NightStartTime) {
		NightAlpha = (SafeTime - (NightStartTime - TransitionDuration)) / TransitionDuration;
	}
	// 밤
	else if (SafeTime >= NightStartTime || SafeTime < DayStartTime - TransitionDuration) {
		NightAlpha = 1.0f;
	}
	// 낮
	else {
		NightAlpha = 0.0f;
	}
	NightAlpha = FMath::Clamp(NightAlpha, 0.0f, 1.0f);


	// State 별 분기 처리
	switch (CurrentState)
	{
	case ETODState::Day:
		// 낮) 태양 O, 달 X
		if (IsValid(SunLightComponent))
		{
			SunLightComponent->SetIntensity(SunMoon.Intensity);
			SunLightComponent->SetLightColor(SunMoon.Color);
			SunLightComponent->SetLightSourceAngle(SunMoon.SourceAngle);
			SunLightComponent->SetLightSourceSoftAngle(SunMoon.SourceSoftAngle);
			SunLightComponent->SetIndirectLightingIntensity(SunMoon.IndirectLightingIntensity);
			SunLightComponent->SetVisibility(SunMoon.bVisible);
		}
		if (IsValid(MoonLightComponent)) MoonLightComponent->SetVisibility(false);
		break;

	case ETODState::Night:
		// 밤) 태양 X, 달 O
		if (IsValid(SunLightComponent)) SunLightComponent->SetVisibility(false);
		if (IsValid(MoonLightComponent))
		{
			float MoonPitch = MoonLightComponent->GetComponentRotation().Pitch;
			float HorizonDimming = FMath::Clamp(FMath::Abs(MoonPitch) / 10.0f, 0.5f, 1.0f);

			float FinalIntensity = SunMoon.Intensity * 0.5f * HorizonDimming;

			if (MoonLightComponent->bAtmosphereSunLight) MoonLightComponent->bAtmosphereSunLight = false;

			MoonLightComponent->SetIntensity(FinalIntensity);
			MoonLightComponent->SetLightColor(SunMoon.Color);
			MoonLightComponent->SetLightSourceAngle(SunMoon.SourceAngle);
			MoonLightComponent->SetLightSourceSoftAngle(SunMoon.SourceSoftAngle);
			MoonLightComponent->SetIndirectLightingIntensity(SunMoon.IndirectLightingIntensity);
			MoonLightComponent->SetVisibility(SunMoon.bVisible);
		}
		break;
	case ETODState::Transition:
		if (IsValid(SunLightComponent))
		{
			float SunFade = 1.0f - NightAlpha;
			SunLightComponent->SetIntensity(SunMoon.Intensity * SunFade);
			SunLightComponent->SetLightColor(SunMoon.Color);
			SunLightComponent->SetLightSourceAngle(SunMoon.SourceAngle);
			SunLightComponent->SetLightSourceSoftAngle(SunMoon.SourceSoftAngle);
			SunLightComponent->SetIndirectLightingIntensity(SunMoon.IndirectLightingIntensity);
			SunLightComponent->SetVisibility(SunMoon.bVisible);
		}
		
		if (IsValid(MoonLightComponent))
		{
			if (MoonLightComponent->bAtmosphereSunLight) MoonLightComponent->bAtmosphereSunLight = false;

			float MoonFade = NightAlpha;
			float BaseMoonIntensity = SunMoon.Intensity * 0.5f;

			float MoonPitch = MoonLightComponent->GetComponentRotation().Pitch;
			float HorizonDimming = FMath::Clamp(FMath::Abs(MoonPitch) / 10.0f, 0.5f, 1.0f);

			MoonLightComponent->SetIntensity(BaseMoonIntensity * MoonFade * HorizonDimming);
			MoonLightComponent->SetLightColor(SunMoon.Color);
			MoonLightComponent->SetLightSourceAngle(SunMoon.SourceAngle);
			MoonLightComponent->SetLightSourceSoftAngle(SunMoon.SourceSoftAngle);
			MoonLightComponent->SetIndirectLightingIntensity(SunMoon.IndirectLightingIntensity);
			MoonLightComponent->SetVisibility(SunMoon.bVisible);
		}
		break;
	}

	// 공통 환경
	if (IsValid(SkyLightComponent))
	{
		SkyLightComponent->SetIntensity(Sky.Sky_Light_Intensity);
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

// ======= Day/Night State =========

void ATODManager::UpdateState(float CurrentTime)
{
	float SafeTime = FMath::Fmod(CurrentTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	// 낮 전환
	if (SafeTime >= DayStartTime - TransitionDuration && SafeTime < DayStartTime)
	{
		CurrentState = ETODState::Transition;
	}
	// 밤 전환
	else if (SafeTime >= NightStartTime - TransitionDuration && SafeTime < NightStartTime)
	{
		CurrentState = ETODState::Transition;
	}
	// 낮
	else if (SafeTime >= DayStartTime && SafeTime < NightStartTime - TransitionDuration)
	{
		CurrentState = ETODState::Day;
	}
	// 밤
	else
	{
		CurrentState = ETODState::Night;
	}
}

// ======= Editor 기능 관련 =========

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
		SortTODDataArray();
		BakeTODCurves();
		UpdateTOD(StartTime);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, StartTime))
	{
		if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
		{
			SortTODDataArray();
		}

		int32 Hours = FMath::FloorToInt(StartTime);
		int32 Minutes = FMath::FloorToInt((StartTime - Hours) * 60.0f);

		StartTimeDisplay = FString::Printf(TEXT("[ %02d : %02d ]"), Hours, Minutes);

		UpdateTOD(StartTime);
	}

	if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
	{
		BakeTODCurves();
		UpdateTOD(StartTime);
	}
}

void ATODManager::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.PropertyChain.GetActiveMemberNode())
	{
		const FName ActiveMemberName = PropertyChangedEvent.PropertyChain.GetActiveMemberNode()->GetValue()->GetFName();

		if (ActiveMemberName == GET_MEMBER_NAME_CHECKED(ATODManager, TOD_DataArray))
		{
			// 배열 내부 값이 변경될 때
			UpdateTOD(StartTime);
		}
	}

	if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
	{
		BakeTODCurves();
	}
}

void ATODManager::PostInitProperties()
{
	Super::PostInitProperties();

	// 엔진 시작 시 등록
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		PropertyChangeDelegateHandle = FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &ATODManager::OnExternalPropertyChanged);
	}
}

void ATODManager::BeginDestroy()
{
	// 해제
	if (PropertyChangeDelegateHandle.IsValid())
	{
		FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(PropertyChangeDelegateHandle);
	}
	Super::BeginDestroy();
}

void ATODManager::OnExternalPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object && Object->IsA<APostProcessVolume>())
	{
		for (const FTODMasterData& Data : TOD_DataArray)
		{
			if (Data.PPV == Object)
			{
				UpdateTOD(StartTime);
				break;
			}
		}
	}
}

#endif