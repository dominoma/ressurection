//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TSleepFlowItem::TSleepFlowItem(TBasicCustomList* List)
	: TGameFlowItem(List), Timer(new TTimer(NULL))
{
	Timer->Enabled = false;
	Timer->OnTimer = TimerOnFinish;
}
//---------------------------------------------------------------------------
__fastcall TSleepFlowItem::~TSleepFlowItem(void)
{
	delete Timer;
}
//---------------------------------------------------------------------------
void __fastcall TSleepFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TSleepFlowItem)))
	{
		TSleepFlowItem *Item = (TSleepFlowItem*)Source;
		Sleep = Item->Sleep;
	}
	TGameFlowItem::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TSleepFlowItem::DoStart(void)
{
	Timer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TSleepFlowItem::DoStop(void)
{
	Timer->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TSleepFlowItem::DoPause(void)
{
	Timer->Enabled = false;
}
//---------------------------------------------------------------------------
bool __fastcall TSleepFlowItem::IsRunning(void)
{
	return Timer->Enabled;
}
//---------------------------------------------------------------------------
bool __fastcall TSleepFlowItem::IsPaused(void)
{
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TSleepFlowItem::TimerOnFinish(TObject *Sender)
{
	Finish();
}
//---------------------------------------------------------------------------
unsigned int __fastcall TSleepFlowItem::GetSleep(void)
{
	if(Timer == NULL)
		return 0;
	return Timer->Interval;
}
//---------------------------------------------------------------------------
void __fastcall TSleepFlowItem::SetSleep(unsigned int value)
{
	Timer->Interval = value;
}
//---------------------------------------------------------------------------

