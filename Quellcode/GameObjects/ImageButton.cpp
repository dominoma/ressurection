//---------------------------------------------------------------------------

#include <fmx.h>

#pragma hdrstop

#include "ImageButton.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TImageButton *)
{
	new TImageButton(NULL);
}
//---------------------------------------------------------------------------
__fastcall TImageButton::TImageButton(TComponent* Owner)
	: TControl(Owner), FImage(new TImage(this)), FCaption(new TText(this)),
	FBmpNormal(new TBitmap()), FBmpHovered(new TBitmap()), FBmpPressed(new TBitmap()), FIsPressed(false), FStaysPressed(false)
{
	FImage->Parent = this;
	FImage->Stored = false;
	FImage->HitTest = false;
	FImage->Align = TAlignLayout::Client;
	FImage->WrapMode = TImageWrapMode::Stretch;

	FCaption->Parent = FImage;
	FCaption->Stored = false;
	FCaption->HitTest = false;
	FCaption->Align = TAlignLayout::Client;
	FCaption->TextSettings->HorzAlign = TTextAlign::Center;
	FCaption->TextSettings->VertAlign = TTextAlign::Center;
	FCaption->Text = "";

	FBmpNormal->OnChange = BitmapChanged;
	FBmpHovered->OnChange = BitmapChanged;
	FBmpPressed->OnChange = BitmapChanged;

	FMouseState = TMouseState::Normal;
}
//---------------------------------------------------------------------------
__fastcall TImageButton::~TImageButton(void)
{
	delete FBmpNormal;
	delete FBmpHovered;
	delete FBmpPressed;
	delete FCaption;
	delete FImage;
}
//---------------------------------------------------------------------------
bool __fastcall TImageButton::SetIsPressed(bool Value)
{
	if(FStaysPressed)
	{
		FIsPressed = Value;
		UpdateBitmap();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TImageButton::SetStaysPressed(bool Value)
{
	FStaysPressed = Value;
	/*if(!FStaysPressed && FMouseState != TMouseState::Pressed)
	{
		FIsPressed = false;
		UpdateBitmap();
	}*/
}
//---------------------------------------------------------------------------
void __fastcall TImageButton::UpdateBitmap(void)
{
	if(FIsPressed)
	{
		FImage->Bitmap->SetSize(FBmpPressed->Width, FBmpPressed->Height);
		FImage->Bitmap->CopyFromBitmap(FBmpPressed);
	}
	else if(FMouseState == TMouseState::Hovered)
	{
		FImage->Bitmap->SetSize(FBmpHovered->Width, FBmpHovered->Height);
		FImage->Bitmap->CopyFromBitmap(FBmpHovered);
	}
	else
	{
		FImage->Bitmap->SetSize(FBmpNormal->Width, FBmpNormal->Height);
		FImage->Bitmap->CopyFromBitmap(FBmpNormal);
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageButton::DoMouseEnter(void)
{
	TControl::DoMouseEnter();
	FMouseState = TMouseState::Hovered;
	if(!FStaysPressed)
	{
		FIsPressed = false;
		UpdateBitmap();
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageButton::DoMouseLeave(void)
{
	TControl::DoMouseLeave();
	FMouseState = TMouseState::Normal;
	if(!FStaysPressed)
	{
		FIsPressed = false;
		UpdateBitmap();
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageButton::Click(void)
{
	TControl::Click();
	if(FStaysPressed)
	{
		FIsPressed = !FIsPressed;
		UpdateBitmap();
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageButton::MouseDown(TMouseButton Button, TShiftState Shift, float X, float Y)
{
	if(Button == TMouseButton::mbLeft)
	{
		FMouseState = TMouseState::Pressed;
		if(!FStaysPressed)
		{
			FIsPressed = true;
			UpdateBitmap();
		}
	}
	TControl::MouseDown(Button,Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TImageButton::MouseUp(TMouseButton Button, TShiftState Shift, float X, float Y)
{
	TControl::MouseUp(Button,Shift,X,Y);
	if(Button == TMouseButton::mbLeft)
	{
		FMouseState = TMouseState::Hovered;
		if(!FStaysPressed)
		{
			FIsPressed = false;
			UpdateBitmap();
		}
	}
}
//---------------------------------------------------------------------------
namespace Imagebutton
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TImageButton)};
		RegisterComponents(L"Standard", classes, 0);
	}
}
//---------------------------------------------------------------------------
