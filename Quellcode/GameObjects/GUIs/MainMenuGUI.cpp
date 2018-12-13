//---------------------------------------------------------------------------

#include "GameObjects.h"

#pragma hdrstop

#include "MainMenuGUI.h"
#include "MainMenuGUIFrame.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TMainMenuGUI *)
{
	new TMainMenuGUI(NULL);
}
//---------------------------------------------------------------------------
__fastcall TMainMenuGUI::TMainMenuGUI(TComponent* Owner)
	: TGameGUI(Owner, new TMainMenuGUIFrame(this))
{
}
//---------------------------------------------------------------------------
void __fastcall TMainMenuGUI::StartGame(void)
{
	TGameManager::Manager()->StartGame();
}
//---------------------------------------------------------------------------
void __fastcall TMainMenuGUI::NewGame(void)
{
	TGameManager::Manager()->NewGame();
}
//---------------------------------------------------------------------------
void __fastcall TMainMenuGUI::DoOpen(void)
{
	TGameGUI::DoOpen();
	if(TGameManager::IsCreated() && BGTrack != "")
	{
		TGameManager::Manager()->PlayTrack(ResourceRoot()+"\\BGMusic\\"+BGTrack, BGVolume);
	}
}
//---------------------------------------------------------------------------
namespace Mainmenugui
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TMainMenuGUI)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
