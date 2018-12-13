//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TGameFlowCustomItem::TGameFlowCustomItem(TBasicCustomList* List)
	: TCustomListItem(List), isBlocking(true), repeat(false), lockScreen(false)
{
}
//---------------------------------------------------------------------------
__fastcall TGameFlowCustomItem::~TGameFlowCustomItem(void)
{
	Stop();
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowCustomItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TGameFlowCustomItem)))
	{
		TGameFlowCustomItem *Item = (TGameFlowCustomItem*)Source;
		FOnStartedList = Item->FOnStartedList;
		FOnStoppedList = Item->FOnStoppedList;
		FOnPausedList = Item->FOnPausedList;
		FOnFinishedList = Item->FOnFinishedList;

		isBlocking = Item->isBlocking;
		repeat = Item->repeat;
	}
	else
		TCustomListItem::Assign(Source);
}
//---------------------------------------------------------------------------
TGameFlowList* __fastcall TGameFlowCustomItem::GetFlowList(void)
{
	return (TGameFlowList*)ParentList;
}
//---------------------------------------------------------------------------
bool __fastcall TGameFlowCustomItem::HasFocus(void)
{
	return FlowList->CurrItem == this;
}
//---------------------------------------------------------------------------
bool __fastcall TGameFlowCustomItem::CanLooseFocus(void)
{
	return HasFocus() && FlowList->IsRunning() && (!IsBlocking || !IsRunning());
}
//---------------------------------------------------------------------------
TGameFlowCustomItem* __fastcall TGameFlowCustomItem::GetNextItem(void)
{
	if(Index == FlowList->Count-1)
		return NULL;
	else
		return FlowList->Items[Index+1];
}
//---------------------------------------------------------------------------
TGameFlowCustomItem* __fastcall TGameFlowCustomItem::GetLastItem(void)
{
	if(Index-1 < 0)
		return NULL;
	else
		return FlowList->Items[Index-1];
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowCustomItem::Start(void)
{
	if(LastItem == NULL || LastItem->CanLooseFocus())
	{
		FlowList->currItemIndex = Index;
		try
		{
			if(lockScreen && TGameManager::IsCreated() && TGameManager::Manager()->OpenedFrame != NULL)
				TGameManager::Manager()->OpenedFrame->LockScreen(this);
			DoStart();
			OnStartedList.CallEvents(this);
			Started();
		}
		catch(Exception &e) //Bei Exception FlowList stoppen und Exception weitergeben
		{
			if(lockScreen && TGameManager::IsCreated() && TGameManager::Manager()->OpenedFrame != NULL)
				TGameManager::Manager()->OpenedFrame->UnlockScreen();
			FlowList->Stop();
			throw e;
		}
		if(!IsBlocking && NextItem != NULL)
			NextItem->Start();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowCustomItem::Stop(void)
{
	if(lockScreen && TGameManager::IsCreated() && TGameManager::Manager()->OpenedFrame != NULL)
		TGameManager::Manager()->OpenedFrame->UnlockScreen();
	if(IsRunning() || IsPaused())
	{
		DoStop();
		OnStoppedList.CallEvents(this);
		Stopped();
	}
	if(CanLooseFocus())
	{
		if(NextItem == NULL)
			FlowList->Finish();
		else
			NextItem->Start();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowCustomItem::Pause(void)
{
	DoPause();
	OnPausedList.CallEvents(this);
	Paused();
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowCustomItem::Finish(void)
{
	OnFinishedList.CallEvents(this);
	Finished();
	if(repeat)
	{
		DoStop();
		try
		{
			DoStart();
		}
		catch(Exception &e) //Bei Exception FlowList stoppen und Exception weitergeben
		{
			if(lockScreen && TGameManager::IsCreated() && TGameManager::Manager()->OpenedFrame != NULL)
				TGameManager::Manager()->OpenedFrame->UnlockScreen();
			FlowList->Stop();
			throw e;
		}
	}
	else
	{
        Stop();
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TGameFlowList::TGameFlowList(TGameObject *Owner)
	: TVectorList(Owner), currItemIndex(-1), isRunning(false), repeat(false)
{
	if(Owner != NULL)
	{
		if(!Owner->InheritsFrom(__classid(TGameObject)))
			throw EArgumentException("Owner isn't inherited from TGameObject!");
		Owner->AddFlowToList(this);
	}
}
//---------------------------------------------------------------------------
__fastcall TGameFlowList::~TGameFlowList(void)
{
	if(Owner != NULL)
		((TGameObject*)Owner)->DeleteFlowFromList(this);
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::BeforeDestruction(void)
{
	Stop();
	TVectorList::BeforeDestruction();
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TGameFlowList)))
	{
		TGameFlowList *Item = (TGameFlowList*)Source;
		FOnStartedList = Item->FOnStartedList;
		FOnStoppedList = Item->FOnStoppedList;
		FOnPausedList = Item->FOnPausedList;
		FOnFinishedList = Item->FOnFinishedList;

		repeat = Item->repeat;
	}
	TVectorList::Assign(Source);
}
//---------------------------------------------------------------------------
TClass __fastcall TGameFlowList::MinimumClass(void)
{
	return __classid(TGameFlowCustomItem);
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::AddAllClasses(TClassList *ClassList)
{
	ClassList->Add(__classid(TCustomEventFlowItem));
	ClassList->Add(__classid(TAudioFlowItem));
	ClassList->Add(__classid(TAnimationFlowItem));
	ClassList->Add(__classid(TSleepFlowItem));
	ClassList->Add(__classid(TStopFlowItem));
	ClassList->Add(__classid(TGiveItemFlowItem));
	ClassList->Add(__classid(TLoadLocationFlowItem));
	ClassList->Add(__classid(TConversationFlowItem));
	ClassList->Add(__classid(TChangeStateFlowItem));
	ClassList->Add(__classid(TChangeAnimationFlowItem));
	ClassList->Add(__classid(TChangeLocalStateFlowItem));
	ClassList->Add(__classid(TLoadPicFlowItem));
	ClassList->Add(__classid(TOpenConvFlowItem));
	ClassList->Add(__classid(TMoveObjFlowItem));
	ClassList->Add(__classid(TMoveFlowItem));
	ClassList->Add(__classid(TChangePropertyFlowItem));
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::SetAllowedClasses(TClassList *ClassList)
{
	AddAllClasses(ClassList);

	TClass MinClass = MinimumClass();
	if(MinClass != NULL)
	{
		for(int i=0;i<ClassList->Count;i++)
		{
			if(!IsClassAllowed(ClassList->Items[i]))
			{
				ClassList->Delete(i);
				i--;
            }
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::Finish(void)
{
	OnFinishedList.CallEvents(this);
	Finished();
	if(GameObject != NULL)
		GameObject->FlowListFinished(this);
	if(Repeat)
	{
		Stop();
		Start();
	}
	else
	{
        Stop();
    }
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::StopAll(void)
{
	for(int i=0;i<Count;i++)
	{
		if(Items[i]->IsRunning())
			Items[i]->Stop();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::PauseAll(void)
{
	for(int i=0;i<Count;i++)
	{
        Items[i]->Pause();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::Start(void)
{
	try
	{
		if(!IsRunning() && GameObject->IsOwnerRunning())
		{
			isRunning = true;
			if(IsPaused())
			{
				for(int i=0;i<Count;i++)
				{
					if(GetItem(i)->IsPaused())
					{
						GetItem(i)->Start();
					}
				}
				OnStartedList.CallEvents(this);
				Started();
				if(GameObject != NULL)
					GameObject->FlowListStarted(this);
			}
			else if(Count > 0)
			{
				GetItem(0)->Start();
				OnStartedList.CallEvents(this);
				Started();
				if(GameObject != NULL)
					GameObject->FlowListStarted(this);
			}
			else
			{
				Stop();
			}
		}
	}
	catch(EFlowItemError &e) //Bei FlowItemError Exception weitergeben
	{
		throw e;
	}
	catch(Exception &e) //Bei normaler Exception die Exception anpassen, Message übernehmen
	{
		throw EFlowListError(this,e.Message);
	}
	catch(...) //Bei unbekannter Exception die Exception anpassen
	{
		throw EFlowListError(this,"Unknown error!");
    }
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::Stop(void)
{
	if(IsRunning() || IsPaused())
	{
		isRunning = false;
		StopAll();
		currItemIndex = -1;
		OnStoppedList.CallEvents(this);
		Stopped();
		if(GameObject != NULL)
			GameObject->FlowListStopped(this);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::Pause(void)
{
	isRunning = false;
	PauseAll();
	OnPausedList.CallEvents(this);
	Paused();
	if(GameObject != NULL)
		GameObject->FlowListPaused(this);
}
//---------------------------------------------------------------------------
bool __fastcall TGameFlowList::IsItemRunning(void)
{
	for(int i=0;i<Count;i++)
	{
		if(Items[i]->IsRunning())
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall TGameFlowList::IsRunning(void)
{
	return isRunning;
}
//---------------------------------------------------------------------------
bool __fastcall TGameFlowList::IsPaused(void)
{
	return !IsRunning() && currItemIndex >= 0 && CurrItem->IsPaused();
}
//---------------------------------------------------------------------------
TGameFlowCustomItem* __fastcall TGameFlowList::GetCurrItem(void)
{
	if(currItemIndex < 0 || currItemIndex >= Count)
		return NULL;
	else
		return Items[currItemIndex];
}
//---------------------------------------------------------------------------
TGameFlowCustomItem* __fastcall TGameFlowList::GetItem(int Index)
{
	return (TGameFlowCustomItem*)TVectorList::GetItem(Index);
}
//---------------------------------------------------------------------------
void __fastcall TGameFlowList::SetItem(int Index, TGameFlowCustomItem *obj)
{
	TVectorList::SetItem(Index, obj);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TFlowListNameItem::TFlowListNameItem(TCollection *Owner, TGameFlowList *FlowList)
	: TCollectionItem(Owner), FFlowList(FlowList)
{
}
//---------------------------------------------------------------------------
__fastcall TFlowListNameItem::~TFlowListNameItem(void)
{
	delete FFlowList;
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TFlowListNameItem)))
	{
		TFlowListNameItem *Item = (TFlowListNameItem*)Source;
		FName = Item->FName;
		FFlowList->Assign(Item->FFlowList);
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFlowListNameItem::Equals(TObject* Obj)
{
	if(Obj != NULL && Obj->InheritsFrom(__classid(TFlowListNameItem)))
	{
		TFlowListNameItem *Item = (TFlowListNameItem*)Obj;
		return FName == Item->FName && FFlowList->Equals(Item->FFlowList);
	}
	else
		return false;
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameItem::SetFlowList(TGameFlowList *NewFlow)
{
	FFlowList->Assign(NewFlow);
}
//---------------------------------------------------------------------------
TFlowListNameCollection* __fastcall TFlowListNameItem::GetCollection(void)
{
	return (TFlowListNameCollection*)TCollectionItem::Collection;
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameItem::SetName(String NewName)
{
	if(Collection->ItemExists(NewName))
		throw EArgumentException("Item with Name '"+NewName+"' is already in the list!");
	FName = NewName;
}
//---------------------------------------------------------------------------
String __fastcall TFlowListNameItem::GetDisplayName(void)
{
	return FName;
}
//---------------------------------------------------------------------------
TGameObject* __fastcall TFlowListNameItem::GetGameObject(void)
{
	return Collection->GameObject;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TFlowListNameSelItem::TFlowListNameSelItem(TCollection *Owner, TGameFlowList *FlowList)
	: TFlowListNameItem(Owner,FlowList)
{
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameSelItem::SetName(String NewName)
{
	TFlowListNameItem::SetName(NewName);
	if(Collection->IsFixedup && !Collection->ItemExists(((TFlowListNameSelCollection*)Collection)->Selected))
		((TFlowListNameSelCollection*)Collection)->Selected = "";
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TFlowListNameCollection::TFlowListNameCollection(TGameObject *Owner, TClass ItemClass)
	: TOwnedCollection(Owner, ItemClass), FIsFixedUp(false)
{
	if(!ItemClass->InheritsFrom(__classid(TFlowListNameItem)))
		throw EArgumentException("Parmeter 'ItemClass' must be inherited from 'TFlowListNameItem'!");
}
//---------------------------------------------------------------------------
TFlowListNameItem* __fastcall TFlowListNameCollection::GetItem(String IndexOrName)
{
	TFlowListNameItem *Item = SearchItem(IndexOrName);
	if(Item == NULL)
		throw EArgumentException("Item with name '"+IndexOrName+"' doesn't exist");
	return Item;
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameCollection::SetItem(String IndexOrName, TFlowListNameItem *NewItem)
{
	TFlowListNameItem *Item = SearchItem(IndexOrName);
	if(Item == NULL)
		throw EArgumentException("Item with name '"+IndexOrName+"' doesn't exist");
	Item->Assign(NewItem);
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameCollection::Added(TCollectionItem* &Item)
{
	/*if(!Item->InheritsFrom(__classid(TFlowListNameItem)))
		throw EArgumentException("Item must be inherited from 'TFlowListNameItem'!");
	TFlowListNameItem *LItem = (TFlowListNameItem*)Item;

	int i;
	for(i=0;ItemExists("Item"+String(i));i++);
	LItem->Name = "Item"+String(i); */
}
//---------------------------------------------------------------------------
bool __fastcall TFlowListNameCollection::ItemExists(String Name)
{
	return SearchItem(Name) != NULL;
}
//---------------------------------------------------------------------------
TFlowListNameItem* __fastcall TFlowListNameCollection::SearchItem(String IndexOrName)
{
	try
	{
		int Index = IndexOrName.ToInt();
		return (TFlowListNameItem*)TOwnedCollection::Items[Index];
	}
	catch(EConvertError &e)
	{
		for(int i=0;i<Count;i++)
		{
			if(Items[i]->Name == IndexOrName)
				return Items[i];
        }
	}
	return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameCollection::Fixup(void)
{
	if(!FIsFixedUp)
	{
		DoFixup();
		FIsFixedUp = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameCollection::DoFixup(void)
{
	 for(int i=0;i<Count;i++)
	 {
         Items[i]->DoFixup();
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameCollection::Start(void)
{
	Fixup();
	DoStart();
}
//---------------------------------------------------------------------------
__fastcall TFlowListNameSelCollection::TFlowListNameSelCollection(TGameObject *Owner, TClass ItemClass)
	: TFlowListNameCollection(Owner, ItemClass)
{
}
//---------------------------------------------------------------------------
void __fastcall TFlowListNameSelCollection::SetSelected(String Value)
{
	if(IsFixedup && Value != "" && !ItemExists(Value))
		throw EArgumentException("Item with name '"+Value+"' doesn't exist!");
	FSelected = Value;
}
//---------------------------------------------------------------------------
__fastcall TGameFlow::TGameFlow(TComponent *Owner, TGameFlowList *FlowList)
	: TFmxObject(Owner), flowList(FlowList)
{
}
//---------------------------------------------------------------------------
__fastcall TGameFlow::~TGameFlow(void)
{
	delete flowList;
}
//---------------------------------------------------------------------------
void __fastcall TGameFlow::Start(void)
{
	FlowList->Start();
}
//---------------------------------------------------------------------------
void __fastcall TGameFlow::Stop(void)
{
	FlowList->Stop();
}
//---------------------------------------------------------------------------
void __fastcall TGameFlow::Pause(void)
{
	FlowList->Pause();
}
//---------------------------------------------------------------------------
bool __fastcall TGameFlow::IsRunning(void)
{
	return FlowList->IsRunning();
}
//---------------------------------------------------------------------------
bool __fastcall TGameFlow::IsPaused(void)
{
	return FlowList->IsPaused();
}
//---------------------------------------------------------------------------
TNotifyEvent __fastcall TGameFlow::GetOnStarted(void)
{
	return FlowList->OnStarted;
}
//---------------------------------------------------------------------------
void __fastcall TGameFlow::SetOnStarted(TNotifyEvent value)
{
	FlowList->OnStarted = value;
}
//---------------------------------------------------------------------------
TNotifyEvent __fastcall TGameFlow::GetOnStopped(void)
{
	return FlowList->OnStopped;
}
//---------------------------------------------------------------------------
void __fastcall TGameFlow::SetOnStopped(TNotifyEvent value)
{
	FlowList->OnStopped = value;
}
//---------------------------------------------------------------------------
TNotifyEvent __fastcall TGameFlow::GetOnPaused(void)
{
	return FlowList->OnPaused;
}
//---------------------------------------------------------------------------
void __fastcall TGameFlow::SetOnPaused(TNotifyEvent value)
{
	FlowList->OnPaused = value;
}
//---------------------------------------------------------------------------
TNotifyEvent __fastcall TGameFlow::GetOnFinished(void)
{
	return FlowList->OnFinished;
}
//---------------------------------------------------------------------------
void __fastcall TGameFlow::SetOnFinished(TNotifyEvent value)
{
	FlowList->OnFinished = value;
}
//---------------------------------------------------------------------------

