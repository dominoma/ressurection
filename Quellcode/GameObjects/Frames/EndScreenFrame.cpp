//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "EndScreenFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameFrame"
#pragma link "GameObject"
#pragma resource "*.fmx"
TEndScreenFrame *EndScreenFrame;
//---------------------------------------------------------------------------
__fastcall TEndScreenFrame::TEndScreenFrame(TComponent* Owner)
	: TGameFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEndScreenFrame::GameEnded(TObject *Sender)

{
	TGameManager::Manager()->OpenFrame("TCityEntryFrame","");
	TGameManager::Manager()->StopGame();
}
//---------------------------------------------------------------------------
