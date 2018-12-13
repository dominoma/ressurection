//---------------------------------------------------------------------------

#ifndef PropertyClassesH
#define PropertyClassesH
#include "ArrayClass.h"
#include "XmlSerialize.h"
//---------------------------------------------------------------------------
//Diese Unit stellt Klassen (TPropertySet, TPropertyList) bereit,
//die das Arbeiten mit veröffentlichten (__published) Properties vereinfacht.
//TPropertyBase und davon abgeleitete Klassen werden nur innerhalb der TPropertyList-Klasse benötigt,
//daher werden diese nicht dokumentiert.
//Anmerkung: Viele der Methoden in dieser Unit arbeiten sehr tief im FMX-Framework,
//für Erläuterungen verweise ich auf die Online-Hilfe von Embarcadero.
class TClassProperty;
class TPropertyList;
//---------------------------------------------------------------------------
class PACKAGE TPropertySet : public TPersistent, public IXmlSerializable
{
private:
	TStringArray FProperties;

	void __fastcall ReadPropertyXML(TStream *Stream);
	void __fastcall WritePropertyXML(TStream *Stream);
protected:
	void __fastcall DefineProperties(TFiler* Filer);
public:
	void __fastcall Assign(TPersistent *Object);
	bool __fastcall IsInList(String Property);
	void __fastcall AddToList(String Property);
	void __fastcall RemoveFromList(String Property);

	bool __fastcall operator==(const TPropertySet &Set);
	bool __fastcall operator!=(const TPropertySet &Set);

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	String __fastcall NameAtPos(int Index);

	int __fastcall Count(void) const;
	void __fastcall Clear(void);
};
//---------------------------------------------------------------------------
class PACKAGE TOwnedPropertySet : public TPropertySet
{
private:
	TPersistent *FOwner;
protected:
	DYNAMIC TPersistent* __fastcall GetOwner(void);
public:
	__fastcall TOwnedPropertySet(TPersistent *Owner);
	void __fastcall LoadNames(void);
};
//---------------------------------------------------------------------------
class PACKAGE TPropertyBase : public TPersistent, public IXmlSerializable
{
private:
	String FName;
	TPropertyList *FParentList;

	TPersistent* __fastcall GetObject(void);

	TPropInfo __fastcall GetPropertyInfo(void);
	TTypeInfo __fastcall GetTypeInfo(void);
	bool __fastcall GetIsStored(void);
protected:
	virtual void __fastcall SetName(String NewName);
	virtual int __fastcall GetPropertyType(void)=0;
	virtual bool __fastcall IsPropertyFitting(void)=0;
	DYNAMIC TPersistent* __fastcall GetOwner(void);
public:
	__fastcall TPropertyBase(TPropertyList *Owner);
	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TPersistent* Source);

	virtual bool __fastcall IsDefault(void);

	bool __fastcall IsReadOnly(void);

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	bool __fastcall PropertyExists(void);

	virtual void __fastcall UpdateValue(void)=0;
	virtual void __fastcall ApplyValue(void)=0;

	__property TPropertyList* ParentList = {read=FParentList};
	__property TPersistent* Object = {read=GetObject};
	__property int PropertyType = {read=GetPropertyType};
	__property TPropInfo PropertyInfo = {read=GetPropertyInfo};
	__property TTypeInfo TypeInfo = {read=GetTypeInfo};
	__property bool IsStored = {read=GetIsStored};

	__property String Name = {read=FName,write=SetName};
};
//---------------------------------------------------------------------------
enum TPropertyType {ptClass, ptValue, ptReference, ptMethod};
//---------------------------------------------------------------------------
class PACKAGE TProperty : public TPropertyBase
{
	Variant FValue;
	int __fastcall GetPropertyType(void){ return ptValue; };
	bool __fastcall IsPropertyFitting(void);
public:
	__fastcall TProperty(TPropertyList *Owner);
	bool __fastcall IsDefault(void);

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	void __fastcall UpdateValue(void);
	void __fastcall ApplyValue(void);

	__property Variant Value = {read=FValue,write=FValue};
};
//---------------------------------------------------------------------------
class PACKAGE TFixupProperty : public TPropertyBase
{
friend TPropertyList;
private:

protected:
	virtual void __fastcall DoFixup(void)=0;
	void __fastcall AfterConstruction(void);
public:

	bool __fastcall IsFixedup(void);

	__fastcall TFixupProperty(TPropertyList *Owner);
};
//---------------------------------------------------------------------------
class PACKAGE TOwnedProperty : public TFixupProperty
{
private:
	TComponent *FOwner;
protected:
	void __fastcall SetOwner(TComponent *Owner);
public:
	__fastcall TOwnedProperty(TPropertyList *ParentList, TComponent *Owner);

	__property TComponent* Owner = {read=FOwner};

};
//---------------------------------------------------------------------------
class PACKAGE TReferenceProperty : public TOwnedProperty
{
private:
	String FValueStr;

