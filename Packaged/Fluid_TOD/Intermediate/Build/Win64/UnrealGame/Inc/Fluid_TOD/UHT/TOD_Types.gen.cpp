// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TOD_Types.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTOD_Types() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
ENGINE_API UClass* Z_Construct_UClass_APostProcessVolume_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UEnum* Z_Construct_UEnum_Engine_ERichCurveInterpMode();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeCurveLinearColor();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
FLUID_TOD_API UClass* Z_Construct_UClass_UTOD_Types();
FLUID_TOD_API UClass* Z_Construct_UClass_UTOD_Types_NoRegister();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODPresetData();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODPresetData_NoRegister();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODSinglePreset();
FLUID_TOD_API UClass* Z_Construct_UClass_UTODSinglePreset_NoRegister();
FLUID_TOD_API UEnum* Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory();
FLUID_TOD_API UEnum* Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType();
FLUID_TOD_API UEnum* Z_Construct_UEnum_Fluid_TOD_ETODSeason();
FLUID_TOD_API UEnum* Z_Construct_UEnum_Fluid_TOD_ETODState();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODCurveKeyMode();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODFogCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODFogSettings();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODMasterData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODMoonCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODMoonSettings();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSingleCurveModeList();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSkyLightCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSkyLightSettings();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSunCurveData();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODSunMoonSettings();
FLUID_TOD_API UScriptStruct* Z_Construct_UScriptStruct_FTODTimePoint();
UPackage* Z_Construct_UPackage__Script_Fluid_TOD();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ETODState *****************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETODState;
static UEnum* ETODState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ETODState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ETODState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Fluid_TOD_ETODState, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("ETODState"));
	}
	return Z_Registration_Info_UEnum_ETODState.OuterSingleton;
}
template<> FLUID_TOD_NON_ATTRIBUTED_API UEnum* StaticEnum<ETODState>()
{
	return ETODState_StaticEnum();
}
struct Z_Construct_UEnum_Fluid_TOD_ETODState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Dawn.DisplayName", "Dawn" },
		{ "Dawn.Name", "ETODState::Dawn" },
		{ "Day.DisplayName", "Day" },
		{ "Day.Name", "ETODState::Day" },
		{ "Dusk.DisplayName", "Dusk" },
		{ "Dusk.Name", "ETODState::Dusk" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "Night.DisplayName", "Night" },
		{ "Night.Name", "ETODState::Night" },
		{ "Sunrise.DisplayName", "Sunrise" },
		{ "Sunrise.Name", "ETODState::Sunrise" },
		{ "Sunset.DisplayName", "Sunset" },
		{ "Sunset.Name", "ETODState::Sunset" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ETODState::Day", (int64)ETODState::Day },
		{ "ETODState::Night", (int64)ETODState::Night },
		{ "ETODState::Dawn", (int64)ETODState::Dawn },
		{ "ETODState::Sunrise", (int64)ETODState::Sunrise },
		{ "ETODState::Dusk", (int64)ETODState::Dusk },
		{ "ETODState::Sunset", (int64)ETODState::Sunset },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Fluid_TOD_ETODState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Fluid_TOD_ETODState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	"ETODState",
	"ETODState",
	Z_Construct_UEnum_Fluid_TOD_ETODState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Fluid_TOD_ETODState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Fluid_TOD_ETODState()
{
	if (!Z_Registration_Info_UEnum_ETODState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETODState.InnerSingleton, Z_Construct_UEnum_Fluid_TOD_ETODState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ETODState.InnerSingleton;
}
// ********** End Enum ETODState *******************************************************************

// ********** Begin Enum ETODSeason ****************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETODSeason;
static UEnum* ETODSeason_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ETODSeason.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ETODSeason.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Fluid_TOD_ETODSeason, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("ETODSeason"));
	}
	return Z_Registration_Info_UEnum_ETODSeason.OuterSingleton;
}
template<> FLUID_TOD_NON_ATTRIBUTED_API UEnum* StaticEnum<ETODSeason>()
{
	return ETODSeason_StaticEnum();
}
struct Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Autumn.DisplayName", "Fall" },
		{ "Autumn.Name", "ETODSeason::Autumn" },
		{ "BlueprintType", "true" },
		{ "Comment", "// \xea\xb3\x84\xec\xa0\x88\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "Spring.DisplayName", "Spring" },
		{ "Spring.Name", "ETODSeason::Spring" },
		{ "Summer.DisplayName", "Summer" },
		{ "Summer.Name", "ETODSeason::Summer" },
		{ "ToolTip", "\xea\xb3\x84\xec\xa0\x88" },
		{ "Winter.DisplayName", "Winter" },
		{ "Winter.Name", "ETODSeason::Winter" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ETODSeason::Spring", (int64)ETODSeason::Spring },
		{ "ETODSeason::Summer", (int64)ETODSeason::Summer },
		{ "ETODSeason::Autumn", (int64)ETODSeason::Autumn },
		{ "ETODSeason::Winter", (int64)ETODSeason::Winter },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	"ETODSeason",
	"ETODSeason",
	Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Fluid_TOD_ETODSeason()
{
	if (!Z_Registration_Info_UEnum_ETODSeason.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETODSeason.InnerSingleton, Z_Construct_UEnum_Fluid_TOD_ETODSeason_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ETODSeason.InnerSingleton;
}
// ********** End Enum ETODSeason ******************************************************************

// ********** Begin Enum ETODDirectionalLightType **************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETODDirectionalLightType;
static UEnum* ETODDirectionalLightType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ETODDirectionalLightType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ETODDirectionalLightType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("ETODDirectionalLightType"));
	}
	return Z_Registration_Info_UEnum_ETODDirectionalLightType.OuterSingleton;
}
template<> FLUID_TOD_NON_ATTRIBUTED_API UEnum* StaticEnum<ETODDirectionalLightType>()
{
	return ETODDirectionalLightType_StaticEnum();
}
struct Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// \xec\x82\xac\xec\x9a\xa9\xed\x95\xa0 \xeb\xb9\x9b \xec\xa2\x85\xeb\xa5\x98 \xec\x84\xa0\xed\x83\x9d (Sun/Moon/Both)\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "MoonOnly.DisplayName", "Moon" },
		{ "MoonOnly.Name", "ETODDirectionalLightType::MoonOnly" },
		{ "SunOnly.DisplayName", "Sun" },
		{ "SunOnly.Name", "ETODDirectionalLightType::SunOnly" },
		{ "ToolTip", "\xec\x82\xac\xec\x9a\xa9\xed\x95\xa0 \xeb\xb9\x9b \xec\xa2\x85\xeb\xa5\x98 \xec\x84\xa0\xed\x83\x9d (Sun/Moon/Both)" },
		{ "Transition.DisplayName", "Sun&Moon" },
		{ "Transition.Name", "ETODDirectionalLightType::Transition" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ETODDirectionalLightType::SunOnly", (int64)ETODDirectionalLightType::SunOnly },
		{ "ETODDirectionalLightType::MoonOnly", (int64)ETODDirectionalLightType::MoonOnly },
		{ "ETODDirectionalLightType::Transition", (int64)ETODDirectionalLightType::Transition },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	"ETODDirectionalLightType",
	"ETODDirectionalLightType",
	Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType()
{
	if (!Z_Registration_Info_UEnum_ETODDirectionalLightType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETODDirectionalLightType.InnerSingleton, Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ETODDirectionalLightType.InnerSingleton;
}
// ********** End Enum ETODDirectionalLightType ****************************************************

// ********** Begin Enum ETODComponentCategory *****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETODComponentCategory;
static UEnum* ETODComponentCategory_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ETODComponentCategory.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ETODComponentCategory.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("ETODComponentCategory"));
	}
	return Z_Registration_Info_UEnum_ETODComponentCategory.OuterSingleton;
}
template<> FLUID_TOD_NON_ATTRIBUTED_API UEnum* StaticEnum<ETODComponentCategory>()
{
	return ETODComponentCategory_StaticEnum();
}
struct Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "All.DisplayName", "All" },
		{ "All.Name", "ETODComponentCategory::All" },
		{ "BlueprintType", "true" },
		{ "Comment", "// EUW\xec\x9a\xa9 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8 \xec\xb9\xb4\xed\x85\x8c\xea\xb3\xa0\xeb\xa6\xac\n" },
		{ "ExponentialHeightFog.DisplayName", "ExponentialHeightFog" },
		{ "ExponentialHeightFog.Name", "ETODComponentCategory::ExponentialHeightFog" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "Moon.DisplayName", "Moon" },
		{ "Moon.Name", "ETODComponentCategory::Moon" },
		{ "PostProcessVolume.DisplayName", "PostProcessVolume" },
		{ "PostProcessVolume.Name", "ETODComponentCategory::PostProcessVolume" },
		{ "SkyAtmosphere.DisplayName", "SkyAtmosphere" },
		{ "SkyAtmosphere.Name", "ETODComponentCategory::SkyAtmosphere" },
		{ "SkyLight.DisplayName", "SkyLight" },
		{ "SkyLight.Name", "ETODComponentCategory::SkyLight" },
		{ "Sun.DisplayName", "Sun" },
		{ "Sun.Name", "ETODComponentCategory::Sun" },
		{ "ToolTip", "EUW\xec\x9a\xa9 \xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8 \xec\xb9\xb4\xed\x85\x8c\xea\xb3\xa0\xeb\xa6\xac" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ETODComponentCategory::All", (int64)ETODComponentCategory::All },
		{ "ETODComponentCategory::Sun", (int64)ETODComponentCategory::Sun },
		{ "ETODComponentCategory::Moon", (int64)ETODComponentCategory::Moon },
		{ "ETODComponentCategory::SkyLight", (int64)ETODComponentCategory::SkyLight },
		{ "ETODComponentCategory::ExponentialHeightFog", (int64)ETODComponentCategory::ExponentialHeightFog },
		{ "ETODComponentCategory::SkyAtmosphere", (int64)ETODComponentCategory::SkyAtmosphere },
		{ "ETODComponentCategory::PostProcessVolume", (int64)ETODComponentCategory::PostProcessVolume },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	"ETODComponentCategory",
	"ETODComponentCategory",
	Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory()
{
	if (!Z_Registration_Info_UEnum_ETODComponentCategory.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETODComponentCategory.InnerSingleton, Z_Construct_UEnum_Fluid_TOD_ETODComponentCategory_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ETODComponentCategory.InnerSingleton;
}
// ********** End Enum ETODComponentCategory *******************************************************

// ********** Begin ScriptStruct FTODTimePoint *****************************************************
struct Z_Construct_UScriptStruct_FTODTimePoint_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODTimePoint); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODTimePoint); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// \xec\x82\xac\xec\x9a\xa9\xec\x9e\x90\xec\xa7\x80\xec\xa0\x95 \xec\x8b\x9c\xea\xb0\x84 \xeb\xb2\x94\xec\x9c\x84 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xec\x82\xac\xec\x9a\xa9\xec\x9e\x90\xec\xa7\x80\xec\xa0\x95 \xec\x8b\x9c\xea\xb0\x84 \xeb\xb2\x94\xec\x9c\x84 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_State_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartTime_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMax", "24.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODTimePoint constinit property declarations *********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StartTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODTimePoint constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODTimePoint>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODTimePoint_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODTimePoint;
class UScriptStruct* FTODTimePoint::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODTimePoint.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODTimePoint.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODTimePoint, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODTimePoint"));
	}
	return Z_Registration_Info_UScriptStruct_FTODTimePoint.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODTimePoint Property Definitions ********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FTODTimePoint_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FTODTimePoint_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODTimePoint, State), Z_Construct_UEnum_Fluid_TOD_ETODState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_State_MetaData), NewProp_State_MetaData) }; // 2526692313
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODTimePoint_Statics::NewProp_StartTime = { "StartTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODTimePoint, StartTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartTime_MetaData), NewProp_StartTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODTimePoint_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODTimePoint_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODTimePoint_Statics::NewProp_State,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODTimePoint_Statics::NewProp_StartTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODTimePoint_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODTimePoint Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODTimePoint_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODTimePoint",
	Z_Construct_UScriptStruct_FTODTimePoint_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODTimePoint_Statics::PropPointers),
	sizeof(FTODTimePoint),
	alignof(FTODTimePoint),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODTimePoint_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODTimePoint_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODTimePoint()
{
	if (!Z_Registration_Info_UScriptStruct_FTODTimePoint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODTimePoint.InnerSingleton, Z_Construct_UScriptStruct_FTODTimePoint_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODTimePoint.InnerSingleton);
}
// ********** End ScriptStruct FTODTimePoint *******************************************************

