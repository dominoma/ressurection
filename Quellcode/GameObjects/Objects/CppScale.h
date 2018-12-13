//---------------------------------------------------------------------------

#ifndef CppScaleH
#define CppScaleH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
//Klasse ist von Delphi in C++ übersetzt aus FMX.Layouts.pas (TScaledLayout)
//Ausnahme: statt csDesigning wird das Flag csDesignInstance im Set ComponentState asl
//Kriterium für die Skalierungsfunktion beachtet, damit die Skalierungsfunktion in zur Design-Zeit
//bearbeitbaren Komponenten, die das ScaledLayout in ihrer Oberfläche verwenden, aktiviert wird.
class PACKAGE TCppScaledLayout : public TControl
{
private:
	float FOriginalWidth;
	float FOriginalHeight;
	void __fastcall SetOriginalWidth(const float Value);
	void __fastcall SetOriginalHeight(const float Value);
protected:
	virtual void __fastcall DoRealign(void);
	virtual bool __fastcall GetChildrenMatrix(System::Math::Vectors::TMatrix &Matrix, bool &Simple);
	virtual void __fastcall SetHeight(const float Value);
	virtual void __fastcall SetWidth(const float Value);
	virtual void __fastcall Paint(void);
public:
	__fastcall TCppScaledLayout(TComponent* Owner);
__published:
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DesignVisible = {default=1};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property HitTest = {default=0};
	__property Padding;
	__property Opacity;
	__property float OriginalWidth = {read=FOriginalWidth, write=SetOriginalWidth};
	__property float OriginalHeight = {read=FOriginalHeight, write=SetOriginalHeight};
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
};
//---------------------------------------------------------------------------
#endif
