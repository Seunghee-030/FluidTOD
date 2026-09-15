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
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "EngineUtils.h"
#include "Engine/StaticMesh.h"

#include "TODCurveEvaluator.h"
#include "Materials/MaterialInstanceDynamic.h"

#if WITH_EDITOR
#include "Editor.h"
#include "LevelEditorViewport.h"
#include "UObject/ObjectSaveContext.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif


ATODManager::ATODManager()
{
	PrimaryActorTick.bCanEverTick = true;
	// 카메라/시퀀서 평가 이후에 앵커를 갱신해야 프레임 지연 없이 정렬된다.
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

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
				SeqPlayer->OnPlay.AddUniqueDynamic(this, &ATODManager::EvaluateCinematicState);
				SeqPlayer->OnStop.AddUniqueDynamic(this, &ATODManager::EvaluateCinematicState);
				SeqPlayer->OnPause.AddUniqueDynamic(this, &ATODManager::EvaluateCinematicState);
			}
		}
	}

	FindComponents();
	UpdateSunTimes();
	SortTODDataArray();

	BakeTODCurves();
	UpdateTOD(StartTime);
	ApplyStaticSunMoonOffsets();
	UpdatePivotRotation(StartTime);

	// 0번째 프레임부터 정렬 상태로 시작
	UpdateSkyAnchorPosition();
	UpdateMoonMeshTransform();

	if (bEnableDebugPrint) GetWorldTimerManager().SetTimer(DebugTimerHandle, this, &ATODManager::PrintTODDebugInfo, DebugPrintInterval, true);
}

void ATODManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (FTODCinematicSetting& Setting : TargetCinematics)
	{
		if (!IsValid(Setting.SequenceActor))
		{
			continue;
		}

		if (ULevelSequencePlayer* SeqPlayer = Setting.SequenceActor->GetSequencePlayer())
		{
			SeqPlayer->OnPlay.RemoveDynamic(this, &ATODManager::EvaluateCinematicState);
			SeqPlayer->OnStop.RemoveDynamic(this, &ATODManager::EvaluateCinematicState);
			SeqPlayer->OnPause.RemoveDynamic(this, &ATODManager::EvaluateCinematicState);
		}
	}

	GetWorldTimerManager().ClearTimer(DebugTimerHandle);

	Super::EndPlay(EndPlayReason);
}

void ATODManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const UWorld* World = GetWorld();
	if (!World) return;

	// 데디케이티드 서버는 화면을 렌더링하지 않으므로 뷰 추종/메쉬 트랜스폼 등
	// 시각 전용 갱신은 아무도 보지 않는 값을 계산하는 순수 낭비다. 전부 건너뛴다.
	const bool bIsDedicatedServer = World->GetNetMode() == NM_DedicatedServer;

	// 앵커는 시간 정지/컷신/에디터 여부와 무관하게 항상 뷰를 따라간다. (서버 제외)
	const bool bAnchorMoved = !bIsDedicatedServer && UpdateSkyAnchorPosition();

	if (!World->IsGameWorld())
	{
		// 에디터 뷰포트: 시간은 진행시키지 않고 앵커 이동분만 메쉬에 반영
		if (bAnchorMoved)
		{
			UpdateMoonMeshTransform();
		}
		return;
	}

	if (bIsTimePaused)
	{
		if (bAnchorMoved)
		{
			UpdateMoonMeshTransform();
		}
		return;
	}

	const float Speed = CalculateCycleSpeed(CurrentSystemTime) * TimeDirection;

	float NewTime = CurrentSystemTime + Speed * DeltaSeconds;
	NewTime = FMath::Fmod(NewTime, 24.0f);
	if (NewTime < 0.0f)
	{
		NewTime += 24.0f;
	}

	if (!bIsDedicatedServer)
	{
		UpdatePivotRotation(NewTime);
	}

	// CurrentSystemTime/상태(GetCurrentTODState 등 게임플레이 조회용)는 항상 갱신된다.
	// 커브 평가·라이트 Set 등 시각 갱신은 UpdateTOD 내부에서 서버일 때 다시 한번 스킵된다.
	UpdateTOD(NewTime);

	if (!bIsDedicatedServer)
	{
		UpdateMoonMeshTransform();
	}
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
	UpdateMoonMeshTransform();

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
	UpdateMoonMeshTransform();

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

	float ActualSkyEmissive = 0.f;
	float ActualMoonEmissive = 0.f;
	float ActualMoonScale =
		bOverrideMoonSourceScale
		? OverriddenMoonSourceScale
		: Moon.Moon_Source_Scale;
	float ActualMoonGlowEmissive = 0.f;
	float ActualMoonGlowScale = Moon.Moon_Glow_Scale;

	if (IsValid(SkyMaterialInstance))
	{
		SkyMaterialInstance->GetScalarParameterValue(
			FMaterialParameterInfo(TEXT("SkyTextureEmissiveIntensity")),
			ActualSkyEmissive
		);
	}

	if (IsValid(MoonMaterialInstance))
	{
		MoonMaterialInstance->GetScalarParameterValue(
			FMaterialParameterInfo(TEXT("MoonSourceEmissiveIntensity")),
			ActualMoonEmissive
		);
	}

	if (IsValid(MoonGlowMaterialInstance))
	{
		MoonGlowMaterialInstance->GetScalarParameterValue(
			FMaterialParameterInfo(TEXT("MoonGlowEmissiveIntensity")),
			ActualMoonGlowEmissive
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
		"\tTime   %s\t\t\t\t\t[%s]\n"
		"--------------------------------------------------\n"
		"[Sun] Intensity %.2f | Angle %.1f\n"
		"[SunIndirect] Intensity %.2f\n"
		"\n"
		"[Moon] Intensity %.2f | Angle %.1f \n"
		"[MoonIndirect] Intensity %.2f\n"
		"[MoonSource] Scale %.1f | Emissive Intensity %.1f\n"
		"[MoonGlow] Scale %.1f | Emissive Intensity %.1f\n"
		"[MoonAlign] View Alignment Error %.3f deg\n"
		"\n"
		"[SkyLight] Intensity %.2f | Indirect Intensity %.1f\n"
		"[SkyDome] Sky Emissive Intensity %.2f\n"
		"[Stars] Emissive Intensity %.2f\n"
		"\n"
		"[Fog] Density %.5f | Height Falloff %.5f\n"
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
		Sun.Indirect_Light_Intensity,
		Moon.Intensity, Moon.Source_Angle,
		Moon.Indirect_Light_Intensity,
		ActualMoonScale, ActualMoonEmissive,
		ActualMoonGlowScale, ActualMoonGlowEmissive,
		GetMoonAlignmentErrorDeg(),
		Sky.Sky_Light_Intensity, Sky.Sky_Indirect_Lighting_Intensity,
		ActualSkyEmissive,
		Sky.Star_Emissive_Intensity,
		Fog.Fog_Density, Fog.Fog_Height_Falloff,
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

	return FString::Printf(TEXT("%02d : %02d"), Hours, Minutes);
}

// 정렬
void ATODManager::SortTODDataArray()
{
	if (TOD_DataArray.Num() < 2) return;
	TOD_DataArray.StableSort([](const FTODMasterData& A, const FTODMasterData& B) { return A.Time < B.Time; });
}

float ATODManager::GetCalculatedMoonScale(float InTime) const
{
	float TargetScale = bOverrideMoonSourceScale ? OverriddenMoonSourceScale : GetMoonSourceScaleAtTime(InTime);

	TargetScale = FMath::Max(TargetScale, 0.001f);

	const float ReferenceDistance = 10000.0f;
	float DistanceRatio = GetScaledMoonDistance() / ReferenceDistance;

	return TargetScale * DistanceRatio;
}

float ATODManager::GetScaledMoonDistance() const
{
	if (!bAutoScaleMoonDistanceByMeshSize || !IsValid(MoonMesh))
	{
		return MoonDistance;
	}

	UStaticMesh* Mesh = MoonMesh->GetStaticMesh();
	if (!Mesh)
	{
		return MoonDistance;
	}

	const float LocalRadius = Mesh->GetBounds().SphereRadius;

	if (LocalRadius <= KINDA_SMALL_NUMBER || MoonMeshReferenceRadius <= KINDA_SMALL_NUMBER)
	{
		return MoonDistance;
	}

	return MoonDistance * (LocalRadius / MoonMeshReferenceRadius);
}

void ATODManager::UpdateMoonMeshTransform()
{
	if (!IsValid(MoonMesh)) return;

	if (IsValid(MeshPivotComponent))
	{
		MeshPivotComponent->SetRelativeRotation(MoonLocalRotationOffset);
	}

	const float ActualDistance = GetScaledMoonDistance();
	MoonMesh->SetRelativeLocation(FVector(-ActualDistance, 0.0f, 0.0f));

	const float BaseScale = FMath::Max(bOverrideMoonSourceScale ? OverriddenMoonSourceScale : GetMoonSourceScaleAtTime(CurrentSystemTime), 0.001f);
	MoonMesh->SetRelativeScale3D(FVector((BaseScale * (ActualDistance / 100000.0f)))); // moon 크기 조절

	if (IsValid(MoonGlowMesh) && IsValid(MeshPivotComponent))
	{
		const float GlowScale = FMath::Max(GetMoonGlowScaleAtTime(CurrentSystemTime), 0.001f);
		MoonGlowMesh->SetRelativeScale3D(FVector((GlowScale * (ActualDistance / 100000.0f)))); // moon glow 크기 조절

		const FVector MoonWorldLocation = MoonMesh->GetComponentLocation();
		const FVector PivotWorldLocation = MeshPivotComponent->GetComponentLocation();
		const FVector DirectionToPivot = (PivotWorldLocation - MoonWorldLocation).GetSafeNormal();

		// Moon의 현재 실제(월드) 반지름 계산
		float MoonWorldRadius = 0.0f;
		if (const UStaticMesh* MoonStaticMesh = MoonMesh->GetStaticMesh())
		{
			MoonWorldRadius = MoonStaticMesh->GetBounds().SphereRadius * MoonMesh->GetComponentScale().X;
		}

		// 반지름보다 살짝 크게 (10% 여유)
		constexpr float FrontOffsetMultiplier = 1.1f;
		const float FrontOffset = MoonWorldRadius * FrontOffsetMultiplier;

		MoonGlowMesh->SetWorldLocation(MoonWorldLocation + DirectionToPivot * FrontOffset);
	}
}

// ======== Curve Evaluation =========
void ATODManager::BakeTODCurves()
{
	FTODCurveEvaluator::BakeTODCurves(this);
}

void ATODManager::ApplyPPVBlending(float CurrentTime)
{
	FTODCurveEvaluator::ApplyPPVBlending(this, CurrentTime);
}

void ATODManager::GetTODSettingsAtTime(
	float InTime,
	FTODSunMoonSettings& OutSun,
	FTODMoonSettings& OutMoon,
	FTODSkyLightSettings& OutSkyLight,
	FTODFogSettings& OutFog,
	FTODSkyAtmosphereSettings& OutSkyAtmosphere)
{
	FTODCurveEvaluator::GetTODSettingsAtTime(
		this,
		InTime,
		OutSun,
		OutMoon,
		OutSkyLight,
		OutFog,
		OutSkyAtmosphere
	);
}

// =========================================================
// Sky Anchor: 활성 뷰 추종
// =========================================================

bool ATODManager::GetActiveViewLocation(FVector& OutViewLocation) const
{
	const UWorld* World = GetWorld();
	if (!World) return false;

	if (World->IsGameWorld())
	{
		// Camera Cut 트랙 / CineCamera / Movie Render Queue 모두
		// 로컬 플레이어의 뷰 타겟을 거치므로 PlayerCameraManager 하나로 커버된다.
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PC = It->Get();
			if (!PC || !PC->IsLocalPlayerController())
			{
				continue;
			}

			if (const APlayerCameraManager* CamMgr = PC->PlayerCameraManager)
			{
				OutViewLocation = CamMgr->GetCameraLocation();
				return true;
			}

			FVector ViewLoc = FVector::ZeroVector;
			FRotator ViewRot = FRotator::ZeroRotator;
			PC->GetPlayerViewPoint(ViewLoc, ViewRot);
			OutViewLocation = ViewLoc;
			return true;
		}

		return false;
	}

#if WITH_EDITOR
	if (!bFollowEditorViewport || !GEditor)
	{
		return false;
	}

	// 시퀀서 프리뷰 시 레벨 뷰포트는 씨네카메라에 락되므로
	// 뷰포트 클라이언트의 ViewLocation 이 곧 씨네카메라 위치가 된다.
	const FLevelEditorViewportClient* Client = GCurrentLevelEditingViewportClient;

	if (!Client || !Client->IsPerspective() || Client->GetWorld() != World)
	{
		Client = nullptr;

		for (const FLevelEditorViewportClient* Candidate : GEditor->GetLevelViewportClients())
		{
			if (Candidate &&
				Candidate->IsPerspective() &&
				Candidate->IsVisible() &&
				Candidate->GetWorld() == World)
			{
				Client = Candidate;
				break;
			}
		}
	}

	if (Client)
	{
		OutViewLocation = Client->GetViewLocation();
		return true;
	}
#endif

	return false;
}

