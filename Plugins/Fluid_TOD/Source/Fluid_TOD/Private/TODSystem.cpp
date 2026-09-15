#include "TODSystem.h"
#include "TODManager.h"
#include "Engine/StaticMesh.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

namespace
{
	// 상대 오차(0.05%) + 최소 절대치 중 큰 값을 임계치로 사용.
	// 임계치 이하 변화는 육안으로 구분되지 않으므로 SetXXX(-> MarkRenderStateDirty) 호출 자체를 생략한다.
	FORCEINLINE bool HasChangedNoticeably(float NewValue, float OldValue, float AbsEpsilon)
	{
		const float Threshold = FMath::Max(AbsEpsilon, FMath::Abs(OldValue) * 0.0005f);
		return FMath::Abs(NewValue - OldValue) > Threshold;
	}

	FORCEINLINE bool HasChangedNoticeably(const FLinearColor& NewValue, const FLinearColor& OldValue, float AbsEpsilon)
	{
		return HasChangedNoticeably(NewValue.R, OldValue.R, AbsEpsilon)
			|| HasChangedNoticeably(NewValue.G, OldValue.G, AbsEpsilon)
			|| HasChangedNoticeably(NewValue.B, OldValue.B, AbsEpsilon)
			|| HasChangedNoticeably(NewValue.A, OldValue.A, AbsEpsilon);
	}

