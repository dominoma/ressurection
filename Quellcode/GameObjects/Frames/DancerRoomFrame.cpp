//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "DancerRoomFrame.h"
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
TDancerRoomFrame *DancerRoomFrame;
bool bHideBandit = false;
//---------------------------------------------------------------------------
__fastcall TDancerRoomFrame::TDancerRoomFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDancerRoomFrame::BlackoutStarted(TObject *Sender)

{
	TGameManager::Manager()->OpenedFrame->LockScreen(NULL, 1);
	Player->Left = Tänzerin->Left + Tänzerin->PlayerOffset - 20;
}
//---------------------------------------------------------------------------

void __fastcall TDancerRoomFrame::BlackoutStopped(TObject *Sender)

{
	TGameManager::Manager()->OpenedFrame->UnlockScreen();
}
//---------------------------------------------------------------------------

void __fastcall TDancerRoomFrame::HideBandit(TObject *Sender)
{
	bHideBandit = true;
}
//---------------------------------------------------------------------------

void __fastcall TDancerRoomFrame::Exit1Action(THotspot *Sender)
{
	if(bHideBandit)
	{
        Bandit->State = "Gone";
    }
}
//---------------------------------------------------------------------------

