//---------------------------------------------------------------------------

#include "GameObjects.h"
#pragma hdrstop
#include "GameCursor.h"
#include "GameForm.h"
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("GameForm.cpp", AdventureForm);
//---------------------------------------------------------------------------
class TAdventureManager : public TGameManager //Implementierung eines Game-Managers
{
protected:
	void __fastcall DoStartGame(void)
	{
		TGameManager::DoStartGame();
		TInventoryGUI::Instance()->Open();
	};
	void __fastcall CreateFrames(void)
	{
		new TSaloonFrame(NULL);
		new TMarketPlaceFrame(NULL);
		new TSheriffFrame(NULL);
		new TTrainFrame(NULL);
		new TStreetFrame(NULL);
		new TFireplaceFrame(NULL);
		new TCityEntryFrame(NULL);
		new TFakeGGHomeFrame(NULL);
		new TRealGGHomeFrame(NULL);
		new TMapCloseupFrame(NULL);
		new TInnerMineFrame(NULL);
		new TMineFrame(NULL);
		new TDancerRoomFrame(NULL);
		new TInnerTrainFrame(NULL);
		new TEndScreenFrame(NULL);
		new TPicCloseupFrame(NULL);
		new TSheriffEntryFrame(NULL);
	};
	void __fastcall RegisterItems(void)
	{
		new TGameItemReg("Friedenspfeife");
		new TGameItemReg("Rohrzange");
		new TGameItemReg("Schlüssel");
		new TGameItemReg("Rohr");
		new TGameItemReg("Sheriffstern");
		new TGameItemReg("Zellenschlüssel");
	};
public:
	__fastcall TAdventureManager(TClass MainMenuGUI, TClass DefaultFrame) : TGameManager(MainMenuGUI,DefaultFrame){};
};
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		RegisterClass(__classid(TForegroundObj));
		new TAdventureManager(__classid(TMainMenuGUI),__classid(TCityEntryFrame));  //Instanziierung des Game-Managers
		Application->CreateForm(__classid(TAdventureForm), &AdventureForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		TGameManager::Manager()->LogFile.Log(TLogType::Error, exception.ToString());  //Bei Exceptions während der Programmausführung wird die Fehlermeldung in die Log-datei geschrieben
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	TGameCursor::Clear(); //Beim Beenden des Programms werden die Cursors zurückgesetzt
	return 0;
}
//---------------------------------------------------------------------------
