//---------------------------------------------------------------------------

#ifndef StreetFrameH
#define StreetFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Background.h"
#include "GameFrame.h"
#include "GameObject.h"
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include "Exit.h"
#include "ForegroundObj.h"
#include "Hotspot.h"
#include "Person.h"
#include "Player.h"
//---------------------------------------------------------------------------
class TStreetFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *MarketExit;
	TExit *EntryExit;
	TExit *RealGGEntry;
	TExit *FakeGGEntry;
	TPerson *Goldgraeber;
	TForegroundObj *Tutorial;
	TPlayer *Player;
	void __fastcall TutorialStarted(TObject *Sender);
	void __fastcall GoldDiggerGoneTalked(TObject *Sender);
	void __fastcall MarketExitAction(THotspot *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TStreetFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStreetFrame *StreetFrame;
//---------------------------------------------------------------------------
#endif
