#include "TODManager.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SceneComponent.h"
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

#if WITH_EDITOR
#include "Editor.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif


ATODManager::ATODManager()
{
	PrimaryActorTick.bCanEverTick = true;

	RuntimePPVComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("RuntimePPVComponent"));

	if (RootComponent) RuntimePPVComponent->SetupAttachment(RootComponent);
	else RootComponent = RuntimePPVComponent;

	RuntimePPVComponent->bUnbound = true;
	RuntimePPVComponent->Priority = 1;

	CurveData = CreateDefaultSubobject<UTODCurveContainer>(TEXT("CurveData"));

	FTODTimePoint DawnPoint; DawnPoint.State = ETODState::Dawn; DawnPoint.StartTime = 2.0f; TOD_State.Add(DawnPoint);
	FTODTimePoint SunrisePoint; SunrisePoint.State = ETODState::Sunrise; SunrisePoint.StartTime = 6.0f; TOD_State.Add(SunrisePoint);
	FTODTimePoint DayPoint; DayPoint.State = ETODState::Day; DayPoint.StartTime = 10.0f; TOD_State.Add(DayPoint);
	FTODTimePoint SunsetPoint; SunsetPoint.State = ETODState::Sunset; SunsetPoint.StartTime = 14.0f; TOD_State.Add(SunsetPoint);
	FTODTimePoint DuskPoint; DuskPoint.State = ETODState::Dusk; DuskPoint.StartTime = 18.0f; TOD_State.Add(DuskPoint);
	FTODTimePoint NightPoint; NightPoint.State = ETODState::Night; NightPoint.StartTime = 20.0f; TOD_State.Add(NightPoint);
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
	ApplyStaticSunMoonOffsets();
	BakeTODCurves();
	UpdatePivotRotation(StartTime);
	UpdateTOD(StartTime);

	if (bEnableDebugPrint) GetWorldTimerManager().SetTimer(DebugTimerHandle, this, &ATODManager::PrintTODDebugInfo, DebugPrintInterval, true);
}

void ATODManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const UWorld* World = GetWorld();
	if (!World || !World->IsGameWorld())
	{
		return;
	}

	if (bIsTimePaused)
	{
		return;
	}

	const float Speed = CalculateCycleSpeed(CurrentSystemTime);

	float NewTime = CurrentSystemTime + Speed * DeltaSeconds;
	NewTime = FMath::Fmod(NewTime, 24.0f);
	if (NewTime < 0.0f)
	{
		NewTime += 24.0f;
	}

	UpdatePivotRotation(NewTime);
	UpdateTOD(NewTime);
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

		ULevelSequencePlayer* SeqPlayer = Setting.SequenceActor->GetSequencePlayer();
		if (!IsValid(SeqPlayer) || !SeqPlayer->IsPlaying())
		{
			continue;
		}

		if (Setting.bPauseTime) bIsTimePaused = true;
		if (Setting.bOverrideVisuals) bIsVisualOverridden = true;
	}
}

float ATODManager::GetStartTime() const
{
	return StartTime;
}

void ATODManager::SetStartTime(float NewTime)
{
	StartTime = WrapStartTime(NewTime);
	CurrentSystemTime = StartTime;

	SortTODDataArray();
	UpdatePivotRotation(StartTime);
	UpdateTOD(StartTime);

#if WITH_EDITOR
	ForceViewportRedraw();
#endif
}

float ATODManager::GetCurrentTime() const
{
	return CurrentSystemTime;
}

void ATODManager::SetCurrentTime(float NewTime)
{
	CurrentSystemTime = NewTime;

	UpdatePivotRotation(CurrentSystemTime);
	UpdateTOD(CurrentSystemTime);

#if WITH_EDITOR
	ForceViewportRedraw();
#endif
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
			UE_LOG(LogTemp, Warning, TEXT("[TODManager] CycleSpeedCurve has no ExternalCurve (UCurveFloat) assigned. Defaulting to 1.0."));
		}
	}
#endif

	return CurrentSpeed * BaseMultiplier * CurveValue;
}

ETODState ATODManager::GetCurrentTODState(float InTime) const
{
	if (TOD_State.IsEmpty())
	{
		return ETODState::Day;
	}

	for (int32 i = TOD_State.Num() - 1; i >= 0; --i)
	{
		if (InTime >= TOD_State[i].StartTime)
		{
			return TOD_State[i].State;
		}
	}

	return TOD_State.Last().State;
}

