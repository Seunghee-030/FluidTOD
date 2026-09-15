#pragma once

#include "CoreMinimal.h"

class ATODManager;

class FLUID_TOD_API FTODEditor
{
public:
    static void SaveNewPreset(ATODManager* Owner);
    static void SaveCurrentPreset(ATODManager* Owner);
    static void OpenPresetDialog(ATODManager* Owner);
    static void LoadSelectedPreset(ATODManager* Owner);

    static void ForceViewportRedraw(ATODManager* Owner);
};