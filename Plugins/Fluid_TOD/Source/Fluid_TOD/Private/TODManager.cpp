#include "TODManager.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/PostProcessComponent.h"
#include "Engine/Engine.h"
#include "Engine/PostProcessVolume.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "EngineUtils.h"

#include "TODCurveEvaluator.h"
#include "Materials/MaterialInstanceDynamic.h"


ATODManager::ATODManager()
{
	PrimaryActorTick.bCanEverTick = false;

	RuntimePPVComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("RuntimePPVComponent"));

	if (RootComponent) RuntimePPVComponent->SetupAttachment(RootComponent);
	else RootComponent = RuntimePPVComponent;

	RuntimePPVComponent->bUnbound = true;
	RuntimePPVComponent->Priority = 100;
}

// ======= System =========

// 게임 시작
void ATODManager::BeginPlay()
{
	Super::BeginPlay();

	for (FTODCinematicSetting& Setting : TargetCinematics)
	{
		if (IsValid(Setting.SequenceActor))
		{
			if (ULevelSequencePlayer* SeqPlayer = Setting.SequenceActor->GetSequencePlayer())
			{
				// 모든 컷신 재생/정지/일시정지 될 때마다 상태 평가 함수 호출
				SeqPlayer->OnPlay.AddDynamic(this, &ATODManager::EvaluateCinematicState);
				SeqPlayer->OnStop.AddDynamic(this, &ATODManager::EvaluateCinematicState);
				SeqPlayer->OnPause.AddDynamic(this, &ATODManager::EvaluateCinematicState);
			}
		}
	}

	FindComponents();
	UpdateSunTimes();
	SortTODDataArray();
	BakeTODCurves();
	UpdateTOD(StartTime);

	if (bEnableDebugPrint) GetWorldTimerManager().SetTimer(DebugTimerHandle, this, &ATODManager::PrintTODDebugInfo, DebugPrintInterval, true);
}

void ATODManager::SetMaterialScalarByName(
	FName ParameterName,
	float Value,
	bool bSkyDome)
{
	UMaterialInstanceDynamic* MID =
		bSkyDome
		? SkyMaterialInstance
		: MoonMaterialInstance;

	if (!IsValid(MID))
	{
		return;
	}

	MID->SetScalarParameterValue(ParameterName, Value);
}

void ATODManager::SetMaterialVectorByName(
	FName ParameterName,
	FLinearColor Value,
	bool bSkyDome)
{
	UMaterialInstanceDynamic* MID =
		bSkyDome
		? SkyMaterialInstance
		: MoonMaterialInstance;

	if (!IsValid(MID))
	{
		return;
	}

	MID->SetVectorParameterValue(ParameterName, Value);
}

// 컷신 재생 상태에 따라 시간 흐름과 시각 요소 갱신 여부 결정
void ATODManager::EvaluateCinematicState()
{
	bIsTimePaused = false;
	bIsVisualOverridden = false;

	// 재생 중인 컷신 확인
	for (const FTODCinematicSetting& Setting : TargetCinematics)
	{
		if (!IsValid(Setting.SequenceActor))
		{
			continue;
		}

		// 시퀀스 에셋이 비어있거나 아직 플레이어가 생성되지 않은 경우 nullptr일 수 있음
		ULevelSequencePlayer* SeqPlayer = Setting.SequenceActor->GetSequencePlayer();
		if (!IsValid(SeqPlayer) || !SeqPlayer->IsPlaying())
		{
			continue;
		}

		if (Setting.bPauseTime) bIsTimePaused = true;
		if (Setting.bOverrideVisuals) bIsVisualOverridden = true;
	}
}

