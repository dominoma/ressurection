//---------------------------------------------------------------------------

#include "GameObjects.h"

#pragma hdrstop
#include "NotesGUIFrame.h"
#include "NotesGUI.h"
#pragma link "GameGUI"
#pragma link "GameObject"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TNotesGUI *)
{
	new TNotesGUI(NULL);
}
//---------------------------------------------------------------------------
__fastcall TNotesGUI::TNotesGUI(TComponent* Owner)
	: TGameGUI(Owner, new TNotesGUIFrame(this))
{
}
//---------------------------------------------------------------------------
void __fastcall TNotesGUI::DoOpen(void)
{
	if(TInventoryGUI::IsInstance())
		TInventoryGUI::Instance()->Close();
	if(TGameManager::IsCreated())
	{
		if(TGameManager::Manager()->OpenedFrame != NULL)
			TGameManager::Manager()->OpenedFrame->LockScreen(NULL,0.5);
		if(TGameManager::Manager()->GlobalFlags.FlagExists("Notes"))
			((TNotesGUIFrame*)GUIFrame)->Notes->Lines->Text = TGameManager::Manager()->GlobalFlags.FlagValue["Notes"];
		else
			((TNotesGUIFrame*)GUIFrame)->Notes->Lines->Text = "";
	}
	TGameGUI::DoOpen();
}
//---------------------------------------------------------------------------
void __fastcall TNotesGUI::DoClose(void)
{
	TGameGUI::DoClose();
	if(TGameManager::IsCreated())
	{
		if(!TGameManager::Manager()->GlobalFlags.FlagExists("Notes"))
			TGameManager::Manager()->GlobalFlags.AddFlag("Notes","");
		TGameManager::Manager()->GlobalFlags.FlagValue["Notes"] = ((TNotesGUIFrame*)GUIFrame)->Notes->Lines->Text;
		if(TGameManager::Manager()->OpenedFrame != NULL)
			TGameManager::Manager()->OpenedFrame->UnlockScreen();
	}
	if(TInventoryGUI::IsInstance())
		TInventoryGUI::Instance()->Open();
}
//---------------------------------------------------------------------------
namespace Notesgui
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TNotesGUI)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
