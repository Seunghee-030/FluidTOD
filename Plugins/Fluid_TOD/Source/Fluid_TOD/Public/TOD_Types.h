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

// 사용할 빛 종류 선택 (Sun/Moon/Both)
UENUM(BlueprintType)
enum class ETODDirectionalLightType : uint8
{
	SunOnly         UMETA(DisplayName = "Sun"),
	MoonOnly       UMETA(DisplayName = "Moon"),
	Transition  UMETA(DisplayName = "Sun&Moon")
};

USTRUCT(BlueprintType)
struct FTODSunMoonSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "1"))
	float Intensity = 8000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "2"))
	float Source_Angle = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "3"))
	float Source_Soft_Angle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "4"))
	float Indirect_Light_Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "5"))
	FLinearColor Light_Color = FLinearColor::White;
};

USTRUCT(BlueprintType)
struct FTODMoonSettings : public FTODSunMoonSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "10"))
	float Moon_Source_Scale = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "11"))
	float Moon_Source_Emissive_Intensity = 300.0f;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	float Sky_Texture_Emissive_Intensity = 1.0f;
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

	// 밤,낮,전환기 선택
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	ETODDirectionalLightType ActiveLightMode = ETODDirectionalLightType::SunOnly;

	// Day/Transition 상태일 때만 노출
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (EditCondition = "ActiveLightMode == ETODDirectionalLightType::SunOnly || ActiveLightMode == ETODDirectionalLightType::Transition", EditConditionHides))
	FTODSunMoonSettings Sun_Settings;

	// Night/Transition 상태일 때만 노출
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (EditCondition = "ActiveLightMode == ETODDirectionalLightType::MoonOnly || ActiveLightMode == ETODDirectionalLightType::Transition", EditConditionHides))
	FTODMoonSettings Moon_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODSkyLightSettings SkyLight_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODFogSettings Fog_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FTODSkyAtmosphereSettings SkyAtmosphere_Settings;
};

// 커브 구조체
USTRUCT(BlueprintType)
struct FTODSunCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve IntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") TEnumAsByte<ERichCurveInterpMode> IntensityInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve SourceAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") TEnumAsByte<ERichCurveInterpMode> SourceAngleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve SourceSoftAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") TEnumAsByte<ERichCurveInterpMode> SourceSoftAngleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeFloatCurve IndirectIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") TEnumAsByte<ERichCurveInterpMode> IndirectIntensityInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") FRuntimeCurveLinearColor ColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Curves") TEnumAsByte<ERichCurveInterpMode> ColorInterpMode = RCIM_Linear;
};

USTRUCT(BlueprintType)
struct FTODMoonCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve IntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") TEnumAsByte<ERichCurveInterpMode> IntensityInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") TEnumAsByte<ERichCurveInterpMode> SourceAngleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceSoftAngleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") TEnumAsByte<ERichCurveInterpMode> SourceSoftAngleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve IndirectIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") TEnumAsByte<ERichCurveInterpMode> IndirectIntensityInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeCurveLinearColor LightColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") TEnumAsByte<ERichCurveInterpMode> LightColorInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") TEnumAsByte<ERichCurveInterpMode> SourceScaleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") FRuntimeFloatCurve SourceEmissiveIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon Curves") TEnumAsByte<ERichCurveInterpMode> SourceEmissiveIntensityInterpMode = RCIM_Linear;
};

USTRUCT(BlueprintType)
struct FTODSkyLightCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve IntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") TEnumAsByte<ERichCurveInterpMode> IntensityInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve IndirectIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") TEnumAsByte<ERichCurveInterpMode> IndirectIntensityInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve VolumetricScatteringIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") TEnumAsByte<ERichCurveInterpMode> VolumetricScatteringInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeCurveLinearColor LightColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") TEnumAsByte<ERichCurveInterpMode> LightColorInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") FRuntimeFloatCurve TextureEmissiveIntensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight Curves") TEnumAsByte<ERichCurveInterpMode> TextureEmissiveIntensityInterpMode = RCIM_Linear;
};

USTRUCT(BlueprintType)
struct FTODFogCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeFloatCurve DensityCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") TEnumAsByte<ERichCurveInterpMode> DensityInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeFloatCurve HeightFalloffCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") TEnumAsByte<ERichCurveInterpMode> HeightFalloffInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeCurveLinearColor InscatteringColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") TEnumAsByte<ERichCurveInterpMode> InscatteringColorInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") FRuntimeCurveLinearColor DirectionalColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog Curves") TEnumAsByte<ERichCurveInterpMode> DirectionalColorInterpMode = RCIM_Linear;
};

USTRUCT(BlueprintType)
struct FTODSkyAtmosphereCurveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeFloatCurve MieScatteringScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") TEnumAsByte<ERichCurveInterpMode> MieScatteringScaleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeFloatCurve RayleighScatteringScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") TEnumAsByte<ERichCurveInterpMode> RayleighScatteringScaleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeFloatCurve AerialPerspectiveDistanceScaleCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") TEnumAsByte<ERichCurveInterpMode> AerialPerspectiveDistanceScaleInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeCurveLinearColor MieScatteringColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") TEnumAsByte<ERichCurveInterpMode> MieScatteringColorInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeCurveLinearColor AbsorptionColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") TEnumAsByte<ERichCurveInterpMode> AbsorptionColorInterpMode = RCIM_Linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") FRuntimeCurveLinearColor SkyLuminanceFactorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere Curves") TEnumAsByte<ERichCurveInterpMode> SkyLuminanceFactorInterpMode = RCIM_Linear;
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