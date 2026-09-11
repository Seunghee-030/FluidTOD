// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TODCurveEvaluator.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTODCurveEvaluator() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APostProcessVolume_NoRegister();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODPPVEntry();
UPackage* Z_Construct_UPackage__Script_Fluid_TOD();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FTODPPVEntry ******************************************************
struct Z_Construct_UScriptStruct_FTODPPVEntry_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODPPVEntry); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODPPVEntry); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// \xeb\x9f\xb0\xed\x83\x80\xec\x9e\x84 PPV \xeb\xb8\x94\xeb\xa0\x8c\xeb\x93\x9c \xec\xba\x90\xec\x8b\x9c \xec\x97\x94\xed\x8a\xb8\xeb\xa6\xac.\n// GC \xec\xb6\x94\xec\xa0\x81\xec\x9d\x84 \xec\x9c\x84\xed\x95\xb4 \xeb\xb0\x98\xeb\x93\x9c\xec\x8b\x9c USTRUCT + TObjectPtr \xec\x97\xac\xec\x95\xbc \xed\x95\x9c\xeb\x8b\xa4.\n// raw \xed\x8f\xac\xec\x9d\xb8\xed\x84\xb0\xeb\xa1\x9c \xeb\x91\x90\xeb\xa9\xb4 \xeb\xa0\x88\xeb\xb2\xa8 \xec\x8a\xa4\xed\x8a\xb8\xeb\xa6\xac\xeb\xb0\x8d/GC \xec\x8b\x9c \xed\x95\xb4\xec\xa0\x9c\xeb\x90\x9c \xeb\xa9\x94\xeb\xaa\xa8\xeb\xa6\xac\xeb\xa5\xbc IsValid()\xeb\xa1\x9c \xec\x9d\xbd\xea\xb2\x8c \xeb\x90\x9c\xeb\x8b\xa4.\n" },
		{ "ModuleRelativePath", "Public/TODCurveEvaluator.h" },
		{ "ToolTip", "\xeb\x9f\xb0\xed\x83\x80\xec\x9e\x84 PPV \xeb\xb8\x94\xeb\xa0\x8c\xeb\x93\x9c \xec\xba\x90\xec\x8b\x9c \xec\x97\x94\xed\x8a\xb8\xeb\xa6\xac.\nGC \xec\xb6\x94\xec\xa0\x81\xec\x9d\x84 \xec\x9c\x84\xed\x95\xb4 \xeb\xb0\x98\xeb\x93\x9c\xec\x8b\x9c USTRUCT + TObjectPtr \xec\x97\xac\xec\x95\xbc \xed\x95\x9c\xeb\x8b\xa4.\nraw \xed\x8f\xac\xec\x9d\xb8\xed\x84\xb0\xeb\xa1\x9c \xeb\x91\x90\xeb\xa9\xb4 \xeb\xa0\x88\xeb\xb2\xa8 \xec\x8a\xa4\xed\x8a\xb8\xeb\xa6\xac\xeb\xb0\x8d/GC \xec\x8b\x9c \xed\x95\xb4\xec\xa0\x9c\xeb\x90\x9c \xeb\xa9\x94\xeb\xaa\xa8\xeb\xa6\xac\xeb\xa5\xbc IsValid()\xeb\xa1\x9c \xec\x9d\xbd\xea\xb2\x8c \xeb\x90\x9c\xeb\x8b\xa4." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[] = {
		{ "ModuleRelativePath", "Public/TODCurveEvaluator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PPV_MetaData[] = {
		{ "ModuleRelativePath", "Public/TODCurveEvaluator.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODPPVEntry constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PPV;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODPPVEntry constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODPPVEntry>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODPPVEntry_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODPPVEntry;
class UScriptStruct* FTODPPVEntry::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODPPVEntry.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODPPVEntry.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODPPVEntry, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODPPVEntry"));
	}
	return Z_Registration_Info_UScriptStruct_FTODPPVEntry.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODPPVEntry Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODPPVEntry_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODPPVEntry, Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Time_MetaData), NewProp_Time_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FTODPPVEntry_Statics::NewProp_PPV = { "PPV", nullptr, (EPropertyFlags)0x0114000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODPPVEntry, PPV), Z_Construct_UClass_APostProcessVolume_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PPV_MetaData), NewProp_PPV_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODPPVEntry_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODPPVEntry_Statics::NewProp_Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODPPVEntry_Statics::NewProp_PPV,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODPPVEntry_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODPPVEntry Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODPPVEntry_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODPPVEntry",
	Z_Construct_UScriptStruct_FTODPPVEntry_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODPPVEntry_Statics::PropPointers),
	sizeof(FTODPPVEntry),
	alignof(FTODPPVEntry),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODPPVEntry_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODPPVEntry_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODPPVEntry()
{
	if (!Z_Registration_Info_UScriptStruct_FTODPPVEntry.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODPPVEntry.InnerSingleton, Z_Construct_UScriptStruct_FTODPPVEntry_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODPPVEntry.InnerSingleton);
}
// ********** End ScriptStruct FTODPPVEntry ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveEvaluator_h__Script_Fluid_TOD_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTODPPVEntry::StaticStruct, Z_Construct_UScriptStruct_FTODPPVEntry_Statics::NewStructOps, TEXT("TODPPVEntry"),&Z_Registration_Info_UScriptStruct_FTODPPVEntry, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODPPVEntry), 2929301188U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveEvaluator_h__Script_Fluid_TOD_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveEvaluator_h__Script_Fluid_TOD_1813684135{
	TEXT("/Script/Fluid_TOD"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveEvaluator_h__Script_Fluid_TOD_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveEvaluator_h__Script_Fluid_TOD_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
