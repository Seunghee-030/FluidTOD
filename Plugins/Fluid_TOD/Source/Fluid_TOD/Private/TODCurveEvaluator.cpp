#include "TODCurveEvaluator.h"
#include "TODManager.h"
#include "MyBlueprintFunctionLibrary.h"

#if WITH_EDITOR
#include "Editor.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

namespace
{
	constexpr float TODHours = 24.0f;
	constexpr float TODBoundaryTolerance = 0.001f;

	float NormalizeTODTimeForBake(float Time)
	{
		float SafeTime = FMath::Fmod(Time, TODHours);
		if (SafeTime < 0.0f)
		{
			SafeTime += TODHours;
		}

		if (FMath::IsNearlyEqual(SafeTime, TODHours, TODBoundaryTolerance) ||
			FMath::IsNearlyEqual(SafeTime, 0.0f, TODBoundaryTolerance))
		{
			return 0.0f;
		}

		return SafeTime;
	}

	bool IsTwentyFourBoundary(float Time)
	{
		return FMath::IsNearlyEqual(Time, TODHours, TODBoundaryTolerance);
	}

	void AddTwentyFourBoundaryFromEarliest(TArray<FTODMasterData>& DataArray)
	{
		if (DataArray.Num() == 0) return;

		if (IsTwentyFourBoundary(DataArray.Last().Time)) return;

		FTODMasterData BoundaryData = DataArray[0];
		BoundaryData.Time = TODHours;
		DataArray.Add(BoundaryData);
	}

	// Canonical PPV Data 구조체
	struct FTODPPVEntry
	{
		float Time = 0.0f;
		APostProcessVolume* PPV = nullptr;
	};

	TArray<FTODPPVEntry> BuildCanonicalPPVData(const TArray<FTODMasterData>& SourceData)
	{
		struct FCanonicalPPVEntry
		{
			FTODPPVEntry Data;
			bool bCameFromTwentyFour = false;
		};

		TArray<FCanonicalPPVEntry> Entries;
		Entries.Reserve(SourceData.Num());

		for (const FTODMasterData& Source : SourceData)
		{
			if (!IsValid(Source.PPV))
			{
				continue;
			}

			const bool bCameFromTwentyFour = IsTwentyFourBoundary(Source.Time);
			const float NormalizedTime = NormalizeTODTimeForBake(Source.Time);

			const int32 ExistingIndex = Entries.IndexOfByPredicate(
				[NormalizedTime](const FCanonicalPPVEntry& Entry)
				{
					return FMath::IsNearlyEqual(Entry.Data.Time, NormalizedTime, TODBoundaryTolerance);
				});

			if (ExistingIndex == INDEX_NONE)
			{
				Entries.Add({ FTODPPVEntry{ NormalizedTime, Source.PPV }, bCameFromTwentyFour });
			}
			else if (Entries[ExistingIndex].bCameFromTwentyFour && !bCameFromTwentyFour)
			{
				// 0h이 24h 자리를 대체
				Entries[ExistingIndex] = { FTODPPVEntry{ NormalizedTime, Source.PPV }, false };
			}
			else
			{
				// 예외
				UE_LOG(LogTemp, Warning, TEXT("Duplicate PPV entry at time %.3f. Dropping one of them."), NormalizedTime);
			}
		}

		TArray<FTODPPVEntry> Result;
		Result.Reserve(Entries.Num());
		for (const FCanonicalPPVEntry& Entry : Entries)
		{
			Result.Add(Entry.Data);
		}

		Result.Sort([](const FTODPPVEntry& A, const FTODPPVEntry& B)
			{
				return A.Time < B.Time;
			});

		return Result;
	}

	void AddTwentyFourBoundaryFromEarliestPPV(TArray<FTODPPVEntry>& DataArray)
	{
		if (DataArray.Num() == 0) return;

		if (IsTwentyFourBoundary(DataArray.Last().Time)) return;

		FTODPPVEntry BoundaryData = DataArray[0];
		BoundaryData.Time = TODHours;
		DataArray.Add(BoundaryData);
	}

	TArray<FTODMasterData> BuildCanonicalTODData(
		const TArray<FTODMasterData>& SourceData,
		bool bRequireValidPPV,
		TArray<FString>* OutDroppedNames = nullptr)
	{
		struct FCanonicalEntry
		{
			FTODMasterData Data;
			bool bCameFromTwentyFour = false;
		};

		TArray<FCanonicalEntry> Entries;

		for (const FTODMasterData& Source : SourceData)
		{
			if (bRequireValidPPV && !IsValid(Source.PPV))
			{
				continue;
			}

			FTODMasterData Copy = Source;
			const bool bCameFromTwentyFour = IsTwentyFourBoundary(Copy.Time);
			Copy.Time = NormalizeTODTimeForBake(Copy.Time);

			const int32 ExistingIndex = Entries.IndexOfByPredicate(
				[&Copy](const FCanonicalEntry& Entry)
				{
					return FMath::IsNearlyEqual(Entry.Data.Time, Copy.Time, TODBoundaryTolerance);
				});

			if (ExistingIndex == INDEX_NONE)
			{
				FCanonicalEntry NewEntry;
				NewEntry.Data = Copy;
				NewEntry.bCameFromTwentyFour = bCameFromTwentyFour;
				Entries.Add(NewEntry);
			}
			else if (Entries[ExistingIndex].bCameFromTwentyFour && !bCameFromTwentyFour)
			{
				// 0h이 24h 자리를 대체
				Entries[ExistingIndex].Data = Copy;
				Entries[ExistingIndex].bCameFromTwentyFour = false;
			}
			else
			{
				// 예외
				if (OutDroppedNames)
				{
					OutDroppedNames->Add(Copy.Name.IsEmpty() ? TEXT("(Unnamed)") : Copy.Name);
				}
			}
		}

		TArray<FTODMasterData> Result;
		for (const FCanonicalEntry& Entry : Entries)
		{
			Result.Add(Entry.Data);
		}

		Result.Sort([](const FTODMasterData& A, const FTODMasterData& B)
			{
				return A.Time < B.Time;
			});

		return Result;
	}

	void FlattenSeamTangentRich(FRichCurve* Rich)
	{
		if (!Rich || Rich->GetNumKeys() < 2) return;

		FKeyHandle FirstHandle = Rich->GetFirstKeyHandle();
		FKeyHandle LastHandle = Rich->GetLastKeyHandle();

		if (FMath::IsNearlyEqual(Rich->GetKey(FirstHandle).Value, Rich->GetKey(LastHandle).Value, KINDA_SMALL_NUMBER))
		{
			Rich->SetKeyTangentMode(FirstHandle, RCTM_User);
			Rich->SetKeyTangentMode(LastHandle, RCTM_User);
			Rich->SetKeyInterpMode(FirstHandle, RCIM_Cubic);
			Rich->SetKeyInterpMode(LastHandle, RCIM_Cubic);

			FRichCurveKey& FirstKey = Rich->GetKey(FirstHandle);
			FRichCurveKey& LastKey = Rich->GetKey(LastHandle);
			FirstKey.ArriveTangent = FirstKey.LeaveTangent = 0.0f;
			LastKey.ArriveTangent = LastKey.LeaveTangent = 0.0f;
		}
	}

