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

// 사용자지정 시간 범위 구조체
USTRUCT(BlueprintType)
struct FTODTimePoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	ETODState State = ETODState::Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float StartTime = 0.0f;
};
USTRUCT(BlueprintType)
struct FTODSunMoonSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "1", ClampMin = "0.0", UIMin = "0.0"))
	float Intensity = 8000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "2", ClampMin = "0.0", UIMin = "0.0", UIMax = "20.0"))
	float Source_Angle = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "3", ClampMin = "0.0", UIMin = "0.0", UIMax = "20.0"))
	float Source_Soft_Angle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "4", ClampMin = "0.0", UIMin = "0.0"))
	float Indirect_Light_Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "5"))
	FLinearColor Light_Color = FLinearColor::White;
};

USTRUCT(BlueprintType)
struct FTODMoonSettings : public FTODSunMoonSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "10", ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))
	float Moon_Source_Scale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (DisplayPriority = "11", ClampMin = "0.0", UIMin = "0.0"))
	float Moon_Source_Emissive_Intensity = 1.0f;
};

USTRUCT(BlueprintType)
struct FTODSkyLightSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Sky_Light_Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Sky_Light_Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Sky_Indirect_Lighting_Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Sky_Volumetric_Scattering_Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SkyDome_Texture_Emissive_Intensity = 1.0f;
};

USTRUCT(BlueprintType)
struct FTODFogSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Fog_Density = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Mie_Scattering_Scale = 0.003996f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Mie_Scattering_Color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 대기 흡수 (필터 효과, 오존)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD")
	FLinearColor Absorption_Color = FLinearColor(0.345561f, 1.000000f, 0.045189f, 531.632080f);

	// 레일리 산란 (기본 하늘 톤)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Rayleigh_Scattering_Scale = 0.0331f;

	// 공기 원근법 (거리에 따른 포그화 강도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", UIMin = "0.0"))
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
		meta = (ClampMin = "0.0", ClampMax = "24.0",
			UIMin = "0.0", UIMax = "24.0"))
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

// 커브 키 1개의 시간+보간모드 (프리셋 저장/리베이크 보존용, UI에는 노출 안 함)
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

// CurveData 전체(float 18개 + color 8개×4채널)의 InterpMode 스냅샷.
// FTODCurveEvaluator::GetAllFloatCurves() / GetAllColorCurves()와 동일한 순서로 저장됨.
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

	// 저장 시점 커브의 키별 Interpolation 모드 스냅샷. 프리셋 로드 시 복원됨.
	UPROPERTY()
	FTODCurveDataModeSnapshot CurveInterpModes;
};