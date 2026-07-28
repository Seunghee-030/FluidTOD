#pragma once

#include "CoreMinimal.h"
#include "TOD_Types.h"
#include "TODCurveContainer.generated.h"

// TOD 커브 5종을 하나로 묶는 컨테이너.
UCLASS(EditInlineNew, DefaultToInstanced, BlueprintType)
class FLUID_TOD_API UTODCurveContainer : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Sun Curves")
	FTODSunCurveData SunCurves;

	UPROPERTY(VisibleAnywhere, Category = "Moon Curves")
	FTODMoonCurveData MoonCurves;

	UPROPERTY(VisibleAnywhere, Category = "SkyLight Curves")
	FTODSkyLightCurveData SkyLightCurves;

	UPROPERTY(VisibleAnywhere, Category = "Fog Curves")
	FTODFogCurveData FogCurves;

	UPROPERTY(VisibleAnywhere, Category = "SkyAtmosphere Curves")
	FTODSkyAtmosphereCurveData SkyAtmosphereCurves;
};