	void FlattenSeamTangent(FRuntimeFloatCurve& InCurve)
	{
		FlattenSeamTangentRich(InCurve.GetRichCurve());
	}

	void FlattenSeamTangentColor(FRuntimeCurveLinearColor& InCurve)
	{
		for (int32 i = 0; i < 4; ++i)
		{
			FlattenSeamTangentRich(&InCurve.ColorCurves[i]);
		}
	}

	// 0h/24h 경계 키 InterpMode 동기화
	void MirrorBoundaryInterpMode(FRichCurve* Rich)
	{
		if (!Rich || Rich->GetNumKeys() < 2) return;

		const FKeyHandle FirstHandle = Rich->GetFirstKeyHandle();
		const FKeyHandle LastHandle = Rich->GetLastKeyHandle();

		if (FMath::IsNearlyEqual(Rich->GetKeyTime(FirstHandle), 0.0f, TODBoundaryTolerance) &&
			FMath::IsNearlyEqual(Rich->GetKeyTime(LastHandle), TODHours, TODBoundaryTolerance))
		{
			Rich->SetKeyInterpMode(LastHandle, Rich->GetKeyInterpMode(FirstHandle));
		}
	}

	void FixCyclicSeamTangents(FRichCurve* Rich)
	{
		if (!Rich) return;

		const int32 NumKeys = Rich->GetNumKeys();
		if (NumKeys < 2) return;

		if (NumKeys < 3)
		{
			FlattenSeamTangentRich(Rich);
			return;
		}

		FKeyHandle FirstHandle = Rich->GetFirstKeyHandle();
		FKeyHandle LastHandle = Rich->GetLastKeyHandle();

		const float FirstTime = Rich->GetKeyTime(FirstHandle);
		const float LastTime = Rich->GetKeyTime(LastHandle);

		if (!FMath::IsNearlyEqual(FirstTime, 0.0f, TODBoundaryTolerance) ||
			!FMath::IsNearlyEqual(LastTime, TODHours, TODBoundaryTolerance))
		{
			FlattenSeamTangentRich(Rich);
			return;
		}

		TArray<TPair<float, float>> Snapshot;
		for (auto It = Rich->GetKeyIterator(); It; ++It)
		{
			Snapshot.Add(TPair<float, float>(It->Time, It->Value));
		}

		const TPair<float, float> SecondKey = Snapshot[1];
		const TPair<float, float> SecondLastKey = Snapshot[Snapshot.Num() - 2];
		const FKeyHandle PadAfterHandle = Rich->AddKey(SecondKey.Key + TODHours, SecondKey.Value);
		const FKeyHandle PadBeforeHandle = Rich->AddKey(SecondLastKey.Key - TODHours, SecondLastKey.Value);

		Rich->SetKeyTangentMode(FirstHandle, RCTM_Auto);
		Rich->SetKeyTangentMode(LastHandle, RCTM_Auto);

		Rich->AutoSetTangents(0.0f);
		Rich->SetKeyTangentMode(FirstHandle, RCTM_User);
		Rich->SetKeyTangentMode(LastHandle, RCTM_User);

		Rich->DeleteKey(PadAfterHandle);
		Rich->DeleteKey(PadBeforeHandle);
	}

	void ApplyPPVCompensation(ATODManager* Owner, float CurrentTime)
	{
		if (!Owner || !IsValid(Owner->RuntimePPVComponent))
		{
			return;
		}

		const float SafeTime = NormalizeTODTimeForBake(CurrentTime);
		FPostProcessSettings& Settings = Owner->RuntimePPVComponent->Settings;

		// 노출 보정 (가산)
		if (const FRichCurve* Curve = Owner->PPV_ExposureCompensationCurve.GetRichCurveConst())
		{
			if (Curve->GetNumKeys() > 0)
			{
				Settings.bOverride_AutoExposureBias = true;
				Settings.AutoExposureBias += Curve->Eval(SafeTime);
			}
		}

		// 밝기 보정 (배율)
		if (const FRichCurve* Curve = Owner->PPV_BrightnessCompensationCurve.GetRichCurveConst())
		{
			if (Curve->GetNumKeys() > 0)
			{
				Settings.bOverride_BloomIntensity = true;
				Settings.BloomIntensity *= Curve->Eval(SafeTime);
			}
		}

		// 색온도 보정 (가산)
		if (const FRichCurve* Curve = Owner->PPV_WhiteTempCompensationCurve.GetRichCurveConst())
		{
			if (Curve->GetNumKeys() > 0)
			{
				Settings.bOverride_WhiteTemp = true;
				Settings.WhiteTemp += Curve->Eval(SafeTime);
			}
		}

		// 색감 보정 (RGBA 배율)
		bool bHasColorCompensation = false;
		for (int32 i = 0; i < 4; ++i)
		{
			if (Owner->PPV_ColorGradingCompensationCurve.ColorCurves[i].GetNumKeys() > 0)
			{
				bHasColorCompensation = true;
				break;
			}
		}

		if (bHasColorCompensation)
		{
			const FLinearColor Comp = Owner->PPV_ColorGradingCompensationCurve.GetLinearColorValue(SafeTime);
			Settings.bOverride_ColorSaturation = true;
			Settings.ColorSaturation *= FVector4(Comp.R, Comp.G, Comp.B, Comp.A);
		}
	}
}

TArray<FRuntimeFloatCurve*> FTODCurveEvaluator::GetAllFloatCurves(UTODCurveContainer* CurveData)
{
	if (!CurveData) return {};

	return {
		&CurveData->SunCurves.IntensityCurve, &CurveData->SunCurves.SourceAngleCurve, &CurveData->SunCurves.SourceSoftAngleCurve, &CurveData->SunCurves.IndirectIntensityCurve,
		&CurveData->MoonCurves.IntensityCurve, &CurveData->MoonCurves.SourceAngleCurve, &CurveData->MoonCurves.SourceSoftAngleCurve, &CurveData->MoonCurves.IndirectIntensityCurve, &CurveData->MoonCurves.SourceScaleCurve, &CurveData->MoonCurves.SourceEmissiveIntensityCurve,
		&CurveData->SkyLightCurves.IntensityCurve, &CurveData->SkyLightCurves.IndirectIntensityCurve, &CurveData->SkyLightCurves.VolumetricScatteringIntensityCurve, &CurveData->SkyLightCurves.TextureEmissiveIntensityCurve,
		&CurveData->FogCurves.DensityCurve, &CurveData->FogCurves.HeightFalloffCurve,
		&CurveData->SkyAtmosphereCurves.MieScatteringScaleCurve, &CurveData->SkyAtmosphereCurves.RayleighScatteringScaleCurve, &CurveData->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve
	};
}

TArray<FRuntimeCurveLinearColor*> FTODCurveEvaluator::GetAllColorCurves(UTODCurveContainer* CurveData)
{
	if (!CurveData) return {};

	return {
		&CurveData->SunCurves.LightColorCurve, &CurveData->MoonCurves.LightColorCurve, &CurveData->SkyLightCurves.LightColorCurve, &CurveData->FogCurves.InscatteringColorCurve, &CurveData->FogCurves.DirectionalColorCurve,
		&CurveData->SkyAtmosphereCurves.MieScatteringColorCurve, &CurveData->SkyAtmosphereCurves.AbsorptionColorCurve, &CurveData->SkyAtmosphereCurves.SkyLuminanceFactorCurve
	};
}

