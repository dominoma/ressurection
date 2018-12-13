//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TExit *)
{
	new TExit(NULL);
}
//---------------------------------------------------------------------------
__fastcall TExit::TExit(TComponent* Owner)
	: THotspot(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TExit::Loaded(void)
{
	THotspot::Loaded(); Cursor = TGameCursor::Exit;
}
//---------------------------------------------------------------------------
namespace Exit
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TExit)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
