// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TODManager.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "TOD_Types.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTODManager() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FQuat();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDirectionalLightComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UExponentialHeightFogComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPostProcessComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkyAtmosphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkyLightComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeCurveLinearColor();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
FLUID_TOD_API UClass* Z_Construct_UClass_ATODManager();
FLUID_TOD_API UClass* Z_Construct_UClass_ATODManager_NoRegister();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODCurveContainer_NoRegister();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODPresetData_NoRegister();
FLUID_TOD_API UEnum* Z_Construct_UEnum_Fluid_TOD_ETODSeason();
FLUID_TOD_API UEnum* Z_Construct_UEnum_Fluid_TOD_ETODState();
FLUID_TOD_API UFunction* Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODCinematicSetting();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODMasterData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODTimePoint();
LEVELSEQUENCE_API UClass* Z_Construct_UClass_ALevelSequenceActor_NoRegister();
UPackage* Z_Construct_UPackage__Script_Fluid_TOD();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnTODDataChangedSignature ********************************************
struct Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnTODDataChangedSignature constinit property declarations ************
// ********** End Delegate FOnTODDataChangedSignature constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Fluid_TOD, nullptr, "OnTODDataChangedSignature__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnTODDataChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnTODDataChangedSignature)
{
	OnTODDataChangedSignature.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnTODDataChangedSignature **********************************************

// ********** Begin ScriptStruct FTODCinematicSetting **********************************************
struct Z_Construct_UScriptStruct_FTODCinematicSetting_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODCinematicSetting); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODCinematicSetting); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// \xec\x8b\x9c\xed\x80\x80\xec\x84\x9c\xeb\xb3\x84 TOD \xec\xa0\x9c\xec\x96\xb4 \xec\x98\xb5\xec\x85\x98 \xec\x84\xa4\xec\xa0\x95 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "\xec\x8b\x9c\xed\x80\x80\xec\x84\x9c\xeb\xb3\x84 TOD \xec\xa0\x9c\xec\x96\xb4 \xec\x98\xb5\xec\x85\x98 \xec\x84\xa4\xec\xa0\x95 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SequenceActor_MetaData[] = {
		{ "Category", "Cinematic" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPauseTime_MetaData[] = {
		{ "Category", "Cinematic" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Pauses TOD time progression during sequence playback." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOverrideVisuals_MetaData[] = {
		{ "Category", "Cinematic" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Stops TOD visual updates to allow sequence-based overrides." },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODCinematicSetting constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SequenceActor;
	static void NewProp_bPauseTime_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPauseTime;
	static void NewProp_bOverrideVisuals_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverrideVisuals;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODCinematicSetting constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODCinematicSetting>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODCinematicSetting_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODCinematicSetting;
class UScriptStruct* FTODCinematicSetting::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODCinematicSetting.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODCinematicSetting.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODCinematicSetting, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODCinematicSetting"));
	}
	return Z_Registration_Info_UScriptStruct_FTODCinematicSetting.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODCinematicSetting Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_SequenceActor = { "SequenceActor", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODCinematicSetting, SequenceActor), Z_Construct_UClass_ALevelSequenceActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SequenceActor_MetaData), NewProp_SequenceActor_MetaData) };
void Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bPauseTime_SetBit(void* Obj)
{
	((FTODCinematicSetting*)Obj)->bPauseTime = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bPauseTime = { "bPauseTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FTODCinematicSetting), &Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bPauseTime_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPauseTime_MetaData), NewProp_bPauseTime_MetaData) };
void Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bOverrideVisuals_SetBit(void* Obj)
{
	((FTODCinematicSetting*)Obj)->bOverrideVisuals = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bOverrideVisuals = { "bOverrideVisuals", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FTODCinematicSetting), &Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bOverrideVisuals_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOverrideVisuals_MetaData), NewProp_bOverrideVisuals_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_SequenceActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bPauseTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewProp_bOverrideVisuals,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODCinematicSetting Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODCinematicSetting",
	Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::PropPointers),
	sizeof(FTODCinematicSetting),
	alignof(FTODCinematicSetting),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODCinematicSetting()
{
	if (!Z_Registration_Info_UScriptStruct_FTODCinematicSetting.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODCinematicSetting.InnerSingleton, Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODCinematicSetting.InnerSingleton);
}
// ********** End ScriptStruct FTODCinematicSetting ************************************************

// ********** Begin Class ATODManager Function BakeTODCurves ***************************************
struct Z_Construct_UFunction_ATODManager_BakeTODCurves_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|System" },
		{ "Comment", "// =========================================================================\n// Functions: System\n// =========================================================================\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Functions: System" },
	};
#endif // WITH_METADATA

// ********** Begin Function BakeTODCurves constinit property declarations *************************
// ********** End Function BakeTODCurves constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_BakeTODCurves_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "BakeTODCurves", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_BakeTODCurves_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_BakeTODCurves_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_BakeTODCurves()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_BakeTODCurves_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execBakeTODCurves)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BakeTODCurves();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function BakeTODCurves *****************************************

// ********** Begin Class ATODManager Function CalculateCycleSpeed *********************************
struct Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics
{
	struct TODManager_eventCalculateCycleSpeed_Parms
	{
		float InTime;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CalculateCycleSpeed constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CalculateCycleSpeed constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CalculateCycleSpeed Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventCalculateCycleSpeed_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventCalculateCycleSpeed_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::PropPointers) < 2048);
// ********** End Function CalculateCycleSpeed Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "CalculateCycleSpeed", 	Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::TODManager_eventCalculateCycleSpeed_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::TODManager_eventCalculateCycleSpeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_CalculateCycleSpeed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_CalculateCycleSpeed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execCalculateCycleSpeed)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->CalculateCycleSpeed(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function CalculateCycleSpeed ***********************************

// ********** Begin Class ATODManager Function CalculatePivotRotation ******************************
struct Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics
{
	struct TODManager_eventCalculatePivotRotation_Parms
	{
		float InTime;
		FQuat ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CalculatePivotRotation constinit property declarations ****************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CalculatePivotRotation constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CalculatePivotRotation Property Definitions ***************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventCalculatePivotRotation_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventCalculatePivotRotation_Parms, ReturnValue), Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::PropPointers) < 2048);
// ********** End Function CalculatePivotRotation Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "CalculatePivotRotation", 	Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::TODManager_eventCalculatePivotRotation_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::TODManager_eventCalculatePivotRotation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_CalculatePivotRotation()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_CalculatePivotRotation_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execCalculatePivotRotation)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FQuat*)Z_Param__Result=P_THIS->CalculatePivotRotation(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function CalculatePivotRotation ********************************

// ********** Begin Class ATODManager Function EvaluateCinematicState ******************************
struct Z_Construct_UFunction_ATODManager_EvaluateCinematicState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function EvaluateCinematicState constinit property declarations ****************
// ********** End Function EvaluateCinematicState constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_EvaluateCinematicState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "EvaluateCinematicState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_EvaluateCinematicState_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_EvaluateCinematicState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_EvaluateCinematicState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_EvaluateCinematicState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execEvaluateCinematicState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->EvaluateCinematicState();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function EvaluateCinematicState ********************************

// ********** Begin Class ATODManager Function FindComponents **************************************
struct Z_Construct_UFunction_ATODManager_FindComponents_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|System" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function FindComponents constinit property declarations ************************
// ********** End Function FindComponents constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_FindComponents_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "FindComponents", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_FindComponents_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_FindComponents_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_FindComponents()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_FindComponents_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execFindComponents)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->FindComponents();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function FindComponents ****************************************

// ********** Begin Class ATODManager Function ForceViewportRedraw *********************************
struct Z_Construct_UFunction_ATODManager_ForceViewportRedraw_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Editor" },
		{ "Comment", "// =========================================================================\n// Functions: Editor & Helper\n// =========================================================================\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Functions: Editor & Helper" },
	};
#endif // WITH_METADATA

