//---------------------------------------------------------------------------

#ifndef BackgroundH
#define BackgroundH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "Hotspot.h"
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class PACKAGE TFlowListEventItem : public TFlowListNameSelItem
{
public:
	__fastcall TFlowListEventItem(TCollection *Owner) : TFlowListNameSelItem(Owner, new TEventFlowList((TGameObject*)Owner->Owner())){};
};
//---------------------------------------------------------------------------
class PACKAGE TFlowListEventList : public TFlowListNameCollectionTmpl<TFlowListEventItem>
{
public:
	__fastcall TFlowListEventList(TGameObject *Owner) : TFlowListNameCollectionTmpl<TFlowListEventItem>(Owner){};
};
//---------------------------------------------------------------------------
class PACKAGE TBackground : public TGameObject
{
private:
	String FBackgroundFile;
	TFlowListGameList* FOpenFlowList;
	TFlowListEventList* FBeforeOpenFlowList;
	String FBackgroundTrack;
	float FBGTrackVolume;

	TNotifyEvent FOnFrameClosed;

	void __fastcall SetBackgroundFile(String FileName);
	void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, float X, float Y);
protected:
	void __fastcall Loaded(void);
public:
	__fastcall TBackground(TComponent* Owner);
	__fastcall ~TBackground(void);

	String __fastcall BGTrackFileName(void){ return ResourceRoot()+"\\BGMusic\\"+FBackgroundTrack; };

	__property Align;

__published:
	__property String BackgroundFile = {read=FBackgroundFile,write=SetBackgroundFile};
	__property TNotifyEvent OnFrameClosed = {read=FOnFrameClosed,write=FOnFrameClosed};

	__property TFlowListGameList* OpenFlowList = {read=FOpenFlowList,write=FOpenFlowList};
	__property TFlowListEventList* BeforeOpenFlowList = {read=FBeforeOpenFlowList,write=FBeforeOpenFlowList};
	__property String BackgroundTrack = {read=FBackgroundTrack,write=FBackgroundTrack};
	__property float BGTrackVolume = {read=FBGTrackVolume,write=FBGTrackVolume};

	
};
//---------------------------------------------------------------------------
#endif
