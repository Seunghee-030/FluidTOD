#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TOD_Types.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "TODManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTODDataChangedSignature);

UCLASS(BlueprintType, meta = (PrioritizeCategories = "TOD_Geography TOD TOD_Preset TOD_Debug"))
class FLUID_TOD_API ATODManager : public AActor
{
    GENERATED_BODY()

public:
    ATODManager();

    // EUW 용 디스패쳐 선언
    UPROPERTY(BlueprintAssignable, Category = "TOD_Events")
    FOnTODDataChangedSignature OnTODDataChanged;

    UPROPERTY(VisibleAnywhere, Category = "TOD", meta = (DisplayPriority = "1"))
    FString StartTimeDisplay = TEXT("[ 12 : 00 ]");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (UIMin = "0.0", UIMax = "24.0", ClampMin = "0.0", ClampMax = "24.0", DisplayPriority = "2"))
    float StartTime = 12.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD", meta = (DisplayPriority = "3", TitleProperty = "Name"))
    TArray<FTODMasterData> TOD_DataArray;

public:
    // Moon Source Scale 오버라이드
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Material")
    bool bOverrideMoonSourceScale = false;

    // 고정 Moon Source Scale 값
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Material")
    float OverriddenMoonSourceScale = 1.0f;

    // 새로 저장
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "TOD_Preset", meta = (DisplayPriority = "1"))
    void SaveNewPreset();

    // 덮어쓰며 저장
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "TOD_Preset")
    void SaveCurrentPreset();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "TOD_Preset", meta = (DisplayPriority = "2"))
    void OpenPresetDialog();

    // Preset Asset
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Preset")
    TObjectPtr<UTODPresetData> LoadPreset;

    UFUNCTION(BlueprintCallable, Category = "TOD_Preset")
    void LoadSelectedPreset();

    // 디버그 텍스트 출력
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Debug", meta = (DisplayPriority = "1"))
    bool bEnableDebugPrint = false;

    // 출력 갱신 간격
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Debug", meta = (EditCondition = "bEnableDebugPrint", DisplayPriority = "2"))
    float DebugPrintInterval = 1.0f;


    // 지리적 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD_Geography")
    float Latitude = 37.5f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD_Geography")
    float Longitude = 127.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD_Geography")
    float CalculatedSunriseTime = 6.0f;

    UPROPERTY(BlueprintReadOnly, Category = "TOD_Geography")
    float CalculatedSunsetTime = 18.0f;

    // 일출/일몰 시간
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD_Geography")
    FString SunriseTime = TEXT("[ 06 : 00 ]");

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD_Geography")
    FString SunsetTime = TEXT("[ 18 : 00 ]");

    // 위도 기반 일출/일몰 계산 함수
    UFUNCTION(BlueprintCallable, Category = "TOD_Geography")
    void UpdateSunTimes();

    UFUNCTION(BlueprintPure, Category = "TOD_Geography")
    FRotator CalculatePivotRotation(float InTime) const;

    // =============== State ===============
public:
    // 현재 낮/밤 상태
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TOD_Geography")
    ETODState CurrentState;

    // 전환되는 시간
    UPROPERTY()
    float TransitionDuration = 1.0f;

public:
    // EUW 컴포넌트 필터 상태 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TOD|Editor")
    ETODComponentCategory CurrentComponentFilter = ETODComponentCategory::All;

public:
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

    UPROPERTY(BlueprintReadWrite, Category = "TOD|Material")
    TObjectPtr<UMaterialInstanceDynamic> MoonMaterialInstance;

    UPROPERTY(BlueprintReadWrite, Category = "TOD|Material")
    TObjectPtr<UMaterialInstanceDynamic> SkyMaterialInstance;

	// Curve Data
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun")
    FTODSunCurveData SunCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moon")
    FTODMoonCurveData MoonCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyLight")
    FTODSkyLightCurveData SkyLightCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
    FTODFogCurveData FogCurves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkyAtmosphere")
    FTODSkyAtmosphereCurveData SkyAtmosphereCurves;

	// Curve Bake
    UFUNCTION(BlueprintCallable, Category = "TOD|System")
    void BakeTODCurves();

    void GetTODSettingsAtTime(
        float InTime,
        FTODSunMoonSettings& OutSun,
        FTODMoonSettings& OutMoon,
        FTODSkyLightSettings& OutSkyLight,
        FTODFogSettings& OutFog,
        FTODSkyAtmosphereSettings& OutSkyAtmosphere
    );

    UFUNCTION(BlueprintCallable, Category = "TOD|System")
    void UpdateTOD(float CurrentTime);

    // EUW 뷰포트 갱신
    UFUNCTION(BlueprintCallable, Category = "TOD|Editor")
    void ForceViewportRedraw();

    void FindComponents();

    //  Material 이벤트
    UFUNCTION(BlueprintImplementableEvent, Category = "TOD|System")
    void OnUpdateCustomMaterials(float CurrentTime);

    // float 값 시간 변환
    UFUNCTION(BlueprintPure, Category = "TOD|Helper")
    FString GetFormattedTimeAsString(float InTime) const;

    // System/PPV
    void SortTODDataArray();

    void ApplyPPVBlending(float CurrentTime);

protected:
    // 게임 시작 시 타이머를 작동시키기 위한 BeginPlay 오버라이드
    virtual void BeginPlay() override;

private:
    FTimerHandle DebugTimerHandle;
    float CurrentSystemTime = 0.0f; // 현재 시간을 기억해둘 변수

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