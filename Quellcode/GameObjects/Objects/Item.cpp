//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
#pragma package(smart_init)
TItemList* TItemList::itemList=NULL;
//---------------------------------------------------------------------------
__fastcall TGameItemReg::TGameItemReg(String ItemName)
	: FItemName(ItemName), FInventoryTexture(TGameBase::RunPath() + "\\Resources\\Items\\"+ItemName+".png")
{
	TGameManager::Manager()->RegisterItem(this);
}
//---------------------------------------------------------------------------
__fastcall TGameItemReg::~TGameItemReg(void)
{
	TGameManager::Manager()->UnregisterItem(this);
}
//---------------------------------------------------------------------------
__fastcall TGameItem::TGameItem(TComponent* Owner)
	: THotspot(Owner)
{
	if(TGameManager::IsCreated())
		TGameManager::Manager()->RegisterItem(this);
}
//---------------------------------------------------------------------------
__fastcall TGameItem::~TGameItem(void)
{
	if(TGameManager::IsCreated())
		TGameManager::Manager()->UnregisterItem(this);
}
//---------------------------------------------------------------------------
void __fastcall TGameItem::SetName(String NewName)
{
	if(TGameManager::IsCreated() && TGameManager::Manager()->ItemExists[NewName])
	{
		if(!ComponentState.Contains(csLoading))
		{
			throw EArgumentException("Item with name '"+NewName+"' already exists!");
		}
	}
	THotspot::SetName(NewName);

}
//---------------------------------------------------------------------------
String __fastcall TGameItem::GetResourcePath(void)
{
	return TGameObject::ResourceRoot() + "\\Frames\\"+Owner->Name+"\\Items\\"+Name;
}
//---------------------------------------------------------------------------
namespace Item
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[] = {__classid(TGameItem), __classid(TItemList)};
		RegisterComponents(L"Adventure", classes, 1);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameItem::FlowListStopped(TGameFlowList *List)
{
	THotspot::FlowListStopped(List);
	if(List == StateSelActnFlow)
		PickItemUp();
}
//---------------------------------------------------------------------------
void __fastcall TGameItem::Action(void)
{
	
}
//---------------------------------------------------------------------------
void __fastcall TGameItem::ItemDrop(void)
{
	
}
//---------------------------------------------------------------------------
void TGameItem::PickItemUp(void)
{
	if(!((TInventoryGUI*)TInventoryGUI::Instance())->IsItemInInventory(Data))
		((TInventoryGUI*)TInventoryGUI::Instance())->AddItem(Data);
}
//---------------------------------------------------------------------------
__fastcall TCombineCollection::TCombineCollection(TPersistent *Owner)
	: TOwnedCollection(Owner,__classid(TCombineCollectionItem))
{
}
//---------------------------------------------------------------------------
IGameRunnable* __fastcall TCombineCollection::GetFlow(String Item1Name, String Item2Name)
{
	for(int i=0;i<Count;i++)
	{
		TCombineCollectionItem *CurrItem = (TCombineCollectionItem*)Items[i];
		if((CurrItem->Item1 == Item1Name && CurrItem->Item2 == Item2Name) ||
		   (CurrItem->Item1 == Item2Name && CurrItem->Item2 == Item1Name)   )
			return CurrItem->FlowList;
	}
	throw EArgumentException("Nohing found!");
}
//---------------------------------------------------------------------------
__fastcall TCombineCollectionItem::TCombineCollectionItem(TCollection *Owner)
	: TCollectionItem(Owner), flowList(new TVariadicFlowList(NULL))
{
}
//---------------------------------------------------------------------------
__fastcall TCombineCollectionItem::~TCombineCollectionItem(void)
{
	delete flowList;
}
//---------------------------------------------------------------------------
void __fastcall TCombineCollectionItem::SetFlowList(TGameFlowList *FlowList)
{
	delete flowList;
	flowList = FlowList;
}
//---------------------------------------------------------------------------
__fastcall TItemList::TItemList(TComponent *Owner)
	: TFmxObject(Owner),
	  combColl(new TCombineCollection(this))
{
	if(itemList == NULL)
		itemList = this;
	else
		throw EArgumentException("ItemList was already created!");
}
//---------------------------------------------------------------------------
__fastcall TItemList::~TItemList(void)
{
	delete combColl;

	if(itemList == this)
		itemList = NULL;
}
//---------------------------------------------------------------------------
TItemList* __fastcall TItemList::ItemList(void)
{
	if(itemList == NULL)
		throw EArgumentException("ItemList isn't created yet!");
	return itemList;
}
//---------------------------------------------------------------------------
