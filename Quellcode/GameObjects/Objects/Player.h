//---------------------------------------------------------------------------

#ifndef PlayerH
#define PlayerH
#include "GameObject.h"
#include "FlowLists.h"
#include <FMX.Ani.hpp>
#include "EventList.h"
//---------------------------------------------------------------------------
class PACKAGE TPlayer : public TForegroundObj
{
	String FMoveAnimation;
	String FIdleAnimation;

	TFacingDirection FFacingDir;
	TFacingDirection FTextureDir;

	float FMoveStopPos;
	float FYOffsetPerPic;

	float FMinPos;
	float FMaxPos;

	TNotifyEventList FOnMovingFinishedList;
	TNotifyEventList& __fastcall GetOnMovingFinishedList(void){ return FOnMovingFinishedList; };

	THotspot *HotspotDest;

protected:
	String __fastcall GetResourcePath(void);
	void __fastcall SetLeft(float Value);

	bool __fastcall CanMove(void);
	float __fastcall GetOffset(void);
	void __fastcall UpdateFacingDir(void);
	void __fastcall PicLoaded(TImage *ImgObj);

	float __fastcall GetStopPosition(void);
public:
	__fastcall TPlayer(TComponent *Owner);
	void __fastcall MoveHorz(int X);
	void __fastcall MoveToHotspot(THotspot *Hotspot);

	__property TNotifyEventList& OnMovingFinishedList = {read=GetOnMovingFinishedList};
__published:
	__property String MoveAnimation = {read=FMoveAnimation,write=FMoveAnimation};
	__property String IdleAnimation = {read=FIdleAnimation,write=FIdleAnimation};

	__property TFacingDirection FacingDirection = {read=FFacingDir,write=FFacingDir};
	__property TFacingDirection TextureDirection = {read=FTextureDir,write=FTextureDir};
	__property float YOffsetPerPic = {read=FYOffsetPerPic,write=FYOffsetPerPic};
	__property float MoveStopPos = {read=FMoveStopPos,write=FMoveStopPos};

	__property float MinPosition = {read=FMinPos,write=FMinPos};
	__property float MaxPosition = {read=FMaxPos,write=FMaxPos};

	__property Height;
	__property Padding;
	__property Opacity;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Visible = {default=1};
	__property Width;
};
#endif
