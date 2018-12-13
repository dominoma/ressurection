//---------------------------------------------------------------------------

#ifndef CustomTreeH
#define CustomTreeH
#include "CustomList.h"
#include "Flows/GameFlow.h"
//---------------------------------------------------------------------------
class TCustomTree;
class TCustomTreeItem;
class PACKAGE TCustomTreeItem : public TBasicCustomListItem
{
private:
	TCustomTree *AOwner;
	TCustomTreeItem *AParent;

	void __fastcall SetParent(TCustomTreeItem *Parent);

	int __fastcall GetIndex(void);
	void __fastcall SetIndex(int Index);

	int __fastcall GetLevel(void);

	void __fastcall ReadItems(TReader* Reader);
	void __fastcall WriteItems(TWriter* Writer);
	void __fastcall ReadClassNames(TReader* Reader);
	void __fastcall WriteClassNames(TWriter* Writer);

protected:
	DYNAMIC TPersistent* __fastcall GetOwner(void);
	DYNAMIC String __fastcall GetNamePath(void);

	virtual TCustomTreeItem* __fastcall GetItem(int Index)=0;
	virtual void __fastcall SetItem(int Index, TCustomTreeItem *Item)=0;

	virtual void __fastcall AddItem(TCustomTreeItem *Item)=0;
	virtual void __fastcall DeleteItem(TCustomTreeItem *Item)=0;

	virtual int __fastcall GetCount(void)=0;

	void __fastcall CheckBounds(int Index);

public:
	virtual String __fastcall DisplayName(void);

	virtual void __fastcall DefineProperties(TFiler* Filer);
	virtual void __fastcall Assign(TPersistent* Source);

	virtual void __fastcall SwapItems(int Index1, int Index2)=0;

	void __fastcall Clear(void);
	void __fastcall Delete(int Index);
	TCustomTreeItem* __fastcall Add(void);
	TCustomTreeItem* __fastcall Add(String ClassName);

	__fastcall TCustomTreeItem(TBasicCustomList *Owner);
	__fastcall TCustomTreeItem(TBasicCustomList *Owner, TCustomTreeItem *Parent);
	__fastcall ~TCustomTreeItem(void);

	__property TCustomTreeItem* Parent = {read=AParent,write=SetParent};
	__property TCustomTree* Owner = {read=AOwner};

	__property int Index = {read=GetIndex,write=SetIndex};
	__property int Level = {read=GetLevel};

	__property int Count = {read=GetCount};

	__property TCustomTreeItem* Items[int Index] = {read=GetItem,write=SetItem};
};
//---------------------------------------------------------------------------
class PACKAGE TCustomTree : public TBasicCustomList
{
private:
	TClassList *classList;
    TPersistent *AOwner;

	void __fastcall ReadRoot(TReader* Reader);
	void __fastcall WriteRoot(TWriter* Writer);
protected:

	virtual void __fastcall SetAllowedClasses(TClassList *ClassList);

	DYNAMIC TPersistent* __fastcall GetOwner(void){ return AOwner; };
	virtual void __fastcall DefineProperties(TFiler* Filer);

	virtual TCustomTreeItem* __fastcall GetRoot(void)=0;
public:

	bool __fastcall IsClassAllowed(TClass Class);
	TClass __fastcall GetClassByName(String ClassName);
	TClassList* __fastcall AllowedClasses(void);

	__fastcall TCustomTree(TPersistent *Owner);
	__fastcall ~TCustomTree(void);

	__property TCustomTreeItem* Root = {read=GetRoot};
	__property TPersistent* Owner = {read=AOwner};
};
//---------------------------------------------------------------------------
class PACKAGE TVectorTreeItem : public TCustomTreeItem
{
private:
	TArrayClass<TCustomTreeItem*> items;

	TCustomTreeItem* __fastcall GetItem(int Index){ return items[Index]; };
	void __fastcall SetItem(int Index, TCustomTreeItem *Item);
	void __fastcall SwapItems(int Index1, int Index2);
	void __fastcall AddItem(TCustomTreeItem *Item){ items.Add(Item); };
	void __fastcall DeleteItem(TCustomTreeItem *Item){ items.Delete(Item->Index); };

	int __fastcall GetCount(void){ return items.Count(); };
public:
	__fastcall TVectorTreeItem(TBasicCustomList *Owner);
	__fastcall TVectorTreeItem(TBasicCustomList *Owner, TCustomTreeItem *Parent);
};
//---------------------------------------------------------------------------
class PACKAGE TVectorTree : public TCustomTree
{
private:
	TVectorTreeItem* root;
	TCustomTreeItem* __fastcall GetRoot(void){ return root; };
protected:
	virtual void __fastcall SetAllowedClasses(TClassList *ClassList);
public:
	__fastcall TVectorTree(TPersistent *Owner);
};
//---------------------------------------------------------------------------
#endif
