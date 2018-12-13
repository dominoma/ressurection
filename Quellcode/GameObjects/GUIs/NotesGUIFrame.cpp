//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#include "NotesGUIFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GameGUIFrame"
#pragma link "ImageButton"
#pragma link "CppScale"
#pragma resource "*.fmx"
TNotesGUIFrame *NotesGUIFrame;
//---------------------------------------------------------------------------
__fastcall TNotesGUIFrame::TNotesGUIFrame(TComponent* Owner)
	: TGameGUIFrame(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TNotesGUIFrame::BStartGameClick(TObject *Sender)
{
	GUIComp->Close();
}
//---------------------------------------------------------------------------

