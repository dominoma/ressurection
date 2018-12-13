//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "StreetFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "Exit"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Person"
#pragma link "Player"
#pragma resource "*.fmx"
TStreetFrame *StreetFrame;
//---------------------------------------------------------------------------
__fastcall TStreetFrame::TStreetFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TStreetFrame::TutorialStarted(TObject *Sender)

{
	MarketExit->Enabled = false;
	EntryExit->Enabled = false;
	RealGGEntry->Enabled = false;
	FakeGGEntry->Enabled = false;
	Goldgraeber->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TStreetFrame::GoldDiggerGoneTalked(TObject *Sender)

{
	MarketExit->Enabled = true;
	EntryExit->Enabled = true;
	RealGGEntry->Enabled = true;
	FakeGGEntry->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TStreetFrame::MarketExitAction(THotspot *Sender)
{
	Goldgraeber->Visible = false;
}
//---------------------------------------------------------------------------

