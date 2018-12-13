//---------------------------------------------------------------------------

#ifndef GameFlowH
#define GameFlowH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include "..\Stuff.h"
#include "CustomList.h"
#include "XmlSerialize.h"
#include "GameObject.h"
#include "EventList.h"
//---------------------------------------------------------------------------
class TGameFlow;
class TGameFlowList;
enum class TStopFlowPos {Start,Stop,Pause,Repeat};
//---------------------------------------------------------------------------
__interface IGameRunnable
{
	virtual void __fastcall Start(void)=0; //Startet eine Aktion
	virtual void __fastcall Stop(void)=0;  //Stoppt eine Aktion
	virtual void __fastcall Pause(void)=0; //Pausiert eine aktion

	virtual bool __fastcall IsRunning(void)=0; //Gibt an, ob die Aktion gerade ausgeführt wird
	virtual bool __fastcall IsPaused(void)=0;  //Gibt an, ob die Aktion pausiert ist
};
//---------------------------------------------------------------------------
class PACKAGE TGameFlowCustomItem : public TCustomListItem,
							  public IGameRunnable
{
private:
    //defines private FOnStartedList, public OnStartedList, protected OnStarted
	DEFINE_EVENTLIST_PROPERTIES(OnStarted,TNotifyEvent,public,protected)

	//defines private FOnStoppedList, public OnStoppedList, protected OnStopped
	DEFINE_EVENTLIST_PROPERTIES(OnStopped,TNotifyEvent,public,protected)

	//defines private FOnPausedList, public OnPausedList, protected OnPaused
	DEFINE_EVENTLIST_PROPERTIES(OnPaused,TNotifyEvent,public,protected)

	//defines private FOnFinishedList, public OnFinishedList, protected OnFinished
	DEFINE_EVENTLIST_PROPERTIES(OnFinished,TNotifyEvent,public,protected)

	bool isBlocking;
	bool repeat;
	bool lockScreen;

protected:
	virtual void __fastcall Started(void){};
	virtual void __fastcall Stopped(void){};
	virtual void __fastcall Paused(void){};
	virtual void __fastcall Finished(void){};

	virtual void __fastcall DoStart(void)=0;
	virtual void __fastcall DoStop(void)=0;
	virtual void __fastcall DoPause(void)=0;

	void __fastcall Finish(void);

	TGameFlowList* __fastcall GetFlowList(void);
	TGameFlowCustomItem* __fastcall GetNextItem(void);
	TGameFlowCustomItem* __fastcall GetLastItem(void);
public:

	void __fastcall Start(void);
	void __fastcall Stop(void);
	void __fastcall Pause(void);
	virtual void __fastcall Jump(void){ Stop(); };

	bool __fastcall HasFocus(void);
	bool __fastcall CanLooseFocus(void);

	__fastcall TGameFlowCustomItem(TBasicCustomList* List);
	__fastcall ~TGameFlowCustomItem(void);

	void __fastcall Assign(TPersistent* Source);

	__property TGameFlowList* FlowList = {read=GetFlowList};
	__property TGameFlowCustomItem* NextItem = {read=GetNextItem};
	__property TGameFlowCustomItem* LastItem = {read=GetLastItem};

protected:
	__property bool IsBlocking = {read=isBlocking,write=isBlocking, default=true};
	__property bool Repeat = {read=repeat,write=repeat};
	__property bool LockScreen = {read=lockScreen,write=lockScreen};
};
//---------------------------------------------------------------------------
template<class RefClass>
class PACKAGE TReferenceFlowItem : public TGameFlowCustomItem
{
private:
	RefClass *FObject;
protected:
	virtual void __fastcall SetObject(RefClass *NewObj)
	{
		if(NewObj != NULL && !NewObj->InheritsFrom(__classid(RefClass)))
			throw EArgumentException("Error in setting Property 'Object': '"+NewObj->ClassName()+"' inst inherited from '"+RefClass::ClassName()+"'!");
		FObject = NewObj;
	};

	__property RefClass *Object = {read=FObject,write=SetObject,nodefault};
public:
	__fastcall TReferenceFlowItem(TBasicCustomList* List)
		: TGameFlowCustomItem(List)
	{
		if(FlowList->GameObject != NULL && FlowList->GameObject->InheritsFrom(__classid(RefClass)))
			FObject = (RefClass*)FlowList->GameObject;
		else
			FObject = NULL;
	};
	void __fastcall Assign(TPersistent* Source)
	{
		if(Source != NULL && Source->InheritsFrom(__classid(TReferenceFlowItem<RefClass>)))
		{
			Object = ((TReferenceFlowItem<RefClass>*)Source)->Object;
		}
		TGameFlowCustomItem::Assign(Source);
	};
};
//---------------------------------------------------------------------------
//template<class RefClass>
class TGameObject;
class PACKAGE TGameFlowItem : public TGameFlowCustomItem
{
public:
	__fastcall TGameFlowItem(TBasicCustomList* List) : TGameFlowCustomItem(List){};
__published:
	__property IsBlocking;
	__property Repeat;
	__property LockScreen;

