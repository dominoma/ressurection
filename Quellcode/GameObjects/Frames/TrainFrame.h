//---------------------------------------------------------------------------

#ifndef TrainFrameH
#define TrainFrameH
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
class TTrainFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *MarketPlaceExit;
	TPerson *Zugführer;
	THotspot *Wasserleine;
	TExit *LokExit;
	TPlayer *Player;
	void __fastcall WaterFilled(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TTrainFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTrainFrame *TrainFrame;
//---------------------------------------------------------------------------
#endif
