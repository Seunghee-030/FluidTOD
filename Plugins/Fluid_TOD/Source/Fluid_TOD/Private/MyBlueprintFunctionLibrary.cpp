#include "MyBlueprintFunctionLibrary.h"
#include "TOD_Types.h"
#include "Curves/RichCurve.h"
#include "Engine/Engine.h"

// System
void UMyBlueprintFunctionLibrary::SortTODDataArray(TArray<FTODMasterData>& DataArray)
{
	if (DataArray.Num() < 2) return;
	DataArray.Sort([](const FTODMasterData& A, const FTODMasterData& B) { return A.Time < B.Time; });
}

// Presets
void UMyBlueprintFunctionLibrary::SaveToSinglePreset(const TArray<FTODMasterData>& DataArray, int32 Index, UTODSinglePreset* Preset)
{
	if (!IsValid(Preset)) return;
	if (!DataArray.IsValidIndex(Index)) return;

	Preset->SavedData = DataArray[Index];
	Preset->MarkPackageDirty();
}

void UMyBlueprintFunctionLibrary::LoadFromSinglePreset(UTODSinglePreset* Preset, TArray<FTODMasterData>& DataArray, int32 Index)
{
	if (!IsValid(Preset)) return;
	if (!DataArray.IsValidIndex(Index)) return;

	DataArray[Index] = Preset->SavedData;
}

void UMyBlueprintFunctionLibrary::SaveToFullPreset(const TArray<FTODMasterData>& DataArray, UTODPresetData* Preset)
{
	if (!IsValid(Preset)) return;

	Preset->TOD_DataArray = DataArray;
	Preset->MarkPackageDirty();
}

void UMyBlueprintFunctionLibrary::LoadFromFullPreset(UTODPresetData* Preset, TArray<FTODMasterData>& DataArray)
{
	if (!IsValid(Preset)) return;

	DataArray = Preset->TOD_DataArray;
}

// PPV
void UMyBlueprintFunctionLibrary::GetTODInterpolationData(const TArray<FTODMasterData>& DataArray, float CurrentTime, int32& OutPrevIndex, int32& OutNextIndex, float& OutAlpha)
{
	OutPrevIndex = 0; OutNextIndex = 0; OutAlpha = 0.0f;
	const int32 Num = DataArray.Num();
	if (Num < 2) return;

	float SafeTime = FMath::Fmod(CurrentTime, 24.0f);
	if (SafeTime < 0.0f) SafeTime += 24.0f;

	OutPrevIndex = Num - 1;
	for (int32 i = 0; i < Num - 1; ++i)
	{
		if (SafeTime >= DataArray[i].Time && SafeTime < DataArray[i + 1].Time)
		{
			OutPrevIndex = i;
			break;
		}
	}
	OutNextIndex = (OutPrevIndex + 1) % Num;

	float PrevTime = DataArray[OutPrevIndex].Time;
	float NextTime = DataArray[OutNextIndex].Time;
	float AdjustedCurrentTime = SafeTime;

	if (NextTime < PrevTime)
	{
		NextTime += 24.0f;
		if (AdjustedCurrentTime < DataArray[0].Time) AdjustedCurrentTime += 24.0f;
	}

	float TimeDiff = NextTime - PrevTime;
	if (TimeDiff > KINDA_SMALL_NUMBER)
	{
		OutAlpha = FMath::Clamp((AdjustedCurrentTime - PrevTime) / TimeDiff, 0.0f, 1.0f);
	}
}

