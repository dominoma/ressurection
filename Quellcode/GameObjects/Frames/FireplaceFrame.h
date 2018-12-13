//---------------------------------------------------------------------------

#ifndef FireplaceFrameH
#define FireplaceFrameH
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
class TFireplaceFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *Exit1;
	TPerson *Indianer;
	TExit *MineFrameEntry;
	TPlayer *Player;
	void __fastcall IndianerTConvGUIFlowList4Started(TObject *Sender);
	void __fastcall ThunderStarted(TObject *Sender);
	void __fastcall ThunderStopped(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TFireplaceFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFireplaceFrame *FireplaceFrame;
//---------------------------------------------------------------------------
#endif
