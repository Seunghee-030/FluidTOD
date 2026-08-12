#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Components/StaticMeshComponent.h"

#include "TOD_Types.h"
#include "TODCurveContainer.h"
#include "TODCurveEvaluator.h"
#include "TODEditor.h"
#include "TODSystem.h"
#include "TODManager.generated.h"

class UMaterialInstanceDynamic;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTODDataChangedSignature);

// 시퀀서별 TOD 제어 옵션 설정 구조체
USTRUCT(BlueprintType)
struct FTODCinematicSetting
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
    TObjectPtr<class ALevelSequenceActor> SequenceActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic", meta = (Tooltip = "Pauses TOD time progression during sequence playback."))
    bool bPauseTime = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic", meta = (Tooltip = "Stops TOD visual updates to allow sequence-based overrides."))
    bool bOverrideVisuals = true;
};

UCLASS(BlueprintType, meta = (HideFunctions = "SetStartTime, SetTOD_State"))
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

    // =========================================================================
    // Sequence Override
    // =========================================================================
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Sequencer")
    TArray<FTODCinematicSetting> TargetCinematics;

    bool bIsTimePaused = false;
    bool bIsVisualOverridden = false;

public:
    UFUNCTION()
    void EvaluateCinematicState();

    bool IsVisualOverridden() const { return bIsVisualOverridden; }
    bool IsTimePaused() const { return bIsTimePaused; }

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

    UPROPERTY()
    TObjectPtr<class USceneComponent> PivotOrbitTiltComponent;

    UPROPERTY()
    TObjectPtr<class USceneComponent> PivotSunMoonComponent;

    UPROPERTY()
    TObjectPtr<class USceneComponent> MeshPivotComponent;

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
public:
    UPROPERTY(VisibleAnywhere, Category = "TOD",
        meta = (DisplayPriority = "1", ToolTip = "Read-only display of the configured start time."))
    FString StartTimeDisplay = TEXT("[ 12 : 00 ]");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
        meta = (UIMin = "0.0", UIMax = "24.0",
            DisplayPriority = "2", NonInterp, ToolTip = "Initial time of day when the game starts. 0-24"))
    float StartTime = 12.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD",
        meta = (DisplayPriority = "3", TitleProperty = "Name",
            ToolTip = "TOD Data array containing all time-of-day settings."))
    TArray<FTODMasterData> TOD_DataArray;

    // =========================================================================
    // Properties: Speed, Time, and Cycle
    // =========================================================================
public:
    float CurrentSystemTime = 0.0f;

    UFUNCTION(BlueprintPure, Category = "TOD|Time")
    float GetStartTime() const;

    UFUNCTION(BlueprintCallable, Category = "TOD|Time")
    void SetStartTime(float NewTime);

    UFUNCTION(BlueprintPure, Category = "TOD|Time")
    float GetCurrentTime() const;

    UFUNCTION(BlueprintCallable, Category = "TOD|Time")
    void SetCurrentTime(float NewTime);

    UFUNCTION(BlueprintCallable, Category = "TOD|Time")
    float CalculateCycleSpeed(float InTime);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|State Setting", meta = (TitleProperty = "State", NonInterp))
    TArray<FTODTimePoint> TOD_State;

    UFUNCTION(BlueprintPure, Category = "TOD|Time")
    ETODState GetCurrentTODState(float InTime) const;

    UFUNCTION(BlueprintPure, Category = "TOD|Time")
    bool IsTimeInState(float InTime, ETODState TargetState) const;
    
	// =========================================================================
	// Properties: PIE console Control
	// =========================================================================
  public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Time")
    float TimeDirection = 1.0f; // 1: 정방향, -1: 역방향

    UFUNCTION(BlueprintCallable, Category = "TOD|Time")
    void ToggleTimeDirection() { TimeDirection *= -1.0f; }

    UFUNCTION(BlueprintCallable, Category = "TOD|Time")
    void ToggleTimePause() { bIsTimePaused = !bIsTimePaused; }
    UFUNCTION(BlueprintPure, Category = "TOD|Debug")
    FString GetFullDebugDumpString() const;

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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD|Geography")
    ETODState CurrentState;

    UPROPERTY()
    float TransitionDuration = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD|Geography",
        meta = (ToolTip = "크로스페이드 시작 시점의 이전 상태. CurrentState로 전환되는 중이라면 이 상태에서 블렌드되어 온다."))
    ETODState PreviousState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD|Geography",
        meta = (ToolTip = "PreviousState -> CurrentState 전환 진행률. 0=PreviousState 방금 벗어남, 1=CurrentState로 완전 전환됨."))
    float StateBlendAlpha = 1.0f;

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

    FRotator MoonLocalRotationOffset = FRotator(0.0f, 180.0f, 0.0f);
    float SunLatitudeTiltMultiplier = -1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Geography",
        meta = (ToolTip = "Keeps the sun/moon pivot centered on the camera so distant light and mesh stay aligned (removes parallax)."))
    bool bFollowCameraPosition = true;

    UFUNCTION(BlueprintCallable, Category = "TOD|Geography")
    void UpdateSkyAnchorPosition();
    // =========================================================================
    // Properties: Moon
    // =========================================================================
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Moon",
        meta = (ClampMin = "0.0", UIMin = "0.0", ToolTip = "Reference mesh radius distance for Moon."))
    float MoonDistance = 50000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Moon",
        meta = (ToolTip = "Auto-scale MoonDistance based on Moon Mesh bounding size."))
    bool bAutoScaleMoonDistanceByMeshSize = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Moon",
        meta = (EditCondition = "bAutoScaleMoonDistanceByMeshSize", ClampMin = "1.0",
            ToolTip = "Reference mesh radius (uu) that MoonDistance corresponds to."))
    float MoonMeshReferenceRadius = 100.0f;

    UFUNCTION(BlueprintPure, Category = "TOD|Moon")
    float GetCalculatedMoonScale(float InTime) const;

    UFUNCTION(BlueprintCallable, Category = "TOD|Moon")
    void UpdateMoonMeshTransform();

