//---------------------------------------------------------------------------

#ifndef GameGUIFrameH
#define GameGUIFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Types.hpp>
#include "UniqueRegisterHlp.h"
#include "XmlSerialize.h"
//---------------------------------------------------------------------------
class TGameGUI;
class PACKAGE TGameGUIFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TFloatAnimation *OpenCloseAnimation;
	void __fastcall OpenCloseAnimationFinish(TObject *Sender);
private:	// Benutzer-Deklarationen
	TGameGUI* __fastcall GetGUIComp(void){ return (TGameGUI*)Owner; };
protected:

public:		// Benutzer-Deklarationen
	__fastcall TGameGUIFrame(TComponent* Owner);
	__property TGameGUI* GUIComp = {read=GetGUIComp};
};
//---------------------------------------------------------------------------
extern PACKAGE TGameGUIFrame *GameGUIFrame;
//---------------------------------------------------------------------------
#endif
