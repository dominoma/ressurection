//---------------------------------------------------------------------------

#ifndef CustomListH
#define CustomListH
#include <FMX.Types.hpp>
#include <System.Contnrs.hpp>
#include "ArrayClass.h"
#include "MetaCreate.hpp"
#include "XmlSerialize.h"
//---------------------------------------------------------------------------
class TCustomList;
class TCustomListEditorForm;
class PACKAGE TCustomListItem : public TBasicCustomListItem, public IXmlSerializable
{
friend TCustomList;
private:
	TCustomList *AOwner;

	int __fastcall GetIndex(void);
protected:

	DYNAMIC TPersistent* __fastcall GetOwner(void);
	DYNAMIC String __fastcall GetNamePath(void);

public:
	__fastcall TCustomListItem(TBasicCustomList *Owner);
	__fastcall ~TCustomListItem(void);

	_di_IXMLNode __fastcall ToXmlNode(TComponent *Root);
	void __fastcall FromXmlNode(_di_IXMLNode Node, TComponent *Root);

	bool __fastcall Equals(TObject *Obj);

	virtual String __fastcall DisplayName(void);

	__property int Index = {read=GetIndex};
	__property TCustomList* ParentList = {read=AOwner};
__published:
};
//---------------------------------------------------------------------------
class PACKAGE TCustomList : public TBasicCustomList
{
friend TCustomListItem;
private:
	TPersistent *AOwner;
	TClassList *classList;

	void __fastcall ReadItems(TReader* Reader);
	void __fastcall WriteItems(TWriter* Writer);
	void __fastcall ReadClassNames(TReader* Reader);
	void __fastcall WriteClassNames(TWriter* Writer);

	void __fastcall DoAddItem(TCustomListItem* Item);

	bool __fastcall IsClassAllowed(TClass Class);
	TClass __fastcall GetClassByName(String ClassName);

	DYNAMIC TPersistent* __fastcall GetOwner(void);
	virtual void __fastcall DefineProperties(TFiler* Filer);

protected:

	virtual TCustomListItem* __fastcall GetItem(int Index)=0;
	virtual void __fastcall SetItem(int Index, TCustomListItem *Item);

	virtual void __fastcall AddItem(TCustomListItem* Item)=0;
	virtual void __fastcall DeleteItem(TCustomListItem* Item)=0;

	virtual int __fastcall GetCount(void)=0;

	virtual void __fastcall SetAllowedClasses(TClassList *ClassList);

	DYNAMIC String __fastcall GetNamePath(void);

public:

	bool __fastcall Equals(TObject *Obj);
	void __fastcall Assign(TPersistent* Source);

	_di_IXMLNode __fastcall ToXmlNode(TComponent *Root);
	void __fastcall FromXmlNode(_di_IXMLNode Node, TComponent *Root);

	TClassList* __fastcall AllowedClasses(void);

	void __fastcall Clear(void);
	void __fastcall Delete(int Index);
	TCustomListItem* __fastcall Add(void);
	TCustomListItem* __fastcall Add(TClass Class);
	TCustomListItem* __fastcall Add(String ClassName);

	virtual void __fastcall ItemUp(int Index)=0;
	virtual void __fastcall ItemDown(int Index)=0;

	__fastcall TCustomList(TPersistent *Owner);
	__fastcall ~TCustomList(void);

	__property int Count = {read=GetCount};
	__property TCustomListItem* Items[int Index] = {read=GetItem,write=SetItem};

	__property TPersistent* Owner = {read=AOwner};
__published:

};
//---------------------------------------------------------------------------
class PACKAGE TVectorList : public TCustomList
{
private:

	TArrayClass<TCustomListItem*> list;

	void __fastcall AddItem(TCustomListItem* Item);
	void __fastcall DeleteItem(TCustomListItem* Item);

	int __fastcall GetCount(void);
protected:
	TCustomListItem* __fastcall GetItem(int Index);
public:
	__fastcall TVectorList(TPersistent *Owner);

	void __fastcall ItemUp(int Index);
	void __fastcall ItemDown(int Index);
__published:

};
//---------------------------------------------------------------------------
#endif
