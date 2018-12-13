//---------------------------------------------------------------------------

#pragma hdrstop
#include "CustomList.h"
#include "GameExceptions.h"
#include "SerializeTools.h"
#include "PropertyClasses.h"
#include <FMX.Dialogs.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Customlist
{
	void __fastcall PACKAGE Register()
	{
		TPersistentClass Classes[] = {__classid(TCustomListItem),__classid(TCustomList)};
		RegisterClasses(Classes, 1);
	}
}
//---------------------------------------------------------------------------
__fastcall TCustomListItem::TCustomListItem(TBasicCustomList *Owner)
	: TBasicCustomListItem(Owner), AOwner((TCustomList*)Owner)
{
	if(AOwner == NULL)
		throw EArgumentException("'Owner' must not be zero!");
	ParentList->DoAddItem(this);
}
//---------------------------------------------------------------------------
bool __fastcall TCustomListItem::Equals(TObject *Obj)
{
	if(Obj == NULL)
		return false;
	return TPropertyList::EqualByPublished(Obj,this);
}
//---------------------------------------------------------------------------
__fastcall TCustomListItem::~TCustomListItem(void)
{
	ParentList->DeleteItem(this);
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TCustomListItem::ToXmlNode(TComponent *Root)
{
	TPropertyList *List = new TPropertyList(this,Root);
	List->ReloadProperties();
	_di_IXMLNode Node = CreateNode(ClassName());
	Node->ChildNodes->Add(List->ToXmlNode());
	delete List;
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TCustomListItem::FromXmlNode(_di_IXMLNode Node, TComponent *Root)
{
	TPropertyList *List = new TPropertyList(this,Root);
	List->FromXmlNode(Node->ChildNodes->GetNode("PropertyList"));
	List->ApplyValues();
	delete List;
}
//---------------------------------------------------------------------------
String __fastcall TCustomListItem::GetNamePath(void)
{
	return AOwner->GetNamePath() + "["+String(Index)+"]";
}
//---------------------------------------------------------------------------
int __fastcall TCustomListItem::GetIndex(void)
{
	for(int i=0;i<ParentList->Count;i++)
	{
		if(ParentList->Items[i] == this)
			return i;
	}
	throw ENotInParentList();
}
//---------------------------------------------------------------------------
TPersistent* __fastcall TCustomListItem::GetOwner(void)
{
	return AOwner;
}
//---------------------------------------------------------------------------
String __fastcall TCustomListItem::DisplayName(void)
{
	return ClassName();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TCustomList::TCustomList(TPersistent *Owner)
	: AOwner(Owner), classList(new TClassList)
{
}
//---------------------------------------------------------------------------
__fastcall TCustomList::~TCustomList(void)
{
	Clear();
	delete classList;
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TCustomList::ToXmlNode(TComponent *Root)
{
	TPropertyList *List = new TPropertyList(this,Root);
	List->ReloadProperties();
	_di_IXMLNode Node = CreateNode(ClassName());
	Node->ChildNodes->Add(List->ToXmlNode());
	_di_IXMLNode ChildNode = Node->AddChild("ChildElements");
	for(int i=0;i<Count;i++)
	{
		ChildNode->ChildNodes->Add(Items[i]->ToXmlNode(Root));
    }
	delete List;
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::FromXmlNode(_di_IXMLNode Node, TComponent *Root)
{
	Clear();
	TPropertyList *List = new TPropertyList(this,Root);
	List->FromXmlNode(Node->ChildNodes->GetNode("PropertyList"));
	List->ApplyValues();
	_di_IXMLNodeList Children = Node->ChildNodes->GetNode("ChildElements")->ChildNodes;
	for(int i=0;i<Children->Count;i++)
	{
        Add(Children->Get(i)->LocalName)->FromXmlNode(Children->Get(i),Root);
    }
	delete List;
}
//---------------------------------------------------------------------------
bool __fastcall TCustomList::Equals(TObject *Obj)
{
	if(Obj == NULL)
		return false;
	if(!Obj->InheritsFrom(ClassType()))
		return false;
	TCustomList *List = (TCustomList*)Obj;
	if(List->Count != Count)
		return false;
	for(int i=0;i<Count;i++)
	{
		if(!Items[i]->Equals(List->Items[i]))
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TCustomList)))
	{
		TCustomList *Item = (TCustomList*)Source;
		Clear();
		for(int i=0;i<Item->Count;i++)
		{
            Add(Item->Items[i]->ClassName())->Assign(Item->Items[i]);
        }
	}
	else
		TPersistent::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::SetItem(int Index, TCustomListItem *Item)
{
	Items[Index]->Assign(Item);
}
//---------------------------------------------------------------------------
TClass __fastcall TCustomList::GetClassByName(String ClassName)
{
	TClassList* classes = AllowedClasses();
	for(int i=0;i<classes->Count;i++)
	{
		if(classes->Items[i]->ClassName() == ClassName)
			return classes->Items[i];
	}
	throw EClassNotAllowed(ClassName);
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::SetAllowedClasses(TClassList *ClassList)
{
	ClassList->Add(__classid(TCustomListItem));
}
//---------------------------------------------------------------------------
TClassList* __fastcall TCustomList::AllowedClasses(void)
{
	classList->Clear();
	SetAllowedClasses(classList);
	return classList;
}
//---------------------------------------------------------------------------
TPersistent* __fastcall TCustomList::GetOwner(void)
{
	return AOwner;
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::Clear(void)
{
	while(Count > 0)
		Delete(0);
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::Delete(int Index)
{
	delete Items[Index];
}
//---------------------------------------------------------------------------
TCustomListItem* __fastcall TCustomList::Add(String ClassName)
{
	TCustomListItem::NewListItem(GetClassByName(ClassName),this);
	return Items[Count-1];
}
//---------------------------------------------------------------------------
TCustomListItem* __fastcall TCustomList::Add(void)
{
	TClassList *classes = AllowedClasses();
	if(classes->Count == 1)
	{
        TCustomListItem::NewListItem(classes->Items[0],this);
		return Items[Count-1];
    }
	else
	{
		throw ECustomListError("There isn't just one class registred!");
    }
}
//---------------------------------------------------------------------------
TCustomListItem* __fastcall TCustomList::Add(TClass Class)
{
	GetClassByName(Class->ClassName());
	TCustomListItem::NewListItem(Class,this);
	return Items[Count-1];
}
//---------------------------------------------------------------------------
bool __fastcall TCustomList::IsClassAllowed(TClass Class)
{
	TClassList *classes = AllowedClasses();
	if(classes->Count == 0)
		return false;
	while(Class != NULL)
	{
		if(classes->IndexOf(Class) == -1)
		{
			Class = Class->ClassParent();
		}
		else
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::DoAddItem(TCustomListItem* Item)
{
	if(IsClassAllowed(Item->ClassType()))
	{
		AddItem(Item);
	}
	else
	{
		delete Item;
		throw EClassNotAllowed(Item->ClassName());
	}
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::DefineProperties(TFiler* Filer)
{
	TPersistent::DefineProperties(Filer);
	bool DoWrite = true ? Filer->Ancestor == NULL : !Equals(Filer->Ancestor);
	Filer->DefineProperty("ItemClasses", ReadClassNames, WriteClassNames, DoWrite);
	Filer->DefineProperty("Items", ReadItems, WriteItems, DoWrite);
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::ReadClassNames(TReader* Reader)
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
void __fastcall TCustomList::WriteClassNames(TWriter* Writer)
{
	Writer->WriteListBegin();
	for(int i=0;i<Count;i++)
	{
		Writer->WriteString(Items[i]->ClassName());
	}
	Writer->WriteListEnd();
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::ReadItems(TReader *Reader)
{
	ReadObjListBegin(Reader);
	for(int i=0;!Reader->EndOfList();i++)
	{
		ReadObjListItem(Reader, Items[i]);
	}
	ReadObjListEnd(Reader);
}
//---------------------------------------------------------------------------
void __fastcall TCustomList::WriteItems(TWriter *Writer)
{
	WriteObjListBegin(Writer);
	for(int i=0;i<Count;i++)
	{
		WriteObjListItem(Writer, Items[i]);
	}
	WriteObjListEnd(Writer);
}
//---------------------------------------------------------------------------
String __fastcall TCustomList::GetNamePath(void)
{
	return AOwner->GetNamePath() + "." + ClassName();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TVectorList::TVectorList(TPersistent *Owner)
	: TCustomList(Owner)
{
}
//---------------------------------------------------------------------------
TCustomListItem* __fastcall TVectorList::GetItem(int Index)
{
	return list[Index];
}
//---------------------------------------------------------------------------
void __fastcall TVectorList::AddItem(TCustomListItem* Item)
{
	list.Add(Item);
}
//---------------------------------------------------------------------------
void __fastcall TVectorList::DeleteItem(TCustomListItem* Item)
{
	list.Delete(Item->Index);
}
//---------------------------------------------------------------------------
int __fastcall TVectorList::GetCount(void)
{
	return list.Count();
}
//---------------------------------------------------------------------------
void __fastcall TVectorList::ItemUp(int Index)
{
	ItemDown(Index+1);
}
//---------------------------------------------------------------------------
void __fastcall TVectorList::ItemDown(int Index)
{
	if(Index > 0 && Index < Count)
	{
		TCustomListItem *temp = list[Index-1];
		list[Index-1] = list[Index];
		list[Index] = temp;
    }
}
//---------------------------------------------------------------------------

