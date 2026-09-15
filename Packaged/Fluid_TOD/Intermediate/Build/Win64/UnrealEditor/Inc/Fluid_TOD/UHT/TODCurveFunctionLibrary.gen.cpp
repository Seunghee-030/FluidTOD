// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TODCurveFunctionLibrary.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTODCurveFunctionLibrary() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UEnum* Z_Construct_UEnum_Engine_ERichCurveInterpMode();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeCurveLinearColor();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODCurveFunctionLibrary();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODCurveFunctionLibrary_NoRegister();
UPackage* Z_Construct_UPackage__Script_Fluid_TOD();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UTODCurveFunctionLibrary Function AddKeyToRuntimeColorCurve **************
struct Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics
{
	struct TODCurveFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms
	{
		FRuntimeCurveLinearColor InCurve;
		float InTime;
		FLinearColor InColor;
		TEnumAsByte<ERichCurveInterpMode> InterpMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "CPP_Default_InterpMode", "RCIM_Linear" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddKeyToRuntimeColorCurve constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InColor;
	static const UECodeGen_Private::FBytePropertyParams NewProp_InterpMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddKeyToRuntimeColorCurve constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddKeyToRuntimeColorCurve Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(0, nullptr) }; // 3548222332
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InColor = { "InColor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InterpMode = { "InterpMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InterpMode), Z_Construct_UEnum_Engine_ERichCurveInterpMode, METADATA_PARAMS(0, nullptr) }; // 3137508823
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InterpMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers) < 2048);
// ********** End Function AddKeyToRuntimeColorCurve Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTODCurveFunctionLibrary, nullptr, "AddKeyToRuntimeColorCurve", 	Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::TODCurveFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::TODCurveFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTODCurveFunctionLibrary::execAddKeyToRuntimeColorCurve)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_GET_STRUCT(FLinearColor,Z_Param_InColor);
	P_GET_PROPERTY(FByteProperty,Z_Param_InterpMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	UTODCurveFunctionLibrary::AddKeyToRuntimeColorCurve(Z_Param_Out_InCurve,Z_Param_InTime,Z_Param_InColor,ERichCurveInterpMode(Z_Param_InterpMode));
	P_NATIVE_END;
}
// ********** End Class UTODCurveFunctionLibrary Function AddKeyToRuntimeColorCurve ****************

// ********** Begin Class UTODCurveFunctionLibrary Function AddKeyToRuntimeFloatCurve **************
struct Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics
{
	struct TODCurveFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms
	{
		FRuntimeFloatCurve InCurve;
		float InTime;
		float InValue;
		TEnumAsByte<ERichCurveInterpMode> InterpMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "CPP_Default_InterpMode", "RCIM_Linear" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AddKeyToRuntimeFloatCurve constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InValue;
	static const UECodeGen_Private::FBytePropertyParams NewProp_InterpMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AddKeyToRuntimeFloatCurve constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AddKeyToRuntimeFloatCurve Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(0, nullptr) }; // 2560417949
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InterpMode = { "InterpMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InterpMode), Z_Construct_UEnum_Engine_ERichCurveInterpMode, METADATA_PARAMS(0, nullptr) }; // 3137508823
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InterpMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers) < 2048);
// ********** End Function AddKeyToRuntimeFloatCurve Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTODCurveFunctionLibrary, nullptr, "AddKeyToRuntimeFloatCurve", 	Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::TODCurveFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::TODCurveFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTODCurveFunctionLibrary::execAddKeyToRuntimeFloatCurve)
{
	P_GET_STRUCT_REF(FRuntimeFloatCurve,Z_Param_Out_InCurve);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InValue);
	P_GET_PROPERTY(FByteProperty,Z_Param_InterpMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	UTODCurveFunctionLibrary::AddKeyToRuntimeFloatCurve(Z_Param_Out_InCurve,Z_Param_InTime,Z_Param_InValue,ERichCurveInterpMode(Z_Param_InterpMode));
	P_NATIVE_END;
}
// ********** End Class UTODCurveFunctionLibrary Function AddKeyToRuntimeFloatCurve ****************

// ********** Begin Class UTODCurveFunctionLibrary Function ClearRuntimeColorCurve *****************
struct Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics
{
	struct TODCurveFunctionLibrary_eventClearRuntimeColorCurve_Parms
	{
		FRuntimeCurveLinearColor InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClearRuntimeColorCurve constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClearRuntimeColorCurve constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClearRuntimeColorCurve Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventClearRuntimeColorCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(0, nullptr) }; // 3548222332
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers) < 2048);
// ********** End Function ClearRuntimeColorCurve Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTODCurveFunctionLibrary, nullptr, "ClearRuntimeColorCurve", 	Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::TODCurveFunctionLibrary_eventClearRuntimeColorCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::TODCurveFunctionLibrary_eventClearRuntimeColorCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTODCurveFunctionLibrary::execClearRuntimeColorCurve)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UTODCurveFunctionLibrary::ClearRuntimeColorCurve(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UTODCurveFunctionLibrary Function ClearRuntimeColorCurve *******************