bool ATODManager::IsTimeInState(float InTime, ETODState TargetState) const
{
	return GetCurrentTODState(InTime) == TargetState;
}

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

	FString StateStr = StaticEnum<ETODState>()->GetNameStringByValue(static_cast<int64>(GetCurrentTODState(CurrentSystemTime)));

	FString DebugMsg = FString::Printf(TEXT(
		"=========== TOD System Debug ===========\n"
		"	Time   %s [%s]\n"
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
		*StateStr,
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

float ATODManager::GetMoonSourceScaleAtTime(float InTime) const
{
	return CurveEvaluator.GetMoonSourceScaleAtTime(this, InTime);
}

float ATODManager::GetMoonIntensity(float InTime) const
{
	return CurveEvaluator.GetMoonIntensity(this, InTime);
}

float ATODManager::GetSunIntensity(float InTime) const
{
	return CurveEvaluator.GetSunIntensity(this, InTime);
}

float ATODManager::GetFinalSpeed(float InTime)
{
	return CalculateCycleSpeed(CurrentSystemTime)*50.0f;
}

// 기존 BP Timeline의 "Calculate Pivot Rotation -> Set Relative Rotation(PivotSunMoon)"을 대체
void ATODManager::UpdatePivotRotation(float InTime)
{
	if (!IsValid(PivotSunMoonComponent))
	{
		return;
	}

	PivotSunMoonComponent->SetRelativeRotation(CalculatePivotRotation(InTime));
}

float ATODManager::WrapStartTime(float InTime)
{
	float Wrapped = FMath::Fmod(InTime, 24.0f);
	if (Wrapped < 0.0f)
	{
		Wrapped += 24.0f;
	}
	return Wrapped;
}

void ATODManager::ApplyStaticSunMoonOffsets()
{
	if (IsValid(MoonLightComponent))
	{
		MoonLightComponent->SetRelativeRotation(MoonLocalRotationOffset);
	}

	if (IsValid(SunLightComponent))
	{
		SunLightComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, SunLatitudeTiltMultiplier * Latitude));
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

void ATODManager::RequestDeferredRebake()
{
	if (bRebakeRequested)
	{
		return;
	}
	bRebakeRequested = true;

	if (GEditor)
	{
		GEditor->GetTimerManager()->SetTimerForNextTick([this]()
			{
				bRebakeRequested = false;

				if (!IsValid(this))
				{
					return;
				}

				BakeTODCurves();
				ApplyStaticSunMoonOffsets();
				UpdatePivotRotation(StartTime);
				UpdateTOD(StartTime);
				ForceViewportRedraw();
			});
	}
	else
	{
		// 에디터가 아닌 예외상황 안전장치
		bRebakeRequested = false;
		BakeTODCurves();
		ApplyStaticSunMoonOffsets();
		UpdatePivotRotation(StartTime);
		UpdateTOD(StartTime);
		ForceViewportRedraw();
	}
}

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
		RequestDeferredRebake();
		return;
	}

	if (
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Latitude) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Longitude))
	{
		UpdateSunTimes();
		ApplyStaticSunMoonOffsets();
		ForceViewportRedraw();
		return;
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, StartTime))
	{
		// Start Time 슬라이더 순환
		StartTime = WrapStartTime(StartTime);
		CurrentSystemTime = StartTime;

		StartTimeDisplay = GetFormattedTimeAsString(StartTime);
		if (!bIsInteractive)
		{
			SortTODDataArray();
		}
		UpdatePivotRotation(StartTime);
		UpdateTOD(StartTime);
		ForceViewportRedraw();
		return;
	}

	if (
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, MoonLocalRotationOffset) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, SunLatitudeTiltMultiplier))
	{
		ApplyStaticSunMoonOffsets();
		ForceViewportRedraw();
		return;
	}

	RequestDeferredRebake();
}

