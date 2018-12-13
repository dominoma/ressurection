//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop

#include "InventoryGUI.h"
#include "NotesGUI.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Inventorygui
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TInventoryGUI)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
__fastcall TInventoryItem::TInventoryItem(TInventoryGUI *GUI, IGameItemData *Item)
	: TImageButton(GUI->GUIFrame), FGUI(GUI), FItem(Item), FItemIcon(new TImage(this))
{
	Parent = ((TInventoryGUIFrame*)GUI->GUIFrame)->ItemContainer;
	StaysPressed = true;

	BmpNormal = GUI->ItemNormal;
	BmpHovered = GUI->ItemHovered;
	BmpPressed = GUI->ItemSelected;

	FItemIcon->Parent = this;
	FItemIcon->Align = TAlignLayout::Contents;
	FItemIcon->Bitmap->LoadFromFile(Item->InventoryTexture);
	FItemIcon->HitTest = false;
}
//---------------------------------------------------------------------------
void __fastcall TInventoryItem::Click(void)
{
	TImageButton::Click();
	if(IsPressed)
		GUI->SelectItem(Item);
	else
		GUI->SelectItem(NULL);
}
//---------------------------------------------------------------------------
__fastcall TInventoryGUI::TInventoryGUI(TComponent *Owner)
	: TGameGUI(Owner, new TInventoryGUIFrame(this)), selItem(NULL),
	  FItemNormal(new TBitmap), FItemHovered(new TBitmap), FItemSelected(new TBitmap)
{
	FItemNormal->OnChange = BitmapChanged;
	FItemHovered->OnChange = BitmapChanged;
	FItemSelected->OnChange = BitmapChanged;
}
//---------------------------------------------------------------------------
__fastcall TInventoryGUI::~TInventoryGUI(void)
{
	delete FItemNormal;
	delete FItemHovered;
	delete FItemSelected;
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::OpenMenu(void)
{
	TGameManager::Manager()->StopGame();
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::OpenNodes(void)
{
	TNotesGUI::Instance()->Open();
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::DisableMenuButton(void)
{
	((TInventoryGUIFrame*)GUIFrame)->MenuButton->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::EnableMenuButton(void)
{
	((TInventoryGUIFrame*)GUIFrame)->MenuButton->Enabled = true;
}
//---------------------------------------------------------------------------
IGameItemData* __fastcall TInventoryGUI::SelectedItem(void)
{
	if(selItem == NULL)
		throw EArgumentException("There is no Item selected!");
	return selItem;
}
//---------------------------------------------------------------------------
int __fastcall TInventoryGUI::GetIndex(IGameItemData* Item)
{
	if(Item == NULL)
		return -1;
	for(int i=0;i<items.Count();i++)
	{
		if(items[i]->Item->ItemName == Item->ItemName)
		{
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
bool __fastcall TInventoryGUI::IsItemInInventory(IGameItemData* Item)
{
	return GetIndex(Item) != -1;
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::AddItem(IGameItemData* Item)
{
	if(IsItemInInventory(Item))
		throw EArgumentException("Item '"+Item->ItemName+"' is already in the inventory!");
	items.Add(new TInventoryItem(this,Item));
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::DeleteItem(IGameItemData* Item)
{
	int Index = GetIndex(Item);
	if(Index == -1)
		throw EArgumentException("Item '"+Item->ItemName+"' is not in the inventory!");
	delete items[Index];
	items.Delete(Index);
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::SelectItem(IGameItemData* Item)
{
	if(Item != NULL && GetIndex(Item) == -1)
		throw EArgumentException("Item '"+Item->ItemName+"' is not in the inventory!");
	for(int i=0;i<items.Count();i++)
	{
		items[i]->IsPressed = Item == NULL ? false : items[i]->Item->ItemName == Item->ItemName;
	}
	selItem = Item;
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::UpdateItemBitmaps(void)
{
	for(int i=0;i<items.Count();i++)
	{
		items[i]->BmpNormal = ItemNormal;
		items[i]->BmpHovered = ItemHovered;
		items[i]->BmpPressed = ItemSelected;
	}
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TInventoryGUI::ToXmlNode(void)
{
	_di_IXMLNode Node = CreateNode(ClassName());
	for(int i=0;i<items.Count();i++)
	{
		Node->AddChild(items[i]->ClassName())->Attributes["Name"] = items[i]->Item->ItemName;
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::FromXmlNode(_di_IXMLNode Node)
{
	if(Node->NodeName != ClassName())
		throw EArgumentException("'"+Node->NodeName+"' doesn't fit to this class!");
	ClearItems();
	if(TGameManager::IsCreated())
	{
		for(int i=0;i<Node->ChildNodes->Count;i++)
		{
			AddItem(TGameManager::Manager()->Items[Node->ChildNodes->GetNode(i)->Attributes["Name"]]);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TInventoryGUI::ClearItems(void)
{
	for(int i=0;i<items.Count();i++)
	{
        delete items[i];
    }
	items.Clear();
}
//---------------------------------------------------------------------------
