//---------------------------------------------------------------------------

#ifndef GameManagerH
#define GameManagerH
#include "XmlSerialize.h"
#include <FMX.Media.hpp>
//---------------------------------------------------------------------------
class TPlayer;
enum class TLogType {Message, Warning, Error};
//---------------------------------------------------------------------------
class TLogFile
{
private:
	String FFileName;
	TStringList *List;
	bool FActive;
public:
	__fastcall TLogFile(String FileName);
	__fastcall ~TLogFile(void);
	void __fastcall Log(TLogType Type, String Text);
	void __fastcall Log(String Text);
	void __fastcall Clear(void);

	__property bool Active = {read=FActive,write=FActive}; //Standardmäßig true
};
//---------------------------------------------------------------------------
class PACKAGE TStringFlags : public IXmlSerializable
{
private:
	struct TStringMapType
	{
		String Name, Value;
	};
	TArrayClass<TStringMapType> FFlags;

	String __fastcall GetFlagValue(String Name);
	void __fastcall SetFlagValue(String Name, String Value);

	int __fastcall GetFlagIndex(String Name);

	String FName;
public:

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	void __fastcall AddFlag(String Name, String Value);
	void __fastcall RemoveFlag(String Name);
	bool __fastcall FlagExists(String Name);

	void __fastcall Clear(void);

	__property String FlagValue[String Name] = {read=GetFlagValue,write=SetFlagValue};

	__property String Name = {read=FName,write=FName};

};
//---------------------------------------------------------------------------
class PACKAGE TGameSave
{
private:
	String FFileName;
	int UpdateCount;
	TXMLDocument *Document;

	_di_IXMLNode __fastcall GetSaveNode(String NodeName);
	void __fastcall SetSaveNode(String NodeName, _di_IXMLNode Node);
public:
	__fastcall TGameSave(String FileName) : FFileName(FileName), UpdateCount(0) {};
	void __fastcall BeginSaveUpdate(void);
	void __fastcall EndSaveUpdate(void);
	__property String FileName = {read=FFileName};
	__property _di_IXMLNode SaveNode[String NodeName] = {read=GetSaveNode,write=SetSaveNode};
};
//---------------------------------------------------------------------------
class TGameFrame;
class TGameGUI;
class IGameItemData;
//---------------------------------------------------------------------------
class PACKAGE TGameManager
{
friend TGameFrame;
private:
	TClass FMainMenuGUI;
	TClass FDefaultFrame;
	bool FIsStarted;
	bool ItemsRegistred;
	String FOpenedFrameFlagName;
	TFmxObject *FFrameParent;
	TGameFrame *FOpenedFrame;

	TMediaPlayer *BGPlayer; //
	TTimer *BGTimer;        //  Zuständig für das Abspielen einer Audiodatei in Dauerschleife

	TGameSave FGameSave;
	TStringFlags FGlobalFlags;
	TLogFile FLogFile;

	TBitmap *FHintIcon;

	TArrayClass<TGameGUI*> FGUIs;
	TArrayClass<TGameFrame*> FFrames;
	TArrayClass<IGameItemData*> FItemDataList;

	static TGameManager *FManager;

	TStringFlags& __fastcall GetGlobalFlags(void){ return FGlobalFlags; };
	TLogFile& __fastcall GetLogFile(void){ return FLogFile; };

	int __fastcall GetFrameIndex(String FrameClassName);
	int __fastcall GetGUIIndex(String GUIClassName);
	int __fastcall GetItemIndex(String ItemName);

	TGameFrame* __fastcall GetFrame(String FrameClassNameOrIndex);
	bool __fastcall GetFrameExists(String FrameClassName){ return GetFrameIndex(FrameClassName) != -1; };
	int __fastcall GetFrameCount(void){ return FFrames.Count(); };

	TGameGUI* __fastcall GetGUI(String GUIClassNameOrIndex);
	bool __fastcall GetGUIExists(String GUIClassName){ return GetGUIIndex(GUIClassName) != -1; };
	int __fastcall GetGUICount(void){ return FGUIs.Count(); };

	IGameItemData* __fastcall GetItem(String ItemNameOrIndex);
	bool __fastcall GetItemExists(String ItemName){ return GetItemIndex(ItemName) != -1; };
	int __fastcall GetItemCount(void){ return FItemDataList.Count(); };

	void __fastcall BGTrackFinished(TObject *Sender);

protected:
	virtual void __fastcall CreateFrames(void)=0;
	virtual void __fastcall RegisterItems(void){};
	virtual void __fastcall DoStartGame(void);
	virtual void __fastcall DoStopGame(void);
	virtual void __fastcall DoNewGame(void);
	virtual void __fastcall LoadGame(void);
	virtual void __fastcall KeyDown(TGameFrame *Sender, wchar_t Key);
	virtual void __fastcall KeyUp(TGameFrame *Sender, wchar_t Key);

	void __fastcall SetGameSave(TGameSave GameSave);
public:
	__fastcall TGameManager(TClass MainMenuGUI, TClass DefaultFrame);
	__fastcall ~TGameManager(void){ delete FHintIcon; delete BGPlayer; delete BGTimer; };

	void __fastcall PlayTrack(String FileName, float Volume);

	void __fastcall RegisterFrame(TGameFrame *Frame);
	void __fastcall UnregisterFrame(TGameFrame *Frame);
	void __fastcall RegisterGUI(TGameGUI *GUI);
	void __fastcall UnregisterGUI(TGameGUI *GUI);
	void __fastcall RegisterItem(IGameItemData *Item);
	void __fastcall UnregisterItem(IGameItemData *Item);

	void __fastcall OpenFrame(String FrameClassName, String OpenFlowName);

	virtual void __fastcall SaveGame(void);

	void __fastcall StartGame(void);
	void __fastcall StopGame(void);
	void __fastcall NewGame(void);

	void __fastcall LoadFrame(TGameFrame *Frame);
	void __fastcall SaveFrame(TGameFrame *Frame);

	void __fastcall LoadGUI(TGameGUI *GUI);
	void __fastcall SaveGUI(TGameGUI *GUI);

	static TGameManager* __fastcall Manager(void);
	static bool __fastcall IsCreated(void){ return FManager != NULL; };

	__property TClass MainMenuGUI = {read=FMainMenuGUI};
	__property TClass DefaultFrame = {read=FDefaultFrame};

	__property bool IsStarted = {read=FIsStarted};
	__property String OpenedFrameFlagName = {read=FOpenedFrameFlagName};
	__property TFmxObject *FrameParent = {read=FFrameParent,write=FFrameParent};

	__property TGameSave GameSave = {read=FGameSave};
	__property TStringFlags& GlobalFlags = {read=GetGlobalFlags};
	__property TLogFile& LogFile = {read=GetLogFile};

	__property TBitmap* HintIcon = {read=FHintIcon};

	__property TGameFrame* OpenedFrame = {read=FOpenedFrame};

	__property TGameFrame* Frames[String FrameClassNameOrIndex] = {read=GetFrame};
	__property bool FrameExists[String FrameClassName] = {read=GetFrameExists};
	__property int FrameCount = {read=GetFrameCount};

	__property TGameGUI* GUIs[String GUIClassNameOrIndex] = {read=GetGUI};
	__property bool GUIExists[String GUIClassName] = {read=GetGUIExists};
	__property int GUICount = {read=GetGUICount};

	__property IGameItemData* Items[String ItemNameOrIndex] = {read=GetItem};
	__property bool ItemExists[String ItemName] = {read=GetItemExists};
	__property int ItemCount = {read=GetItemCount};
};
//---------------------------------------------------------------------------
#endif
