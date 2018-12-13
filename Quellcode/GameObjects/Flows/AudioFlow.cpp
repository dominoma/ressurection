//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TAudioFlowItem::TAudioFlowItem(TBasicCustomList* List)
	: TGameFlowItem(List), Player(new TMediaPlayer(NULL)), Timer(new TTimer(NULL)), FObject(NULL)
{
	Timer->Enabled = false;
	Timer->OnTimer = TimerOnFinished;
}
//---------------------------------------------------------------------------
__fastcall TAudioFlowItem::~TAudioFlowItem(void)
{
	delete Player;
	delete Timer;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TAudioFlowItem)))
	{
		TAudioFlowItem *Item = (TAudioFlowItem*)Source;
		caption = Item->caption;
		speakerName = Item->speakerName;
		audioFile = Item->audioFile;
		FObject = Item->FObject;
	}
	TGameFlowItem::Assign(Source);
}
//---------------------------------------------------------------------------
String __fastcall TAudioFlowItem::GetAudioDir(void)
{
	if(FObject != NULL)
		return FObject->ResourcePath + "\\Audio";
}
//---------------------------------------------------------------------------
String __fastcall TAudioFlowItem::GetFullAudioPath(void)
{
	if(FileExists(audioFile))
		return audioFile;
	else
		return AudioDir + "\\" + audioFile;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFlowItem::SplitCaption(void)
{
	CurrCaption = 0;
	Captions.Clear();
	int sentenceBegin = 1;
	if(caption == "")
	{
		Captions.Add(TAudioCaptionPart());
		Captions.Last().Duration = Player->Duration / 10000.0;
	}
	else
	{
		for(int i=1;i<=caption.Length();i++)
		{
			if(i-sentenceBegin > 30 || i == caption.Length())
			{
				if(caption[i] == '.' || caption[i] == '?' || i == caption.Length() || caption[i] == ',')
				{
					Captions.Add(TAudioCaptionPart());
					Captions.Last().Caption = caption.SubString(sentenceBegin,i-sentenceBegin+1);
					int captLength = Captions.Last().Caption.Length();
					Captions.Last().Duration = Player->State == TMediaState::Playing ? (Player->Duration / 10000.0) * (float(captLength) / float(caption.Length())) : 75 * captLength;
					sentenceBegin = i + 1;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAudioFlowItem::DoStart(void)
{
	if(FObject == NULL)
		throw EFlowItemError(this,"Object must not be null!");
	if(FileExists(FullAudioPath))
	{
		try
		{
			if(Player->FileName != FullAudioPath)
			{
				Player->FileName = FullAudioPath;
			}
			if(FlowList->GameObject->IsRunning())
				Player->Play();
		}
		catch(Exception &e)
		{
			if(TGameManager::IsCreated())
				TGameManager::Manager()->LogFile.Log(TLogType::Warning, "Audio File '"+FullAudioPath+"' couldn't be played! Error: "+e.ToString());
		}
		catch(...)
		{
			if(TGameManager::IsCreated())
				TGameManager::Manager()->LogFile.Log(TLogType::Warning, "Audio File '"+FullAudioPath+"' couldn't be played!");
		}
	}
	else
	{
		if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log(TLogType::Warning, "Audio File '"+FullAudioPath+"' doesn't exist");
    }
	SplitCaption();
	Timer->Interval = Captions[CurrCaption].Duration;
	FObject->DisplayCaption(Captions[CurrCaption].Caption);
	Timer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFlowItem::DoStop(void)
{
	Timer->Enabled = false;
	Player->Stop();
	Player->CurrentTime = 0;
	FObject->DisplayCaption("");
	CurrCaption = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFlowItem::DoPause(void)
{
	Timer->Enabled = false;
	Player->Stop();
}
//---------------------------------------------------------------------------
bool __fastcall TAudioFlowItem::IsRunning(void)
{
	return Timer->Enabled;
}
//---------------------------------------------------------------------------
bool __fastcall TAudioFlowItem::IsPaused(void)
{
	return !IsRunning() && Player->CurrentTime > 0;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFlowItem::TimerOnFinished(TObject *Sender)
{
	CurrCaption++;
	if(CurrCaption < Captions.Count())
	{
		Timer->Interval = Captions[CurrCaption].Duration;
		FObject->DisplayCaption(Captions[CurrCaption].Caption);
		Timer->Enabled = true;
	}
	else
	{
		Finish();
	}
}
//---------------------------------------------------------------------------
String __fastcall TAudioFlowItem::GetAudioFile(void)
{
	return audioFile;
}
//---------------------------------------------------------------------------
void __fastcall TAudioFlowItem::SetAudioFile(String value)
{
	audioFile = value;
	//Player->CurrentTime = 0;
}
//---------------------------------------------------------------------------
