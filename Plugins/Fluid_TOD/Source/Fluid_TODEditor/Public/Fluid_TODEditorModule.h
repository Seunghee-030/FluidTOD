#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FFluid_TODEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:

};