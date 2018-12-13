//---------------------------------------------------------------------------

#ifndef GameFormH
#define GameFormH
#include <FMX.Controls.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TreeView.hpp>
#include <FMX.Types.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include "ForegroundObj.h"
#include "GameObject.h"
#include "ConversationFlow.h"
#include "GameFlow.h"

#include "Hotspot.h"
#include "Person.h"
#include "CppScale.h"
#include <FMX.Platform.Win.hpp>
#include <FMX.Ani.hpp>
#include "Item.h"
#include <FMX.Menus.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Objects.hpp>
#include "ImageButton.h"
#include "ConversationGUIFrame.h"
#include "GameGUIFrame.h"
#include "InventoryGUIFrame.h"
#include "GameObjects.h"
#include "GameGUI.h"
#include "InventoryGUI.h"
#include "ConversationGUI.h"
#include "MainMenuGUI.h"
#include "NotesGUI.h"
//---------------------------------------------------------------------------
class TAdventureForm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TPanel *Panel1;
	TLayout *Layout1;
	TInventoryGUI *InventoryGUI;
	TConversationGUI *ConversationGUI;
	TMainMenuGUI *MainMenuGUI;
	TNotesGUI *NotesGUI;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);






private:	// Benutzer-Deklarationen


public:		// Benutzer-Deklarationen
	__fastcall TAdventureForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAdventureForm *AdventureForm;
//---------------------------------------------------------------------------
#endif