void UMyBlueprintFunctionLibrary::ApplyPPVBlending(const TArray<FTODMasterData>& DataArray, float CurrentTime, UPostProcessComponent* RuntimePPV)
{
	if (!IsValid(RuntimePPV)) return;

	// 추출 및 정렬
	TArray<FTODMasterData> ValidPPVs;
	for (const FTODMasterData& Data : DataArray)
	{
		if (IsValid(Data.PPV)) ValidPPVs.Add(Data);
	}

	const int32 Num = ValidPPVs.Num();
	if (Num == 0) return;

	ValidPPVs.Sort([](const FTODMasterData& A, const FTODMasterData& B) {
		return A.Time < B.Time;
		});

	for (const FTODMasterData& Data : ValidPPVs)
	{
		Data.PPV->BlendWeight = 0.0f;
		Data.PPV->Priority = -10;
	}

	float SafeTime = CurrentTime;
	while (SafeTime >= 24.0f) SafeTime -= 24.0f;
	while (SafeTime < 0.0f) SafeTime += 24.0f;

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
	while (Range <= 0.0f) Range += 24.0f;

	float Elapsed = SafeTime - PrevTime;
	while (Elapsed < 0.0f) Elapsed += 24.0f;

	float Alpha = FMath::Clamp(Elapsed / Range, 0.0f, 1.0f);

	APostProcessVolume* PrevPPV = ValidPPVs[PrevIndex].PPV;
	APostProcessVolume* NextPPV = ValidPPVs[NextIndex].PPV;

	RuntimePPV->bEnabled = true;
	RuntimePPV->bUnbound = true;
	RuntimePPV->Priority = 0; // TOD PPV Priority 설정
	RuntimePPV->BlendWeight = 1.0f;

	// ---보간용 매크로

	// float
#define LERP_PPV(Prop) \
		RuntimePPV->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		RuntimePPV->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

	// FVector4
#define LERP_VEC4_PPV(Prop) \
		RuntimePPV->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		RuntimePPV->Settings.Prop = FMath::Lerp(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);

	// FLinearColor
#define LERP_COLOR_PPV(Prop) \
		RuntimePPV->Settings.bOverride_##Prop = PrevPPV->Settings.bOverride_##Prop || NextPPV->Settings.bOverride_##Prop; \
		RuntimePPV->Settings.Prop = FLinearColor::LerpUsingHSV(PrevPPV->Settings.Prop, NextPPV->Settings.Prop, Alpha);
	

// Exposure
	LERP_PPV(AutoExposureMinBrightness);
	LERP_PPV(AutoExposureMaxBrightness);
	LERP_PPV(AutoExposureBias);
	LERP_PPV(AutoExposureSpeedUp);
	LERP_PPV(AutoExposureSpeedDown);
	LERP_PPV(AutoExposureApplyPhysicalCameraExposure);

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

#undef LERP_PPV
#undef LERP_VEC4_PPV
#undef LERP_COLOR_PPV
}

// Curve Control

void UMyBlueprintFunctionLibrary::ClearRuntimeFloatCurve(FRuntimeFloatCurve& InCurve)
{
	if (FRichCurve* RichCurve = InCurve.GetRichCurve())
	{
		RichCurve->Reset();
		RichCurve->PreInfinityExtrap = RCCE_Cycle;
		RichCurve->PostInfinityExtrap = RCCE_Cycle;
	}
}

void UMyBlueprintFunctionLibrary::AddKeyToRuntimeFloatCurve(FRuntimeFloatCurve& InCurve, float InTime, float InValue, ERichCurveInterpMode InterpMode)
{
	if (FRichCurve* RichCurve = InCurve.GetRichCurve())
	{
		FKeyHandle NewKey = RichCurve->AddKey(InTime, InValue);
		RichCurve->SetKeyInterpMode(NewKey, InterpMode);

		if (InterpMode == RCIM_Cubic)
		{
			RichCurve->SetKeyTangentMode(NewKey, RCTM_SmartAuto);
		}

		RichCurve->PreInfinityExtrap = RCCE_Cycle;
		RichCurve->PostInfinityExtrap = RCCE_Cycle;
	}
}

void UMyBlueprintFunctionLibrary::ClearRuntimeColorCurve(FRuntimeCurveLinearColor& InCurve)
{
	for (int32 i = 0; i < 4; ++i)
	{
		InCurve.ColorCurves[i].Reset();
		InCurve.ColorCurves[i].PreInfinityExtrap = RCCE_Cycle;
		InCurve.ColorCurves[i].PostInfinityExtrap = RCCE_Cycle;
	}
}

void UMyBlueprintFunctionLibrary::AddKeyToRuntimeColorCurve(FRuntimeCurveLinearColor& InCurve, float InTime, FLinearColor InColor, ERichCurveInterpMode InterpMode)
{
	float Vals[4] = { InColor.R, InColor.G, InColor.B, InColor.A };
	for (int32 i = 0; i < 4; ++i)
	{
		FKeyHandle NewKey = InCurve.ColorCurves[i].AddKey(InTime, Vals[i]);
		InCurve.ColorCurves[i].SetKeyInterpMode(NewKey, InterpMode);

		if (InterpMode == RCIM_Cubic)
		{
			InCurve.ColorCurves[i].SetKeyTangentMode(NewKey, RCTM_SmartAuto);
		}

		InCurve.ColorCurves[i].PreInfinityExtrap = RCCE_Cycle;
		InCurve.ColorCurves[i].PostInfinityExtrap = RCCE_Cycle;
	}
}

