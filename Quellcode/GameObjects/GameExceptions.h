//---------------------------------------------------------------------------

#ifndef GameExceptionsH
#define GameExceptionsH
#include <System.Classes.hpp>
#include "XmlSerialize.h"
//---------------------------------------------------------------------------
class EIllegalState : public Exception
{
public:
	__fastcall EIllegalState(String Msg) : Exception(Msg){};
};
class ECustomListError : public Exception
{
public:
	__fastcall ECustomListError(String Msg) : Exception(Msg){};
};
class EClassNotAllowed : public ECustomListError
{
public:
	__fastcall EClassNotAllowed(String ClassName) : ECustomListError("Elements o type '"+ClassName+"' are not allowed in the list!"){};
};
class ENotInParentList : public ECustomListError
{
public:
	__fastcall ENotInParentList(void) : ECustomListError("This item isn't in the list of its parent!"){};
};
class EOutOfBounds : public ECustomListError
{
public:
	__fastcall EOutOfBounds(int Min, int Max, int Pos) : ECustomListError("Index '"+String(Pos)+"' is out of bounds ["+String(Min)+"-"+String(Max)+"]!"){};
};
class TGameFlowCustomItem;
class EFlowItemError : public Exception //Exception für FlowItems, durch Übergabe des betroffenen Items genaue Bestimmung und detailierter Fehlerbericht möglich
{
private:
	String FMsg;
	TGameFlowCustomItem *FItem;
public:
	__fastcall EFlowItemError(TGameFlowCustomItem *Item, String Msg);
	__property String Message = {read=FMsg};
	__property TGameFlowCustomItem* Item = {read=FItem};
};
class TGameFlowList;
class EFlowListError : public Exception
{
private:
	String FMsg;
	TGameFlowList *FList;
public:
	__fastcall EFlowListError(TGameFlowList* List, String Msg);
	__property String Message = {read=FMsg};
	__property TGameFlowList* List = {read=FList};
};
class EXmlSerializeError : public Exception
{
private:
	TObject *FObject;
	_di_IXMLNode FNode;
public:
	__fastcall EXmlSerializeError(TObject *Object, _di_IXMLNode Node, String Msg)
		: FObject(Object), FNode(Node), Exception(Msg) {};
	__property TObject *Object = {read=FObject};
	__property _di_IXMLNode Node = {read=FNode};
};
class EXmlNodeNameError : public EXmlSerializeError
{
public:
	__fastcall EXmlNodeNameError(TObject *Object, _di_IXMLNode Node)
		: EXmlSerializeError(Object,Node,"Xml Node with name '"+Node->NodeName+"' doesn't fit to object with class name '"+Object->ClassName()+"'!") {};
	__fastcall EXmlNodeNameError(TComponent *Component, _di_IXMLNode Node)
		: EXmlSerializeError(Object,Node,"Xml Node with name '"+Node->NodeName+"' doesn't fit to object with name '"+Component->Name+"'!") {};
};
#endif
