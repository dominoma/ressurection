//---------------------------------------------------------------------------

#ifndef SleepFlowH
#define SleepFlowH
#include "GameFlow.h"
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class PACKAGE TSleepFlowItem : public TGameFlowItem
{
private:

	TTimer *Timer;

	void __fastcall TimerOnFinish(TObject *Sender);

	unsigned int __fastcall GetSleep(void);
	void __fastcall SetSleep(unsigned int value);

	void __fastcall DoStart(void);
	void __fastcall DoStop(void);
	void __fastcall DoPause(void);
public:
	bool __fastcall IsRunning(void);
	bool __fastcall IsPaused(void);

	__fastcall TSleepFlowItem(TBasicCustomList* List);
	__fastcall ~TSleepFlowItem(void);

	void __fastcall Assign(TPersistent* Source);
__published:
	__property unsigned int Sleep = {read=GetSleep,write=SetSleep};
};
#endif
