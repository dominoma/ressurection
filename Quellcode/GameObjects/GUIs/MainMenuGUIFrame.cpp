//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainMenuGUI.h"
#include "MainMenuGUIFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GameGUIFrame"
#pragma link "ImageButton"
#pragma link "CppScale"
#pragma resource "*.fmx"
TMainMenuGUIFrame *MainMenuGUIFrame;
//---------------------------------------------------------------------------
__fastcall TMainMenuGUIFrame::TMainMenuGUIFrame(TComponent* Owner)
	: TGameGUIFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainMenuGUIFrame::BStartGameClick(TObject *Sender)
{
	((TMainMenuGUI*)GUIComp)->StartGame();
}
//---------------------------------------------------------------------------

void __fastcall TMainMenuGUIFrame::BNewGameClick(TObject *Sender)
{
	((TMainMenuGUI*)GUIComp)->NewGame();
}
//---------------------------------------------------------------------------


void __fastcall TMainMenuGUIFrame::CloseButtonClick(TObject *Sender)
{
	((TForm*)GUIComp->Owner)->Close();
}
//---------------------------------------------------------------------------

