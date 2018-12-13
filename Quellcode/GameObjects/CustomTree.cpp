//---------------------------------------------------------------------------
#define protected public
#define private public
#include <System.Classes.hpp>
#undef protected
#undef private
#include "CustomTree.h"
#include "GameExceptions.h"
#include "SerializeTools.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TCustomTreeItem::TCustomTreeItem(TBasicCustomList *Owner)
	: TBasicCustomListItem(Owner), AOwner((TCustomTree*)Owner), AParent(AOwner->Root)
{
	if(AOwner == NULL)
		throw EArgumentException("'Owner' must not be zero!");
	if(AParent != NULL)
		AParent->AddItem(this);
}
//---------------------------------------------------------------------------
__fastcall TCustomTreeItem::TCustomTreeItem(TBasicCustomList *Owner, TCustomTreeItem *Parent)
	: TBasicCustomListItem(Owner), AOwner((TCustomTree*)Owner), AParent(Parent)
{
	if(AOwner == NULL)
		throw EArgumentException("'Owner' must not be zero!");
	if(AParent != NULL)
		AParent->AddItem(this);
}
//---------------------------------------------------------------------------
__fastcall TCustomTreeItem::~TCustomTreeItem(void)
{
	Clear();
	if(AParent != NULL)
		AParent->DeleteItem(this);
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::ReadClassNames(TReader* Reader)
{
	Clear();
	Reader->ReadListBegin();
	while(!Reader->EndOfList())
	{
		Add(Reader->ReadString());
	}
	Reader->ReadListEnd();
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::WriteClassNames(TWriter* Writer)
{
	Writer->WriteListBegin();
	for(int i=0;i<Count;i++)
	{
		Writer->WriteString(Items[i]->ClassName());
	}
	Writer->WriteListEnd();
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::ReadItems(TReader *Reader)
{
	ReadObjListBegin(Reader);
	for(int i=0;!Reader->EndOfList();i++)
	{
		ReadObjListItem(Reader, Items[i]);
	}
	ReadObjListEnd(Reader);
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::WriteItems(TWriter *Writer)
{
	WriteObjListBegin(Writer);
	for(int i=0;i<Count;i++)
	{
		WriteObjListItem(Writer, Items[i]);
	}
	WriteObjListEnd(Writer);
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::DefineProperties(TFiler* Filer)
{
	bool DoWrite=true;
	Filer->DefineProperty("ItemClasses", ReadClassNames, WriteClassNames, DoWrite);
	Filer->DefineProperty("Items", ReadItems, WriteItems, DoWrite);
	TPersistent::DefineProperties(Filer);
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::SetParent(TCustomTreeItem *Parent)
{
	if(AParent == this || AParent == NULL)
		throw ECustomListError("Invalid parent! (NULL or THIS)");
	if(AParent != NULL)
	{
		int index = Index;
		AParent->DeleteItem(this);
		AParent = Parent;
		AParent->AddItem(this);
		if(index < Parent->Count)
			Index = index;
		else
			Index = Parent->Count-1;
	}
}
//---------------------------------------------------------------------------
int __fastcall TCustomTreeItem::GetIndex(void)
{
	for(int i=0;i<AParent->Count;i++)
	{
		if(AParent->Items[i] == this)
			return i;
	}
	throw ENotInParentList();
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::SetIndex(int AIndex)
{
	if(AParent != NULL)
	{
		AParent->CheckBounds(AIndex);
		AParent->SwapItems(Index,AIndex);
	}
}
//---------------------------------------------------------------------------
int __fastcall TCustomTreeItem::GetLevel(void)
{
	int layer=0;
	for(TCustomTreeItem* Item=this;Item->Parent != NULL;Item=Item->Parent)
	{
        layer++;
	}
	return layer;
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::Assign(TPersistent* Source)
{
	if(Source->InheritsFrom(TCustomTreeItem::ClassType()))
	{
		TCustomTreeItem *Item = (TCustomTreeItem*)Source;
		Clear();
		for(int i=0;i<Item->Count;i++)
		{
			Add(Item->Items[i]->ClassName())->Assign(Item->Items[i]);
        }
	}
	else
	{
        TBasicCustomListItem::Assign(Source);
    }
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::Clear(void)
{
	while(Count > 0)
	{
        delete Items[0];
    }
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::Delete(int Index)
{
	CheckBounds(Index);
	delete Items[Index];
}
//---------------------------------------------------------------------------
void __fastcall TCustomTreeItem::CheckBounds(int Index)
{
	if(Index < 0 || Index >= Count)
		throw EOutOfBounds(0,Count-1,Index);
}
//---------------------------------------------------------------------------
TCustomTreeItem* __fastcall TCustomTreeItem::Add(void)
{
	TCustomTreeItem* Item = (TCustomTreeItem*)TCustomListItem::NewListItem(Owner->AllowedClasses()->Items[0],Owner);
	Item->Parent = this;
	return Item;
}
//---------------------------------------------------------------------------
TCustomTreeItem* __fastcall TCustomTreeItem::Add(String ClassName)
{
	TCustomTreeItem* Item = (TCustomTreeItem*)TCustomListItem::NewListItem(Owner->GetClassByName(ClassName),Owner);
	Item->Parent = this;
	return Item;
}
//---------------------------------------------------------------------------
TPersistent* __fastcall TCustomTreeItem::GetOwner(void)
{
	return AOwner;
}
//---------------------------------------------------------------------------
String __fastcall TCustomTreeItem::GetNamePath(void)
{
	String name;
	for(TCustomTreeItem *Item=this;Item->Parent!=NULL;Item=Item->Parent)
	{
		name = "["+String(Item->Index)+"]"+name;
	}
	return Owner->GetNamePath()+"."+ClassName()+name;
}
//---------------------------------------------------------------------------
String __fastcall TCustomTreeItem::DisplayName(void)
{
	return ClassName();
}
//---------------------------------------------------------------------------
__fastcall TCustomTree::TCustomTree(TPersistent *Owner)
	: classList(new TClassList), AOwner(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TCustomTree::~TCustomTree(void)
{
	delete classList;
}
//---------------------------------------------------------------------------
bool __fastcall TCustomTree::IsClassAllowed(TClass Class)
{
	TClassList *List = AllowedClasses();
	for(int i=0;i<List->Count;i++)
	{
		if(Class->InheritsFrom(List->Items[i]))
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
TClass __fastcall TCustomTree::GetClassByName(String ClassName)
{
	TClassList *List = AllowedClasses();
	for(int i=0;i<List->Count;i++)
	{
		if(List->Items[i]->ClassName() == ClassName)
			return List->Items[i];
	}
	throw EClassNotAllowed(ClassName);
}
//---------------------------------------------------------------------------
TClassList* __fastcall TCustomTree::AllowedClasses(void)
{
	classList->Clear();
	SetAllowedClasses(classList);
	return classList;
}
//---------------------------------------------------------------------------
void __fastcall TCustomTree::DefineProperties(TFiler* Filer)
{
	bool DoWrite = true;
	Filer->DefineProperty("Root", ReadRoot, WriteRoot, DoWrite);
	TPersistent::DefineProperties(Filer);
}
//---------------------------------------------------------------------------
void __fastcall TCustomTree::ReadRoot(TReader* Reader)
{
	Reader->CheckValue(vaCollection);
		Reader->ReadListBegin();
		Root->DefineProperties(Reader);
		while(!Reader->EndOfList())
		{
            Reader->ReadProperty(Root);
        }
		Reader->ReadListEnd();
	Reader->ReadListEnd();
	/*ReadObjListBegin(Reader);
	ReadObjListItem(Reader, Root);
	ReadObjListEnd(Reader);*/
}
//---------------------------------------------------------------------------
void __fastcall TCustomTree::WriteRoot(TWriter* Writer)
{
	Writer->WriteValue(vaCollection);
		Writer->FPropPath = "";
		Writer->WriteListBegin();
		Root->DefineProperties(Writer);
		Writer->WriteListEnd();
	Writer->WriteListEnd();
	/*WriteObjListBegin(Writer);
	WriteObjListItem(Writer, Root);
	WriteObjListEnd(Writer); */
}
//---------------------------------------------------------------------------
void __fastcall TCustomTree::SetAllowedClasses(TClassList *ClassList)
{
	ClassList->Add(__classid(TCustomTreeItem));
}
//---------------------------------------------------------------------------
__fastcall TVectorTree::TVectorTree(TPersistent *Owner)
	: TCustomTree(Owner), root(new TVectorTreeItem(this,NULL))
{
}
//---------------------------------------------------------------------------
void __fastcall TVectorTree::SetAllowedClasses(TClassList *ClassList)
{
	TCustomTree::SetAllowedClasses(ClassList);
	ClassList->Add(__classid(TVectorTreeItem));
}
//---------------------------------------------------------------------------
__fastcall TVectorTreeItem::TVectorTreeItem(TBasicCustomList *Owner)
	: TCustomTreeItem(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TVectorTreeItem::TVectorTreeItem(TBasicCustomList *Owner, TCustomTreeItem *Parent)
	: TCustomTreeItem(Owner,Parent)
{

}
//---------------------------------------------------------------------------
void __fastcall TVectorTreeItem::SetItem(int Index, TCustomTreeItem *Item)
{
	delete Items[Index];
	items.Insert(Index,Item);
}
//---------------------------------------------------------------------------
void __fastcall TVectorTreeItem::SwapItems(int Index1, int Index2)
{
	TCustomTreeItem *Item = items[Index1];
	items[Index1] = items[Index2];
	items[Index2] = Item;
}
//---------------------------------------------------------------------------
