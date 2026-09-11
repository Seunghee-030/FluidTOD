#pragma once

#include "CoreMinimal.h"
#include "TOD_Types.h"
#include "TODCurveEvaluator.generated.h"

class ATODManager;
class APostProcessVolume;

// 런타임 PPV 블렌드 캐시 엔트리.
// GC 추적을 위해 반드시 USTRUCT + TObjectPtr 여야 한다.
// raw 포인터로 두면 레벨 스트리밍/GC 시 해제된 메모리를 IsValid()로 읽게 된다.
USTRUCT()
struct FTODPPVEntry
{
    GENERATED_BODY()

    UPROPERTY()
    float Time = 0.0f;

    UPROPERTY()
    TObjectPtr<APostProcessVolume> PPV = nullptr;
};

class FLUID_TOD_API FTODCurveEvaluator
{
public:
    void ApplyPPVBlending(ATODManager* Owner, float CurrentTime);

    void RebuildPPVCache(ATODManager* Owner);

    // 다음 ApplyPPVBlending 호출에서 무조건 전체 재계산
    void InvalidatePPVBlendState();

    void BakeTODCurves(ATODManager* Owner);

    void GetTODSettingsAtTime(
        ATODManager* Owner,
        float InTime,
        FTODSunMoonSettings& OutSun,
        FTODMoonSettings& OutMoon,
        FTODSkyLightSettings& OutSkyLight,
        FTODFogSettings& OutFog,
        FTODSkyAtmosphereSettings& OutSkyAtmosphere
    );

    float GetMoonSourceScaleAtTime(const class ATODManager* Owner, float InTime) const;
    float GetMoonGlowScaleAtTime(const class ATODManager* Owner, float InTime) const;
    float GetMoonIntensity(const class ATODManager* Owner, float InTime) const;

    float GetSunIntensity(const class ATODManager* Owner, float InTime) const;

    static TArray<FRuntimeFloatCurve*> GetAllFloatCurves(class UTODCurveContainer* CurveData);
    static TArray<FRuntimeCurveLinearColor*> GetAllColorCurves(class UTODCurveContainer* CurveData);

    // Curve InterpMode를 캡처/복원
    static FTODCurveDataModeSnapshot CaptureInterpModes(class UTODCurveContainer* CurveData);
    static void RestoreInterpModes(class UTODCurveContainer* CurveData, const FTODCurveDataModeSnapshot& Snapshot);

#if WITH_EDITOR
    static TArray<TPair<float, float>> SnapshotFloatCurve(const FRuntimeFloatCurve& Curve);
    static TArray<TArray<TPair<float, float>>> SnapshotColorCurve(const FRuntimeCurveLinearColor& Curve);

    static void SyncGraphEditToDataArray(ATODManager* Owner, class UTODCurveContainer* CurveData);
#endif

private:
    // ApplyPPVBlending 조기 탈출 상태.
    // 블렌드 구간과 Alpha가 사실상 그대로면 FPostProcessSettings 재구성 전체를 건너뛴다.
    int32 LastPrevIndex = INDEX_NONE;
    int32 LastNextIndex = INDEX_NONE;
    float LastAlpha = -1.0f;
    bool bPPVBlendStateValid = false;
};