//---------------------------------------------------------------------------

#ifndef SheriffFrameH
#define SheriffFrameH
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
class TSheriffFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TExit *Exit1;
	TPerson *Sheriff;
	TPlayer *Player;
	void __fastcall SheriffTVariadicFlowList4Started(TObject *Sender);
	void __fastcall BackgroundFrameClosed(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TSheriffFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSheriffFrame *SheriffFrame;
//---------------------------------------------------------------------------
#endif
