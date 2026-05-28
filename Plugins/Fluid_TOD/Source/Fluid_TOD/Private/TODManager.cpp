#include "TODManager.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/PostProcessComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "TODCurveEvaluator.h"


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

	UpdateSunTimes();

	SortTODDataArray();
	BakeTODCurves();

	UpdateTOD(StartTime);

	GetWorldTimerManager().SetTimer(DebugTimerHandle, this, &ATODManager::PrintTODDebugInfo, DebugPrintInterval, true);
}

// 디버그 출력
void ATODManager::PrintTODDebugInfo()
{
	if (!bEnableDebugPrint || !GEngine) return;

	FTODSunMoonSettings Sun;
	FTODMoonSettings Moon;
	FTODSkyLightSettings Sky;
	FTODFogSettings Fog;
	FTODSkyAtmosphereSettings Atmos;
	GetTODSettingsAtTime(CurrentSystemTime, Sun, Moon, Sky, Fog, Atmos);

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
		"=========== TOD System Debug ===========\n"
		"Time   %s\n"
		"--------------------------------------------------\n"
		"[Sun] Intensity %.2f | Angle %.1f\n"
		"[Moon] Intensity %.2f | Angle %.1f \n"
		"[MoonSource] Source Scale %.1f | Emissive Intensity %.1f\n"
		"[SkyLight] %.2f | Emissive Intensity %.1f\n"
		"[SkyIndirect] %.2f\n"
		"[Fog] Density %.5f\n"
		"[Atmos] Mie Scattering Scale %.5f\n"
		"--------------------------------------------------\n"
		"[PPV] Bloom: %.2f\n"
		"[PPV] Min EV100: % .2f | Max EV100: % .2f\n"
		"[PPV] White Temp: %.0fK\n"
		"[PPV] Saturation: (R:%.2f, G:%.2f, B:%.2f)"
	),
		*GetFormattedTimeAsString(CurrentSystemTime),
		Sun.Intensity, Sun.Source_Angle,
		Moon.Intensity, Moon.Source_Angle, 
		Moon.Moon_Source_Scale, Moon.Moon_Source_Emissive_Intensity,
		Sky.Sky_Light_Intensity, Sky.Sky_Texture_Emissive_Intensity,
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

FString ATODManager::GetFormattedTimeAsString(float InTime) const
{
	// 시간 0~24 보정
	float SafeTime = FMath::Fmod(InTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	int32 Hours = FMath::FloorToInt(SafeTime);
	int32 Minutes = FMath::FloorToInt((SafeTime - Hours) * 60.0f);

	return FString::Printf(TEXT("[ %02d : %02d ]"), Hours, Minutes);
}

// 정렬
void ATODManager::SortTODDataArray()
{
	if (TOD_DataArray.Num() < 2) return;
	TOD_DataArray.StableSort([](const FTODMasterData& A, const FTODMasterData& B) { return A.Time < B.Time; });
}

void ATODManager::BakeTODCurves()
{
	CurveEvaluator.BakeTODCurves(this);
}

void ATODManager::ApplyPPVBlending(float CurrentTime)
{
	CurveEvaluator.ApplyPPVBlending(this, CurrentTime);
}

void ATODManager::GetTODSettingsAtTime(
	float InTime,
	FTODSunMoonSettings& OutSun,
	FTODMoonSettings& OutMoon,
	FTODSkyLightSettings& OutSkyLight,
	FTODFogSettings& OutFog,
	FTODSkyAtmosphereSettings& OutSkyAtmosphere)
{
	CurveEvaluator.GetTODSettingsAtTime(
		this,
		InTime,
		OutSun,
		OutMoon,
		OutSkyLight,
		OutFog,
		OutSkyAtmosphere
	);
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
		// 해시 비교
		if (Light->ComponentHasTag(FName(TEXT("Moon"))))
		{
			MoonLightComponent = Light;
		}
		else if (Light->ComponentHasTag(FName(TEXT("Sun"))))
		{
			SunLightComponent = Light;
		}
	}

	SkyLightComponent = FindComponentByClass<USkyLightComponent>();
	FogComponent = FindComponentByClass<UExponentialHeightFogComponent>();
	SkyAtmosphereComponent = FindComponentByClass<USkyAtmosphereComponent>();
}

