//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
#include "SerializeTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TItemDropEvent::TItemDropEvent(TCollection *Owner)
	: TCollectionItem(Owner), flowList(new TVariadicFlowList((TGameObject*)Owner->Owner()))
{
	TNotifyEvent event = &FlowListStarted;
	flowList->OnStartedList.AddEventListener(event);
}
//---------------------------------------------------------------------------
__fastcall TItemDropEvent::~TItemDropEvent(void)
{
	delete flowList;
}
//---------------------------------------------------------------------------
void __fastcall TItemDropEvent::FlowListStarted(TObject *Sender)
{
	if(FDeleteItem)
	{
		((TInventoryGUI*)TInventoryGUI::Instance())->DeleteItem(((TInventoryGUI*)TInventoryGUI::Instance())->SelectedItem());
    }
}
//---------------------------------------------------------------------------
void __fastcall TItemDropEvent::SetHotspotState(String State)
{
	THotspot *Hotspot = (THotspot*)Collection->Owner();
	if(!Hotspot->States->ItemExists(State))
		throw EArgumentException("State '"+State+"' doesn't exist in state list of '"+Hotspot->Name+"'!");
	FHotspotState = State;
}
//---------------------------------------------------------------------------
__fastcall TItemDropEvents::TItemDropEvents(THotspot *Owner)
	: TOwnedCollection(Owner, __classid(TItemDropEvent))
{
}
//---------------------------------------------------------------------------
void __fastcall TItemDropEvents::StatesUpdate(void)
{
	for(int i=0;i<Count;i++)
	{
		TItemDropEvent *CurrItem = (TItemDropEvent*)Items[i];
		THotspot *AOwner = (THotspot*)Owner();
		if(!AOwner->States->ItemExists(CurrItem->HotspotState))
		{
            CurrItem->HotspotState = "";
        }
    }
}
//---------------------------------------------------------------------------
IGameRunnable* __fastcall TItemDropEvents::GetFlow(void)
{
	return GetFlow(((TInventoryGUI*)TInventoryGUI::Instance())->SelectedItem()->ItemName,((THotspot*)Owner())->State);
}
//---------------------------------------------------------------------------
IGameRunnable* __fastcall TItemDropEvents::GetFlow(String ItemName, String HotspotState)
{
	for(int i=0;i<Count;i++)
	{
		TItemDropEvent *CurrItem = (TItemDropEvent*)Items[i];
		if(CurrItem->ItemName == ItemName && CurrItem->HotspotState == HotspotState)
			return CurrItem->FlowList;
	}
	throw EArgumentException("Nothing found");
}
//---------------------------------------------------------------------------
bool __fastcall TItemDropEvents::IsFlow(void)
{
	return IsFlow(((TInventoryGUI*)TInventoryGUI::Instance())->SelectedItem()->ItemName,((THotspot*)Owner())->State);
}
//---------------------------------------------------------------------------
bool __fastcall TItemDropEvents::IsFlow(String ItemName, String HotspotState)
{
	for(int i=0;i<Count;i++)
	{
		TItemDropEvent *CurrItem = (TItemDropEvent*)Items[i];
		if(CurrItem->ItemName == ItemName && CurrItem->HotspotState == HotspotState)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
__fastcall THotspotStateList::THotspotStateList(THotspot *Owner)
	: Inherited(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THotspotStateList::SetSelected(String NewName)
{
	if(IsFixedup && GameObject->IsOwnerRunning())
	{
		if(ItemExists(Selected))
			Items[Selected]->FlowList->Stop();
		if(ItemExists(NewName))
			Items[NewName]->FlowList->Start();
	}
	Inherited::SetSelected(NewName);
}
//---------------------------------------------------------------------------
void __fastcall THotspotStateList::DoStart(void)
{
	if(ItemExists(Selected))
		Items[Selected]->FlowList->Start();
}
//---------------------------------------------------------------------------
__fastcall THotspot::THotspot(TComponent *Owner)
	: TForegroundObj(Owner), FHintImage(new TImage(this)),
		FInspectFlows(new TFlowListGameList(this)), FActionFlows(new TFlowListGameList(this)),
		stateList(new THotspotStateList(this)), FItemDropEvents(new TItemDropEvents(this)),
		onInspect(NULL), onAction(NULL), onItemDrop(NULL)
{
	Cursor = crHourGlass;
	HitTest = true;

	FHintImage->Parent = this;
	FHintImage->HitTest = false;
	FHintImage->Stored = false;
	FHintImage->Width = 32;
	FHintImage->Height = 32;
	FHintImage->Align = TAlignLayout::Center;
	FHintImage->WrapMode = TImageWrapMode::Stretch;
	FHintImage->Visible = false;
}
//---------------------------------------------------------------------------
__fastcall THotspot::~THotspot(void)
{
	delete stateList;
	delete FItemDropEvents;
	delete FInspectFlows;
	delete FActionFlows;
	delete FHintImage;
}
//---------------------------------------------------------------------------
void __fastcall THotspot::ShowHint(TBitmap *HintImg)
{
	FHintImage->Bitmap = HintImg;
	FHintImage->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall THotspot::HideHint(void)
{
	FHintImage->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall THotspot::Loaded(void)
{
	TForegroundObj::Loaded();
	if(FInspectFlows->Count == 0 && FActionFlows->Count > 0)
		Cursor = TGameCursor::Action;
	else if(FInspectFlows->Count > 0 && FActionFlows->Count == 0)
		Cursor = TGameCursor::Inspect;
	else if(FInspectFlows->Count > 0 && FActionFlows->Count > 0)
		Cursor = TGameCursor::ActionInspect;
	stateList->Fixup();
}
//---------------------------------------------------------------------------
String __fastcall THotspot::GetState(void)
{
	return States->Selected;
}
//---------------------------------------------------------------------------
void __fastcall THotspot::SetState(String value)
{
	if(TGameManager::IsCreated())
	TGameManager::Manager()->LogFile.Log("Object '"+Name+"' State changed to '"+value+"'");
	States->Selected = value;
}
//---------------------------------------------------------------------------
void __fastcall THotspot::DoStart(void)
{
	stateList->Start();
	TForegroundObj::DoStart();
}
//---------------------------------------------------------------------------
void __fastcall THotspot::DoStop(void)
{
	if(stateList->Selected != "")
	{
		stateList->Items[stateList->Selected]->FlowList->Stop();
	}
}
//---------------------------------------------------------------------------
TGameFlowList* __fastcall THotspot::GetStateSelActnFlow(void)
{
	if(FActionFlows->ItemExists(State))
		return FActionFlows->Items[State]->FlowList;
	else if(FActionFlows->ItemExists("#ALLSTATES#"))
		return FActionFlows->Items["#ALLSTATES#"]->FlowList;
	else
		return NULL;
}
//---------------------------------------------------------------------------
TGameFlowList* __fastcall THotspot::GetStateSelInspctFlow(void)
{
	if(FInspectFlows->ItemExists(State))
		return FInspectFlows->Items[State]->FlowList;
	else if(FInspectFlows->ItemExists("#ALLSTATES#"))
		return FInspectFlows->Items["#ALLSTATES#"]->FlowList;
	else
		return NULL;
}
//---------------------------------------------------------------------------
void __fastcall THotspot::RunEventState(void)
{
	if(FEventState == THotspotEventState::Acting)
	{
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log("Object '"+Name+"' start action...");
		if(FActionFlows->Count > 0)
		{
			TGameFlowList *FlowList = StateSelActnFlow;
			if(FlowList != NULL)
				FlowList->Start();
		}
		Action();
		if(onAction != NULL)
			onAction(this);
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log("Object '"+Name+"' action finished");
	}
	else if(FEventState == THotspotEventState::ItemDropping)
	{
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log("Object '"+Name+"' start item drop...");
		FItemDropEvents->GetFlow()->Start();
		ItemDrop();
		if(onItemDrop != NULL)
			onItemDrop(this);
		((TInventoryGUI*)TInventoryGUI::Instance())->SelectItem(NULL);
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log("Object '"+Name+"' item drop finished");
	}
	else if(FEventState == THotspotEventState::Inspecting)
	{
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log("Object '"+Name+"' start inspecting...");
		if(FInspectFlows->Count > 0)
		{
			TGameFlowList *FlowList = StateSelInspctFlow;
			if(FlowList != NULL)
				FlowList->Start();
		}
		Inspect();
		if(onInspect != NULL)
			onInspect(this);
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log("Object '"+Name+"' inspecting finished.");
    }

}
//---------------------------------------------------------------------------
void __fastcall THotspot::MouseUp(TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
	TForegroundObj::MouseUp(Button, Shift, X, Y);
	if(Button == TMouseButton::mbLeft)
	{
		if(((TInventoryGUI*)TInventoryGUI::Instance())->IsItemSelected() && FItemDropEvents->IsFlow())
		{
			FEventState = THotspotEventState::ItemDropping;
		}
		else
		{
			FEventState = THotspotEventState::Acting;
			((TInventoryGUI*)TInventoryGUI::Instance())->SelectItem(NULL);
		}
	}
	else if(Button == TMouseButton::mbRight)
	{
		FEventState = THotspotEventState::Inspecting;
	}
	if(TGameManager::IsCreated() && TGameManager::Manager()->OpenedFrame->IsPlayer())
	{
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log("Player starts moving to Object '"+Name+"'");
		TGameManager::Manager()->OpenedFrame->Player()->MoveToHotspot(this);
	}
	else
	{
		RunEventState();
    }
}
//---------------------------------------------------------------------------
TGameXmlNode __fastcall THotspot::ToXmlNode(void)
{
	TGameXmlNode Node = TForegroundObj::ToXmlNode();
	Node->Attributes["State"] = State;
    return Node;
}
//---------------------------------------------------------------------------
void __fastcall THotspot::FromXmlNode(TGameXmlNode Node)
{
	TForegroundObj::FromXmlNode(Node);
    State = Node->Attributes["State"];
}
//---------------------------------------------------------------------------
namespace Hotspot
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(THotspot)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
