//---------------------------------------------------------------------------

#ifndef MarketPlaceFrameH
#define MarketPlaceFrameH
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
#include "Exit.h"
#include "Hotspot.h"
#include "Person.h"
#include "Player.h"
//---------------------------------------------------------------------------
class TMarketPlaceFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *SaloonExit;
	TExit *SheriffExit;
	THotspot *Brunnen;
	TExit *TrainExit;
	TExit *DesertExit;
	TExit *Exit1;
	THotspot *Hotspot1;
	TPerson *Quacksalber;
	TPlayer *Player;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TMarketPlaceFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMarketPlaceFrame *MarketPlaceFrame;
//---------------------------------------------------------------------------
#endif
