//---------------------------------------------------------------------------

#ifndef HotspotH
#define HotspotH
#include "../Flows/FlowLists.h"
#include "ForegroundObj.h"
#include "../PropertyClasses.h"
//---------------------------------------------------------------------------
class THotspot;
//---------------------------------------------------------------------------
class PACKAGE TItemDropEvent : public TCollectionItem
{
private:
	String itemName;
	String FHotspotState;
	TGameFlowList *flowList;
	bool FDeleteItem;

	void __fastcall SetHotspotState(String State);
	void __fastcall SetFlowList(TGameFlowList *FlowList){};
	void __fastcall FlowListStarted(TObject *Sender);
public:

	__fastcall TItemDropEvent(TCollection *Owner);
	__fastcall ~TItemDropEvent(void);

__published:
	__property String ItemName = {read=itemName,write=itemName};
	__property String HotspotState = {read=FHotspotState,write=SetHotspotState};
	__property TGameFlowList* FlowList = {read=flowList,write=SetFlowList};
	__property bool DeleteItem = {read=FDeleteItem,write=FDeleteItem};
};
//---------------------------------------------------------------------------
class PACKAGE TItemDropEvents : public TOwnedCollection
{
private:

public:
	IGameRunnable* __fastcall GetFlow(void);
	IGameRunnable* __fastcall GetFlow(String ItemName, String HotspotState);

	bool __fastcall IsFlow(void);
	bool __fastcall IsFlow(String ItemName, String HotspotState);

	void __fastcall StatesUpdate(void);

	__fastcall TItemDropEvents(THotspot *Owner);
};
//---------------------------------------------------------------------------
class PACKAGE THotspotStateList : public TFlowListNameSelCollectionTmpl<TFlowListGameItem>
{
typedef TFlowListNameSelCollectionTmpl<TFlowListGameItem> Inherited;
private:

protected:
	void __fastcall SetSelected(String NewName);
	void __fastcall DoStart(void);
public:
	__fastcall THotspotStateList(THotspot *Owner);
__published:
	__property Selected;
};
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TGameEvent)(THotspot *Sender);
enum class TFacingDirection {Left,Right};
//---------------------------------------------------------------------------
class PACKAGE THotspot : public TForegroundObj
{
private:
	enum class THotspotEventState {Nothing, Inspecting, Acting, ItemDropping} FEventState;

	THotspotStateList *stateList;
	TImage *FHintImage;

	TGameEvent onInspect;
	TGameEvent onAction;
	TGameEvent onItemDrop;

	TFlowListGameList *FInspectFlows;
	TFlowListGameList *FActionFlows;

	TItemDropEvents *FItemDropEvents;

	float FPlayerOffset;
	TFacingDirection FPlayerFacing;
	String FPlayerAnimation;

	String __fastcall GetState(void);
	void __fastcall SetState(String value);

	void __fastcall MouseUp(TMouseButton Button, TShiftState Shift,
	  float X, float Y);

	void __fastcall SetStates(THotspotStateList *States){};

	void __fastcall SetInspectFlows(TFlowListGameList *InspectFlow){};
	void __fastcall SetActionFlows(TFlowListGameList *ActionFlow){};
	void __fastcall SetItemDropEvents(TItemDropEvents *Events){};

	TGameFlowList* __fastcall GetStateSelActnFlow(void);
	TGameFlowList* __fastcall GetStateSelInspctFlow(void);

protected:
	void __fastcall DoStart(void);
	void __fastcall DoStop(void);

	void __fastcall Loaded(void);

	__property TGameFlowList* StateSelActnFlow = {read=GetStateSelActnFlow};
	__property TGameFlowList* StateSelInspctFlow = {read=GetStateSelInspctFlow};

	virtual void __fastcall Inspect(void){};
	virtual void __fastcall Action(void){};
	virtual void __fastcall ItemDrop(void){};

public:

	void __fastcall RunEventState(void);

	void __fastcall ShowHint(TBitmap *HintImg);
	void __fastcall HideHint(void);

	__fastcall THotspot(TComponent *Owner);
	__fastcall ~THotspot(void);

	TGameXmlNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(TGameXmlNode Node);

__published:

	__property TFlowListGameList* InspectFlows = {read=FInspectFlows, write=SetInspectFlows};
	__property TFlowListGameList* ActionFlows = {read=FActionFlows, write=SetActionFlows};

	__property THotspotStateList* States = {read=stateList,write=SetStates};
	__property String State = {read=GetState,write=SetState,stored=false};
	__property TItemDropEvents* ItemDropEvents = {read=FItemDropEvents,write=SetItemDropEvents};

	__property float PlayerOffset = {read=FPlayerOffset, write=FPlayerOffset};
	__property TFacingDirection PlayerFacing = {read=FPlayerFacing, write=FPlayerFacing};
	__property String PlayerAnimation = {read=FPlayerAnimation, write=FPlayerAnimation};

	__property TGameEvent OnInspect = {read=onInspect, write=onInspect};
	__property TGameEvent OnAction = {read=onAction, write=onAction};
	__property TGameEvent OnItemDrop = {read=onItemDrop, write=onItemDrop};

};
#endif
