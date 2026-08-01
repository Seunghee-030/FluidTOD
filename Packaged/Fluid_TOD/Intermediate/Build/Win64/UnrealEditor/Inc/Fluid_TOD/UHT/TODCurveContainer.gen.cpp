// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TODCurveContainer.h"
#include "TOD_Types.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTODCurveContainer() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODCurveContainer();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODCurveContainer_NoRegister();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODFogCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODMoonCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSkyLightCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSunCurveData();
UPackage* Z_Construct_UPackage__Script_Fluid_TOD();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UTODCurveContainer *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UTODCurveContainer;
UClass* UTODCurveContainer::GetPrivateStaticClass()
{
	using TClass = UTODCurveContainer;
	if (!Z_Registration_Info_UClass_UTODCurveContainer.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TODCurveContainer"),
			Z_Registration_Info_UClass_UTODCurveContainer.InnerSingleton,
			StaticRegisterNativesUTODCurveContainer,
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
	return Z_Registration_Info_UClass_UTODCurveContainer.InnerSingleton;
}
UClass* Z_Construct_UClass_UTODCurveContainer_NoRegister()
{
	return UTODCurveContainer::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTODCurveContainer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// TOD \xec\xbb\xa4\xeb\xb8\x8c 5\xec\xa2\x85\xec\x9d\x84 \xed\x95\x98\xeb\x82\x98\xeb\xa1\x9c \xeb\xac\xb6\xeb\x8a\x94 \xec\xbb\xa8\xed\x85\x8c\xec\x9d\xb4\xeb\x84\x88.\n" },
		{ "IncludePath", "TODCurveContainer.h" },
		{ "ModuleRelativePath", "Public/TODCurveContainer.h" },
		{ "ToolTip", "TOD \xec\xbb\xa4\xeb\xb8\x8c 5\xec\xa2\x85\xec\x9d\x84 \xed\x95\x98\xeb\x82\x98\xeb\xa1\x9c \xeb\xac\xb6\xeb\x8a\x94 \xec\xbb\xa8\xed\x85\x8c\xec\x9d\xb4\xeb\x84\x88." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunCurves_MetaData[] = {
		{ "Category", "Sun Curves" },
		{ "ModuleRelativePath", "Public/TODCurveContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoonCurves_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TODCurveContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyLightCurves_MetaData[] = {
		{ "Category", "SkyLight Curves" },
		{ "ModuleRelativePath", "Public/TODCurveContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogCurves_MetaData[] = {
		{ "Category", "Fog Curves" },
		{ "ModuleRelativePath", "Public/TODCurveContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyAtmosphereCurves_MetaData[] = {
		{ "Category", "SkyAtmosphere Curves" },
		{ "ModuleRelativePath", "Public/TODCurveContainer.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UTODCurveContainer constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_SunCurves;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MoonCurves;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyLightCurves;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FogCurves;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyAtmosphereCurves;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UTODCurveContainer constinit property declarations *************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTODCurveContainer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UTODCurveContainer_Statics

// ********** Begin Class UTODCurveContainer Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_SunCurves = { "SunCurves", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODCurveContainer, SunCurves), Z_Construct_UScriptStruct_FTODSunCurveData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunCurves_MetaData), NewProp_SunCurves_MetaData) }; // 2133515494
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_MoonCurves = { "MoonCurves", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODCurveContainer, MoonCurves), Z_Construct_UScriptStruct_FTODMoonCurveData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoonCurves_MetaData), NewProp_MoonCurves_MetaData) }; // 958035676
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_SkyLightCurves = { "SkyLightCurves", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODCurveContainer, SkyLightCurves), Z_Construct_UScriptStruct_FTODSkyLightCurveData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyLightCurves_MetaData), NewProp_SkyLightCurves_MetaData) }; // 3685823124
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_FogCurves = { "FogCurves", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODCurveContainer, FogCurves), Z_Construct_UScriptStruct_FTODFogCurveData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogCurves_MetaData), NewProp_FogCurves_MetaData) }; // 808622522
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_SkyAtmosphereCurves = { "SkyAtmosphereCurves", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODCurveContainer, SkyAtmosphereCurves), Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyAtmosphereCurves_MetaData), NewProp_SkyAtmosphereCurves_MetaData) }; // 2812713979
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTODCurveContainer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_SunCurves,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_MoonCurves,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_SkyLightCurves,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_FogCurves,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODCurveContainer_Statics::NewProp_SkyAtmosphereCurves,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTODCurveContainer_Statics::PropPointers) < 2048);
// ********** End Class UTODCurveContainer Property Definitions ************************************
UObject* (*const Z_Construct_UClass_UTODCurveContainer_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTODCurveContainer_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTODCurveContainer_Statics::ClassParams = {
	&UTODCurveContainer::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UTODCurveContainer_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UTODCurveContainer_Statics::PropPointers),
	0,
	0x003010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTODCurveContainer_Statics::Class_MetaDataParams), Z_Construct_UClass_UTODCurveContainer_Statics::Class_MetaDataParams)
};
void UTODCurveContainer::StaticRegisterNativesUTODCurveContainer()
{
}
UClass* Z_Construct_UClass_UTODCurveContainer()
{
	if (!Z_Registration_Info_UClass_UTODCurveContainer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTODCurveContainer.OuterSingleton, Z_Construct_UClass_UTODCurveContainer_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTODCurveContainer.OuterSingleton;
}
UTODCurveContainer::UTODCurveContainer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UTODCurveContainer);
UTODCurveContainer::~UTODCurveContainer() {}
// ********** End Class UTODCurveContainer *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveContainer_h__Script_Fluid_TOD_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTODCurveContainer, UTODCurveContainer::StaticClass, TEXT("UTODCurveContainer"), &Z_Registration_Info_UClass_UTODCurveContainer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTODCurveContainer), 4115789788U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveContainer_h__Script_Fluid_TOD_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveContainer_h__Script_Fluid_TOD_1669641844{
	TEXT("/Script/Fluid_TOD"),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveContainer_h__Script_Fluid_TOD_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TODCurveContainer_h__Script_Fluid_TOD_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
