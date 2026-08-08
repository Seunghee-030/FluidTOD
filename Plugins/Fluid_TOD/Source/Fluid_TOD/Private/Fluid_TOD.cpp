// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fluid_TOD.h"
#include "EngineUtils.h"
#include "TODManager.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"


#define LOCTEXT_NAMESPACE "FFluid_TODModule"

void FFluid_TODModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FFluid_TODModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

// 콘솔 명령어: TOD 시간 즉시 변경
static FAutoConsoleCommandWithWorldAndArgs CVar_TOD_SetTime(
    TEXT("Tod"),
    TEXT("Tod time (0–24/Immediately sets the current time in the TOD manager. Example: Tod 12)"),
    FConsoleCommandWithWorldAndArgsDelegate::CreateLambda(
        [](const TArray<FString>& Args, UWorld* World)
        {
            if (!World || Args.Num() == 0) return;
            const float NewTime = FCString::Atof(*Args[0]);

            for (TActorIterator<ATODManager> It(World); It; ++It)
            {
                It->SetCurrentTime(NewTime);
                break; // 씬에 매니저가 하나
            }
        })
);

// 콘솔 명령어: TOD 시간 상대 이동 (+3시간)
static FAutoConsoleCommandWithWorldAndArgs CVar_TOD_Jump(
    TEXT("Tod.Jump"),
    TEXT("Usage: Tod.Jump 3 (relative movement from the current time, negative values are allowed)"),
    FConsoleCommandWithWorldAndArgsDelegate::CreateLambda(
        [](const TArray<FString>& Args, UWorld* World)
        {
            if (!World || Args.Num() == 0) return;
            const float Delta = FCString::Atof(*Args[0]);
            for (TActorIterator<ATODManager> It(World); It; ++It)
            {
                It->SetCurrentTime(It->GetCurrentTime() + Delta); // Fmod 처리는 SetCurrentTime 내부에 없으므로 필요시 wrap 추가
                break;
            }
        })
);

// 콘솔 명령어: TOD 시간 흐름 방향 전환
static FAutoConsoleCommandWithWorld CVar_TOD_ToggleReverse(
    TEXT("Tod.Reverse"),
    TEXT("Tod.Reverse (Toggles the time direction in the TOD manager.)"),
    FConsoleCommandWithWorldDelegate::CreateLambda(
        [](UWorld* World)
        {
            if (!World) return;

            for (TActorIterator<ATODManager> It(World); It; ++It)
            {
                It->ToggleTimeDirection();
                break;
            }
        })
);

// 콘솔 명령어: TOD 시간 일시정지/재개
static FAutoConsoleCommandWithWorldAndArgs CVar_TOD_TogglePause(
    TEXT("Tod.Pause"),
    TEXT("Tod.Pause [0|1] (If there’s no person, toggle; 1= pause, 0= play)"),
    FConsoleCommandWithWorldAndArgsDelegate::CreateLambda(
        [](const TArray<FString>& Args, UWorld* World)
        {
            if (!World) return;
            ATODManager* Manager = nullptr;
            for (TActorIterator<ATODManager> It(World); It; ++It)
            {
                Manager = *It;
                break;
            }
            if (!Manager) return;

            if (Args.Num() == 0) { Manager->ToggleTimePause(); }
            else
            {
                const bool bWantPause = FCString::Atoi(*Args[0]) != 0;
                if (Manager->IsTimePaused() != bWantPause)
                {
                    Manager->ToggleTimePause();
                }
            }

            UE_LOG(LogTemp, Log, TEXT("[TOD] TimePaused = %s"),
                Manager->IsTimePaused() ? TEXT("true") : TEXT("false"));
        })
);


// 콘솔 명령어: TOD 곡선 재베이크
static FAutoConsoleCommandWithWorld CVar_TOD_Bake(
    TEXT("Tod.Bake"),
    TEXT("Tod.Bake (Forces TOD curve rebake.)"),    
    FConsoleCommandWithWorldDelegate::CreateLambda(
        [](UWorld* World)
        {
            if (!World) return;
            for (TActorIterator<ATODManager> It(World); It; ++It)
            {
                It->BakeTODCurves();
                It->UpdateTOD(It->GetCurrentTime());
                break;
            }
        })
);

// 콘솔 명령어: TOD 상태 출력
static FAutoConsoleCommandWithWorld CVar_TOD_PrintFullState(
    TEXT("Tod.Log"),
    TEXT("Tod.Log (Dumps every TOD manager variable to the log.)"),
    FConsoleCommandWithWorldDelegate::CreateLambda(
        [](UWorld* World)
        {
            if (!World) return;
            for (TActorIterator<ATODManager> It(World); It; ++It)
            {
                UE_LOG(LogTemp, Log, TEXT("%s"), *It->GetFullDebugDumpString());
                break;
            }
        })
);
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFluid_TODModule, Fluid_TOD)