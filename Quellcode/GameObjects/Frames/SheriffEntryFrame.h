//---------------------------------------------------------------------------

#ifndef SheriffEntryFrameH
#define SheriffEntryFrameH
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
#include "Player.h"
//---------------------------------------------------------------------------
class TSheriffEntryFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *BlockExit;
	TExit *MarketExit;
	TPlayer *Player;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TSheriffEntryFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSheriffEntryFrame *SheriffEntryFrame;
//---------------------------------------------------------------------------
#endif
