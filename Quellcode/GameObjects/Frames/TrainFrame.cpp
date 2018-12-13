//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "TrainFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "Exit"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Person"
#pragma link "Player"
#pragma resource "*.fmx"
TTrainFrame *TrainFrame;
//---------------------------------------------------------------------------
__fastcall TTrainFrame::TTrainFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTrainFrame::WaterFilled(TObject *Sender)

{
	((TFlowTreeItem*)Zugführer->ConvTree->Root->Items[3])->Hidden = false;
}
//---------------------------------------------------------------------------

