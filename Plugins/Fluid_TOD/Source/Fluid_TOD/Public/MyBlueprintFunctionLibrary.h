#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/PostProcessVolume.h"
#include "Components/PostProcessComponent.h"
#include "TOD_Types.h"
#include "MyBlueprintFunctionLibrary.generated.h"

UCLASS()
class FLUID_TOD_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Curve Control
	UFUNCTION(BlueprintCallable, Category = "TOD|Curve")
	static void ClearRuntimeFloatCurve(UPARAM(ref) FRuntimeFloatCurve& InCurve);

	UFUNCTION(BlueprintCallable, Category = "TOD|Curve")
	static void AddKeyToRuntimeFloatCurve(UPARAM(ref) FRuntimeFloatCurve& InCurve, float InTime, float InValue, ERichCurveInterpMode InterpMode = RCIM_Linear);

	UFUNCTION(BlueprintCallable, Category = "TOD|Curve")
	static void ClearRuntimeColorCurve(UPARAM(ref) FRuntimeCurveLinearColor& InCurve);

	UFUNCTION(BlueprintCallable, Category = "TOD|Curve")
	static void AddKeyToRuntimeColorCurve(UPARAM(ref) FRuntimeCurveLinearColor& InCurve, float InTime, FLinearColor InColor, ERichCurveInterpMode InterpMode = RCIM_Linear);

	UFUNCTION(BlueprintPure, Category = "TOD|Curve")
	static FLinearColor GetRuntimeColorCurveValue(const FRuntimeCurveLinearColor& InCurve, float InTime);

	// Auto-Seal
	UFUNCTION(BlueprintCallable, Category = "TOD|Curve")
	static void SealTODCurveFor24Hours(UPARAM(ref) FRuntimeFloatCurve& InCurve);

	UFUNCTION(BlueprintCallable, Category = "TOD|Curve")
	static void SealColorCurveFor24Hours(UPARAM(ref) FRuntimeCurveLinearColor& InCurve);
};