	constexpr float EpsIntensityLarge = 0.01f;  // Sun/Moon Intensity
	constexpr float EpsAngleDeg = 0.001f;       // Source Angle / Soft Angle
	constexpr float EpsUnitScale = 0.0001f;     // 0~1 근방 배율/보정값 (density, falloff, indirect 등)
	constexpr float EpsColor = 0.0008f;         // 색상 채널당
}

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

	// 컴포넌트가 교체되었을 수 있으므로, 적용 캐시를 무효화해 다음 UpdateTOD에서 전체 재적용되게 한다.
	AppliedState.ResetAll();
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
	if (SafeTime < 0.0f) SafeTime += 24.0f;
	if (FMath::IsNearlyEqual(SafeTime, 24.0f, 0.001f)) return 0.0f;
	return SafeTime;
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

	// 경과시간 계산을 위한 세그먼트 시작 시간
	float SegmentStart;

	if (SafeTime >= DawnStart && SafeTime < Owner->CalculatedSunriseTime)
	{
		SegmentStart = DawnStart;
	}
	else if (SafeTime >= Owner->CalculatedSunriseTime && SafeTime < SunriseEnd)
	{
		SegmentStart = Owner->CalculatedSunriseTime;
	}
	else if (SafeTime >= SunriseEnd && SafeTime < SunsetStart)
	{
		SegmentStart = SunriseEnd;
	}
	else if (SafeTime >= SunsetStart && SafeTime < Owner->CalculatedSunsetTime)
	{
		SegmentStart = SunsetStart;
	}
	else if (SafeTime >= Owner->CalculatedSunsetTime && SafeTime < DuskEnd)
	{
		SegmentStart = Owner->CalculatedSunsetTime;
	}
	else
	{
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

	// 데디케이티드 서버는 렌더링하지 않으므로 커브 평가/PPV 블렌딩/라이트 Set 등
	// 시각 갱신은 건너뛴다. CurrentSystemTime과 상태(StateBlendAlpha 등)는 위에서 이미 갱신됨.
	if (Owner->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	if (Owner->IsVisualOverridden())
	{
		bWasVisuallyOverridden = true;
		return;
	}

	// 컷신 오버라이드가 방금 끝났다면 그동안 외부(시퀀서 등)가 컴포넌트 값을 바꿔놨을 수 있으므로
	// 캐시를 무시하고 이번 틱에는 전체를 강제로 재적용한다.
	if (bWasVisuallyOverridden)
	{
		AppliedState.ResetAll();
		bWasVisuallyOverridden = false;
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
		FindComponents(Owner);
	}

	Owner->ApplyPPVBlending(CurrentTime);

	bool bTimeJumped = false;
	if (Owner->LastEvaluatedTime >= 0.0f)
	{
		float LastSafe = NormalizeTime(Owner->LastEvaluatedTime);
		float CurrSafe = NormalizeTime(CurrentTime);
		// 시간이 1시간 이상 튀면(24->0 순환 등) Temporal 캐시를 비우기 위한 플래그
		if (FMath::Abs(CurrSafe - LastSafe) > 1.0f)
		{
			bTimeJumped = true;
		}
	}

	if (!FMath::IsNearlyEqual(Owner->LastEvaluatedTime, CurrentTime, 0.001f))
	{
		Owner->GetTODSettingsAtTime(
			CurrentTime,
			Owner->CachedSun,
			Owner->CachedMoon,
			Owner->CachedSky,
			Owner->CachedFog,
			Owner->CachedAtmos
		);
		Owner->LastEvaluatedTime = CurrentTime;
	}

	const FTODSunMoonSettings& Sun = Owner->CachedSun;
	const FTODMoonSettings& Moon = Owner->CachedMoon;
	const FTODSkyLightSettings& Sky = Owner->CachedSky;
	const FTODFogSettings& Fog = Owner->CachedFog;
	const FTODSkyAtmosphereSettings& Atmos = Owner->CachedAtmos;

	if (IsValid(Owner->SkyMaterialInstance))
	{
		Owner->SkyMaterialInstance->SetScalarParameterValue(
			TEXT("SkyTextureEmissiveIntensity"),
			Sky.SkyDome_Texture_Emissive_Intensity
		);

		Owner->SkyMaterialInstance->SetScalarParameterValue(
			TEXT("StarEmissiveIntensity"),
			Sky.Star_Emissive_Intensity
		);
	}

	if (IsValid(Owner->MoonMaterialInstance))
	{
		Owner->MoonMaterialInstance->SetScalarParameterValue(
			TEXT("MoonSourceEmissiveIntensity"),
			Moon.Moon_Source_Emissive_Intensity
		);
	}

	if (IsValid(Owner->MoonGlowMaterialInstance))
	{
		Owner->MoonGlowMaterialInstance->SetScalarParameterValue(
			TEXT("MoonGlowEmissiveIntensity"),
			Moon.Moon_Glow_Emissive_Intensity
		);
	}

	// Sun
	if (IsValid(Owner->SunLightComponent))
	{
		if (!Owner->SunLightComponent->bAtmosphereSunLight)
		{
			//Owner->SunLightComponent->SetAtmosphereSunLight(true);
			Owner->SunLightComponent->MarkRenderStateDirty();
		}

		Owner->SunLightComponent->SetIntensity(Sun.Intensity);
		Owner->SunLightComponent->SetLightColor(Sun.Light_Color);
		Owner->SunLightComponent->SetLightSourceAngle(Sun.Source_Angle);
		Owner->SunLightComponent->SetLightSourceSoftAngle(Sun.Source_Soft_Angle);
		Owner->SunLightComponent->SetIndirectLightingIntensity(Sun.Indirect_Light_Intensity);
	}

	// Moon
	if (IsValid(Owner->MoonLightComponent))
	{
		// 달의 대기 산란 영향 차단 (붉은 달 방지)
		if (Owner->MoonLightComponent->bAtmosphereSunLight)
		{
			Owner->bCachedMoonAtmosphere = Owner->MoonLightComponent->bAtmosphereSunLight;
			Owner->MoonLightComponent->MarkRenderStateDirty();
		}

		Owner->MoonLightComponent->SetIntensity(Moon.Intensity);
		Owner->MoonLightComponent->SetLightColor(Moon.Light_Color);
		Owner->MoonLightComponent->SetLightSourceAngle(Moon.Source_Angle);
		Owner->MoonLightComponent->SetLightSourceSoftAngle(Moon.Source_Soft_Angle);
		Owner->MoonLightComponent->SetIndirectLightingIntensity(Moon.Indirect_Light_Intensity);
	}

	// Sky Light
	if (IsValid(Owner->SkyLightComponent))
	{
		FTODSkyLightSettings& Cache = AppliedState.SkyLight;
		const bool bForce = !AppliedState.bSkyLightInitialized;

		if (bForce || HasChangedNoticeably(Sky.Sky_Light_Intensity, Cache.Sky_Light_Intensity, EpsUnitScale))
		{
			Owner->SkyLightComponent->SetIntensity(Sky.Sky_Light_Intensity);
			Cache.Sky_Light_Intensity = Sky.Sky_Light_Intensity;
		}
		if (bForce || HasChangedNoticeably(Sky.Sky_Light_Color, Cache.Sky_Light_Color, EpsColor))
		{
			Owner->SkyLightComponent->SetLightColor(Sky.Sky_Light_Color);
			Cache.Sky_Light_Color = Sky.Sky_Light_Color;
		}
		if (bForce || HasChangedNoticeably(Sky.Sky_Indirect_Lighting_Intensity, Cache.Sky_Indirect_Lighting_Intensity, EpsUnitScale))
		{
			Owner->SkyLightComponent->SetIndirectLightingIntensity(Sky.Sky_Indirect_Lighting_Intensity);
			Cache.Sky_Indirect_Lighting_Intensity = Sky.Sky_Indirect_Lighting_Intensity;
		}
		if (bForce || HasChangedNoticeably(Sky.Sky_Volumetric_Scattering_Intensity, Cache.Sky_Volumetric_Scattering_Intensity, EpsUnitScale))
		{
			Owner->SkyLightComponent->SetVolumetricScatteringIntensity(Sky.Sky_Volumetric_Scattering_Intensity);
			Cache.Sky_Volumetric_Scattering_Intensity = Sky.Sky_Volumetric_Scattering_Intensity;
		}

		AppliedState.bSkyLightInitialized = true;
	}

	// Fog
	if (IsValid(Owner->FogComponent))
	{
		FTODFogSettings& Cache = AppliedState.Fog;
		const bool bForce = !AppliedState.bFogInitialized;

		if (bForce || HasChangedNoticeably(Fog.Fog_Density, Cache.Fog_Density, EpsUnitScale))
		{
			Owner->FogComponent->SetFogDensity(Fog.Fog_Density);
			Cache.Fog_Density = Fog.Fog_Density;
		}
		if (bForce || HasChangedNoticeably(Fog.Fog_Height_Falloff, Cache.Fog_Height_Falloff, EpsUnitScale))
		{
			Owner->FogComponent->SetFogHeightFalloff(Fog.Fog_Height_Falloff);
			Cache.Fog_Height_Falloff = Fog.Fog_Height_Falloff;
		}
		if (bForce || HasChangedNoticeably(Fog.Fog_Inscattering_Color, Cache.Fog_Inscattering_Color, EpsColor))
		{
			Owner->FogComponent->SetFogInscatteringColor(Fog.Fog_Inscattering_Color);
			Cache.Fog_Inscattering_Color = Fog.Fog_Inscattering_Color;
		}
		if (bForce || HasChangedNoticeably(Fog.Fog_Directional_Inscattering, Cache.Fog_Directional_Inscattering, EpsColor))
		{
			Owner->FogComponent->SetDirectionalInscatteringColor(Fog.Fog_Directional_Inscattering);
			Cache.Fog_Directional_Inscattering = Fog.Fog_Directional_Inscattering;
		}

		AppliedState.bFogInitialized = true;
	}

	// Sky Atmosphere
	if (IsValid(Owner->SkyAtmosphereComponent))
	{
		FTODSkyAtmosphereSettings& Cache = AppliedState.SkyAtmosphere;
		const bool bForce = !AppliedState.bSkyAtmosphereInitialized;

		if (bForce || HasChangedNoticeably(Atmos.Mie_Scattering_Scale, Cache.Mie_Scattering_Scale, EpsUnitScale))
		{
			Owner->SkyAtmosphereComponent->SetMieScatteringScale(Atmos.Mie_Scattering_Scale);
			Cache.Mie_Scattering_Scale = Atmos.Mie_Scattering_Scale;
		}
		if (bForce || HasChangedNoticeably(Atmos.Mie_Scattering_Color, Cache.Mie_Scattering_Color, EpsColor))
		{
			Owner->SkyAtmosphereComponent->SetMieScattering(Atmos.Mie_Scattering_Color);
			Cache.Mie_Scattering_Color = Atmos.Mie_Scattering_Color;
		}
		if (bForce || HasChangedNoticeably(Atmos.Absorption_Color, Cache.Absorption_Color, EpsColor))
		{
			Owner->SkyAtmosphereComponent->SetOtherAbsorption(Atmos.Absorption_Color);
			Cache.Absorption_Color = Atmos.Absorption_Color;
		}
		if (bForce || HasChangedNoticeably(Atmos.Rayleigh_Scattering_Scale, Cache.Rayleigh_Scattering_Scale, EpsUnitScale))
		{
			Owner->SkyAtmosphereComponent->SetRayleighScatteringScale(Atmos.Rayleigh_Scattering_Scale);
			Cache.Rayleigh_Scattering_Scale = Atmos.Rayleigh_Scattering_Scale;
		}
		if (bForce || HasChangedNoticeably(Atmos.Aerial_Perspective_Distance_Scale, Cache.Aerial_Perspective_Distance_Scale, EpsUnitScale))
		{
			Owner->SkyAtmosphereComponent->SetAerialPespectiveViewDistanceScale(Atmos.Aerial_Perspective_Distance_Scale);
			Cache.Aerial_Perspective_Distance_Scale = Atmos.Aerial_Perspective_Distance_Scale;
		}
		if (bForce || HasChangedNoticeably(Atmos.Sky_Luminance_Factor, Cache.Sky_Luminance_Factor, EpsColor))
		{
			Owner->SkyAtmosphereComponent->SetSkyLuminanceFactor(Atmos.Sky_Luminance_Factor);
			Cache.Sky_Luminance_Factor = Atmos.Sky_Luminance_Factor;
		}

		AppliedState.bSkyAtmosphereInitialized = true;
	}

	// Custom Material Updates
	Owner->OnUpdateCustomMaterials(CurrentTime);

}