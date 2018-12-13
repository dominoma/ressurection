//---------------------------------------------------------------------------

#ifndef ConversationGUIH
#define ConversationGUIH
#include "ConversationGUIFrame.h"
#include "GameGUI.h"
//---------------------------------------------------------------------------
class TConversationGUI;
class TFlowTreeItem;
class TFlowTreeList;
class TCustomTreeItem;
class TConversationGUIItem : public TText
{
private:
	TFlowTreeItem *FItem;

	TConversationGUI* __fastcall GetGUI(void);

	void __fastcall Click(void);
	void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall DoMouseEnter(void);
	void __fastcall DoMouseLeave(void);

	void __fastcall ItemStopped(TObject *Sender);

	void __fastcall BeforeDestruction(void);
public:
	__fastcall TConversationGUIItem(TFmxObject *Parent, TFlowTreeItem* Item);
	__property TConversationGUI* GUI = {read=GetGUI};
	__property TFlowTreeItem* Item = {read=FItem};
};
//---------------------------------------------------------------------------
class PACKAGE TItemColors : public TPersistent
{
private:
	TColor FHovered;
	TColor FPressed;
	TColor FNormal;

	void __fastcall ReadColors(TReader *Reader);
	void __fastcall WriteColors(TWriter *Writer);
protected:
	void __fastcall DefineProperties(TFiler *Filer);
public:
__published:
	__property TColor Hovered = {read=FHovered,write=FHovered,stored=false};
	__property TColor Pressed = {read=FPressed,write=FPressed,stored=false};
	__property TColor Normal = {read=FNormal,write=FNormal,stored=false};
};
//---------------------------------------------------------------------------
class PACKAGE TConversationGUI : public TGameGUI
{
private:

	TFlowTreeList *FConvTreeList;
	TCustomTreeItem* FCurrTreeItem;
	TArrayClass<TConversationGUIItem*> GUIItems;

	TItemColors *FItemColors;

	bool __fastcall LoadConvOptions(void);

	void __fastcall SetItemColors(TItemColors *Colors){ FItemColors->Assign(Colors); };
protected:
	void __fastcall DoOpen(void);
	void __fastcall DoClose(void);

	void __fastcall Resize(void);
	void __fastcall AfterPaint(void) { Resize(); };
public:
	__fastcall TConversationGUI(TComponent *Owner);

	void __fastcall SelectConv(int Index);

	void __fastcall LoadFromConvTree(TFlowTreeList *ConvTreeList);

	__property TCustomTreeItem* CurrTreeItem = {read=FCurrTreeItem,write=FCurrTreeItem};
	__property TFlowTreeList *ConvTreeList = {read=FConvTreeList};
__published:
	__property TItemColors* ItemColors = {read=FItemColors,write=SetItemColors};

};
//---------------------------------------------------------------------------
#endif
