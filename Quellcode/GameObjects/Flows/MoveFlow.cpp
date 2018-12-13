//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop

#include "MoveFlow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TMoveFlowItem::TMoveFlowItem(TBasicCustomList* List)
	: TAnimationBaseFlowItem(List), FLeftChange(0), FTopChange(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TMoveFlowItem::AddBeforePic(int PicIndex, TFlowItemAddProc AddProc)
{
	float LeftStep = FLeftChange / Pictures().Count();
	float TopStep = FTopChange / Pictures().Count();

	TMoveObjFlowItem* NewMove = AddItem<TMoveObjFlowItem>(AddProc);
	NewMove->Object = Object;
	NewMove->LeftChange = LeftStep;
	NewMove->TopChange = TopStep;

}
//---------------------------------------------------------------------------
void __fastcall TMoveFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TMoveFlowItem)))
	{
		TMoveFlowItem *Item = (TMoveFlowItem*)Source;
		FLeftChange = Item->FLeftChange;
		FTopChange = Item->FTopChange;
	}
	TAnimationBaseFlowItem::Assign(Source);
}
//---------------------------------------------------------------------------

