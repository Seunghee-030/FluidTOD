#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Components/StaticMeshComponent.h"

#include "TOD_Types.h"
#include "TODCurveEvaluator.h"
#include "TODEditor.h"
#include "TODSystem.h"
#include "TODManager.generated.h"

class UMaterialInstanceDynamic;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTODDataChangedSignature);

UCLASS(BlueprintType)
class FLUID_TOD_API ATODManager : public AActor
{
    GENERATED_BODY()

public:
    ATODManager();

    // =========================================================================
    // Events / Delegates
    // =========================================================================

    UPROPERTY(BlueprintAssignable, Category = "TOD|Events")
    FOnTODDataChangedSignature OnTODDataChanged;

    UFUNCTION(BlueprintImplementableEvent, Category = "TOD|Events")
    void OnUpdateCustomMaterials(float CurrentTime);

public:
    UFUNCTION()
    void OnCinematicStarted();

    UFUNCTION()
    void OnCinematicFinished();

    // =========================================================================
	// Sequence Override
    // =========================================================================
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "TOD|Sequencer")
    bool bSequencerOverride = false;

    UFUNCTION(BlueprintCallable, Category = "TOD|Sequencer")
    void SetSequencerOverride(bool bIsOverride);

    // =========================================================================
    // Components
    // =========================================================================
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UPostProcessComponent> RuntimePPVComponent;

    UPROPERTY()
    TObjectPtr<class UDirectionalLightComponent> SunLightComponent;

    UPROPERTY()
    TObjectPtr<class UDirectionalLightComponent> MoonLightComponent;

    UPROPERTY()
    TObjectPtr<class USkyLightComponent> SkyLightComponent;

    UPROPERTY()
    TObjectPtr<class UExponentialHeightFogComponent> FogComponent;

    UPROPERTY()
    TObjectPtr<class USkyAtmosphereComponent> SkyAtmosphereComponent;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Material")
    TObjectPtr<UStaticMeshComponent> SkyDomeMesh;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Material")
    TObjectPtr<UStaticMeshComponent> MoonMesh;

    UPROPERTY(BlueprintReadWrite, Category = "TOD|Material")
    TObjectPtr<UMaterialInstanceDynamic> MoonMaterialInstance;

    UPROPERTY(BlueprintReadWrite, Category = "TOD|Material")
    TObjectPtr<UMaterialInstanceDynamic> SkyMaterialInstance;

    UFUNCTION(BlueprintCallable, Category = "TOD|Material")
    void SetMaterialScalarByName(FName ParameterName, float Value, bool bSkyDome);

    UFUNCTION(BlueprintCallable, Category = "TOD|Material")
    void SetMaterialVectorByName(FName ParameterName, FLinearColor Value, bool bSkyDome);

    // =========================================================================
    // Properties: TOD Base Settings
    // =========================================================================

    UPROPERTY(VisibleAnywhere, Category = "TOD",
        meta = (DisplayPriority = "1", ToolTip = "Read-only display of the configured start time."))
    FString StartTimeDisplay = TEXT("[ 12 : 00 ]");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
        meta = (UIMin = "0.0", UIMax = "24.0", ClampMin = "0.0", ClampMax = "24.0",
            DisplayPriority = "2", ToolTip = "Initial time of day when the game starts."))
    float StartTime = 12.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
        meta = (DisplayPriority = "3", TitleProperty = "Name",
            ToolTip = "TOD Data array containing all time-of-day settings."))
    TArray<FTODMasterData> TOD_DataArray;

    // =========================================================================
    // Properties: Speed
    // =========================================================================
public:
    UFUNCTION(BlueprintCallable, Category = "TOD|Time")
    float CalculateCycleSpeed(float InTime);

protected:
    UPROPERTY(BlueprintReadWrite, Category = "TOD|Speed", meta = (AllowPrivateAccess = "true", Tooltip = "Reference to the player character to track movement state."))
    TObjectPtr<class ACharacter> PlayerRef;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Speed", meta = (Tooltip = "Time multiplier when the player is moving.", ClampMin = "0.1", ClampMax = "50.0"))
    float ActiveDaySpeed = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Speed", meta = (Tooltip = "Time multiplier when the player is idle.", ClampMin = "0.0", ClampMax = "50.0"))
    float IdleDaySpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Speed", meta = (Tooltip = "Interpolation speed. \nHigher values make the transition faster\nLower values make the transition smoother.", ClampMin = "0.01", UIMax = "10.0"))
    float InterpSpeed = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Speed", meta = (Tooltip = "Total duration of one full day cycle in minutes.", ClampMin = "0.1", ClampMax = "360.0", Units = "min"))
    float DayCycleDuration = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Speed", meta = (Tooltip = "Custom curve to modulate speed over the 24-hour cycle."))
    FRuntimeFloatCurve CycleSpeedCurve;

