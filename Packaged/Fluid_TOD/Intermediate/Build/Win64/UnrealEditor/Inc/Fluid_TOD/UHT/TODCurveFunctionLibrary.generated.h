// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TODCurveFunctionLibrary.h"

#ifdef FLUID_TOD_TODCurveFunctionLibrary_generated_h
#error "TODCurveFunctionLibrary.generated.h already included, missing '#pragma once' in TODCurveFunctionLibrary.h"
#endif
#define FLUID_TOD_TODCurveFunctionLibrary_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLinearColor;
struct FRuntimeCurveLinearColor;
struct FRuntimeFloatCurve;

// ********** Begin Class UTODCurveFunctionLibrary *************************************************
#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSealColorCurveFor24Hours); \
	DECLARE_FUNCTION(execSealTODCurveFor24Hours); \
	DECLARE_FUNCTION(execGetRuntimeColorCurveValue); \
	DECLARE_FUNCTION(execAddKeyToRuntimeColorCurve); \
	DECLARE_FUNCTION(execClearRuntimeColorCurve); \
	DECLARE_FUNCTION(execAddKeyToRuntimeFloatCurve); \
	DECLARE_FUNCTION(execClearRuntimeFloatCurve);


struct Z_Construct_UClass_UTODCurveFunctionLibrary_Statics;
FLUID_TOD_API UClass* Z_Construct_UClass_UTODCurveFunctionLibrary_NoRegister();

#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUTODCurveFunctionLibrary(); \
	friend struct ::Z_Construct_UClass_UTODCurveFunctionLibrary_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FLUID_TOD_API UClass* ::Z_Construct_UClass_UTODCurveFunctionLibrary_NoRegister(); \
public: \
	DECLARE_CLASS2(UTODCurveFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Fluid_TOD"), Z_Construct_UClass_UTODCurveFunctionLibrary_NoRegister) \
	DECLARE_SERIALIZER(UTODCurveFunctionLibrary)


#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UTODCurveFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UTODCurveFunctionLibrary(UTODCurveFunctionLibrary&&) = delete; \
	UTODCurveFunctionLibrary(const UTODCurveFunctionLibrary&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UTODCurveFunctionLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UTODCurveFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UTODCurveFunctionLibrary) \
	NO_API virtual ~UTODCurveFunctionLibrary();


#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_12_PROLOG
#define FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UTODCurveFunctionLibrary;

// ********** End Class UTODCurveFunctionLibrary ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
