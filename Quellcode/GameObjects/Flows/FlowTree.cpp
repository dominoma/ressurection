//---------------------------------------------------------------------------
#include "GameObjects.h"
#include "SerializeTools.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TFlowTreeItem::TFlowTreeItem(TBasicCustomList *Owner)
	: TVectorTreeItem(Owner), FHidden(false), FHideItem(false)
{
	flowList = new TConvGUIFlowList((TGameObject*)((TCustomTree*)Owner)->Owner);
}
//---------------------------------------------------------------------------
TGameXmlNode __fastcall TFlowTreeItem::ToXmlNode(void)
{
	TGameXmlNode Node = CreateNode(ClassName());
	Node->Attributes["Hidden"] = Hidden;
	for(int i=0;i<Count;i++)
	{
		Node->ChildNodes->Add(((TFlowTreeItem*)Items[i])->ToXmlNode());
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TFlowTreeItem::FromXmlNode(TGameXmlNode Node)
{
	if(Node->NodeName != ClassName())
	{
		throw EArgumentException("Xml Node with name '"+Node->NodeName+"' doesn't fit to object with class name '"+ClassName()+"'!");
	}
	Hidden = Node->Attributes["Hidden"];
	for(int i=0;i<Count&&i<Node->ChildNodes->Count;i++)
	{
		((TFlowTreeItem*)Items[i])->FromXmlNode(Node->ChildNodes->Get(i));
    }
}
//---------------------------------------------------------------------------
String __fastcall TFlowTreeItem::DisplayName(void)
{
	return Text;
}
//---------------------------------------------------------------------------
__fastcall TFlowTreeList::TFlowTreeList(TGameObject *Owner)
	: TVectorTree(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFlowTreeList::SetAllowedClasses(TClassList *ClassList)
{
	ClassList->Add(__classid(TFlowTreeItem));
}
//---------------------------------------------------------------------------
TGameXmlNode __fastcall TFlowTreeList::ToXmlNode(void)
{
	TGameXmlNode Node = CreateNode(ClassName());
	for(int i=0;i<Root->Count;i++)
	{
		Node->ChildNodes->Add(((TFlowTreeItem*)Root->Items[i])->ToXmlNode());
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TFlowTreeList::FromXmlNode(TGameXmlNode Node)
{
	if(Node->NodeName != ClassName())
	{
		throw EArgumentException("Xml Node with name '"+Node->NodeName+"' doesn't fit to object with class name '"+ClassName()+"'!");
	}
	for(int i=0;i<Root->Count&&i<Node->ChildNodes->Count;i++)
	{
		((TFlowTreeItem*)Root->Items[i])->FromXmlNode(Node->ChildNodes->Get(i));
	}
}
//---------------------------------------------------------------------------
