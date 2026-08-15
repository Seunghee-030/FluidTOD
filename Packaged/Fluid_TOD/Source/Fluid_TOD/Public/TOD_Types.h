#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/DataAsset.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "TOD_Types.generated.h"

UENUM(BlueprintType)
enum class ETODState : uint8
{
	Day         UMETA(DisplayName = "Day"),
	Night       UMETA(DisplayName = "Night"),
	Dawn  UMETA(DisplayName = "Dawn"),
	Sunrise  UMETA(DisplayName = "Sunrise"),
	Dusk  UMETA(DisplayName = "Dusk"),
	Sunset  UMETA(DisplayName = "Sunset"),
};

// 계절
UENUM(BlueprintType)
enum class ETODSeason : uint8
{
	Spring   UMETA(DisplayName = "Spring"),
	Summer   UMETA(DisplayName = "Summer"),
	Autumn   UMETA(DisplayName = "Fall"),
	Winter   UMETA(DisplayName = "Winter"),
};

// 사용할 빛 종류 선택 (Sun/Moon/Transition)
UENUM(BlueprintType)
enum class ETODDirectionalLightType : uint8
{
	SunOnly         UMETA(DisplayName = "Sun"),
	MoonOnly       UMETA(DisplayName = "Moon"),
	Transition  UMETA(DisplayName = "Sun&Moon")
};

// EUW용 컴포넌트 카테고리
UENUM(BlueprintType)
enum class ETODComponentCategory : uint8
{
	All                   UMETA(DisplayName = "All"),
	Sun					  UMETA(DisplayName = "Sun"),
	Moon				  UMETA(DisplayName = "Moon"),
	SkyLight              UMETA(DisplayName = "SkyLight"),
	ExponentialHeightFog  UMETA(DisplayName = "ExponentialHeightFog"),
	SkyAtmosphere         UMETA(DisplayName = "SkyAtmosphere"),
	PostProcessVolume     UMETA(DisplayName = "PostProcessVolume")
};

// 시간대별 TOD 상태를 정의하는 구조체
USTRUCT(BlueprintType)
struct FTODTimePoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	ETODState State = ETODState::Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float StartTime = 0.0f;
};

// Sun Settings
USTRUCT(BlueprintType)
struct FTODSunMoonSettings
{
	GENERATED_BODY()

	// Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "1", ClampMin = "0.0", UIMin = "0.0"))
	float Intensity = 8000.0f;

	// Source Angle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "2", ClampMin = "0.0", UIMin = "0.0", UIMax = "20.0"))
	float Source_Angle = 1.0f;

	// Source Soft Angle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "3", ClampMin = "0.0", UIMin = "0.0", UIMax = "20.0"))
	float Source_Soft_Angle = 0.0f;

	// Indirect Light Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "4", ClampMin = "0.0", UIMin = "0.0"))
	float Indirect_Light_Intensity = 1.0f;

	// Light Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "5"))
	FLinearColor Light_Color = FLinearColor::White;
};

// Moon Settings
USTRUCT(BlueprintType)
struct FTODMoonSettings : public FTODSunMoonSettings
{
	GENERATED_BODY()

	FTODMoonSettings()
	{
		Intensity = 100.0f;
	}

	// Moon Source Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "10", ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))
	float Moon_Source_Scale = 1.0f;

	// Moon Source Emissive Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "11", ClampMin = "0.0", UIMin = "0.0"))
	float Moon_Source_Emissive_Intensity = 1.0f;

	// Moon Glow(Halo) Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "10", ClampMin = "0.0", UIMin = "0.0", UIMax = "500.0"))
	float Moon_Glow_Scale = 0.0f;

	// Moon Glow(Halo) Emissive Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "12", ClampMin = "0.0", UIMin = "0.0"))
	float Moon_Glow_Emissive_Intensity = 1.0f;
};

// Sky Light Settings
USTRUCT(BlueprintType)
struct FTODSkyLightSettings
{
	GENERATED_BODY()

	// Sky Light Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Sky_Light_Intensity = 1.0f;

	// Sky Light Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Sky_Light_Color = FLinearColor::White;

	// Sky Indirect Lighting Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Sky_Indirect_Lighting_Intensity = 1.0f;

	// Sky Volumetric Scattering Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Sky_Volumetric_Scattering_Intensity = 1.0f;

	// Sky Dome Texture Emissive Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SkyDome_Texture_Emissive_Intensity = 0.0f;

	// Sky Dome Stars Emissive Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Star_Emissive_Intensity = 1.0f;
};

// Fog Settings
USTRUCT(BlueprintType)
struct FTODFogSettings
{
	GENERATED_BODY()

	// Fog Density (0~1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Fog_Density = 0.02f;

