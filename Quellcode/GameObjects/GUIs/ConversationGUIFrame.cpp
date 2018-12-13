//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop

#include "ConversationGUIFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GameGUIFrame"
#pragma resource "*.fmx"
TConversationGUIFrame *ConversationGUIFrame;
//---------------------------------------------------------------------------
__fastcall TConversationGUIFrame::TConversationGUIFrame(TComponent* Owner)
	: TGameGUIFrame(Owner)
{
}
//---------------------------------------------------------------------------

