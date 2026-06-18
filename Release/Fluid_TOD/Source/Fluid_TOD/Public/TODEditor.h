#pragma once

#include "CoreMinimal.h"

class ATODManager;
struct FPropertyChangedEvent;
struct FPropertyChangedChainEvent;

class FLUID_TOD_API FTODEditor
{
public:
    void SaveNewPreset(ATODManager* Owner);
    void SaveCurrentPreset(ATODManager* Owner);
    void OpenPresetDialog(ATODManager* Owner);
    void LoadSelectedPreset(ATODManager* Owner);

    void ForceViewportRedraw(ATODManager* Owner);

#if WITH_EDITOR
    void HandlePostEditChangeProperty(
        ATODManager* Owner,
        FPropertyChangedEvent& PropertyChangedEvent
    );

    void HandlePostEditChangeChainProperty(
        ATODManager* Owner,
        FPropertyChangedChainEvent& PropertyChangedEvent
    );
#endif
};