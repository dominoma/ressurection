//---------------------------------------------------------------------------

#ifndef GameCursorH
#define GameCursorH
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TGameCursor : public TObject
{
private:
	__fastcall TGameCursor(void);

	static TGameCursor *Instance;

	HCURSOR HOldDefault;
	HCURSOR HOldInspect;
	HCURSOR HOldAction;
	HCURSOR HOldActionInspect;
	HCURSOR HOldTalkInspect;
	HCURSOR HOldExit;

	void __fastcall BeforeDestruction(void);
public:
	static void __fastcall Init(void); //Lädt Cursors
	static void __fastcall Clear(void); //Setzt die Cursors zurück auf Windows-Voreinstellung

	static const TCursor Default;
	static const TCursor Inspect;
	static const TCursor Action;
	static const TCursor ActionInspect;
	static const TCursor TalkInspect;
	static const TCursor Exit;

	static const AnsiString Path;
};
#endif
