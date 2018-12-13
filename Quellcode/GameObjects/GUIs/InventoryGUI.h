//---------------------------------------------------------------------------

#ifndef InventoryGUIH
#define InventoryGUIH
#include "InventoryGUIFrame.h"
#include "GameGUI.h"
#include "ImageButton.h"
//---------------------------------------------------------------------------
class TInventoryGUI;
class PACKAGE TInventoryItem : public TImageButton
{
private:
	TImage *FItemIcon;
	TInventoryGUI *FGUI;
	IGameItemData *FItem;
protected:
	void __fastcall Click(void);
public:
	__fastcall TInventoryItem(TInventoryGUI *GUI, IGameItemData *Item);
	__property TInventoryGUI* GUI = {read=FGUI};
	__property IGameItemData* Item = {read=FItem};
};
//---------------------------------------------------------------------------
class PACKAGE TInventoryGUI : public TGameGUI
{
private:
	TArrayClass<TInventoryItem*> items;
	IGameItemData *selItem;

	TBitmap *FItemNormal;
	TBitmap *FItemHovered;
	TBitmap *FItemSelected;

	void __fastcall SetItemNormal(TBitmap *Bmp){ FItemNormal->CopyFromBitmap(Bmp); UpdateItemBitmaps(); };
	void __fastcall SetItemHovered(TBitmap *Bmp){ FItemHovered->CopyFromBitmap(Bmp); UpdateItemBitmaps(); };
	void __fastcall SetItemSelected(TBitmap *Bmp){ FItemSelected->CopyFromBitmap(Bmp); UpdateItemBitmaps(); };

	void __fastcall BitmapChanged(TObject *Sender){ UpdateItemBitmaps(); };

	void __fastcall UpdateItemBitmaps(void);

	int __fastcall GetIndex(IGameItemData* Item);

	void __fastcall ClearItems(void);
public:
	__fastcall TInventoryGUI(TComponent *Owner);
	__fastcall ~TInventoryGUI(void);

	void __fastcall Reset(void){ ClearItems(); };

	IGameItemData* __fastcall SelectedItem(void);
	bool __fastcall IsItemSelected(void){ return selItem != NULL; };

	void __fastcall DisableMenuButton(void);
	void __fastcall EnableMenuButton(void);

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	void __fastcall AddItem(IGameItemData* Item);
	void __fastcall DeleteItem(IGameItemData* Item);
	void __fastcall SelectItem(IGameItemData* Item);
	bool __fastcall IsItemInInventory(IGameItemData* Item);

	void __fastcall OpenMenu(void);
	void __fastcall OpenNodes(void);
__published:
	__property TBitmap* ItemNormal = {read=FItemNormal,write=SetItemNormal};
	__property TBitmap* ItemHovered = {read=FItemHovered,write=SetItemHovered};
	__property TBitmap* ItemSelected = {read=FItemSelected,write=SetItemSelected};
};
//---------------------------------------------------------------------------
#endif