	__property OnStarted;
	__property OnStopped;
	__property OnPaused;
	__property OnFinished;
};
//---------------------------------------------------------------------------
class TGameObject;
//---------------------------------------------------------------------------
class PACKAGE TGameFlowList : public TVectorList,
							  public IGameRunnable
{
friend void __fastcall TGameFlowCustomItem::Start(void);
private:
	//defines private FOnStartedList, public OnStartedList, __published OnStarted
	DEFINE_EVENTLIST_PROPERTIES(OnStarted,TNotifyEvent,public,__published)

	//defines private FOnStoppedList, public OnStoppedList, __published OnStopped
	DEFINE_EVENTLIST_PROPERTIES(OnStopped,TNotifyEvent,public,__published)

	//defines private FOnPausedList, public OnPausedList, __published OnPaused
	DEFINE_EVENTLIST_PROPERTIES(OnPaused,TNotifyEvent,public,__published)

	//defines private FOnFinishedList, public OnFinishedList, __published OnFinished
	DEFINE_EVENTLIST_PROPERTIES(OnFinished,TNotifyEvent,public,__published)

	bool isRunning;
	bool repeat;

	int currItemIndex; //Index des Items, welches gerade den Fokus hat

	void __fastcall StopAll(void);
	void __fastcall PauseAll(void);

	TGameFlowCustomItem* __fastcall GetItem(int Index);
	void __fastcall SetItem(int Index, TGameFlowCustomItem *obj);

	TGameFlowCustomItem* __fastcall GetCurrItem(void);

	TGameObject* __fastcall GetGameObject(void){ return (TGameObject*)Owner; };

	void __fastcall AddAllClasses(TClassList *ClassList);

protected:
	virtual void __fastcall Started(void){};
	virtual void __fastcall Stopped(void){};
	virtual void __fastcall Paused(void){};
	virtual void __fastcall Finished(void){};

	bool __fastcall IsItemRunning(void);

	virtual void __fastcall SetAllowedClasses(TClassList *ClassList);
	virtual TClass __fastcall MinimumClass(void);
	virtual bool __fastcall IsClassAllowed(TClass Class){ return Class->InheritsFrom(MinimumClass()); };

	void __fastcall BeforeDestruction(void);

public:

	void __fastcall Start(void);
	void __fastcall Stop(void);
	void __fastcall Pause(void);
	void __fastcall Finish(void);

	bool __fastcall IsRunning(void);
	bool __fastcall IsPaused(void);


	__fastcall TGameFlowList(TGameObject *Owner);
	__fastcall ~TGameFlowList(void);

	void __fastcall Assign(TPersistent* Source);

	__property TGameFlowCustomItem* Items[int Index] = {read=GetItem,write=SetItem};
	__property TGameFlowCustomItem* CurrItem = {read=GetCurrItem};

	__property TGameObject* GameObject = {read=GetGameObject};

__published:

	__property bool Repeat = {read=repeat,write=repeat};
};
//---------------------------------------------------------------------------
class TFlowListNameCollection;
//---------------------------------------------------------------------------
class PACKAGE TFlowListNameItem : public TCollectionItem
{
friend TFlowListNameCollection;
private:
	String FName;
	TGameFlowList *FFlowList;

	void __fastcall SetFlowList(TGameFlowList *NewFlow);

	TFlowListNameCollection* __fastcall GetCollection(void);
	TGameObject* __fastcall GetGameObject(void);
protected:
	virtual void __fastcall SetName(String NewName);
	String __fastcall GetDisplayName(void);

	virtual void __fastcall DoFixup(void){};
public:

	__fastcall TFlowListNameItem(TCollection *Owner, TGameFlowList *FlowList);
	__fastcall ~TFlowListNameItem(void);

	void __fastcall Assign(TPersistent* Source);
	bool __fastcall Equals(TObject* Obj);

	__property TFlowListNameCollection* Collection = {read=GetCollection};
	__property TGameObject* GameObject = {read=GetGameObject};
__published:
	__property String Name = {read=FName,write=SetName};
	__property TGameFlowList* FlowList = {read=FFlowList,write=SetFlowList};
};
//---------------------------------------------------------------------------
class PACKAGE TFlowListNameCollection : public TOwnedCollection
{
private:
	bool FIsFixedUp;

	TFlowListNameItem* __fastcall GetItem(String IndexOrName);
	void __fastcall SetItem(String IndexOrName, TFlowListNameItem *NewItem);

	TFlowListNameItem* __fastcall SearchItem(String IndexOrName);

