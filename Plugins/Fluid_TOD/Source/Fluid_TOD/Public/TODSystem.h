#pragma once

#include "CoreMinimal.h"
#include "TOD_Types.h"

class ATODManager;

// 실제로 컴포넌트에 마지막으로 적용된 값의 캐시.
// 매 틱 SetXXX(-> MarkRenderStateDirty)를 무조건 호출하는 대신,
// 육안으로 구분 불가능한 변화는 걸러내 렌더 스테이트/프록시 재생성 빈도를 줄이기 위함.
struct FTODAppliedLightingState
{
    bool bSunInitialized = false;
    bool bMoonInitialized = false;
    bool bSkyLightInitialized = false;
    bool bFogInitialized = false;
    bool bSkyAtmosphereInitialized = false;

    FTODSunMoonSettings Sun;
    FTODMoonSettings Moon;
    FTODSkyLightSettings SkyLight;
    FTODFogSettings Fog;
    FTODSkyAtmosphereSettings SkyAtmosphere;

    // 컴포넌트가 재탐색되었거나(교체 가능성) 컷신 오버라이드가 막 끝난 경우처럼
    // 실제 컴포넌트 값이 캐시와 무관하게 바뀌었을 수 있을 때 전체 강제 재적용을 위해 호출
    void ResetAll()
    {
        bSunInitialized = false;
        bMoonInitialized = false;
        bSkyLightInitialized = false;
        bFogInitialized = false;
        bSkyAtmosphereInitialized = false;
    }
};

struct FLUID_TOD_API FTODSystem
{
public:
    void FindComponents(ATODManager* Owner);

    void UpdateTOD(ATODManager* Owner, float CurrentTime);

    void UpdateState(ATODManager* Owner, float CurrentTime);

    void UpdateSunTimes(ATODManager* Owner);

    static float NormalizeTime(float Time);

    static float GetSeasonDeclinationDeg(ETODSeason Season);

    FQuat CalculatePivotRotation(
        const ATODManager* Owner,
        float InTime) const;

private:
    FTODAppliedLightingState AppliedState;

    // 직전 틱에 컷신으로 시각 오버라이드 중이었는지 (오버라이드 종료 시점에 캐시 리셋용)
    bool bWasVisuallyOverridden = false;
};