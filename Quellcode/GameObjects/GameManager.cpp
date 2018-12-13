//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop

#include "GameManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TGameManager *TGameManager::FManager = NULL;
//---------------------------------------------------------------------------
__fastcall TLogFile::TLogFile(String FileName)
	: FFileName(FileName), List(new TStringList), FActive(true)
{
	if(FileExists(FFileName))
	{
		List->LoadFromFile(FFileName);
	}
	List->Add("----------------------"+TDateTime::CurrentDateTime().DateTimeString()+"----------------------");
	ForceDirectories(ExtractFileDir(FFileName));
	List->SaveToFile(FFileName);
}
//---------------------------------------------------------------------------
__fastcall TLogFile::~TLogFile(void)
{
	delete List;
}
//---------------------------------------------------------------------------
void __fastcall TLogFile::Log(TLogType Type, String Text)
{
	if(FActive)
	{
		String TypeStr;
		if(Type == TLogType::Message)
			TypeStr = "[Message] ";
		if(Type == TLogType::Warning)
			TypeStr = "[Warning] ";
		if(Type == TLogType::Error)
			TypeStr = "[ERROR] ";
		List->Add(TypeStr+Text);
		ForceDirectories(ExtractFileDir(FFileName));
		List->SaveToFile(FFileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TLogFile::Log(String Text)
{
	Log(TLogType::Message, Text);
}
//---------------------------------------------------------------------------
void __fastcall TLogFile::Clear(void)
{
	List->Clear();
	List->SaveToFile(FFileName);
}
//---------------------------------------------------------------------------
String __fastcall TStringFlags::GetFlagValue(String Name)
{
	int Index = GetFlagIndex(Name);
	if(Index == -1)
		throw EArgumentException("Flag '"+Name+"' doesn't exist!");
	else
		return FFlags[Index].Value;
}
//---------------------------------------------------------------------------
void __fastcall TStringFlags::SetFlagValue(String Name, String Value)
{
	int Index = GetFlagIndex(Name);
	if(Index == -1)
		throw EArgumentException("Flag '"+Name+"' doesn't exist!");
	else
		FFlags[Index].Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TStringFlags::AddFlag(String Name, String Value)
{
	if(FlagExists(Name))
		throw EArgumentException("Flag '"+Name+"' already exists!");
	FFlags.Add(TStringMapType());
	FFlags.Last().Name = Name;
	FFlags.Last().Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TStringFlags::RemoveFlag(String Name)
{
	int Index = GetFlagIndex(Name);
	if(Index == -1)
		throw EArgumentException("Flag '"+Name+"' doesn't exist!");
	else
		FFlags.Delete(Index);
}
//---------------------------------------------------------------------------
bool __fastcall TStringFlags::FlagExists(String Name)
{
	return GetFlagIndex(Name) != -1;
}
//---------------------------------------------------------------------------
int __fastcall TStringFlags::GetFlagIndex(String Name)
{
	for(int i=0;i<FFlags.Count();i++)
	{
		if(FFlags[i].Name == Name)
		{
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
void __fastcall TStringFlags::Clear(void)
{
	FFlags.Clear();
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TStringFlags::ToXmlNode(void)
{
	_di_IXMLNode Node = CreateNode(FName);
	for(int i=0;i<FFlags.Count();i++)
	{
		_di_IXMLNode ChildNode = CreateNode("Flag");
		ChildNode->Attributes["Name"] = FFlags[i].Name;
		ChildNode->Attributes["Value"] = FFlags[i].Value;
		Node->ChildNodes->Add(ChildNode);
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TStringFlags::FromXmlNode(_di_IXMLNode Node)
{
	if(Node->LocalName != FName)
		throw EArgumentException("Node with name '"+Node->LocalName+"' doesn't fit to object from class '"+FName+"'!");
	Clear();
	for(int i=0;i<Node->ChildNodes->Count;i++)
	{
		_di_IXMLNode ChildNode = Node->ChildNodes->Get(i);
		FFlags.Add(TStringMapType());
		FFlags.Last().Name = ChildNode->Attributes["Name"];
		FFlags.Last().Value = ChildNode->Attributes["Value"];
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameSave::BeginSaveUpdate(void)
{
	if(UpdateCount == 0)
	{
		Document = new TXMLDocument(Application);
		Document->Active = true;
		if(FileExists(FFileName))
		{
			Document->LoadFromFile(FFileName);
		}
		else
		{
			Document->AddChild("Save");
		}
    }
	UpdateCount++;
}
//---------------------------------------------------------------------------
void __fastcall TGameSave::EndSaveUpdate(void)
{
	if(UpdateCount == 0)
		throw EArgumentException("'EndSaveUpdate' was called too many times!");
	UpdateCount--;
	if(UpdateCount == 0)
	{
		BeautifyXML(Document);
		ForceDirectories(ExtractFileDir(FFileName));
		Document->SaveToFile(FFileName);
		delete Document;
	}
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TGameSave::GetSaveNode(String NodeName)
{
	_di_IXMLNode Node = NULL;
	if(UpdateCount == 0)
	{
		Document = new TXMLDocument(Application);
		Document->Active = true;
		if(FileExists(FFileName))
		{
			Document->LoadFromFile(FFileName);
			Node = Document->DocumentElement->ChildNodes->FindNode(NodeName);
		}
		delete Document;
	}
	else
	{
		Node = Document->DocumentElement->ChildNodes->FindNode(NodeName);
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TGameSave::SetSaveNode(String NodeName, _di_IXMLNode Node)
{
	if(NodeName != Node->NodeName)
		throw EArgumentException("NodeName '"+NodeName+"' isn't equal to the name of node ('"+Node->NodeName+"')!");
	if(UpdateCount == 0)
	{
		Document = new TXMLDocument(Application);
		Document->Active = true;
		if(FileExists(FFileName))
		{
			Document->LoadFromFile(FFileName);
		}
		else
		{
			Document->AddChild("Save");
		}
	}
	_di_IXMLNode OldNode = Document->DocumentElement->ChildNodes->FindNode(NodeName);
	if(OldNode == NULL)
		Document->DocumentElement->ChildNodes->Add(Node);
	else
		Document->DocumentElement->ChildNodes->ReplaceNode(OldNode,Node);
	if(UpdateCount == NULL)
	{
		BeautifyXML(Document);
		ForceDirectories(ExtractFileDir(FFileName));
		Document->SaveToFile(FFileName);
		delete Document;
    }
}
//---------------------------------------------------------------------------
TGameManager* __fastcall TGameManager::Manager(void)
{
	if(FManager == NULL)
		throw EArgumentException("Game Manager is not created yet!");
	return FManager;
}
//---------------------------------------------------------------------------
String __fastcall GetAppDataDir(void)
{
	return String(getenv("APPDATA"))+"\\Resurrection\\";
}
//---------------------------------------------------------------------------
__fastcall TGameManager::TGameManager(TClass MainMenuGUI, TClass DefaultFrame)
	: FIsStarted(false), FGameSave(GetAppDataDir()+"CurrentSave.xml"), FOpenedFrameFlagName("OpenedFrame"),
	  FFrameParent(NULL), FOpenedFrame(NULL), FHintIcon(new TBitmap), ItemsRegistred(false),
	  BGPlayer(new TMediaPlayer(NULL)), BGTimer(new TTimer(NULL)), FLogFile(GetAppDataDir()+"GameLog.txt")
{
	FLogFile.Active = false;  //Logging deaktiviert
	BGTimer->OnTimer = BGTrackFinished;
	if(FManager != NULL)
		throw EArgumentException("Game Manager was already created!");
	if(MainMenuGUI == NULL)
		throw EArgumentException("Main Menu GUI must not be null!");
	if(!MainMenuGUI->InheritsFrom(__classid(TGameGUI)))
		throw EArgumentException("'"+MainMenuGUI->ClassName()+"' isn't inherited from 'TGameGUI'");
	if(DefaultFrame == NULL)
		throw EArgumentException("Default Frame must not be null!");
	if(!DefaultFrame->InheritsFrom(__classid(TGameFrame)))
		throw EArgumentException("'"+DefaultFrame->ClassName()+"' isn't inherited from 'TGameFrame'");
	FMainMenuGUI = MainMenuGUI;
	FDefaultFrame = DefaultFrame;
	FGlobalFlags.Name = "GlobalFlags";
	FManager = this;
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::KeyDown(TGameFrame *Sender, wchar_t Key)
{
	LogFile.Log("Key '"+String(Key)+"' pressed.");
	if(Key == ' ' && FOpenedFrame != NULL)
		FOpenedFrame->ShowHotspotHints(FHintIcon);
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::KeyUp(TGameFrame *Sender, wchar_t Key)
{
	LogFile.Log("Key '"+String(Key)+"' released.");
	if(Key == ' ' && FOpenedFrame != NULL)
		FOpenedFrame->HideHotspotHints();
}
//---------------------------------------------------------------------------
int __fastcall TGameManager::GetFrameIndex(String FrameClassName)
{
	for(int i=0;i<FFrames.Count();i++)
	{
		if(FFrames[i]->ClassName() == FrameClassName)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------
int __fastcall TGameManager::GetGUIIndex(String GUIClassName)
{
	for(int i=0;i<FGUIs.Count();i++)
	{
		if(FGUIs[i]->ClassName() == GUIClassName)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------
int __fastcall TGameManager::GetItemIndex(String ItemName)
{
	for(int i=0;i<FItemDataList.Count();i++)
	{
		if(FItemDataList[i]->ItemName == ItemName)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------
TGameFrame* __fastcall TGameManager::GetFrame(String FrameClassNameOrIndex)
{
	int Index = -1;
	try
	{
		Index = FrameClassNameOrIndex.ToInt();
	}
	catch(EConvertError &e)
	{
		Index = GetFrameIndex(FrameClassNameOrIndex);
	}
	if(Index == -1)
		throw EArgumentException("Frame '"+FrameClassNameOrIndex+"' doesn't exist!");
	else
		return FFrames[Index];
}
//---------------------------------------------------------------------------
TGameGUI* __fastcall TGameManager::GetGUI(String GUIClassNameOrIndex)
{
	int Index = -1;
	try
	{
		Index = GUIClassNameOrIndex.ToInt();
	}
	catch(EConvertError &e)
	{
		Index = GetGUIIndex(GUIClassNameOrIndex);
	}
	if(Index == -1)
		throw EArgumentException("GUI '"+GUIClassNameOrIndex+"' doesn't exist!");
	else
		return FGUIs[Index];
}
//---------------------------------------------------------------------------
IGameItemData* __fastcall TGameManager::GetItem(String ItemNameOrIndex)
{
	int Index = -1;
	try
	{
		Index = ItemNameOrIndex.ToInt();
	}
	catch(EConvertError &e)
	{
		Index = GetItemIndex(ItemNameOrIndex);
	}
	if(Index == -1)
		throw EArgumentException("Item '"+ItemNameOrIndex+"' doesn't exist!");
	else
		return FItemDataList[Index];
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::RegisterFrame(TGameFrame *Frame)
{
	if(FrameExists[Frame->ClassName()])
		throw EArgumentException("Frame '"+Frame->ClassName()+"' is already registred!");
	FFrames.Add(Frame);
	LogFile.Log("Frame '"+Frame->ClassName()+"' registred.");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::UnregisterFrame(TGameFrame *Frame)
{
	int Index = GetFrameIndex(Frame->ClassName());
	if(Index == -1)
		throw EArgumentException("Frame '"+Frame->ClassName()+"' isn't registred!");
	FFrames.Delete(Index);
	LogFile.Log("Frame '"+Frame->ClassName()+"' unregistred.");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::RegisterGUI(TGameGUI *GUI)
{
	if(GUIExists[GUI->ClassName()])
		throw EArgumentException("GUI '"+GUI->ClassName()+"' is already registred!");
	FGUIs.Add(GUI);
	LogFile.Log("GUI '"+GUI->ClassName()+"' registred.");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::UnregisterGUI(TGameGUI *GUI)
{
	int Index = GetGUIIndex(GUI->ClassName());
	if(Index == -1)
		throw EArgumentException("GUI '"+GUI->ClassName()+"' isn't registred!");
	FGUIs.Delete(Index);
	LogFile.Log("GUI '"+GUI->ClassName()+"' unregistred.");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::RegisterItem(IGameItemData *Item)
{
	if(ItemExists[Item->ItemName])
		throw EArgumentException("Item '"+Item->ItemName+"' is already registred!");
	FItemDataList.Add(Item);
	LogFile.Log("Item '"+Item->ItemName+"' registred.");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::UnregisterItem(IGameItemData *Item)
{
	int Index = GetItemIndex(Item->ItemName);
	if(Index == -1)
		throw EArgumentException("Item '"+Item->ItemName+"' isn't registred!");
	FItemDataList.Delete(Index);
	LogFile.Log("Item '"+Item->ItemName+"' unregistred.");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::OpenFrame(String FrameClassName, String OpenFlowName)
{
	LogFile.Log("Open Frame '"+FrameClassName+"' with OpenFlow '"+OpenFlowName+"'");
	int Index = GetFrameIndex(FrameClassName);
	if(Index == -1)
		throw EArgumentException("Frame '"+FrameClassName+"' isn't registred!");
	if(FFrames[Index] != FOpenedFrame)
	{
		if(FOpenedFrame != NULL)
		{
			FOpenedFrame->HideHotspotHints();
			FOpenedFrame->Parent = NULL;
			FOpenedFrame->Close();
		}
		FOpenedFrame = FFrames[Index];
		FOpenedFrame->Parent = FFrameParent;
		FOpenedFrame->SetFocus();
		FOpenedFrame->HideHotspotHints();
		LoadFrame(FOpenedFrame);
		if(FOpenedFrame->Background->BeforeOpenFlowList->ItemExists(OpenFlowName))
		{
			LogFile.Log("Start BeforeOpenFlow '"+OpenFlowName+"'");
			FOpenedFrame->Background->BeforeOpenFlowList->Items[OpenFlowName]->FlowList->Start();
		}
		FOpenedFrame->DoOpen();
		FOpenedFrame->Run();
		if(FOpenedFrame->Background->OpenFlowList->ItemExists(OpenFlowName))
		{
			LogFile.Log("Start OpenFlow '"+OpenFlowName+"'");
			FOpenedFrame->Background->OpenFlowList->Items[OpenFlowName]->FlowList->Start();
		}

		if(FOpenedFrame->Background->BackgroundTrack != "")
		{
			PlayTrack(FOpenedFrame->Background->BGTrackFileName(), FOpenedFrame->Background->BGTrackVolume);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::PlayTrack(String FileName, float Volume)
{
	if(FileName != "" && BGPlayer->FileName != FileName)
	{
		LogFile.Log("Play Background Track '"+FileName+"'");
		BGTimer->Enabled = false;
		BGPlayer->Stop();
		BGPlayer->FileName = FileName;
		BGPlayer->Volume = Volume;
		BGTimer->Interval = BGPlayer->Duration / 10000.0;
		BGTimer->Enabled = true;
		BGPlayer->Play();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::BGTrackFinished(TObject *Sender)
{
	LogFile.Log("Repeat Background Track");
	BGPlayer->CurrentTime = 0;
	BGPlayer->Play();
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::LoadGame(void)
{
	LogFile.Log("Loading game...");
	FGameSave.BeginSaveUpdate();
	_di_IXMLNode Node = FGameSave.SaveNode[FGlobalFlags.Name];
	if(Node != NULL)
	{
		LogFile.Log("Load Global Flags");
		FGlobalFlags.FromXmlNode(Node);
	}
	for(int i=0;i<FGUIs.Count();i++)
	{
		LoadGUI(FGUIs[i]);
	}
	for(int i=0;i<FFrames.Count();i++)
	{
		LoadFrame(FFrames[i]);
	}
	FGameSave.EndSaveUpdate();
	LogFile.Log("Game loaded");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::SaveGame(void)
{
	LogFile.Log("Saving game...");
	FGameSave.BeginSaveUpdate();
	LogFile.Log("Save Global Flags");
	FGameSave.SaveNode[FGlobalFlags.Name] = FGlobalFlags.ToXmlNode();
	for(int i=0;i<FGUIs.Count();i++)
	{
		SaveGUI(FGUIs[i]);
	}
	for(int i=0;i<FFrames.Count();i++)
	{
		SaveFrame(FFrames[i]);
	}
	FGameSave.EndSaveUpdate();
	LogFile.Log("Game saved");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::LoadFrame(TGameFrame *Frame)
{
	LogFile.Log("Load Frame '"+Frame->ClassName()+"'");
	_di_IXMLNode Node = FGameSave.SaveNode["Frames"];
	_di_IXMLNode FrameNode = NULL;
	if(Node != NULL)
	{
		LogFile.Log("Frame Node found");
		FrameNode = Node->ChildNodes->FindNode(Frame->ClassName());
	}
	if(FrameNode != NULL)
	{
		LogFile.Log("Frame loading...");
		Frame->FromXmlNode(FrameNode);
	}
	LogFile.Log("Frame loaded");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::SaveFrame(TGameFrame *Frame)
{
	LogFile.Log("Save Frame '"+Frame->ClassName()+"'");
	FGameSave.BeginSaveUpdate();
	_di_IXMLNode Node = FGameSave.SaveNode["Frames"];
	if(Node == NULL)
	{
		LogFile.Log("Create Frames Node");
		Node = CreateNode("Frames");
	}
	_di_IXMLNode OldNode = Node->ChildNodes->FindNode(Frame->ClassName());
	LogFile.Log("Frame Saving...");
	if(OldNode == NULL)
	{
		Node->ChildNodes->Add(Frame->ToXmlNode());
	}
	else
	{
		LogFile.Log("Old Node Found. Replacing...");
		Node->ChildNodes->ReplaceNode(OldNode,Frame->ToXmlNode());
	}
	FGameSave.SaveNode["Frames"] = Node;
	FGameSave.EndSaveUpdate();
	LogFile.Log("Frame '"+Frame->ClassName()+"' Saved");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::LoadGUI(TGameGUI *GUI)
{
	LogFile.Log("Loading GUI '"+GUI->ClassName()+"' ...");
	_di_IXMLNode Node = FGameSave.SaveNode["GUIs"];
	_di_IXMLNode GuiNode = NULL;
	if(Node != NULL)
		GuiNode = Node->ChildNodes->FindNode(GUI->ClassName());
	if(GuiNode != NULL)
	{
		LogFile.Log("GUI loading...");
		GUI->FromXmlNode(GuiNode);
	}
	LogFile.Log("GUI '"+GUI->ClassName()+"' loaded");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::SaveGUI(TGameGUI *GUI)
{
	LogFile.Log("Saving GUI '"+GUI->ClassName()+"' ...");
	FGameSave.BeginSaveUpdate();
	_di_IXMLNode Node = FGameSave.SaveNode["GUIs"];
	if(Node == NULL)
		Node = CreateNode("GUIs");
	_di_IXMLNode OldNode = Node->ChildNodes->FindNode(GUI->ClassName());
	LogFile.Log("GUI saving...");
	if(OldNode == NULL)
		Node->ChildNodes->Add(GUI->ToXmlNode());
	else
	{
		LogFile.Log("Old Node found. Replacing ...");
		Node->ChildNodes->ReplaceNode(OldNode,GUI->ToXmlNode());
	}
	FGameSave.SaveNode["GUIs"] = Node;
	FGameSave.EndSaveUpdate();
	LogFile.Log("GUI '"+GUI->ClassName()+"' saved");
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::DoStartGame(void)
{
	GUIs[FMainMenuGUI->ClassName()]->Close();
	if(FGlobalFlags.FlagExists(FOpenedFrameFlagName))
	{
		Frames[FGlobalFlags.FlagValue[FOpenedFrameFlagName]]->Open("Start Game");
	}
	else
	{
		Frames[FDefaultFrame->ClassName()]->Open("Start Game");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::DoStopGame(void)
{
	if(!FGlobalFlags.FlagExists(FOpenedFrameFlagName))
		FGlobalFlags.AddFlag(FOpenedFrameFlagName,"");
	FGlobalFlags.FlagValue[FOpenedFrameFlagName] = FOpenedFrame->ClassName();
	FOpenedFrame->Close();
	FOpenedFrame = NULL;
	for(int i=0;i<FGUIs.Count();i++)
	{
		FGUIs[i]->Close();
	}
	BGTimer->Enabled = false;
	BGPlayer->Stop();
	GUIs[FMainMenuGUI->ClassName()]->Open();
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::DoNewGame(void)
{
	DeleteFile(FGameSave.FileName);
	while(FFrames.Count() > 0)
	{
        delete FFrames[0];
	}
	FGlobalFlags.Clear();
	for(int i=0;i<FGUIs.Count();i++)
	{
        FGUIs[i]->Reset();
    }
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::SetGameSave(TGameSave GameSave)
{
	if(FIsStarted)
		throw EArgumentException("You can't change the GameSave while the game is running!");
	FGameSave = GameSave;
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::StartGame(void)
{
	if(!FIsStarted)
	{
		LogFile.Log("Starting Game ...");
		if(FFrames.Count() == 0)
			CreateFrames();
		if(!ItemsRegistred)
		{
			RegisterItems();
			ItemsRegistred = true;
		}
		FIsStarted = true;
		LoadGame();
		DoStartGame();
		LogFile.Log("Game started");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::StopGame(void)
{
	if(FIsStarted)
	{
		FIsStarted = false;
		LogFile.Log("Stopping Game ...");
		DoStopGame();
		SaveGame();
		LogFile.Log("Game stopped");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameManager::NewGame(void)
{
	if(!FIsStarted)
	{
		LogFile.Log("New Game");
		DoNewGame();
		StartGame();
	}
}
//---------------------------------------------------------------------------
