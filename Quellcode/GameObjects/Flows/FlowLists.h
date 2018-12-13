//---------------------------------------------------------------------------

#ifndef FlowListsH
#define FlowListsH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "GameFlow.h"
#include <FMX.Types.hpp>
#include <System.Contnrs.hpp>
//---------------------------------------------------------------------------
class PACKAGE TVariadicFlowList : public TGameFlowList
{
private:

public:
	__fastcall TVariadicFlowList(TGameObject* Owner);
};
//---------------------------------------------------------------------------
class PACKAGE TEventFlowList : public TGameFlowList
{
protected:
	bool __fastcall IsClassAllowed(TClass Class);
public:
	__fastcall TEventFlowList(TGameObject* Owner);
};
//---------------------------------------------------------------------------
#endif
