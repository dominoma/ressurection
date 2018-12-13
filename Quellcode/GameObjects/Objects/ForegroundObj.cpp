//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Durch ValidCtrCheck wird sichergestellt, dass die erstellen Komponenten
// keine virtuellen Funktionen haben.
//

static inline void ValidCtrCheck(TForegroundObj *)
{
	new TForegroundObj(NULL);
}
//---------------------------------------------------------------------------
__fastcall TFlowListGameItem::TFlowListGameItem(TCollection *Owner)
	: TFlowListNameSelItem(Owner, new TVariadicFlowList((TGameObject*)Owner->Owner()))
{
}
//---------------------------------------------------------------------------
__fastcall TFlowListGameList::TFlowListGameList(TGameObject *Owner)
	: TFlowListNameCollectionTmpl<TFlowListGameItem>(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TGameAnimationItem::TGameAnimationItem(TCollection *Owner)
	: TFlowListGameItem(Owner), FSaveStatePos(false),
	  FPropList(new TPropertyList(GameObject, GameObject->Owner))
{
}
//---------------------------------------------------------------------------
__fastcall TGameAnimationItem::~TGameAnimationItem(void)
{
	delete FPropList;
}
//---------------------------------------------------------------------------
void __fastcall TGameAnimationItem::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TGameAnimationItem)))
	{
		TGameAnimationItem *Item = (TGameAnimationItem*)Source;
		FSaveStatePos = Item->FSaveStatePos;
		FPropList->Assign(Item->FPropList);
	}
	TFlowListGameItem::Assign(Source);
}
//---------------------------------------------------------------------------
bool __fastcall TGameAnimationItem::Equals(TObject* Obj)
{
	return true;
	if(Obj != NULL && Obj->InheritsFrom(__classid(TGameAnimationItem)))
	{
		TGameAnimationItem *Item = (TGameAnimationItem*)Obj;
		return TFlowListGameItem::Equals(Obj) && FSaveStatePos == Item->FSaveStatePos && FPropList->Equals(Item->FPropList);
	}
	else
		return false;
}
//---------------------------------------------------------------------------
__fastcall TGameAnimationList::TGameAnimationList(TGameObject *Owner)
	: Inherited(Owner), FSavedProperties(new TOwnedPropertySet(Owner))
{
}
//---------------------------------------------------------------------------
__fastcall TGameAnimationList::~TGameAnimationList(void)
{
	delete FSavedProperties;
}
//---------------------------------------------------------------------------
void __fastcall TGameAnimationList::SetSelected(String NewName)
{
	if(NewName != Selected)
	{
		String OldName = Selected;
		Inherited::SetSelected(NewName);
		if(IsFixedup)
		{
			if(ItemExists(OldName))
			{
				Items[OldName]->FlowList->Stop();
				if(Items[OldName]->SaveStatePos)
				{
					if(GameObject->ComponentState.Contains(csDesigning))
					{
						SaveToProperties(OldName);
					}
				}
			}
			if(!ItemExists(NewName))
				Inherited::SetSelected("");
			if(ItemExists(Selected))
			{
				Items[Selected]->FlowList->Start();
				if(Items[Selected]->SaveStatePos)
				{
					LoadFromProperties(Selected);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameAnimationList::SaveToProperties(String State)
{
	TPropertyList *PropList = Items[State]->StateProperties;
	PropList->KeepProperties(FSavedProperties);
	PropList->UpdateValues();
}
//---------------------------------------------------------------------------
void __fastcall TGameAnimationList::LoadFromProperties(String State)
{
	Items[State]->StateProperties->ApplyValues(FSavedProperties);
}
//---------------------------------------------------------------------------
void __fastcall TGameAnimationList::DoStart(void)
{
	if(Selected != "")
	{
		LoadFromProperties(Selected);
		Items[Selected]->FlowList->Start();
	}
	Inherited::DoStart();
}
//---------------------------------------------------------------------------
__fastcall TForegroundObj::TForegroundObj(TComponent* Owner)
	: TGameObject(Owner), FLoadFlow(new TEventFlowList(this)), FAnimations(new TGameAnimationList(this))
{
	HitTest = false;
	AnimationSavedProperties->AddToList("Width");
	AnimationSavedProperties->AddToList("Height");
	AnimationSavedProperties->AddToList("Left");
	AnimationSavedProperties->AddToList("Top");

	BGBox = new TCalloutRectangle(this);
	BGBox->Parent = this;
	BGBox->Stored = false;
	BGBox->HitTest = false;
	BGBox->CanFocus = false;
	BGBox->Fill->Color = 0xCCFFFFFF;

	FTextOffsetX = 0;
	FTextOffsetY = 0;
	FTextWidth = 200;

	FConvCaption = new TText(this);
	FConvCaption->Parent = BGBox;
	FConvCaption->Stored = false;
	FConvCaption->HitTest = false;
	FConvCaption->CanFocus = false;
	FConvCaption->Align = TAlignLayout::Client;
	FConvCaption->TextSettings->HorzAlign = TTextAlign::Center;
	FConvCaption->TextSettings->VertAlign = TTextAlign::Center;
	FConvCaption->Font->Family = "Comic Sans MS";
	FConvCaption->Font->Size = 15;
	FConvCaption->Color = claRed;
	RearrangeText();
}
//---------------------------------------------------------------------------
__fastcall TForegroundObj::~TForegroundObj(void)
{
	delete FAnimations;
	delete FLoadFlow;
	delete FConvCaption;
	delete BGBox;
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::Loaded(void)
{
	TGameObject::Loaded();
    FAnimations->Fixup();
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::RearrangeText(void)
{
	BGBox->CalloutPosition = TCalloutPosition::Bottom;
	BGBox->Padding->Rect = TRectF(5,0,5,BGBox->CalloutLength);
	BGBox->Height = 60;
	BGBox->Width = FConvCaption->Text == "" ? 0 : FTextWidth;
	BGBox->Position->X = (Width-BGBox->Width)/2.0 + FTextOffsetX;
	BGBox->Position->Y = -BGBox->Height + FTextOffsetY;
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::DisplayCaption(String Caption)
{
	FConvCaption->Text = Caption;
	RearrangeText();
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::Paint(void)
{
	TGameObject::Paint();
	FConvCaption->Font->Size = 15 ;
	if(FConvCaption->Text != "")
	{
		float linesHeight;
		do
		{
			FConvCaption->Font->Size--;
			Canvas->Font->Assign(FConvCaption->Font);
			float textWidth = Canvas->TextWidth(FConvCaption->Text);
			float lines = textWidth / FConvCaption->Width;
			linesHeight = lines * Canvas->TextHeight(FConvCaption->Text);
		}
		while(linesHeight + 20 > FConvCaption->Height);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::DoStart(void)
{
	FAnimations->Start();
	FLoadFlow->Start();
	TGameObject::DoStart();
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::ReadAnimations(TReader *Reader)
{
	Reader->ReadCollection(FAnimations);
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::WriteAnimations(TWriter *Writer)
{
	Writer->WriteCollection(FAnimations);
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::DefineProperties(TFiler *Filer)
{
	//Filer->DefineProperty("AnimationList",ReadAnimations,WriteAnimations,Filer->Ancestor == NULL);
	Filer->DefineProperty("CaptColor",ReadColor,WriteColor,true);
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::ReadColor(TReader *Reader)
{
	CaptionColor = Reader->ReadInteger();
}
//---------------------------------------------------------------------------
void __fastcall TForegroundObj::WriteColor(TWriter *Writer)
{
	Writer->WriteInteger(CaptionColor);
}
//---------------------------------------------------------------------------
namespace Foregroundobj
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TForegroundObj)};
		RegisterComponents(L"Adventure", classes, 0);
	}
}
//---------------------------------------------------------------------------
