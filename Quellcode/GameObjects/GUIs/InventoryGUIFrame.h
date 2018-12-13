//---------------------------------------------------------------------------

#ifndef InventoryGUIFrameH
#define InventoryGUIFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "GameGUIFrame.h"
#include <FMX.Ani.hpp>
#include <FMX.Types.hpp>
#include "ImageButton.h"
#include <FMX.Objects.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TInventoryGUIFrame : public TGameGUIFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TImage *BGImage;
	TImageButton *ArrowLeft;
	TImage *ItemBox;
	TImageButton *ArrowRight;
	TImageButton *MenuButton;
	TImageButton *NotesButton;
	TImage *Splitter;
	TLayout *Content;
	TGridLayout *ItemContainer;
	void __fastcall MenuButtonClick(TObject *Sender);
	void __fastcall NotesButtonClick(TObject *Sender);
private:	// Benutzer-Deklarationen

public:		// Benutzer-Deklarationen

	__fastcall TInventoryGUIFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInventoryGUIFrame *InventoryGUIFrame;
//---------------------------------------------------------------------------
#endif
