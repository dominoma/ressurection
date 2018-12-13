//---------------------------------------------------------------------------

#ifndef PicCloseupFrameH
#define PicCloseupFrameH
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
//---------------------------------------------------------------------------
class TPicCloseupFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	THotspot *Mine;
	THotspot *GGIndi;
	THotspot *Koordinaten;
	TText *Coords;
	TForegroundObj *Player;
	TExit *Exit1;
	void __fastcall KoordinatenTVariadicFlowList0Started(TObject *Sender);
	void __fastcall IndiFriendshipUnlocked(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TPicCloseupFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPicCloseupFrame *PicCloseupFrame;
//---------------------------------------------------------------------------
#endif
