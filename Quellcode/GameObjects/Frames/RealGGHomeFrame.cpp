//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "RealGGHomeFrame.h"
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
TRealGGHomeFrame *RealGGHomeFrame;
//---------------------------------------------------------------------------
__fastcall TRealGGHomeFrame::TRealGGHomeFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
