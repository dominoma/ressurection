//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MineFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Exit"
#pragma link "Player"
#pragma resource "*.fmx"
TMineFrame *MineFrame;
//---------------------------------------------------------------------------
__fastcall TMineFrame::TMineFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
