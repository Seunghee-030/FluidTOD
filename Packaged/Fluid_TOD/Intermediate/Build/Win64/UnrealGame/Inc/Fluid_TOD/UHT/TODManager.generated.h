// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TODManager.h"

#ifdef FLUID_TOD_TODManager_generated_h
#error "TODManager.generated.h already included, missing '#pragma once' in TODManager.h"
#endif
#define FLUID_TOD_TODManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ETODState : uint8;
struct FLinearColor;

// ********** Begin Delegate FOnTODDataChangedSignature ********************************************
#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_18_DELEGATE \
FLUID_TOD_API void FOnTODDataChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnTODDataChangedSignature);


// ********** End Delegate FOnTODDataChangedSignature **********************************************

// ********** Begin ScriptStruct FTODCinematicSetting **********************************************
struct Z_Construct_UScriptStruct_FTODCinematicSetting_Statics;
#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_24_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FTODCinematicSetting_Statics; \
	FLUID_TOD_API static class UScriptStruct* StaticStruct();


struct FTODCinematicSetting;
// ********** End ScriptStruct FTODCinematicSetting ************************************************

// ********** Begin Class ATODManager **************************************************************
#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execPrintTODDebugInfo); \
	DECLARE_FUNCTION(execGetFormattedTimeAsString); \
	DECLARE_FUNCTION(execForceViewportRedraw); \
	DECLARE_FUNCTION(execLoadSelectedPreset); \
	DECLARE_FUNCTION(execOpenPresetDialog); \
	DECLARE_FUNCTION(execSaveCurrentPreset); \
	DECLARE_FUNCTION(execSaveNewPreset); \
	DECLARE_FUNCTION(execCalculatePivotRotation); \
	DECLARE_FUNCTION(execUpdateSunTimes); \
	DECLARE_FUNCTION(execUpdatePivotRotation); \
	DECLARE_FUNCTION(execGetFinalSpeed); \
	DECLARE_FUNCTION(execGetSunIntensity); \
	DECLARE_FUNCTION(execGetMoonIntensity); \
	DECLARE_FUNCTION(execGetMoonSourceScaleAtTime); \
	DECLARE_FUNCTION(execUpdateTOD); \
	DECLARE_FUNCTION(execBakeTODCurves); \
	DECLARE_FUNCTION(execUpdateMoonMeshTransform); \
	DECLARE_FUNCTION(execGetCalculatedMoonScale); \
	DECLARE_FUNCTION(execUpdateSkyAnchorPosition); \
	DECLARE_FUNCTION(execSetSunAzimuthOffset); \
	DECLARE_FUNCTION(execGetFullDebugDumpString); \
	DECLARE_FUNCTION(execToggleTimePause); \
	DECLARE_FUNCTION(execToggleTimeDirection); \
	DECLARE_FUNCTION(execIsTimeInState); \
	DECLARE_FUNCTION(execGetCurrentTODState); \
	DECLARE_FUNCTION(execCalculateCycleSpeed); \
	DECLARE_FUNCTION(execSetCurrentTime); \
	DECLARE_FUNCTION(execGetCurrentTime); \
	DECLARE_FUNCTION(execSetStartTime); \
	DECLARE_FUNCTION(execGetStartTime); \
	DECLARE_FUNCTION(execSetMaterialVectorByName); \
	DECLARE_FUNCTION(execSetMaterialScalarByName); \
	DECLARE_FUNCTION(execEvaluateCinematicState);


#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ATODManager_Statics;
FLUID_TOD_API UClass* Z_Construct_UClass_ATODManager_NoRegister();

#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATODManager(); \
	friend struct ::Z_Construct_UClass_ATODManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FLUID_TOD_API UClass* ::Z_Construct_UClass_ATODManager_NoRegister(); \
public: \
	DECLARE_CLASS2(ATODManager, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Fluid_TOD"), Z_Construct_UClass_ATODManager_NoRegister) \
	DECLARE_SERIALIZER(ATODManager)


#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATODManager(ATODManager&&) = delete; \
	ATODManager(const ATODManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATODManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATODManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATODManager) \
	NO_API virtual ~ATODManager();


#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_36_PROLOG
#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_CALLBACK_WRAPPERS \
	FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_INCLASS_NO_PURE_DECLS \
	FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h_39_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATODManager;

// ********** End Class ATODManager ****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
