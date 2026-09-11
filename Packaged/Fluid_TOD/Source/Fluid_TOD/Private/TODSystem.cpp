#include "TODSystem.h"
#include "TODManager.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

namespace
{
	// 상대 오차 기준. 값이 0 근처일 때도 동작하도록 분모를 1로 클램프한다.
	FORCEINLINE bool TODValueChanged(float Last, float New, float RelTolerance)
	{
		return FMath::Abs(New - Last) > RelTolerance * FMath::Max(1.0f, FMath::Abs(Last));
	}

	FORCEINLINE bool TODColorChanged(const FLinearColor& Last, const FLinearColor& New, float RelTolerance)
	{
		return !Last.Equals(New, FMath::Max(RelTolerance, UE_KINDA_SMALL_NUMBER));
	}
}

// 값이 실질적으로 바뀐 경우에만 setter를 호출한다.
// 대부분의 엔진 setter는 내부에서 MarkRenderStateDirty()를 호출하므로,
// 커브 기반의 미세한 변화까지 전부 밀어 넣으면 매 프레임 렌더 상태가 재생성된다.
#define TOD_APPLY_FLOAT(LastRef, NewVal, SetterExpr) \
	if (bForceApply || TODValueChanged((LastRef), (NewVal), Tol)) { SetterExpr; (LastRef) = (NewVal); }

#define TOD_APPLY_COLOR(LastRef, NewVal, SetterExpr) \
	if (bForceApply || TODColorChanged((LastRef), (NewVal), Tol)) { SetterExpr; (LastRef) = (NewVal); }

