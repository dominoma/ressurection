//---------------------------------------------------------------------------

#ifndef EndScreenFrameH
#define EndScreenFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Background.h"
#include "GameFrame.h"
#include "GameObject.h"
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TEndScreenFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TText *Text1;
	TText *Text2;
	TText *Text3;
	void __fastcall GameEnded(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TEndScreenFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEndScreenFrame *EndScreenFrame;
//---------------------------------------------------------------------------
#endif