FTODCurveDataModeSnapshot FTODCurveEvaluator::CaptureInterpModes(UTODCurveContainer* CurveData)
{
	FTODCurveDataModeSnapshot Snapshot;
	if (!CurveData) return Snapshot;

	for (FRuntimeFloatCurve* Curve : GetAllFloatCurves(CurveData))
	{
		FTODSingleCurveModeList List;
		if (const FRichCurve* Rich = Curve->GetRichCurveConst())
		{
			for (auto It = Rich->GetKeyIterator(); It; ++It)
			{
				FTODCurveKeyMode KeyMode;
				KeyMode.Time = It->Time;
				KeyMode.InterpMode = It->InterpMode;
				List.Keys.Add(KeyMode);
			}
		}
		Snapshot.FloatCurveModes.Add(MoveTemp(List));
	}

	for (FRuntimeCurveLinearColor* Curve : GetAllColorCurves(CurveData))
	{
		for (int32 Ch = 0; Ch < 4; ++Ch)
		{
			FTODSingleCurveModeList List;
			const FRichCurve& Rich = Curve->ColorCurves[Ch];
			for (auto It = Rich.GetKeyIterator(); It; ++It)
			{
				FTODCurveKeyMode KeyMode;
				KeyMode.Time = It->Time;
				KeyMode.InterpMode = It->InterpMode;
				List.Keys.Add(KeyMode);
			}
			Snapshot.ColorCurveModes.Add(MoveTemp(List));
		}
	}

	return Snapshot;
}

void FTODCurveEvaluator::RestoreInterpModes(UTODCurveContainer* CurveData, const FTODCurveDataModeSnapshot& Snapshot)
{
	if (!CurveData) return;

	auto ApplyToRichCurve = [](FRichCurve* Rich, const FTODSingleCurveModeList& List)
		{
			if (!Rich) return;
			for (const FTODCurveKeyMode& KeyMode : List.Keys)
			{
				const FKeyHandle Handle = Rich->FindKey(KeyMode.Time, TODBoundaryTolerance);
				if (Rich->IsKeyHandleValid(Handle))
				{
					Rich->SetKeyInterpMode(Handle, KeyMode.InterpMode);
				}
			}
		};

	TArray<FRuntimeFloatCurve*> FloatCurves = GetAllFloatCurves(CurveData);
	for (int32 i = 0; i < FloatCurves.Num() && i < Snapshot.FloatCurveModes.Num(); ++i)
	{
		ApplyToRichCurve(FloatCurves[i]->GetRichCurve(), Snapshot.FloatCurveModes[i]);
	}

	TArray<FRuntimeCurveLinearColor*> ColorCurves = GetAllColorCurves(CurveData);
	int32 ColorListIdx = 0;
	for (FRuntimeCurveLinearColor* Curve : ColorCurves)
	{
		for (int32 Ch = 0; Ch < 4; ++Ch, ++ColorListIdx)
		{
			if (Snapshot.ColorCurveModes.IsValidIndex(ColorListIdx))
			{
				ApplyToRichCurve(&Curve->ColorCurves[Ch], Snapshot.ColorCurveModes[ColorListIdx]);
			}
		}
	}
}

void FTODCurveEvaluator::ApplyPPVBlending(ATODManager* Owner, float CurrentTime)
{
	if (!Owner || !IsValid(Owner->RuntimePPVComponent)) return;

	TArray<FTODPPVEntry> ValidPPVs = BuildCanonicalPPVData(Owner->TOD_DataArray);
	AddTwentyFourBoundaryFromEarliestPPV(ValidPPVs);

	const int32 Num = ValidPPVs.Num();
	if (Num == 0)
	{
		// TOD 데이터가 모두 삭제되면 런타임 PPV 리셋
		Owner->RuntimePPVComponent->bEnabled = false;
		Owner->RuntimePPVComponent->BlendWeight = 0.0f;
		Owner->RuntimePPVComponent->Settings = FPostProcessSettings();
		return;
	}

	for (const FTODPPVEntry& Data : ValidPPVs)
	{
		if (!IsValid(Data.PPV)) continue;

		Data.PPV->bEnabled = true;
		Data.PPV->bUnbound = true;
		Data.PPV->Priority = 1.0f;
		Data.PPV->BlendWeight = 0.0f;
	}

	// PPV 1개뿐 일 때.
	if (Num == 1)
	{
		APostProcessVolume* OnlyPPV = ValidPPVs[0].PPV;
		if (!IsValid(OnlyPPV)) return;

		Owner->RuntimePPVComponent->bEnabled = true;
		Owner->RuntimePPVComponent->bUnbound = true;
		Owner->RuntimePPVComponent->Priority = 1.0f;
		Owner->RuntimePPVComponent->BlendWeight = 1.0f;
		Owner->RuntimePPVComponent->Settings = OnlyPPV->Settings;
		return;
	}

	const float SafeTime = NormalizeTODTimeForBake(CurrentTime);

	int32 PrevIndex = Num - 1;
	int32 NextIndex = 0;

	for (int32 i = 0; i < Num; ++i)
	{
		if (SafeTime < ValidPPVs[i].Time)
		{
			NextIndex = i;
			PrevIndex = (i == 0) ? (Num - 1) : (i - 1);
			break;
		}
	}

	if (SafeTime >= ValidPPVs[Num - 1].Time)
	{
		PrevIndex = Num - 1;
		NextIndex = 0;
	}

	float PrevTime = ValidPPVs[PrevIndex].Time;
	float NextTime = ValidPPVs[NextIndex].Time;

	float Range = NextTime - PrevTime;
	while (Range <= 0.0f) Range += TODHours;

	float Elapsed = SafeTime - PrevTime;
	while (Elapsed < 0.0f) Elapsed += TODHours;

	const float RawAlpha = FMath::Clamp(Elapsed / Range, 0.0f, 1.0f);

	const float Alpha = RawAlpha;

	APostProcessVolume* PrevPPV = ValidPPVs[PrevIndex].PPV;
	APostProcessVolume* NextPPV = ValidPPVs[NextIndex].PPV;

	if (!IsValid(PrevPPV) || !IsValid(NextPPV)) return;

	Owner->RuntimePPVComponent->bEnabled = true;
	Owner->RuntimePPVComponent->bUnbound = true;
	Owner->RuntimePPVComponent->Priority = 1.0f;
	Owner->RuntimePPVComponent->BlendWeight = 1.0f;

	// 초기화
	Owner->RuntimePPVComponent->Settings = FPostProcessSettings();

#define LERP_PPV(Prop) \
	{ \
		const bool bPrevOverride = PrevPPV->Settings.bOverride_##Prop; \
		const bool bNextOverride = NextPPV->Settings.bOverride_##Prop; \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = bPrevOverride || bNextOverride; \
		if (bPrevOverride || bNextOverride) \
		{ \
			Owner->RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha); \
		} \
	}

#define LERP_VEC4_PPV(Prop) LERP_PPV(Prop)

