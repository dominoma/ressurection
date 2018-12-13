//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MarketPlaceFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Exit"
#pragma link "Hotspot"
#pragma link "Person"
#pragma link "Player"
#pragma resource "*.fmx"
TMarketPlaceFrame *MarketPlaceFrame;
//---------------------------------------------------------------------------
__fastcall TMarketPlaceFrame::TMarketPlaceFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
