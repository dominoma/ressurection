//---------------------------------------------------------------------------

#ifndef MineFrameH
#define MineFrameH
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
#include "Exit.h"
#include "Player.h"
//---------------------------------------------------------------------------
class TMineFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	THotspot *Mine;
	TExit *Exit;
	TPlayer *Player;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TMineFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMineFrame *MineFrame;
//---------------------------------------------------------------------------
#endif