float ATODManager::CalculateCycleSpeed(float InTime)
{
#if WITH_EDITOR
	if (FRichCurve* RichCurve = CycleSpeedCurve.GetRichCurve())
	{
		if (RichCurve->GetNumKeys() == 0)
		{
			RichCurve->Reset();
			RichCurve->AddKey(0.0f, 1.0f);
			RichCurve->AddKey(24.0f, 1.0f);
			RichCurve->PreInfinityExtrap = RCCE_Cycle;
			RichCurve->PostInfinityExtrap = RCCE_Cycle;
		}
	}
#endif

	if (bIsTimePaused)
	{
		return 0.0f;
	}

	float SafeTime = FMath::Fmod(InTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	if (IsValid(PlayerRef) && PlayerRef->GetVelocity().SizeSquared() > 0.0)
	{
		TargetSpeed = ActiveDaySpeed;
	}
	else
	{
		TargetSpeed = IdleDaySpeed;
	}

	float DeltaTime = GetWorld() ? GetWorld()->GetDeltaSeconds() : 0.0f;
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpSpeed);

	float BaseMultiplier = (DayCycleDuration > 0.0f) ? (24.0f / (DayCycleDuration * 60.0f)) : 0.0f;

	float CurveValue = 1.0f;
	if (const FRichCurve* EvalCurve = CycleSpeedCurve.GetRichCurveConst())
	{
		CurveValue = EvalCurve->Eval(SafeTime);
	}
#if !WITH_EDITOR
	else if (!CycleSpeedCurve.ExternalCurve)
	{
		static bool bWarnedMissingCycleSpeedCurve = false;
		if (!bWarnedMissingCycleSpeedCurve)
		{
			bWarnedMissingCycleSpeedCurve = true;
			UE_LOG(LogTemp, Warning, TEXT("[TODManager] CycleSpeedCurve에 ExternalCurve(UCurveFloat 에셋)가 할당되어 있지 않아 패키징 빌드에서는 커브 형태가 적용되지 않고 기본값(1.0)으로 동작합니다. 빌드에 반영하려면 외부 UCurveFloat 에셋을 만들어 CycleSpeedCurve에 연결해 주세요."));
		}
	}
#endif

	return CurrentSpeed * BaseMultiplier * CurveValue;
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
	float ActualMoonScale =
		bOverrideMoonSourceScale
		? OverriddenMoonSourceScale
		: Moon.Moon_Source_Scale;

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
		"	Time   %s\n"
		"--------------------------------------------------\n"
		"[Sun] Intensity %.2f | Angle %.1f\n"
		"\n"
		"[Moon] Intensity %.2f | Angle %.1f \n"
		"[MoonSource] Scale %.1f | Emissive Intensity %.1f\n"
		"\n"
		"[SkyLight] Intensity %.2f | Emissive Intensity %.1f\n"
		"[SkyIndirectLighting] Intensity %.2f\n"
		"\n"
		"[Fog] Density %.5f\n"
		"[Atmos] Mie Scattering Scale %.5f\n"
		"--------------------------------------------------\n"
		"[PPV] Bloom: %.2f\n"
		"[PPV] Min EV100: % .2f | Max EV100: % .2f\n"
		"[PPV] White Temp: %.0fK\n"
		"[PPV] Saturation: (R:%.2f, G:%.2f, B:%.2f)\n"
		"--------------------------------------------------"
	),
		*GetFormattedTimeAsString(CurrentSystemTime),
		Sun.Intensity, Sun.Source_Angle,
		Moon.Intensity, Moon.Source_Angle, 
		ActualMoonScale, ActualMoonEmissive,
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

	const FName PropertyName = PropertyChangedEvent.Property
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	const bool bIsInteractive =
		!!(PropertyChangedEvent.ChangeType & EPropertyChangeType::Interactive);

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, LoadPreset))
	{
		LoadSelectedPreset();
		SortTODDataArray();
		BakeTODCurves();
	}

	else if (
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Latitude) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Longitude))
	{
		UpdateSunTimes();
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, StartTime))
	{
		StartTimeDisplay = GetFormattedTimeAsString(StartTime);
		if (!bIsInteractive)
		{
			SortTODDataArray();
		}
	}
	else
	{
		BakeTODCurves();
	}

	UpdateTOD(StartTime);
	ForceViewportRedraw();
}

void ATODManager::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.PropertyChain.GetActiveMemberNode())
	{
		const FName ActiveMemberName =
			PropertyChangedEvent.PropertyChain
			.GetActiveMemberNode()
			->GetValue()
			->GetFName();

		if (ActiveMemberName == GET_MEMBER_NAME_CHECKED(ATODManager, TOD_DataArray))
		{
			const EPropertyChangeType::Type ChangeType =
				PropertyChangedEvent.ChangeType;

			const bool bArrayChanged =
				(ChangeType & EPropertyChangeType::ArrayAdd) ||
				(ChangeType & EPropertyChangeType::ArrayRemove) ||
				(ChangeType & EPropertyChangeType::ArrayClear) ||
				(ChangeType & EPropertyChangeType::Duplicate);

			if (bArrayChanged)
			{
				SortTODDataArray();
			}

			BakeTODCurves();
			UpdateTOD(StartTime);
			ForceViewportRedraw();
		}
	}

	OnTODDataChanged.Broadcast();
}

void ATODManager::PostInitProperties()
{
	Super::PostInitProperties();

	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		PropertyChangeDelegateHandle =
			FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(
				this,
				&ATODManager::OnExternalPropertyChanged
			);
	}
}

void ATODManager::BeginDestroy()
{
	if (PropertyChangeDelegateHandle.IsValid())
	{
		FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(
			PropertyChangeDelegateHandle
		);
	}

	Super::BeginDestroy();
}

void ATODManager::OnExternalPropertyChanged(
	UObject* Object,
	FPropertyChangedEvent& PropertyChangedEvent)
{
	if (!Object || !Object->IsA<APostProcessVolume>())
	{
		return;
	}

	bool bIsRelevant = false;
	for (const FTODMasterData& Data : TOD_DataArray)
	{
		if (Data.PPV == Object)
		{
			bIsRelevant = true;
			break;
		}
	}

	if (!bIsRelevant)
	{
		return;
	}

	if (bPendingPPVUpdate)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	bPendingPPVUpdate = true;
	World->GetTimerManager().SetTimerForNextTick([this]()
	{
		bPendingPPVUpdate = false;
		UpdateTOD(StartTime);
		ForceViewportRedraw();
	});
}

void ATODManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (GetWorld() &&
		GetWorld()->WorldType == EWorldType::Editor)
	{
		SetActorLocation(FVector::ZeroVector);
		SetActorRotation(FRotator::ZeroRotator);
		SetActorScale3D(FVector::OneVector);
	}

	PostEditMove(true);
}

void ATODManager::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);

	UpdateTOD(StartTime);
	ForceViewportRedraw();
}

#endif