private:
    float GetScaledMoonDistance() const;

    // =========================================================================
    // Properties: Curves
    // =========================================================================
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "TOD_Curves")
    TObjectPtr<UTODCurveContainer> CurveData;

    // =========================================================================
    // Properties: Visual Overrides
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Texture")
    bool bOverrideMoonSourceScale = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Texture",
        meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))
    float OverriddenMoonSourceScale = 0.5f;

    // =========================================================================
    // Properties: PPV Compensation
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|PPV Compensation",
        meta = (ToolTip = "Time-of-day exposure compensation. Added to the blended PPV's AutoExposureBias."))
    FRuntimeFloatCurve PPV_ExposureCompensationCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|PPV Compensation",
        meta = (ToolTip = "Time-of-day brightness compensation. Applied as a multiplier to the blended PPV's BloomIntensity."))
    FRuntimeFloatCurve PPV_BrightnessCompensationCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|PPV Compensation",
        meta = (ToolTip = "Time-of-day color temperature compensation (Kelvin). Added to the blended PPV's WhiteTemp."))
    FRuntimeFloatCurve PPV_WhiteTempCompensationCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|PPV Compensation",
        meta = (ToolTip = "Time-of-day color grading compensation. Applied as an RGBA multiplier to the blended PPV's ColorSaturation."))
    FRuntimeCurveLinearColor PPV_ColorGradingCompensationCurve;

    // =========================================================================
    // Properties: Preset
    // =========================================================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Preset")
    TObjectPtr<UTODPresetData> LoadPreset;

    bool bApplyPresetCurveModesOnNextBake = false;

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

    // getter for print debug info
    UFUNCTION(BlueprintPure, Category = "TOD|Moon")
    float GetMoonSourceScaleAtTime(float InTime) const;

    UFUNCTION(BlueprintPure, Category = "TOD|Moon")
    float GetMoonIntensity(float InTime) const;

    UFUNCTION(BlueprintPure, Category = "TOD|Sun")
    float GetSunIntensity(float InTime) const;

    UFUNCTION(BlueprintPure, Category = "TOD|Speed")
    float GetFinalSpeed(float InTime);

    UFUNCTION(BlueprintCallable, Category = "TOD|Geography")
    void UpdatePivotRotation(float InTime);

    void ApplyPPVBlending(float CurrentTime);
    void FindComponents();
    void SortTODDataArray();

    // =========================================================================
    // Functions: Geography
    // =========================================================================

    UFUNCTION(BlueprintCallable, Category = "TOD|Geography")
    void UpdateSunTimes();

    UFUNCTION(BlueprintCallable, Category = "TOD|Geography")
    FQuat CalculatePivotRotation(float InTime) const;

    // =========================================================================
    // Functions: Preset
    // =========================================================================

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "TOD|Preset")
    void SaveNewPreset();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "TOD|Preset")
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
    virtual void Tick(float DeltaSeconds) override;

private:
    FTODCurveEvaluator CurveEvaluator;
    FTODEditor EditorModule;
    FTODSystem TODSystem;
    FTimerHandle DebugTimerHandle;

    void ApplyStaticSunMoonOffsets();

    UFUNCTION()
    void PrintTODDebugInfo();

    // StartTime이 0~24 범위를 벗어나면 순환(wrap)시켜 되돌린다.
    static float WrapStartTime(float InTime);

#if WITH_EDITOR
protected:
    virtual void PostInitProperties() override;
    virtual void BeginDestroy() override;
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
    virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void PostEditMove(bool bFinished) override;

private:
    void OnExternalPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
    FDelegateHandle PropertyChangeDelegateHandle;

    bool bPendingPPVUpdate = false;

    // 프레임당 1회로 묶어서 실행하기 위한 디바운스 플래그
    bool bRebakeRequested = false;
    void RequestDeferredRebake();

    // TOD_DataArray의 Time 필드가 바뀌기 직전 상태를 캐시
    TArray<FTODMasterData> PreEditTOD_DataArray;
#endif
};