//---------------------------------------------------------------------------
#include "GameObjects.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TGameBase::TGameBase(TComponent *Owner)
	: TControl(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGameBase::BeforeDestruction(void)
{
	if(ComponentState.Contains(csDesigning) && !Owner->ComponentState.Contains(csDestroying))
		RemoveDir(ResourcePath);
}
//---------------------------------------------------------------------------
void __fastcall TGameBase::SetName(const TComponentName NewName)
{
	if(ComponentState.Contains(csDesigning))
	{
		String OldTexturePath = ResourcePath;
		String OldName = Name;
		TControl::SetName(NewName);
		if(OldName == "" || !DirectoryExists(OldTexturePath))
			ForceDirectories(ResourcePath);
		else
			MoveFileW(OldTexturePath.c_str(),ResourcePath.c_str());
	}
	else
	{
		TControl::SetName(NewName);
    }
}
//---------------------------------------------------------------------------
TGameXmlNode __fastcall TGameBase::ToXmlNode(void)
{
	if(TGameManager::IsCreated())
		TGameManager::Manager()->LogFile.Log("Object '"+Name+"' saving to XML");
	return CreateNode(Name);
}
//---------------------------------------------------------------------------
void __fastcall TGameBase::FromXmlNode(TGameXmlNode Node)
{
	if(TGameManager::IsCreated())
		TGameManager::Manager()->LogFile.Log("Object '"+Name+"' loading from XML");
	if(Node->NodeName != Name)
	{
        throw EXmlNodeNameError(this,Node);
    }
}
//---------------------------------------------------------------------------
String __fastcall TGameBase::DesignPath(void)
{
	return "C:\\Users\\Dominik\\Documents\\Embarcadero\\Studio\\Projekte\\Adventure\\Win32\\Release";
}
//---------------------------------------------------------------------------
String __fastcall TGameBase::RunPath(void)
{
	return ".";
}
//---------------------------------------------------------------------------
String __fastcall TGameBase::Path(void)
{
	if(ComponentState.Contains(csDesigning) || (Owner != NULL && Owner->ComponentState.Contains(csDesigning)))
		return DesignPath();
	else
		return RunPath();
}
//---------------------------------------------------------------------------
String __fastcall TGameBase::ResourceRoot(void)
{
	return Path()+"\\Resources";
}
//---------------------------------------------------------------------------
__fastcall TGameObject::TGameObject(TComponent *Owner)
	: TGameBase(Owner), FFixedSide(TFixedSide::Width), FIsRunning(false)
{
	CanFocus = true;
	TabStop = true;
	FOriginalWidth = Width;
	FOriginalHeight = Height;
	if(!ComponentState.Contains(csDesigning) && !Owner->InheritsFrom(__classid(TGameFrame)))
		throw EArgumentException("Game-Component isn't placed on a TGameFrame-inherited frame!");
	imgObj = new TImage(this);
	imgObj->Parent = this;
	imgObj->CanFocus = false;
	imgObj->HitTest = false;
	imgObj->Align = TAlignLayout::Client;
	//imgObj->Locked = true;
	imgObj->Stored = false;
	imgObj->WrapMode = TImageWrapMode::Stretch;
}
//---------------------------------------------------------------------------
__fastcall TGameObject::~TGameObject(void)
{
	while (FObjFlows.Count() > 0)
		delete FObjFlows[0];
}
//---------------------------------------------------------------------------
TBackground* __fastcall TGameObject::GetBackground(void)
{
	for(TFmxObject *tmp=Parent;tmp!=NULL;tmp=tmp->Parent)
	{
		if(tmp->ClassType() == __classid(TBackground))
			return (TBackground*)tmp;
	}
	return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::DoRealign(void)
{
	//aus FMX.Layouts.pas (TScaledLayout) in C++ übersetzt
	if(ComponentState.Contains(csDesigning))
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
bool __fastcall TGameObject::GetChildrenMatrix(System::Math::Vectors::TMatrix &Matrix, bool &Simple)
{
	//aus FMX.Layouts.pas (TScaledLayout) in C++ übersetzt
	if (ComponentState.Contains(csDesigning))
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
void __fastcall TGameObject::SetHeight(const float Value)
{
	//aus FMX.Layouts.pas (TScaledLayout) in C++ übersetzt
	TControl::SetHeight(Value);
	if (ComponentState.Contains(csDesigning))
	{
		OriginalWidth = Width;
		OriginalHeight = Height;
	}
	else
		RecalcAbsolute();
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::SetWidth(const float Value)
{
	//aus FMX.Layouts.pas (TScaledLayout) in C++ übersetzt
	TControl::SetWidth(Value);
	if (ComponentState.Contains(csDesigning))
	{
		OriginalWidth = Width;
		OriginalHeight = Height;
	}
	else
		RecalcAbsolute();
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::Paint(void)
{
	//aus FMX.Layouts.pas (TScaledLayout) in C++ übersetzt
	if (ComponentState.Contains(csDesigning) && !Locked && !FInPaintTo)
	{
		TRectF R = LocalRect;
		InflateRect(R, -0.5, -0.5);
		Canvas->DrawDashRect(R, 0, 0, AllCorners, AbsoluteOpacity, 0xA0909090);
	}
	TControl::Paint();
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::SetOriginalWidth(const float Value)
{
	//aus FMX.Layouts.pas (TScaledLayout) in C++ übersetzt
	if(FOriginalWidth != Value)
	{
		FOriginalWidth = Value;
		if(FOriginalWidth < 1)
			FOriginalWidth = 1;
		RecalcAbsolute();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::SetOriginalHeight(const float Value)
{
	//aus FMX.Layouts.pas (TScaledLayout) in C++ übersetzt
	if(FOriginalHeight != Value)
	{
		FOriginalHeight = Value;
		if(FOriginalHeight < 1)
			FOriginalHeight = 1;
		RecalcAbsolute();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::CheckObjForReference(TGameObject *Obj)
{
	for(int i=0;i<Obj->FObjFlows.Count();i++)
	{
		TGameFlowList *CurrList = Obj->FObjFlows[i];
		for(int j=0;j<CurrList->Count;j++)
		{
			TGameFlowCustomItem *CurrItem = CurrList->Items[j];
			TPropList *List=NULL;
			int propCount=0;
			propCount = GetPropList(CurrItem,List);
			for(int i=0;i<propCount;i++)
			{
				TPropInfo *PropInfo = List->data[i];
				TTypeInfo *TypeInfo = *(PropInfo->PropType);
				String name = PropInfo->Name.operator AnsiString();
				if(TypeInfo->Kind == tkClass)
				{
					TObject *Reference = GetObjectProp(CurrItem,name);
					if(Reference == this)
					{
						SetObjectProp(CurrItem,name,NULL);
					}
				}
			}
			delete List;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::Loaded(void)
{
	if(TGameManager::IsCreated())
		TGameManager::Manager()->LogFile.Log("Object '"+Name+"' loading");
	TControl::Loaded();
	Start();
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::BeforeDestruction(void)
{
	for(int i=0;i<Owner->ComponentCount;i++)
	{
		if(Owner->Components[i]->InheritsFrom(__classid(TGameObject)))
		{
			CheckObjForReference((TGameObject*)Owner->Components[i]);
		}
	}
	Stop();
	TGameBase::BeforeDestruction();
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::Start(void)
{
	if(IsOwnerRunning())
	{
		DoStart();
		FIsRunning = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::Stop(void)
{
	DoStop();
	for(int i=0;i<FObjFlows.Count();i++)
		FObjFlows[i]->Stop();
	FIsRunning = false;
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::AddFlowToList(TGameFlowList* List)
{
	for(int i=0;i<FObjFlows.Count();i++)
	{
		if(FObjFlows[i] == List)
			throw EArgumentException("FlowList is already in the list!");
	}
	FObjFlows.Add(List);
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::DeleteFlowFromList(TGameFlowList* List)
{
	for(int i=0;i<FObjFlows.Count();i++)
	{
		if(FObjFlows[i] == List)
		{
			FObjFlows.Delete(i);
			return;
		}
	}
	throw EArgumentException("FlowList is not in the list!");
}
//---------------------------------------------------------------------------
bool __fastcall TGameObject::IsOwnerRunning(void)
{
	if(ComponentState.Contains(csDesigning))
		return !Owner->InheritsFrom(__classid(TGameFrame)) && !ComponentState.Contains(csLoading); //Zur Design-Zeit ist der Frame noch nich vollständig instanziiert, also noch kein Nachkomme von TGameFrame. Die Ausnahme bilden die Dummys, die in jeder von TGameFrame abgeleiteten Unit erzeugt werden. Diese sollen nichts ausführen, für GameObjects auf den Dummys gilt IsRunning() = false.
	else
		return ((TGameFrame*)Owner)->IsOpen;
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::LoadPic(String FileName)
{
	if(FileName == "")
	{
		imgObj->MultiResBitmap->Clear();
		PicLoaded(imgObj);
	}
	else if(FileExists(FileName))
	{
		imgObj->Bitmap->LoadFromFile(FileName);
		PicLoaded(imgObj);
		Resize();
	}
	else
	{
        if(TGameManager::IsCreated())
			TGameManager::Manager()->LogFile.Log(TLogType::Warning, "Texture File '"+FileName+"' doesn't exist!");
    }
}
//---------------------------------------------------------------------------
void __fastcall TGameObject::Resize(void)
{
	if(imgObj->Bitmap != NULL && !imgObj->Bitmap->IsEmpty() && imgObj->MultiResBitmap->Count != 0)
	{
		float ImgRatio = float(imgObj->Bitmap->Width)/float(imgObj->Bitmap->Height);
		if(FFixedSide == TFixedSide::Width)
		{
			Height = float(Width) / ImgRatio;
		}
		else
		{
			Width = ImgRatio * Height;
		}
	}
}
//---------------------------------------------------------------------------
String __fastcall TGameObject::GetResourcePath(void)
{
	return ResourceRoot() + "\\Frames\\"+Owner->Name+"\\"+Name;
}
//---------------------------------------------------------------------------
