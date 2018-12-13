//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SheriffFrame.h"
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
TSheriffFrame *SheriffFrame;
bool HideSheriff = false;
//---------------------------------------------------------------------------
__fastcall TSheriffFrame::TSheriffFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSheriffFrame::SheriffTVariadicFlowList4Started(TObject *Sender)
{
	HideSheriff = true;
}
//---------------------------------------------------------------------------


void __fastcall TSheriffFrame::BackgroundFrameClosed(TObject *Sender)
{
	if(HideSheriff)
	{
		Sheriff->State = "Hidden";
    }
}
//---------------------------------------------------------------------------

