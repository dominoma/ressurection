//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//
//---------------------------------------------------------------------------
__fastcall TVariadicFlowList::TVariadicFlowList(TGameObject* Owner)
	: TGameFlowList(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TEventFlowList::TEventFlowList(TGameObject* Owner)
	: TGameFlowList(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TEventFlowList::IsClassAllowed(TClass Class)
{
	for(TClass PrntClass=Class;PrntClass->ClassName().Pos("TEventFlowItem")==0;PrntClass=PrntClass->ClassParent())
	{
		if(PrntClass->ClassParent() == NULL)
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
