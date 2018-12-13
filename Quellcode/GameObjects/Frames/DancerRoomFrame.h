//---------------------------------------------------------------------------

#ifndef DancerRoomFrameH
#define DancerRoomFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Background.h"
#include "GameFrame.h"
#include "GameObject.h"
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include "ForegroundObj.h"
#include "Hotspot.h"
#include "Person.h"
#include "Exit.h"
#include "Player.h"
//---------------------------------------------------------------------------
class TDancerRoomFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TPerson *Bandit;
	TPerson *Tänzerin;
	TExit *Exit1;
	TPlayer *Player;
	void __fastcall BlackoutStarted(TObject *Sender);
	void __fastcall BlackoutStopped(TObject *Sender);
	void __fastcall HideBandit(TObject *Sender);
	void __fastcall Exit1Action(THotspot *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TDancerRoomFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDancerRoomFrame *DancerRoomFrame;
//---------------------------------------------------------------------------
#endif
