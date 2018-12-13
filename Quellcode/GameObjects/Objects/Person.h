//---------------------------------------------------------------------------

#ifndef PersonH
#define PersonH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "ForegroundObj.h"
#include "GameObject.h"
#include "Hotspot.h"
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include "..\Flows\FlowTree.h"
//---------------------------------------------------------------------------
class PACKAGE TPerson : public THotspot
{
private:
	void __fastcall Action(void);
	TFlowTreeList *FConvTree;

	void __fastcall SetConvTree(TFlowTreeList *NewConv);
protected:
	String __fastcall GetResourcePath(void);
	void __fastcall Loaded(void);

public:
	__fastcall TPerson(TComponent* Owner);
	__fastcall ~TPerson(void);

	TGameXmlNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(TGameXmlNode Node);
__published:
	__property TFlowTreeList* ConvTree = {read=FConvTree,write=SetConvTree};
};
//---------------------------------------------------------------------------
#endif
