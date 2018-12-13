//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop

#include "ConversationGUI.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Conversationgui
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TConversationGUI)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
__fastcall TConversationGUI::TConversationGUI(TComponent *Owner)
	: TGameGUI(Owner, new TConversationGUIFrame(this)), FItemColors(new TItemColors),
	FConvTreeList(NULL), FCurrTreeItem(NULL)
{
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUI::LoadFromConvTree(TFlowTreeList *ConvTreeList)
{
	FConvTreeList = ConvTreeList;
	FCurrTreeItem = ConvTreeList->Root;
	if(IsOpen)
		LoadConvOptions();
}
//---------------------------------------------------------------------------
bool __fastcall TConversationGUI::LoadConvOptions(void)
{
	for(int i=0;i<GUIItems.Count();i++)
		delete GUIItems[i];
	GUIItems.Clear();
	if(!ConvTreeList == NULL && !CurrTreeItem == NULL)
	{
		for(int i=CurrTreeItem->Count-1;i>=0;i--)
		{
			TFlowTreeItem* SubItem = (TFlowTreeItem*)CurrTreeItem->Items[i];
			if(!SubItem->Hidden)
			{
				GUIItems.Add(new TConversationGUIItem(((TConversationGUIFrame*)GUIFrame)->BGImage,SubItem));
				//GUIItems.Last()->Position->Y = i*GUIItems.Last()->AbsoluteRect.Height();
			}
		}
		Resize();
		DoRealign();
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUI::Resize(void)
{
	if(GUIItems.Count() > 0)
		Height = GUIItems.Count() * (GUIItems[0]->Height + GUIItems[0]->Margins->Top + GUIItems[0]->Margins->Bottom) + ((TControl*)GUIItems[0]->Parent)->Padding->Top + ((TControl*)GUIItems[0]->Parent)->Padding->Bottom;
	TGameGUI::Resize();
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUI::DoOpen(void)
{
	LoadConvOptions();
	TGameGUI::DoOpen();
	if(!ComponentState.Contains(csLoading) && !ComponentState.Contains(csDesigning))
		TInventoryGUI::Instance()->Close();
	if(TGameManager::IsCreated() &&  TGameManager::Manager()->OpenedFrame != NULL)
		TGameManager::Manager()->OpenedFrame->LockScreen();
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUI::DoClose(void)
{
	TGameGUI::DoClose();
	if(TGameManager::IsCreated() &&  TGameManager::Manager()->OpenedFrame != NULL)
		TGameManager::Manager()->OpenedFrame->UnlockScreen();
	if(!ComponentState.Contains(csLoading) && !ComponentState.Contains(csDesigning))
		TInventoryGUI::Instance()->Open();
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUI::SelectConv(int Index)
{
	//TCustomTreeItem *test = CurrTreeItem->Items[Index];
	//TGameFlowList *Flow = ((TFlowTreeItem*)test)->FlowList;
	ShowMessage(int(ConvTreeList->Root));
	if(Index == FCurrTreeItem->Count-1)
	{
		FCurrTreeItem = FCurrTreeItem->Parent;
	}
	else if(FCurrTreeItem->Items[Index]->Count > 0)
	{
		FCurrTreeItem = FCurrTreeItem->Items[Index];
	}
	//if(Flow != NULL)
	   //	Flow->Start();
}
//---------------------------------------------------------------------------
void __fastcall TItemColors::ReadColors(TReader *Reader)
{
	Reader->ReadListBegin();
	FHovered = Reader->ReadInteger();
	FPressed = Reader->ReadInteger();
	FNormal = Reader->ReadInteger();
	Reader->ReadListEnd();
}
//---------------------------------------------------------------------------
void __fastcall TItemColors::WriteColors(TWriter *Writer)
{
	Writer->WriteListBegin();
	Writer->WriteInteger(FHovered);
	Writer->WriteInteger(FPressed);
	Writer->WriteInteger(FNormal);
	Writer->WriteListEnd();
}
//---------------------------------------------------------------------------
void __fastcall TItemColors::DefineProperties(TFiler *Filer)
{
	Filer->DefineProperty("Colors",ReadColors,WriteColors,true);
}
//---------------------------------------------------------------------------
__fastcall TConversationGUIItem::TConversationGUIItem(TFmxObject *Parent,
	TFlowTreeItem* Item)
	: TText(Parent->Owner), FItem(Item)
{
	Text = FItem->Text;
	AutoSize = true;
	Align = TAlignLayout::Top;
	Margins->Bottom = 7;
	Stored = false;
	this->Parent = Parent;
	TextSettings->HorzAlign = TTextAlign::Leading;
	Font->Family = "Comic Sans MS";
	TextSettings->FontColor = NormalToAlphaColor(GUI->ItemColors->Normal);
	Font->Size = 25;

	FItem->FlowList->OnStopped = ItemStopped;
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUIItem::BeforeDestruction(void)
{
	HitTest = false;
	TText::BeforeDestruction();
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUIItem::ItemStopped(TObject *Sender)
{

}
//---------------------------------------------------------------------------
TConversationGUI* __fastcall TConversationGUIItem::GetGUI(void)
{
	return (TConversationGUI*)TConversationGUI::Instance();
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUIItem::Click(void)
{
	//TText::Click();
	if(FItem->HideItem)
		FItem->Hidden = true;
	if(FItem->Index == FItem->Parent->Count-1)
	{
		GUI->CurrTreeItem = FItem->Parent->Parent;
	}
	else if(FItem->Count > 0)
	{
		GUI->CurrTreeItem = FItem;
	}
	GUI->Close();
	//ShowMessage(FItem->FlowList->GameObject->Name);
	FItem->FlowList->Start();
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUIItem::MouseUp(TMouseButton Button, TShiftState Shift, float X, float Y)
{
	if(HitTest)
	{
		TextSettings->FontColor = NormalToAlphaColor(GUI->ItemColors->Hovered);
	}
	TText::MouseUp(Button,Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUIItem::MouseDown(TMouseButton Button, TShiftState Shift, float X, float Y)
{
	if(HitTest)
	{
		TextSettings->FontColor = NormalToAlphaColor(GUI->ItemColors->Pressed);
	}
	TText::MouseDown(Button,Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUIItem::DoMouseEnter(void)
{
	if(HitTest)
	{
		TextSettings->FontColor = NormalToAlphaColor(GUI->ItemColors->Hovered);
	}
	TText::DoMouseEnter();
}
//---------------------------------------------------------------------------
void __fastcall TConversationGUIItem::DoMouseLeave(void)
{
	if(HitTest)
	{
		TextSettings->FontColor = NormalToAlphaColor(GUI->ItemColors->Normal);
	}
	TText::DoMouseLeave();
}
//---------------------------------------------------------------------------
