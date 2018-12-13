//---------------------------------------------------------------------------

#ifndef InnerTrainFrameH
#define InnerTrainFrameH
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
#include "Person.h"
//---------------------------------------------------------------------------
class TInnerTrainFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	THotspot *Rohr;
	THotspot *Kohle;
	THotspot *Wasser;
	TExit *Exit;
	TPerson *Player;
	void __fastcall ObjectStateChanged(TObject *Sender);
	void __fastcall CoalFilled(TObject *Sender);
	void __fastcall RohrRepaired(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TInnerTrainFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInnerTrainFrame *InnerTrainFrame;
//---------------------------------------------------------------------------
#endif
