#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/DataAsset.h"
#include "TOD_Types.generated.h"

UENUM(BlueprintType)
enum class ETODState : uint8
{
	Day         UMETA(DisplayName = "Day"),
	Night       UMETA(DisplayName = "Night"),
	Transition  UMETA(DisplayName = "Transition (Dawn/Dusk)")
};

USTRUCT(BlueprintType)
struct FTODSunMoonSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Intensity = 8000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float SourceAngle = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float SourceSoftAngle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float IndirectLightingIntensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	bool bVisible = true;
};

USTRUCT(BlueprintType)
struct FTODSkyLightSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Sky_Light_Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Sky_Light_Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Sky_Indirect_Lighting_Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Sky_Volumetric_Scattering_Intensity = 1.0f;
};

USTRUCT(BlueprintType)
struct FTODFogSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Fog_Density = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Fog_Height_Falloff = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Fog_Inscattering_Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Fog_Directional_Inscattering = FLinearColor::Black;
};

USTRUCT(BlueprintType)
struct FTODSkyAtmosphereSettings
{
	GENERATED_BODY()

	// 미 산란 (빛 번짐, 먼지 밀도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Mie_Scattering_Scale = 0.003996f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Mie_Scattering_Color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 대기 흡수 (필터 효과, 오존)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Absorption_Color = FLinearColor(0.345561f, 1.000000f, 0.045189f, 531.632080f);

	// 레일리 산란 (기본 하늘 톤)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Rayleigh_Scattering_Scale = 0.0331f;

	// 공기 원근법 (거리에 따른 포그화 강도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Aerial_Perspective_Distance_Scale = 1.0f;

	// 산란광 제어
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Sky_Luminance_Factor = FLinearColor::White;
};

// 마스터 구조체
USTRUCT(BlueprintType)
struct FTODMasterData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FString Name = TEXT("New Time Slot");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Time = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	TObjectPtr<APostProcessVolume> PPV = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODSunMoonSettings SunMoon_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODSkyLightSettings SkyLight_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODFogSettings Fog_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODSkyAtmosphereSettings SkyAtmosphere_Settings;
};

UCLASS()
class FLUID_TOD_API UTOD_Types : public UObject
{
	GENERATED_BODY()
};

UCLASS(BlueprintType)
class FLUID_TOD_API UTODSinglePreset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODMasterData SavedData;
};

UCLASS(BlueprintType)
class FLUID_TOD_API UTODPresetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	TArray<FTODMasterData> TOD_DataArray;
};