void ATODManager::ResetSkyAnchorToActorOrigin()
{
	if (!IsValid(PivotOrbitTiltComponent))
	{
		return;
	}

	const FVector ActorLocation = GetActorLocation();
	if (PivotOrbitTiltComponent->GetComponentLocation().Equals(ActorLocation, 0.01f))
	{
		return;
	}

	PivotOrbitTiltComponent->SetWorldLocation(ActorLocation, false, nullptr, ETeleportType::TeleportPhysics);
}

bool ATODManager::UpdateSkyAnchorPosition()
{
	if (!IsValid(PivotOrbitTiltComponent))
	{
		return false;
	}

#if WITH_EDITOR
	// Undo/Redo 중 트랜스폼을 건드리면 트랜잭션이 오염된다.
	if (GIsTransacting)
	{
		return false;
	}
#endif

	if (!bSkyFollowsActiveView)
	{
		ResetSkyAnchorToActorOrigin();
		return false;
	}

	FVector ViewLocation = FVector::ZeroVector;
	if (!GetActiveViewLocation(ViewLocation))
	{
		return false;
	}

	if (PivotOrbitTiltComponent->GetComponentLocation().Equals(ViewLocation, 0.01f))
	{
		return false;
	}

	PivotOrbitTiltComponent->SetWorldLocation(ViewLocation, false, nullptr, ETeleportType::TeleportPhysics);
	return true;
}

