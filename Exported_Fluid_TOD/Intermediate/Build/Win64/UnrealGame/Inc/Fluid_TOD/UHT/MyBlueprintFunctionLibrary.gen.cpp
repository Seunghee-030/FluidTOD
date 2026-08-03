// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMyBlueprintFunctionLibrary() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UEnum* Z_Construct_UEnum_Engine_ERichCurveInterpMode();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeCurveLinearColor();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
FLUID_TOD_API UClass* Z_Construct_UClass_UMyBlueprintFunctionLibrary();
FLUID_TOD_API UClass* Z_Construct_UClass_UMyBlueprintFunctionLibrary_NoRegister();
UPackage* Z_Construct_UPackage__Script_Fluid_TOD();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMyBlueprintFunctionLibrary Function AddKeyToRuntimeColorCurve ***********
struct Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics
{
	struct MyBlueprintFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms
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
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(0, nullptr) }; // 3548222332
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InColor = { "InColor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InterpMode = { "InterpMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms, InterpMode), Z_Construct_UEnum_Engine_ERichCurveInterpMode, METADATA_PARAMS(0, nullptr) }; // 3137508823
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::NewProp_InterpMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers) < 2048);
// ********** End Function AddKeyToRuntimeColorCurve Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyBlueprintFunctionLibrary, nullptr, "AddKeyToRuntimeColorCurve", 	Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::MyBlueprintFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::MyBlueprintFunctionLibrary_eventAddKeyToRuntimeColorCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyBlueprintFunctionLibrary::execAddKeyToRuntimeColorCurve)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_GET_STRUCT(FLinearColor,Z_Param_InColor);
	P_GET_PROPERTY(FByteProperty,Z_Param_InterpMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Z_Param_Out_InCurve,Z_Param_InTime,Z_Param_InColor,ERichCurveInterpMode(Z_Param_InterpMode));
	P_NATIVE_END;
}
// ********** End Class UMyBlueprintFunctionLibrary Function AddKeyToRuntimeColorCurve *************

// ********** Begin Class UMyBlueprintFunctionLibrary Function AddKeyToRuntimeFloatCurve ***********
struct Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics
{
	struct MyBlueprintFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms
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
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(0, nullptr) }; // 2560417949
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InterpMode = { "InterpMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms, InterpMode), Z_Construct_UEnum_Engine_ERichCurveInterpMode, METADATA_PARAMS(0, nullptr) }; // 3137508823
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::NewProp_InterpMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers) < 2048);
// ********** End Function AddKeyToRuntimeFloatCurve Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyBlueprintFunctionLibrary, nullptr, "AddKeyToRuntimeFloatCurve", 	Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::MyBlueprintFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::MyBlueprintFunctionLibrary_eventAddKeyToRuntimeFloatCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyBlueprintFunctionLibrary::execAddKeyToRuntimeFloatCurve)
{
	P_GET_STRUCT_REF(FRuntimeFloatCurve,Z_Param_Out_InCurve);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InValue);
	P_GET_PROPERTY(FByteProperty,Z_Param_InterpMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Z_Param_Out_InCurve,Z_Param_InTime,Z_Param_InValue,ERichCurveInterpMode(Z_Param_InterpMode));
	P_NATIVE_END;
}
// ********** End Class UMyBlueprintFunctionLibrary Function AddKeyToRuntimeFloatCurve *************

// ********** Begin Class UMyBlueprintFunctionLibrary Function ClearRuntimeColorCurve **************
struct Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics
{
	struct MyBlueprintFunctionLibrary_eventClearRuntimeColorCurve_Parms
	{
		FRuntimeCurveLinearColor InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClearRuntimeColorCurve constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ClearRuntimeColorCurve constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ClearRuntimeColorCurve Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventClearRuntimeColorCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(0, nullptr) }; // 3548222332
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers) < 2048);
// ********** End Function ClearRuntimeColorCurve Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyBlueprintFunctionLibrary, nullptr, "ClearRuntimeColorCurve", 	Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::MyBlueprintFunctionLibrary_eventClearRuntimeColorCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::MyBlueprintFunctionLibrary_eventClearRuntimeColorCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyBlueprintFunctionLibrary::execClearRuntimeColorCurve)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UMyBlueprintFunctionLibrary::ClearRuntimeColorCurve(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UMyBlueprintFunctionLibrary Function ClearRuntimeColorCurve ****************

