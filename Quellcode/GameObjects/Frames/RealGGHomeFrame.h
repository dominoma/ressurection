//---------------------------------------------------------------------------

#ifndef RealGGHomeFrameH
#define RealGGHomeFrameH
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
class TRealGGHomeFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *Exit1;
	THotspot *Fireplace;
	THotspot *Nugget;
	THotspot *Hotspot1;
	THotspot *Hotspot2;
	THotspot *Bild;
	TPlayer *Player;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TRealGGHomeFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRealGGHomeFrame *RealGGHomeFrame;
//---------------------------------------------------------------------------
#endif
