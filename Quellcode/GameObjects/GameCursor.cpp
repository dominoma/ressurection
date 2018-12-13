//---------------------------------------------------------------------------

#pragma hdrstop
#define OEMRESOURCE
#include "GameCursor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
const TCursor TGameCursor::Default = crDefault;
const TCursor TGameCursor::Inspect = crCross;
const TCursor TGameCursor::Action = crHandPoint;
const TCursor TGameCursor::ActionInspect = crHourGlass;
const TCursor TGameCursor::TalkInspect = crNo;
const TCursor TGameCursor::Exit = crSizeAll;
TGameCursor *TGameCursor::Instance = NULL;
const AnsiString TGameCursor::Path = ".\\Resources\\Cursors";
//---------------------------------------------------------------------------
__fastcall TGameCursor::TGameCursor(void)
{
	HOldDefault = CopyCursor(LoadCursor(NULL, IDC_ARROW));
	HOldInspect = CopyCursor(LoadCursor(NULL, IDC_CROSS));
	HOldAction = CopyCursor(LoadCursor(NULL, IDC_HAND));
	HOldActionInspect = CopyCursor(LoadCursor(NULL, IDC_WAIT));
	HOldTalkInspect = CopyCursor(LoadCursor(NULL, IDC_NO));
	HOldExit = CopyCursor(LoadCursor(NULL, IDC_SIZEALL));

	SetSystemCursor(LoadCursorFromFile((Path+"\\Normal.cur").c_str()), OCR_NORMAL);
	SetSystemCursor(LoadCursorFromFile((Path+"\\Action.cur").c_str()), OCR_CROSS);
	SetSystemCursor(LoadCursorFromFile((Path+"\\Action.cur").c_str()), OCR_HAND);
	SetSystemCursor(LoadCursorFromFile((Path+"\\Action.cur").c_str()), OCR_WAIT);
	SetSystemCursor(LoadCursorFromFile((Path+"\\Talk.cur").c_str()), OCR_NO);
	SetSystemCursor(LoadCursorFromFile((Path+"\\Exit.cur").c_str()), OCR_SIZEALL);
}
//---------------------------------------------------------------------------
void __fastcall TGameCursor::BeforeDestruction(void)
{
	SetSystemCursor(HOldDefault, OCR_NORMAL);
	SetSystemCursor(HOldInspect, OCR_CROSS);
	SetSystemCursor(HOldAction, OCR_HAND);
	SetSystemCursor(HOldActionInspect, OCR_WAIT);
	SetSystemCursor(HOldTalkInspect, OCR_NO);
	SetSystemCursor(HOldExit, OCR_SIZEALL);

	DestroyCursor(HOldDefault);
	DestroyCursor(HOldInspect);
	DestroyCursor(HOldAction);
	DestroyCursor(HOldActionInspect);
	DestroyCursor(HOldTalkInspect);
}
//---------------------------------------------------------------------------
void __fastcall TGameCursor::Init(void)
{
	if(Instance == NULL)
	{
        Instance = new TGameCursor;
    }
}
//---------------------------------------------------------------------------
void __fastcall TGameCursor::Clear(void)
{
	delete Instance;
	Instance = NULL;
}
//---------------------------------------------------------------------------