// ********** Begin Class UMyBlueprintFunctionLibrary Function ClearRuntimeFloatCurve **************
struct Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics
{
	struct MyBlueprintFunctionLibrary_eventClearRuntimeFloatCurve_Parms
	{
		FRuntimeFloatCurve InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "Comment", "// Curve Control\n" },
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventClearRuntimeFloatCurve_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(0, nullptr) }; // 2560417949
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers) < 2048);
// ********** End Function ClearRuntimeFloatCurve Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyBlueprintFunctionLibrary, nullptr, "ClearRuntimeFloatCurve", 	Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::MyBlueprintFunctionLibrary_eventClearRuntimeFloatCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::MyBlueprintFunctionLibrary_eventClearRuntimeFloatCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyBlueprintFunctionLibrary::execClearRuntimeFloatCurve)
{
	P_GET_STRUCT_REF(FRuntimeFloatCurve,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UMyBlueprintFunctionLibrary::ClearRuntimeFloatCurve(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UMyBlueprintFunctionLibrary Function ClearRuntimeFloatCurve ****************

// ********** Begin Class UMyBlueprintFunctionLibrary Function GetRuntimeColorCurveValue ***********
struct Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics
{
	struct MyBlueprintFunctionLibrary_eventGetRuntimeColorCurveValue_Parms
	{
		FRuntimeCurveLinearColor InCurve;
		float InTime;
		FLinearColor ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventGetRuntimeColorCurveValue_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InCurve_MetaData), NewProp_InCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InTime = { "InTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventGetRuntimeColorCurveValue_Parms, InTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventGetRuntimeColorCurveValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_InTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers) < 2048);
// ********** End Function GetRuntimeColorCurveValue Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyBlueprintFunctionLibrary, nullptr, "GetRuntimeColorCurveValue", 	Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::MyBlueprintFunctionLibrary_eventGetRuntimeColorCurveValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::MyBlueprintFunctionLibrary_eventGetRuntimeColorCurveValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyBlueprintFunctionLibrary::execGetRuntimeColorCurveValue)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FLinearColor*)Z_Param__Result=UMyBlueprintFunctionLibrary::GetRuntimeColorCurveValue(Z_Param_Out_InCurve,Z_Param_InTime);
	P_NATIVE_END;
}
// ********** End Class UMyBlueprintFunctionLibrary Function GetRuntimeColorCurveValue *************

// ********** Begin Class UMyBlueprintFunctionLibrary Function SealColorCurveFor24Hours ************
struct Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics
{
	struct MyBlueprintFunctionLibrary_eventSealColorCurveFor24Hours_Parms
	{
		FRuntimeCurveLinearColor InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SealColorCurveFor24Hours constinit property declarations **************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SealColorCurveFor24Hours constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SealColorCurveFor24Hours Property Definitions *************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventSealColorCurveFor24Hours_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(0, nullptr) }; // 3548222332
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers) < 2048);
// ********** End Function SealColorCurveFor24Hours Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyBlueprintFunctionLibrary, nullptr, "SealColorCurveFor24Hours", 	Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::MyBlueprintFunctionLibrary_eventSealColorCurveFor24Hours_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::MyBlueprintFunctionLibrary_eventSealColorCurveFor24Hours_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyBlueprintFunctionLibrary::execSealColorCurveFor24Hours)
{
	P_GET_STRUCT_REF(FRuntimeCurveLinearColor,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UMyBlueprintFunctionLibrary::SealColorCurveFor24Hours(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UMyBlueprintFunctionLibrary Function SealColorCurveFor24Hours **************

// ********** Begin Class UMyBlueprintFunctionLibrary Function SealTODCurveFor24Hours **************
struct Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics
{
	struct MyBlueprintFunctionLibrary_eventSealTODCurveFor24Hours_Parms
	{
		FRuntimeFloatCurve InCurve;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TOD|Curve" },
		{ "Comment", "// Auto-Seal\n" },
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::NewProp_InCurve = { "InCurve", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyBlueprintFunctionLibrary_eventSealTODCurveFor24Hours_Parms, InCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(0, nullptr) }; // 2560417949
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::NewProp_InCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers) < 2048);
// ********** End Function SealTODCurveFor24Hours Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMyBlueprintFunctionLibrary, nullptr, "SealTODCurveFor24Hours", 	Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::MyBlueprintFunctionLibrary_eventSealTODCurveFor24Hours_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::MyBlueprintFunctionLibrary_eventSealTODCurveFor24Hours_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMyBlueprintFunctionLibrary::execSealTODCurveFor24Hours)
{
	P_GET_STRUCT_REF(FRuntimeFloatCurve,Z_Param_Out_InCurve);
	P_FINISH;
	P_NATIVE_BEGIN;
	UMyBlueprintFunctionLibrary::SealTODCurveFor24Hours(Z_Param_Out_InCurve);
	P_NATIVE_END;
}
// ********** End Class UMyBlueprintFunctionLibrary Function SealTODCurveFor24Hours ****************

// ********** Begin Class UMyBlueprintFunctionLibrary **********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary;
UClass* UMyBlueprintFunctionLibrary::GetPrivateStaticClass()
{
	using TClass = UMyBlueprintFunctionLibrary;
	if (!Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MyBlueprintFunctionLibrary"),
			Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary.InnerSingleton,
			StaticRegisterNativesUMyBlueprintFunctionLibrary,
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
	return Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UMyBlueprintFunctionLibrary_NoRegister()
{
	return UMyBlueprintFunctionLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MyBlueprintFunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/MyBlueprintFunctionLibrary.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UMyBlueprintFunctionLibrary constinit property declarations **************
// ********** End Class UMyBlueprintFunctionLibrary constinit property declarations ****************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AddKeyToRuntimeColorCurve"), .Pointer = &UMyBlueprintFunctionLibrary::execAddKeyToRuntimeColorCurve },
		{ .NameUTF8 = UTF8TEXT("AddKeyToRuntimeFloatCurve"), .Pointer = &UMyBlueprintFunctionLibrary::execAddKeyToRuntimeFloatCurve },
		{ .NameUTF8 = UTF8TEXT("ClearRuntimeColorCurve"), .Pointer = &UMyBlueprintFunctionLibrary::execClearRuntimeColorCurve },
		{ .NameUTF8 = UTF8TEXT("ClearRuntimeFloatCurve"), .Pointer = &UMyBlueprintFunctionLibrary::execClearRuntimeFloatCurve },
		{ .NameUTF8 = UTF8TEXT("GetRuntimeColorCurveValue"), .Pointer = &UMyBlueprintFunctionLibrary::execGetRuntimeColorCurveValue },
		{ .NameUTF8 = UTF8TEXT("SealColorCurveFor24Hours"), .Pointer = &UMyBlueprintFunctionLibrary::execSealColorCurveFor24Hours },
		{ .NameUTF8 = UTF8TEXT("SealTODCurveFor24Hours"), .Pointer = &UMyBlueprintFunctionLibrary::execSealTODCurveFor24Hours },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeColorCurve, "AddKeyToRuntimeColorCurve" }, // 1392303004
		{ &Z_Construct_UFunction_UMyBlueprintFunctionLibrary_AddKeyToRuntimeFloatCurve, "AddKeyToRuntimeFloatCurve" }, // 3454437206
		{ &Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeColorCurve, "ClearRuntimeColorCurve" }, // 3119878293
		{ &Z_Construct_UFunction_UMyBlueprintFunctionLibrary_ClearRuntimeFloatCurve, "ClearRuntimeFloatCurve" }, // 3093329410
		{ &Z_Construct_UFunction_UMyBlueprintFunctionLibrary_GetRuntimeColorCurveValue, "GetRuntimeColorCurveValue" }, // 2515327942
		{ &Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealColorCurveFor24Hours, "SealColorCurveFor24Hours" }, // 1703284518
		{ &Z_Construct_UFunction_UMyBlueprintFunctionLibrary_SealTODCurveFor24Hours, "SealTODCurveFor24Hours" }, // 3395144170
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMyBlueprintFunctionLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics
UObject* (*const Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics::ClassParams = {
	&UMyBlueprintFunctionLibrary::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics::Class_MetaDataParams)
};
void UMyBlueprintFunctionLibrary::StaticRegisterNativesUMyBlueprintFunctionLibrary()
{
	UClass* Class = UMyBlueprintFunctionLibrary::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics::Funcs));
}
UClass* Z_Construct_UClass_UMyBlueprintFunctionLibrary()
{
	if (!Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary.OuterSingleton, Z_Construct_UClass_UMyBlueprintFunctionLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary.OuterSingleton;
}
UMyBlueprintFunctionLibrary::UMyBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMyBlueprintFunctionLibrary);
UMyBlueprintFunctionLibrary::~UMyBlueprintFunctionLibrary() {}
// ********** End Class UMyBlueprintFunctionLibrary ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Exported_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_MyBlueprintFunctionLibrary_h__Script_Fluid_TOD_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMyBlueprintFunctionLibrary, UMyBlueprintFunctionLibrary::StaticClass, TEXT("UMyBlueprintFunctionLibrary"), &Z_Registration_Info_UClass_UMyBlueprintFunctionLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMyBlueprintFunctionLibrary), 110918977U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Exported_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_MyBlueprintFunctionLibrary_h__Script_Fluid_TOD_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Exported_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_MyBlueprintFunctionLibrary_h__Script_Fluid_TOD_925852782{
	TEXT("/Script/Fluid_TOD"),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Exported_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_MyBlueprintFunctionLibrary_h__Script_Fluid_TOD_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Exported_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_MyBlueprintFunctionLibrary_h__Script_Fluid_TOD_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