// ********** Begin ScriptStruct FTODSunMoonSettings ***********************************************
struct Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODSunMoonSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODSunMoonSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intensity_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Source_Angle_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMax", "20.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Source_Soft_Angle_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMax", "20.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Indirect_Light_Intensity_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Light_Color_MetaData[] = {
		{ "Category", "TOD" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODSunMoonSettings constinit property declarations ***************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Intensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Source_Angle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Source_Soft_Angle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Indirect_Light_Intensity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Light_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODSunMoonSettings constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODSunMoonSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODSunMoonSettings;
class UScriptStruct* FTODSunMoonSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSunMoonSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODSunMoonSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODSunMoonSettings, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODSunMoonSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FTODSunMoonSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODSunMoonSettings Property Definitions **************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Intensity = { "Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunMoonSettings, Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intensity_MetaData), NewProp_Intensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Source_Angle = { "Source_Angle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunMoonSettings, Source_Angle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Source_Angle_MetaData), NewProp_Source_Angle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Source_Soft_Angle = { "Source_Soft_Angle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunMoonSettings, Source_Soft_Angle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Source_Soft_Angle_MetaData), NewProp_Source_Soft_Angle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Indirect_Light_Intensity = { "Indirect_Light_Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunMoonSettings, Indirect_Light_Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Indirect_Light_Intensity_MetaData), NewProp_Indirect_Light_Intensity_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Light_Color = { "Light_Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunMoonSettings, Light_Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Light_Color_MetaData), NewProp_Light_Color_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Intensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Source_Angle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Source_Soft_Angle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Indirect_Light_Intensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewProp_Light_Color,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODSunMoonSettings Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODSunMoonSettings",
	Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::PropPointers),
	sizeof(FTODSunMoonSettings),
	alignof(FTODSunMoonSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODSunMoonSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSunMoonSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODSunMoonSettings.InnerSingleton, Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODSunMoonSettings.InnerSingleton);
}
// ********** End ScriptStruct FTODSunMoonSettings *************************************************

// ********** Begin ScriptStruct FTODMoonSettings **************************************************
struct Z_Construct_UScriptStruct_FTODMoonSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODMoonSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODMoonSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Moon_Source_Scale_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "DisplayPriority", "10" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMax", "10.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Moon_Source_Emissive_Intensity_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "DisplayPriority", "11" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODMoonSettings constinit property declarations ******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Moon_Source_Scale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Moon_Source_Emissive_Intensity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODMoonSettings constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODMoonSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODMoonSettings_Statics
static_assert(std::is_polymorphic<FTODMoonSettings>() == std::is_polymorphic<FTODSunMoonSettings>(), "USTRUCT FTODMoonSettings cannot be polymorphic unless super FTODSunMoonSettings is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODMoonSettings;
class UScriptStruct* FTODMoonSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODMoonSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODMoonSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODMoonSettings, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODMoonSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FTODMoonSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODMoonSettings Property Definitions *****************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODMoonSettings_Statics::NewProp_Moon_Source_Scale = { "Moon_Source_Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonSettings, Moon_Source_Scale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Moon_Source_Scale_MetaData), NewProp_Moon_Source_Scale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODMoonSettings_Statics::NewProp_Moon_Source_Emissive_Intensity = { "Moon_Source_Emissive_Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonSettings, Moon_Source_Emissive_Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Moon_Source_Emissive_Intensity_MetaData), NewProp_Moon_Source_Emissive_Intensity_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODMoonSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonSettings_Statics::NewProp_Moon_Source_Scale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonSettings_Statics::NewProp_Moon_Source_Emissive_Intensity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMoonSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODMoonSettings Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODMoonSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	Z_Construct_UScriptStruct_FTODSunMoonSettings,
	&NewStructOps,
	"TODMoonSettings",
	Z_Construct_UScriptStruct_FTODMoonSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMoonSettings_Statics::PropPointers),
	sizeof(FTODMoonSettings),
	alignof(FTODMoonSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMoonSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODMoonSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODMoonSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FTODMoonSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODMoonSettings.InnerSingleton, Z_Construct_UScriptStruct_FTODMoonSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODMoonSettings.InnerSingleton);
}
// ********** End ScriptStruct FTODMoonSettings ****************************************************

