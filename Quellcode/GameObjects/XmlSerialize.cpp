//---------------------------------------------------------------------------
#pragma hdrstop
#include "XmlSerialize.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool __fastcall IsXMLNodeInList(_di_IXMLNode Node, _di_IXMLNodeList NodeList)
{
	for(int i=0;i<NodeList->Count;i++)
	{
		_di_IXMLNode ChildNode = NodeList->Get(i);
		if(XMLNodesEqual(Node, ChildNode))
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall XMLNodeCollectionsEqual(_di_IXMLNodeList NodeList1, _di_IXMLNodeList NodeList2)
{
	if(NodeList1->Count != NodeList2->Count)
		return false;
	for(int i=0;i<NodeList1->Count;i++)
	{
		_di_IXMLNode ChildNode = NodeList1->Get(i);
		if(!IsXMLNodeInList(ChildNode, NodeList2))
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall XMLNodesEqual(_di_IXMLNode Node1, _di_IXMLNode Node2)
{
	return Node1->NodeName == Node2->NodeName && XMLNodeValuesEqual(Node1,Node2) && Node1->Prefix == Node2->Prefix && XMLNodeCollectionsEqual(Node1->AttributeNodes,Node2->AttributeNodes) && XMLNodeCollectionsEqual(Node1->ChildNodes,Node2->ChildNodes);
}
//---------------------------------------------------------------------------
bool __fastcall XMLNodeValuesEqual(_di_IXMLNode Node1, _di_IXMLNode Node2)
{
	if(Node1->NodeType != Node2->NodeType)
		return false;
	if(Node1->NodeType == ntElement)
	{
		if(Node1->IsTextElement != Node2->IsTextElement)
			return false;
		else if(!Node1->IsTextElement)
			return true;
		else
			return Node1->NodeValue == Node2->NodeValue;
	}
	else
	{
        return Node1->NodeValue == Node2->NodeValue;
    }
}
//---------------------------------------------------------------------------
