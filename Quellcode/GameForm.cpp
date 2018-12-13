//---------------------------------------------------------------------------
#define OEMRESOURCE
#include <fmx.h>
#pragma hdrstop

#include "GameForm.h"
#include "GameObjects.h"
#include "GameCursor.h"
#include "PropertyClasses.h"
#include "EventList.h"
#include <FMX.Platform.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma link "ImageButton"
#pragma link "ConversationGUIFrame"
#pragma link "GameGUIFrame"
#pragma link "InventoryGUIFrame"
#pragma link "GameGUI"
#pragma link "GameObjects"
#pragma link "GameGUI"
#pragma link "InventoryGUI"
#pragma link "ConversationGUI"
#pragma link "MainMenuGUI"
#pragma link "NotesGUI"
#pragma resource "*.fmx"

TAdventureForm *AdventureForm;
TPropertyList *List;

TEventList<TNotifyEvent> EventList;
//---------------------------------------------------------------------------
__fastcall TAdventureForm::TAdventureForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TAdventureForm::FormActivate(TObject *Sender)
{
	TGameCursor::Init();
	TGameManager::Manager()->FrameParent = Panel1;
	TGameManager::Manager()->HintIcon->LoadFromFile("Resources\\Geschlossen.png");
}
//---------------------------------------------------------------------------
void __fastcall TAdventureForm::FormDeactivate(TObject *Sender)
{
	TGameCursor::Clear();
}
//---------------------------------------------------------------------------
void __fastcall TAdventureForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(TGameManager::Manager()->IsStarted)
	{
		TGameManager::Manager()->StopGame();
	};
}
//---------------------------------------------------------------------------

