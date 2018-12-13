//---------------------------------------------------------------------------

#ifndef EventFlowsH
#define EventFlowsH
#include "GameFlow.h"
#include "FlowTree.h"
#include "Hotspot.h"
#include "../GUIs/GameGUIFrame.h"
#include "../Frames/GameFrame.h"
#include "Person.h"
//---------------------------------------------------------------------------
template<class RefClass>
class PACKAGE TEventFlowItem : public TReferenceFlowItem<RefClass>
{
typedef TReferenceFlowItem<RefClass> Inherited;
private:
	DEFINE_EVENTLIST_PROPERTIES(OnEvent,TNotifyEvent,public,__published)

	void __fastcall DoStart(void);
	void __fastcall DoStop(void){};
	void __fastcall DoPause(void){};
protected:
	virtual void __fastcall DoEvent(void)=0;
public:
	bool __fastcall IsRunning(void){ return false; };
	bool __fastcall IsPaused(void){ return false; };

	__fastcall TEventFlowItem(TBasicCustomList* List) : Inherited(List){ IsBlocking = false; };

	void __fastcall Assign(TPersistent* Source)
	{
		if(Source != NULL && Source->InheritsFrom(__classid(TEventFlowItem)))
		{
			TEventFlowItem *Item = (TEventFlowItem*)Source;
			FOnEventList = Item->FOnEventList;
		}
		Inherited::Assign(Source);
	}
};
//---------------------------------------------------------------------------
template<class RefClass>
void __fastcall TEventFlowItem<RefClass>::DoStart(void)
{
	FOnEventList.CallEvents(this);
	DoEvent();
	Stop();
}
//---------------------------------------------------------------------------
class PACKAGE TCustomEventFlowItem : public TEventFlowItem<TGameObject>
{
protected:
	void __fastcall DoEvent(void){};
public:
	__fastcall TCustomEventFlowItem(TBasicCustomList* List) : TEventFlowItem<TGameObject>(List){};
};
//---------------------------------------------------------------------------
class PACKAGE TStopFlowItem : public TEventFlowItem<TGameObject>
{
typedef TEventFlowItem<TGameObject> Inherited;
private:
	int stopIndex;

	void __fastcall DoEvent(void);
public:
	__fastcall TStopFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property int StopIndex = {read=stopIndex,write=stopIndex}; //Index des zu stoppenden Items
};
//---------------------------------------------------------------------------
class PACKAGE TGiveItemFlowItem : public TEventFlowItem<TGameObject>
{
typedef TEventFlowItem<TGameObject> Inherited;
private:
	String item;
	void __fastcall DoEvent(void);
public:
	__fastcall TGiveItemFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property String Item = {read=item,write=item}; //Item, was ins Inventar gelegt werden soll
};
//---------------------------------------------------------------------------
class PACKAGE TLoadLocationFlowItem : public TEventFlowItem<TGameObject>
{
typedef TEventFlowItem<TGameObject> Inherited;
private:
	String FrameName;
	String FOpenFlowName;
	void __fastcall DoEvent(void);
public:
	__fastcall TLoadLocationFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property String Location = {read=FrameName,write=FrameName}; //Name des zu ladenden Frames
	__property String OpenFlowName = {read=FOpenFlowName,write=FOpenFlowName}; //OpenFlow des zu ladenden Frames
};
//---------------------------------------------------------------------------
class PACKAGE TChangeStateFlowItem : public TEventFlowItem<TGameObject>
{
typedef TEventFlowItem<TGameObject> Inherited;
private:
	String FHotspotName;
	String FFrameName;
	String FState;
	void __fastcall DoEvent(void);
	THotspot* __fastcall GetHotspot(void);
	TGameFrame* __fastcall GetFrame(void);
protected:

public:
	__fastcall TChangeStateFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);

	__property THotspot* Hotspot = {read=GetHotspot};
	__property TGameFrame* Frame = {read=GetFrame};
__published:
	__property String FrameName = {read=FFrameName,write=FFrameName};
	__property String HotspotName = {read=FHotspotName,write=FHotspotName};
	__property String State = {read=FState,write=FState};
};
//---------------------------------------------------------------------------
class PACKAGE TChangeLocalStateFlowItem : public TEventFlowItem<THotspot>
{
typedef TEventFlowItem<THotspot> Inherited;
private:
	String FState;
	void __fastcall DoEvent(void);
protected:

public:
	__fastcall TChangeLocalStateFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property String State = {read=FState,write=FState};
	__property Object;
};
//---------------------------------------------------------------------------
class PACKAGE TChangeAnimationFlowItem : public TEventFlowItem<TForegroundObj>
{
typedef TEventFlowItem<TForegroundObj> Inherited;
private:
	String FAnimation;
	void __fastcall DoEvent(void);
protected:

public:
	__fastcall TChangeAnimationFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property Object;
	__property String Animation = {read=FAnimation,write=FAnimation};
};
//---------------------------------------------------------------------------
class PACKAGE TLoadPicFlowItem : public TEventFlowItem<TGameObject>
{
typedef TEventFlowItem<TGameObject> Inherited;
private:
	String FPicture;
	void __fastcall DoEvent(void);

	String __fastcall GetTexturePath(void);

public:
	__fastcall TLoadPicFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property Object;
	__property String Picture = {read=FPicture,write=FPicture};
	__property String TexturePath = {read=GetTexturePath};
};
//---------------------------------------------------------------------------
class PACKAGE TOpenConvFlowItem : public TEventFlowItem<TPerson>
{
typedef TEventFlowItem<TPerson> Inherited;
private:
	void __fastcall DoEvent(void);
public:
	__fastcall TOpenConvFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property Object;
};
//---------------------------------------------------------------------------
class PACKAGE TMoveObjFlowItem : public TEventFlowItem<TGameObject>
{
typedef TEventFlowItem<TGameObject> Inherited;
private:

	float FLeftChange;
	float FTopChange;

	void __fastcall DoEvent(void);
public:
	__fastcall TMoveObjFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property Object;
	__property float LeftChange = {read=FLeftChange,write=FLeftChange};
	__property float TopChange = {read=FTopChange,write=FTopChange};
};
//---------------------------------------------------------------------------
class PACKAGE TChangePropertyFlowItem : public TEventFlowItem<TGameObject>
{
typedef TEventFlowItem<TGameObject> Inherited;
typedef bool __fastcall (__closure *TPropertySetEvent)(TGameObject *Sender, String PropName, String &PropVal);
private:
	String FPropName;
	String FPropVal;

	TPropertySetEvent FOnPropertySet;

	void __fastcall DoEvent(void);
public:
	__fastcall TChangePropertyFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property Object;
	__property String PropertyName = {read=FPropName,write=FPropName};
	__property String PropertyValue = {read=FPropVal,write=FPropVal};
	__property TPropertySetEvent OnPropertySet = {read=FOnPropertySet,write=FOnPropertySet};
};
//---------------------------------------------------------------------------
#endif
