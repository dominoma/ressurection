//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop

#pragma package(smart_init)

//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//
//---------------------------------------------------------------------------
__fastcall TAnimationBaseFlowItem::TAnimationBaseFlowItem(TBasicCustomList* List)
	: TCustomFlowItem(List), FObject(NULL), picSleep(1000)
{
}
//---------------------------------------------------------------------------
void __fastcall TAnimationBaseFlowItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TAnimationBaseFlowItem)))
	{
		TAnimationBaseFlowItem *Item = (TAnimationBaseFlowItem*)Source;
		FObject = Item->FObject;
		FAnimation = Item->FAnimation;
		picSleep = Item->picSleep;
	}
	TCustomFlowItem::Assign(Source);
}
//---------------------------------------------------------------------------
void __fastcall TAnimationBaseFlowItem::SetObject(TGameObject *Object)
{
	FObject = Object;
}
//---------------------------------------------------------------------------
void __fastcall TAnimationBaseFlowItem::SetupPics(void)
{
	if(GetObject() == NULL)
		throw EFlowItemError(this,"Object must not be null!");
	if(!DirectoryExists(AnimationPath()))
		throw EFlowItemError(this,"Directory '"+AnimationPath()+"' doesn't exist!");
	pics = GetFileList(AnimationPath(),"*.png",false,true);
	if(pics.Count() == 0)
		throw EFlowItemError(this, "No pics were found (full path: '"+AnimationPath()+"')");
}
//---------------------------------------------------------------------------
String __fastcall TAnimationBaseFlowItem::AnimationPath(void)
{
	if(GetObject() != NULL)
		return GetObject()->ResourcePath+"\\"+FAnimation;
}
//---------------------------------------------------------------------------
float __fastcall TAnimationBaseFlowItem::GetFPS(void)
{
	double scale = 0.01;  // round to nearest one-hundreth
	float value = 1000.0 / float(picSleep);
	return floor(value / scale + 0.5) * scale;
}
//---------------------------------------------------------------------------
void __fastcall TAnimationBaseFlowItem::SetFPS(float value)
{
	if(value == 0)
		throw EArgumentException("FPS must be bigger than 0");
	picSleep = 1000.0 / value;
}
//---------------------------------------------------------------------------
void __fastcall TAnimationBaseFlowItem::AddFlowItems(TFlowItemAddProc AddProc)
{
	SetupPics();
	for(int i=0;i<pics.Count();i++)
	{
		AddBeforePic(i,AddProc);

		TLoadPicFlowItem* NewPicFlow = AddItem<TLoadPicFlowItem>(AddProc);
		NewPicFlow->Object = GetObject();
		NewPicFlow->Picture = FAnimation+"\\"+pics[i];

		TSleepFlowItem *NewSleep = AddItem<TSleepFlowItem>(AddProc);
		NewSleep->Sleep = picSleep;

		AddAfterPic(i,AddProc);
	}
}
//---------------------------------------------------------------------------
String __fastcall TAnimationBaseFlowItem::GetTexturePath(void)
{
	if(GetObject() != NULL)
		return GetObject()->ResourcePath;
}
//---------------------------------------------------------------------------

