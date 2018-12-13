//---------------------------------------------------------------------------

#ifndef MapCloseupFrameH
#define MapCloseupFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Background.h"
#include "GameFrame.h"
#include "GameObject.h"
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include "ForegroundObj.h"
#include "Exit.h"
#include "Hotspot.h"
//---------------------------------------------------------------------------
class TMapCloseupFrame : public TGameFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TForegroundObj *Tutorial;
	TExit *Exit1;
	THotspot *MineFrameEntryFound;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TMapCloseupFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMapCloseupFrame *MapCloseupFrame;
//---------------------------------------------------------------------------
#endif
