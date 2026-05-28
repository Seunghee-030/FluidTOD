#pragma once

class ATODManager;

struct FLUID_TOD_API FTODSystem
{
public:
    void FindComponents(ATODManager* Owner);

    void UpdateTOD(ATODManager* Owner, float CurrentTime);

    void UpdateState(ATODManager* Owner, float CurrentTime);

    void UpdateSunTimes(ATODManager* Owner);

    FRotator CalculatePivotRotation(
        const ATODManager* Owner,
        float InTime
    ) const;
};