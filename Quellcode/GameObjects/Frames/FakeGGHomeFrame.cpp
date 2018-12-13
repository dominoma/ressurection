//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FakeGGHomeFrame.h"
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
TFakeGGHomeFrame *FakeGGHomeFrame;
//---------------------------------------------------------------------------
__fastcall TFakeGGHomeFrame::TFakeGGHomeFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
