//---------------------------------------------------------------------------

#ifndef MoveFlowH
#define MoveFlowH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include "../StringArray.h"
#include "CustomFlow.h"
#include "../Objects/GameObject.h"
#include "../Stuff.h"
//---------------------------------------------------------------------------
class PACKAGE TMoveFlowItem : public TAnimationBaseFlowItem
{
private:


	float FLeftChange;
	float FTopChange;

protected:

	void __fastcall AddBeforePic(int PicIndex, TFlowItemAddProc AddProc);

public:

	__fastcall TMoveFlowItem(TBasicCustomList* List);

	void __fastcall Assign(TPersistent* Source);

__published:

	__property float LeftChange = {read=FLeftChange,write=FLeftChange};
	__property float TopChange = {read=FTopChange,write=FTopChange};

	__property Object;

	__property Animation;
	__property FPS;
};
//---------------------------------------------------------------------------
#endif
