#include "TODCurveContainer.h"

#if WITH_EDITOR
#include "TODManager.h"
#include "TODCurveEvaluator.h"

void UTODCurveContainer::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// 드래그 중(Interactive) 이벤트에는 개입하지 않는다. 마우스를 뗀 최종 커밋에만 반응한다.
	if (PropertyChangedEvent.ChangeType & EPropertyChangeType::Interactive)
	{
		return;
	}

	ATODManager* Owner = GetTypedOuter<ATODManager>();
	if (!Owner) return;

	FTODCurveEvaluator::SyncGraphEditToDataArray(Owner, this);
}
#endif