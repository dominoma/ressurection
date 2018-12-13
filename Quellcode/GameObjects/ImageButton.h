//---------------------------------------------------------------------------

#ifndef ImageButtonH
#define ImageButtonH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Controls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TImageButton : public TControl
{
enum class TMouseState {Normal, Hovered, Pressed};
private:
	TImage *FImage;
	TText *FCaption;
	TBitmap *FBmpNormal;
	TBitmap *FBmpHovered;
	TBitmap *FBmpPressed;

	TMouseState FMouseState;
	bool FIsPressed;
	bool FStaysPressed;

	bool __fastcall SetIsPressed(bool Value);
	bool __fastcall SetStaysPressed(bool Value);

	void __fastcall UpdateBitmap(void);

	String __fastcall GetText(void){ return FCaption->Text; };
	void __fastcall SetText(String Text){ FCaption->Text = Text; };

	TFont* __fastcall GetFont(void){ return FCaption->Font; };
	void __fastcall SetFont(TFont *Font){ FCaption->Font->Assign(Font); };

	void __fastcall SetBmpNormal(TBitmap *Bmp){ FBmpNormal->Assign(Bmp); UpdateBitmap(); };
	void __fastcall SetBmpHovered(TBitmap *Bmp){ FBmpHovered->Assign(Bmp); UpdateBitmap(); };
	void __fastcall SetBmpPressed(TBitmap *Bmp){ FBmpPressed->Assign(Bmp); UpdateBitmap(); };
	void __fastcall SetMauseState(TMouseState MouseState){ if(ComponentState.Contains(csDesigning)){FMouseState = MouseState; UpdateBitmap();} };
	void __fastcall BitmapChanged(TObject *Sender){ UpdateBitmap(); };
protected:
	void __fastcall DoMouseEnter(void);
	void __fastcall DoMouseLeave(void);
	void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall Click(void);
	void __fastcall Loaded(void){ TControl::Loaded(); UpdateBitmap(); };
public:
	__fastcall TImageButton(TComponent* Owner);
	__fastcall ~TImageButton(void);
__published:

	__property TBitmap* BmpNormal = {read=FBmpNormal,write=SetBmpNormal};
	__property TBitmap* BmpHovered = {read=FBmpHovered,write=SetBmpHovered};
	__property TBitmap* BmpPressed = {read=FBmpPressed,write=SetBmpPressed};

	__property TMouseState MouseState = {read=FMouseState,write=SetMauseState,stored=false};
	__property bool IsPressed = {read=FIsPressed,write=SetIsPressed};
	__property bool StaysPressed = {read=FStaysPressed,write=SetStaysPressed};

	__property String Text = {read=GetText,write=SetText};
	__property TFont* Font = {read=GetFont,write=SetFont};

	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DesignVisible = {default=1};
	__property Height;
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property OnApplyStyleLookup;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
};
//---------------------------------------------------------------------------
#endif
