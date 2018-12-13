//---------------------------------------------------------------------------

#ifndef GameGUIH
#define GameGUIH
#include "GameObject.h"
#include "GameGUIFrame.h"
#include "UniqueRegisterHlp.h"
//---------------------------------------------------------------------------
class PACKAGE TGameGUI : public TGameBase
{
private:
	bool isOpen;

	void __fastcall SetIsOpen(bool value);

	TGameGUIFrame *FGUIFrame;


protected:


	virtual void __fastcall DoOpen(void);
	virtual void __fastcall DoClose(void);

	void __fastcall Loaded(void);

	String __fastcall GetResourcePath(void);

public:
	__property TGameGUIFrame* GUIFrame = {read=FGUIFrame};
	__fastcall TGameGUI(TComponent *Owner, TGameGUIFrame *GUIFrame);
	__fastcall ~TGameGUI(void);

	virtual void __fastcall Reset(void){};

	TGameXmlNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(TGameXmlNode Node);

	void __fastcall Open(void);
	void __fastcall Close(void);

	__classmethod virtual TGameGUI* __fastcall Instance(void);
	__classmethod virtual bool __fastcall IsInstance(void);

__published:
	__property bool IsOpen = {read=isOpen,write=SetIsOpen,default=true};

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
