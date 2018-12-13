//---------------------------------------------------------------------------

#ifndef ConversationFlowH
#define ConversationFlowH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Media.hpp>
#include "../StringArray.h"
#include "../Stuff.h"
#include "GameFlow.h"
#include "CustomFlow.h"
//---------------------------------------------------------------------------
class TConversationFlowItem;
class PACKAGE TConvPart : public TCollectionItem
{
private:
	String FAudioFile;
	String FCaption;

	String __fastcall GetAudioDir(void);
protected:
	String __fastcall DisplayName(void){ return FCaption; };
public:

	__fastcall TConvPart(TCollection *Owner);

	void __fastcall Assign(TPersistent* Source);

__published:

	__property String AudioFile = {read=FAudioFile,write=FAudioFile};
	__property String Caption = {read=FCaption,write=FCaption};
	__property String AudioDir = {read=GetAudioDir};
};
//---------------------------------------------------------------------------
class PACKAGE TConvParts : public TOwnedCollection
{
public:
	__fastcall TConvParts(TConversationFlowItem *Owner);
};
//---------------------------------------------------------------------------
class PACKAGE TConversationFlowItem : public TCustomFlowItem
{
private:
	TConvParts *FConvParts;
	TForegroundObj *FPerson;
	String FIdleAnimation;
	String FTalkAnimation;
	String FDialog;

	String __fastcall GetTexturePath(void);

	void __fastcall AddFlowItems(TFlowItemAddProc AddProc);

	void __fastcall SetConvParts(TConvParts *ConvParts){ FConvParts->Assign(ConvParts); };
protected:

public:
	__fastcall TConversationFlowItem(TBasicCustomList* List);
	__fastcall ~TConversationFlowItem(void);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property TConvParts* ConvParts = {read=FConvParts,write=SetConvParts};
	__property TForegroundObj* Person = {read=FPerson,write=FPerson};
	__property String IdleAnimation = {read=FIdleAnimation,write=FIdleAnimation};
	__property String TalkAnimation = {read=FTalkAnimation,write=FTalkAnimation};
	__property String Dialog = {read=FDialog,write=FDialog};

	__property String TexturePath = {read=GetTexturePath};

	__property LockScreen = {default=true};
};
//---------------------------------------------------------------------------
#endif