float ATODManager::GetMoonAlignmentErrorDeg() const
{
	if (!IsValid(MoonMesh) || !IsValid(MoonLightComponent))
	{
		return 0.0f;
	}

	FVector ViewLocation = FVector::ZeroVector;
	if (!GetActiveViewLocation(ViewLocation))
	{
		return 0.0f;
	}

	const FVector ToMoon = (MoonMesh->GetComponentLocation() - ViewLocation).GetSafeNormal();
	const FVector ToMoonFromLight = -MoonLightComponent->GetForwardVector();

	if (ToMoon.IsNearlyZero())
	{
		return 0.0f;
	}

	const float Dot = FMath::Clamp(FVector::DotProduct(ToMoon, ToMoonFromLight), -1.0f, 1.0f);
	return FMath::RadiansToDegrees(FMath::Acos(Dot));
}

float ATODManager::GetMoonSourceScaleAtTime(float InTime) const
{
	return FTODCurveEvaluator::GetMoonSourceScaleAtTime(this, InTime);
}

float ATODManager::GetMoonGlowScaleAtTime(float InTime) const
{
	return FTODCurveEvaluator::GetMoonGlowScaleAtTime(this, InTime);
}

float ATODManager::GetMoonIntensity(float InTime) const
{
	return FTODCurveEvaluator::GetMoonIntensity(this, InTime);
}

float ATODManager::GetSunIntensity(float InTime) const
{
	return FTODCurveEvaluator::GetSunIntensity(this, InTime);
}

float ATODManager::GetFinalSpeed(float InTime)
{
	return CalculateCycleSpeed(CurrentSystemTime) * 50.0f;
}

void ATODManager::UpdatePivotRotation(float InTime)
{
	if (!IsValid(PivotSunMoonComponent))
	{
		return;
	}

	PivotSunMoonComponent->SetRelativeRotation(
		CalculatePivotRotation(InTime)
	);
}