#define LERP_PPV_FORCE_OVERRIDE(Prop) \
	{ \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = true; \
		Owner->RuntimePPVComponent->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha); \
	}

#define LERP_COLOR_PPV(Prop) \
	{ \
		const bool bPrevOverride = PrevPPV->Settings.bOverride_##Prop; \
		const bool bNextOverride = NextPPV->Settings.bOverride_##Prop; \
		Owner->RuntimePPVComponent->Settings.bOverride_##Prop = bPrevOverride || bNextOverride; \
		if (bPrevOverride || bNextOverride) \
		{ \
			Owner->RuntimePPVComponent->Settings.Prop = FLinearColor::LerpUsingHSV(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha); \
		} \
	}

	// Exposure / EV100
	LERP_PPV_FORCE_OVERRIDE(AutoExposureMinBrightness);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureMaxBrightness);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureBias);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureSpeedUp);
	LERP_PPV_FORCE_OVERRIDE(AutoExposureSpeedDown);

	// Bloom
	LERP_PPV(BloomIntensity);
	LERP_PPV(BloomThreshold);
	LERP_PPV(BloomSizeScale);
	LERP_PPV(BloomConvolutionIntensity);

	// White Balance
	LERP_PPV(WhiteTemp);
	LERP_PPV(WhiteTint);

	// Color Grading
	LERP_VEC4_PPV(ColorSaturation);
	LERP_VEC4_PPV(ColorContrast);
	LERP_VEC4_PPV(ColorGamma);
	LERP_VEC4_PPV(ColorGain);
	LERP_VEC4_PPV(ColorOffset);

	// Shadows
	LERP_VEC4_PPV(ColorSaturationShadows);
	LERP_VEC4_PPV(ColorContrastShadows);
	LERP_VEC4_PPV(ColorGammaShadows);
	LERP_VEC4_PPV(ColorGainShadows);
	LERP_VEC4_PPV(ColorOffsetShadows);

	// Midtones
	LERP_VEC4_PPV(ColorSaturationMidtones);
	LERP_VEC4_PPV(ColorContrastMidtones);
	LERP_VEC4_PPV(ColorGammaMidtones);
	LERP_VEC4_PPV(ColorGainMidtones);
	LERP_VEC4_PPV(ColorOffsetMidtones);

	// Highlights
	LERP_VEC4_PPV(ColorSaturationHighlights);
	LERP_VEC4_PPV(ColorContrastHighlights);
	LERP_VEC4_PPV(ColorGammaHighlights);
	LERP_VEC4_PPV(ColorGainHighlights);
	LERP_VEC4_PPV(ColorOffsetHighlights);

	// Lens & Effects
	LERP_PPV(VignetteIntensity);
	LERP_PPV(FilmGrainIntensity);
	LERP_PPV(FilmGrainTexelSize);
	LERP_PPV(SceneFringeIntensity);
	LERP_PPV(LensFlareIntensity);
	LERP_PPV(AmbientOcclusionIntensity);
	LERP_PPV(IndirectLightingIntensity);
	LERP_PPV(MotionBlurAmount);

	// Indirect Color
	LERP_COLOR_PPV(IndirectLightingColor);

	// Lumen
	LERP_PPV(LumenSceneLightingQuality);
	LERP_PPV(LumenSceneDetail);

	// Depth of Field
	LERP_PPV(DepthOfFieldFocalDistance);
	LERP_PPV(DepthOfFieldFstop);
	LERP_PPV(DepthOfFieldMinFstop);
	LERP_PPV(DepthOfFieldSensorWidth);
	LERP_PPV(DepthOfFieldDepthBlurAmount);
	LERP_PPV(DepthOfFieldDepthBlurRadius);

	// Local Exposure / Film Tonemapper
	LERP_PPV(LocalExposureHighlightContrastScale);
	LERP_PPV(LocalExposureShadowContrastScale);
	LERP_PPV(LocalExposureDetailStrength);
	LERP_PPV(LocalExposureMiddleGreyBias);
	LERP_PPV(FilmSlope);
	LERP_PPV(FilmToe);
	LERP_PPV(FilmShoulder);
	LERP_PPV(FilmBlackClip);
	LERP_PPV(FilmWhiteClip);

	// Lens Flare / 기타 렌즈 이펙트
	LERP_PPV(LensFlareBokehSize);
	LERP_PPV(LensFlareThreshold);
	LERP_COLOR_PPV(LensFlareTint);

	// Film Grain 확장
	LERP_PPV(FilmGrainIntensityShadows);
	LERP_PPV(FilmGrainIntensityMidtones);
	LERP_PPV(FilmGrainIntensityHighlights);
	LERP_PPV(FilmGrainShadowsMax);
	LERP_PPV(FilmGrainHighlightsMin);
	LERP_PPV(FilmGrainHighlightsMax);

	// Scene Color / Chromatic Aberration
	LERP_COLOR_PPV(SceneColorTint);
	LERP_PPV(ChromaticAberrationStartOffset);

	// Color Grading 경계값 / 기타
	LERP_PPV(ColorCorrectionShadowsMax);
	LERP_PPV(ColorCorrectionHighlightsMin);
	LERP_PPV(ColorCorrectionHighlightsMax);
	LERP_PPV(BlueCorrection);
	LERP_PPV(ExpandGamut);
	LERP_PPV(ToneCurveAmount);

	// Bloom 커널 (Standard 방식)
	LERP_PPV(Bloom1Size);
	LERP_PPV(Bloom2Size);
	LERP_PPV(Bloom3Size);
	LERP_PPV(Bloom4Size);
	LERP_PPV(Bloom5Size);
	LERP_PPV(Bloom6Size);
	LERP_COLOR_PPV(Bloom1Tint);
	LERP_COLOR_PPV(Bloom2Tint);
	LERP_COLOR_PPV(Bloom3Tint);
	LERP_COLOR_PPV(Bloom4Tint);
	LERP_COLOR_PPV(Bloom5Tint);
	LERP_COLOR_PPV(Bloom6Tint);

	// Ambient Occlusion 세부값
	LERP_PPV(AmbientOcclusionRadius);
	LERP_PPV(AmbientOcclusionStaticFraction);
	LERP_PPV(AmbientOcclusionBias);
	LERP_PPV(AmbientOcclusionPower);
	LERP_PPV(AmbientOcclusionFadeDistance);
	LERP_PPV(AmbientOcclusionFadeRadius);

	// Screen Space Reflection
	LERP_PPV(ScreenSpaceReflectionIntensity);

	// Local Exposure 추가값
	LERP_PPV(LocalExposureBlurredLuminanceBlend);

	// Motion Blur 추가값
	LERP_PPV(MotionBlurMax);

#undef LERP_PPV
#undef LERP_VEC4_PPV
#undef LERP_PPV_FORCE_OVERRIDE
#undef LERP_COLOR_PPV

	ApplyPPVCompensation(Owner, CurrentTime);
}

