//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Player
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TPlayer)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
__fastcall TPlayer::TPlayer(TComponent *Owner)
	: TForegroundObj(Owner), FMinPos(0), FMaxPos(100), FMoveStopPos(0), FYOffsetPerPic(5),
	  FFacingDir(TFacingDirection::Left), FTextureDir(TFacingDirection::Left), HotspotDest(NULL)
{
}
//---------------------------------------------------------------------------
float __fastcall TPlayer::GetOffset(void)
{
	return (FFacingDir == FTextureDir ? -1 : 1) * FYOffsetPerPic;
}
//---------------------------------------------------------------------------
float __fastcall TPlayer::GetStopPosition(void)
{
	return HotspotDest == NULL ? MoveStopPos : HotspotDest->Left + HotspotDest->PlayerOffset;
}
//---------------------------------------------------------------------------
bool __fastcall TPlayer::CanMove(void)
{
	float NewLeft = Left + GetOffset();
	return FFacingDir == TFacingDirection::Right ? NewLeft <= GetStopPosition() : NewLeft >= GetStopPosition();
}
//---------------------------------------------------------------------------
void __fastcall TPlayer::UpdateFacingDir(void)
{
	if(Left < GetStopPosition())
	{
		FFacingDir = TFacingDirection::Right;
	}
	else
	{
		FFacingDir = TFacingDirection::Left;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPlayer::PicLoaded(TImage *ImgObj)
{
	if(Animations->Selected == FMoveAnimation)
	{
		UpdateFacingDir();
		if(CanMove())
		{
			Left = Left + GetOffset();
		}
		else
		{
			Left = GetStopPosition();
			if(HotspotDest != NULL)
				FFacingDir = HotspotDest->PlayerFacing;
			FOnMovingFinishedList.CallEvents(this);
			if(HotspotDest == NULL || HotspotDest->PlayerAnimation == "")
				Animations->Selected = FIdleAnimation;
			else
				Animations->Selected = HotspotDest->PlayerAnimation;
			if(HotspotDest != NULL)
				HotspotDest->RunEventState();
			return;
		}
	}
	if(FFacingDir != FTextureDir)
	{
		ImgObj->Bitmap->FlipHorizontal();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPlayer::MoveHorz(int X)
{
	HotspotDest = NULL;
	if(X < MinPosition)
		MoveStopPos = MinPosition;
	else if(X > MaxPosition)
		MoveStopPos = MaxPosition;
	else
		MoveStopPos = X;
	MoveStopPos -= Width/2;

	UpdateFacingDir();
	if(CanMove())
	{
		Animations->Selected = FMoveAnimation;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPlayer::MoveToHotspot(THotspot *Hotspot)
{
	HotspotDest = Hotspot;
	UpdateFacingDir();
	Animations->Selected = FMoveAnimation;
}
//---------------------------------------------------------------------------
void __fastcall TPlayer::SetLeft(float Value)
{
	TGameObject::SetLeft(Value);
}
//---------------------------------------------------------------------------
String __fastcall TPlayer::GetResourcePath(void)
{
	return ResourceRoot()+"\\Player";
}
//---------------------------------------------------------------------------
