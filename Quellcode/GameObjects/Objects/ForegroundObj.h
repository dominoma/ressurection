//---------------------------------------------------------------------------

#ifndef ForegroundObjH
#define ForegroundObjH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include "GameObject.h"
#include "PropertyClasses.h"
#include "FlowLists.h"
//---------------------------------------------------------------------------
class PACKAGE TFlowListGameItem : public TFlowListNameSelItem
{
public:
	__fastcall TFlowListGameItem(TCollection *Owner);
};
//---------------------------------------------------------------------------
class PACKAGE TFlowListGameList : public TFlowListNameCollectionTmpl<TFlowListGameItem>
{
public:
	__fastcall TFlowListGameList(TGameObject *Owner);
};
//---------------------------------------------------------------------------
class PACKAGE TGameAnimationItem : public TFlowListGameItem
{
private:
	bool FSaveStatePos;
	TPropertyList *FPropList;

	void __fastcall SetPropList(TPropertyList *NewList){};
protected:
	void __fastcall DoFixup(void){ FPropList->Fixup(); TFlowListGameItem::DoFixup(); };
public:

	void __fastcall Assign(TPersistent* Source);
	bool __fastcall Equals(TObject* Obj);

	__fastcall TGameAnimationItem(TCollection *Owner);
	__fastcall ~TGameAnimationItem(void);

__published:
	__property bool SaveStatePos = {read=FSaveStatePos,write=FSaveStatePos}; //Gibt an, ob der Objektzustand gespeichert werden soll
	__property TPropertyList* StateProperties = {read=FPropList,write=SetPropList};
};
//---------------------------------------------------------------------------
class PACKAGE TGameAnimationList : public TFlowListNameSelCollectionTmpl<TGameAnimationItem>
{
typedef TFlowListNameSelCollectionTmpl<TGameAnimationItem> Inherited;
private:
	TOwnedPropertySet *FSavedProperties;

	void __fastcall SetSavedProperties(TPropertySet *NewSet){};

	void __fastcall SaveToProperties(String State);
	void __fastcall LoadFromProperties(String State);
protected:
	void __fastcall SetSelected(String NewName);
	void __fastcall DoStart(void);
public:
	__fastcall TGameAnimationList(TGameObject *Owner);
	__fastcall ~TGameAnimationList(void);

__published:
	__property TOwnedPropertySet* SavedProperties = {read=FSavedProperties,write=SetSavedProperties}; //Gibt an, welche Eigenschaften gespeichert werden sollen
	__property Selected;
};
//---------------------------------------------------------------------------
class PACKAGE TForegroundObj : public TGameObject
{
private:
	TGameAnimationList *FAnimations;
	TEventFlowList *FLoadFlow;
	TText *FConvCaption;
	TCalloutRectangle *BGBox;

	float FTextOffsetX;
	float FTextOffsetY;
	float FTextWidth;

	virtual void __fastcall SetTextOffsetX(float NewVal){ FTextOffsetX = NewVal; RearrangeText(); };
	virtual void __fastcall SetTextOffsetY(float NewVal){ FTextOffsetY = NewVal; RearrangeText(); };

	String __fastcall GetAnimation(void){ return FAnimations->Selected; };
	void __fastcall SetAnimation(String value){ FAnimations->Selected = value; };

	TOwnedPropertySet* __fastcall GetStateSavedProperties(void){ return FAnimations->SavedProperties; };
	void __fastcall SetStateSavedProperties(TOwnedPropertySet* Set){ FAnimations->SavedProperties = Set; };

	void __fastcall SetAnimations(TGameAnimationList *Animations){};
	void __fastcall SetLoadFlow(TEventFlowList *LoadFlow){};

	TColor __fastcall GetCaptColor(void){ return AlphaToNormalColor(FConvCaption->TextSettings->FontColor); };
	void __fastcall SetCaptColor(TColor NewColor){ FConvCaption->TextSettings->FontColor = NormalToAlphaColor(NewColor); };

	void __fastcall ReadAnimations(TReader *Reader);
	void __fastcall WriteAnimations(TWriter *Writer);
	void __fastcall ReadColor(TReader *Reader);
	void __fastcall WriteColor(TWriter *Writer);

	void __fastcall RearrangeText(void);
protected:
	void __fastcall DoStart(void);


	void __fastcall Paint(void);

	void __fastcall Loaded(void);

	void __fastcall DefineProperties(TFiler *Filer);
public:
	__fastcall TForegroundObj(TComponent* Owner);
	__fastcall ~TForegroundObj(void);

	void __fastcall DisplayCaption(String Caption);
__published:

	__property Height;
	__property Padding;
	__property Opacity;
	__property Left;
	__property Top;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Visible = {default=1};
	__property Width;

	__property TGameAnimationList* Animations = {read=FAnimations, write=SetAnimations};
	__property TEventFlowList* LoadFlow = {read=FLoadFlow, write=SetLoadFlow};

	__property String Animation = {read=GetAnimation,write=SetAnimation,stored=false};
	__property TOwnedPropertySet* AnimationSavedProperties = {read=GetStateSavedProperties,write=SetStateSavedProperties,stored=false};

	__property float TextOffsetX = {read=FTextOffsetX,write=SetTextOffsetX};
	__property float TextOffsetY = {read=FTextOffsetY,write=SetTextOffsetY};
	__property float TextWidth = {read=FTextWidth,write=FTextWidth};

	__property TColor CaptionColor = {read=GetCaptColor,write=SetCaptColor,stored=false};
};
//---------------------------------------------------------------------------
#endif
