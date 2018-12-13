//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TPerson *)
{
	new TPerson(NULL);
}
//---------------------------------------------------------------------------
__fastcall TPerson::TPerson(TComponent* Owner)
	: THotspot(Owner), FConvTree(new TFlowTreeList(this))
{
}
//---------------------------------------------------------------------------
__fastcall TPerson::~TPerson(void)
{
	delete FConvTree;
}
//---------------------------------------------------------------------------
void __fastcall TPerson::Loaded(void)
{
	THotspot::Loaded();
	Cursor = TGameCursor::TalkInspect;
}
//---------------------------------------------------------------------------
void __fastcall TPerson::SetConvTree(TFlowTreeList *NewConv)
{
	FConvTree->Assign(NewConv);
}
//---------------------------------------------------------------------------
void __fastcall TPerson::Action(void)
{

}
//---------------------------------------------------------------------------
String __fastcall TPerson::GetResourcePath(void)
{
	return ResourceRoot()+"\\Persons\\"+Name;
}
//---------------------------------------------------------------------------
TGameXmlNode __fastcall TPerson::ToXmlNode(void)
{
	TGameXmlNode Node = THotspot::ToXmlNode();
	Node->ChildNodes->Add(ConvTree->ToXmlNode());
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TPerson::FromXmlNode(TGameXmlNode Node)
{
	THotspot::FromXmlNode(Node);
	TGameXmlNode ConvNode = Node->ChildNodes->FindNode(ConvTree->ClassName());
	if(ConvNode != NULL)
		ConvTree->FromXmlNode(ConvNode);
}
//---------------------------------------------------------------------------
namespace Person
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TPerson)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
