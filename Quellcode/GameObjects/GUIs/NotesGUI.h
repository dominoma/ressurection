//---------------------------------------------------------------------------

#ifndef NotesGUIH
#define NotesGUIH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "GameGUI.h"
#include "GameObject.h"
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class PACKAGE TNotesGUI : public TGameGUI
{
private:
protected:
	void __fastcall DoOpen(void);
	void __fastcall DoClose(void);
public:
	__fastcall TNotesGUI(TComponent* Owner);
__published:
};
//---------------------------------------------------------------------------
#endif
