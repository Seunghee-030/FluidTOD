#include "TODCurveFunctionLibrary.h"
#include "TOD_Types.h"
#include "Curves/RichCurve.h"
#include "Engine/Engine.h"


// Curve Control

void UTODCurveFunctionLibrary::ClearRuntimeFloatCurve(FRuntimeFloatCurve& InCurve)
{
	if (FRichCurve* RichCurve = InCurve.GetRichCurve())
	{
		RichCurve->Reset();
		RichCurve->PreInfinityExtrap = RCCE_Cycle;
		RichCurve->PostInfinityExtrap = RCCE_Cycle;
	}
}

void UTODCurveFunctionLibrary::AddKeyToRuntimeFloatCurve(FRuntimeFloatCurve& InCurve, float InTime, float InValue, ERichCurveInterpMode InterpMode)
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

void UTODCurveFunctionLibrary::ClearRuntimeColorCurve(FRuntimeCurveLinearColor& InCurve)
{
	for (int32 i = 0; i < 4; ++i)
	{
		InCurve.ColorCurves[i].Reset();
		InCurve.ColorCurves[i].PreInfinityExtrap = RCCE_Cycle;
		InCurve.ColorCurves[i].PostInfinityExtrap = RCCE_Cycle;
	}
}

void UTODCurveFunctionLibrary::AddKeyToRuntimeColorCurve(FRuntimeCurveLinearColor& InCurve, float InTime, FLinearColor InColor, ERichCurveInterpMode InterpMode)
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

FLinearColor UTODCurveFunctionLibrary::GetRuntimeColorCurveValue(const FRuntimeCurveLinearColor& InCurve, float InTime)
{
	return InCurve.GetLinearColorValue(InTime);
}

// Auto-Seal

namespace
{
	void SealRichCurveFor24Hours(FRichCurve& RichCurve)
	{
		if (RichCurve.GetNumKeys() == 0) return;

		float MinTime, MaxTime;
		RichCurve.GetTimeRange(MinTime, MaxTime);

		if (MaxTime == 24.0f && MinTime > 0.0f)
		{
			RichCurve.AddKey(0.0f, RichCurve.Eval(24.0f));
		}
		else if (MinTime == 0.0f && MaxTime < 24.0f)
		{
			RichCurve.AddKey(24.0f, RichCurve.Eval(0.0f));
		}
		else if (MinTime > 0.0f && MaxTime < 24.0f)
		{
			const float BlendedValue = (RichCurve.Eval(MinTime) + RichCurve.Eval(MaxTime)) * 0.5f;
			RichCurve.AddKey(0.0f, BlendedValue);
			RichCurve.AddKey(24.0f, BlendedValue);
		}

		RichCurve.PreInfinityExtrap = RCCE_Cycle;
		RichCurve.PostInfinityExtrap = RCCE_Cycle;
	}
}

void UTODCurveFunctionLibrary::SealTODCurveFor24Hours(FRuntimeFloatCurve& InCurve)
{
	if (FRichCurve* RichCurve = InCurve.GetRichCurve())
	{
		SealRichCurveFor24Hours(*RichCurve);
	}
}

void UTODCurveFunctionLibrary::SealColorCurveFor24Hours(FRuntimeCurveLinearColor& InCurve)
{
	for (int32 i = 0; i < 4; ++i)
	{
		SealRichCurveFor24Hours(InCurve.ColorCurves[i]);
	}
}
