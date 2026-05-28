#include "TODSystem.h"
#include "TODManager.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"

void FTODSystem::FindComponents(ATODManager* Owner)
{
	if (!Owner) return;

	TArray<UDirectionalLightComponent*> Lights;
	Owner->GetComponents<UDirectionalLightComponent>(Lights);

	Owner->SunLightComponent = nullptr;
	Owner->MoonLightComponent = nullptr;

	for (UDirectionalLightComponent* Light : Lights)
	{
		if (Light->ComponentHasTag(TEXT("Moon")))
		{
			Owner->MoonLightComponent = Light;
		}
		else if (Light->ComponentHasTag(TEXT("Sun")))
		{
			Owner->SunLightComponent = Light;
		}
	}

	Owner->SkyLightComponent =
		Owner->FindComponentByClass<USkyLightComponent>();

	Owner->FogComponent =
		Owner->FindComponentByClass<UExponentialHeightFogComponent>();

	Owner->SkyAtmosphereComponent =
		Owner->FindComponentByClass<USkyAtmosphereComponent>();
}

void FTODSystem::UpdateSunTimes(ATODManager* Owner)
{
	if (!Owner) return;

	float LatitudeOffset = (Owner->Latitude / 90.0f) * 2.0f;

	Owner->CalculatedSunriseTime = 6.0f - LatitudeOffset;
	Owner->CalculatedSunsetTime = 18.0f + LatitudeOffset;

	Owner->SunriseTime =
		Owner->GetFormattedTimeAsString(Owner->CalculatedSunriseTime);

	Owner->SunsetTime =
		Owner->GetFormattedTimeAsString(Owner->CalculatedSunsetTime);
}

