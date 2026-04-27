#include "Fluid_TODEditorModule.h"
#include "Modules/ModuleManager.h"

void FFluid_TODEditorModule::StartupModule()
{
}

void FFluid_TODEditorModule::ShutdownModule()
{
}

// 이 부분이 반드시 있어야 엔진이 이 클래스를 모듈로 인식합니다.
IMPLEMENT_MODULE(FFluid_TODEditorModule, Fluid_TODEditor)