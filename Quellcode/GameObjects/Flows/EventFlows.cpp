//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TStopFlowItem::TStopFlowItem(TBasicCustomList* List)
	: Inherited(List), stopIndex(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TStopFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TStopFlowItem)))
	{
		TStopFlowItem *Item = (TStopFlowItem*)Source;
		stopIndex = Item->stopIndex;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TStopFlowItem::DoEvent(void)
{
	if(stopIndex < 0 || stopIndex >= FlowList->Count)
		throw EFlowItemError(this, "StopIndex "+String(stopIndex)+" is out of bounds! [0-"+String(FlowList->Count-1)+"]");
	FlowList->Items[stopIndex]->Stop();
}
//---------------------------------------------------------------------------
__fastcall TGiveItemFlowItem::TGiveItemFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TGiveItemFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TGiveItemFlowItem)))
	{
		TGiveItemFlowItem *Item = (TGiveItemFlowItem*)Source;
		item = Item->item;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TGiveItemFlowItem::DoEvent(void)
{
	if(item != "")
	{
		((TInventoryGUI*)TInventoryGUI::Instance())->AddItem(TGameManager::Manager()->Items[item]);

	}
}
//---------------------------------------------------------------------------
__fastcall TLoadLocationFlowItem::TLoadLocationFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TLoadLocationFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TLoadLocationFlowItem)))
	{
		TLoadLocationFlowItem *Item = (TLoadLocationFlowItem*)Source;
		FrameName = Item->FrameName;
		FOpenFlowName = Item->FOpenFlowName;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TLoadLocationFlowItem::DoEvent(void)
{
	if(TGameManager::IsCreated())
		TGameManager::Manager()->OpenFrame(FrameName,FOpenFlowName);
}
//---------------------------------------------------------------------------
__fastcall TChangeStateFlowItem::TChangeStateFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TChangeStateFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TChangeStateFlowItem)))
	{
		TChangeStateFlowItem *Item = (TChangeStateFlowItem*)Source;
		FHotspotName = Item->FHotspotName;
		FFrameName = Item->FFrameName;
		FState = Item->FState;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
TGameFrame* __fastcall TChangeStateFlowItem::GetFrame(void)
{
	if(FFrameName == "" || !TGameManager::IsCreated())
		return NULL;
	else
		return TGameManager::Manager()->Frames[FFrameName];
}
//---------------------------------------------------------------------------
THotspot* __fastcall TChangeStateFlowItem::GetHotspot(void)
{
	if(Frame == NULL)
		return NULL;
	if(FHotspotName == "")
		return NULL;
	TComponent *retVal = Frame->FindComponent(FHotspotName);
	if(retVal == NULL || !retVal->InheritsFrom(__classid(THotspot)))
		throw EArgumentException("Hotspot value is not allowed!");
	return (THotspot*)retVal;
}
//---------------------------------------------------------------------------
void __fastcall TChangeStateFlowItem::DoEvent(void)
{
	if(Hotspot == NULL)
		throw EFlowItemError(this, "Hotspot must not be null!");
	Hotspot->State = FState;
}
//---------------------------------------------------------------------------
__fastcall TChangeLocalStateFlowItem::TChangeLocalStateFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TChangeLocalStateFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TChangeLocalStateFlowItem)))
	{
		TChangeLocalStateFlowItem *Item = (TChangeLocalStateFlowItem*)Source;
		FState = Item->FState;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TChangeLocalStateFlowItem::DoEvent(void)
{
	if(Object == NULL)
		throw EFlowItemError(this, "Object must not be null!");
	Object->State = State;
}
//---------------------------------------------------------------------------
__fastcall TChangeAnimationFlowItem::TChangeAnimationFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TChangeAnimationFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TChangeAnimationFlowItem)))
	{
		TChangeAnimationFlowItem *Item = (TChangeAnimationFlowItem*)Source;
		FAnimation = Item->FAnimation;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TChangeAnimationFlowItem::DoEvent(void)
{
	if(Object == NULL)
		throw EFlowItemError(this, "Object must not be null!");
	Object->Animation = FAnimation;
}
//---------------------------------------------------------------------------
__fastcall TLoadPicFlowItem::TLoadPicFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TLoadPicFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TLoadPicFlowItem)))
	{
		TLoadPicFlowItem *Item = (TLoadPicFlowItem*)Source;
		FPicture = Item->FPicture;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TLoadPicFlowItem::DoEvent(void)
{
	if(Object == NULL)
		throw EFlowItemError(this, "Object must not be null!");
	String PicFile;
	if(FPicture != "")
		PicFile = Object->ResourcePath+"\\"+FPicture;
	if(!FileExists(PicFile) && PicFile != "")
    	throw EFlowItemError(this, "PicFile (FullPath: '"+PicFile+"') is not a valid file!");
	Object->LoadPic(PicFile);
}
//---------------------------------------------------------------------------
String __fastcall TLoadPicFlowItem::GetTexturePath(void)
{
	if(Object != NULL)
		return Object->ResourcePath;
}
//---------------------------------------------------------------------------
__fastcall TOpenConvFlowItem::TOpenConvFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TOpenConvFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TOpenConvFlowItem)))
	{
		TOpenConvFlowItem *Item = (TOpenConvFlowItem*)Source;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TOpenConvFlowItem::DoEvent(void)
{
	if(Object == NULL)
		throw EFlowItemError(this, "Object must not be null!");
	TConversationGUI::Instance()->Open();
	((TConversationGUI*)TConversationGUI::Instance())->LoadFromConvTree(Object->ConvTree);
}
//---------------------------------------------------------------------------
__fastcall TMoveObjFlowItem::TMoveObjFlowItem(TBasicCustomList* List)
	: Inherited(List)
{
}
//---------------------------------------------------------------------------
void __fastcall TMoveObjFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TMoveObjFlowItem)))
	{
		TMoveObjFlowItem *Item = (TMoveObjFlowItem*)Source;
		FLeftChange = Item->FLeftChange;
		FTopChange = Item->FTopChange;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TMoveObjFlowItem::DoEvent(void)
{
	if(Object == NULL)
		throw EFlowItemError(this, "Object must not be null!");
	Object->Position->X += FLeftChange;
	Object->Position->Y += FTopChange;
}
//---------------------------------------------------------------------------
__fastcall TChangePropertyFlowItem::TChangePropertyFlowItem(TBasicCustomList* List)
	: Inherited(List), FOnPropertySet(NULL)
{
}
//---------------------------------------------------------------------------
void __fastcall TChangePropertyFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TChangePropertyFlowItem)))
	{
		TChangePropertyFlowItem *Item = (TChangePropertyFlowItem*)Source;
		FPropName = Item->FPropName;
		FPropVal = Item->FPropVal;
	}
	Inherited::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TChangePropertyFlowItem::DoEvent(void)
{
	if(Object == NULL)
		throw EFlowItemError(this, "Object must not be null!");
	String PropVal = FPropVal;
	if(FOnPropertySet == NULL || !FOnPropertySet(Object,FPropName,PropVal))
		SetPropValue(Object,FPropName,PropVal);
}
//---------------------------------------------------------------------------


