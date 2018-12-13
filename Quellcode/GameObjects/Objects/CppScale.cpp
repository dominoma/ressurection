//---------------------------------------------------------------------------

#include <fmx.h>

#pragma hdrstop

#include "CppScale.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TCppScaledLayout *)
{
	new TCppScaledLayout(NULL);
}
//---------------------------------------------------------------------------
__fastcall TCppScaledLayout::TCppScaledLayout(TComponent* Owner)
	: TControl(Owner)
{
	HitTest = false;
	FOriginalWidth = Width;
	FOriginalHeight = Height;
}
//---------------------------------------------------------------------------
void __fastcall TCppScaledLayout::DoRealign(void)
{
  if (Owner->ComponentState.Contains(csDesignInstance))
	 TControl::DoRealign();
  else
  {
	if(FNeedAlign)
      AlignObjects(this, Padding, FOriginalWidth, FOriginalHeight, FLastWidth, FLastHeight, FDisableAlign);

	RecalcAbsolute();
	FRecalcUpdateRect = true;
  }
}
//---------------------------------------------------------------------------
bool __fastcall TCppScaledLayout::GetChildrenMatrix(System::Math::Vectors::TMatrix &Matrix, bool &Simple)
{
	if (Owner->ComponentState.Contains(csDesignInstance))
	{
		OriginalHeight = Height;
		OriginalWidth = Width;
	}
	Matrix = TMatrix().Inverse();
	Matrix.m11 = Width / FOriginalWidth;
	Matrix.m22 = Height / FOriginalHeight;
	Simple = SameValue(Matrix.m11, 1, float(TEpsilon_Matrix)) && SameValue(Matrix.m22, 1, float(TEpsilon_Matrix));
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TCppScaledLayout::SetHeight(const float Value)
{
	TControl::SetHeight(Value);
  if (Owner->ComponentState.Contains(csDesignInstance))
	OriginalHeight = Height;
  else
	RecalcAbsolute();
}
//---------------------------------------------------------------------------
void __fastcall TCppScaledLayout::SetWidth(const float Value)
{
		TControl::SetWidth(Value);
  if (Owner->ComponentState.Contains(csDesignInstance))
	OriginalWidth = Width;
  else
	RecalcAbsolute();
}
//---------------------------------------------------------------------------
void __fastcall TCppScaledLayout::Paint(void)
{
	if (Owner->ComponentState.Contains(csDesignInstance) && !Locked && !FInPaintTo)
	{
		TRectF R = LocalRect;
		InflateRect(R, -0.5, -0.5);
		Canvas->DrawDashRect(R, 0, 0, AllCorners, AbsoluteOpacity, 0xA0909090);
	}
	TControl::Paint();
}
//---------------------------------------------------------------------------
void __fastcall TCppScaledLayout::SetOriginalWidth(const float Value)
{
	if(FOriginalWidth != Value)
  {
	FOriginalWidth = Value;
	if(FOriginalWidth < 1)
	  FOriginalWidth = 1;
	RecalcAbsolute();
  }
}
//---------------------------------------------------------------------------
void __fastcall TCppScaledLayout::SetOriginalHeight(const float Value)
{
	if(FOriginalHeight != Value)
  {
	FOriginalHeight = Value;
	if(FOriginalHeight < 1)
	  FOriginalHeight = 1;
	RecalcAbsolute();
  }
}
//---------------------------------------------------------------------------
namespace Cppscale
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TCppScaledLayout)};
		RegisterComponents(L"Standard", classes, 0);
	}
}
//---------------------------------------------------------------------------
