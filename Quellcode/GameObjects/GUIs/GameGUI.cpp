//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TGameGUI* __fastcall TGameGUI::Instance(void)
{
	if(!TGameManager::IsCreated())
	{
		throw EArgumentException("Can't get GUI without Game Manager!");
		return NULL;
	}
	return TGameManager::Manager()->GUIs[this->ClassName()];
}
//---------------------------------------------------------------------------
bool __fastcall TGameGUI::IsInstance(void)
{
	if(!TGameManager::IsCreated())
		return false;
	return TGameManager::Manager()->GUIExists[this->ClassName()];
}
//---------------------------------------------------------------------------
__fastcall TGameGUI::TGameGUI(TComponent *Owner, TGameGUIFrame *GUIFrame)
	: TGameBase(Owner), FGUIFrame(GUIFrame), isOpen(true)
{
	if(!ComponentState.Contains(csDesigning) && !TGameManager::IsCreated())
		throw EArgumentException("You have to create the Game Manager before the form!");
	if(TGameManager::IsCreated())
		TGameManager::Manager()->RegisterGUI(this);

	FGUIFrame->Parent = this;
	FGUIFrame->Align = TAlignLayout::Contents;
	FGUIFrame->Stored = false;
}
//---------------------------------------------------------------------------
__fastcall TGameGUI::~TGameGUI(void)
{
	if(TGameManager::IsCreated())
		TGameManager::Manager()->UnregisterGUI(this);
	delete FGUIFrame;
}
//---------------------------------------------------------------------------
String __fastcall TGameGUI::GetResourcePath(void)
{
	return ResourceRoot()+"\\GUIs\\"+ClassName();
}
//---------------------------------------------------------------------------
void __fastcall TGameGUI::DoOpen(void)
{
	Visible = true;
	BringToFront();
	if(ComponentState.Contains(csDesigning) || ComponentState.Contains(csLoading))
	{
		FGUIFrame->Opacity = 1;
		Visible = true;
	}
	else
	{
		FGUIFrame->OpenCloseAnimation->Inverse = !IsOpen;
		FGUIFrame->OpenCloseAnimation->Start();
	}
	DoRealign();
}
//---------------------------------------------------------------------------
void __fastcall TGameGUI::DoClose(void)
{
	if(ComponentState.Contains(csDesigning) || ComponentState.Contains(csLoading))
	{
		FGUIFrame->Opacity = 0;
		Visible = false;
	}
	else
	{
		FGUIFrame->OpenCloseAnimation->Inverse = !IsOpen;
		FGUIFrame->OpenCloseAnimation->Start();
	}
	DoRealign();
}
//---------------------------------------------------------------------------
void __fastcall TGameGUI::Open(void)
{
	if(!isOpen)
	{
		isOpen = true;
		DoOpen();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameGUI::Close(void)
{
	if(isOpen)
	{
		isOpen = false;
		DoClose();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameGUI::SetIsOpen(bool value)
{
	if(value != isOpen || ComponentState.Contains(csLoading))
	{
		isOpen = value;
		if(value)
			DoOpen();
		else
			DoClose();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameGUI::Loaded(void)
{
	TGameBase::Loaded();
	if(isOpen)
	{
        DoOpen();
    }
}
//---------------------------------------------------------------------------
TGameXmlNode __fastcall TGameGUI::ToXmlNode(void)
{
	return CreateNode(ClassName());
}
//---------------------------------------------------------------------------
void __fastcall TGameGUI::FromXmlNode(TGameXmlNode Node)
{
	if(Node->NodeName != ClassName())
	{
        throw EXmlNodeNameError((TObject*)this,Node);
    }
}
//---------------------------------------------------------------------------
