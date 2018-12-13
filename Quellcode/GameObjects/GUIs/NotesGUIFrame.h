//---------------------------------------------------------------------------

#ifndef NotesGUIFrameH
#define NotesGUIFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "GameGUIFrame.h"
#include <FMX.Ani.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Memo.hpp>
#include "ImageButton.h"
#include "CppScale.h"
//---------------------------------------------------------------------------
class PACKAGE TNotesGUIFrame : public TGameGUIFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TImage *BGImage;
	TMemo *Notes;
	TText *Heading;
	TImageButton *BStartGame;
	TCppScaledLayout *ScaledLayout;
	void __fastcall BStartGameClick(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TNotesGUIFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNotesGUIFrame *NotesGUIFrame;
//---------------------------------------------------------------------------
#endif
