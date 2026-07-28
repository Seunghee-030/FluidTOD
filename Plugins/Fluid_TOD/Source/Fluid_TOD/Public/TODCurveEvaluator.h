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
};