	// Fog Height Falloff (0~1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Fog_Height_Falloff = 0.2f;

	// Fog Inscattering Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Fog_Inscattering_Color = FLinearColor::White;

	// Fog Directional Inscattering Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Fog_Directional_Inscattering = FLinearColor::Black;
};

// Sky Atmosphere Settings
USTRUCT(BlueprintType)
struct FTODSkyAtmosphereSettings
{
	GENERATED_BODY()

	// Mie Scattering Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Mie_Scattering_Scale = 0.003996f;

	// Mie Scattering Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Mie_Scattering_Color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Mie Absorption Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Absorption_Color = FLinearColor(0.345561f, 1.000000f, 0.045189f, 531.632080f);

	// Rayleigh Scattering Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Rayleigh_Scattering_Scale = 0.0331f;

	// Aerial Perspective Distance Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Aerial_Perspective_Distance_Scale = 1.0f;

	// Sky Luminance Factor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Sky_Luminance_Factor = FLinearColor::White;
};

// =========================================================
// 마스터 구조체
// =========================================================
USTRUCT(BlueprintType)
struct FTODMasterData
{
	GENERATED_BODY()

	// PPV Data Index Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FString Name = TEXT("New Time Slot");

	// Time of Day (0~24)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", ClampMax = "24.0",
			UIMin = "0.0", UIMax = "24.0"))
	float Time = 0.0f;

	// PostProcessVolume Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	TObjectPtr<APostProcessVolume> PPV = nullptr;

	// Select Directional Light ActiveMode (SunOnly/MoonOnly/Transition)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	ETODDirectionalLightType ActiveLightMode = ETODDirectionalLightType::Transition;

	// Sun Settindgs (Active SunOnly or Transition)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (EditCondition = "ActiveLightMode == ETODDirectionalLightType::SunOnly || ActiveLightMode == ETODDirectionalLightType::Transition", EditConditionHides))
	FTODSunMoonSettings Sun_Settings;

	// Moon Settings (Active MoonOnly or Transition)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (EditCondition = "ActiveLightMode == ETODDirectionalLightType::MoonOnly || ActiveLightMode == ETODDirectionalLightType::Transition", EditConditionHides))
	FTODMoonSettings Moon_Settings;

	// SkyLight, Sky Dome Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODSkyLightSettings SkyLight_Settings;

	// Fog Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODFogSettings Fog_Settings;

	// SkyAtmosphere Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODSkyAtmosphereSettings SkyAtmosphere_Settings;
};

// =========================================================
// 커브 구조체
// =========================================================

USTRUCT(BlueprintType)
struct FTODSunCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve IntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve SourceAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve SourceSoftAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve IndirectIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeCurveLinearColor LightColorCurve;
};

USTRUCT(BlueprintType)
struct FTODMoonCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve IntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceSoftAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve IndirectIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeCurveLinearColor LightColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceEmissiveIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve GlowScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve GlowEmissiveIntensityCurve;
};

USTRUCT(BlueprintType)
struct FTODSkyLightCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve IntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve IndirectIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve VolumetricScatteringIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeCurveLinearColor LightColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve TextureEmissiveIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve StarEmissiveIntensityCurve;
};

USTRUCT(BlueprintType)
struct FTODFogCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeFloatCurve DensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeFloatCurve HeightFalloffCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeCurveLinearColor InscatteringColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeCurveLinearColor DirectionalColorCurve;
};

USTRUCT(BlueprintType)
struct FTODSkyAtmosphereCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeFloatCurve MieScatteringScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeFloatCurve RayleighScatteringScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeFloatCurve AerialPerspectiveDistanceScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeCurveLinearColor MieScatteringColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeCurveLinearColor AbsorptionColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeCurveLinearColor SkyLuminanceFactorCurve;
};

// =========================================================
// 커브 프리셋 저장/리베이크 보존, UI 노출 X
// =========================================================
USTRUCT()
struct FTODCurveKeyMode
{
	GENERATED_BODY()

	UPROPERTY()
	float Time = 0.0f;

	UPROPERTY()
	TEnumAsByte<ERichCurveInterpMode> InterpMode = RCIM_Linear;
};

USTRUCT()
struct FTODSingleCurveModeList
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FTODCurveKeyMode> Keys;
};

USTRUCT()
struct FTODCurveDataModeSnapshot
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FTODSingleCurveModeList> FloatCurveModes;

	UPROPERTY()
	TArray<FTODSingleCurveModeList> ColorCurveModes;
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

	UPROPERTY()
	FTODCurveDataModeSnapshot CurveInterpModes;
};