//---------------------------------------------------------------------------

#ifndef CityEntryFrameH
#define CityEntryFrameH
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
class TCityEntryFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *TownExit;
	THotspot *Map;
	TForegroundObj *Tutorial;
	TPlayer *Player;
	void __fastcall StartGameEvent(TObject *Sender);
	void __fastcall MoveTutStarted(TObject *Sender);
	void __fastcall BackgroundFrameClosed(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TCityEntryFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCityEntryFrame *CityEntryFrame;
//---------------------------------------------------------------------------
#endif
