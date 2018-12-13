//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TBackground *)
{
	new TBackground(NULL);
}
//---------------------------------------------------------------------------
__fastcall TBackground::TBackground(TComponent* Owner)
	: TGameObject(Owner), FOpenFlowList(new TFlowListGameList(this)),
	FBeforeOpenFlowList(new TFlowListEventList(this)),
	FOnFrameClosed(NULL), BGTrackVolume(1.0)
{
	//Align = TAlignLayout::Client;
	//Anchors = TAnchors() << TAnchorKind::akLeft << TAnchorKind::akTop << TAnchorKind::akRight << TAnchorKind::akBottom;
}
//---------------------------------------------------------------------------
__fastcall TBackground::~TBackground(void)
{
	delete FOpenFlowList;
}
//---------------------------------------------------------------------------
void __fastcall TBackground::Loaded(void)
{
	if(ComponentState.Contains(csDesigning))
	{
        ForceDirectories(ResourcePath);
    }
	TGameObject::Loaded();
	if(ComponentState.Contains(csDesigning))
		Align = TAlignLayout::Client;
}
//---------------------------------------------------------------------------
void __fastcall TBackground::SetBackgroundFile(String FileName)
{
	if(FileExists(ResourcePath+"\\"+FileName))
	{
		LoadPic(ResourcePath+"\\"+FileName);
		FBackgroundFile = FileName;
	}
}
//---------------------------------------------------------------------------
void __fastcall TBackground::MouseUp(TMouseButton Button, TShiftState Shift, float X, float Y)
{
	if(TGameManager::IsCreated() && TGameManager::Manager()->OpenedFrame->IsPlayer())
		TGameManager::Manager()->OpenedFrame->Player()->MoveHorz(X*OriginalWidth/Width);
}
//---------------------------------------------------------------------------
namespace Background
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TBackground)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