// ********** Begin ScriptStruct FTODSkyLightSettings **********************************************
struct Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODSkyLightSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODSkyLightSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sky_Light_Intensity_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sky_Light_Color_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sky_Indirect_Lighting_Intensity_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sky_Volumetric_Scattering_Intensity_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyDome_Texture_Emissive_Intensity_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODSkyLightSettings constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Sky_Light_Intensity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Sky_Light_Color;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Sky_Indirect_Lighting_Intensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Sky_Volumetric_Scattering_Intensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SkyDome_Texture_Emissive_Intensity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODSkyLightSettings constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODSkyLightSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODSkyLightSettings;
class UScriptStruct* FTODSkyLightSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyLightSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODSkyLightSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODSkyLightSettings, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODSkyLightSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FTODSkyLightSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODSkyLightSettings Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Light_Intensity = { "Sky_Light_Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightSettings, Sky_Light_Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sky_Light_Intensity_MetaData), NewProp_Sky_Light_Intensity_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Light_Color = { "Sky_Light_Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightSettings, Sky_Light_Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sky_Light_Color_MetaData), NewProp_Sky_Light_Color_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Indirect_Lighting_Intensity = { "Sky_Indirect_Lighting_Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightSettings, Sky_Indirect_Lighting_Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sky_Indirect_Lighting_Intensity_MetaData), NewProp_Sky_Indirect_Lighting_Intensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Volumetric_Scattering_Intensity = { "Sky_Volumetric_Scattering_Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightSettings, Sky_Volumetric_Scattering_Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sky_Volumetric_Scattering_Intensity_MetaData), NewProp_Sky_Volumetric_Scattering_Intensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_SkyDome_Texture_Emissive_Intensity = { "SkyDome_Texture_Emissive_Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightSettings, SkyDome_Texture_Emissive_Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyDome_Texture_Emissive_Intensity_MetaData), NewProp_SkyDome_Texture_Emissive_Intensity_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Light_Intensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Light_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Indirect_Lighting_Intensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_Sky_Volumetric_Scattering_Intensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewProp_SkyDome_Texture_Emissive_Intensity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODSkyLightSettings Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODSkyLightSettings",
	Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::PropPointers),
	sizeof(FTODSkyLightSettings),
	alignof(FTODSkyLightSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODSkyLightSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyLightSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODSkyLightSettings.InnerSingleton, Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODSkyLightSettings.InnerSingleton);
}
// ********** End ScriptStruct FTODSkyLightSettings ************************************************

// ********** Begin ScriptStruct FTODFogSettings ***************************************************
struct Z_Construct_UScriptStruct_FTODFogSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODFogSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODFogSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Fog_Density_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Fog_Height_Falloff_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Fog_Inscattering_Color_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Fog_Directional_Inscattering_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODFogSettings constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Fog_Density;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Fog_Height_Falloff;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Fog_Inscattering_Color;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Fog_Directional_Inscattering;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODFogSettings constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODFogSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODFogSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODFogSettings;
class UScriptStruct* FTODFogSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODFogSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODFogSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODFogSettings, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODFogSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FTODFogSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODFogSettings Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Density = { "Fog_Density", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogSettings, Fog_Density), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Fog_Density_MetaData), NewProp_Fog_Density_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Height_Falloff = { "Fog_Height_Falloff", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogSettings, Fog_Height_Falloff), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Fog_Height_Falloff_MetaData), NewProp_Fog_Height_Falloff_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Inscattering_Color = { "Fog_Inscattering_Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogSettings, Fog_Inscattering_Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Fog_Inscattering_Color_MetaData), NewProp_Fog_Inscattering_Color_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Directional_Inscattering = { "Fog_Directional_Inscattering", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogSettings, Fog_Directional_Inscattering), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Fog_Directional_Inscattering_MetaData), NewProp_Fog_Directional_Inscattering_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODFogSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Density,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Height_Falloff,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Inscattering_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewProp_Fog_Directional_Inscattering,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODFogSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODFogSettings Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODFogSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODFogSettings",
	Z_Construct_UScriptStruct_FTODFogSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODFogSettings_Statics::PropPointers),
	sizeof(FTODFogSettings),
	alignof(FTODFogSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODFogSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODFogSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODFogSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FTODFogSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODFogSettings.InnerSingleton, Z_Construct_UScriptStruct_FTODFogSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODFogSettings.InnerSingleton);
}
// ********** End ScriptStruct FTODFogSettings *****************************************************

// ********** Begin ScriptStruct FTODSkyAtmosphereSettings *****************************************
struct Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODSkyAtmosphereSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODSkyAtmosphereSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mie_Scattering_Scale_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// \xeb\xaf\xb8 \xec\x82\xb0\xeb\x9e\x80 (\xeb\xb9\x9b \xeb\xb2\x88\xec\xa7\x90, \xeb\xa8\xbc\xec\xa7\x80 \xeb\xb0\x80\xeb\x8f\x84)\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xeb\xaf\xb8 \xec\x82\xb0\xeb\x9e\x80 (\xeb\xb9\x9b \xeb\xb2\x88\xec\xa7\x90, \xeb\xa8\xbc\xec\xa7\x80 \xeb\xb0\x80\xeb\x8f\x84)" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mie_Scattering_Color_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Absorption_Color_MetaData[] = {
		{ "Category", "TOD" },
		{ "Comment", "// \xeb\x8c\x80\xea\xb8\xb0 \xed\x9d\xa1\xec\x88\x98 (\xed\x95\x84\xed\x84\xb0 \xed\x9a\xa8\xea\xb3\xbc, \xec\x98\xa4\xec\xa1\xb4)\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xeb\x8c\x80\xea\xb8\xb0 \xed\x9d\xa1\xec\x88\x98 (\xed\x95\x84\xed\x84\xb0 \xed\x9a\xa8\xea\xb3\xbc, \xec\x98\xa4\xec\xa1\xb4)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rayleigh_Scattering_Scale_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// \xeb\xa0\x88\xec\x9d\xbc\xeb\xa6\xac \xec\x82\xb0\xeb\x9e\x80 (\xea\xb8\xb0\xeb\xb3\xb8 \xed\x95\x98\xeb\x8a\x98 \xed\x86\xa4)\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xeb\xa0\x88\xec\x9d\xbc\xeb\xa6\xac \xec\x82\xb0\xeb\x9e\x80 (\xea\xb8\xb0\xeb\xb3\xb8 \xed\x95\x98\xeb\x8a\x98 \xed\x86\xa4)" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Aerial_Perspective_Distance_Scale_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// \xea\xb3\xb5\xea\xb8\xb0 \xec\x9b\x90\xea\xb7\xbc\xeb\xb2\x95 (\xea\xb1\xb0\xeb\xa6\xac\xec\x97\x90 \xeb\x94\xb0\xeb\xa5\xb8 \xed\x8f\xac\xea\xb7\xb8\xed\x99\x94 \xea\xb0\x95\xeb\x8f\x84)\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xea\xb3\xb5\xea\xb8\xb0 \xec\x9b\x90\xea\xb7\xbc\xeb\xb2\x95 (\xea\xb1\xb0\xeb\xa6\xac\xec\x97\x90 \xeb\x94\xb0\xeb\xa5\xb8 \xed\x8f\xac\xea\xb7\xb8\xed\x99\x94 \xea\xb0\x95\xeb\x8f\x84)" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sky_Luminance_Factor_MetaData[] = {
		{ "Category", "TOD" },
		{ "Comment", "// \xec\x82\xb0\xeb\x9e\x80\xea\xb4\x91 \xec\xa0\x9c\xec\x96\xb4\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xec\x82\xb0\xeb\x9e\x80\xea\xb4\x91 \xec\xa0\x9c\xec\x96\xb4" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODSkyAtmosphereSettings constinit property declarations *********
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Mie_Scattering_Scale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Mie_Scattering_Color;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Absorption_Color;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rayleigh_Scattering_Scale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Aerial_Perspective_Distance_Scale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Sky_Luminance_Factor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODSkyAtmosphereSettings constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODSkyAtmosphereSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings;
class UScriptStruct* FTODSkyAtmosphereSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODSkyAtmosphereSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODSkyAtmosphereSettings Property Definitions ********************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Mie_Scattering_Scale = { "Mie_Scattering_Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereSettings, Mie_Scattering_Scale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mie_Scattering_Scale_MetaData), NewProp_Mie_Scattering_Scale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Mie_Scattering_Color = { "Mie_Scattering_Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereSettings, Mie_Scattering_Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mie_Scattering_Color_MetaData), NewProp_Mie_Scattering_Color_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Absorption_Color = { "Absorption_Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereSettings, Absorption_Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Absorption_Color_MetaData), NewProp_Absorption_Color_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Rayleigh_Scattering_Scale = { "Rayleigh_Scattering_Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereSettings, Rayleigh_Scattering_Scale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rayleigh_Scattering_Scale_MetaData), NewProp_Rayleigh_Scattering_Scale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Aerial_Perspective_Distance_Scale = { "Aerial_Perspective_Distance_Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereSettings, Aerial_Perspective_Distance_Scale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Aerial_Perspective_Distance_Scale_MetaData), NewProp_Aerial_Perspective_Distance_Scale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Sky_Luminance_Factor = { "Sky_Luminance_Factor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereSettings, Sky_Luminance_Factor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sky_Luminance_Factor_MetaData), NewProp_Sky_Luminance_Factor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Mie_Scattering_Scale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Mie_Scattering_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Absorption_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Rayleigh_Scattering_Scale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Aerial_Perspective_Distance_Scale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewProp_Sky_Luminance_Factor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODSkyAtmosphereSettings Property Definitions **********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODSkyAtmosphereSettings",
	Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::PropPointers),
	sizeof(FTODSkyAtmosphereSettings),
	alignof(FTODSkyAtmosphereSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings.InnerSingleton, Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings.InnerSingleton);
}
// ********** End ScriptStruct FTODSkyAtmosphereSettings *******************************************