FRotator FTODSystem::CalculatePivotRotation(
	const ATODManager* Owner,
	float InTime) const
{
	float SafeTime = FMath::Fmod(InTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	float PitchAngle = 0.0f;

	bool bIsDaytime =
		(SafeTime >= Owner->CalculatedSunriseTime) &&
		(SafeTime < Owner->CalculatedSunsetTime);

	if (bIsDaytime)
	{
		PitchAngle = FMath::GetMappedRangeValueClamped(
			FVector2D(
				Owner->CalculatedSunriseTime,
				Owner->CalculatedSunsetTime),
			FVector2D(180.0f, 360.0f),
			SafeTime
		);
	}
	else
	{
		float TotalNightDuration =
			24.0f - (Owner->CalculatedSunsetTime - Owner->CalculatedSunriseTime);

		float ElapsedNightTime =
			(SafeTime >= Owner->CalculatedSunsetTime)
			? SafeTime - Owner->CalculatedSunsetTime
			: (24.0f - Owner->CalculatedSunsetTime) + SafeTime;

		PitchAngle = FMath::GetMappedRangeValueClamped(
			FVector2D(0.0f, TotalNightDuration),
			FVector2D(0.0f, 180.0f),
			ElapsedNightTime
		);
	}

	return FRotator(0.0f, PitchAngle, 0.0f);
}

void FTODSystem::UpdateState(ATODManager* Owner, float CurrentTime)
{
	if (!Owner) return;

	float SafeTime = FMath::Fmod(CurrentTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	float DawnStart = Owner->CalculatedSunriseTime - Owner->TransitionDuration;
	float SunriseEnd = Owner->CalculatedSunriseTime + Owner->TransitionDuration;

	float SunsetStart = Owner->CalculatedSunsetTime - Owner->TransitionDuration;
	float DuskEnd = Owner->CalculatedSunsetTime + Owner->TransitionDuration;

	if (SafeTime >= DawnStart && SafeTime < Owner->CalculatedSunriseTime)
	{
		Owner->CurrentState = ETODState::Dawn;
	}
	else if (SafeTime >= Owner->CalculatedSunriseTime && SafeTime < SunriseEnd)
	{
		Owner->CurrentState = ETODState::Sunrise;
	}
	else if (SafeTime >= SunriseEnd && SafeTime < SunsetStart)
	{
		Owner->CurrentState = ETODState::Day;
	}
	else if (SafeTime >= SunsetStart && SafeTime < Owner->CalculatedSunsetTime)
	{
		Owner->CurrentState = ETODState::Sunset;
	}
	else if (SafeTime >= Owner->CalculatedSunsetTime && SafeTime < DuskEnd)
	{
		Owner->CurrentState = ETODState::Dusk;
	}
	else
	{
		Owner->CurrentState = ETODState::Night;
	}
}

void FTODSystem::UpdateTOD(ATODManager* Owner, float CurrentTime)
{
	if (!Owner || Owner->TOD_DataArray.Num() == 0) return;

	Owner->CurrentSystemTime = CurrentTime;

	UpdateState(Owner, CurrentTime);

	if (!Owner->SkyLightComponent)
	{
		FindComponents(Owner);
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

	if (IsValid(Owner->SunLightComponent))
	{
		if (!Owner->SunLightComponent->bAtmosphereSunLight)
		{
			Owner->SunLightComponent->SetAtmosphereSunLight(true);
			Owner->SunLightComponent->MarkRenderStateDirty();
		}

		Owner->SunLightComponent->SetIntensity(Sun.Intensity);
		Owner->SunLightComponent->SetLightColor(Sun.Light_Color);
		Owner->SunLightComponent->SetLightSourceAngle(Sun.Source_Angle);
		Owner->SunLightComponent->SetLightSourceSoftAngle(Sun.Source_Soft_Angle);
		Owner->SunLightComponent->SetIndirectLightingIntensity(Sun.Indirect_Light_Intensity);
	}

	if (IsValid(Owner->MoonLightComponent))
	{
		// 달의 대기 산란 영향 차단 (붉은 달 방지)
		if (Owner->MoonLightComponent->bAtmosphereSunLight)
		{
			Owner->MoonLightComponent->SetAtmosphereSunLight(false);
			Owner->MoonLightComponent->MarkRenderStateDirty();
		}
		Owner->MoonLightComponent->SetAtmosphereSunLightIndex(1);
		Owner->MoonLightComponent->bPerPixelAtmosphereTransmittance = false;

		Owner->MoonLightComponent->SetIntensity(Moon.Intensity);
		Owner->MoonLightComponent->SetLightColor(Moon.Light_Color);
		Owner->MoonLightComponent->SetLightSourceAngle(Moon.Source_Angle);
		Owner->MoonLightComponent->SetLightSourceSoftAngle(Moon.Source_Soft_Angle);
		Owner->MoonLightComponent->SetIndirectLightingIntensity(Moon.Indirect_Light_Intensity);

		if (IsValid(Owner->MoonMaterialInstance))
		{
			//Owner->MoonMaterialInstance->SetScalarParameterValue(TEXT("MoonEmissiveColor"), FinalMoonSourceScale);
			Owner->MoonMaterialInstance->SetScalarParameterValue(TEXT("MoonSourceEmissiveIntensity"), Moon.Moon_Source_Emissive_Intensity);
		}
	}

	// 공통 환경
	if (IsValid(Owner->SkyLightComponent))
	{
		Owner->SkyLightComponent->SetIntensity(Sky.Sky_Light_Intensity);
		Owner->SkyLightComponent->SetLightColor(Sky.Sky_Light_Color);
		Owner->SkyLightComponent->SetIndirectLightingIntensity(Sky.Sky_Indirect_Lighting_Intensity);
		Owner->SkyLightComponent->SetVolumetricScatteringIntensity(Sky.Sky_Volumetric_Scattering_Intensity);
		if (IsValid(Owner->SkyMaterialInstance))
		{
			Owner->SkyMaterialInstance->SetScalarParameterValue(TEXT("SkyTextureEmissiveIntensity"), Sky.Sky_Texture_Emissive_Intensity);
		}
	}

	if (IsValid(Owner->FogComponent))
	{
		Owner->FogComponent->SetFogDensity(Fog.Fog_Density);
		Owner->FogComponent->SetFogHeightFalloff(Fog.Fog_Height_Falloff);
		Owner->FogComponent->SetFogInscatteringColor(Fog.Fog_Inscattering_Color);
		Owner->FogComponent->SetDirectionalInscatteringColor(Fog.Fog_Directional_Inscattering);
	}

	if (IsValid(Owner->SkyAtmosphereComponent))
	{
		Owner->SkyAtmosphereComponent->SetMieScatteringScale(Atmos.Mie_Scattering_Scale);
		Owner->SkyAtmosphereComponent->SetMieScattering(Atmos.Mie_Scattering_Color);
		Owner->SkyAtmosphereComponent->SetOtherAbsorption(Atmos.Absorption_Color);
		Owner->SkyAtmosphereComponent->SetRayleighScatteringScale(Atmos.Rayleigh_Scattering_Scale);
		Owner->SkyAtmosphereComponent->SetAerialPespectiveViewDistanceScale(Atmos.Aerial_Perspective_Distance_Scale);
		Owner->SkyAtmosphereComponent->SetSkyLuminanceFactor(Atmos.Sky_Luminance_Factor);
	}

	Owner->OnUpdateCustomMaterials(CurrentTime);

}