//---------------------------------------------------------------------------

#ifndef AnimationFlowH
#define AnimationFlowH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include "../StringArray.h"
#include "CustomFlow.h"
#include "../Objects/GameObject.h"
#include "../Stuff.h"
//---------------------------------------------------------------------------

class PACKAGE TAnimationBaseFlowItem : public TCustomFlowItem
{
private:

	TGameObject *FObject;
	TStringArray pics; //Liste von in der Animation enthaltenen Bildpfaden
	String FAnimation;
	int picSleep;     //FPS wird in Millisekunden Verzögerung zwischen Bildern umgerechnet

	float __fastcall GetFPS(void);
	void __fastcall SetFPS(float value);

	void __fastcall SetupPics(void);

	void __fastcall SetObject(TGameObject *Object);
	TGameObject* __fastcall GetObject(void)
	{
		if(FObject != NULL)
			return FObject;
		else
			return (TGameObject*)this->GetFlowList()->Owner;
	};


	virtual String __fastcall GetTexturePath(void);
	String __fastcall AnimationPath(void);

public:

	__fastcall TAnimationBaseFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);

protected:

	TStringArray __fastcall Pictures(void){ return pics; };

	void __fastcall AddFlowItems(TFlowItemAddProc AddProc);



	virtual void __fastcall AddAfterPic(int PicIndex, TFlowItemAddProc AddProc){};
	virtual void __fastcall AddBeforePic(int PicIndex, TFlowItemAddProc AddProc){};

	__property TGameObject* Object = {read=GetObject,write=SetObject};

	__property String Animation = {read=FAnimation,write=FAnimation};
	__property float FPS = {read=GetFPS,write=SetFPS};

__published:
	__property String TexturePath = {read=GetTexturePath};
};
//---------------------------------------------------------------------------
class PACKAGE TAnimationFlowItem : public TAnimationBaseFlowItem
{
public:
	__fastcall TAnimationFlowItem(TBasicCustomList* List) : TAnimationBaseFlowItem(List){};
__published:
	__property Object;

	__property Animation;
	__property FPS;
};
//---------------------------------------------------------------------------
#endif
