//---------------------------------------------------------------------------

#ifndef MainMenuGUIH
#define MainMenuGUIH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "GameGUI.h"
//---------------------------------------------------------------------------
class PACKAGE TMainMenuGUI : public TGameGUI
{
private:
	String FBGTrack;
	float FBGVolume;
protected:
	void __fastcall DoOpen(void);
public:
	__fastcall TMainMenuGUI(TComponent* Owner);

	void __fastcall StartGame(void);
	void __fastcall NewGame(void);
__published:
	__property String BGTrack = {read=FBGTrack,write=FBGTrack};
	__property float BGVolume = {read=FBGVolume,write=FBGVolume};
};
//---------------------------------------------------------------------------
#endif
