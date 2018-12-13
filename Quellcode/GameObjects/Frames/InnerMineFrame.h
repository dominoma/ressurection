//---------------------------------------------------------------------------

#ifndef InnerMineFrameH
#define InnerMineFrameH
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
#include "Item.h"
#include "Exit.h"
#include "Player.h"
//---------------------------------------------------------------------------
class TInnerMineFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TGameItem *Kohlehaufen;
	TExit *Exit;
	TPlayer *Player;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TInnerMineFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInnerMineFrame *InnerMineFrame;
//---------------------------------------------------------------------------
#endif