void FTODCurveEvaluator::BakeTODCurves(ATODManager* Owner)
{
	if (!Owner || !Owner->CurveData)
	{
		return;
	}

	Owner->FindComponents();

	// 구조체 내부 커브 포인터 매핑 (그래프 동기화 로직과 동일한 순서를 공유)
	TArray<FRuntimeFloatCurve*> FloatCurves = GetAllFloatCurves(Owner->CurveData);
	TArray<FRuntimeCurveLinearColor*> ColorCurves = GetAllColorCurves(Owner->CurveData);

	// Clear 하기 전 InterpMode를 캡처 (리베이크 복원용)
	const FTODCurveDataModeSnapshot PreviousModes = CaptureInterpModes(Owner->CurveData);

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeFloatCurve(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::ClearRuntimeColorCurve(*Curve); }

	if (Owner->TOD_DataArray.Num() == 0) return;

	TArray<FString> DroppedNames;
	TArray<FTODMasterData> SortedCopy =
		BuildCanonicalTODData(Owner->TOD_DataArray, false, &DroppedNames);
	if (SortedCopy.Num() == 0) return;

	AddTwentyFourBoundaryFromEarliest(SortedCopy);

#if WITH_EDITOR
	if (DroppedNames.Num() > 0)
	{
		FNotificationInfo Info(FText::Format(
			FText::FromString(TEXT("The following items were ignored due to duplicate times: {0}")),
			FText::FromString(FString::Join(DroppedNames, TEXT(", ")))));
		Info.ExpireDuration = 5.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
#endif

	for (const FTODMasterData& Data : SortedCopy)
	{
		float T = Data.Time;

		float FinalSunIntensity = (Data.ActiveLightMode != ETODDirectionalLightType::MoonOnly) ? Data.Sun_Settings.Intensity : 0.0f;
		float FinalMoonIntensity = (Data.ActiveLightMode != ETODDirectionalLightType::SunOnly) ? Data.Moon_Settings.Intensity : 0.0f;

		// Sun
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.IntensityCurve, T, FinalSunIntensity);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.SourceAngleCurve, T, Data.Sun_Settings.Source_Angle);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.SourceSoftAngleCurve, T, Data.Sun_Settings.Source_Soft_Angle);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SunCurves.IndirectIntensityCurve, T, Data.Sun_Settings.Indirect_Light_Intensity);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SunCurves.LightColorCurve, T, Data.Sun_Settings.Light_Color);

		// Moon
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.IntensityCurve, T, FinalMoonIntensity);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceAngleCurve, T, Data.Moon_Settings.Source_Angle);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceSoftAngleCurve, T, Data.Moon_Settings.Source_Soft_Angle);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.IndirectIntensityCurve, T, Data.Moon_Settings.Indirect_Light_Intensity);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->MoonCurves.LightColorCurve, T, Data.Moon_Settings.Light_Color);

		float TargetMoonScale = (Data.ActiveLightMode == ETODDirectionalLightType::SunOnly) ? 0.0f : Data.Moon_Settings.Moon_Source_Scale;
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceScaleCurve, T, TargetMoonScale);

		float TargetMoonEmissive = (Data.ActiveLightMode == ETODDirectionalLightType::SunOnly) ? 0.0f : Data.Moon_Settings.Moon_Source_Emissive_Intensity;
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->MoonCurves.SourceEmissiveIntensityCurve, T, TargetMoonEmissive);

		// SkyLight
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.IntensityCurve, T, Data.SkyLight_Settings.Sky_Light_Intensity);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.IndirectIntensityCurve, T, Data.SkyLight_Settings.Sky_Indirect_Lighting_Intensity);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.VolumetricScatteringIntensityCurve, T, Data.SkyLight_Settings.Sky_Volumetric_Scattering_Intensity);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyLightCurves.LightColorCurve, T, Data.SkyLight_Settings.Sky_Light_Color);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyLightCurves.TextureEmissiveIntensityCurve, T, Data.SkyLight_Settings.SkyDome_Texture_Emissive_Intensity);

		// Fog
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->FogCurves.DensityCurve, T, Data.Fog_Settings.Fog_Density);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->FogCurves.HeightFalloffCurve, T, Data.Fog_Settings.Fog_Height_Falloff);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->FogCurves.InscatteringColorCurve, T, Data.Fog_Settings.Fog_Inscattering_Color);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->FogCurves.DirectionalColorCurve, T, Data.Fog_Settings.Fog_Directional_Inscattering);

		// SkyAtmosphere
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyAtmosphereCurves.MieScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Scale);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyAtmosphereCurves.RayleighScatteringScaleCurve, T, Data.SkyAtmosphere_Settings.Rayleigh_Scattering_Scale);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(Owner->CurveData->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve, T, Data.SkyAtmosphere_Settings.Aerial_Perspective_Distance_Scale);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyAtmosphereCurves.MieScatteringColorCurve, T, Data.SkyAtmosphere_Settings.Mie_Scattering_Color);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyAtmosphereCurves.AbsorptionColorCurve, T, Data.SkyAtmosphere_Settings.Absorption_Color);
		UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(Owner->CurveData->SkyAtmosphereCurves.SkyLuminanceFactorCurve, T, Data.SkyAtmosphere_Settings.Sky_Luminance_Factor);
	}

	// InterpMode 복원
	if (Owner->bApplyPresetCurveModesOnNextBake && IsValid(Owner->LoadPreset))
	{
		RestoreInterpModes(Owner->CurveData, Owner->LoadPreset->CurveInterpModes);
		Owner->bApplyPresetCurveModesOnNextBake = false;
	}
	else
	{
		RestoreInterpModes(Owner->CurveData, PreviousModes);
	}

	for (FRuntimeFloatCurve* Curve : FloatCurves) { UMyBlueprintFunctionLibrary::SealTODCurveFor24Hours(*Curve); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves) { UMyBlueprintFunctionLibrary::SealColorCurveFor24Hours(*Curve); }

	// 0h/24h 경계 키 InterpMode를 동기화
	for (FRuntimeFloatCurve* Curve : FloatCurves) { MirrorBoundaryInterpMode(Curve->GetRichCurve()); }
	for (FRuntimeCurveLinearColor* Curve : ColorCurves)
	{
		for (int32 i = 0; i < 4; ++i) { MirrorBoundaryInterpMode(&Curve->ColorCurves[i]); }
	}

	for (FRuntimeFloatCurve* Curve : FloatCurves)
	{
		FixCyclicSeamTangents(Curve->GetRichCurve());
	}
	for (FRuntimeCurveLinearColor* Curve : ColorCurves)
	{
		for (int32 i = 0; i < 4; ++i)
		{
			FixCyclicSeamTangents(&Curve->ColorCurves[i]);
		}
	}
}