FQuat ATODManager::CalculatePivotRotation(float InTime) const
{
	return TODSystem.CalculatePivotRotation(this, InTime);
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
	if (IsValid(PivotOrbitTiltComponent))
	{
		const FRotator OrbitTiltRotation(0.0f, SunAzimuthOffset, 0.0f);

		PivotOrbitTiltComponent->SetRelativeRotation(OrbitTiltRotation);
	}

	if (IsValid(MoonLightComponent))
	{
		MoonLightComponent->SetRelativeRotation(MoonLocalRotationOffset);
	}

	if (IsValid(MoonGlowMesh))
	{
		MoonGlowMesh->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	}
}

// 태양 방위각 변경 Setter
void ATODManager::SetSunAzimuthOffset(float InAzimuthOffset)
{
	SunAzimuthOffset = InAzimuthOffset;
	ApplyStaticSunMoonOffsets();
	MarkPackageDirty();
}

// ======= Presets: Editor =========
void ATODManager::SaveNewPreset()
{
	FTODEditor::SaveNewPreset(this);
}

void ATODManager::SaveCurrentPreset()
{
	FTODEditor::SaveCurrentPreset(this);
}

void ATODManager::OpenPresetDialog()
{
	FTODEditor::OpenPresetDialog(this);
}

void ATODManager::LoadSelectedPreset()
{
	FTODEditor::LoadSelectedPreset(this);
	BakeTODCurves();
	UpdateTOD(CurrentSystemTime);
}

