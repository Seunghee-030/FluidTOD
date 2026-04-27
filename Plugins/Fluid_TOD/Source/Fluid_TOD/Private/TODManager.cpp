#include "TODManager.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/PostProcessComponent.h"

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

	UMyBlueprintFunctionLibrary::SortTODDataArray(TOD_DataArray);

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
	if (TOD_DataArray.Num() == 0) return;

	if (!SkyLightComponent) FindComponents();

	int32 PrevIndex, NextIndex;
	float Alpha;
	UMyBlueprintFunctionLibrary::GetTODInterpolationData(TOD_DataArray, CurrentTime, PrevIndex, NextIndex, Alpha);

	// 런타임 PPV 사용
	UMyBlueprintFunctionLibrary::ApplyPPVBlending(TOD_DataArray, CurrentTime, RuntimePPVComponent);

	FTODSunMoonSettings SunMoon;
	FTODSkyLightSettings Sky;
	FTODFogSettings Fog;
	FTODSkyAtmosphereSettings Atmos;
	GetTODSettingsAtTime(CurrentTime, SunMoon, Sky, Fog, Atmos);

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

	if (IsValid(MoonLightComponent))
	{
		MoonLightComponent->SetIntensity(SunMoon.Intensity);
		MoonLightComponent->SetLightColor(SunMoon.Color);
		MoonLightComponent->SetLightSourceAngle(SunMoon.SourceAngle);
		MoonLightComponent->SetLightSourceSoftAngle(SunMoon.SourceSoftAngle);
		MoonLightComponent->SetIndirectLightingIntensity(SunMoon.IndirectLightingIntensity);
		MoonLightComponent->SetVisibility(SunMoon.bVisible);
	}

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