	TComponent* __fastcall GetValue(void);
	void __fastcall SetValue(TComponent *Value);
protected:
	void __fastcall DoFixup(void);
	int __fastcall GetPropertyType(void){ return ptReference; };
	bool __fastcall IsPropertyFitting(void);
public:
	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);
	bool __fastcall IsDefault(void);

	void __fastcall UpdateValue(void);
	void __fastcall ApplyValue(void);

	__fastcall TReferenceProperty(TPropertyList *ParentList, TComponent *Owner);

	__property String ValueString = {read=FValueStr,write=FValueStr};
	__property TComponent* Value = {read=GetValue,write=SetValue};
};
//---------------------------------------------------------------------------
class PACKAGE TMethodProperty : public TOwnedProperty
{
private:
	String FPropStrBuf;
	String FValue;

	TMethod __fastcall GetObjMethod(void);
	void __fastcall SetObjMethod(TMethod Value);

protected:
	int __fastcall GetPropertyType(void){ return ptMethod; };
	void __fastcall DoFixup(void);
	bool __fastcall IsPropertyFitting(void);
public:
	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);
	bool __fastcall IsDefault(void);

	void __fastcall UpdateValue(void);
	void __fastcall ApplyValue(void);

	template<typename FuncType>
	void __fastcall SetMethod(FuncType Method)
	{
		this->Method = *reinterpret_cast<TMethod*>(&Method);
	};

	template<typename FuncType>
	FuncType __fastcall GetMethod(void)
	{
		return *reinterpret_cast<FuncType*>(&Method);
	};

	__fastcall TMethodProperty(TPropertyList *ParentList, TComponent *Owner);

	__property TMethod Method = {read=GetObjMethod,write=SetObjMethod};
	__property String Value = {read=FValue,write=FValue};

};
//---------------------------------------------------------------------------
class PACKAGE TClassProperty : public TFixupProperty
{
	TPropertyList *FValue;

	void __fastcall SetName(String Name);
	int __fastcall GetPropertyType(void){ return ptClass; };
	bool __fastcall IsPropertyFitting(void);
protected:
	void __fastcall DoFixup(void);
public:
	__fastcall TClassProperty(TPropertyList *Owner);
	__fastcall ~TClassProperty(void);
	bool __fastcall IsDefault(void);

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	void __fastcall UpdateValue(void);
	void __fastcall ApplyValue(void);

	__property TPropertyList* Value = {read=FValue,write=FValue};
};
//---------------------------------------------------------------------------
class PACKAGE TPropertyList : public TPersistent, public IXmlSerializable
{
private:
	TPersistent *FOwner;
	TComponent *FObjectOwner;
	TFiler *FFiler;

	TArrayClass<TPropertyBase*> FProperties;

	bool FApplyAfterLoading;
	bool FIsFixedup;

	String __fastcall GetValue(String Property);
	void __fastcall SetValue(String Property, String Value);

	TPropertyBase* __fastcall GetProperty(String Property);
	void __fastcall SetProperty(String Property, TPropertyBase* Value);

	TPropertyBase* __fastcall GetByDotName(String FullPropName);

	int __fastcall SearchProperty(String Name);

	void __fastcall ReadPropertyXML(TStream *Stream);
	void __fastcall WritePropertyXML(TStream *Stream);

	void __fastcall ReadPropertyString(TReader *Reader);
	void __fastcall WritePropertyString(TWriter *Writer);

	TWriter* __fastcall GetWriter(void);
	TReader* __fastcall GetReader(void);

protected:
	DYNAMIC TPersistent* __fastcall GetOwner(void);
	void __fastcall DefineProperties(TFiler* Filer);

	void __fastcall SetFiler(TFiler *Filer);

	virtual TPropertyBase* __fastcall CreateProperty(TPropInfo *Info);
	virtual TPropertyBase* __fastcall CreateProperty(String ClassName);

public:

	static bool __fastcall EqualByPublished(TObject *Obj1, TObject *Obj2);

	__fastcall TPropertyList(TPersistent *Owner, TComponent *ObjectOwner);
	__fastcall TPropertyList(TPersistent *Owner, TFiler *Filer);

	static const String XMLPrefix;

	void __fastcall ReadFromReader(void);
	void __fastcall WriteToWriter(void);

	void __fastcall Fixup(void);
	bool __fastcall IsFixedup(void);

	bool __fastcall Equals(TObject* Obj);

	void __fastcall Assign(TPersistent *Object);

	int __fastcall Count(void);
	void __fastcall Clear(void);

	bool __fastcall IsInList(String Property);
	void __fastcall AddProperty(String Name);
	void __fastcall AddProperty(String Property, String ClassName);
	void __fastcall RemoveProperty(String Property);

	String __fastcall NameAtPos(int Index);

	void __fastcall KeepProperties(TPropertySet *Properties);

	void __fastcall ApplyValues(void);
	void __fastcall ApplyValues(TPropertySet *Properties);
	void __fastcall UpdateValues(void);
	void __fastcall UpdateValues(TPropertySet *Properties);
	void __fastcall ReloadProperties(void);

	_di_IXMLNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(_di_IXMLNode Node);

	__property String Value[String Property] = {read=GetValue,write=SetValue};
	__property TPropertyBase* Property[String Property] = {read=GetProperty,write=SetProperty};
	__property TPersistent *Owner = {read=FOwner};
	__property TComponent *ObjectOwner = {read=FObjectOwner};
	__property TWriter* Writer = {read=GetWriter};
	__property TReader* Reader = {read=GetReader};
	__property bool ApplyAfterLoading = {read=FApplyAfterLoading,write=FApplyAfterLoading};
};
//---------------------------------------------------------------------------
#endif
