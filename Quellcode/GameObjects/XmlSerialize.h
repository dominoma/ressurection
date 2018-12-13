//---------------------------------------------------------------------------

#ifndef XmlSerializeH
#define XmlSerializeH
#include "..\Stuff.h"
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
__interface IXmlSerializable
{
	virtual _di_IXMLNode __fastcall ToXmlNode(void)=0; //Gibt einen XML-Knoten mit den zu speichernden Eigenschaften des Objektes zurück
	virtual	void __fastcall FromXmlNode(_di_IXMLNode Node)=0; //Liest Eigenschaften des Objektes aus dem übergebenen XML-Knoten
};
TComponent* __fastcall GetHighestOwner(TPersistent *Persistent);
bool __fastcall XMLNodesEqual(_di_IXMLNode Node1, _di_IXMLNode Node2);
bool __fastcall XMLNodeCollectionsEqual(_di_IXMLNodeList NodeList1, _di_IXMLNodeList NodeList2);
bool __fastcall XMLNodeValuesEqual(_di_IXMLNode Node1, _di_IXMLNode Node2);
//---------------------------------------------------------------------------
#endif
