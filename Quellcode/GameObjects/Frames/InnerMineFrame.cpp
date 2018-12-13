//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "InnerMineFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Item"
#pragma link "Exit"
#pragma link "Player"
#pragma resource "*.fmx"
TInnerMineFrame *InnerMineFrame;
//---------------------------------------------------------------------------
__fastcall TInnerMineFrame::TInnerMineFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