void FTODCurveEvaluator::GetTODSettingsAtTime(
	ATODManager* Owner,
	float InTime,
	FTODSunMoonSettings& OutSun,
	FTODMoonSettings& OutMoon,
	FTODSkyLightSettings& OutSkyLight,
	FTODFogSettings& OutFog,
	FTODSkyAtmosphereSettings& OutSkyAtmosphere)
{
	if (!Owner || !Owner->CurveData) return;

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	// ===== Sun =====
	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.IntensityCurve.GetRichCurveConst())
		OutSun.Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.SourceAngleCurve.GetRichCurveConst())
		OutSun.Source_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.SourceSoftAngleCurve.GetRichCurveConst())
		OutSun.Source_Soft_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSun.Indirect_Light_Intensity = Curve->Eval(SafeTime);

	OutSun.Light_Color = Owner->CurveData->SunCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== Moon =====
	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.IntensityCurve.GetRichCurveConst())
		OutMoon.Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceAngleCurve.GetRichCurveConst())
		OutMoon.Source_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceSoftAngleCurve.GetRichCurveConst())
		OutMoon.Source_Soft_Angle = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutMoon.Indirect_Light_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceScaleCurve.GetRichCurveConst())
		OutMoon.Moon_Source_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceEmissiveIntensityCurve.GetRichCurveConst())
		OutMoon.Moon_Source_Emissive_Intensity = Curve->Eval(SafeTime);

	OutMoon.Light_Color = Owner->CurveData->MoonCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== SkyLight =====
	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.IntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Light_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.IndirectIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Indirect_Lighting_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.VolumetricScatteringIntensityCurve.GetRichCurveConst())
		OutSkyLight.Sky_Volumetric_Scattering_Intensity = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyLightCurves.TextureEmissiveIntensityCurve.GetRichCurveConst())
		OutSkyLight.SkyDome_Texture_Emissive_Intensity = Curve->Eval(SafeTime);

	OutSkyLight.Sky_Light_Color = Owner->CurveData->SkyLightCurves.LightColorCurve.GetLinearColorValue(SafeTime);

	// ===== Fog =====
	if (const FRichCurve* Curve = Owner->CurveData->FogCurves.DensityCurve.GetRichCurveConst())
		OutFog.Fog_Density = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->FogCurves.HeightFalloffCurve.GetRichCurveConst())
		OutFog.Fog_Height_Falloff = Curve->Eval(SafeTime);

	OutFog.Fog_Inscattering_Color = Owner->CurveData->FogCurves.InscatteringColorCurve.GetLinearColorValue(SafeTime);
	OutFog.Fog_Directional_Inscattering = Owner->CurveData->FogCurves.DirectionalColorCurve.GetLinearColorValue(SafeTime);

	// ===== Atmosphere =====
	if (const FRichCurve* Curve = Owner->CurveData->SkyAtmosphereCurves.MieScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Mie_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyAtmosphereCurves.RayleighScatteringScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Rayleigh_Scattering_Scale = Curve->Eval(SafeTime);

	if (const FRichCurve* Curve = Owner->CurveData->SkyAtmosphereCurves.AerialPerspectiveDistanceScaleCurve.GetRichCurveConst())
		OutSkyAtmosphere.Aerial_Perspective_Distance_Scale = Curve->Eval(SafeTime);

	OutSkyAtmosphere.Mie_Scattering_Color = Owner->CurveData->SkyAtmosphereCurves.MieScatteringColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Absorption_Color = Owner->CurveData->SkyAtmosphereCurves.AbsorptionColorCurve.GetLinearColorValue(SafeTime);
	OutSkyAtmosphere.Sky_Luminance_Factor = Owner->CurveData->SkyAtmosphereCurves.SkyLuminanceFactorCurve.GetLinearColorValue(SafeTime);
}

float FTODCurveEvaluator::GetMoonSourceScaleAtTime(const ATODManager* Owner, float InTime) const
{
	if (!Owner || !Owner->CurveData)
	{
		return 0.0f;
	}

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.SourceScaleCurve.GetRichCurveConst())
	{
		return Curve->Eval(SafeTime);
	}

	return 0.0f;
}

float FTODCurveEvaluator::GetMoonIntensity(const ATODManager* Owner, float InTime) const
{
	if (!Owner || !Owner->CurveData)
	{
		return 0.0f;
	}

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	if (const FRichCurve* Curve = Owner->CurveData->MoonCurves.IntensityCurve.GetRichCurveConst())
	{
		return Curve->Eval(SafeTime);
	}

	return 0.0f;
}

float FTODCurveEvaluator::GetSunIntensity(const ATODManager* Owner, float InTime) const
{
	if (!Owner || !Owner->CurveData)
	{
		return 0.0f;
	}

	const float SafeTime = NormalizeTODTimeForBake(InTime);

	if (const FRichCurve* Curve = Owner->CurveData->SunCurves.IntensityCurve.GetRichCurveConst())
	{
		return Curve->Eval(SafeTime);
	}

	return 0.0f;
}

// ============================================================================
// Editor 전용 코드
// ============================================================================

#if WITH_EDITOR

TArray<TPair<float, float>> FTODCurveEvaluator::SnapshotFloatCurve(const FRuntimeFloatCurve& Curve)
{
	TArray<TPair<float, float>> Keys;
	if (const FRichCurve* Rich = Curve.GetRichCurveConst())
	{
		for (auto It = Rich->GetKeyIterator(); It; ++It)
		{
			Keys.Add(TPair<float, float>(It->Time, It->Value));
		}
	}
	return Keys;
}

TArray<TArray<TPair<float, float>>> FTODCurveEvaluator::SnapshotColorCurve(const FRuntimeCurveLinearColor& Curve)
{
	TArray<TArray<TPair<float, float>>> Channels;
	Channels.SetNum(4);
	for (int32 i = 0; i < 4; ++i)
	{
		for (auto It = Curve.ColorCurves[i].GetKeyIterator(); It; ++It)
		{
			Channels[i].Add(TPair<float, float>(It->Time, It->Value));
		}
	}
	return Channels;
}

namespace
{
	using FTODFieldSetter = TFunction<void(FTODMasterData&, float)>;
	using FTODFieldGetter = TFunction<float(const FTODMasterData&)>;

	struct FTODFloatBinding
	{
		FTODFieldSetter Setter;
		FTODFieldGetter Getter;
	};

	using FTODColorSetter = TFunction<void(FTODMasterData&, FLinearColor)>;
	using FTODColorGetter = TFunction<FLinearColor(const FTODMasterData&)>;

	struct FTODColorBinding
	{
		FTODColorSetter Setter;
		FTODColorGetter Getter;
	};

