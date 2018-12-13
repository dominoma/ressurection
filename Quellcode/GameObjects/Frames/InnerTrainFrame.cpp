//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#include "InnerTrainFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Exit"
#pragma link "Person"
#pragma resource "*.fmx"
TInnerTrainFrame *InnerTrainFrame;
//---------------------------------------------------------------------------
__fastcall TInnerTrainFrame::TInnerTrainFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInnerTrainFrame::ObjectStateChanged(TObject *Sender)
{
	if(Rohr->State == "Fixiert" && Wasser->State == "Voll" && Kohle->State == "Voll")
	{
		 Exit->State = "Erledigt";
		 ((TTrainFrame*)TGameManager::Manager()->Frames["TTrainFrame"])->Zugführer->State = "Repaired";
    }
}
//---------------------------------------------------------------------------

void __fastcall TInnerTrainFrame::CoalFilled(TObject *Sender)

{
	((TFlowTreeItem*)((TTrainFrame*)TGameManager::Manager()->Frames["TTrainFrame"])->Zugführer->ConvTree->Root->Items[2])->Hidden = false;
}
//---------------------------------------------------------------------------

void __fastcall TInnerTrainFrame::RohrRepaired(TObject *Sender)
{
	((TFlowTreeItem*)((TTrainFrame*)TGameManager::Manager()->Frames["TTrainFrame"])->Zugführer->ConvTree->Root->Items[0])->Hidden = false;
}
//---------------------------------------------------------------------------

