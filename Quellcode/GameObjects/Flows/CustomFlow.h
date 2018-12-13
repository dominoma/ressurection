//---------------------------------------------------------------------------

#ifndef CustomFlowH
#define CustomFlowH
#include "GameFlow.h"
#include "Person.h"
//---------------------------------------------------------------------------
typedef TCustomListItem* __fastcall (__closure *TFlowItemAddProc)(TClass Class);
class PACKAGE TCustomFlowItem : public TGameFlowItem
{
private:
	TGameFlowList *FlowList; //Interne FlowList, in der die in AddFlowItems mit AddProc hinzugefüngten Items sich befinden

	void __fastcall FlowListStopped(TObject *Sender);

	void __fastcall DoStart(void);
	void __fastcall DoStop(void);
	void __fastcall DoPause(void);
protected:

	virtual void __fastcall AddFlowItems(TFlowItemAddProc AddProc)=0;

	template<class FlowItemClass> FlowItemClass* __fastcall AddItem(TFlowItemAddProc AddProc);

public:

	void __fastcall Jump(void);

	bool __fastcall IsRunning(void);
	bool __fastcall IsPaused(void);

	__fastcall TCustomFlowItem(TBasicCustomList* List);
	__fastcall ~TCustomFlowItem(void);
};
//---------------------------------------------------------------------------
template<class FlowItemClass>
FlowItemClass* __fastcall TCustomFlowItem::AddItem(TFlowItemAddProc AddProc)
{
	return (FlowItemClass*)AddProc(__classid(FlowItemClass));
}
//---------------------------------------------------------------------------
#endif
