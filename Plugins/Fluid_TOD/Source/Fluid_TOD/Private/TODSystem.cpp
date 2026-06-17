#include "TODSystem.h"
#include "TODManager.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

void FTODSystem::FindComponents(ATODManager* Owner)
{
	if (!Owner) return;

	// Sun & Moon
	TArray<UDirectionalLightComponent*> Lights;
	Owner->GetComponents<UDirectionalLightComponent>(Lights);

	Owner->SunLightComponent = nullptr;
	Owner->MoonLightComponent = nullptr;

	for (UDirectionalLightComponent* Light : Lights)
	{
		if (Light->ComponentHasTag(TEXT("Moon"))) Owner->MoonLightComponent = Light;
		else if (Light->ComponentHasTag(TEXT("Sun"))) Owner->SunLightComponent = Light;
		if (IsValid(Owner->SunLightComponent) && IsValid(Owner->MoonLightComponent)) break;
	}

	// SkyDome & Moon Mesh
	TArray<UStaticMeshComponent*> Meshes;
	Owner->GetComponents<UStaticMeshComponent>(Meshes);

	Owner->SkyDomeMesh = nullptr;
	Owner->MoonMesh = nullptr;

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
	}

	// SkyLight, Fog, SkyAtmosphere
	Owner->SkyLightComponent = Owner->FindComponentByClass<USkyLightComponent>();
	Owner->FogComponent = Owner->FindComponentByClass<UExponentialHeightFogComponent>();
	Owner->SkyAtmosphereComponent = Owner->FindComponentByClass<USkyAtmosphereComponent>();

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

float FTODSystem::NormalizeTime(float Time)
{
	float SafeTime = FMath::Fmod(Time, 24.0f);
	return SafeTime < 0.f ? SafeTime + 24.f : SafeTime;
}

FRotator FTODSystem::CalculatePivotRotation(
	const ATODManager* Owner,
	float InTime) const
{
	const float SafeTime = NormalizeTime(InTime);

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

	const float SafeTime = NormalizeTime(CurrentTime);

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

	if (Owner->bSequencerOverride) return;

	Owner->CurrentSystemTime = CurrentTime;

	UpdateState(Owner, CurrentTime);

	if (
		!IsValid(Owner->SunLightComponent) ||
		!IsValid(Owner->MoonLightComponent) ||
		!IsValid(Owner->SkyLightComponent) ||
		!IsValid(Owner->FogComponent) ||
		!IsValid(Owner->SkyAtmosphereComponent) ||
		!IsValid(Owner->SkyDomeMesh) ||
		!IsValid(Owner->MoonMesh)
		)
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

	if (IsValid(Owner->SkyMaterialInstance))
	{
		Owner->SkyMaterialInstance->SetScalarParameterValue(
			TEXT("SkyTextureEmissiveIntensity"),
			Sky.SkyDome_Texture_Emissive_Intensity
		);
	}

	if (IsValid(Owner->MoonMaterialInstance))
	{
		Owner->MoonMaterialInstance->SetScalarParameterValue(
			TEXT("MoonSourceEmissiveIntensity"),
			Moon.Moon_Source_Emissive_Intensity
		);

		if (IsValid(Owner->SunLightComponent))
		{
			const FVector SunDirection =
				-Owner->SunLightComponent->GetForwardVector();

			Owner->MoonMaterialInstance->SetVectorParameterValue(
				TEXT("SunDirection"),
				FLinearColor(
					SunDirection.X,
					SunDirection.Y,
					SunDirection.Z,
					0.0f
				)
			);
		}
	}

	// Sun
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

	// Moon
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
	}

	// Sky Light
	if (IsValid(Owner->SkyLightComponent))
	{
		Owner->SkyLightComponent->SetIntensity(Sky.Sky_Light_Intensity);
		Owner->SkyLightComponent->SetLightColor(Sky.Sky_Light_Color);
		Owner->SkyLightComponent->SetIndirectLightingIntensity(Sky.Sky_Indirect_Lighting_Intensity);
		Owner->SkyLightComponent->SetVolumetricScatteringIntensity(Sky.Sky_Volumetric_Scattering_Intensity);
	}

	// Fog
	if (IsValid(Owner->FogComponent))
	{
		Owner->FogComponent->SetFogDensity(Fog.Fog_Density);
		Owner->FogComponent->SetFogHeightFalloff(Fog.Fog_Height_Falloff);
		Owner->FogComponent->SetFogInscatteringColor(Fog.Fog_Inscattering_Color);
		Owner->FogComponent->SetDirectionalInscatteringColor(Fog.Fog_Directional_Inscattering);
	}

	// Sky Atmosphere
	if (IsValid(Owner->SkyAtmosphereComponent))
	{
		Owner->SkyAtmosphereComponent->SetMieScatteringScale(Atmos.Mie_Scattering_Scale);
		Owner->SkyAtmosphereComponent->SetMieScattering(Atmos.Mie_Scattering_Color);
		Owner->SkyAtmosphereComponent->SetOtherAbsorption(Atmos.Absorption_Color);
		Owner->SkyAtmosphereComponent->SetRayleighScatteringScale(Atmos.Rayleigh_Scattering_Scale);
		Owner->SkyAtmosphereComponent->SetAerialPespectiveViewDistanceScale(Atmos.Aerial_Perspective_Distance_Scale);
		Owner->SkyAtmosphereComponent->SetSkyLuminanceFactor(Atmos.Sky_Luminance_Factor);
	}

	// Custom Material Updates
	Owner->OnUpdateCustomMaterials(CurrentTime);

}