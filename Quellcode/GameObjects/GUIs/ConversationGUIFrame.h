//---------------------------------------------------------------------------

#ifndef ConversationGUIFrameH
#define ConversationGUIFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "GameGUIFrame.h"
#include <FMX.Ani.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class PACKAGE TConversationGUIFrame : public TGameGUIFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TImage *BGImage;
private:	// Benutzer-Deklarationen


public:		// Benutzer-Deklarationen

	__fastcall TConversationGUIFrame(TComponent* Owner);

	
};
//---------------------------------------------------------------------------
extern PACKAGE TConversationGUIFrame *ConversationGUIFrame;
//---------------------------------------------------------------------------
#endif
