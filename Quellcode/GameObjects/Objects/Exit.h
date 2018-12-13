//---------------------------------------------------------------------------

#ifndef ExitH
#define ExitH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "ForegroundObj.h"
#include "GameObject.h"
#include "Hotspot.h"
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class PACKAGE TExit : public THotspot
{
private:
protected:
	void __fastcall Loaded(void);
public:
	__fastcall TExit(TComponent* Owner);
__published:
};
//---------------------------------------------------------------------------
#endif
