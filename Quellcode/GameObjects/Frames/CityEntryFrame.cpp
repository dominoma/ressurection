//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CityEntryFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "Exit"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Player"
#pragma resource "*.fmx"
TCityEntryFrame *CityEntryFrame;
//---------------------------------------------------------------------------
__fastcall TCityEntryFrame::TCityEntryFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCityEntryFrame::StartGameEvent(TObject *Sender)

{
	if(!TGameManager::Manager()->GlobalFlags.FlagExists("TutorialSolved"))
	{
		TownExit->Enabled = false;
		Background->OpenFlowList->Items["StartTutorial"]->FlowList->Start();
		TGameManager::Manager()->GlobalFlags.AddFlag("TutorialSolved", "yes");
    }
}
//---------------------------------------------------------------------------


void __fastcall TCityEntryFrame::MoveTutStarted(TObject *Sender)

{
	TownExit->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TCityEntryFrame::BackgroundFrameClosed(TObject *Sender)
{
	Map->State = "Normal";
}
//---------------------------------------------------------------------------

