//---------------------------------------------------------------------------

#ifndef FakeGGHomeFrameH
#define FakeGGHomeFrameH
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
class TFakeGGHomeFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *Exit;
	THotspot *Goldgraeber;
	THotspot *Hotspot1;
	THotspot *Hotspot2;
	THotspot *Hotspot3;
	THotspot *Hotspot5;
	TPlayer *Player;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TFakeGGHomeFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFakeGGHomeFrame *FakeGGHomeFrame;
//---------------------------------------------------------------------------
#endif
