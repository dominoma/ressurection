//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MapCloseupFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Exit"
#pragma link "Hotspot"
#pragma resource "*.fmx"
TMapCloseupFrame *MapCloseupFrame;
//---------------------------------------------------------------------------
__fastcall TMapCloseupFrame::TMapCloseupFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