private:
    float TargetSpeed = 0.0f;
    float CurrentSpeed = 1.0f;

    // =========================================================================
    // Properties: State
    // =========================================================================
public:
    float CurrentSystemTime = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD|Geography")
    ETODState CurrentState;

    UPROPERTY()
    float TransitionDuration = 1.0f;

    // =========================================================================
    // Properties: Geography
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Geography",
        meta = (ClampMin = "-90.0", ClampMax = "90.0", UIMin = "-60.0", UIMax = "60.0",
            ToolTip = "Controls sunrise/sunset timing. Artistic setting, not physically accurate."))
    float Latitude = 45.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Geography")
    float Longitude = 127.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Geography")
    float CalculatedSunriseTime = 6.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Geography")
    float CalculatedSunsetTime = 18.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD|Geography",
        meta = (ToolTip = "Calculated sunrise time based on the current latitude setting."))
    FString SunriseTime = TEXT("[ 06 : 00 ]");

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD|Geography",
        meta = (ToolTip = "Calculated sunset time based on the current latitude setting."))
    FString SunsetTime = TEXT("[ 18 : 00 ]");

    // =========================================================================
    // Properties: Curves
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Curves")
    FTODSunCurveData SunCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Curves")
    FTODMoonCurveData MoonCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Curves")
    FTODSkyLightCurveData SkyLightCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Curves")
    FTODFogCurveData FogCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Curves")
    FTODSkyAtmosphereCurveData SkyAtmosphereCurves;

    // =========================================================================
    // Properties: Visual Overrides
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Texture")
    bool bOverrideMoonSourceScale = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Texture",
        meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))
    float OverriddenMoonSourceScale = 0.5f;

    // =========================================================================
    // Properties: Preset
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Preset")
    TObjectPtr<UTODPresetData> LoadPreset;

    // =========================================================================
    // Properties: Debug
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Debug",
        meta = (ToolTip = "Enables on-screen debug information for the TOD system."))
    bool bEnableDebugPrint = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Debug",
        meta = (EditCondition = "bEnableDebugPrint", ClampMin = "0.1", UIMin = "0.1",
            ToolTip = "Interval in seconds between debug updates."))
    float DebugPrintInterval = 1.0f;

    // =========================================================================
    // Functions: System
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Cinematic")
    bool bIsCinematicOverride = false;

    UFUNCTION(BlueprintCallable, Category = "TOD|Cinematic")
    void SetCinematicMode(bool bEnable) { bIsCinematicOverride = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "TOD|System")
    void BakeTODCurves();

    UFUNCTION(BlueprintCallable, Category = "TOD|System")
    void UpdateTOD(float CurrentTime);

    void GetTODSettingsAtTime(
        float InTime,
        FTODSunMoonSettings& OutSun,
        FTODMoonSettings& OutMoon,
        FTODSkyLightSettings& OutSkyLight,
        FTODFogSettings& OutFog,
        FTODSkyAtmosphereSettings& OutSkyAtmosphere);

    void ApplyPPVBlending(float CurrentTime);
    void FindComponents();
    void SortTODDataArray();

    // =========================================================================
    // Functions: Geography
    // =========================================================================

    UFUNCTION(BlueprintCallable, Category = "TOD|Geography")
    void UpdateSunTimes();

    UFUNCTION(BlueprintPure, Category = "TOD|Geography")
    FRotator CalculatePivotRotation(float InTime) const;

    // =========================================================================
    // Functions: Preset
    // =========================================================================

    UFUNCTION(BlueprintCallable, Category = "TOD|Preset")
    void SaveNewPreset();

    UFUNCTION(BlueprintCallable, Category = "TOD|Preset")
    void SaveCurrentPreset();

    UFUNCTION(BlueprintCallable, Category = "TOD|Preset")
    void OpenPresetDialog();

    UFUNCTION(BlueprintCallable, Category = "TOD|Preset")
    void LoadSelectedPreset();

    // =========================================================================
    // Functions: Editor & Helper
    // =========================================================================

    UFUNCTION(BlueprintCallable, Category = "TOD|Editor")
    void ForceViewportRedraw();

    UFUNCTION(BlueprintPure, Category = "TOD|Helper")
    FString GetFormattedTimeAsString(float InTime) const;

protected:
    virtual void BeginPlay() override;

private:
    FTODCurveEvaluator CurveEvaluator;
    FTODEditor EditorModule;
    FTODSystem TODSystem;
    FTimerHandle DebugTimerHandle;

    UFUNCTION()
    void PrintTODDebugInfo();

#if WITH_EDITOR
protected:
    virtual void PostInitProperties() override;
    virtual void BeginDestroy() override;
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void PostEditMove(bool bFinished) override;

private:
    void OnExternalPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
    FDelegateHandle PropertyChangeDelegateHandle;
#endif
};