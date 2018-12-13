//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop

#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//
//---------------------------------------------------------------------------
__fastcall TConvPart::TConvPart(TCollection *Owner)
	: TCollectionItem(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConvPart::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TConvPart)))
	{
		TConvPart *Item = (TConvPart*)Source;
		FAudioFile = Item->FAudioFile;
		FCaption = Item->FCaption;
	}
	else
		TCollectionItem::Assign(Source);
}
//---------------------------------------------------------------------------
String __fastcall TConvPart::GetAudioDir(void)
{
	TConversationFlowItem *Item = (TConversationFlowItem*)Collection->Owner();
	if(Item->Person != NULL)
		return Item->Person->ResourceRoot()+"\\Dialogs\\"+Item->Dialog+"\\";
}
//---------------------------------------------------------------------------
__fastcall TConvParts::TConvParts(TConversationFlowItem *Owner)
	: TOwnedCollection(Owner, __classid(TConvPart))
{
}
//---------------------------------------------------------------------------
__fastcall TConversationFlowItem::TConversationFlowItem(TBasicCustomList* List)
	: TCustomFlowItem(List), FConvParts(new TConvParts(this)), FPerson(NULL)
{
	LockScreen = true;
}
//---------------------------------------------------------------------------
__fastcall TConversationFlowItem::~TConversationFlowItem(void)
{
	delete FConvParts;
}
//---------------------------------------------------------------------------
void __fastcall TConversationFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TConversationFlowItem)))
	{
		TConversationFlowItem *Item = (TConversationFlowItem*)Source;
		FPerson = Item->FPerson;
		FIdleAnimation = Item->FIdleAnimation;
		FTalkAnimation = Item->FTalkAnimation;
		FConvParts->Assign(Item->FConvParts);
	}
	TCustomFlowItem::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TConversationFlowItem::AddFlowItems(TFlowItemAddProc AddProc)
{
	if(FTalkAnimation != "")
	{
		TChangeAnimationFlowItem *TalkChange = AddItem<TChangeAnimationFlowItem>(AddProc);
		TalkChange->Object = FPerson;
		TalkChange->Animation = FTalkAnimation;
	}

	for(int i=0;i<FConvParts->Count;i++)
	{
		TAudioFlowItem *ConvFlow = AddItem<TAudioFlowItem>(AddProc);
		TConvPart *CurrItem = (TConvPart*)FConvParts->Items[i];
		ConvFlow->Object = FPerson;
		ConvFlow->AudioFile = CurrItem->AudioDir + CurrItem->AudioFile;
		ConvFlow->SpeakerName = FPerson->Name;
		ConvFlow->Caption = CurrItem->Caption;
	}
	if(FIdleAnimation != "")
	{
		TChangeAnimationFlowItem *IdleChange = AddItem<TChangeAnimationFlowItem>(AddProc);
		IdleChange->Object = FPerson;
		IdleChange->Animation = FIdleAnimation;
	}
}
//---------------------------------------------------------------------------
String __fastcall TConversationFlowItem::GetTexturePath(void)
{
	if(FPerson != NULL)
		return FPerson->ResourcePath;
}
//---------------------------------------------------------------------------
