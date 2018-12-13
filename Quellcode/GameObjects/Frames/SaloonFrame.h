//---------------------------------------------------------------------------

#ifndef SaloonFrameH
#define SaloonFrameH
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
#include "Person.h"
#include "Exit.h"
#include "Player.h"
//---------------------------------------------------------------------------
class TSaloonFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TPerson *Barmann;
	TPerson *Goldgraeber;
	TForegroundObj *Tisch1;
	TForegroundObj *Tisch2;
	TForegroundObj *Fass;
	TExit *BackRoomExit;
	TExit *Exit1;
	TPerson *Tänzerin;
	TPlayer *Player;
	TForegroundObj *Stuhl1;
	TForegroundObj *Candle;
	TForegroundObj *Light;
	TForegroundObj *Stuhl2;
	TForegroundObj *Stuhl3;
	void __fastcall GoldDiggerInvited(TObject *Sender);
	void __fastcall GoldDiggerDrinkMentioned(TObject *Sender);
	void __fastcall BarmannIndianaMentioned(TObject *Sender);
	void __fastcall BackgroundFrameClosed(TObject *Sender);
	void __fastcall GoneStateSelected(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TSaloonFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSaloonFrame *SaloonFrame;
//---------------------------------------------------------------------------
#endif
