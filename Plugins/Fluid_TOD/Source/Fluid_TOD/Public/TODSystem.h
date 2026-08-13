#pragma once

#include "CoreMinimal.h"
#include "TOD_Types.h"

class ATODManager;

struct FLUID_TOD_API FTODSystem
{
public:
    void FindComponents(ATODManager* Owner);

    void UpdateTOD(ATODManager* Owner, float CurrentTime);

    void UpdateState(ATODManager* Owner, float CurrentTime);

    void UpdateSunTimes(ATODManager* Owner);

    static float NormalizeTime(float Time);

    static float GetSeasonDeclinationDeg(ETODSeason Season);

    FQuat CalculatePivotRotation(
        const ATODManager* Owner,
        float InTime) const;
};