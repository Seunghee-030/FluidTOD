#include "MyBlueprintFunctionLibrary.h"
#include "TOD_Types.h"
#include "Curves/RichCurve.h"
#include "Engine/Engine.h"


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