	// GetAllFloatCurves()와 정확히 같은 순서. (Sun 4, Moon 6, SkyLight 4, Fog 2, SkyAtmosphere 3)
	const TArray<FTODFloatBinding>& GetFloatBindings()
	{
		static const TArray<FTODFloatBinding> Bindings = {
			// Sun
			{ [](FTODMasterData& D, float V) { D.Sun_Settings.Intensity = V; }, [](const FTODMasterData& D) { return D.Sun_Settings.Intensity; } },
			{ [](FTODMasterData& D, float V) { D.Sun_Settings.Source_Angle = V; }, [](const FTODMasterData& D) { return D.Sun_Settings.Source_Angle; } },
			{ [](FTODMasterData& D, float V) { D.Sun_Settings.Source_Soft_Angle = V; }, [](const FTODMasterData& D) { return D.Sun_Settings.Source_Soft_Angle; } },
			{ [](FTODMasterData& D, float V) { D.Sun_Settings.Indirect_Light_Intensity = V; }, [](const FTODMasterData& D) { return D.Sun_Settings.Indirect_Light_Intensity; } },
			// Moon
			{ [](FTODMasterData& D, float V) { D.Moon_Settings.Intensity = V; }, [](const FTODMasterData& D) { return D.Moon_Settings.Intensity; } },
			{ [](FTODMasterData& D, float V) { D.Moon_Settings.Source_Angle = V; }, [](const FTODMasterData& D) { return D.Moon_Settings.Source_Angle; } },
			{ [](FTODMasterData& D, float V) { D.Moon_Settings.Source_Soft_Angle = V; }, [](const FTODMasterData& D) { return D.Moon_Settings.Source_Soft_Angle; } },
			{ [](FTODMasterData& D, float V) { D.Moon_Settings.Indirect_Light_Intensity = V; }, [](const FTODMasterData& D) { return D.Moon_Settings.Indirect_Light_Intensity; } },
			{ [](FTODMasterData& D, float V) { D.Moon_Settings.Moon_Source_Scale = V; }, [](const FTODMasterData& D) { return D.Moon_Settings.Moon_Source_Scale; } },
			{ [](FTODMasterData& D, float V) { D.Moon_Settings.Moon_Source_Emissive_Intensity = V; }, [](const FTODMasterData& D) { return D.Moon_Settings.Moon_Source_Emissive_Intensity; } },
			// SkyLight
			{ [](FTODMasterData& D, float V) { D.SkyLight_Settings.Sky_Light_Intensity = V; }, [](const FTODMasterData& D) { return D.SkyLight_Settings.Sky_Light_Intensity; } },
			{ [](FTODMasterData& D, float V) { D.SkyLight_Settings.Sky_Indirect_Lighting_Intensity = V; }, [](const FTODMasterData& D) { return D.SkyLight_Settings.Sky_Indirect_Lighting_Intensity; } },
			{ [](FTODMasterData& D, float V) { D.SkyLight_Settings.Sky_Volumetric_Scattering_Intensity = V; }, [](const FTODMasterData& D) { return D.SkyLight_Settings.Sky_Volumetric_Scattering_Intensity; } },
			{ [](FTODMasterData& D, float V) { D.SkyLight_Settings.SkyDome_Texture_Emissive_Intensity = V; }, [](const FTODMasterData& D) { return D.SkyLight_Settings.SkyDome_Texture_Emissive_Intensity; } },
			// Fog
			{ [](FTODMasterData& D, float V) { D.Fog_Settings.Fog_Density = V; }, [](const FTODMasterData& D) { return D.Fog_Settings.Fog_Density; } },
			{ [](FTODMasterData& D, float V) { D.Fog_Settings.Fog_Height_Falloff = V; }, [](const FTODMasterData& D) { return D.Fog_Settings.Fog_Height_Falloff; } },
			// SkyAtmosphere
			{ [](FTODMasterData& D, float V) { D.SkyAtmosphere_Settings.Mie_Scattering_Scale = V; }, [](const FTODMasterData& D) { return D.SkyAtmosphere_Settings.Mie_Scattering_Scale; } },
			{ [](FTODMasterData& D, float V) { D.SkyAtmosphere_Settings.Rayleigh_Scattering_Scale = V; }, [](const FTODMasterData& D) { return D.SkyAtmosphere_Settings.Rayleigh_Scattering_Scale; } },
			{ [](FTODMasterData& D, float V) { D.SkyAtmosphere_Settings.Aerial_Perspective_Distance_Scale = V; }, [](const FTODMasterData& D) { return D.SkyAtmosphere_Settings.Aerial_Perspective_Distance_Scale; } },
		};
		return Bindings;
	}

	const TArray<FTODColorBinding>& GetColorBindings()
	{
		static const TArray<FTODColorBinding> Bindings = {
			{ [](FTODMasterData& D, FLinearColor C) { D.Sun_Settings.Light_Color = C; }, [](const FTODMasterData& D) { return D.Sun_Settings.Light_Color; } },
			{ [](FTODMasterData& D, FLinearColor C) { D.Moon_Settings.Light_Color = C; }, [](const FTODMasterData& D) { return D.Moon_Settings.Light_Color; } },
			{ [](FTODMasterData& D, FLinearColor C) { D.SkyLight_Settings.Sky_Light_Color = C; }, [](const FTODMasterData& D) { return D.SkyLight_Settings.Sky_Light_Color; } },
			{ [](FTODMasterData& D, FLinearColor C) { D.Fog_Settings.Fog_Inscattering_Color = C; }, [](const FTODMasterData& D) { return D.Fog_Settings.Fog_Inscattering_Color; } },
			{ [](FTODMasterData& D, FLinearColor C) { D.Fog_Settings.Fog_Directional_Inscattering = C; }, [](const FTODMasterData& D) { return D.Fog_Settings.Fog_Directional_Inscattering; } },
			{ [](FTODMasterData& D, FLinearColor C) { D.SkyAtmosphere_Settings.Mie_Scattering_Color = C; }, [](const FTODMasterData& D) { return D.SkyAtmosphere_Settings.Mie_Scattering_Color; } },
			{ [](FTODMasterData& D, FLinearColor C) { D.SkyAtmosphere_Settings.Absorption_Color = C; }, [](const FTODMasterData& D) { return D.SkyAtmosphere_Settings.Absorption_Color; } },
			{ [](FTODMasterData& D, FLinearColor C) { D.SkyAtmosphere_Settings.Sky_Luminance_Factor = C; }, [](const FTODMasterData& D) { return D.SkyAtmosphere_Settings.Sky_Luminance_Factor; } },
		};
		return Bindings;
	}

	// 0h/24h 경계 키가 서로 다른 값일 경우
	void ResolveBoundaryPair(FRichCurve* Rich, TArray<TPair<float, float>>& CurrentKeys, float OldValue)
	{
		const int32 LastIdx = CurrentKeys.Num() - 1;
		if (LastIdx < 1 || !Rich) return;

		const bool bZeroChanged = !FMath::IsNearlyEqual(CurrentKeys[0].Value, OldValue, TODBoundaryTolerance);
		const float FinalValue = bZeroChanged ? CurrentKeys[0].Value : CurrentKeys[LastIdx].Value;

		CurrentKeys[0].Value = FinalValue;
		CurrentKeys[LastIdx].Value = FinalValue;

		const FKeyHandle FirstHandle = Rich->GetFirstKeyHandle();
		const FKeyHandle LastHandle = Rich->GetLastKeyHandle();
		if (!Rich->IsKeyHandleValid(FirstHandle) || !Rich->IsKeyHandleValid(LastHandle)) return;

		Rich->SetKeyValue(FirstHandle, FinalValue);
		Rich->SetKeyValue(LastHandle, FinalValue);

		const ERichCurveInterpMode FinalMode = bZeroChanged
			? Rich->GetKeyInterpMode(FirstHandle)
			: Rich->GetKeyInterpMode(LastHandle);
		Rich->SetKeyInterpMode(FirstHandle, FinalMode);
		Rich->SetKeyInterpMode(LastHandle, FinalMode);
	}

	bool FindMatchingDataIndex(const TArray<FTODMasterData>& DataArray, float KeyTime, int32& OutIndex)
	{
		const float Target = NormalizeTODTimeForBake(KeyTime);

		for (int32 i = 0; i < DataArray.Num(); ++i)
		{
			if (FMath::IsNearlyEqual(NormalizeTODTimeForBake(DataArray[i].Time), Target, TODBoundaryTolerance))
			{
				OutIndex = i;
				return true;
			}
		}
		return false;
	}
}

