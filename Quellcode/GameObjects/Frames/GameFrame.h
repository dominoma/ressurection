//---------------------------------------------------------------------------

#ifndef GameFrameH
#define GameFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Background.h"
#include "GameObject.h"
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include "ForegroundObj.h"
#include "Player.h"
#include "Exit.h"
#include "Hotspot.h"
#include "GameManager.h"
//---------------------------------------------------------------------------
class PACKAGE TGameFrame : public TFrame, public IXmlSerializable
{
friend void __fastcall TGameManager::DoStopGame(void);
friend void __fastcall TGameManager::OpenFrame(String FrameClassName, String OpenFlowName);
__published:	// Von der IDE verwaltete Komponenten
	TRectangle *BGRect;
	TBackground *Background;

private:	// Benutzer-Deklarationen

	bool isRunning;
	TRectangle *LockObj;
	TGameFlowCustomItem *LockedSender;

	bool __fastcall GetIsOpen(void);

	void __fastcall Run(void);
	void __fastcall Terminate(void);
	void __fastcall Close(void);

	void __fastcall LockedObjClick(TObject *Sender);
protected:
	virtual void __fastcall DoOpen(void){};
	virtual void __fastcall DoClose(void){};

	virtual void __fastcall LockedScreenClicked(void){};

	void __fastcall BeforeDestruction(void);
	void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	void __fastcall KeyUp(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);

	void __fastcall Paint(void);
public:		// Benutzer-Deklarationen

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	__classmethod virtual TGameFrame* __fastcall Instance(void);
	__classmethod virtual bool __fastcall IsInstance(void);

	TPlayer* __fastcall Player(void);
	bool __fastcall IsPlayer(void);

	__fastcall TGameFrame(TComponent* Owner);
	__fastcall ~TGameFrame(void);

	void __fastcall LockScreen(TGameFlowCustomItem* Sender=NULL, float Opacity=0);
	void __fastcall UnlockScreen(void);

	void __fastcall ShowHotspotHints(TBitmap *HintImg);
	void __fastcall HideHotspotHints(void);

	void __fastcall Open(String OpenFlowName);

	__property bool IsOpen = {read=GetIsOpen};
	__property Anchors;
};
//---------------------------------------------------------------------------
extern PACKAGE TGameFrame *GameFrame;
//---------------------------------------------------------------------------
#endif
