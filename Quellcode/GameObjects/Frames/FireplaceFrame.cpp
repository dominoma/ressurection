//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#include "FireplaceFrame.h"
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
TFireplaceFrame *FireplaceFrame;
//---------------------------------------------------------------------------
__fastcall TFireplaceFrame::TFireplaceFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFireplaceFrame::IndianerTConvGUIFlowList4Started(TObject *Sender)

{
	((TFlowTreeItem*)((TMarketPlaceFrame*)TGameManager::Manager()->Frames["TMarketPlaceFrame"])->Quacksalber->ConvTree->Root->Items[3])->Hidden = false;
}
//---------------------------------------------------------------------------

void __fastcall TFireplaceFrame::ThunderStarted(TObject *Sender)

{
	TGameManager::Manager()->OpenedFrame->LockScreen(NULL,0.8F);
}
//---------------------------------------------------------------------------

void __fastcall TFireplaceFrame::ThunderStopped(TObject *Sender)

{
	TGameManager::Manager()->OpenedFrame->UnlockScreen();
}
//---------------------------------------------------------------------------

