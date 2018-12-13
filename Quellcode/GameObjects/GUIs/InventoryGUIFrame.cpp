//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#include "InventoryGUIFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GameGUIFrame"
#pragma link "ImageButton"
#pragma resource "*.fmx"
TInventoryGUIFrame *InventoryGUIFrame;
//---------------------------------------------------------------------------
__fastcall TInventoryGUIFrame::TInventoryGUIFrame(TComponent* Owner)
	: TGameGUIFrame(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TInventoryGUIFrame::MenuButtonClick(TObject *Sender)
{
	((TInventoryGUI*)GUIComp)->OpenMenu();
}
//---------------------------------------------------------------------------

void __fastcall TInventoryGUIFrame::NotesButtonClick(TObject *Sender)
{
	((TInventoryGUI*)GUIComp)->OpenNodes();
}
//---------------------------------------------------------------------------

