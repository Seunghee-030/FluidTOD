// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFluid_TOD_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	FLUID_TOD_API UFunction* Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Fluid_TOD;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Fluid_TOD()
	{
		if (!Z_Registration_Info_UPackage__Script_Fluid_TOD.OuterSingleton)
		{
		static UObject* (*const SingletonFuncArray[])() = {
			(UObject* (*)())Z_Construct_UDelegateFunction_Fluid_TOD_OnTODDataChangedSignature__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/Fluid_TOD",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x59F347C2,
			0x819B599C,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Fluid_TOD.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_Fluid_TOD.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Fluid_TOD(Z_Construct_UPackage__Script_Fluid_TOD, TEXT("/Script/Fluid_TOD"), Z_Registration_Info_UPackage__Script_Fluid_TOD, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x59F347C2, 0x819B599C));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
