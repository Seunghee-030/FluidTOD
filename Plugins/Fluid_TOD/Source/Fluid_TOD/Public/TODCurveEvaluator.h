#pragma once

#include "CoreMinimal.h"
#include "TOD_Types.h"

class ATODManager;

class FLUID_TOD_API FTODCurveEvaluator
{
public:
    void ApplyPPVBlending(ATODManager* Owner, float CurrentTime);

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
};