	TGameObject* __fastcall GetGameObject(void){ return (TGameObject*)Owner(); };
protected:
	void __fastcall Added(TCollectionItem* &Item);
	virtual void __fastcall DoFixup(void);
	virtual void __fastcall DoStart(void){};
public:
	void __fastcall Fixup(void);
	void __fastcall Start(void);

	__fastcall TFlowListNameCollection(TGameObject *Owner, TClass ItemClass);

	bool __fastcall ItemExists(String Name);

	__property TFlowListNameItem* Items[String NameOrIndex] = {read=GetItem, write=SetItem};
	__property TGameObject* GameObject = {read=GetGameObject};
	__property bool IsFixedup = {read=FIsFixedUp};
};
//---------------------------------------------------------------------------
template<class ItemType, class ListType>
class PACKAGE TFlowListCollectionTmpl : public ListType
{
private:
	ItemType* __fastcall GetItem(String IndexOrName)
	{
		return (ItemType*)ListType::Items[IndexOrName];
	};
	void __fastcall SetItem(String IndexOrName, ItemType *NewItem)
	{
		ListType::Item[IndexOrName] = NewItem;
	};
public:
	__fastcall TFlowListCollectionTmpl(TGameObject *Owner)
		: ListType(Owner,__classid(ItemType))
	{
	};

	__property ItemType* Items[String NameOrIndex] = {read=GetItem, write=SetItem};
};
//---------------------------------------------------------------------------
template<class ItemType>
class TFlowListNameCollectionTmpl : public TFlowListCollectionTmpl<ItemType, TFlowListNameCollection>
{
public:
	__fastcall TFlowListNameCollectionTmpl(TGameObject *Owner)
		: TFlowListCollectionTmpl<ItemType, TFlowListNameCollection>(Owner)
	{
	};
};
//---------------------------------------------------------------------------
class PACKAGE TFlowListNameSelItem : public TFlowListNameItem
{
protected:
	void __fastcall SetName(String NewName);
public:
	__fastcall TFlowListNameSelItem(TCollection *Owner, TGameFlowList *FlowList);
};
//---------------------------------------------------------------------------
class PACKAGE TFlowListNameSelCollection : public TFlowListNameCollection
{
private:
	String FSelected;
protected:
	virtual void __fastcall SetSelected(String Value);

public:
	__fastcall TFlowListNameSelCollection(TGameObject *Owner, TClass ItemClass);

	__property String Selected = {read=FSelected,write=SetSelected};
};
//---------------------------------------------------------------------------
template<class ItemType>
class TFlowListNameSelCollectionTmpl : public TFlowListCollectionTmpl<ItemType, TFlowListNameSelCollection>
{
public:
	__fastcall TFlowListNameSelCollectionTmpl(TGameObject *Owner)
		: TFlowListCollectionTmpl<ItemType, TFlowListNameSelCollection>(Owner)
	{
	};
};
//---------------------------------------------------------------------------
class PACKAGE TGameFlow : public TFmxObject,
						  public IGameRunnable
{
private:
	TGameFlowList *flowList;

	TNotifyEvent __fastcall GetOnStarted(void);
	void __fastcall SetOnStarted(TNotifyEvent value);

	TNotifyEvent __fastcall GetOnStopped(void);
	void __fastcall SetOnStopped(TNotifyEvent value);

	TNotifyEvent __fastcall GetOnPaused(void);
	void __fastcall SetOnPaused(TNotifyEvent value);

	TNotifyEvent __fastcall GetOnFinished(void);
	void __fastcall SetOnFinished(TNotifyEvent value);

	void __fastcall SetFlowList(TGameFlowList* value){flowList->Assign(value);};

	bool __fastcall GetRepeat(void){ return flowList->Repeat; };
	void __fastcall SetRepeat(bool Value){ flowList->Repeat = Value; };

public:
	__fastcall TGameFlow(TComponent *Owner, TGameFlowList *FlowList);
	__fastcall ~TGameFlow(void);

	void __fastcall Start(void);
	void __fastcall Stop(void);
	void __fastcall Pause(void);

	bool __fastcall IsRunning(void);
	bool __fastcall IsPaused(void);


__published:
	__property TGameFlowList* FlowList = {read=flowList,write=SetFlowList};
	__property bool Repeat = {read=GetRepeat,write=SetRepeat};

	__property TNotifyEvent OnStarted = {read=GetOnStarted,write=SetOnStarted};
	__property TNotifyEvent OnStopped = {read=GetOnStopped,write=SetOnStopped};
	__property TNotifyEvent OnPaused = {read=GetOnPaused,write=SetOnPaused};
	__property TNotifyEvent OnFinished = {read=GetOnFinished,write=SetOnFinished};
};
//---------------------------------------------------------------------------
#endif