// ======= Presets =========
void ATODManager::SaveNewPreset()
{
	EditorModule.SaveNewPreset(this);
}

void ATODManager::SaveCurrentPreset()
{
	EditorModule.SaveCurrentPreset(this);
}

void ATODManager::OpenPresetDialog()
{
	EditorModule.OpenPresetDialog(this);
}

void ATODManager::LoadSelectedPreset()
{
	EditorModule.LoadSelectedPreset(this);
}

void ATODManager::ForceViewportRedraw()
{
	EditorModule.ForceViewportRedraw(this);
}


// ======= TOD Geography =========

void ATODManager::UpdateSunTimes()
{
	float LatitudeOffset = (Latitude / 90.0f) * 2.0f;

	CalculatedSunriseTime = 6.0f - LatitudeOffset;
	CalculatedSunsetTime = 18.0f + LatitudeOffset;

	SunriseTime = GetFormattedTimeAsString(CalculatedSunriseTime);
	SunsetTime = GetFormattedTimeAsString(CalculatedSunsetTime);
}

FRotator ATODManager::CalculatePivotRotation(float InTime) const
{
	// 시간 0~24 보정
	float SafeTime = FMath::Fmod(InTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	float PitchAngle = 0.0f;

	bool bIsDaytime = (SafeTime >= CalculatedSunriseTime) && (SafeTime < CalculatedSunsetTime);

	if (bIsDaytime)
	{
		// 낮
		PitchAngle = FMath::GetMappedRangeValueClamped(
			FVector2D(CalculatedSunriseTime, CalculatedSunsetTime),
			FVector2D(180.0f, 360.0f),
			SafeTime
		);
	}
	else
	{
		// 밤
		float TotalNightDuration = 24.0f - (CalculatedSunsetTime - CalculatedSunriseTime);
		float ElapsedNightTime = 0.0f;

		if (SafeTime >= CalculatedSunsetTime)
		{
			ElapsedNightTime = SafeTime - CalculatedSunsetTime;
		}
		else
		{
			ElapsedNightTime = (24.0f - CalculatedSunsetTime) + SafeTime;
		}

		PitchAngle = FMath::GetMappedRangeValueClamped(
			FVector2D(0.0f, TotalNightDuration),
			FVector2D(0.0f, 180.0f),
			ElapsedNightTime
		);
	}

	return FRotator(0.0f, PitchAngle, 0.0f);
}

void ATODManager::UpdateTOD(float CurrentTime)
{
	if (!IsValid(this) || IsActorBeingDestroyed() || TOD_DataArray.Num() == 0) return;

	CurrentSystemTime = CurrentTime;

	UpdateState(CurrentTime);

	if (!SkyLightComponent) FindComponents();

	// 런타임 PPV 보간 적용
	ApplyPPVBlending(CurrentTime);

	FTODSunMoonSettings SunSettings;
	FTODMoonSettings MoonSettings;
	FTODSkyLightSettings Sky;
	FTODFogSettings Fog;
	FTODSkyAtmosphereSettings Atmos;
	GetTODSettingsAtTime(CurrentTime, SunSettings, MoonSettings, Sky, Fog, Atmos);

	if (IsValid(SunLightComponent))
	{
		if (!SunLightComponent->bAtmosphereSunLight)
		{
			SunLightComponent->SetAtmosphereSunLight(true);
			SunLightComponent->MarkRenderStateDirty();
		}

		SunLightComponent->SetIntensity(SunSettings.Intensity);
		SunLightComponent->SetLightColor(SunSettings.Light_Color);
		SunLightComponent->SetLightSourceAngle(SunSettings.Source_Angle);
		SunLightComponent->SetLightSourceSoftAngle(SunSettings.Source_Soft_Angle);
		SunLightComponent->SetIndirectLightingIntensity(SunSettings.Indirect_Light_Intensity);
	}

	if (IsValid(MoonLightComponent))
	{
		// 달의 대기 산란 영향 차단 (붉은 달 방지)
		if (MoonLightComponent->bAtmosphereSunLight)
		{
			MoonLightComponent->SetAtmosphereSunLight(false);
			MoonLightComponent->MarkRenderStateDirty();
		}
		MoonLightComponent->SetAtmosphereSunLightIndex(1);
		MoonLightComponent->bPerPixelAtmosphereTransmittance = false;

		MoonLightComponent->SetIntensity(MoonSettings.Intensity);
		MoonLightComponent->SetLightColor(MoonSettings.Light_Color);
		MoonLightComponent->SetLightSourceAngle(MoonSettings.Source_Angle);
		MoonLightComponent->SetLightSourceSoftAngle(MoonSettings.Source_Soft_Angle);
		MoonLightComponent->SetIndirectLightingIntensity(MoonSettings.Indirect_Light_Intensity);
	
		if (IsValid(MoonMaterialInstance))
		{
			//MoonMaterialInstance->SetScalarParameterValue(TEXT("MoonEmissiveColor"), FinalMoonSourceScale);
			MoonMaterialInstance->SetScalarParameterValue(TEXT("MoonSourceEmissiveIntensity"), MoonSettings.Moon_Source_Emissive_Intensity);
		}
	}

	// 공통 환경
	if (IsValid(SkyLightComponent))
	{
		SkyLightComponent->SetIntensity(Sky.Sky_Light_Intensity);
		SkyLightComponent->SetLightColor(Sky.Sky_Light_Color);
		SkyLightComponent->SetIndirectLightingIntensity(Sky.Sky_Indirect_Lighting_Intensity);
		SkyLightComponent->SetVolumetricScatteringIntensity(Sky.Sky_Volumetric_Scattering_Intensity);
		if (IsValid(SkyMaterialInstance))
		{
			SkyMaterialInstance->SetScalarParameterValue(TEXT("SkyTextureEmissiveIntensity"), Sky.Sky_Texture_Emissive_Intensity);
		}
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

	float DawnStart = CalculatedSunriseTime - TransitionDuration;
	float SunriseEnd = CalculatedSunriseTime + TransitionDuration;

	float SunsetStart = CalculatedSunsetTime - TransitionDuration;
	float DuskEnd = CalculatedSunsetTime + TransitionDuration;

	// 일출 전
	if (SafeTime >= DawnStart && SafeTime < CalculatedSunriseTime)
	{
		CurrentState = ETODState::Dawn;
	}
	// 일출
	else if (SafeTime >= CalculatedSunriseTime && SafeTime < SunriseEnd)
	{
		CurrentState = ETODState::Sunrise;
	}
	// 낮
	else if (SafeTime >= SunriseEnd && SafeTime < SunsetStart)
	{
		CurrentState = ETODState::Day;
	}
	// 일몰
	else if (SafeTime >= SunsetStart && SafeTime < CalculatedSunsetTime)
	{
		CurrentState = ETODState::Sunset;
	}
	// 일몰 후
	else if (SafeTime >= CalculatedSunsetTime && SafeTime < DuskEnd)
	{
		CurrentState = ETODState::Dusk;
	}
	// Night
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

	// 위도,경도 관련
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Latitude) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Longitude))
	{
		UpdateSunTimes();
		UpdateTOD(StartTime);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, StartTime))
	{
		if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
		{
			SortTODDataArray();
		}

		StartTimeDisplay = GetFormattedTimeAsString(StartTime);

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

	// TOD 데이터 변경 시 브로드캐스트
	OnTODDataChanged.Broadcast();
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