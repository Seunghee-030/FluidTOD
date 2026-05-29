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

	// Sky Dome Mesh Component
	SkyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkyMeshComponent"));
	SkyMeshComponent->SetupAttachment(RootComponent);

	// Sky Dome Mesh 기본 설정
	SkyMeshComponent->SetCastShadow(false);
	SkyMeshComponent->bReceivesDecals = false;
	SkyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

	float ActualMoonEmissive = 0.f;
	float ActualSkyEmissive = 0.f;

	if (IsValid(MoonMaterialInstance))
	{
		MoonMaterialInstance->GetScalarParameterValue(
			FMaterialParameterInfo(TEXT("MoonSourceEmissiveIntensity")),
			ActualMoonEmissive
		);
	}

	if (IsValid(SkyMaterialInstance))
	{
		SkyMaterialInstance->GetScalarParameterValue(
			FMaterialParameterInfo(TEXT("SkyTextureEmissiveIntensity")),
			ActualSkyEmissive
		);
	}
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
		Moon.Moon_Source_Scale, ActualMoonEmissive,
		Sky.Sky_Light_Intensity, ActualSkyEmissive,
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


// ======== Curve Evaluation =========
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

// ======= Presets: Editor =========
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

// ========= System ===========
void ATODManager::UpdateTOD(float CurrentTime)
{
	TODSystem.UpdateTOD(this, CurrentTime);
}

void ATODManager::FindComponents()
{
	TODSystem.FindComponents(this);
}

void ATODManager::UpdateSunTimes()
{
	TODSystem.UpdateSunTimes(this);
}

FRotator ATODManager::CalculatePivotRotation(float InTime) const
{
	return TODSystem.CalculatePivotRotation(this, InTime);
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