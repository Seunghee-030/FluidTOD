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

class UMaterialInstanceDynamic;   // MID

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

    // EUW 용 디스패쳐 선언
    UPROPERTY(BlueprintAssignable, Category = "TOD|Events")
    FOnTODDataChangedSignature OnTODDataChanged;

    //  Material 이벤트
    UFUNCTION(BlueprintImplementableEvent, Category = "TOD|Events")
    void OnUpdateCustomMaterials(float CurrentTime);

    // =========================================================================
    // Components & Classes
    // =========================================================================

    // Class
    UPROPERTY()
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

    // Mesh Components
    UPROPERTY(BlueprintReadOnly, Category = "TOD|Material")
    TObjectPtr<UStaticMeshComponent> SkyDomeMesh;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Material")
    TObjectPtr<UStaticMeshComponent> MoonMesh;

	// Material Instances
    UPROPERTY(BlueprintReadWrite, Category = "TOD|Material")
    TObjectPtr<UMaterialInstanceDynamic> MoonMaterialInstance;

    UPROPERTY(BlueprintReadWrite, Category = "TOD|Material")
    TObjectPtr<UMaterialInstanceDynamic> SkyMaterialInstance;

    UFUNCTION(BlueprintCallable, Category = "TOD|Material")
    void SetMaterialScalarByName(
        FName ParameterName,
        float Value,
        bool bSkyDome
    );

    UFUNCTION(BlueprintCallable, Category = "TOD|Material")
    void SetMaterialVectorByName(
        FName ParameterName,
        FLinearColor Value,
        bool bSkyDome
    );

    // =========================================================================
    // Properties: TOD Base Settings
    // =========================================================================

    UPROPERTY(
        VisibleAnywhere,
        Category = "TOD",
        meta = (
            DisplayPriority = "1",
            ToolTip = "Read-only display of the configured start time."
            )
    )
    FString StartTimeDisplay = TEXT("[ 12 : 00 ]");

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "TOD",
        meta = (
            UIMin = "0.0",
            UIMax = "24.0",
            ClampMin = "0.0",
            ClampMax = "24.0",
            DisplayPriority = "2",
            ToolTip = "Initial time of day when the game starts. The TOD system will be initialized using this value."
            )
    )
    float StartTime = 12.0f;

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "TOD",
        meta = (
            DisplayPriority = "3",
            TitleProperty = "Name",
            ToolTip = "Collection of time-of-day presets used by the TOD system."
            )
    )
    TArray<FTODMasterData> TOD_DataArray;

    // =========================================================================
    // Properties: State
    // =========================================================================

    // =============== State ===============
    // 현재 시간을 기억해둘 변수
    float CurrentSystemTime = 0.0f;

    // 현재 낮/밤 상태
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD|Geography")
    ETODState CurrentState;

    // 전환되는 시간
    UPROPERTY()
    float TransitionDuration = 1.0f;

    // =========================================================================
    // Properties: Geography
    // =========================================================================

    // 지리적 설정
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "TOD|Geography",
        meta = (
            ClampMin = "-90.0",
            ClampMax = "90.0",
            UIMin = "-60.0",
            UIMax = "60.0",
            ToolTip = "Controls sunrise and sunset timing based on an artistic latitude setting. Not intended for physically accurate astronomical calculations."
            )
    )
    float Latitude = 45.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Geography")
    float Longitude = 127.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Geography")
    float CalculatedSunriseTime = 6.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD|Geography")
    float CalculatedSunsetTime = 18.0f;

    // 일출/일몰 시간
    UPROPERTY(
        VisibleAnywhere,
        BlueprintReadOnly,
        Category = "TOD|Geography",
        meta = (
            ToolTip = "Calculated sunrise time based on the current latitude setting."
            )
    )
    FString SunriseTime = TEXT("[ 06 : 00 ]");

    UPROPERTY(
        VisibleAnywhere,
        BlueprintReadOnly,
        Category = "TOD|Geography",
        meta = (
            ToolTip = "Calculated sunset time based on the current latitude setting."
            )
    )
    FString SunsetTime = TEXT("[ 18 : 00 ]");

    // =========================================================================
    // Properties: Curves Data
    // =========================================================================

    // Curve Data
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
    // Properties: Material / Visual Overrides
    // =========================================================================

    // Moon Source Scale 오버라이드
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Texture")
    bool bOverrideMoonSourceScale = true;

    // 고정 Moon Source Scale 값
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "TOD|Texture",
        meta = (
            ClampMin = "0.0",
            UIMin = "0.0",
            UIMax = "10.0"
            )
    )
    float OverriddenMoonSourceScale = 0.5f;

    // =========================================================================
    // Properties: Preset
    // =========================================================================

    // ======= Preset Asset =========
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Preset")
    TObjectPtr<UTODPresetData> LoadPreset;

    // =========================================================================
    // Properties: Debug
    // =========================================================================

    // Debug text output
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "TOD|Debug",
        meta = (
            ToolTip = "Enables on-screen debug information for the TOD system."
            )
    )
    bool bEnableDebugPrint = false;

    // Debug update interval
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "TOD|Debug",
        meta = (
            EditCondition = "bEnableDebugPrint",
            ClampMin = "0.1",
            UIMin = "0.1",
            ToolTip = "Interval in seconds between debug updates."
            )
    )
    float DebugPrintInterval = 1.0f;

    // =========================================================================
    // Functions: System & Core Logic
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
        FTODSkyAtmosphereSettings& OutSkyAtmosphere
    );

    void ApplyPPVBlending(float CurrentTime);
    void FindComponents();

    // System/PPV
    void SortTODDataArray();

    // =========================================================================
    // Functions: Geography
    // =========================================================================

    // 위도 기반 일출/일몰 계산 함수
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

    // EUW 뷰포트 갱신
    UFUNCTION(BlueprintCallable, Category = "TOD|Editor")
    void ForceViewportRedraw();

    // float 값 시간 변환
    UFUNCTION(BlueprintPure, Category = "TOD|Helper")
    FString GetFormattedTimeAsString(float InTime) const;

protected:
    // 게임 시작 시 타이머를 작동시키기 위한 BeginPlay 오버라이드
    virtual void BeginPlay() override;

private:
    // =========================================================================
    // Internal Variables & Logic
    // =========================================================================

    FTODCurveEvaluator CurveEvaluator;
    FTODEditor EditorModule;
    FTODSystem TODSystem;

    FTimerHandle DebugTimerHandle;

    // 지정된 간격마다 호출될 디버그 출력 함수
    UFUNCTION()
    void PrintTODDebugInfo();

    // 시간에 따른 상태 업데이트 함수
    void UpdateState(float CurrentTime);

#if WITH_EDITOR
protected:
    virtual void PostInitProperties() override;
    virtual void BeginDestroy() override;
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

private:
    // 외부 액터(PPV)의 변경을 감지할 함수
    void OnExternalPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
    FDelegateHandle PropertyChangeDelegateHandle;
#endif
};