// ********** Begin Class UTODCurveFunctionLibrary Function ClearRuntimeFloatCurve *****************
struct Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics
{
	struct TODCurveFunctionLibrary_eventClearRuntimeFloatCurve_Parms
	{
		FRuntimeFloatCurve InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "Comment", "// Curve Control\n" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
		{ "ToolTip", "Curve Control" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClearRuntimeFloatCurve constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClearRuntimeFloatCurve constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClearRuntimeFloatCurve Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventClearRuntimeFloatCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(0, nullptr) }; // 2560417949
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers) < 2048);
// ********** End Function ClearRuntimeFloatCurve Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTODCurveFunctionLibrary, nullptr, "ClearRuntimeFloatCurve", 	Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::TODCurveFunctionLibrary_eventClearRuntimeFloatCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::TODCurveFunctionLibrary_eventClearRuntimeFloatCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTODCurveFunctionLibrary::execClearRuntimeFloatCurve)
{
	P_GET_STRUCT_REF(FRuntimeFloatCurve,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UTODCurveFunctionLibrary::ClearRuntimeFloatCurve(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UTODCurveFunctionLibrary Function ClearRuntimeFloatCurve *******************

// ********** Begin Class UTODCurveFunctionLibrary Function GetRuntimeColorCurveValue **************
struct Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics
{
	struct TODCurveFunctionLibrary_eventGetRuntimeColorCurveValue_Parms
	{
		FRuntimeCurveLinearColor InCurve;
		float InTime;
		FLinearColor ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InCurve_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRuntimeColorCurveValue constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRuntimeColorCurveValue constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRuntimeColorCurveValue Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventGetRuntimeColorCurveValue_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InCurve_MetaData), NewProp_InCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventGetRuntimeColorCurveValue_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventGetRuntimeColorCurveValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers) < 2048);
// ********** End Function GetRuntimeColorCurveValue Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTODCurveFunctionLibrary, nullptr, "GetRuntimeColorCurveValue", 	Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::TODCurveFunctionLibrary_eventGetRuntimeColorCurveValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::TODCurveFunctionLibrary_eventGetRuntimeColorCurveValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTODCurveFunctionLibrary::execGetRuntimeColorCurveValue)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FLinearColor*)Z_Param__Result=UTODCurveFunctionLibrary::GetRuntimeColorCurveValue(Z_Param_Out_InCurve,Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class UTODCurveFunctionLibrary Function GetRuntimeColorCurveValue ****************

// ********** Begin Class UTODCurveFunctionLibrary Function SealColorCurveFor24Hours ***************
struct Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics
{
	struct TODCurveFunctionLibrary_eventSealColorCurveFor24Hours_Parms
	{
		FRuntimeCurveLinearColor InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SealColorCurveFor24Hours constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SealColorCurveFor24Hours constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SealColorCurveFor24Hours Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventSealColorCurveFor24Hours_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(0, nullptr) }; // 3548222332
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers) < 2048);
// ********** End Function SealColorCurveFor24Hours Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTODCurveFunctionLibrary, nullptr, "SealColorCurveFor24Hours", 	Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::TODCurveFunctionLibrary_eventSealColorCurveFor24Hours_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::TODCurveFunctionLibrary_eventSealColorCurveFor24Hours_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTODCurveFunctionLibrary::execSealColorCurveFor24Hours)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UTODCurveFunctionLibrary::SealColorCurveFor24Hours(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UTODCurveFunctionLibrary Function SealColorCurveFor24Hours *****************

// ********** Begin Class UTODCurveFunctionLibrary Function SealTODCurveFor24Hours *****************
struct Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics
{
	struct TODCurveFunctionLibrary_eventSealTODCurveFor24Hours_Parms
	{
		FRuntimeFloatCurve InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "Comment", "// Auto-Seal\n" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
		{ "ToolTip", "Auto-Seal" },
	};
#endif // WITH_METADATA

// ********** Begin Function SealTODCurveFor24Hours constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SealTODCurveFor24Hours constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SealTODCurveFor24Hours Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TODCurveFunctionLibrary_eventSealTODCurveFor24Hours_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(0, nullptr) }; // 2560417949
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers) < 2048);
// ********** End Function SealTODCurveFor24Hours Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTODCurveFunctionLibrary, nullptr, "SealTODCurveFor24Hours", 	Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::TODCurveFunctionLibrary_eventSealTODCurveFor24Hours_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::TODCurveFunctionLibrary_eventSealTODCurveFor24Hours_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTODCurveFunctionLibrary::execSealTODCurveFor24Hours)
{
	P_GET_STRUCT_REF(FRuntimeFloatCurve,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UTODCurveFunctionLibrary::SealTODCurveFor24Hours(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UTODCurveFunctionLibrary Function SealTODCurveFor24Hours *******************

// ********** Begin Class UTODCurveFunctionLibrary *************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UTODCurveFunctionLibrary;
UClass* UTODCurveFunctionLibrary::GetPrivateStaticClass()
{
	using TClass = UTODCurveFunctionLibrary;
	if (!Z_Registration_Info_UClass_UTODCurveFunctionLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TODCurveFunctionLibrary"),
			Z_Registration_Info_UClass_UTODCurveFunctionLibrary.InnerSingleton,
			StaticRegisterNativesUTODCurveFunctionLibrary,
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
	return Z_Registration_Info_UClass_UTODCurveFunctionLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UTODCurveFunctionLibrary_NoRegister()
{
	return UTODCurveFunctionLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTODCurveFunctionLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "TODCurveFunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/TODCurveFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UTODCurveFunctionLibrary constinit property declarations *****************
// ********** End Class UTODCurveFunctionLibrary constinit property declarations *******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AddKeyToRuntimeColorCurve"), .Pointer = &UTODCurveFunctionLibrary::execAddKeyToRuntimeColorCurve },
		{ .NameUTF8 = UTF8TEXT("AddKeyToRuntimeFloatCurve"), .Pointer = &UTODCurveFunctionLibrary::execAddKeyToRuntimeFloatCurve },
		{ .NameUTF8 = UTF8TEXT("ClearRuntimeColorCurve"), .Pointer = &UTODCurveFunctionLibrary::execClearRuntimeColorCurve },
		{ .NameUTF8 = UTF8TEXT("ClearRuntimeFloatCurve"), .Pointer = &UTODCurveFunctionLibrary::execClearRuntimeFloatCurve },
		{ .NameUTF8 = UTF8TEXT("GetRuntimeColorCurveValue"), .Pointer = &UTODCurveFunctionLibrary::execGetRuntimeColorCurveValue },
		{ .NameUTF8 = UTF8TEXT("SealColorCurveFor24Hours"), .Pointer = &UTODCurveFunctionLibrary::execSealColorCurveFor24Hours },
		{ .NameUTF8 = UTF8TEXT("SealTODCurveFor24Hours"), .Pointer = &UTODCurveFunctionLibrary::execSealTODCurveFor24Hours },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeColorCurve, "AddKeyToRuntimeColorCurve" }, // 50122755
		{ &Z_Construct_UFunction_UTODCurveFunctionLibrary_AddKeyToRuntimeFloatCurve, "AddKeyToRuntimeFloatCurve" }, // 3950356447
		{ &Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeColorCurve, "ClearRuntimeColorCurve" }, // 630018742
		{ &Z_Construct_UFunction_UTODCurveFunctionLibrary_ClearRuntimeFloatCurve, "ClearRuntimeFloatCurve" }, // 813505467
		{ &Z_Construct_UFunction_UTODCurveFunctionLibrary_GetRuntimeColorCurveValue, "GetRuntimeColorCurveValue" }, // 2317023348
		{ &Z_Construct_UFunction_UTODCurveFunctionLibrary_SealColorCurveFor24Hours, "SealColorCurveFor24Hours" }, // 2164548874
		{ &Z_Construct_UFunction_UTODCurveFunctionLibrary_SealTODCurveFor24Hours, "SealTODCurveFor24Hours" }, // 2814674503
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTODCurveFunctionLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UTODCurveFunctionLibrary_Statics
UObject* (*const Z_Construct_UClass_UTODCurveFunctionLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTODCurveFunctionLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTODCurveFunctionLibrary_Statics::ClassParams = {
	&UTODCurveFunctionLibrary::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTODCurveFunctionLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UTODCurveFunctionLibrary_Statics::Class_MetaDataParams)
};
void UTODCurveFunctionLibrary::StaticRegisterNativesUTODCurveFunctionLibrary()
{
	UClass* Class = UTODCurveFunctionLibrary::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UTODCurveFunctionLibrary_Statics::Funcs));
}
UClass* Z_Construct_UClass_UTODCurveFunctionLibrary()
{
	if (!Z_Registration_Info_UClass_UTODCurveFunctionLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTODCurveFunctionLibrary.OuterSingleton, Z_Construct_UClass_UTODCurveFunctionLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTODCurveFunctionLibrary.OuterSingleton;
}
UTODCurveFunctionLibrary::UTODCurveFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UTODCurveFunctionLibrary);
UTODCurveFunctionLibrary::~UTODCurveFunctionLibrary() {}
// ********** End Class UTODCurveFunctionLibrary ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h__Script_Fluid_TOD_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTODCurveFunctionLibrary, UTODCurveFunctionLibrary::StaticClass, TEXT("UTODCurveFunctionLibrary"), &Z_Registration_Info_UClass_UTODCurveFunctionLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTODCurveFunctionLibrary), 2666731221U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h__Script_Fluid_TOD_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h__Script_Fluid_TOD_3203107266{
	TEXT("/Script/Fluid_TOD"),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h__Script_Fluid_TOD_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveFunctionLibrary_h__Script_Fluid_TOD_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
