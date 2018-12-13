//---------------------------------------------------------------------------

#ifndef ItemH
#define ItemH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include "Hotspot.h"
//---------------------------------------------------------------------------
__interface IGameItemData
{
protected:
	virtual String __fastcall GetItemName(void)=0; //Name des Items
	virtual String __fastcall GetInventoryTexture(void)=0; //Pfad zum Inventar-Icon des Items
public:
	__property String ItemName = {read=GetItemName};
	__property String InventoryTexture = {read=GetInventoryTexture};
};
//---------------------------------------------------------------------------
class PACKAGE TGameItemReg : public IGameItemData
{
private:
	String FItemName;
	String FInventoryTexture;
protected:
	String __fastcall GetItemName(void){ return FItemName; };
	String __fastcall GetInventoryTexture(void){ return FInventoryTexture; };
public:
	__fastcall TGameItemReg(String ItemName);
	__fastcall ~TGameItemReg(void);
};
//---------------------------------------------------------------------------
class PACKAGE TGameItem : public THotspot, public IGameItemData
{
private:
	void PickItemUp(void);

	String __fastcall GetResourcePath(void);
	IGameItemData* __fastcall GetItemData(void){ return this; };

protected:
	void __fastcall FlowListStopped(TGameFlowList *List);
	void __fastcall SetName(String NewName);
	String __fastcall GetItemName(void){ return Name; };
	String __fastcall GetInventoryTexture(void){ return ResourcePath + "\\inventory.png"; };
public:
	__fastcall TGameItem(TComponent* Owner);
	__fastcall ~TGameItem(void);

	void __fastcall Action(void);
	void __fastcall ItemDrop(void);
public:
	__property IGameItemData* Data = {read=GetItemData};

};
//---------------------------------------------------------------------------
//Folgende Klassen ermöglichen das Kombinieren zweier Items durch den Spieler,
//um ein drittes zu erhalten. Diese Funktion ist im fertigen Spiel allerdings nicht benötigt worden,
//daher sind diese Klassen nicht dokumentiert worden
class PACKAGE TCombineCollection : public TOwnedCollection
{
public:
	__fastcall TCombineCollection(TPersistent *Owner);

	IGameRunnable* __fastcall GetFlow(String Item1Name, String Item2Name);
};
//---------------------------------------------------------------------------
class PACKAGE TCombineCollectionItem : public TCollectionItem
{
private:
	String item1Name;
	String item2Name;
	TGameFlowList *flowList;

	void __fastcall SetFlowList(TGameFlowList *FlowList);
public:
	__fastcall TCombineCollectionItem(TCollection *Owner);
	__fastcall ~TCombineCollectionItem(void);
__published:
	__property String Item2 = {read=item2Name,write=item2Name};
	__property String Item1 = {read=item1Name,write=item1Name};
	__property TGameFlowList* FlowList = {read=flowList,write=SetFlowList};
};
//---------------------------------------------------------------------------
class PACKAGE TItemList : public TFmxObject
{
private:
	TCombineCollection *combColl;

	static TItemList* itemList;
public:
	__fastcall TItemList(TComponent *Owner);
	__fastcall ~TItemList(void);

	static TItemList* __fastcall ItemList(void);
	static bool __fastcall IsItemList(void){ return itemList != NULL; };
__published:
	__property TCombineCollection* Combinations = {read=combColl,write=combColl};
};
//---------------------------------------------------------------------------
#endif