FLinearColor UMyBlueprintFunctionLibrary::GetRuntimeColorCurveValue(const FRuntimeCurveLinearColor& InCurve, float InTime)
{
	return InCurve.GetLinearColorValue(InTime);
}

// Auto-Seal

void UMyBlueprintFunctionLibrary::SealTODCurveFor24Hours(FRuntimeFloatCurve& InCurve)
{
	FRichCurve* RichCurve = InCurve.GetRichCurve();
	if (!RichCurve || RichCurve->GetNumKeys() == 0) return;

	float MinTime, MaxTime;
	RichCurve->GetTimeRange(MinTime, MaxTime);

	float ValueAtZero = 0.0f;
	float ValueAt24 = 0.0f;

	if (MaxTime == 24.0f && MinTime > 0.0f)
	{
		ValueAtZero = RichCurve->Eval(24.0f);
		RichCurve->AddKey(0.0f, ValueAtZero);
	}
	else if (MinTime == 0.0f && MaxTime < 24.0f)
	{
		ValueAt24 = RichCurve->Eval(0.0f);
		RichCurve->AddKey(24.0f, ValueAt24);
	}
	else if (MinTime > 0.0f && MaxTime < 24.0f)
	{
		float BlendedValue = (RichCurve->Eval(MinTime) + RichCurve->Eval(MaxTime)) * 0.5f;
		RichCurve->AddKey(0.0f, BlendedValue);
		RichCurve->AddKey(24.0f, BlendedValue);
	}
	else if (MinTime == 0.0f && MaxTime == 24.0f)
	{
		float ValueToSync = RichCurve->Eval(0.0f);
		FKeyHandle Key24 = RichCurve->FindKey(24.0f);
		if (RichCurve->IsKeyHandleValid(Key24))
		{
			RichCurve->UpdateOrAddKey(24.0f, ValueToSync);
		}
	}

	RichCurve->PreInfinityExtrap = RCCE_Cycle;
	RichCurve->PostInfinityExtrap = RCCE_Cycle;
}

void UMyBlueprintFunctionLibrary::SealColorCurveFor24Hours(FRuntimeCurveLinearColor& InCurve)
{
	for (int32 i = 0; i < 4; ++i)
	{
		FRichCurve* RichCurve = &InCurve.ColorCurves[i];
		if (!RichCurve || RichCurve->GetNumKeys() == 0) continue;

		float MinTime, MaxTime;
		RichCurve->GetTimeRange(MinTime, MaxTime);

		float ValueAtZero = 0.0f;
		float ValueAt24 = 0.0f;

		if (MaxTime == 24.0f && MinTime > 0.0f)
		{
			ValueAtZero = RichCurve->Eval(24.0f);
			RichCurve->AddKey(0.0f, ValueAtZero);
		}
		else if (MinTime == 0.0f && MaxTime < 24.0f)
		{
			ValueAt24 = RichCurve->Eval(0.0f);
			RichCurve->AddKey(24.0f, ValueAt24);
		}
		else if (MinTime > 0.0f && MaxTime < 24.0f)
		{
			float BlendedValue = (RichCurve->Eval(MinTime) + RichCurve->Eval(MaxTime)) * 0.5f;
			RichCurve->AddKey(0.0f, BlendedValue);
			RichCurve->AddKey(24.0f, BlendedValue);
		}
		else if (MinTime == 0.0f && MaxTime == 24.0f)
		{
			float ValueToSync = RichCurve->Eval(0.0f);
			FKeyHandle Key24 = RichCurve->FindKey(24.0f);
			if (RichCurve->IsKeyHandleValid(Key24))
			{
				RichCurve->UpdateOrAddKey(24.0f, ValueToSync);
			}
		}

		RichCurve->PreInfinityExtrap = RCCE_Cycle;
		RichCurve->PostInfinityExtrap = RCCE_Cycle;
	}
}