//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TCustomFlowItem::TCustomFlowItem(TBasicCustomList* List)
	: TGameFlowItem(List), FlowList(new TGameFlowList((TGameObject*)((TCustomList*)List)->Owner))
{
	FlowList->OnStopped = FlowListStopped;
}
//---------------------------------------------------------------------------
__fastcall TCustomFlowItem::~TCustomFlowItem(void)
{
	delete FlowList;
}
//---------------------------------------------------------------------------
void __fastcall TCustomFlowItem::DoStart(void)
{
	FlowList->Clear();
	FlowList->Repeat = Repeat;
	try
	{
		AddFlowItems(FlowList->Add);
		FlowList->Start();
	}
	catch(EFlowItemError &e) //Subklasse oder Subitem hat Exception geworfen
	{
		if(e.Item == this) //Subklasse hat geworfen, Exception weitergeben
			throw e;
		else  			  //Subitem hat geworfen, Message anpassen, Exception dann weitergeben
			throw EFlowItemError(this,"SubItem '"+e.Item->ClassName()+"' threw error '"+e.Message+"'!");
	}
	catch(Exception &e) //Funktion in Subitem hat Exception geworfen, Exception anpassen und weitergeben
	{
		throw EFlowItemError(this,e.Message);
	}
	catch(...) //unbekannte Exception, Exception anpassen und weitergeben
	{
		throw EFlowItemError(this,"Unknown error!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TCustomFlowItem::Jump(void)
{
	if(FlowList->IsRunning())
	{
        FlowList->CurrItem->Stop();
    }
}
//---------------------------------------------------------------------------
void __fastcall TCustomFlowItem::DoStop(void)
{
	FlowList->Stop();
}
//---------------------------------------------------------------------------
void __fastcall TCustomFlowItem::DoPause(void)
{
	FlowList->Pause();
}
//---------------------------------------------------------------------------
bool __fastcall TCustomFlowItem::IsRunning(void)
{
	return FlowList->IsRunning();
}
//---------------------------------------------------------------------------
bool __fastcall TCustomFlowItem::IsPaused(void)
{
	return FlowList->IsPaused();
}
//---------------------------------------------------------------------------
void __fastcall TCustomFlowItem::FlowListStopped(TObject *Sender)
{
	Stop();
}
//---------------------------------------------------------------------------

