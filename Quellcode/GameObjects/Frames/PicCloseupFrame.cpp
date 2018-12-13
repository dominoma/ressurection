//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#include "PicCloseupFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Hotspot"
#pragma link "Exit"
#pragma resource "*.fmx"
TPicCloseupFrame *PicCloseupFrame;
//---------------------------------------------------------------------------
__fastcall TPicCloseupFrame::TPicCloseupFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPicCloseupFrame::KoordinatenTVariadicFlowList0Started(TObject *Sender)

{
	String notes;
	if(TGameManager::Manager()->GlobalFlags.FlagExists("Notes"))
	{
		notes = TGameManager::Manager()->GlobalFlags.FlagValue["Notes"];
	}
	else
	{
		TGameManager::Manager()->GlobalFlags.AddFlag("Notes","");
	}
	TGameManager::Manager()->GlobalFlags.FlagValue["Notes"] = notes + "\n\n"+Coords->Text;
}
//---------------------------------------------------------------------------


void __fastcall TPicCloseupFrame::IndiFriendshipUnlocked(TObject *Sender)
{
	((TFlowTreeItem*)((TFireplaceFrame*)TGameManager::Manager()->Frames["TFireplaceFrame"])->Indianer->ConvTree->Root->Items[3])->Hidden = false;
}
//---------------------------------------------------------------------------

