//---------------------------------------------------------------------------

#pragma hdrstop

#include "PropertyClasses.h"
#include "SerializeTools.h"
#include <fmx.h>
const String TPropertyList::XMLPrefix = "pl";
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//						+++TOwnedProperty+++
//---------------------------------------------------------------------------
__fastcall TPropertyBase::TPropertyBase(TPropertyList *Owner)
	: FParentList(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyBase::Equals(TObject* Obj)
{
	if(Obj->ClassType() != TPropertyBase::ClassType())
		return false;
	TPropertyBase *Prop = (TPropertyBase*)Obj;
	_di_IXMLNode thisNode = ToXmlNode();
	_di_IXMLNode otherNode = Prop->ToXmlNode();
	return XMLNodesEqual(thisNode,otherNode);
}
//---------------------------------------------------------------------------
void __fastcall TPropertyBase::Assign(TPersistent* Source)
{
	if(Source != NULL && Source->InheritsFrom(__classid(TPropertyBase)))
	{
		TPropertyBase *Item = (TPropertyBase*)Source;
		FromXmlNode(Item->ToXmlNode());
	}
	else
		TPersistent::Assign(Source);
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyBase::PropertyExists(void)
{
	return Object != NULL && GetPropInfo(Object,FName) != NULL;
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyBase::IsDefault(void)
{
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyBase::GetIsStored(void)
{
	if(!PropertyExists())
		return false;
	return IsStoredProp(Object, FName);
}
//---------------------------------------------------------------------------
TPropInfo __fastcall TPropertyBase::GetPropertyInfo(void)
{
	if(!PropertyExists())
		throw EArgumentException("Property '"+FName+"' doesn't exist! You can't use PropertyInfo!");
	return *GetPropInfo(Object,FName);
}
//---------------------------------------------------------------------------
TTypeInfo __fastcall TPropertyBase::GetTypeInfo(void)
{
	if(!PropertyExists())
		throw EArgumentException("Property '"+FName+"' doesn't exist! You can't use TypeInfo!");
	return **PropertyInfo.PropType;
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyBase::IsReadOnly(void)
{
	return PropertyInfo.SetProc == NULL;
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TPropertyBase::ToXmlNode(void)
{
	_di_IXMLNode Node = CreateNode(TPropertyList::XMLPrefix+":"+ClassName());
	Node->Attributes["Name"] = FName;
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyBase::FromXmlNode(_di_IXMLNode Node)
{
	if(Node->LocalName != ClassName())
		throw EArgumentException("Node '"+Node->LocalName+"' doesnt fit to property of class '"+ClassName()+"'!");
	if(Node->Prefix != TPropertyList::XMLPrefix)
		throw EArgumentException("Invalid prefix (want: '"+TPropertyList::XMLPrefix+"', got: '"+Node->Prefix+"')");
	Name = Node->Attributes["Name"];
	if(ParentList->ApplyAfterLoading && !IsReadOnly())
		ApplyValue();
}
//---------------------------------------------------------------------------
void __fastcall TPropertyBase::SetName(String NewName)
{
	if(Object != NULL && GetPropInfo(Object,NewName) == NULL)
		throw EArgumentException("Property '"+Name+"' is not a valid property!");
	FName = NewName;
	if(!IsPropertyFitting())
		throw EArgumentException("Property '"+Name+"' forsn't fit to it's type!");
	UpdateValue();
}
//---------------------------------------------------------------------------
TPersistent* __fastcall TPropertyBase::GetOwner(void)
{
	return FParentList;
}
//---------------------------------------------------------------------------
TPersistent* __fastcall TPropertyBase::GetObject(void)
{
	if(FParentList == NULL)
		return NULL;
	else
		return FParentList->Owner;
}
//---------------------------------------------------------------------------
//						+++TFixupProperty+++
//---------------------------------------------------------------------------
__fastcall TFixupProperty::TFixupProperty(TPropertyList *Owner)
	: TPropertyBase(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFixupProperty::AfterConstruction(void)
{
	if(IsFixedup())
		DoFixup();
}
//---------------------------------------------------------------------------
bool __fastcall TFixupProperty::IsFixedup(void)
{
	return ParentList->IsFixedup();
}
//---------------------------------------------------------------------------
//						+++TOwnedProperty+++
//---------------------------------------------------------------------------
__fastcall TOwnedProperty::TOwnedProperty(TPropertyList *ParentList, TComponent *Owner)
	: TFixupProperty(ParentList), FOwner(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOwnedProperty::SetOwner(TComponent *Owner)
{
	FOwner = Owner;
}
//---------------------------------------------------------------------------
//						+++TReferenceProperty+++
//---------------------------------------------------------------------------
__fastcall TReferenceProperty::TReferenceProperty(TPropertyList *ParentList, TComponent *Owner)
	: TOwnedProperty(ParentList,Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TReferenceProperty::IsDefault(void)
{
	return int(Value) == PropertyInfo.Default;
}
//---------------------------------------------------------------------------
bool __fastcall TReferenceProperty::IsPropertyFitting(void)
{
	TObject *Obj = GetObjectProp(Object,Name);
	return TypeInfo.Kind == tkClass && (Obj == NULL || Obj->InheritsFrom(__classid(TComponent)));
}
//---------------------------------------------------------------------------
void __fastcall TReferenceProperty::DoFixup(void)
{
	if(ParentList->ApplyAfterLoading)
		ApplyValue();
}
//---------------------------------------------------------------------------
TComponent* __fastcall TReferenceProperty::GetValue(void)
{
	if(!IsFixedup())
		throw EArgumentException("Property isn't fixed up!");
	if(Owner != NULL && FValueStr != "")
	{
		String ValueStr = FValueStr;
		ValueStr += ".";
		TComponent *retValue = Owner;
		while(ValueStr.Pos("."))
		{
			String SubComp = ValueStr.SubString(1,ValueStr.Pos(".")-1);
			ValueStr.Delete(1,ValueStr.Pos("."));
			retValue = retValue->FindComponent(SubComp);
		}
		return retValue;
	}
	else
		return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TReferenceProperty::SetValue(TComponent *Value)
{
	if(Value == NULL)
		FValueStr = "";
	else
		FValueStr = Value->GetNamePath();
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TReferenceProperty::ToXmlNode(void)
{
	_di_IXMLNode Node = TOwnedProperty::ToXmlNode();
	Node->Attributes["Value"] = FValueStr;
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TReferenceProperty::FromXmlNode(_di_IXMLNode Node)
{
	TOwnedProperty::FromXmlNode(Node);
	FValueStr = Node->Attributes["Value"];
	if(IsFixedup())
		DoFixup();
}
//---------------------------------------------------------------------------
void __fastcall TReferenceProperty::UpdateValue(void)
{
	TObject *Obj = GetObjectProp(Object,Name);
	if(Obj != NULL && !Obj->InheritsFrom(__classid(TComponent)))
		throw EArgumentException("Property '"+Name+"' is not inherited from TComponent!");
	Value = (TComponent*)Obj;
}
//---------------------------------------------------------------------------
void __fastcall TReferenceProperty::ApplyValue(void)
{
	if(IsFixedup())
		SetObjectProp(Object,Name,Value);
}
//---------------------------------------------------------------------------
//						+++TMethodProperty+++
//---------------------------------------------------------------------------
__fastcall TMethodProperty::TMethodProperty(TPropertyList *ParentList, TComponent *Owner)
	: TOwnedProperty(ParentList,Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TMethodProperty::IsDefault(void)
{
	return Value == "";
}
//---------------------------------------------------------------------------
bool __fastcall TMethodProperty::IsPropertyFitting(void)
{
	return TypeInfo.Kind == tkMethod;
}
//---------------------------------------------------------------------------
void __fastcall TMethodProperty::DoFixup(void)
{

}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TMethodProperty::ToXmlNode(void)
{
	_di_IXMLNode Node = TOwnedProperty::ToXmlNode();
	Node->Attributes["Value"] = FValue;
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TMethodProperty::FromXmlNode(_di_IXMLNode Node)
{
	TOwnedProperty::FromXmlNode(Node);
	FValue = Node->Attributes["Value"];
}
//---------------------------------------------------------------------------
void __fastcall TMethodProperty::UpdateValue(void)
{
	Method = GetMethodProp(Object,Name);
}
//---------------------------------------------------------------------------
void __fastcall TMethodProperty::ApplyValue(void)
{
	SetMethodProp(Object,Name,Method);
}
//---------------------------------------------------------------------------
TMethod __fastcall TMethodProperty::GetObjMethod(void)
{
	TMethod Method;
	Method.Data = Owner;
	Method.Code = Owner->MethodAddress(FValue);
	return Method;
}
//---------------------------------------------------------------------------
void __fastcall TMethodProperty::SetObjMethod(TMethod Value)
{
	FValue = Owner->MethodName(Value.Code);
}
//---------------------------------------------------------------------------
//						+++TProperty+++
//---------------------------------------------------------------------------
__fastcall TProperty::TProperty(TPropertyList *Owner)
	: TPropertyBase(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TProperty::IsDefault(void)
{
	try
	{
		int OrdVal = FValue;
		return OrdVal == PropertyInfo.Default;
	}
	catch(...)
	{
		return false;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TProperty::IsPropertyFitting(void)
{
	return TypeInfo.Kind != tkClass && TypeInfo.Kind != tkMethod;
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TProperty::ToXmlNode(void)
{
	_di_IXMLNode Node = TPropertyBase::ToXmlNode();
	String buf = FValue;
	Node->Attributes["Value"] = buf.SubString(1,100);
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TProperty::FromXmlNode(_di_IXMLNode Node)
{
	TPropertyBase::FromXmlNode(Node);
	Value = Node->Attributes["Value"].operator UnicodeString();
}
//---------------------------------------------------------------------------
void __fastcall TProperty::UpdateValue(void)
{
	if(Object == NULL)
		throw EArgumentException("Can't update value with Owner set to null!");
	if(GetPropInfo(Object,Name) == NULL)
		throw EArgumentException("Property '"+Name+"' doesn't exist!");
	FValue = GetPropValue(Object,Name);
}
//---------------------------------------------------------------------------
void __fastcall TProperty::ApplyValue(void)
{
	if(Object == NULL)
		throw EArgumentException("Can't update value with Owner set to null!");
	if(GetPropInfo(Object,Name) == NULL)
		throw EArgumentException("Property '"+Name+"' doesn't exist!");
	SetPropValue(Object,Name,FValue);
}
//---------------------------------------------------------------------------
//						+++TClassProperty+++
//---------------------------------------------------------------------------
__fastcall TClassProperty::TClassProperty(TPropertyList *Owner)
	: TFixupProperty(Owner), FValue(new TPropertyList(NULL,Owner->ObjectOwner))
{
}
//---------------------------------------------------------------------------
__fastcall TClassProperty::~TClassProperty(void)
{
	delete FValue;
}
//---------------------------------------------------------------------------
void __fastcall TClassProperty::DoFixup(void)
{
	FValue->Fixup();
}
//---------------------------------------------------------------------------
bool __fastcall TClassProperty::IsDefault(void)
{
	for(int i=0;i<FValue->Count();i++)
	{
		if(!FValue->Property[FValue->NameAtPos(i)]->IsDefault())
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TClassProperty::IsPropertyFitting(void)
{
	TObject *Obj = GetObjectProp(Object,Name);
	return TypeInfo.Kind == tkClass && Obj != NULL && !Obj->InheritsFrom(__classid(TComponent));
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TClassProperty::ToXmlNode(void)
{
	_di_IXMLNode Node = TPropertyBase::ToXmlNode();
	_di_IXMLNode PropNode = FValue->ToXmlNode();
	for(int i=0;i<PropNode->ChildNodes->Count;i++)
	{
		Node->ChildNodes->Add(PropNode->ChildNodes->Get(i));
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TClassProperty::FromXmlNode(_di_IXMLNode Node)
{
	TPropertyBase::FromXmlNode(Node);
	_di_IXMLNode PropNode = CreateNode("PropertyList");
	for(int i=0;i<Node->ChildNodes->Count;i++)
	{
		PropNode->ChildNodes->Add(Node->ChildNodes->Get(i));
	}
	FValue->FromXmlNode(PropNode);
}
//---------------------------------------------------------------------------
void __fastcall TClassProperty::SetName(String Name)
{
	if(Object != NULL)
	{
		delete FValue;
		FValue = new TPropertyList((TPersistent*)GetObjectProp(Object,Name),ParentList->ObjectOwner);
	}
	TPropertyBase::SetName(Name);
}
//---------------------------------------------------------------------------
void __fastcall TClassProperty::UpdateValue(void)
{
	FValue->ReloadProperties();
}
//---------------------------------------------------------------------------
void __fastcall TClassProperty::ApplyValue(void)
{
	FValue->ApplyValues();
}
//---------------------------------------------------------------------------
//						+++TPropertyList+++
//---------------------------------------------------------------------------
bool __fastcall TPropertyList::EqualByPublished(TObject *Obj1, TObject *Obj2)
{
	if(Obj1 == NULL ^ Obj2 == NULL)
		return false;
	if(Obj1 == NULL && Obj2 == NULL)
		return true;
	if(Obj1->ClassType() != Obj2->ClassType())
		return false;
	TPropList *List=NULL;
	TPropInfo *PropInfo=NULL;
	int propCount=0;
	propCount = GetPropList(Obj1,List);
	for(int i=0;i<propCount;i++)
	{
		PropInfo = List->data[i];
        TTypeInfo *TypeInfo = *PropInfo->PropType;
		if(TypeInfo->Kind == tkClass)
		{
			TObject *ChildObj1 = GetObjectProp(Obj1,PropInfo);
			TObject *ChildObj2 = GetObjectProp(Obj2,PropInfo);
			if(ChildObj1 == NULL || ChildObj1->InheritsFrom(__classid(TComponent)))
			{
				if(ChildObj1 != ChildObj2)
				{
					delete List;
					return false;
				}
			}
			else
			{
				if(!EqualByPublished(ChildObj1,ChildObj2))
				{
					delete List;
					return false;
				}
			}
		}
		else if(TypeInfo->Kind == tkMethod)
		{
			TMethod Method1 = GetMethodProp(Obj1,PropInfo);
			TMethod Method2 = GetMethodProp(Obj2,PropInfo);
			if(Method1.Data != Method2.Data || Method1.Code != Method2.Code)
			{
				delete List;
				return false;
			}
		}
		else
		{
			if(GetPropValue(Obj1,PropInfo) != GetPropValue(Obj2,PropInfo))
			{
				delete List;
				return false;
			}
		}
	}
	delete List;
	return true;
}
//---------------------------------------------------------------------------
__fastcall TPropertyList::TPropertyList(TPersistent *Owner, TComponent *ObjectOwner)
	: FOwner(Owner), FObjectOwner(ObjectOwner), FFiler(NULL), FApplyAfterLoading(false), FIsFixedup(false)
{
	ReloadProperties();
}
//---------------------------------------------------------------------------
__fastcall TPropertyList::TPropertyList(TPersistent *Owner, TFiler *Filer)
	: FOwner(Owner), FApplyAfterLoading(false), FIsFixedup(false)
{
	SetFiler(Filer);
	ReloadProperties();
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::SetFiler(TFiler *Filer)
{
	if(Filer != NULL)
		FObjectOwner = Filer->LookupRoot;
	FFiler = Filer;
}
//---------------------------------------------------------------------------
TWriter* __fastcall TPropertyList::GetWriter(void)
{
	if(FFiler == NULL || !FFiler->InheritsFrom(__classid(TWriter)))
		return NULL;
	else
		return (TWriter*)FFiler;
}
//---------------------------------------------------------------------------
TReader* __fastcall TPropertyList::GetReader(void)
{
	if(FFiler == NULL || !FFiler->InheritsFrom(__classid(TReader)))
		return NULL;
	else
		return (TReader*)FFiler;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::ReadFromReader(void)
{
	if(Reader == NULL)
		throw EArgumentException("Property List is not created with a reader!");
	String XML = Reader->ReadString();
	TXMLDocument *Doc = new TXMLDocument(Application);
	Doc->XML->Text = XML;
	Doc->Active = true;
	FromXmlNode(Doc->DocumentElement);
	delete Doc;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::WriteToWriter(void)
{
	if(Writer == NULL)
		throw EArgumentException("Property List is not created with a writer!");
	Writer->WriteString(ToXmlNode()->XML);
}
//---------------------------------------------------------------------------
TPersistent* __fastcall TPropertyList::GetOwner(void)
{
	return FOwner;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::KeepProperties(TPropertySet *Properties)
{
	for(int i=0;i<FProperties.Count();i++)
	{
		if(!Properties->IsInList(FProperties[i]->Name))
		{
			delete FProperties[i];
			FProperties.Delete(i);
        }
	}
	for(int i=0;i<Properties->Count();i++)
	{
		if(!IsInList(Properties->NameAtPos(i)))
		{
			AddProperty(Properties->NameAtPos(i));
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyList::Equals(TObject* Obj)
{
	if(Obj->ClassType() != TPropertyList::ClassType())
		return false;
	TPropertyList *PropList = (TPropertyList*)Obj;
	if(Count() != PropList->Count())
		return false;
	for(int i=0;i<Count();i++)
	{
		if(!PropList->IsInList(NameAtPos(i)) || !FProperties[i]->Equals(PropList->Property[NameAtPos(i)]))
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::DefineProperties(TFiler* Filer)
{
	TPropertyList *Ancestor = (TPropertyList*)Filer->Ancestor;
	Filer->DefineBinaryProperty("PropertyXML",ReadPropertyXML,WritePropertyXML,Ancestor == NULL ? Count() > 0 : !Ancestor->Equals(this));
	//Filer->DefineProperty("PropertyString",ReadPropertyString,WritePropertyString,true);
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::ReadPropertyString(TReader *Reader)
{
	Reader->ReadString();
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::WritePropertyString(TWriter *Writer)
{
	TFiler *buf = FFiler;
	SetFiler(Writer);
	WriteToWriter();
	SetFiler(buf);
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::ReadPropertyXML(TStream *Stream)
{
	TXMLDocument *Doc = new TXMLDocument(Application);
	Doc->LoadFromStream(Stream);
	Doc->Active = true;
	FromXmlNode(Doc->DocumentElement);
	delete Doc;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::WritePropertyXML(TStream *Stream)
{
	TXMLDocument *Doc = new TXMLDocument(Application);
	Doc->Active = true;
	_di_IXMLNode Node = ToXmlNode();
	Doc->ChildNodes->Add(Node);
	Doc->SaveToStream(Stream);
	delete Doc;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::Clear(void)
{
	for(int i=0;i<FProperties.Count();i++)
	{
		delete FProperties[i];
	}
	FProperties.Clear();
}
//---------------------------------------------------------------------------
int __fastcall TPropertyList::SearchProperty(String Name)
{
	for(int i=0;i<FProperties.Count();i++)
	{
		if(FProperties[i]->Name == Name)
		{
			return i;
        }
	}
	return -1;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::Assign(TPersistent *Object)
{
	if(Object->InheritsFrom(__classid(TPropertyList)))
	{
		TPropertyList *PropList = (TPropertyList*)Object;
		FromXmlNode(PropList->ToXmlNode());
	}
	else
		TPersistent::Assign(Object);
}
//---------------------------------------------------------------------------
String __fastcall TPropertyList::GetValue(String Property)
{
	if(!IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is not in the list!");
	TPropertyBase *Prop = GetByDotName(Property);
	if(Prop->PropertyType == ptClass)
		throw EArgumentException("Property '"+Property+"' is a class property!");
	return ((TProperty*)Prop)->Value;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::SetValue(String Property, String Value)
{
	if(!IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is not in the list!");
	TPropertyBase *Prop = GetByDotName(Property);
    if(Prop->PropertyType == ptClass)
		throw EArgumentException("Property '"+Property+"' is a class property!");
	((TProperty*)Prop)->Value = Value;
}
//---------------------------------------------------------------------------
TPropertyBase* __fastcall TPropertyList::GetProperty(String Property)
{
	if(!IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is not in the list!");
	return GetByDotName(Property);
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::SetProperty(String Property, TPropertyBase* Value)
{
	if(!IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is not in the list!");
	GetByDotName(Property)->Assign(Value);
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyList::IsInList(String Property)
{
	return GetByDotName(Property) != NULL;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::Fixup(void)
{
	if(!IsFixedup())
	{
		for(int i=0;i<Count();i++)
		{
			if(FProperties[i]->InheritsFrom(__classid(TFixupProperty)))
			{
				((TFixupProperty*)FProperties[i])->DoFixup();
			}
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall TPropertyList::IsFixedup(void)
{
	return FIsFixedup;
}
//---------------------------------------------------------------------------
TPropertyBase* __fastcall TPropertyList::GetByDotName(String FullPropName)
{
	FullPropName += ".";
	TPropertyList *ParentList = this;
	TPropertyBase *Prop = NULL;
	while(FullPropName.Pos("."))
	{
		String ClassProp = FullPropName.SubString(1,FullPropName.Pos(".")-1);
		FullPropName.Delete(1,FullPropName.Pos("."));
		int PropIndex = ParentList->SearchProperty(ClassProp);
		if(PropIndex == -1)
			return NULL;
		Prop = ParentList->FProperties[PropIndex];
		if(Prop->PropertyType == ptClass)
		{
			ParentList = ((TClassProperty*)Prop)->Value;
		}
		else if(Prop->PropertyType == ptValue)
		{
			break;
        }
	}
	return Prop;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::AddProperty(String Property, String ClassName)
{
	if(IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is already in the list!");

	TPropInfo *PropInfo = FOwner == NULL ? NULL : GetPropInfo(FOwner,Property);
	TTypeInfo *TypeInfo = PropInfo == NULL ? NULL : *PropInfo->PropType;
	if(FOwner != NULL && PropInfo == NULL)
		throw EArgumentException("Property '"+Property+"' doesn't exist!");
	/*if(TypeInfo->Kind == tkClass ^ PropertyType == ptClass)
		throw EArgumentException("Property '"+Property+"' doesn't match the property type!"); */
	FProperties.Add(CreateProperty(ClassName));
	FProperties.Last()->Name = Property;
}
//---------------------------------------------------------------------------
TPropertyBase* __fastcall TPropertyList::CreateProperty(String ClassName)
{
	if(ClassName == TProperty::ClassName())
	{
		return new TProperty(this);
	}
	else if(ClassName == TClassProperty::ClassName())
	{
		return new TClassProperty(this);
	}
	else if(ClassName == TReferenceProperty::ClassName())
	{
		return new TReferenceProperty(this,FObjectOwner);
	}
	else if(ClassName == TMethodProperty::ClassName())
	{
		return new TMethodProperty(this,FObjectOwner);
	}
	else
		throw EArgumentException("Class '"+ClassName+"' isn't allowed!");
}
//---------------------------------------------------------------------------
TPropertyBase* __fastcall TPropertyList::CreateProperty(TPropInfo *Info)
{
	TTypeInfo *TypeInfo = *Info->PropType;
	if(TypeInfo->Kind == tkClass)
	{
		TObject *Obj = GetObjectProp(FOwner,Info);
		if(Obj == NULL || Obj->InheritsFrom(__classid(TComponent)))
		{
			return new TReferenceProperty(this, FObjectOwner);
		}
		else
		{
			return new TClassProperty(this);
		}
	}
	else if(TypeInfo->Kind == tkMethod)
	{
		return new TMethodProperty(this, FObjectOwner);
	}
	else
	{
		return new TProperty(this);
	}
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::RemoveProperty(String Property)
{
	if(!IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is not in the list!");

	int Index = SearchProperty(Property);
	delete FProperties[Index];
	FProperties.Delete(Index);
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::ApplyValues(void)
{
	for(int i=0;i<FProperties.Count();i++)
	{
		FProperties[i]->ApplyValue();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::ApplyValues(TPropertySet *Properties)
{
	for(int i=0;i<Properties->Count();i++)
	{
		if(IsInList(Properties->NameAtPos(i)))
			Property[Properties->NameAtPos(i)]->ApplyValue();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::UpdateValues(TPropertySet *Properties)
{
	for(int i=0;i<Properties->Count();i++)
	{
		if(IsInList(Properties->NameAtPos(i)))
			Property[Properties->NameAtPos(i)]->UpdateValue();
    }
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::AddProperty(String Name)
{
	if(FOwner == NULL)
		throw EArgumentException("Owner must not be null!");
	TPropInfo *Info = GetPropInfo(FOwner,Name);
	if(Info == NULL)
		throw EArgumentException("Property does not exist!");
	FProperties.Add(CreateProperty(Info));
    FProperties.Last()->Name = Name;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::ReloadProperties(void)
{
	if(FOwner != NULL)
	{
		Clear();
		PPropList List=NULL;
		PPropInfo PropInfo;
		int propCount=0;
		propCount = GetPropList(FOwner,List);
		for(int i=0;i<propCount;i++)
		{
			PropInfo = List->data[i];
			String name = PropInfo->Name.operator AnsiString();
			AddProperty(name);
		}
		delete List;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::UpdateValues(void)
{
	if(FOwner != NULL)
	{
		for(int i=0;i<FProperties.Count();i++)
		{
			FProperties[i]->UpdateValue();
		}
	}
}
//---------------------------------------------------------------------------
int __fastcall TPropertyList::Count(void)
{
	return FProperties.Count();
}
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TPropertyList::ToXmlNode(void)
{
	_di_IXMLNode Node = CreateNode("PropertyList",TPropertyList::XMLPrefix,"PropertyList");
	for(int i=0;i<FProperties.Count();i++)
	{
		Node->ChildNodes->Add(FProperties[i]->ToXmlNode());
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyList::FromXmlNode(_di_IXMLNode Node)
{
	Clear();
	for(int i=0;i<Node->ChildNodes->Count;i++)
	{
		_di_IXMLNode ChildNode = Node->ChildNodes->Get(i);
		if(ChildNode->Prefix == TPropertyList::XMLPrefix)
		{
			AddProperty(ChildNode->Attributes["Name"],ChildNode->LocalName);
			FProperties.Last()->FromXmlNode(ChildNode);
		}
	}
}
//---------------------------------------------------------------------------
String __fastcall TPropertyList::NameAtPos(int Index)
{
	return FProperties[Index]->Name;
}
//---------------------------------------------------------------------------
//						+++TPropertySet+++
//---------------------------------------------------------------------------
_di_IXMLNode __fastcall TPropertySet::ToXmlNode(void)
{
	_di_IXMLNode Node = CreateNode(ClassName());
	for(int i=0;i<FProperties.Count();i++)
	{
		_di_IXMLNode ChildNode = CreateNode("Property");
		ChildNode->Attributes["Name"] = FProperties[i];
		Node->ChildNodes->Add(ChildNode);
	}
	return Node;
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::FromXmlNode(_di_IXMLNode Node)
{
	if(Node->NodeName != ClassName())
		throw EArgumentException("Node with name '"+Node->NodeName+"' doesn't fit to object from class '"+ClassName()+"'!");
	Clear();
	for(int i=0;i<Node->ChildNodes->Count;i++)
	{
		_di_IXMLNode ChildNode = Node->ChildNodes->Get(i);
		if(ChildNode->NodeName == "Property")
			FProperties.Add(ChildNode->Attributes["Name"]);
	}
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::ReadPropertyXML(TStream *Stream)
{
	TXMLDocument *Doc = new TXMLDocument(Application);
	Doc->LoadFromStream(Stream);
	Doc->Active = true;
	FromXmlNode(Doc->DocumentElement);
	delete Doc;
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::WritePropertyXML(TStream *Stream)
{
	TXMLDocument *Doc = new TXMLDocument(Application);
	Doc->Active = true;
	Doc->ChildNodes->Add(ToXmlNode());
	Doc->SaveToStream(Stream);
	delete Doc;
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::DefineProperties(TFiler* Filer)
{
	TPropertySet *Ancestor = (TPropertySet*)Filer->Ancestor;
	Filer->DefineBinaryProperty("PropertiesXML",ReadPropertyXML,WritePropertyXML,Ancestor == NULL || *Ancestor != *this);
}
//---------------------------------------------------------------------------
bool __fastcall TPropertySet::operator==(const TPropertySet &Set)
{
	return !( *this != Set);
}
//---------------------------------------------------------------------------
bool __fastcall TPropertySet::operator!=(const TPropertySet &Set)
{
	if(Set.Count() != Count())
		return false;
	for(int i=0;i<Count();i++)
	{
		if(!IsInList(Set.FProperties[i]))
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TPropertySet::IsInList(String Property)
{
	for(int i=0;i<FProperties.Count();i++)
	{
		if(FProperties[i] == Property)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::AddToList(String Property)
{
	if(IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is already in the list!");
    FProperties.Add(Property);
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::RemoveFromList(String Property)
{
	if(!IsInList(Property))
		throw EArgumentException("Property '"+Property+"' is not in the list!");
	for(int i=0;i<FProperties.Count();i++)
	{
		if(FProperties[i] == Property)
		{
			FProperties.Delete(i);
			return;
        }
	}
}
//---------------------------------------------------------------------------
String __fastcall TPropertySet::NameAtPos(int Index)
{
	return FProperties[Index];
}
//---------------------------------------------------------------------------
int __fastcall TPropertySet::Count(void) const
{
	return FProperties.Count();
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::Clear(void)
{
	FProperties.Clear();
}
//---------------------------------------------------------------------------
void __fastcall TPropertySet::Assign(TPersistent *Object)
{
	if(Object != NULL)
	{
		if(Object->InheritsFrom(__classid(TPropertySet)))
		{
			FProperties = ((TPropertySet*)Object)->FProperties;
		}
		else if(Object->InheritsFrom(__classid(TPropertyList)))
		{
			TPropertyList *PropList = (TPropertyList*)Object;
			FProperties.Clear();
			for(int i=0;i<PropList->Count();i++)
			{
				FProperties.Add(PropList->NameAtPos(i));
			}
		}
	}
}
//---------------------------------------------------------------------------
//						+++TOwnedPropertySet+++
//---------------------------------------------------------------------------
__fastcall TOwnedPropertySet::TOwnedPropertySet(TPersistent *Owner)
	: FOwner(Owner)
{
}
//---------------------------------------------------------------------------
TPersistent* __fastcall TOwnedPropertySet::GetOwner(void)
{
	return FOwner;
}
//---------------------------------------------------------------------------
void __fastcall TOwnedPropertySet::LoadNames(void)
{
	if(FOwner != NULL)
	{
		Clear();
		PPropList List=NULL;
		PPropInfo PropInfo;
		int propCount=0;
		propCount = GetPropList(FOwner,List);
		for(int i=0;i<propCount;i++)
		{
			PropInfo = List->data[i];
			String name = PropInfo->Name.operator AnsiString();
			if(IsStoredProp(FOwner, PropInfo))
			{
				AddToList(name);
			}
		}
		delete List;
	}
}
//---------------------------------------------------------------------------
