//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#include "GameGUIFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TGameGUIFrame *GameGUIFrame;
//---------------------------------------------------------------------------
__fastcall TGameGUIFrame::TGameGUIFrame(TComponent *Owner)
	: TFrame(Owner)
{
	if(Owner == NULL || !Owner->InheritsFrom(__classid(TGameGUI)))
		throw EArgumentException("'Owner' is not inherited from 'TGameGUI'");
}
//---------------------------------------------------------------------------
void __fastcall TGameGUIFrame::OpenCloseAnimationFinish(TObject *Sender)
{
	GUIComp->Visible = GUIComp->IsOpen;
	DoRealign();
}
//---------------------------------------------------------------------------
