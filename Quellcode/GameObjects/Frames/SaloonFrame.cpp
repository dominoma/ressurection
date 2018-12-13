//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#include "SaloonFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Person"
#pragma link "Exit"
#pragma link "Player"
#pragma resource "*.fmx"
TSaloonFrame *SaloonFrame;
bool GGInvitation = false;
//---------------------------------------------------------------------------
__fastcall TSaloonFrame::TSaloonFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TSaloonFrame::GoldDiggerInvited(TObject *Sender)

{
	GGInvitation = true;
}
//---------------------------------------------------------------------------



void __fastcall TSaloonFrame::GoldDiggerDrinkMentioned(TObject *Sender)

{
	((TFlowTreeItem*)((TMarketPlaceFrame*)TGameManager::Manager()->Frames["TMarketPlaceFrame"])->Quacksalber->ConvTree->Root->Items[2])->Hidden = false;
}
//---------------------------------------------------------------------------

void __fastcall TSaloonFrame::BarmannIndianaMentioned(TObject *Sender)
{
	((TFlowTreeItem*)((TFireplaceFrame*)TGameManager::Manager()->Frames["TFireplaceFrame"])->Indianer->ConvTree->Root->Items[2])->Hidden = false;
}
//---------------------------------------------------------------------------

void __fastcall TSaloonFrame::BackgroundFrameClosed(TObject *Sender)
{
	if(GGInvitation)
	{
		Goldgraeber->State = "Gone";
    }
}
//---------------------------------------------------------------------------

void __fastcall TSaloonFrame::GoneStateSelected(TObject *Sender)
{
	Goldgraeber->Cursor = TGameCursor::Default;
}
//---------------------------------------------------------------------------