void FTODCurveEvaluator::SyncGraphEditToDataArray(ATODManager* Owner, UTODCurveContainer* CurveData)
{
	if (!Owner || !CurveData) return;

	TArray<FTODMasterData> Canonical = BuildCanonicalTODData(Owner->TOD_DataArray, false);
	AddTwentyFourBoundaryFromEarliest(Canonical);

	if (Canonical.Num() == 0) return;

	TArray<FRuntimeFloatCurve*> FloatCurves = GetAllFloatCurves(CurveData);
	TArray<FRuntimeCurveLinearColor*> ColorCurves = GetAllColorCurves(CurveData);

	const TArray<FTODFloatBinding>& FloatBindings = GetFloatBindings();
	const TArray<FTODColorBinding>& ColorBindings = GetColorBindings();

	constexpr float FindTolerance = TODBoundaryTolerance;

	bool bDataChanged = false;
	bool bStructureBroken = false;

	// ===== Float 커브 =====
	for (int32 CurveIndex = 0; CurveIndex < FloatCurves.Num(); ++CurveIndex)
	{
		FRichCurve* Rich = FloatCurves[CurveIndex]->GetRichCurve();
		if (!Rich) continue;

		TArray<TPair<float, float>> CurrentKeys = SnapshotFloatCurve(*FloatCurves[CurveIndex]);

		if (CurrentKeys.Num() != Canonical.Num())
		{
			bStructureBroken = true;
			continue;
		}

		// 0h/24h 경계 키 값·InterpMode 동기화
		if (CurrentKeys.Num() >= 2 &&
			FMath::IsNearlyEqual(Canonical[0].Time, 0.0f, TODBoundaryTolerance) &&
			FMath::IsNearlyEqual(Canonical.Last().Time, TODHours, TODBoundaryTolerance))
		{
			int32 BoundaryDataIndex = INDEX_NONE;
			if (FindMatchingDataIndex(Owner->TOD_DataArray, 0.0f, BoundaryDataIndex))
			{
				const float OldValue = FloatBindings[CurveIndex].Getter(Owner->TOD_DataArray[BoundaryDataIndex]);
				ResolveBoundaryPair(Rich, CurrentKeys, OldValue);
			}
		}

		for (int32 KeyIdx = 0; KeyIdx < CurrentKeys.Num(); ++KeyIdx)
		{
			const float CanonicalTime = Canonical[KeyIdx].Time;
			const float CurrentTime = CurrentKeys[KeyIdx].Key;
			const float CurrentValue = CurrentKeys[KeyIdx].Value;

			if (!FMath::IsNearlyEqual(CurrentTime, CanonicalTime, FindTolerance))
			{
				const FKeyHandle Handle = Rich->FindKey(CurrentTime, FindTolerance);
				if (Rich->IsKeyHandleValid(Handle))
				{
					Rich->SetKeyTime(Handle, CanonicalTime);
				}
			}

			int32 DataIndex = INDEX_NONE;
			if (FindMatchingDataIndex(Owner->TOD_DataArray, CanonicalTime, DataIndex))
			{
				FloatBindings[CurveIndex].Setter(Owner->TOD_DataArray[DataIndex], CurrentValue);
				bDataChanged = true;
			}
		}
	}

	// ===== Color 커브 =====
	for (int32 CurveIndex = 0; CurveIndex < ColorCurves.Num(); ++CurveIndex)
	{
		TArray<TArray<TPair<float, float>>> CurrentChannels = SnapshotColorCurve(*ColorCurves[CurveIndex]);

		bool bCountMismatch = false;
		for (int32 Ch = 0; Ch < 4; ++Ch)
		{
			if (CurrentChannels[Ch].Num() != Canonical.Num())
			{
				bCountMismatch = true;
				break;
			}
		}

		if (bCountMismatch)
		{
			bStructureBroken = true;
			continue;
		}

		// 0h/24h 경계 키 값·InterpMode 동기화
		if (Canonical.Num() >= 2 &&
			FMath::IsNearlyEqual(Canonical[0].Time, 0.0f, TODBoundaryTolerance) &&
			FMath::IsNearlyEqual(Canonical.Last().Time, TODHours, TODBoundaryTolerance))
		{
			int32 BoundaryDataIndex = INDEX_NONE;
			if (FindMatchingDataIndex(Owner->TOD_DataArray, 0.0f, BoundaryDataIndex))
			{
				const FLinearColor OldColor = ColorBindings[CurveIndex].Getter(Owner->TOD_DataArray[BoundaryDataIndex]);
				const float OldVals[4] = { OldColor.R, OldColor.G, OldColor.B, OldColor.A };

				for (int32 Ch = 0; Ch < 4; ++Ch)
				{
					ResolveBoundaryPair(&ColorCurves[CurveIndex]->ColorCurves[Ch], CurrentChannels[Ch], OldVals[Ch]);
				}
			}
		}

		for (int32 KeyIdx = 0; KeyIdx < Canonical.Num(); ++KeyIdx)
		{
			const float CanonicalTime = Canonical[KeyIdx].Time;

			for (int32 Ch = 0; Ch < 4; ++Ch)
			{
				FRichCurve& Rich = ColorCurves[CurveIndex]->ColorCurves[Ch];
				const float CurrentTime = CurrentChannels[Ch][KeyIdx].Key;

				if (!FMath::IsNearlyEqual(CurrentTime, CanonicalTime, FindTolerance))
				{
					const FKeyHandle Handle = Rich.FindKey(CurrentTime, FindTolerance);
					if (Rich.IsKeyHandleValid(Handle))
					{
						Rich.SetKeyTime(Handle, CanonicalTime);
					}
				}
			}

			int32 DataIndex = INDEX_NONE;
			if (FindMatchingDataIndex(Owner->TOD_DataArray, CanonicalTime, DataIndex))
			{
				const FLinearColor NewColor(
					CurrentChannels[0][KeyIdx].Value,
					CurrentChannels[1][KeyIdx].Value,
					CurrentChannels[2][KeyIdx].Value,
					CurrentChannels[3][KeyIdx].Value
				);

				ColorBindings[CurveIndex].Setter(Owner->TOD_DataArray[DataIndex], NewColor);
				bDataChanged = true;
			}
		}
	}

	if (bStructureBroken)
	{
		FNotificationInfo Info(FText::FromString(TEXT(
			"Cannot add or remove keys in the graph. Re-creating curves based on TOD_DataArray.")));
		Info.ExpireDuration = 4.0f;
		FSlateNotificationManager::Get().AddNotification(Info);

		Owner->BakeTODCurves();
		Owner->UpdateTOD(Owner->GetCurrentTime());
		Owner->ForceViewportRedraw();
		return;
	}

	if (bDataChanged)
	{
		Owner->MarkPackageDirty();
		Owner->OnTODDataChanged.Broadcast();
		Owner->UpdateTOD(Owner->GetCurrentTime());
		Owner->ForceViewportRedraw();
	}
}

#endif // WITH_EDITOR