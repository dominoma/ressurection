//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SheriffEntryFrame.h"
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
TSheriffEntryFrame *SheriffEntryFrame;
//---------------------------------------------------------------------------
__fastcall TSheriffEntryFrame::TSheriffEntryFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
