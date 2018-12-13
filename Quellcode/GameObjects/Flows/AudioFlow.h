//---------------------------------------------------------------------------

#ifndef AudioFlowH
#define AudioFlowH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Media.hpp>
#include "../StringArray.h"
#include "../Stuff.h"
#include "GameFlow.h"
//---------------------------------------------------------------------------
class PACKAGE TAudioFlowItem : public TGameFlowItem
{
	private:

		struct TAudioCaptionPart
		{
			String Caption; //Teil des Untertiteltextes
			int Duration;   //Anzeigedauer von Caption in ms
		};
		TArrayClass<TAudioCaptionPart> Captions;  //Liste der Untertitel-Textteile
		int CurrCaption;

		String caption;
		String speakerName;
		String audioFile;
		TForegroundObj *FObject;

		TMediaPlayer *Player;
		TTimer *Timer;

		void __fastcall TimerOnFinished(TObject *Sender);

		String __fastcall GetAudioFile(void);
		void __fastcall SetAudioFile(String value);

		String __fastcall GetAudioDir(void);
		String __fastcall GetFullAudioPath(void);

		void __fastcall DoStart(void);
		void __fastcall DoStop(void);
		void __fastcall DoPause(void);

		void __fastcall SplitCaption(void); //Teilt lange Untertiteltexte in mehrere kürzere Teile auf, die nacheinander angezeigt werden

	public:

		__fastcall TAudioFlowItem(TBasicCustomList* List);
		__fastcall ~TAudioFlowItem(void);

		void __fastcall Assign(TPersistent* Source);

		bool __fastcall IsRunning(void);
		bool __fastcall IsPaused(void);

	__published:

		__property String AudioFile = {read=GetAudioFile,write=SetAudioFile};
		__property String Caption = {read=caption,write=caption};
		__property String SpeakerName = {read=speakerName,write=speakerName};
		__property String AudioDir = {read=GetAudioDir};
		__property TForegroundObj* Object = {read=FObject,write=FObject};
		__property String FullAudioPath = {read=GetFullAudioPath};
};
//---------------------------------------------------------------------------
#endif