// ********** Begin ScriptStruct FTODMasterData ****************************************************
struct Z_Construct_UScriptStruct_FTODMasterData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODMasterData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODMasterData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// \xeb\xa7\x88\xec\x8a\xa4\xed\x84\xb0 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xeb\xa7\x88\xec\x8a\xa4\xed\x84\xb0 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[] = {
		{ "Category", "TOD" },
		{ "ClampMax", "24.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "UIMax", "24.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PPV_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveLightMode_MetaData[] = {
		{ "Category", "TOD" },
		{ "Comment", "// \xeb\xb0\xa4,\xeb\x82\xae,\xec\xa0\x84\xed\x99\x98\xea\xb8\xb0 \xec\x84\xa0\xed\x83\x9d\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xeb\xb0\xa4,\xeb\x82\xae,\xec\xa0\x84\xed\x99\x98\xea\xb8\xb0 \xec\x84\xa0\xed\x83\x9d" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sun_Settings_MetaData[] = {
		{ "Category", "TOD" },
		{ "Comment", "// Day/Transition \xec\x83\x81\xed\x83\x9c\xec\x9d\xbc \xeb\x95\x8c\xeb\xa7\x8c \xeb\x85\xb8\xec\xb6\x9c\n" },
		{ "EditCondition", "ActiveLightMode == ETODDirectionalLightType::SunOnly || ActiveLightMode == ETODDirectionalLightType::Transition" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "Day/Transition \xec\x83\x81\xed\x83\x9c\xec\x9d\xbc \xeb\x95\x8c\xeb\xa7\x8c \xeb\x85\xb8\xec\xb6\x9c" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Moon_Settings_MetaData[] = {
		{ "Category", "TOD" },
		{ "Comment", "// Night/Transition \xec\x83\x81\xed\x83\x9c\xec\x9d\xbc \xeb\x95\x8c\xeb\xa7\x8c \xeb\x85\xb8\xec\xb6\x9c\n" },
		{ "EditCondition", "ActiveLightMode == ETODDirectionalLightType::MoonOnly || ActiveLightMode == ETODDirectionalLightType::Transition" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "Night/Transition \xec\x83\x81\xed\x83\x9c\xec\x9d\xbc \xeb\x95\x8c\xeb\xa7\x8c \xeb\x85\xb8\xec\xb6\x9c" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyLight_Settings_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Fog_Settings_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyAtmosphere_Settings_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODMasterData constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PPV;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ActiveLightMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ActiveLightMode;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Sun_Settings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Moon_Settings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyLight_Settings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Fog_Settings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyAtmosphere_Settings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODMasterData constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODMasterData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODMasterData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODMasterData;
class UScriptStruct* FTODMasterData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODMasterData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODMasterData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODMasterData, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODMasterData"));
	}
	return Z_Registration_Info_UScriptStruct_FTODMasterData.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODMasterData Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Time_MetaData), NewProp_Time_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_PPV = { "PPV", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, PPV), Z_Construct_UClass_APostProcessVolume_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PPV_MetaData), NewProp_PPV_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_ActiveLightMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_ActiveLightMode = { "ActiveLightMode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, ActiveLightMode), Z_Construct_UEnum_Fluid_TOD_ETODDirectionalLightType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveLightMode_MetaData), NewProp_ActiveLightMode_MetaData) }; // 734095136
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Sun_Settings = { "Sun_Settings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, Sun_Settings), Z_Construct_UScriptStruct_FTODSunMoonSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sun_Settings_MetaData), NewProp_Sun_Settings_MetaData) }; // 216167566
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Moon_Settings = { "Moon_Settings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, Moon_Settings), Z_Construct_UScriptStruct_FTODMoonSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Moon_Settings_MetaData), NewProp_Moon_Settings_MetaData) }; // 2446821375
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_SkyLight_Settings = { "SkyLight_Settings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, SkyLight_Settings), Z_Construct_UScriptStruct_FTODSkyLightSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyLight_Settings_MetaData), NewProp_SkyLight_Settings_MetaData) }; // 3156703963
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Fog_Settings = { "Fog_Settings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, Fog_Settings), Z_Construct_UScriptStruct_FTODFogSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Fog_Settings_MetaData), NewProp_Fog_Settings_MetaData) }; // 194493249
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_SkyAtmosphere_Settings = { "SkyAtmosphere_Settings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMasterData, SkyAtmosphere_Settings), Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyAtmosphere_Settings_MetaData), NewProp_SkyAtmosphere_Settings_MetaData) }; // 3171145136
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODMasterData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_PPV,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_ActiveLightMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_ActiveLightMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Sun_Settings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Moon_Settings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_SkyLight_Settings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_Fog_Settings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMasterData_Statics::NewProp_SkyAtmosphere_Settings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMasterData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODMasterData Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODMasterData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODMasterData",
	Z_Construct_UScriptStruct_FTODMasterData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMasterData_Statics::PropPointers),
	sizeof(FTODMasterData),
	alignof(FTODMasterData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMasterData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODMasterData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODMasterData()
{
	if (!Z_Registration_Info_UScriptStruct_FTODMasterData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODMasterData.InnerSingleton, Z_Construct_UScriptStruct_FTODMasterData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODMasterData.InnerSingleton);
}
// ********** End ScriptStruct FTODMasterData ******************************************************

// ********** Begin ScriptStruct FTODSunCurveData **************************************************
struct Z_Construct_UScriptStruct_FTODSunCurveData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODSunCurveData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODSunCurveData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// \xec\xbb\xa4\xeb\xb8\x8c \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xec\xbb\xa4\xeb\xb8\x8c \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IntensityCurve_MetaData[] = {
		{ "Category", "Sun Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceAngleCurve_MetaData[] = {
		{ "Category", "Sun Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceSoftAngleCurve_MetaData[] = {
		{ "Category", "Sun Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IndirectIntensityCurve_MetaData[] = {
		{ "Category", "Sun Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LightColorCurve_MetaData[] = {
		{ "Category", "Sun Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODSunCurveData constinit property declarations ******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_IntensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceAngleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceSoftAngleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_IndirectIntensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LightColorCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODSunCurveData constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODSunCurveData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODSunCurveData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODSunCurveData;
class UScriptStruct* FTODSunCurveData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSunCurveData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODSunCurveData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODSunCurveData, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODSunCurveData"));
	}
	return Z_Registration_Info_UScriptStruct_FTODSunCurveData.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODSunCurveData Property Definitions *****************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_IntensityCurve = { "IntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunCurveData, IntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IntensityCurve_MetaData), NewProp_IntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_SourceAngleCurve = { "SourceAngleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunCurveData, SourceAngleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceAngleCurve_MetaData), NewProp_SourceAngleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_SourceSoftAngleCurve = { "SourceSoftAngleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunCurveData, SourceSoftAngleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceSoftAngleCurve_MetaData), NewProp_SourceSoftAngleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_IndirectIntensityCurve = { "IndirectIntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunCurveData, IndirectIntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IndirectIntensityCurve_MetaData), NewProp_IndirectIntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_LightColorCurve = { "LightColorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSunCurveData, LightColorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LightColorCurve_MetaData), NewProp_LightColorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODSunCurveData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_IntensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_SourceAngleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_SourceSoftAngleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_IndirectIntensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewProp_LightColorCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSunCurveData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODSunCurveData Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODSunCurveData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODSunCurveData",
	Z_Construct_UScriptStruct_FTODSunCurveData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSunCurveData_Statics::PropPointers),
	sizeof(FTODSunCurveData),
	alignof(FTODSunCurveData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSunCurveData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODSunCurveData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODSunCurveData()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSunCurveData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODSunCurveData.InnerSingleton, Z_Construct_UScriptStruct_FTODSunCurveData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODSunCurveData.InnerSingleton);
}
// ********** End ScriptStruct FTODSunCurveData ****************************************************

// ********** Begin ScriptStruct FTODMoonCurveData *************************************************
struct Z_Construct_UScriptStruct_FTODMoonCurveData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODMoonCurveData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODMoonCurveData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IntensityCurve_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceAngleCurve_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceSoftAngleCurve_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IndirectIntensityCurve_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LightColorCurve_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceScaleCurve_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceEmissiveIntensityCurve_MetaData[] = {
		{ "Category", "Moon Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODMoonCurveData constinit property declarations *****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_IntensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceAngleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceSoftAngleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_IndirectIntensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LightColorCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceScaleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceEmissiveIntensityCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODMoonCurveData constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODMoonCurveData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODMoonCurveData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODMoonCurveData;
class UScriptStruct* FTODMoonCurveData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODMoonCurveData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODMoonCurveData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODMoonCurveData, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODMoonCurveData"));
	}
	return Z_Registration_Info_UScriptStruct_FTODMoonCurveData.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODMoonCurveData Property Definitions ****************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_IntensityCurve = { "IntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonCurveData, IntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IntensityCurve_MetaData), NewProp_IntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceAngleCurve = { "SourceAngleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonCurveData, SourceAngleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceAngleCurve_MetaData), NewProp_SourceAngleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceSoftAngleCurve = { "SourceSoftAngleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonCurveData, SourceSoftAngleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceSoftAngleCurve_MetaData), NewProp_SourceSoftAngleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_IndirectIntensityCurve = { "IndirectIntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonCurveData, IndirectIntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IndirectIntensityCurve_MetaData), NewProp_IndirectIntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_LightColorCurve = { "LightColorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonCurveData, LightColorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LightColorCurve_MetaData), NewProp_LightColorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceScaleCurve = { "SourceScaleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonCurveData, SourceScaleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceScaleCurve_MetaData), NewProp_SourceScaleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceEmissiveIntensityCurve = { "SourceEmissiveIntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODMoonCurveData, SourceEmissiveIntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceEmissiveIntensityCurve_MetaData), NewProp_SourceEmissiveIntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_IntensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceAngleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceSoftAngleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_IndirectIntensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_LightColorCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceScaleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewProp_SourceEmissiveIntensityCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODMoonCurveData Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODMoonCurveData",
	Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::PropPointers),
	sizeof(FTODMoonCurveData),
	alignof(FTODMoonCurveData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODMoonCurveData()
{
	if (!Z_Registration_Info_UScriptStruct_FTODMoonCurveData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODMoonCurveData.InnerSingleton, Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODMoonCurveData.InnerSingleton);
}
// ********** End ScriptStruct FTODMoonCurveData ***************************************************

// ********** Begin ScriptStruct FTODSkyLightCurveData *********************************************
struct Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODSkyLightCurveData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODSkyLightCurveData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IntensityCurve_MetaData[] = {
		{ "Category", "SkyLight Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IndirectIntensityCurve_MetaData[] = {
		{ "Category", "SkyLight Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VolumetricScatteringIntensityCurve_MetaData[] = {
		{ "Category", "SkyLight Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LightColorCurve_MetaData[] = {
		{ "Category", "SkyLight Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextureEmissiveIntensityCurve_MetaData[] = {
		{ "Category", "SkyLight Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODSkyLightCurveData constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_IntensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_IndirectIntensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VolumetricScatteringIntensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LightColorCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TextureEmissiveIntensityCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODSkyLightCurveData constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODSkyLightCurveData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData;
class UScriptStruct* FTODSkyLightCurveData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODSkyLightCurveData, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODSkyLightCurveData"));
	}
	return Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODSkyLightCurveData Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_IntensityCurve = { "IntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightCurveData, IntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IntensityCurve_MetaData), NewProp_IntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_IndirectIntensityCurve = { "IndirectIntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightCurveData, IndirectIntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IndirectIntensityCurve_MetaData), NewProp_IndirectIntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_VolumetricScatteringIntensityCurve = { "VolumetricScatteringIntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightCurveData, VolumetricScatteringIntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VolumetricScatteringIntensityCurve_MetaData), NewProp_VolumetricScatteringIntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_LightColorCurve = { "LightColorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightCurveData, LightColorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LightColorCurve_MetaData), NewProp_LightColorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_TextureEmissiveIntensityCurve = { "TextureEmissiveIntensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyLightCurveData, TextureEmissiveIntensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextureEmissiveIntensityCurve_MetaData), NewProp_TextureEmissiveIntensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_IntensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_IndirectIntensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_VolumetricScatteringIntensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_LightColorCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewProp_TextureEmissiveIntensityCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODSkyLightCurveData Property Definitions **************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODSkyLightCurveData",
	Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::PropPointers),
	sizeof(FTODSkyLightCurveData),
	alignof(FTODSkyLightCurveData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODSkyLightCurveData()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData.InnerSingleton, Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData.InnerSingleton);
}
// ********** End ScriptStruct FTODSkyLightCurveData ***********************************************

// ********** Begin ScriptStruct FTODFogCurveData **************************************************
struct Z_Construct_UScriptStruct_FTODFogCurveData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODFogCurveData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODFogCurveData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DensityCurve_MetaData[] = {
		{ "Category", "Fog Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeightFalloffCurve_MetaData[] = {
		{ "Category", "Fog Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InscatteringColorCurve_MetaData[] = {
		{ "Category", "Fog Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectionalColorCurve_MetaData[] = {
		{ "Category", "Fog Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODFogCurveData constinit property declarations ******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_DensityCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_HeightFalloffCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InscatteringColorCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DirectionalColorCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODFogCurveData constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODFogCurveData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODFogCurveData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODFogCurveData;
class UScriptStruct* FTODFogCurveData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODFogCurveData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODFogCurveData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODFogCurveData, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODFogCurveData"));
	}
	return Z_Registration_Info_UScriptStruct_FTODFogCurveData.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODFogCurveData Property Definitions *****************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_DensityCurve = { "DensityCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogCurveData, DensityCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DensityCurve_MetaData), NewProp_DensityCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_HeightFalloffCurve = { "HeightFalloffCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogCurveData, HeightFalloffCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeightFalloffCurve_MetaData), NewProp_HeightFalloffCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_InscatteringColorCurve = { "InscatteringColorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogCurveData, InscatteringColorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InscatteringColorCurve_MetaData), NewProp_InscatteringColorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_DirectionalColorCurve = { "DirectionalColorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODFogCurveData, DirectionalColorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectionalColorCurve_MetaData), NewProp_DirectionalColorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODFogCurveData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_DensityCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_HeightFalloffCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_InscatteringColorCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewProp_DirectionalColorCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODFogCurveData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODFogCurveData Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODFogCurveData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODFogCurveData",
	Z_Construct_UScriptStruct_FTODFogCurveData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODFogCurveData_Statics::PropPointers),
	sizeof(FTODFogCurveData),
	alignof(FTODFogCurveData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODFogCurveData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODFogCurveData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODFogCurveData()
{
	if (!Z_Registration_Info_UScriptStruct_FTODFogCurveData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODFogCurveData.InnerSingleton, Z_Construct_UScriptStruct_FTODFogCurveData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODFogCurveData.InnerSingleton);
}
// ********** End ScriptStruct FTODFogCurveData ****************************************************

// ********** Begin ScriptStruct FTODSkyAtmosphereCurveData ****************************************
struct Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODSkyAtmosphereCurveData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODSkyAtmosphereCurveData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MieScatteringScaleCurve_MetaData[] = {
		{ "Category", "SkyAtmosphere Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RayleighScatteringScaleCurve_MetaData[] = {
		{ "Category", "SkyAtmosphere Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AerialPerspectiveDistanceScaleCurve_MetaData[] = {
		{ "Category", "SkyAtmosphere Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MieScatteringColorCurve_MetaData[] = {
		{ "Category", "SkyAtmosphere Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AbsorptionColorCurve_MetaData[] = {
		{ "Category", "SkyAtmosphere Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyLuminanceFactorCurve_MetaData[] = {
		{ "Category", "SkyAtmosphere Curves" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODSkyAtmosphereCurveData constinit property declarations ********
	static const UECodeGen_Private::FStructPropertyParams NewProp_MieScatteringScaleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RayleighScatteringScaleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AerialPerspectiveDistanceScaleCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MieScatteringColorCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AbsorptionColorCurve;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyLuminanceFactorCurve;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODSkyAtmosphereCurveData constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODSkyAtmosphereCurveData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData;
class UScriptStruct* FTODSkyAtmosphereCurveData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODSkyAtmosphereCurveData"));
	}
	return Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODSkyAtmosphereCurveData Property Definitions *******************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_MieScatteringScaleCurve = { "MieScatteringScaleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereCurveData, MieScatteringScaleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MieScatteringScaleCurve_MetaData), NewProp_MieScatteringScaleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_RayleighScatteringScaleCurve = { "RayleighScatteringScaleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereCurveData, RayleighScatteringScaleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RayleighScatteringScaleCurve_MetaData), NewProp_RayleighScatteringScaleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_AerialPerspectiveDistanceScaleCurve = { "AerialPerspectiveDistanceScaleCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereCurveData, AerialPerspectiveDistanceScaleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AerialPerspectiveDistanceScaleCurve_MetaData), NewProp_AerialPerspectiveDistanceScaleCurve_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_MieScatteringColorCurve = { "MieScatteringColorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereCurveData, MieScatteringColorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MieScatteringColorCurve_MetaData), NewProp_MieScatteringColorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_AbsorptionColorCurve = { "AbsorptionColorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereCurveData, AbsorptionColorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AbsorptionColorCurve_MetaData), NewProp_AbsorptionColorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_SkyLuminanceFactorCurve = { "SkyLuminanceFactorCurve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSkyAtmosphereCurveData, SkyLuminanceFactorCurve), Z_Construct_UScriptStruct_FRuntimeCurveLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyLuminanceFactorCurve_MetaData), NewProp_SkyLuminanceFactorCurve_MetaData) }; // 3548222332
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_MieScatteringScaleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_RayleighScatteringScaleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_AerialPerspectiveDistanceScaleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_MieScatteringColorCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_AbsorptionColorCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewProp_SkyLuminanceFactorCurve,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODSkyAtmosphereCurveData Property Definitions *********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODSkyAtmosphereCurveData",
	Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::PropPointers),
	sizeof(FTODSkyAtmosphereCurveData),
	alignof(FTODSkyAtmosphereCurveData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData.InnerSingleton, Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData.InnerSingleton);
}
// ********** End ScriptStruct FTODSkyAtmosphereCurveData ******************************************

// ********** Begin ScriptStruct FTODCurveKeyMode **************************************************
struct Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODCurveKeyMode); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODCurveKeyMode); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// \xec\xbb\xa4\xeb\xb8\x8c \xed\x82\xa4 1\xea\xb0\x9c\xec\x9d\x98 \xec\x8b\x9c\xea\xb0\x84+\xeb\xb3\xb4\xea\xb0\x84\xeb\xaa\xa8\xeb\x93\x9c (\xed\x94\x84\xeb\xa6\xac\xec\x85\x8b \xec\xa0\x80\xec\x9e\xa5/\xeb\xa6\xac\xeb\xb2\xa0\xec\x9d\xb4\xed\x81\xac \xeb\xb3\xb4\xec\xa1\xb4\xec\x9a\xa9, UI\xec\x97\x90\xeb\x8a\x94 \xeb\x85\xb8\xec\xb6\x9c \xec\x95\x88 \xed\x95\xa8)\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xec\xbb\xa4\xeb\xb8\x8c \xed\x82\xa4 1\xea\xb0\x9c\xec\x9d\x98 \xec\x8b\x9c\xea\xb0\x84+\xeb\xb3\xb4\xea\xb0\x84\xeb\xaa\xa8\xeb\x93\x9c (\xed\x94\x84\xeb\xa6\xac\xec\x85\x8b \xec\xa0\x80\xec\x9e\xa5/\xeb\xa6\xac\xeb\xb2\xa0\xec\x9d\xb4\xed\x81\xac \xeb\xb3\xb4\xec\xa1\xb4\xec\x9a\xa9, UI\xec\x97\x90\xeb\x8a\x94 \xeb\x85\xb8\xec\xb6\x9c \xec\x95\x88 \xed\x95\xa8)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[] = {
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterpMode_MetaData[] = {
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODCurveKeyMode constinit property declarations ******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
	static const UECodeGen_Private::FBytePropertyParams NewProp_InterpMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODCurveKeyMode constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODCurveKeyMode>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODCurveKeyMode;
class UScriptStruct* FTODCurveKeyMode::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODCurveKeyMode.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODCurveKeyMode.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODCurveKeyMode, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODCurveKeyMode"));
	}
	return Z_Registration_Info_UScriptStruct_FTODCurveKeyMode.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODCurveKeyMode Property Definitions *****************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODCurveKeyMode, Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Time_MetaData), NewProp_Time_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::NewProp_InterpMode = { "InterpMode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODCurveKeyMode, InterpMode), Z_Construct_UEnum_Engine_ERichCurveInterpMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterpMode_MetaData), NewProp_InterpMode_MetaData) }; // 3137508823
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::NewProp_Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::NewProp_InterpMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODCurveKeyMode Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODCurveKeyMode",
	Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::PropPointers),
	sizeof(FTODCurveKeyMode),
	alignof(FTODCurveKeyMode),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODCurveKeyMode()
{
	if (!Z_Registration_Info_UScriptStruct_FTODCurveKeyMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODCurveKeyMode.InnerSingleton, Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODCurveKeyMode.InnerSingleton);
}
// ********** End ScriptStruct FTODCurveKeyMode ****************************************************

// ********** Begin ScriptStruct FTODSingleCurveModeList *******************************************
struct Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODSingleCurveModeList); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODSingleCurveModeList); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Keys_MetaData[] = {
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODSingleCurveModeList constinit property declarations ***********
	static const UECodeGen_Private::FStructPropertyParams NewProp_Keys_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Keys;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODSingleCurveModeList constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODSingleCurveModeList>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList;
class UScriptStruct* FTODSingleCurveModeList::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODSingleCurveModeList, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODSingleCurveModeList"));
	}
	return Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODSingleCurveModeList Property Definitions **********************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::NewProp_Keys_Inner = { "Keys", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTODCurveKeyMode, METADATA_PARAMS(0, nullptr) }; // 133544755
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::NewProp_Keys = { "Keys", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODSingleCurveModeList, Keys), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Keys_MetaData), NewProp_Keys_MetaData) }; // 133544755
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::NewProp_Keys_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::NewProp_Keys,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODSingleCurveModeList Property Definitions ************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODSingleCurveModeList",
	Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::PropPointers),
	sizeof(FTODSingleCurveModeList),
	alignof(FTODSingleCurveModeList),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODSingleCurveModeList()
{
	if (!Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList.InnerSingleton, Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList.InnerSingleton);
}
// ********** End ScriptStruct FTODSingleCurveModeList *********************************************

// ********** Begin ScriptStruct FTODCurveDataModeSnapshot *****************************************
struct Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTODCurveDataModeSnapshot); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTODCurveDataModeSnapshot); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// CurveData \xec\xa0\x84\xec\xb2\xb4(float 18\xea\xb0\x9c + color 8\xea\xb0\x9c\xc3\x97""4\xec\xb1\x84\xeb\x84\x90)\xec\x9d\x98 InterpMode \xec\x8a\xa4\xeb\x83\x85\xec\x83\xb7.\n// FTODCurveEvaluator::GetAllFloatCurves() / GetAllColorCurves()\xec\x99\x80 \xeb\x8f\x99\xec\x9d\xbc\xed\x95\x9c \xec\x88\x9c\xec\x84\x9c\xeb\xa1\x9c \xec\xa0\x80\xec\x9e\xa5\xeb\x90\xa8.\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "CurveData \xec\xa0\x84\xec\xb2\xb4(float 18\xea\xb0\x9c + color 8\xea\xb0\x9c\xc3\x97""4\xec\xb1\x84\xeb\x84\x90)\xec\x9d\x98 InterpMode \xec\x8a\xa4\xeb\x83\x85\xec\x83\xb7.\nFTODCurveEvaluator::GetAllFloatCurves() / GetAllColorCurves()\xec\x99\x80 \xeb\x8f\x99\xec\x9d\xbc\xed\x95\x9c \xec\x88\x9c\xec\x84\x9c\xeb\xa1\x9c \xec\xa0\x80\xec\x9e\xa5\xeb\x90\xa8." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FloatCurveModes_MetaData[] = {
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorCurveModes_MetaData[] = {
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTODCurveDataModeSnapshot constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_FloatCurveModes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FloatCurveModes;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ColorCurveModes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ColorCurveModes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTODCurveDataModeSnapshot constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTODCurveDataModeSnapshot>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot;
class UScriptStruct* FTODCurveDataModeSnapshot::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot, (UObject*)Z_Construct_UPackage__Script_Fluid_TOD(), TEXT("TODCurveDataModeSnapshot"));
	}
	return Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot.OuterSingleton;
	}

// ********** Begin ScriptStruct FTODCurveDataModeSnapshot Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_FloatCurveModes_Inner = { "FloatCurveModes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTODSingleCurveModeList, METADATA_PARAMS(0, nullptr) }; // 1247844576
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_FloatCurveModes = { "FloatCurveModes", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODCurveDataModeSnapshot, FloatCurveModes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FloatCurveModes_MetaData), NewProp_FloatCurveModes_MetaData) }; // 1247844576
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_ColorCurveModes_Inner = { "ColorCurveModes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTODSingleCurveModeList, METADATA_PARAMS(0, nullptr) }; // 1247844576
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_ColorCurveModes = { "ColorCurveModes", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTODCurveDataModeSnapshot, ColorCurveModes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorCurveModes_MetaData), NewProp_ColorCurveModes_MetaData) }; // 1247844576
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_FloatCurveModes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_FloatCurveModes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_ColorCurveModes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewProp_ColorCurveModes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTODCurveDataModeSnapshot Property Definitions **********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
	nullptr,
	&NewStructOps,
	"TODCurveDataModeSnapshot",
	Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::PropPointers),
	sizeof(FTODCurveDataModeSnapshot),
	alignof(FTODCurveDataModeSnapshot),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot()
{
	if (!Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot.InnerSingleton, Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot.InnerSingleton);
}
// ********** End ScriptStruct FTODCurveDataModeSnapshot *******************************************

// ********** Begin Class UTOD_Types ***************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UTOD_Types;
UClass* UTOD_Types::GetPrivateStaticClass()
{
	using TClass = UTOD_Types;
	if (!Z_Registration_Info_UClass_UTOD_Types.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TOD_Types"),
			Z_Registration_Info_UClass_UTOD_Types.InnerSingleton,
			StaticRegisterNativesUTOD_Types,
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
	return Z_Registration_Info_UClass_UTOD_Types.InnerSingleton;
}
UClass* Z_Construct_UClass_UTOD_Types_NoRegister()
{
	return UTOD_Types::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTOD_Types_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "TOD_Types.h" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UTOD_Types constinit property declarations *******************************
// ********** End Class UTOD_Types constinit property declarations *********************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTOD_Types>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UTOD_Types_Statics
UObject* (*const Z_Construct_UClass_UTOD_Types_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTOD_Types_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTOD_Types_Statics::ClassParams = {
	&UTOD_Types::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTOD_Types_Statics::Class_MetaDataParams), Z_Construct_UClass_UTOD_Types_Statics::Class_MetaDataParams)
};
void UTOD_Types::StaticRegisterNativesUTOD_Types()
{
}
UClass* Z_Construct_UClass_UTOD_Types()
{
	if (!Z_Registration_Info_UClass_UTOD_Types.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTOD_Types.OuterSingleton, Z_Construct_UClass_UTOD_Types_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTOD_Types.OuterSingleton;
}
UTOD_Types::UTOD_Types(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UTOD_Types);
UTOD_Types::~UTOD_Types() {}
// ********** End Class UTOD_Types *****************************************************************

// ********** Begin Class UTODSinglePreset *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UTODSinglePreset;
UClass* UTODSinglePreset::GetPrivateStaticClass()
{
	using TClass = UTODSinglePreset;
	if (!Z_Registration_Info_UClass_UTODSinglePreset.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TODSinglePreset"),
			Z_Registration_Info_UClass_UTODSinglePreset.InnerSingleton,
			StaticRegisterNativesUTODSinglePreset,
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
	return Z_Registration_Info_UClass_UTODSinglePreset.InnerSingleton;
}
UClass* Z_Construct_UClass_UTODSinglePreset_NoRegister()
{
	return UTODSinglePreset::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTODSinglePreset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "TOD_Types.h" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SavedData_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UTODSinglePreset constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_SavedData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UTODSinglePreset constinit property declarations ***************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTODSinglePreset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UTODSinglePreset_Statics

// ********** Begin Class UTODSinglePreset Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODSinglePreset_Statics::NewProp_SavedData = { "SavedData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODSinglePreset, SavedData), Z_Construct_UScriptStruct_FTODMasterData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SavedData_MetaData), NewProp_SavedData_MetaData) }; // 1494437275
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTODSinglePreset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODSinglePreset_Statics::NewProp_SavedData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTODSinglePreset_Statics::PropPointers) < 2048);
// ********** End Class UTODSinglePreset Property Definitions **************************************
UObject* (*const Z_Construct_UClass_UTODSinglePreset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTODSinglePreset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTODSinglePreset_Statics::ClassParams = {
	&UTODSinglePreset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UTODSinglePreset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UTODSinglePreset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTODSinglePreset_Statics::Class_MetaDataParams), Z_Construct_UClass_UTODSinglePreset_Statics::Class_MetaDataParams)
};
void UTODSinglePreset::StaticRegisterNativesUTODSinglePreset()
{
}
UClass* Z_Construct_UClass_UTODSinglePreset()
{
	if (!Z_Registration_Info_UClass_UTODSinglePreset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTODSinglePreset.OuterSingleton, Z_Construct_UClass_UTODSinglePreset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTODSinglePreset.OuterSingleton;
}
UTODSinglePreset::UTODSinglePreset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UTODSinglePreset);
UTODSinglePreset::~UTODSinglePreset() {}
// ********** End Class UTODSinglePreset ***********************************************************

// ********** Begin Class UTODPresetData ***********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UTODPresetData;
UClass* UTODPresetData::GetPrivateStaticClass()
{
	using TClass = UTODPresetData;
	if (!Z_Registration_Info_UClass_UTODPresetData.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TODPresetData"),
			Z_Registration_Info_UClass_UTODPresetData.InnerSingleton,
			StaticRegisterNativesUTODPresetData,
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
	return Z_Registration_Info_UClass_UTODPresetData.InnerSingleton;
}
UClass* Z_Construct_UClass_UTODPresetData_NoRegister()
{
	return UTODPresetData::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTODPresetData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "TOD_Types.h" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TOD_DataArray_MetaData[] = {
		{ "Category", "TOD" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurveInterpModes_MetaData[] = {
		{ "Comment", "// \xec\xa0\x80\xec\x9e\xa5 \xec\x8b\x9c\xec\xa0\x90 \xec\xbb\xa4\xeb\xb8\x8c\xec\x9d\x98 \xed\x82\xa4\xeb\xb3\x84 Interpolation \xeb\xaa\xa8\xeb\x93\x9c \xec\x8a\xa4\xeb\x83\x85\xec\x83\xb7. \xed\x94\x84\xeb\xa6\xac\xec\x85\x8b \xeb\xa1\x9c\xeb\x93\x9c \xec\x8b\x9c \xeb\xb3\xb5\xec\x9b\x90\xeb\x90\xa8.\n" },
		{ "ModuleRelativePath", "Public/TOD_Types.h" },
		{ "ToolTip", "\xec\xa0\x80\xec\x9e\xa5 \xec\x8b\x9c\xec\xa0\x90 \xec\xbb\xa4\xeb\xb8\x8c\xec\x9d\x98 \xed\x82\xa4\xeb\xb3\x84 Interpolation \xeb\xaa\xa8\xeb\x93\x9c \xec\x8a\xa4\xeb\x83\x85\xec\x83\xb7. \xed\x94\x84\xeb\xa6\xac\xec\x85\x8b \xeb\xa1\x9c\xeb\x93\x9c \xec\x8b\x9c \xeb\xb3\xb5\xec\x9b\x90\xeb\x90\xa8." },
	};
#endif // WITH_METADATA

// ********** Begin Class UTODPresetData constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_TOD_DataArray_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TOD_DataArray;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurveInterpModes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UTODPresetData constinit property declarations *****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTODPresetData>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UTODPresetData_Statics

// ********** Begin Class UTODPresetData Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODPresetData_Statics::NewProp_TOD_DataArray_Inner = { "TOD_DataArray", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTODMasterData, METADATA_PARAMS(0, nullptr) }; // 1494437275
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UTODPresetData_Statics::NewProp_TOD_DataArray = { "TOD_DataArray", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODPresetData, TOD_DataArray), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TOD_DataArray_MetaData), NewProp_TOD_DataArray_MetaData) }; // 1494437275
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTODPresetData_Statics::NewProp_CurveInterpModes = { "CurveInterpModes", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTODPresetData, CurveInterpModes), Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurveInterpModes_MetaData), NewProp_CurveInterpModes_MetaData) }; // 2504436887
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTODPresetData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODPresetData_Statics::NewProp_TOD_DataArray_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODPresetData_Statics::NewProp_TOD_DataArray,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTODPresetData_Statics::NewProp_CurveInterpModes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTODPresetData_Statics::PropPointers) < 2048);
// ********** End Class UTODPresetData Property Definitions ****************************************
UObject* (*const Z_Construct_UClass_UTODPresetData_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluid_TOD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTODPresetData_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTODPresetData_Statics::ClassParams = {
	&UTODPresetData::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UTODPresetData_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UTODPresetData_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTODPresetData_Statics::Class_MetaDataParams), Z_Construct_UClass_UTODPresetData_Statics::Class_MetaDataParams)
};
void UTODPresetData::StaticRegisterNativesUTODPresetData()
{
}
UClass* Z_Construct_UClass_UTODPresetData()
{
	if (!Z_Registration_Info_UClass_UTODPresetData.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTODPresetData.OuterSingleton, Z_Construct_UClass_UTODPresetData_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTODPresetData.OuterSingleton;
}
UTODPresetData::UTODPresetData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UTODPresetData);
UTODPresetData::~UTODPresetData() {}
// ********** End Class UTODPresetData *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ETODState_StaticEnum, TEXT("ETODState"), &Z_Registration_Info_UEnum_ETODState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2526692313U) },
		{ ETODSeason_StaticEnum, TEXT("ETODSeason"), &Z_Registration_Info_UEnum_ETODSeason, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3176123401U) },
		{ ETODDirectionalLightType_StaticEnum, TEXT("ETODDirectionalLightType"), &Z_Registration_Info_UEnum_ETODDirectionalLightType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 734095136U) },
		{ ETODComponentCategory_StaticEnum, TEXT("ETODComponentCategory"), &Z_Registration_Info_UEnum_ETODComponentCategory, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3871998882U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTODTimePoint::StaticStruct, Z_Construct_UScriptStruct_FTODTimePoint_Statics::NewStructOps, TEXT("TODTimePoint"),&Z_Registration_Info_UScriptStruct_FTODTimePoint, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODTimePoint), 3289068517U) },
		{ FTODSunMoonSettings::StaticStruct, Z_Construct_UScriptStruct_FTODSunMoonSettings_Statics::NewStructOps, TEXT("TODSunMoonSettings"),&Z_Registration_Info_UScriptStruct_FTODSunMoonSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODSunMoonSettings), 216167566U) },
		{ FTODMoonSettings::StaticStruct, Z_Construct_UScriptStruct_FTODMoonSettings_Statics::NewStructOps, TEXT("TODMoonSettings"),&Z_Registration_Info_UScriptStruct_FTODMoonSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODMoonSettings), 2446821375U) },
		{ FTODSkyLightSettings::StaticStruct, Z_Construct_UScriptStruct_FTODSkyLightSettings_Statics::NewStructOps, TEXT("TODSkyLightSettings"),&Z_Registration_Info_UScriptStruct_FTODSkyLightSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODSkyLightSettings), 3156703963U) },
		{ FTODFogSettings::StaticStruct, Z_Construct_UScriptStruct_FTODFogSettings_Statics::NewStructOps, TEXT("TODFogSettings"),&Z_Registration_Info_UScriptStruct_FTODFogSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODFogSettings), 194493249U) },
		{ FTODSkyAtmosphereSettings::StaticStruct, Z_Construct_UScriptStruct_FTODSkyAtmosphereSettings_Statics::NewStructOps, TEXT("TODSkyAtmosphereSettings"),&Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODSkyAtmosphereSettings), 3171145136U) },
		{ FTODMasterData::StaticStruct, Z_Construct_UScriptStruct_FTODMasterData_Statics::NewStructOps, TEXT("TODMasterData"),&Z_Registration_Info_UScriptStruct_FTODMasterData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODMasterData), 1494437275U) },
		{ FTODSunCurveData::StaticStruct, Z_Construct_UScriptStruct_FTODSunCurveData_Statics::NewStructOps, TEXT("TODSunCurveData"),&Z_Registration_Info_UScriptStruct_FTODSunCurveData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODSunCurveData), 1103826936U) },
		{ FTODMoonCurveData::StaticStruct, Z_Construct_UScriptStruct_FTODMoonCurveData_Statics::NewStructOps, TEXT("TODMoonCurveData"),&Z_Registration_Info_UScriptStruct_FTODMoonCurveData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODMoonCurveData), 1856334401U) },
		{ FTODSkyLightCurveData::StaticStruct, Z_Construct_UScriptStruct_FTODSkyLightCurveData_Statics::NewStructOps, TEXT("TODSkyLightCurveData"),&Z_Registration_Info_UScriptStruct_FTODSkyLightCurveData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODSkyLightCurveData), 2405587168U) },
		{ FTODFogCurveData::StaticStruct, Z_Construct_UScriptStruct_FTODFogCurveData_Statics::NewStructOps, TEXT("TODFogCurveData"),&Z_Registration_Info_UScriptStruct_FTODFogCurveData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODFogCurveData), 2440446943U) },
		{ FTODSkyAtmosphereCurveData::StaticStruct, Z_Construct_UScriptStruct_FTODSkyAtmosphereCurveData_Statics::NewStructOps, TEXT("TODSkyAtmosphereCurveData"),&Z_Registration_Info_UScriptStruct_FTODSkyAtmosphereCurveData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODSkyAtmosphereCurveData), 3775039494U) },
		{ FTODCurveKeyMode::StaticStruct, Z_Construct_UScriptStruct_FTODCurveKeyMode_Statics::NewStructOps, TEXT("TODCurveKeyMode"),&Z_Registration_Info_UScriptStruct_FTODCurveKeyMode, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODCurveKeyMode), 133544755U) },
		{ FTODSingleCurveModeList::StaticStruct, Z_Construct_UScriptStruct_FTODSingleCurveModeList_Statics::NewStructOps, TEXT("TODSingleCurveModeList"),&Z_Registration_Info_UScriptStruct_FTODSingleCurveModeList, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODSingleCurveModeList), 1247844576U) },
		{ FTODCurveDataModeSnapshot::StaticStruct, Z_Construct_UScriptStruct_FTODCurveDataModeSnapshot_Statics::NewStructOps, TEXT("TODCurveDataModeSnapshot"),&Z_Registration_Info_UScriptStruct_FTODCurveDataModeSnapshot, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTODCurveDataModeSnapshot), 2504436887U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTOD_Types, UTOD_Types::StaticClass, TEXT("UTOD_Types"), &Z_Registration_Info_UClass_UTOD_Types, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTOD_Types), 4251130632U) },
		{ Z_Construct_UClass_UTODSinglePreset, UTODSinglePreset::StaticClass, TEXT("UTODSinglePreset"), &Z_Registration_Info_UClass_UTODSinglePreset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTODSinglePreset), 4207087516U) },
		{ Z_Construct_UClass_UTODPresetData, UTODPresetData::StaticClass, TEXT("UTODPresetData"), &Z_Registration_Info_UClass_UTODPresetData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTODPresetData), 3680208432U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_860819625{
	TEXT("/Script/Fluid_TOD"),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_laeum_Documents_GitHub_FluidTOD_Packaged_Fluid_TOD_HostProject_Plugins_Fluid_TOD_Source_Fluid_TOD_Public_TOD_Types_h__Script_Fluid_TOD_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
