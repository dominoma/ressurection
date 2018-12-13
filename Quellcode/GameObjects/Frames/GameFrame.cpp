//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop

#include "GameFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Background"
#pragma link "GameObject"
#pragma link "ForegroundObj"
#pragma link "Player"
#pragma link "Exit"
#pragma link "Hotspot"
#pragma resource "*.fmx"
TGameFrame *GameFrame;
//---------------------------------------------------------------------------
namespace Gameframe
{
	void __fastcall PACKAGE Register()
	{
		//TGameFrame::RegisterFrames();
		//new TGameManager();
	}
}
//---------------------------------------------------------------------------
TGameFrame* __fastcall TGameFrame::Instance(void)
{
	if(!TGameManager::IsCreated())
		throw EArgumentException("Can't get Frame without Game Manager!");
	return TGameManager::Manager()->Frames[this->ClassName()];
}
//---------------------------------------------------------------------------
bool __fastcall TGameFrame::IsInstance(void)
{
	if(!TGameManager::IsCreated())
		return false;
	return TGameManager::Manager()->FrameExists[this->ClassName()];
}
//---------------------------------------------------------------------------
__fastcall TGameFrame::TGameFrame(TComponent* Owner)
	: TFrame(Owner), LockObj(new TRectangle(this)), isRunning(false), LockedSender(NULL)
{
	if(!TGameManager::IsCreated())
		throw EArgumentException("Can't create Frame without Game Manager!");
	TGameManager::Manager()->RegisterFrame(this);

	CanFocus = true;

	LockObj->Parent = this;
	LockObj->Stored = false;
	LockObj->Align = TAlignLayout::Client;
	LockObj->Opacity = 0;
	LockObj->OnClick = LockedObjClick;
	LockObj->HitTest = false;
	LockObj->Fill->Color = claBlack;
}
//---------------------------------------------------------------------------
__fastcall TGameFrame::~TGameFrame(void)
{
	TGameManager::Manager()->UnregisterFrame(this);
	delete LockObj;
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::BeforeDestruction(void)
{
	Terminate();
	TFrame::BeforeDestruction();
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift)
{
	if(!LockObj->HitTest)
		TGameManager::Manager()->KeyDown(this,KeyChar);
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::KeyUp(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift)
{
	if(!LockObj->HitTest)
		TGameManager::Manager()->KeyUp(this,KeyChar);
}
//---------------------------------------------------------------------------
TPlayer* __fastcall TGameFrame::Player(void)
{
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->ClassType() == __classid(TPlayer))
			return (TPlayer*)Components[i];
	}
	throw EArgumentException("There is no player in this frame!");
}
//---------------------------------------------------------------------------
bool __fastcall TGameFrame::IsPlayer(void)
{
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->ClassType() == __classid(TPlayer))
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TGameFrame::ToXmlNode(void)
{
	_di_IXMLNode Node = CreateNode(ClassName());
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->InheritsFrom(__classid(TGameObject)))
		{
			Node->ChildNodes->Add(((TGameObject*)Components[i])->ToXmlNode());
		}
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::FromXmlNode(_di_IXMLNode Node)
{
	if(Node->NodeName != ClassName())
		throw EXmlNodeNameError((TObject*)this,Node);
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->InheritsFrom(__classid(TGameObject)))
		{
			_di_IXMLNode SubNode = Node->ChildNodes->FindNode(Components[i]->Name);
			if(SubNode != NULL)
				((TGameObject*)Components[i])->FromXmlNode(SubNode);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::ShowHotspotHints(TBitmap *HintImg)
{
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->InheritsFrom(__classid(THotspot)))
		{
			((THotspot*)Components[i])->ShowHint(HintImg);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::HideHotspotHints(void)
{
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->InheritsFrom(__classid(THotspot)))
		{
			((THotspot*)Components[i])->HideHint();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::LockScreen(TGameFlowCustomItem* Sender, float Opacity)
{
	LockObj->Width = Width;
	LockObj->Height = Height;
	LockObj->BringToFront();
	LockObj->HitTest = true;
	LockObj->Opacity = Opacity;
	HideHotspotHints();
	LockedSender = Sender;
	((TInventoryGUI*)TInventoryGUI::Instance())->DisableMenuButton();
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::UnlockScreen(void)
{
	LockObj->SendToBack();
	SetFocus();
	LockObj->HitTest = false;
	LockObj->Opacity = 0;
	LockedSender = NULL;
	((TInventoryGUI*)TInventoryGUI::Instance())->EnableMenuButton();
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::LockedObjClick(TObject *Sender)
{
	LockedScreenClicked();
	if(LockedSender != NULL)
	{
        LockedSender->Jump();
    }
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::Run(void)
{
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->InheritsFrom(__classid(TGameObject)))
		{
			((TGameObject*)Components[i])->Start();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::Terminate(void)
{
	for(int i=0;i<ComponentCount;i++)
	{
		if(Components[i]->InheritsFrom(__classid(TGameObject)))
		{
			((TGameObject*)Components[i])->Stop();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::Open(String OpenFlowName)
{
	if(!IsOpen)
	{
		TGameManager::Manager()->OpenFrame(ClassName(),OpenFlowName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::Close(void)
{
	if(IsOpen)
	{
		if(Background->OnFrameClosed != NULL)
			Background->OnFrameClosed(Background);
		Terminate();
		DoClose();
		TGameManager::Manager()->SaveGame();
    }
}
//---------------------------------------------------------------------------
bool __fastcall TGameFrame::GetIsOpen(void)
{
	return TGameManager::IsCreated() ? TGameManager::Manager()->OpenedFrame == this : false;
}
//---------------------------------------------------------------------------
void __fastcall TGameFrame::Paint(void)
{
	TFrame::Paint();
	if(Background != NULL)
	{
		BGRect->SetBounds(0,0,Width,Height);
		Background->SetBounds(0,0,Width,Height);
		Background->Position->X = (Width - Background->Width)/2.0;
	}
}
//---------------------------------------------------------------------------

