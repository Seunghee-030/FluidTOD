// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class UToolMenu;
class AActor;

class FFluid_TODModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

#if WITH_EDITOR
private:
	// Window "Fluid TOD" 서브메뉴
	void RegisterMenus();
	void PopulateFluidTODSubMenu(UToolMenu* Menu);

	// EUW 블루프린트를 탭으로 오픈 (이미 열려있으면 재사용)
	void OpenFluidTODEUW();

	// 레벨 액터 삭제
	void OnLevelActorDeleted(AActor* Actor);

	FName SpawnedTabID;
	FDelegateHandle LevelActorDeletedHandle;
#endif
};