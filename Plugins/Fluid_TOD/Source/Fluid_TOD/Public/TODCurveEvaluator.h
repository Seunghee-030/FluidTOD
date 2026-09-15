#pragma once

#include "CoreMinimal.h"
#include "TOD_Types.h"

class ATODManager;
class APostProcessVolume;

struct FTODPPVEntry
{
    float Time = 0.0f;
    APostProcessVolume* PPV = nullptr;
};

class FLUID_TOD_API FTODCurveEvaluator
{
public:
    static void ApplyPPVBlending(ATODManager* Owner, float CurrentTime);

    static void RebuildPPVCache(ATODManager* Owner);

    static void BakeTODCurves(ATODManager* Owner);

    static void GetTODSettingsAtTime(
        ATODManager* Owner,
        float InTime,
        FTODSunMoonSettings& OutSun,
        FTODMoonSettings& OutMoon,
        FTODSkyLightSettings& OutSkyLight,
        FTODFogSettings& OutFog,
        FTODSkyAtmosphereSettings& OutSkyAtmosphere
    );

    static float GetMoonSourceScaleAtTime(const class ATODManager* Owner, float InTime);
    static float GetMoonGlowScaleAtTime(const class ATODManager* Owner, float InTime);
    static float GetMoonIntensity(const class ATODManager* Owner, float InTime);

    static float GetSunIntensity(const class ATODManager* Owner, float InTime);

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
};