void FTODSystem::FindComponents(ATODManager* Owner)
{
	if (!Owner) return;

	// Store previous meshes
	UStaticMeshComponent* PreviousSkyDomeMesh = Owner->SkyDomeMesh;
	UStaticMeshComponent* PreviousMoonMesh = Owner->MoonMesh;
	UStaticMeshComponent* PreviousMoonGlowMesh = Owner->MoonGlowMesh;

	// Reset
	Owner->SunLightComponent = nullptr;
	Owner->MoonLightComponent = nullptr;
	Owner->SkyLightComponent = nullptr;
	Owner->FogComponent = nullptr;
	Owner->SkyAtmosphereComponent = nullptr;

	Owner->PivotOrbitTiltComponent = nullptr;
	Owner->PivotSunMoonComponent = nullptr;
	Owner->MeshPivotComponent = nullptr;

	Owner->SkyDomeMesh = nullptr;
	Owner->MoonMesh = nullptr;
	Owner->MoonGlowMesh = nullptr;

	// Sun & Moon
	TArray<UDirectionalLightComponent*> Lights;
	Owner->GetComponents<UDirectionalLightComponent>(Lights);
	for (UDirectionalLightComponent* Light : Lights)
	{
		if (Light->ComponentHasTag(TEXT("Moon"))) Owner->MoonLightComponent = Light;
		else if (Light->ComponentHasTag(TEXT("Sun"))) Owner->SunLightComponent = Light;
		if (IsValid(Owner->SunLightComponent) && IsValid(Owner->MoonLightComponent)) break;
	}

	// SkyLight, Fog, SkyAtmosphere
	Owner->SkyLightComponent = Owner->FindComponentByClass<USkyLightComponent>();
	Owner->FogComponent = Owner->FindComponentByClass<UExponentialHeightFogComponent>();
	Owner->SkyAtmosphereComponent = Owner->FindComponentByClass<USkyAtmosphereComponent>();

	// Pivot Components
	Owner->PivotOrbitTiltComponent = Owner->FindComponentByTag<USceneComponent>(TEXT("PivotOrbitTilt"));
	Owner->PivotSunMoonComponent = Owner->FindComponentByTag<USceneComponent>(TEXT("PivotSunMoon"));
	Owner->MeshPivotComponent = Owner->FindComponentByTag<USceneComponent>(TEXT("MeshPivot"));

	// SkyDome & Moon Mesh
	TArray<UStaticMeshComponent*> Meshes;
	Owner->GetComponents<UStaticMeshComponent>(Meshes);

	for (UStaticMeshComponent* Mesh : Meshes)
	{
		if (Mesh->ComponentHasTag(TEXT("SkyDome")))
		{
			Owner->SkyDomeMesh = Mesh;
		}
		else if (Mesh->ComponentHasTag(TEXT("MoonMesh")))
		{
			Owner->MoonMesh = Mesh;
		}
		else if (Mesh->ComponentHasTag(TEXT("MoonGlow")))
		{
			Owner->MoonGlowMesh = Mesh;
		}
	}

	// if Meshes Changed
	if (Owner->SkyDomeMesh != PreviousSkyDomeMesh)
	{
		Owner->SkyMaterialInstance = nullptr;
	}
	if (Owner->MoonMesh != PreviousMoonMesh)
	{
		Owner->MoonMaterialInstance = nullptr;
	}
	if (Owner->MoonGlowMesh != PreviousMoonGlowMesh)
	{
		Owner->MoonGlowMaterialInstance = nullptr;
	}

	// Create Material Instances
	if (IsValid(Owner->SkyDomeMesh) &&
		!IsValid(Owner->SkyMaterialInstance))
	{
		Owner->SkyMaterialInstance =
			Owner->SkyDomeMesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (IsValid(Owner->MoonMesh) &&
		!IsValid(Owner->MoonMaterialInstance))
	{
		Owner->MoonMaterialInstance =
			Owner->MoonMesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (IsValid(Owner->MoonGlowMesh) &&
		!IsValid(Owner->MoonGlowMaterialInstance))
	{
		Owner->MoonGlowMaterialInstance =
			Owner->MoonGlowMesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	// 컴포넌트가 교체됐으므로 "마지막 적용값" 캐시는 더 이상 신뢰할 수 없다.
	Owner->bHasAppliedTODSettings = false;

	// 대기 광원 인덱스 등 1회성 설정은 여기서만 수행한다.
	Owner->ApplyAtmosphereLightSetup();
}

float FTODSystem::GetSeasonDeclinationDeg(ETODSeason Season)
{
	switch (Season)
	{
	case ETODSeason::Spring: return 0.0f;
	case ETODSeason::Summer: return 23.45f;
	case ETODSeason::Autumn: return 0.0f;
	case ETODSeason::Winter: return -23.45f;
	default:                 return 0.0f;
	}
}

void FTODSystem::UpdateSunTimes(ATODManager* Owner)
{
	if (!Owner) return;

	// latitude -> radian
	const float ClampedLat = FMath::Clamp(Owner->Latitude, -90.0f, 90.0f);
	const float LatRad = FMath::DegreesToRadians(ClampedLat);

	// Declination -> radian
	const float DeclinationDeg = GetSeasonDeclinationDeg(Owner->Season);
	const float DecRad = FMath::DegreesToRadians(DeclinationDeg);

	// Hour Angle 계산
	const float CosHourAngle = -FMath::Tan(LatRad) * FMath::Tan(DecRad);

	const float SolarNoonTime = NormalizeTime(12.0f - (Owner->Longitude / 15.0f));

	float HourAngleDeg = 90.0f;

	if (CosHourAngle <= -1.0f)
	{
		// 백야
		Owner->CalculatedSunriseTime = 0.0f;
		Owner->CalculatedSunsetTime = 24.0f;
		Owner->SunriseTime = TEXT("[ Midnight Sun ]");
		Owner->SunsetTime = TEXT("[ Midnight Sun ]");
		return;
	}
	else if (CosHourAngle >= 1.0f)
	{
		// 극야
		Owner->CalculatedSunriseTime = SolarNoonTime;
		Owner->CalculatedSunsetTime = SolarNoonTime;
		Owner->SunriseTime = TEXT("[ Polar Night ]");
		Owner->SunsetTime = TEXT("[ Polar Night ]");
		return;
	}
	else
	{
		HourAngleDeg = FMath::RadiansToDegrees(FMath::Acos(CosHourAngle));
	}

	const float HalfDayHours = HourAngleDeg / 15.0f;

	// 태양 남중(Longitude 반영) 기준으로 설정
	Owner->CalculatedSunriseTime = NormalizeTime(SolarNoonTime - HalfDayHours);
	Owner->CalculatedSunsetTime = NormalizeTime(SolarNoonTime + HalfDayHours);

	// text
	Owner->SunriseTime = Owner->GetFormattedTimeAsString(Owner->CalculatedSunriseTime);
	Owner->SunsetTime = Owner->GetFormattedTimeAsString(Owner->CalculatedSunsetTime);
}

float FTODSystem::NormalizeTime(float Time)
{
	float SafeTime = FMath::Fmod(Time, 24.0f);
	return SafeTime < 0.f ? SafeTime + 24.f : SafeTime;
}

// 태양의 위치에 따라 Pivot 컴포넌트를 회전
FQuat FTODSystem::CalculatePivotRotation(
	const ATODManager* Owner,
	float InTime) const
{
	if (!Owner) return FQuat::Identity;

	const float LatRad = FMath::DegreesToRadians(FMath::Clamp(Owner->Latitude, -90.0f, 90.0f));
	const float DecRad = FMath::DegreesToRadians(GetSeasonDeclinationDeg(Owner->Season));

	const float TimeFromNoon = InTime - 12.0f;
	const float HourAngleRad = FMath::DegreesToRadians((TimeFromNoon * 15.0f) + Owner->Longitude);

	const float SinLat = FMath::Sin(LatRad);
	const float CosLat = FMath::Cos(LatRad);
	const float SinDec = FMath::Sin(DecRad);
	const float CosDec = FMath::Cos(DecRad);
	const float SinHA = FMath::Sin(HourAngleRad);
	const float CosHA = FMath::Cos(HourAngleRad);

	FVector SunDir;
	SunDir.X = (CosLat * SinDec) - (SinLat * CosDec * CosHA); // North/South 방위
	SunDir.Y = -(CosDec * SinHA);                             // East/West 방위
	SunDir.Z = (SinLat * SinDec) + (CosLat * CosDec * CosHA); // 천정(Zenith) 고도

	// 시간각(Latitude+Longitude+Time) 방향 회전
	const FQuat TimeBasedRotation = FRotationMatrix::MakeFromX(-SunDir).ToQuat();

	if (IsValid(Owner->PivotOrbitTiltComponent))
	{
		return TimeBasedRotation;
	}

	// 부모 Pivot이 없는 경우
	const FQuat AzimuthOffsetRotation(FVector::UpVector, FMath::DegreesToRadians(Owner->SunAzimuthOffset));
	return AzimuthOffsetRotation * TimeBasedRotation;
}

void FTODSystem::UpdateState(ATODManager* Owner, float CurrentTime)
{
	if (!Owner) return;

	const float SafeTime = NormalizeTime(CurrentTime);

	float DawnStart = Owner->CalculatedSunriseTime - Owner->TransitionDuration;
	float SunriseEnd = Owner->CalculatedSunriseTime + Owner->TransitionDuration;

	float SunsetStart = Owner->CalculatedSunsetTime - Owner->TransitionDuration;
	float DuskEnd = Owner->CalculatedSunsetTime + Owner->TransitionDuration;

	ETODState NewState;
	ETODState NewPreviousState;

	// 경과시간 계산을 위한 세그먼트 시작 시간
	float SegmentStart;

	if (SafeTime >= DawnStart && SafeTime < Owner->CalculatedSunriseTime)
	{
		NewState = ETODState::Dawn;
		NewPreviousState = ETODState::Night;
		SegmentStart = DawnStart;
	}
	else if (SafeTime >= Owner->CalculatedSunriseTime && SafeTime < SunriseEnd)
	{
		NewState = ETODState::Sunrise;
		NewPreviousState = ETODState::Dawn;
		SegmentStart = Owner->CalculatedSunriseTime;
	}
	else if (SafeTime >= SunriseEnd && SafeTime < SunsetStart)
	{
		NewState = ETODState::Day;
		NewPreviousState = ETODState::Sunrise;
		SegmentStart = SunriseEnd;
	}
	else if (SafeTime >= SunsetStart && SafeTime < Owner->CalculatedSunsetTime)
	{
		NewState = ETODState::Sunset;
		NewPreviousState = ETODState::Day;
		SegmentStart = SunsetStart;
	}
	else if (SafeTime >= Owner->CalculatedSunsetTime && SafeTime < DuskEnd)
	{
		NewState = ETODState::Dusk;
		NewPreviousState = ETODState::Sunset;
		SegmentStart = Owner->CalculatedSunsetTime;
	}
	else
	{
		NewState = ETODState::Night;
		NewPreviousState = ETODState::Dusk;
		SegmentStart = DuskEnd;
	}

	// 정규화 후 경과시간 계산.
	float Elapsed = SafeTime - NormalizeTime(SegmentStart);
	if (Elapsed < 0.0f) Elapsed += 24.0f;

	Owner->StateBlendAlpha = FMath::Clamp(
		Elapsed / FMath::Max(Owner->TransitionDuration, KINDA_SMALL_NUMBER),
		0.0f, 1.0f);
}

void FTODSystem::UpdateTOD(ATODManager* Owner, float CurrentTime)
{
	if (!Owner || Owner->TOD_DataArray.Num() == 0) return;

	Owner->CurrentSystemTime = CurrentTime;
	UpdateState(Owner, CurrentTime);

	if (Owner->IsVisualOverridden())
	{
		return;
	}

	if (
		!IsValid(Owner->SunLightComponent) ||
		!IsValid(Owner->MoonLightComponent) ||
		!IsValid(Owner->SkyLightComponent) ||
		!IsValid(Owner->FogComponent) ||
		!IsValid(Owner->SkyAtmosphereComponent) ||
		!IsValid(Owner->SkyDomeMesh) ||
		!IsValid(Owner->MoonMesh) ||
		!IsValid(Owner->PivotSunMoonComponent)
		)
	{
		// 쿨다운 백오프. 선택적 컴포넌트가 아예 없는 셋업에서
		// 매 프레임 GetComponents<> 전체 순회가 도는 것을 막는다.
		Owner->TryRefreshComponents();
	}

	Owner->ApplyPPVBlending(CurrentTime);

	FTODSunMoonSettings Sun;
	FTODMoonSettings Moon;
	FTODSkyLightSettings Sky;
	FTODFogSettings Fog;
	FTODSkyAtmosphereSettings Atmos;

	Owner->GetTODSettingsAtTime(
		CurrentTime,
		Sun,
		Moon,
		Sky,
		Fog,
		Atmos
	);

	const float Tol = FMath::Max(Owner->ValueChangeTolerance, 0.0f);
	const bool bForceApply = !Owner->bHasAppliedTODSettings;

	// ===== Sky Dome / Star Material =====
	if (IsValid(Owner->SkyMaterialInstance))
	{
		TOD_APPLY_FLOAT(
			Owner->LastAppliedSkyLight.SkyDome_Texture_Emissive_Intensity,
			Sky.SkyDome_Texture_Emissive_Intensity,
			Owner->SkyMaterialInstance->SetScalarParameterValue(TEXT("SkyTextureEmissiveIntensity"), Sky.SkyDome_Texture_Emissive_Intensity));

		TOD_APPLY_FLOAT(
			Owner->LastAppliedSkyLight.Star_Emissive_Intensity,
			Sky.Star_Emissive_Intensity,
			Owner->SkyMaterialInstance->SetScalarParameterValue(TEXT("StarEmissiveIntensity"), Sky.Star_Emissive_Intensity));
	}

	// ===== Moon Material =====
	if (IsValid(Owner->MoonMaterialInstance))
	{
		TOD_APPLY_FLOAT(
			Owner->LastAppliedMoon.Moon_Source_Emissive_Intensity,
			Moon.Moon_Source_Emissive_Intensity,
			Owner->MoonMaterialInstance->SetScalarParameterValue(TEXT("MoonSourceEmissiveIntensity"), Moon.Moon_Source_Emissive_Intensity));
	}

	if (IsValid(Owner->MoonGlowMaterialInstance))
	{
		TOD_APPLY_FLOAT(
			Owner->LastAppliedMoon.Moon_Glow_Emissive_Intensity,
			Moon.Moon_Glow_Emissive_Intensity,
			Owner->MoonGlowMaterialInstance->SetScalarParameterValue(TEXT("MoonGlowEmissiveIntensity"), Moon.Moon_Glow_Emissive_Intensity));
	}

	// ===== Sun =====
	if (IsValid(Owner->SunLightComponent))
	{
		UDirectionalLightComponent* SunLight = Owner->SunLightComponent;

		TOD_APPLY_FLOAT(Owner->LastAppliedSun.Intensity, Sun.Intensity,
			SunLight->SetIntensity(Sun.Intensity));

		TOD_APPLY_COLOR(Owner->LastAppliedSun.Light_Color, Sun.Light_Color,
			SunLight->SetLightColor(Sun.Light_Color));

		TOD_APPLY_FLOAT(Owner->LastAppliedSun.Source_Angle, Sun.Source_Angle,
			SunLight->SetLightSourceAngle(Sun.Source_Angle));

		TOD_APPLY_FLOAT(Owner->LastAppliedSun.Source_Soft_Angle, Sun.Source_Soft_Angle,
			SunLight->SetLightSourceSoftAngle(Sun.Source_Soft_Angle));

		TOD_APPLY_FLOAT(Owner->LastAppliedSun.Indirect_Light_Intensity, Sun.Indirect_Light_Intensity,
			SunLight->SetIndirectLightingIntensity(Sun.Indirect_Light_Intensity));
	}

	// ===== Moon =====
	if (IsValid(Owner->MoonLightComponent))
	{
		UDirectionalLightComponent* MoonLight = Owner->MoonLightComponent;

		TOD_APPLY_FLOAT(Owner->LastAppliedMoon.Intensity, Moon.Intensity,
			MoonLight->SetIntensity(Moon.Intensity));

		TOD_APPLY_COLOR(Owner->LastAppliedMoon.Light_Color, Moon.Light_Color,
			MoonLight->SetLightColor(Moon.Light_Color));

		TOD_APPLY_FLOAT(Owner->LastAppliedMoon.Source_Angle, Moon.Source_Angle,
			MoonLight->SetLightSourceAngle(Moon.Source_Angle));

		TOD_APPLY_FLOAT(Owner->LastAppliedMoon.Source_Soft_Angle, Moon.Source_Soft_Angle,
			MoonLight->SetLightSourceSoftAngle(Moon.Source_Soft_Angle));

		TOD_APPLY_FLOAT(Owner->LastAppliedMoon.Indirect_Light_Intensity, Moon.Indirect_Light_Intensity,
			MoonLight->SetIndirectLightingIntensity(Moon.Indirect_Light_Intensity));
	}

	// ===== Sky Light =====
	if (IsValid(Owner->SkyLightComponent))
	{
		USkyLightComponent* SkyLight = Owner->SkyLightComponent;

		TOD_APPLY_FLOAT(Owner->LastAppliedSkyLight.Sky_Light_Intensity, Sky.Sky_Light_Intensity,
			SkyLight->SetIntensity(Sky.Sky_Light_Intensity));

		TOD_APPLY_COLOR(Owner->LastAppliedSkyLight.Sky_Light_Color, Sky.Sky_Light_Color,
			SkyLight->SetLightColor(Sky.Sky_Light_Color));

		TOD_APPLY_FLOAT(Owner->LastAppliedSkyLight.Sky_Indirect_Lighting_Intensity, Sky.Sky_Indirect_Lighting_Intensity,
			SkyLight->SetIndirectLightingIntensity(Sky.Sky_Indirect_Lighting_Intensity));

		TOD_APPLY_FLOAT(Owner->LastAppliedSkyLight.Sky_Volumetric_Scattering_Intensity, Sky.Sky_Volumetric_Scattering_Intensity,
			SkyLight->SetVolumetricScatteringIntensity(Sky.Sky_Volumetric_Scattering_Intensity));
	}

	// ===== Fog =====
	if (IsValid(Owner->FogComponent))
	{
		UExponentialHeightFogComponent* FogComp = Owner->FogComponent;

		TOD_APPLY_FLOAT(Owner->LastAppliedFog.Fog_Density, Fog.Fog_Density,
			FogComp->SetFogDensity(Fog.Fog_Density));

		TOD_APPLY_FLOAT(Owner->LastAppliedFog.Fog_Height_Falloff, Fog.Fog_Height_Falloff,
			FogComp->SetFogHeightFalloff(Fog.Fog_Height_Falloff));

		TOD_APPLY_COLOR(Owner->LastAppliedFog.Fog_Inscattering_Color, Fog.Fog_Inscattering_Color,
			FogComp->SetFogInscatteringColor(Fog.Fog_Inscattering_Color));

		TOD_APPLY_COLOR(Owner->LastAppliedFog.Fog_Directional_Inscattering, Fog.Fog_Directional_Inscattering,
			FogComp->SetDirectionalInscatteringColor(Fog.Fog_Directional_Inscattering));
	}

	// ===== Sky Atmosphere =====
	if (IsValid(Owner->SkyAtmosphereComponent))
	{
		USkyAtmosphereComponent* Atmosphere = Owner->SkyAtmosphereComponent;

		TOD_APPLY_FLOAT(Owner->LastAppliedAtmos.Mie_Scattering_Scale, Atmos.Mie_Scattering_Scale,
			Atmosphere->SetMieScatteringScale(Atmos.Mie_Scattering_Scale));

		TOD_APPLY_COLOR(Owner->LastAppliedAtmos.Mie_Scattering_Color, Atmos.Mie_Scattering_Color,
			Atmosphere->SetMieScattering(Atmos.Mie_Scattering_Color));

		TOD_APPLY_COLOR(Owner->LastAppliedAtmos.Absorption_Color, Atmos.Absorption_Color,
			Atmosphere->SetOtherAbsorption(Atmos.Absorption_Color));

		TOD_APPLY_FLOAT(Owner->LastAppliedAtmos.Rayleigh_Scattering_Scale, Atmos.Rayleigh_Scattering_Scale,
			Atmosphere->SetRayleighScatteringScale(Atmos.Rayleigh_Scattering_Scale));

		TOD_APPLY_FLOAT(Owner->LastAppliedAtmos.Aerial_Perspective_Distance_Scale, Atmos.Aerial_Perspective_Distance_Scale,
			Atmosphere->SetAerialPespectiveViewDistanceScale(Atmos.Aerial_Perspective_Distance_Scale));

		TOD_APPLY_COLOR(Owner->LastAppliedAtmos.Sky_Luminance_Factor, Atmos.Sky_Luminance_Factor,
			Atmosphere->SetSkyLuminanceFactor(Atmos.Sky_Luminance_Factor));
	}

	Owner->bHasAppliedTODSettings = true;

	// Custom Material Updates
	Owner->OnUpdateCustomMaterials(CurrentTime);
}

#undef TOD_APPLY_FLOAT
#undef TOD_APPLY_COLOR