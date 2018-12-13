//---------------------------------------------------------------------------

#ifndef MainMenuGUIFrameH
#define MainMenuGUIFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "GameGUIFrame.h"
#include <FMX.Ani.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Layouts.hpp>
#include "ImageButton.h"
#include "CppScale.h"
//---------------------------------------------------------------------------
class TMainMenuGUIFrame : public TGameGUIFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TImage *BGImage;
	TImageButton *BStartGame;
	TImageButton *BNewGame;
	TCppScaledLayout *BGLayout;
	TImageButton *CloseButton;
	TText *Text3;
	void __fastcall BStartGameClick(TObject *Sender);
	void __fastcall BNewGameClick(TObject *Sender);
	void __fastcall CloseButtonClick(TObject *Sender);
private:	// Benutzer-Deklarationen
protected:

public:		// Benutzer-Deklarationen
	__fastcall TMainMenuGUIFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainMenuGUIFrame *MainMenuGUIFrame;
//---------------------------------------------------------------------------
#endif