void ATODManager::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);

	if (PropertyAboutToChange &&
		PropertyAboutToChange->GetFName() == GET_MEMBER_NAME_CHECKED(ATODManager, TOD_DataArray))
	{
		PreEditTOD_DataArray = TOD_DataArray;
	}
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
			}
			else if (
				PropertyChangedEvent.Property &&
				PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(FTODMasterData, Time))
			{
				const int32 ChangedIndex = PropertyChangedEvent.GetArrayIndex(
					GET_MEMBER_NAME_CHECKED(ATODManager, TOD_DataArray).ToString());

				if (TOD_DataArray.IsValidIndex(ChangedIndex))
				{
					const float BoundaryTolerance = 0.001f;
					const float NewTime = TOD_DataArray[ChangedIndex].Time;

					const bool bIsZero = FMath::IsNearlyEqual(NewTime, 0.0f, BoundaryTolerance);
					const bool bIsTwentyFour = FMath::IsNearlyEqual(NewTime, 24.0f, BoundaryTolerance);

					if (bIsZero || bIsTwentyFour)
					{
						const float OppositeBoundary = bIsZero ? 24.0f : 0.0f;

						bool bConflict = false;
						for (int32 i = 0; i < TOD_DataArray.Num(); ++i)
						{
							if (i == ChangedIndex) continue;

							if (FMath::IsNearlyEqual(TOD_DataArray[i].Time, OppositeBoundary, BoundaryTolerance))
							{
								bConflict = true;
								break;
							}
						}

						if (bConflict)
						{
							if (PreEditTOD_DataArray.IsValidIndex(ChangedIndex))
							{
								TOD_DataArray[ChangedIndex].Time = PreEditTOD_DataArray[ChangedIndex].Time;
							}
							else
							{
								TOD_DataArray[ChangedIndex].Time = bIsZero ? 0.01f : 23.99f;
							}

							FNotificationInfo Info(FText::FromString(TEXT(
								"0 and 24 represent the same time and cannot coexist. "
								"Input reverted because the opposite boundary already exists.")));
							Info.ExpireDuration = 4.0f;
							FSlateNotificationManager::Get().AddNotification(Info);
						}
					}
				}

			}

			RequestDeferredRebake();
		}
		else if (ActiveMemberName == GET_MEMBER_NAME_CHECKED(ATODManager, TOD_State))
		{
			const int32 MaxStates = 6;

			if (TOD_State.Num() > MaxStates)
			{
				TOD_State.SetNum(MaxStates);
			}

			const int32 ChangedIndex = PropertyChangedEvent.GetArrayIndex(GET_MEMBER_NAME_CHECKED(ATODManager, TOD_State).ToString());
			TSet<ETODState> UsedStates;

			for (int32 i = 0; i < TOD_State.Num(); ++i)
			{
				if (i == ChangedIndex)
				{
					continue;
				}

				if (UsedStates.Contains(TOD_State[i].State))
				{
					ETODState AlternativeState = TOD_State[i].State;
					for (uint8 StateIdx = 0; StateIdx < MaxStates; ++StateIdx)
					{
						ETODState TestState = static_cast<ETODState>(StateIdx);
						if (!UsedStates.Contains(TestState))
						{
							AlternativeState = TestState;
							break;
						}
					}
					TOD_State[i].State = AlternativeState;
				}
				UsedStates.Add(TOD_State[i].State);
			}

			if (TOD_State.IsValidIndex(ChangedIndex))
			{
				if (UsedStates.Contains(TOD_State[ChangedIndex].State))
				{
					ETODState AlternativeState = TOD_State[ChangedIndex].State;
					for (uint8 StateIdx = 0; StateIdx < MaxStates; ++StateIdx)
					{
						ETODState TestState = static_cast<ETODState>(StateIdx);
						if (!UsedStates.Contains(TestState))
						{
							AlternativeState = TestState;
							break;
						}
					}
					TOD_State[ChangedIndex].State = AlternativeState;
				}
			}

			TOD_State.Sort([](const FTODTimePoint& A, const FTODTimePoint& B) {
				return A.StartTime < B.StartTime;
				});

			for (int32 i = 1; i < TOD_State.Num(); ++i)
			{
				if (TOD_State[i].StartTime <= TOD_State[i - 1].StartTime)
				{
					TOD_State[i].StartTime = FMath::Min(TOD_State[i - 1].StartTime + 0.1f, 24.0f);
				}
			}
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

	RequestDeferredRebake();
}

void ATODManager::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);

	RequestDeferredRebake();
}

#endif