// ********** Begin Function ForceViewportRedraw constinit property declarations *******************
// ********** End Function ForceViewportRedraw constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_ForceViewportRedraw_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "ForceViewportRedraw", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_ForceViewportRedraw_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_ForceViewportRedraw_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_ForceViewportRedraw()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_ForceViewportRedraw_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execForceViewportRedraw)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ForceViewportRedraw();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function ForceViewportRedraw ***********************************

// ********** Begin Class ATODManager Function GetCalculatedMoonScale ******************************
struct Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics
{
	struct TODManager_eventGetCalculatedMoonScale_Parms
	{
		float InTime;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Moon" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCalculatedMoonScale constinit property declarations ****************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCalculatedMoonScale constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCalculatedMoonScale Property Definitions ***************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetCalculatedMoonScale_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetCalculatedMoonScale_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::PropPointers) < 2048);
// ********** End Function GetCalculatedMoonScale Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetCalculatedMoonScale", 	Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::TODManager_eventGetCalculatedMoonScale_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::TODManager_eventGetCalculatedMoonScale_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetCalculatedMoonScale)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetCalculatedMoonScale(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetCalculatedMoonScale ********************************

// ********** Begin Class ATODManager Function GetCurrentTime **************************************
struct Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics
{
	struct TODManager_eventGetCurrentTime_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentTime constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentTime constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentTime Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetCurrentTime_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentTime Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetCurrentTime", 	Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::TODManager_eventGetCurrentTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::TODManager_eventGetCurrentTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetCurrentTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetCurrentTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetCurrentTime)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetCurrentTime();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetCurrentTime ****************************************

// ********** Begin Class ATODManager Function GetCurrentTODState **********************************
struct Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics
{
	struct TODManager_eventGetCurrentTODState_Parms
	{
		float InTime;
		ETODState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentTODState constinit property declarations ********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentTODState constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentTODState Property Definitions *******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetCurrentTODState_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetCurrentTODState_Parms, ReturnValue), Z_Construct_UEnum_Fluid_TOD_ETODState, METADATA_PARAMS(0, nullptr) }; // 2526692313
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentTODState Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetCurrentTODState", 	Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::TODManager_eventGetCurrentTODState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::TODManager_eventGetCurrentTODState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetCurrentTODState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetCurrentTODState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetCurrentTODState)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ETODState*)Z_Param__Result=P_THIS->GetCurrentTODState(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetCurrentTODState ************************************

// ********** Begin Class ATODManager Function GetFinalSpeed ***************************************
struct Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics
{
	struct TODManager_eventGetFinalSpeed_Parms
	{
		float InTime;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Speed" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetFinalSpeed constinit property declarations *************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetFinalSpeed constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetFinalSpeed Property Definitions ************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetFinalSpeed_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetFinalSpeed_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::PropPointers) < 2048);
// ********** End Function GetFinalSpeed Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetFinalSpeed", 	Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::TODManager_eventGetFinalSpeed_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::TODManager_eventGetFinalSpeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetFinalSpeed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetFinalSpeed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetFinalSpeed)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetFinalSpeed(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetFinalSpeed *****************************************

// ********** Begin Class ATODManager Function GetFormattedTimeAsString ****************************
struct Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics
{
	struct TODManager_eventGetFormattedTimeAsString_Parms
	{
		float InTime;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Helper" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetFormattedTimeAsString constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetFormattedTimeAsString constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetFormattedTimeAsString Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetFormattedTimeAsString_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetFormattedTimeAsString_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::PropPointers) < 2048);
// ********** End Function GetFormattedTimeAsString Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetFormattedTimeAsString", 	Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::TODManager_eventGetFormattedTimeAsString_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::TODManager_eventGetFormattedTimeAsString_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetFormattedTimeAsString)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetFormattedTimeAsString(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetFormattedTimeAsString ******************************

// ********** Begin Class ATODManager Function GetMoonGlowScaleAtTime ******************************
struct Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics
{
	struct TODManager_eventGetMoonGlowScaleAtTime_Parms
	{
		float InTime;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Moon" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMoonGlowScaleAtTime constinit property declarations ****************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMoonGlowScaleAtTime constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMoonGlowScaleAtTime Property Definitions ***************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetMoonGlowScaleAtTime_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetMoonGlowScaleAtTime_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::PropPointers) < 2048);
// ********** End Function GetMoonGlowScaleAtTime Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetMoonGlowScaleAtTime", 	Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::TODManager_eventGetMoonGlowScaleAtTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::TODManager_eventGetMoonGlowScaleAtTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetMoonGlowScaleAtTime)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetMoonGlowScaleAtTime(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetMoonGlowScaleAtTime ********************************

// ********** Begin Class ATODManager Function GetMoonIntensity ************************************
struct Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics
{
	struct TODManager_eventGetMoonIntensity_Parms
	{
		float InTime;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Moon" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMoonIntensity constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMoonIntensity constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMoonIntensity Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetMoonIntensity_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetMoonIntensity_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::PropPointers) < 2048);
// ********** End Function GetMoonIntensity Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetMoonIntensity", 	Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::TODManager_eventGetMoonIntensity_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::TODManager_eventGetMoonIntensity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetMoonIntensity()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetMoonIntensity_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetMoonIntensity)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetMoonIntensity(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetMoonIntensity **************************************

// ********** Begin Class ATODManager Function GetMoonSourceScaleAtTime ****************************
struct Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics
{
	struct TODManager_eventGetMoonSourceScaleAtTime_Parms
	{
		float InTime;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Moon" },
		{ "Comment", "// getter for print debug info\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "getter for print debug info" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMoonSourceScaleAtTime constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMoonSourceScaleAtTime constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMoonSourceScaleAtTime Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetMoonSourceScaleAtTime_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetMoonSourceScaleAtTime_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::PropPointers) < 2048);
// ********** End Function GetMoonSourceScaleAtTime Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetMoonSourceScaleAtTime", 	Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::TODManager_eventGetMoonSourceScaleAtTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::TODManager_eventGetMoonSourceScaleAtTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetMoonSourceScaleAtTime)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetMoonSourceScaleAtTime(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetMoonSourceScaleAtTime ******************************

// ********** Begin Class ATODManager Function GetStartTime ****************************************
struct Z_Construct_UFunction_ATODManager_GetStartTime_Statics
{
	struct TODManager_eventGetStartTime_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStartTime constinit property declarations **************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStartTime constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStartTime Property Definitions *************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetStartTime_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetStartTime_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetStartTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetStartTime_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetStartTime_Statics::PropPointers) < 2048);
// ********** End Function GetStartTime Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetStartTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetStartTime", 	Z_Construct_UFunction_ATODManager_GetStartTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetStartTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetStartTime_Statics::TODManager_eventGetStartTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetStartTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetStartTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetStartTime_Statics::TODManager_eventGetStartTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetStartTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetStartTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetStartTime)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetStartTime();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetStartTime ******************************************

// ********** Begin Class ATODManager Function GetSunIntensity *************************************
struct Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics
{
	struct TODManager_eventGetSunIntensity_Parms
	{
		float InTime;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Sun" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetSunIntensity constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSunIntensity constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSunIntensity Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetSunIntensity_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventGetSunIntensity_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::PropPointers) < 2048);
// ********** End Function GetSunIntensity Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "GetSunIntensity", 	Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::TODManager_eventGetSunIntensity_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::TODManager_eventGetSunIntensity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_GetSunIntensity()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_GetSunIntensity_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execGetSunIntensity)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetSunIntensity(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function GetSunIntensity ***************************************

// ********** Begin Class ATODManager Function IsTimeInState ***************************************
struct Z_Construct_UFunction_ATODManager_IsTimeInState_Statics
{
	struct TODManager_eventIsTimeInState_Parms
	{
		float InTime;
		ETODState TargetState;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsTimeInState constinit property declarations *************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FBytePropertyParams NewProp_TargetState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_TargetState;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsTimeInState constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsTimeInState Property Definitions ************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventIsTimeInState_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_TargetState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_TargetState = { "TargetState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventIsTimeInState_Parms, TargetState), Z_Construct_UEnum_Fluid_TOD_ETODState, METADATA_PARAMS(0, nullptr) }; // 2526692313
void Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((TODManager_eventIsTimeInState_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TODManager_eventIsTimeInState_Parms), &Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_TargetState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_TargetState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::PropPointers) < 2048);
// ********** End Function IsTimeInState Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "IsTimeInState", 	Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::TODManager_eventIsTimeInState_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::TODManager_eventIsTimeInState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_IsTimeInState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_IsTimeInState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execIsTimeInState)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_GET_ENUM(ETODState,Z_Param_TargetState);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsTimeInState(Z_Param_InTime,ETODState(Z_Param_TargetState));
	P_NATIVE_END;
}
// ********** End Class ATODManager Function IsTimeInState *****************************************

// ********** Begin Class ATODManager Function LoadSelectedPreset **********************************
struct Z_Construct_UFunction_ATODManager_LoadSelectedPreset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Preset" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function LoadSelectedPreset constinit property declarations ********************
// ********** End Function LoadSelectedPreset constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_LoadSelectedPreset_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "LoadSelectedPreset", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_LoadSelectedPreset_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_LoadSelectedPreset_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_LoadSelectedPreset()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_LoadSelectedPreset_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execLoadSelectedPreset)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->LoadSelectedPreset();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function LoadSelectedPreset ************************************

// ********** Begin Class ATODManager Function OnUpdateCustomMaterials *****************************
struct TODManager_eventOnUpdateCustomMaterials_Parms
{
	float CurrentTime;
};
static FName NAME_ATODManager_OnUpdateCustomMaterials = FName(TEXT("OnUpdateCustomMaterials"));
void ATODManager::OnUpdateCustomMaterials(float CurrentTime)
{
	TODManager_eventOnUpdateCustomMaterials_Parms Parms;
	Parms.CurrentTime=CurrentTime;
	UFunction* Func = FindFunctionChecked(NAME_ATODManager_OnUpdateCustomMaterials);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Events" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnUpdateCustomMaterials constinit property declarations ***************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnUpdateCustomMaterials constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnUpdateCustomMaterials Property Definitions **************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::NewProp_CurrentTime = { "CurrentTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventOnUpdateCustomMaterials_Parms, CurrentTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::NewProp_CurrentTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::PropPointers) < 2048);
// ********** End Function OnUpdateCustomMaterials Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "OnUpdateCustomMaterials", 	Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::PropPointers), 
sizeof(TODManager_eventOnUpdateCustomMaterials_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(TODManager_eventOnUpdateCustomMaterials_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ATODManager Function OnUpdateCustomMaterials *******************************

// ********** Begin Class ATODManager Function OpenPresetDialog ************************************
struct Z_Construct_UFunction_ATODManager_OpenPresetDialog_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Preset" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OpenPresetDialog constinit property declarations **********************
// ********** End Function OpenPresetDialog constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_OpenPresetDialog_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "OpenPresetDialog", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_OpenPresetDialog_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_OpenPresetDialog_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_OpenPresetDialog()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_OpenPresetDialog_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execOpenPresetDialog)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OpenPresetDialog();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function OpenPresetDialog **************************************

// ********** Begin Class ATODManager Function PrintTODDebugInfo ***********************************
struct Z_Construct_UFunction_ATODManager_PrintTODDebugInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PrintTODDebugInfo constinit property declarations *********************
// ********** End Function PrintTODDebugInfo constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_PrintTODDebugInfo_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "PrintTODDebugInfo", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_PrintTODDebugInfo_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_PrintTODDebugInfo_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_PrintTODDebugInfo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_PrintTODDebugInfo_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execPrintTODDebugInfo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PrintTODDebugInfo();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function PrintTODDebugInfo *************************************

// ********** Begin Class ATODManager Function SaveCurrentPreset ***********************************
struct Z_Construct_UFunction_ATODManager_SaveCurrentPreset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "TOD|Preset" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SaveCurrentPreset constinit property declarations *********************
// ********** End Function SaveCurrentPreset constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_SaveCurrentPreset_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "SaveCurrentPreset", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SaveCurrentPreset_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_SaveCurrentPreset_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_SaveCurrentPreset()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_SaveCurrentPreset_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execSaveCurrentPreset)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SaveCurrentPreset();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function SaveCurrentPreset *************************************

// ********** Begin Class ATODManager Function SaveNewPreset ***************************************
struct Z_Construct_UFunction_ATODManager_SaveNewPreset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "TOD|Preset" },
		{ "Comment", "// =========================================================================\n// Functions: Preset\n// =========================================================================\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Functions: Preset" },
	};
#endif // WITH_METADATA

// ********** Begin Function SaveNewPreset constinit property declarations *************************
// ********** End Function SaveNewPreset constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_SaveNewPreset_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "SaveNewPreset", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SaveNewPreset_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_SaveNewPreset_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_SaveNewPreset()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_SaveNewPreset_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execSaveNewPreset)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SaveNewPreset();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function SaveNewPreset *****************************************

// ********** Begin Class ATODManager Function SetCurrentTime **************************************
struct Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics
{
	struct TODManager_eventSetCurrentTime_Parms
	{
		float NewTime;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetCurrentTime constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetCurrentTime constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetCurrentTime Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::NewProp_NewTime = { "NewTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventSetCurrentTime_Parms, NewTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::NewProp_NewTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::PropPointers) < 2048);
// ********** End Function SetCurrentTime Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "SetCurrentTime", 	Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::TODManager_eventSetCurrentTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::TODManager_eventSetCurrentTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_SetCurrentTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_SetCurrentTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execSetCurrentTime)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetCurrentTime(Z_Param_NewTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function SetCurrentTime ****************************************

// ********** Begin Class ATODManager Function SetMaterialScalarByName *****************************
struct Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics
{
	struct TODManager_eventSetMaterialScalarByName_Parms
	{
		FName ParameterName;
		float Value;
		bool bSkyDome;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Material" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetMaterialScalarByName constinit property declarations ***************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ParameterName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static void NewProp_bSkyDome_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkyDome;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetMaterialScalarByName constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetMaterialScalarByName Property Definitions **************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_ParameterName = { "ParameterName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventSetMaterialScalarByName_Parms, ParameterName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventSetMaterialScalarByName_Parms, Value), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_bSkyDome_SetBit(void* Obj)
{
	((TODManager_eventSetMaterialScalarByName_Parms*)Obj)->bSkyDome = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_bSkyDome = { "bSkyDome", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TODManager_eventSetMaterialScalarByName_Parms), &Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_bSkyDome_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_ParameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::NewProp_bSkyDome,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::PropPointers) < 2048);
// ********** End Function SetMaterialScalarByName Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "SetMaterialScalarByName", 	Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::TODManager_eventSetMaterialScalarByName_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::TODManager_eventSetMaterialScalarByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_SetMaterialScalarByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_SetMaterialScalarByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execSetMaterialScalarByName)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ParameterName);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_GET_UBOOL(Z_Param_bSkyDome);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMaterialScalarByName(Z_Param_ParameterName,Z_Param_Value,Z_Param_bSkyDome);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function SetMaterialScalarByName *******************************

// ********** Begin Class ATODManager Function SetMaterialVectorByName *****************************
struct Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics
{
	struct TODManager_eventSetMaterialVectorByName_Parms
	{
		FName ParameterName;
		FLinearColor Value;
		bool bSkyDome;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Material" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetMaterialVectorByName constinit property declarations ***************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ParameterName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
	static void NewProp_bSkyDome_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkyDome;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetMaterialVectorByName constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetMaterialVectorByName Property Definitions **************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_ParameterName = { "ParameterName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventSetMaterialVectorByName_Parms, ParameterName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventSetMaterialVectorByName_Parms, Value), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_bSkyDome_SetBit(void* Obj)
{
	((TODManager_eventSetMaterialVectorByName_Parms*)Obj)->bSkyDome = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_bSkyDome = { "bSkyDome", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TODManager_eventSetMaterialVectorByName_Parms), &Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_bSkyDome_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_ParameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::NewProp_bSkyDome,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::PropPointers) < 2048);
// ********** End Function SetMaterialVectorByName Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "SetMaterialVectorByName", 	Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::TODManager_eventSetMaterialVectorByName_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::TODManager_eventSetMaterialVectorByName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_SetMaterialVectorByName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_SetMaterialVectorByName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execSetMaterialVectorByName)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ParameterName);
	P_GET_STRUCT(FLinearColor,Z_Param_Value);
	P_GET_UBOOL(Z_Param_bSkyDome);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMaterialVectorByName(Z_Param_ParameterName,Z_Param_Value,Z_Param_bSkyDome);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function SetMaterialVectorByName *******************************

// ********** Begin Class ATODManager Function SetStartTime ****************************************
struct Z_Construct_UFunction_ATODManager_SetStartTime_Statics
{
	struct TODManager_eventSetStartTime_Parms
	{
		float NewTime;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetStartTime constinit property declarations **************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetStartTime constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetStartTime Property Definitions *************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_SetStartTime_Statics::NewProp_NewTime = { "NewTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventSetStartTime_Parms, NewTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_SetStartTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetStartTime_Statics::NewProp_NewTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetStartTime_Statics::PropPointers) < 2048);
// ********** End Function SetStartTime Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_SetStartTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "SetStartTime", 	Z_Construct_UFunction_ATODManager_SetStartTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetStartTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_SetStartTime_Statics::TODManager_eventSetStartTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetStartTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_SetStartTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_SetStartTime_Statics::TODManager_eventSetStartTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_SetStartTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_SetStartTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execSetStartTime)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetStartTime(Z_Param_NewTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function SetStartTime ******************************************

// ********** Begin Class ATODManager Function SetSunAzimuthOffset *********************************
struct Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics
{
	struct TODManager_eventSetSunAzimuthOffset_Parms
	{
		float InAzimuthOffset;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetSunAzimuthOffset constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InAzimuthOffset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetSunAzimuthOffset constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetSunAzimuthOffset Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::NewProp_InAzimuthOffset = { "InAzimuthOffset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventSetSunAzimuthOffset_Parms, InAzimuthOffset), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::NewProp_InAzimuthOffset,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::PropPointers) < 2048);
// ********** End Function SetSunAzimuthOffset Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "SetSunAzimuthOffset", 	Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::TODManager_eventSetSunAzimuthOffset_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::TODManager_eventSetSunAzimuthOffset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execSetSunAzimuthOffset)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InAzimuthOffset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetSunAzimuthOffset(Z_Param_InAzimuthOffset);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function SetSunAzimuthOffset ***********************************

// ********** Begin Class ATODManager Function ToggleTimeDirection *********************************
struct Z_Construct_UFunction_ATODManager_ToggleTimeDirection_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "Comment", "// 1: \xec\xa0\x95\xeb\xb0\xa9\xed\x96\xa5, -1: \xec\x97\xad\xeb\xb0\xa9\xed\x96\xa5\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "1: \xec\xa0\x95\xeb\xb0\xa9\xed\x96\xa5, -1: \xec\x97\xad\xeb\xb0\xa9\xed\x96\xa5" },
	};
#endif // WITH_METADATA

// ********** Begin Function ToggleTimeDirection constinit property declarations *******************
// ********** End Function ToggleTimeDirection constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_ToggleTimeDirection_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "ToggleTimeDirection", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_ToggleTimeDirection_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_ToggleTimeDirection_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_ToggleTimeDirection()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_ToggleTimeDirection_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execToggleTimeDirection)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleTimeDirection();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function ToggleTimeDirection ***********************************

// ********** Begin Class ATODManager Function ToggleTimePause *************************************
struct Z_Construct_UFunction_ATODManager_ToggleTimePause_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ToggleTimePause constinit property declarations ***********************
// ********** End Function ToggleTimePause constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_ToggleTimePause_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "ToggleTimePause", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_ToggleTimePause_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_ToggleTimePause_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_ToggleTimePause()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_ToggleTimePause_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execToggleTimePause)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleTimePause();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function ToggleTimePause ***************************************

// ********** Begin Class ATODManager Function UpdateMoonMeshTransform *****************************
struct Z_Construct_UFunction_ATODManager_UpdateMoonMeshTransform_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Moon" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateMoonMeshTransform constinit property declarations ***************
// ********** End Function UpdateMoonMeshTransform constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_UpdateMoonMeshTransform_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "UpdateMoonMeshTransform", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdateMoonMeshTransform_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_UpdateMoonMeshTransform_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_UpdateMoonMeshTransform()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_UpdateMoonMeshTransform_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execUpdateMoonMeshTransform)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateMoonMeshTransform();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function UpdateMoonMeshTransform *******************************

// ********** Begin Class ATODManager Function UpdatePivotRotation *********************************
struct Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics
{
	struct TODManager_eventUpdatePivotRotation_Parms
	{
		float InTime;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdatePivotRotation constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UpdatePivotRotation constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UpdatePivotRotation Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventUpdatePivotRotation_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::NewProp_InTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::PropPointers) < 2048);
// ********** End Function UpdatePivotRotation Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "UpdatePivotRotation", 	Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::TODManager_eventUpdatePivotRotation_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::TODManager_eventUpdatePivotRotation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_UpdatePivotRotation()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_UpdatePivotRotation_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execUpdatePivotRotation)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdatePivotRotation(Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function UpdatePivotRotation ***********************************

// ********** Begin Class ATODManager Function UpdateSkyAnchorPosition *****************************
struct Z_Construct_UFunction_ATODManager_UpdateSkyAnchorPosition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateSkyAnchorPosition constinit property declarations ***************
// ********** End Function UpdateSkyAnchorPosition constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_UpdateSkyAnchorPosition_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "UpdateSkyAnchorPosition", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdateSkyAnchorPosition_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_UpdateSkyAnchorPosition_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_UpdateSkyAnchorPosition()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_UpdateSkyAnchorPosition_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execUpdateSkyAnchorPosition)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateSkyAnchorPosition();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function UpdateSkyAnchorPosition *******************************

// ********** Begin Class ATODManager Function UpdateSunTimes **************************************
struct Z_Construct_UFunction_ATODManager_UpdateSunTimes_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Geography" },
		{ "Comment", "// =========================================================================\n// Functions: Geography\n// =========================================================================\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Functions: Geography" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateSunTimes constinit property declarations ************************
// ********** End Function UpdateSunTimes constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_UpdateSunTimes_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "UpdateSunTimes", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdateSunTimes_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_UpdateSunTimes_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATODManager_UpdateSunTimes()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_UpdateSunTimes_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execUpdateSunTimes)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateSunTimes();
	P_NATIVE_END;
}
// ********** End Class ATODManager Function UpdateSunTimes ****************************************

// ********** Begin Class ATODManager Function UpdateTOD *******************************************
struct Z_Construct_UFunction_ATODManager_UpdateTOD_Statics
{
	struct TODManager_eventUpdateTOD_Parms
	{
		float CurrentTime;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|System" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateTOD constinit property declarations *****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UpdateTOD constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UpdateTOD Property Definitions ****************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::NewProp_CurrentTime = { "CurrentTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODManager_eventUpdateTOD_Parms, CurrentTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::NewProp_CurrentTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::PropPointers) < 2048);
// ********** End Function UpdateTOD Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATODManager, nullptr, "UpdateTOD", 	Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::TODManager_eventUpdateTOD_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::TODManager_eventUpdateTOD_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATODManager_UpdateTOD()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATODManager_UpdateTOD_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATODManager::execUpdateTOD)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_CurrentTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateTOD(Z_Param_CurrentTime);
	P_NATIVE_END;
}
// ********** End Class ATODManager Function UpdateTOD *********************************************

// ********** Begin Class ATODManager **************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ATODManager;
UClass* ATODManager::GetPrivateStaticClass()
{
	using TClass = ATODManager;
	if (!Z_Registration_Info_UClass_ATODManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TODManager"),
			Z_Registration_Info_UClass_ATODManager.InnerSingleton,
			StaticRegisterNativesATODManager,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_ATODManager.InnerSingleton;
}
UClass* Z_Construct_UClass_ATODManager_NoRegister()
{
	return ATODManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATODManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "HideFunctions", "SetStartTime, SetTOD_State" },
		{ "IncludePath", "TODManager.h" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnTODDataChanged_MetaData[] = {
		{ "Category", "TOD|Events" },
		{ "Comment", "// =========================================================================\n// Events / Delegates\n// =========================================================================\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Events / Delegates" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetCinematics_MetaData[] = {
		{ "Category", "TOD|Sequencer" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RuntimePPVComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "TOD" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunLightComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonLightComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyLightComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyAtmosphereComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PivotOrbitTiltComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PivotSunMoonComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshPivotComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyDomeMesh_MetaData[] = {
		{ "Category", "TOD|Material" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonMesh_MetaData[] = {
		{ "Category", "TOD|Material" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonMaterialInstance_MetaData[] = {
		{ "Category", "TOD|Material" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonGlowMesh_MetaData[] = {
		{ "Category", "TOD|Material" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonGlowMaterialInstance_MetaData[] = {
		{ "Category", "TOD|Material" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyMaterialInstance_MetaData[] = {
		{ "Category", "TOD|Material" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartTimeDisplay_MetaData[] = {
		{ "Category", "TOD" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Read-only display of the configured start time." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartTime_MetaData[] = {
		{ "Category", "TOD" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "NonInterp", "" },
		{ "ToolTip", "Initial time of day when the game starts. 0-24" },
		{ "UIMax", "24.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TOD_DataArray_MetaData[] = {
		{ "Category", "TOD" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "TOD Data array containing all time-of-day settings." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TOD_State_MetaData[] = {
		{ "Category", "TOD|State Setting" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "NonInterp", "" },
		{ "TitleProperty", "State" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeDirection_MetaData[] = {
		{ "Category", "TOD|Time" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerRef_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "TOD|Speed" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Reference to the player character to track movement state." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveDaySpeed_MetaData[] = {
		{ "Category", "TOD|Speed" },
		{ "ClampMax", "50.0" },
		{ "ClampMin", "0.1" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Time multiplier when the player is moving." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IdleDaySpeed_MetaData[] = {
		{ "Category", "TOD|Speed" },
		{ "ClampMax", "50.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Time multiplier when the player is idle." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterpSpeed_MetaData[] = {
		{ "Category", "TOD|Speed" },
		{ "ClampMin", "0.01" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Interpolation speed. \nHigher values make the transition faster\nLower values make the transition smoother." },
		{ "UIMax", "10.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DayCycleDuration_MetaData[] = {
		{ "Category", "TOD|Speed" },
		{ "ClampMax", "360.0" },
		{ "ClampMin", "0.1" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Total duration of one full day cycle in minutes." },
		{ "Units", "min" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CycleSpeedCurve_MetaData[] = {
		{ "Category", "TOD|Speed" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "Custom curve to modulate speed over the 24-hour cycle." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionDuration_MetaData[] = {
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateBlendAlpha_MetaData[] = {
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Latitude_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ClampMax", "90.0" },
		{ "ClampMin", "-90.0" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Controls sunrise/sunset timing. Artistic setting, not physically accurate." },
		{ "UIMax", "60.0" },
		{ "UIMin", "-60.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Longitude_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ClampMax", "180.0" },
		{ "ClampMin", "-180.0" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Shifts local solar time relative to the reference meridian (longitude degrees == hour-angle degrees, matching the real solar-time offset). Rotates when solar noon occurs without changing sunrise/sunset duration." },
		{ "UIMax", "180.0" },
		{ "UIMin", "-180.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Season_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Sets the sun's declination (Spring/Fall = 0 deg, Summer = +23.45 deg, Winter = -23.45 deg), affecting sunrise/sunset times and sun altitude." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CalculatedSunriseTime_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CalculatedSunsetTime_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunriseTime_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Calculated sunrise time based on the current latitude setting." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunsetTime_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Calculated sunset time based on the current latitude setting." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunAzimuthOffset_MetaData[] = {
		{ "Category", "TOD|Geography" },
		{ "ClampMax", "360.0" },
		{ "ClampMin", "-360.0" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "Tooltip", "\xed\x83\x9c\xec\x96\x91/\xeb\x8b\xac\xec\x9d\xb4 \xeb\x96\xa0\xec\x98\xa4\xeb\xa5\xb4\xeb\x8a\x94 \xeb\xb0\xa9\xec\x9c\x84\xea\xb0\x81(Yaw)\xec\x9e\x85\xeb\x8b\x88\xeb\x8b\xa4. 0\xeb\x8f\x84\xec\x9d\xbc \xeb\x95\x8c \xea\xb8\xb0\xeb\xb3\xb8 \xeb\x8f\x99\xec\xaa\xbd\xec\x97\x90\xec\x84\x9c \xeb\x96\xa0\xec\x98\xa4\xeb\xa6\x85\xeb\x8b\x88\xeb\x8b\xa4. \xeb\xac\xbc\xeb\xa6\xac \xea\xb3\x84\xec\x82\xb0\xea\xb3\xbc \xeb\xac\xb4\xea\xb4\x80\xed\x95\x9c \xec\x95\x84\xed\x8b\xb0\xec\x8a\xa4\xed\x8b\xb1 \xea\xb0\x92\xec\x9e\x85\xeb\x8b\x88\xeb\x8b\xa4." },
		{ "UIMax", "180.0" },
		{ "UIMin", "-180.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonDistance_MetaData[] = {
		{ "Category", "TOD|Moon" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Reference mesh radius distance for Moon." },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoScaleMoonDistanceByMeshSize_MetaData[] = {
		{ "Category", "TOD|Moon" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Auto-scale MoonDistance based on Moon Mesh bounding size." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonMeshReferenceRadius_MetaData[] = {
		{ "Category", "TOD|Moon" },
		{ "ClampMin", "1.0" },
		{ "EditCondition", "bAutoScaleMoonDistanceByMeshSize" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Reference mesh radius (uu) that MoonDistance corresponds to." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurveData_MetaData[] = {
		{ "Category", "TOD_Curves" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOverrideMoonSourceScale_MetaData[] = {
		{ "Category", "TOD|Texture" },
		{ "Comment", "// =========================================================================\n// Properties: Visual Overrides\n// =========================================================================\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Properties: Visual Overrides" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverriddenMoonSourceScale_MetaData[] = {
		{ "Category", "TOD|Texture" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "UIMax", "10.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PPV_ExposureCompensationCurve_MetaData[] = {
		{ "Category", "TOD|PPV Compensation" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Time-of-day exposure compensation. Added to the blended PPV's AutoExposureBias." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PPV_BrightnessCompensationCurve_MetaData[] = {
		{ "Category", "TOD|PPV Compensation" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Time-of-day brightness compensation. Applied as a multiplier to the blended PPV's BloomIntensity." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PPV_WhiteTempCompensationCurve_MetaData[] = {
		{ "Category", "TOD|PPV Compensation" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Time-of-day color temperature compensation (Kelvin). Added to the blended PPV's WhiteTemp." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PPV_ColorGradingCompensationCurve_MetaData[] = {
		{ "Category", "TOD|PPV Compensation" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Time-of-day color grading compensation. Applied as an RGBA multiplier to the blended PPV's ColorSaturation." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoadPreset_MetaData[] = {
		{ "Category", "TOD|Preset" },
		{ "Comment", "// =========================================================================\n// Properties: Preset\n// =========================================================================\n" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Properties: Preset" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableDebugPrint_MetaData[] = {
		{ "Category", "TOD|Debug" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Enables on-screen debug information for the TOD system." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DebugPrintInterval_MetaData[] = {
		{ "Category", "TOD|Debug" },
		{ "ClampMin", "0.1" },
		{ "EditCondition", "bEnableDebugPrint" },
		{ "ModuleRelativePath", "Public/TODManager.h" },
		{ "ToolTip", "Interval in seconds between debug updates." },
		{ "UIMin", "0.1" },
	};
#endif // WITH_METADATA

// ********** Begin Class ATODManager constinit property declarations ******************************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTODDataChanged;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetCinematics_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TargetCinematics;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RuntimePPVComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SunLightComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoonLightComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkyLightComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FogComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkyAtmosphereComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PivotOrbitTiltComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PivotSunMoonComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshPivotComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkyDomeMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoonMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoonMaterialInstance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoonGlowMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoonGlowMaterialInstance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkyMaterialInstance;
	static const UECodeGen_Private::FStrPropertyParams NewProp_StartTimeDisplay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StartTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TOD_DataArray_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TOD_DataArray;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TOD_State_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TOD_State;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeDirection;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerRef;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ActiveDaySpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_IdleDaySpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InterpSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DayCycleDuration;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CycleSpeedCurve;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TransitionDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StateBlendAlpha;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Latitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Longitude;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Season_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Season;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CalculatedSunriseTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CalculatedSunsetTime;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SunriseTime;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SunsetTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SunAzimuthOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoonDistance;
	static void NewProp_bAutoScaleMoonDistanceByMeshSize_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoScaleMoonDistanceByMeshSize;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoonMeshReferenceRadius;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurveData;
	static void NewProp_bOverrideMoonSourceScale_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverrideMoonSourceScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OverriddenMoonSourceScale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PPV_ExposureCompensationCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PPV_BrightnessCompensationCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PPV_WhiteTempCompensationCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PPV_ColorGradingCompensationCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LoadPreset;
	static void NewProp_bEnableDebugPrint_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableDebugPrint;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DebugPrintInterval;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ATODManager constinit property declarations ********************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("BakeTODCurves"), .Pointer = &ATODManager::execBakeTODCurves },
		{ .NameUTF8 = UTF8TEXT("CalculateCycleSpeed"), .Pointer = &ATODManager::execCalculateCycleSpeed },
		{ .NameUTF8 = UTF8TEXT("CalculatePivotRotation"), .Pointer = &ATODManager::execCalculatePivotRotation },
		{ .NameUTF8 = UTF8TEXT("EvaluateCinematicState"), .Pointer = &ATODManager::execEvaluateCinematicState },
		{ .NameUTF8 = UTF8TEXT("FindComponents"), .Pointer = &ATODManager::execFindComponents },
		{ .NameUTF8 = UTF8TEXT("ForceViewportRedraw"), .Pointer = &ATODManager::execForceViewportRedraw },
		{ .NameUTF8 = UTF8TEXT("GetCalculatedMoonScale"), .Pointer = &ATODManager::execGetCalculatedMoonScale },
		{ .NameUTF8 = UTF8TEXT("GetCurrentTime"), .Pointer = &ATODManager::execGetCurrentTime },
		{ .NameUTF8 = UTF8TEXT("GetCurrentTODState"), .Pointer = &ATODManager::execGetCurrentTODState },
		{ .NameUTF8 = UTF8TEXT("GetFinalSpeed"), .Pointer = &ATODManager::execGetFinalSpeed },
		{ .NameUTF8 = UTF8TEXT("GetFormattedTimeAsString"), .Pointer = &ATODManager::execGetFormattedTimeAsString },
		{ .NameUTF8 = UTF8TEXT("GetMoonGlowScaleAtTime"), .Pointer = &ATODManager::execGetMoonGlowScaleAtTime },
		{ .NameUTF8 = UTF8TEXT("GetMoonIntensity"), .Pointer = &ATODManager::execGetMoonIntensity },
		{ .NameUTF8 = UTF8TEXT("GetMoonSourceScaleAtTime"), .Pointer = &ATODManager::execGetMoonSourceScaleAtTime },
		{ .NameUTF8 = UTF8TEXT("GetStartTime"), .Pointer = &ATODManager::execGetStartTime },
		{ .NameUTF8 = UTF8TEXT("GetSunIntensity"), .Pointer = &ATODManager::execGetSunIntensity },
		{ .NameUTF8 = UTF8TEXT("IsTimeInState"), .Pointer = &ATODManager::execIsTimeInState },
		{ .NameUTF8 = UTF8TEXT("LoadSelectedPreset"), .Pointer = &ATODManager::execLoadSelectedPreset },
		{ .NameUTF8 = UTF8TEXT("OpenPresetDialog"), .Pointer = &ATODManager::execOpenPresetDialog },
		{ .NameUTF8 = UTF8TEXT("PrintTODDebugInfo"), .Pointer = &ATODManager::execPrintTODDebugInfo },
		{ .NameUTF8 = UTF8TEXT("SaveCurrentPreset"), .Pointer = &ATODManager::execSaveCurrentPreset },
		{ .NameUTF8 = UTF8TEXT("SaveNewPreset"), .Pointer = &ATODManager::execSaveNewPreset },
		{ .NameUTF8 = UTF8TEXT("SetCurrentTime"), .Pointer = &ATODManager::execSetCurrentTime },
		{ .NameUTF8 = UTF8TEXT("SetMaterialScalarByName"), .Pointer = &ATODManager::execSetMaterialScalarByName },
		{ .NameUTF8 = UTF8TEXT("SetMaterialVectorByName"), .Pointer = &ATODManager::execSetMaterialVectorByName },
		{ .NameUTF8 = UTF8TEXT("SetStartTime"), .Pointer = &ATODManager::execSetStartTime },
		{ .NameUTF8 = UTF8TEXT("SetSunAzimuthOffset"), .Pointer = &ATODManager::execSetSunAzimuthOffset },
		{ .NameUTF8 = UTF8TEXT("ToggleTimeDirection"), .Pointer = &ATODManager::execToggleTimeDirection },
		{ .NameUTF8 = UTF8TEXT("ToggleTimePause"), .Pointer = &ATODManager::execToggleTimePause },
		{ .NameUTF8 = UTF8TEXT("UpdateMoonMeshTransform"), .Pointer = &ATODManager::execUpdateMoonMeshTransform },
		{ .NameUTF8 = UTF8TEXT("UpdatePivotRotation"), .Pointer = &ATODManager::execUpdatePivotRotation },
		{ .NameUTF8 = UTF8TEXT("UpdateSkyAnchorPosition"), .Pointer = &ATODManager::execUpdateSkyAnchorPosition },
		{ .NameUTF8 = UTF8TEXT("UpdateSunTimes"), .Pointer = &ATODManager::execUpdateSunTimes },
		{ .NameUTF8 = UTF8TEXT("UpdateTOD"), .Pointer = &ATODManager::execUpdateTOD },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ATODManager_BakeTODCurves, "BakeTODCurves" }, // 2861635991
		{ &Z_Construct_UFunction_ATODManager_CalculateCycleSpeed, "CalculateCycleSpeed" }, // 3391508547
		{ &Z_Construct_UFunction_ATODManager_CalculatePivotRotation, "CalculatePivotRotation" }, // 2861658708
		{ &Z_Construct_UFunction_ATODManager_EvaluateCinematicState, "EvaluateCinematicState" }, // 2988512050
		{ &Z_Construct_UFunction_ATODManager_FindComponents, "FindComponents" }, // 1145738159
		{ &Z_Construct_UFunction_ATODManager_ForceViewportRedraw, "ForceViewportRedraw" }, // 1059176239
		{ &Z_Construct_UFunction_ATODManager_GetCalculatedMoonScale, "GetCalculatedMoonScale" }, // 1850207794
		{ &Z_Construct_UFunction_ATODManager_GetCurrentTime, "GetCurrentTime" }, // 2657729296
		{ &Z_Construct_UFunction_ATODManager_GetCurrentTODState, "GetCurrentTODState" }, // 2978199089
		{ &Z_Construct_UFunction_ATODManager_GetFinalSpeed, "GetFinalSpeed" }, // 3744602356
		{ &Z_Construct_UFunction_ATODManager_GetFormattedTimeAsString, "GetFormattedTimeAsString" }, // 1742728493
		{ &Z_Construct_UFunction_ATODManager_GetMoonGlowScaleAtTime, "GetMoonGlowScaleAtTime" }, // 1499360453
		{ &Z_Construct_UFunction_ATODManager_GetMoonIntensity, "GetMoonIntensity" }, // 3770409508
		{ &Z_Construct_UFunction_ATODManager_GetMoonSourceScaleAtTime, "GetMoonSourceScaleAtTime" }, // 2135344243
		{ &Z_Construct_UFunction_ATODManager_GetStartTime, "GetStartTime" }, // 4000393215
		{ &Z_Construct_UFunction_ATODManager_GetSunIntensity, "GetSunIntensity" }, // 4236272847
		{ &Z_Construct_UFunction_ATODManager_IsTimeInState, "IsTimeInState" }, // 1731332411
		{ &Z_Construct_UFunction_ATODManager_LoadSelectedPreset, "LoadSelectedPreset" }, // 2740389330
		{ &Z_Construct_UFunction_ATODManager_OnUpdateCustomMaterials, "OnUpdateCustomMaterials" }, // 1651539987
		{ &Z_Construct_UFunction_ATODManager_OpenPresetDialog, "OpenPresetDialog" }, // 2715748180
		{ &Z_Construct_UFunction_ATODManager_PrintTODDebugInfo, "PrintTODDebugInfo" }, // 2266440636
		{ &Z_Construct_UFunction_ATODManager_SaveCurrentPreset, "SaveCurrentPreset" }, // 1477691773
		{ &Z_Construct_UFunction_ATODManager_SaveNewPreset, "SaveNewPreset" }, // 3895784246
		{ &Z_Construct_UFunction_ATODManager_SetCurrentTime, "SetCurrentTime" }, // 3780072989
		{ &Z_Construct_UFunction_ATODManager_SetMaterialScalarByName, "SetMaterialScalarByName" }, // 395030031
		{ &Z_Construct_UFunction_ATODManager_SetMaterialVectorByName, "SetMaterialVectorByName" }, // 1346704532
		{ &Z_Construct_UFunction_ATODManager_SetStartTime, "SetStartTime" }, // 296038344
		{ &Z_Construct_UFunction_ATODManager_SetSunAzimuthOffset, "SetSunAzimuthOffset" }, // 1094141433
		{ &Z_Construct_UFunction_ATODManager_ToggleTimeDirection, "ToggleTimeDirection" }, // 3658701270
		{ &Z_Construct_UFunction_ATODManager_ToggleTimePause, "ToggleTimePause" }, // 3309869841
		{ &Z_Construct_UFunction_ATODManager_UpdateMoonMeshTransform, "UpdateMoonMeshTransform" }, // 3469328852
		{ &Z_Construct_UFunction_ATODManager_UpdatePivotRotation, "UpdatePivotRotation" }, // 3999286077
		{ &Z_Construct_UFunction_ATODManager_UpdateSkyAnchorPosition, "UpdateSkyAnchorPosition" }, // 2689230197
		{ &Z_Construct_UFunction_ATODManager_UpdateSunTimes, "UpdateSunTimes" }, // 52231678
		{ &Z_Construct_UFunction_ATODManager_UpdateTOD, "UpdateTOD" }, // 4202388907
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATODManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ATODManager_Statics

// ********** Begin Class ATODManager Property Definitions *****************************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_OnTODDataChanged = { "OnTODDataChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, OnTODDataChanged), Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnTODDataChanged_MetaData), NewProp_OnTODDataChanged_MetaData) }; // 263358711
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TargetCinematics_Inner = { "TargetCinematics", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTODCinematicSetting, METADATA_PARAMS(0, nullptr) }; // 3645121645
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TargetCinematics = { "TargetCinematics", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, TargetCinematics), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetCinematics_MetaData), NewProp_TargetCinematics_MetaData) }; // 3645121645
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_RuntimePPVComponent = { "RuntimePPVComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, RuntimePPVComponent), Z_Construct_UClass_UPostProcessComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RuntimePPVComponent_MetaData), NewProp_RuntimePPVComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SunLightComponent = { "SunLightComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SunLightComponent), Z_Construct_UClass_UDirectionalLightComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunLightComponent_MetaData), NewProp_SunLightComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MoonLightComponent = { "MoonLightComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MoonLightComponent), Z_Construct_UClass_UDirectionalLightComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonLightComponent_MetaData), NewProp_MoonLightComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SkyLightComponent = { "SkyLightComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SkyLightComponent), Z_Construct_UClass_USkyLightComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyLightComponent_MetaData), NewProp_SkyLightComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_FogComponent = { "FogComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, FogComponent), Z_Construct_UClass_UExponentialHeightFogComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogComponent_MetaData), NewProp_FogComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SkyAtmosphereComponent = { "SkyAtmosphereComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SkyAtmosphereComponent), Z_Construct_UClass_USkyAtmosphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyAtmosphereComponent_MetaData), NewProp_SkyAtmosphereComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_PivotOrbitTiltComponent = { "PivotOrbitTiltComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, PivotOrbitTiltComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PivotOrbitTiltComponent_MetaData), NewProp_PivotOrbitTiltComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_PivotSunMoonComponent = { "PivotSunMoonComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, PivotSunMoonComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PivotSunMoonComponent_MetaData), NewProp_PivotSunMoonComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MeshPivotComponent = { "MeshPivotComponent", nullptr, (EPropertyFlags)0x0114000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MeshPivotComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshPivotComponent_MetaData), NewProp_MeshPivotComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SkyDomeMesh = { "SkyDomeMesh", nullptr, (EPropertyFlags)0x011400000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SkyDomeMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyDomeMesh_MetaData), NewProp_SkyDomeMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MoonMesh = { "MoonMesh", nullptr, (EPropertyFlags)0x011400000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MoonMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonMesh_MetaData), NewProp_MoonMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MoonMaterialInstance = { "MoonMaterialInstance", nullptr, (EPropertyFlags)0x0114000000000004, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MoonMaterialInstance), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonMaterialInstance_MetaData), NewProp_MoonMaterialInstance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MoonGlowMesh = { "MoonGlowMesh", nullptr, (EPropertyFlags)0x011400000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MoonGlowMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonGlowMesh_MetaData), NewProp_MoonGlowMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MoonGlowMaterialInstance = { "MoonGlowMaterialInstance", nullptr, (EPropertyFlags)0x0114000000000004, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MoonGlowMaterialInstance), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonGlowMaterialInstance_MetaData), NewProp_MoonGlowMaterialInstance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SkyMaterialInstance = { "SkyMaterialInstance", nullptr, (EPropertyFlags)0x0114000000000004, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SkyMaterialInstance), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyMaterialInstance_MetaData), NewProp_SkyMaterialInstance_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_StartTimeDisplay = { "StartTimeDisplay", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, StartTimeDisplay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartTimeDisplay_MetaData), NewProp_StartTimeDisplay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_StartTime = { "StartTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, StartTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartTime_MetaData), NewProp_StartTime_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_DataArray_Inner = { "TOD_DataArray", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTODMasterData, METADATA_PARAMS(0, nullptr) }; // 872119232
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_DataArray = { "TOD_DataArray", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, TOD_DataArray), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TOD_DataArray_MetaData), NewProp_TOD_DataArray_MetaData) }; // 872119232
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_State_Inner = { "TOD_State", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTODTimePoint, METADATA_PARAMS(0, nullptr) }; // 1611771925
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_State = { "TOD_State", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, TOD_State), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TOD_State_MetaData), NewProp_TOD_State_MetaData) }; // 1611771925
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TimeDirection = { "TimeDirection", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, TimeDirection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeDirection_MetaData), NewProp_TimeDirection_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_PlayerRef = { "PlayerRef", nullptr, (EPropertyFlags)0x0124080000000004, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, PlayerRef), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerRef_MetaData), NewProp_PlayerRef_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_ActiveDaySpeed = { "ActiveDaySpeed", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, ActiveDaySpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveDaySpeed_MetaData), NewProp_ActiveDaySpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_IdleDaySpeed = { "IdleDaySpeed", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, IdleDaySpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IdleDaySpeed_MetaData), NewProp_IdleDaySpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_InterpSpeed = { "InterpSpeed", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, InterpSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterpSpeed_MetaData), NewProp_InterpSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_DayCycleDuration = { "DayCycleDuration", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, DayCycleDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DayCycleDuration_MetaData), NewProp_DayCycleDuration_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_CycleSpeedCurve = { "CycleSpeedCurve", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, CycleSpeedCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CycleSpeedCurve_MetaData), NewProp_CycleSpeedCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_TransitionDuration = { "TransitionDuration", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, TransitionDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionDuration_MetaData), NewProp_TransitionDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_StateBlendAlpha = { "StateBlendAlpha", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, StateBlendAlpha), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateBlendAlpha_MetaData), NewProp_StateBlendAlpha_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_Latitude = { "Latitude", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, Latitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Latitude_MetaData), NewProp_Latitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_Longitude = { "Longitude", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, Longitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Longitude_MetaData), NewProp_Longitude_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_Season_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_Season = { "Season", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, Season), Z_Construct_UEnum_Fluid_TOD_ETODSeason, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Season_MetaData), NewProp_Season_MetaData) }; // 3176123401
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_CalculatedSunriseTime = { "CalculatedSunriseTime", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, CalculatedSunriseTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CalculatedSunriseTime_MetaData), NewProp_CalculatedSunriseTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_CalculatedSunsetTime = { "CalculatedSunsetTime", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, CalculatedSunsetTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CalculatedSunsetTime_MetaData), NewProp_CalculatedSunsetTime_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SunriseTime = { "SunriseTime", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SunriseTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunriseTime_MetaData), NewProp_SunriseTime_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SunsetTime = { "SunsetTime", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SunsetTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunsetTime_MetaData), NewProp_SunsetTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_SunAzimuthOffset = { "SunAzimuthOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, SunAzimuthOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunAzimuthOffset_MetaData), NewProp_SunAzimuthOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MoonDistance = { "MoonDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MoonDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonDistance_MetaData), NewProp_MoonDistance_MetaData) };
void Z_Construct_UClass_ATODManager_Statics::NewProp_bAutoScaleMoonDistanceByMeshSize_SetBit(void* Obj)
{
	((ATODManager*)Obj)->bAutoScaleMoonDistanceByMeshSize = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_bAutoScaleMoonDistanceByMeshSize = { "bAutoScaleMoonDistanceByMeshSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ATODManager), &Z_Construct_UClass_ATODManager_Statics::NewProp_bAutoScaleMoonDistanceByMeshSize_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoScaleMoonDistanceByMeshSize_MetaData), NewProp_bAutoScaleMoonDistanceByMeshSize_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_MoonMeshReferenceRadius = { "MoonMeshReferenceRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, MoonMeshReferenceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonMeshReferenceRadius_MetaData), NewProp_MoonMeshReferenceRadius_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_CurveData = { "CurveData", nullptr, (EPropertyFlags)0x01160000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, CurveData), Z_Construct_UClass_UTODCurveContainer_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurveData_MetaData), NewProp_CurveData_MetaData) };
void Z_Construct_UClass_ATODManager_Statics::NewProp_bOverrideMoonSourceScale_SetBit(void* Obj)
{
	((ATODManager*)Obj)->bOverrideMoonSourceScale = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_bOverrideMoonSourceScale = { "bOverrideMoonSourceScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ATODManager), &Z_Construct_UClass_ATODManager_Statics::NewProp_bOverrideMoonSourceScale_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOverrideMoonSourceScale_MetaData), NewProp_bOverrideMoonSourceScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_OverriddenMoonSourceScale = { "OverriddenMoonSourceScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, OverriddenMoonSourceScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverriddenMoonSourceScale_MetaData), NewProp_OverriddenMoonSourceScale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_ExposureCompensationCurve = { "PPV_ExposureCompensationCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, PPV_ExposureCompensationCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PPV_ExposureCompensationCurve_MetaData), NewProp_PPV_ExposureCompensationCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_BrightnessCompensationCurve = { "PPV_BrightnessCompensationCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, PPV_BrightnessCompensationCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PPV_BrightnessCompensationCurve_MetaData), NewProp_PPV_BrightnessCompensationCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_WhiteTempCompensationCurve = { "PPV_WhiteTempCompensationCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, PPV_WhiteTempCompensationCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PPV_WhiteTempCompensationCurve_MetaData), NewProp_PPV_WhiteTempCompensationCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_ColorGradingCompensationCurve = { "PPV_ColorGradingCompensationCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, PPV_ColorGradingCompensationCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PPV_ColorGradingCompensationCurve_MetaData), NewProp_PPV_ColorGradingCompensationCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_LoadPreset = { "LoadPreset", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, LoadPreset), Z_Construct_UClass_UTODPresetData_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoadPreset_MetaData), NewProp_LoadPreset_MetaData) };
void Z_Construct_UClass_ATODManager_Statics::NewProp_bEnableDebugPrint_SetBit(void* Obj)
{
	((ATODManager*)Obj)->bEnableDebugPrint = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_bEnableDebugPrint = { "bEnableDebugPrint", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ATODManager), &Z_Construct_UClass_ATODManager_Statics::NewProp_bEnableDebugPrint_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableDebugPrint_MetaData), NewProp_bEnableDebugPrint_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATODManager_Statics::NewProp_DebugPrintInterval = { "DebugPrintInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATODManager, DebugPrintInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DebugPrintInterval_MetaData), NewProp_DebugPrintInterval_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATODManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_OnTODDataChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TargetCinematics_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TargetCinematics,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_RuntimePPVComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SunLightComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MoonLightComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SkyLightComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_FogComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SkyAtmosphereComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_PivotOrbitTiltComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_PivotSunMoonComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MeshPivotComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SkyDomeMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MoonMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MoonMaterialInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MoonGlowMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MoonGlowMaterialInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SkyMaterialInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_StartTimeDisplay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_StartTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_DataArray_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_DataArray,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_State_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TOD_State,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TimeDirection,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_PlayerRef,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_ActiveDaySpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_IdleDaySpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_InterpSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_DayCycleDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_CycleSpeedCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_TransitionDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_StateBlendAlpha,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_Latitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_Longitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_Season_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_Season,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_CalculatedSunriseTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_CalculatedSunsetTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SunriseTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SunsetTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_SunAzimuthOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MoonDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_bAutoScaleMoonDistanceByMeshSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_MoonMeshReferenceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_CurveData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_bOverrideMoonSourceScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_OverriddenMoonSourceScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_ExposureCompensationCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_BrightnessCompensationCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_WhiteTempCompensationCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_PPV_ColorGradingCompensationCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_LoadPreset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_bEnableDebugPrint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATODManager_Statics::NewProp_DebugPrintInterval,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATODManager_Statics::PropPointers) < 2048);
// ********** End Class ATODManager Property Definitions *******************************************
UObject* (*const Z_Construct_UClass_ATODManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATODManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATODManager_Statics::ClassParams = {
	&ATODManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ATODManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ATODManager_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATODManager_Statics::Class_MetaDataParams), Z_Construct_UClass_ATODManager_Statics::Class_MetaDataParams)
};
void ATODManager::StaticRegisterNativesATODManager()
{
	UClass* Class = ATODManager::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ATODManager_Statics::Funcs));
}
UClass* Z_Construct_UClass_ATODManager()
{
	if (!Z_Registration_Info_UClass_ATODManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATODManager.OuterSingleton, Z_Construct_UClass_ATODManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATODManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ATODManager);
ATODManager::~ATODManager() {}
// ********** End Class ATODManager ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Release_Fluid_TOD_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h__Script_Fluid_TOD_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTODCinematicSetting::StaticStruct, Z_Construct_UScriptStruct_FTODCinematicSetting_Statics::NewStructOps, TEXT("TODCinematicSetting"),&Z_Registration_Info_UScriptStruct_FTODCinematicSetting, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODCinematicSetting), 3645121645U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATODManager, ATODManager::StaticClass, TEXT("ATODManager"), &Z_Registration_Info_UClass_ATODManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATODManager), 561579519U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Release_Fluid_TOD_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h__Script_Fluid_TOD_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Release_Fluid_TOD_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h__Script_Fluid_TOD_1549058658{
	TEXT("/Script/Fluid_TOD"),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Release_Fluid_TOD_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h__Script_Fluid_TOD_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Release_Fluid_TOD_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h__Script_Fluid_TOD_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Release_Fluid_TOD_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h__Script_Fluid_TOD_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Release_Fluid_TOD_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODManager_h__Script_Fluid_TOD_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
