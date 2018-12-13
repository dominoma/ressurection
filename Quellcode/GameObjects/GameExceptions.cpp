//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameExceptions.h"
#include "GameObjects.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall EFlowItemError::EFlowItemError(TGameFlowCustomItem *Item, String Msg)
	: Exception("Error at '"+Item->ClassName()+"' in flowlist of '"+Item->FlowList->GameObject->Name+"'! \n"+Msg), FItem(Item), FMsg(Msg)
{
}
//---------------------------------------------------------------------------
__fastcall EFlowListError::EFlowListError(TGameFlowList* List, String Msg)
	: Exception("Error at flowlist of '"+List->GameObject->Name+"'! \n"+Msg), FList(List), FMsg(Msg)
{
}
//---------------------------------------------------------------------------