void ATODManager::ForceViewportRedraw()
{
	FTODEditor::ForceViewportRedraw(this);
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

// =========================================================
// 에디터 전용 기능 (패키징 시 완전 제외)
// =========================================================

#if WITH_EDITOR
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

void ATODManager::RequestDeferredRebake()
{
	if (bRebakeRequested)
	{
		return;
	}

	bRebakeRequested = true;

	if (GEditor)
	{
		TWeakObjectPtr<ATODManager> WeakThis(this);

		GEditor->GetTimerManager()->SetTimerForNextTick(
			[WeakThis]()
			{
				if (!WeakThis.IsValid())
				{
					return;
				}

				ATODManager* Manager = WeakThis.Get();

				Manager->bRebakeRequested = false;
				Manager->UpdateSunTimes();
				Manager->BakeTODCurves();
				Manager->UpdateTOD(Manager->StartTime);
				Manager->ApplyStaticSunMoonOffsets();
				Manager->UpdatePivotRotation(Manager->StartTime);
				Manager->UpdateSkyAnchorPosition();
				Manager->UpdateMoonMeshTransform();
				Manager->ForceViewportRedraw();
			});

		return;
	}

	bRebakeRequested = false;

	BakeTODCurves();
	UpdateSunTimes();
	UpdateTOD(StartTime);
	ApplyStaticSunMoonOffsets();
	UpdatePivotRotation(StartTime);
	UpdateSkyAnchorPosition();
	UpdateMoonMeshTransform();
	ForceViewportRedraw();
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

		PreSaveWorldHandle =
			FEditorDelegates::PreSaveWorldWithContext.AddUObject(
				this,
				&ATODManager::OnPreSaveWorld
			);

		PostSaveWorldHandle =
			FEditorDelegates::PostSaveWorldWithContext.AddUObject(
				this,
				&ATODManager::OnPostSaveWorld
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

	if (PreSaveWorldHandle.IsValid())
	{
		FEditorDelegates::PreSaveWorldWithContext.Remove(PreSaveWorldHandle);
	}

	if (PostSaveWorldHandle.IsValid())
	{
		FEditorDelegates::PostSaveWorldWithContext.Remove(PostSaveWorldHandle);
	}

	Super::BeginDestroy();
}

// 저장 직전: 뷰 추종으로 밀려난 앵커 오프셋이 레벨에 직렬화되지 않도록 원점 복귀
void ATODManager::OnPreSaveWorld(UWorld* InWorld, FObjectPreSaveContext InContext)
{
	if (InWorld != GetWorld())
	{
		return;
	}

	ResetSkyAnchorToActorOrigin();
}

void ATODManager::OnPostSaveWorld(UWorld* InWorld, FObjectPostSaveContext InContext)
{
	if (InWorld != GetWorld())
	{
		return;
	}

	if (UpdateSkyAnchorPosition())
	{
		UpdateMoonMeshTransform();
	}
}

#endif

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
		RequestDeferredRebake();
		return;
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, bSkyFollowsActiveView) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, bFollowEditorViewport))
	{
		UpdateSkyAnchorPosition();
		UpdateMoonMeshTransform();
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

	// =========================================================================
	//  Latitude / Longitude / Season 변경 시 일출·일몰 재계산 + 뷰포트 즉시 업데이트
	// =========================================================================
	if (
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Latitude) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Longitude) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ATODManager, Season))
	{
		UpdateSunTimes();
		ApplyStaticSunMoonOffsets();
		UpdatePivotRotation(CurrentSystemTime);
		ForceViewportRedraw();
		return;
	}

	if (bIsInteractive)
	{
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

		// Interactive 여부
		const bool bIsInteractive =
			!!(PropertyChangedEvent.ChangeType & EPropertyChangeType::Interactive);

		if (ActiveMemberName == GET_MEMBER_NAME_CHECKED(ATODManager, TOD_DataArray))
		{
			const EPropertyChangeType::Type ChangeType =
				PropertyChangedEvent.ChangeType;

			const bool bArrayChanged =
				(ChangeType & EPropertyChangeType::ArrayAdd) ||
				(ChangeType & EPropertyChangeType::ArrayRemove) ||
				(ChangeType & EPropertyChangeType::ArrayClear) ||
				(ChangeType & EPropertyChangeType::Duplicate);

			// 배열 변경 시, Time 값이 겹치지 않도록 조정
			if (bArrayChanged)
			{
				const int32 ChangedIndex = PropertyChangedEvent.GetArrayIndex(
					GET_MEMBER_NAME_CHECKED(ATODManager, TOD_DataArray).ToString());

				if (TOD_DataArray.IsValidIndex(ChangedIndex))
				{
					const float BoundaryTolerance = 0.001f;
					bool bCollision = true;

					while (bCollision)
					{
						bCollision = false;
						for (int32 i = 0; i < TOD_DataArray.Num(); ++i)
						{
							if (i == ChangedIndex) continue;

							if (FMath::IsNearlyEqual(TOD_DataArray[i].Time, TOD_DataArray[ChangedIndex].Time, BoundaryTolerance))
							{
								TOD_DataArray[ChangedIndex].Time =
									FMath::Min(TOD_DataArray[ChangedIndex].Time + 0.1f, 24.0f);
								bCollision = true;
								break;
							}
						}
					}
				}
			}
			else if (
				!bIsInteractive &&   // 값이 확정된 경우만 검사
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
					else
					{
						// 0/24 경계가 아닌 일반 슬롯끼리의 Time 중복 검사
						bool bConflict = false;
						for (int32 i = 0; i < TOD_DataArray.Num(); ++i)
						{
							if (i == ChangedIndex) continue;

							if (FMath::IsNearlyEqual(TOD_DataArray[i].Time, NewTime, BoundaryTolerance))
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
								TOD_DataArray[ChangedIndex].Time = FMath::Clamp(NewTime + 0.1f, 0.0f, 24.0f);
							}

							FNotificationInfo Info(FText::FromString(TEXT(
								"Another slot already uses this time. "
								"Input reverted to avoid overwriting its data.")));
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

	if (!bIsRelevant || bPendingPPVUpdate)
	{
		return;
	}

	if (!GEditor)
	{
		return;
	}

	bPendingPPVUpdate = true;

	TWeakObjectPtr<ATODManager> WeakThis(this);
	GEditor->GetTimerManager()->SetTimerForNextTick([WeakThis]()
		{
			if (!WeakThis.IsValid())
			{
				return;
			}

			WeakThis->bPendingPPVUpdate = false;
			WeakThis->UpdateTOD(WeakThis->CurrentSystemTime);
			WeakThis->ForceViewportRedraw();
		});
}

void ATODManager::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);

	RequestDeferredRebake();
}

#endif