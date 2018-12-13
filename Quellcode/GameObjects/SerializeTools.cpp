//---------------------------------------------------------------------------

#pragma hdrstop
#define protected public
#define private public
#include <System.Classes.hpp>
#undef protected
#undef private
#include "SerializeTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall WriteObjListBegin(TWriter *Writer)
{
	Writer->WriteValue(vaCollection);
	Writer->FPropPath = "";
}
//---------------------------------------------------------------------------
void __fastcall WriteObjListEnd(TWriter *Writer)
{
    Writer->WriteListEnd();
}
//---------------------------------------------------------------------------
void __fastcall WriteObjListItem(TWriter *Writer, TPersistent *Item)
{
	Writer->WriteListBegin();
	Writer->WriteProperties(Item);
	Writer->WriteListEnd();
}
//---------------------------------------------------------------------------
void __fastcall ReadObjListBegin(TReader *Reader)
{
	Reader->CheckValue(vaCollection);
}
//---------------------------------------------------------------------------
void __fastcall ReadObjListEnd(TReader *Reader)
{
	Reader->ReadListEnd();
}
//---------------------------------------------------------------------------
void __fastcall ReadObjListItem(TReader *Reader, TPersistent *Item)
{
	Reader->ReadListBegin();
	while(!Reader->EndOfList())
	{
		Reader->ReadProperty(Item);
	}
	Reader->ReadListEnd();
}
//---------------------------------------------------------------------------
String __fastcall FindMethodName(TWriter *Writer, TMethod Method)
{
	return Writer->FindMethodName(Method);
}
//---------------------------------------------------------------------------
TMethod __fastcall FindMethodInstance(TReader *Reader, String Name)
{
	return Reader->FindMethodInstance(Reader->LookupRoot,Name);
}
//---------------------------------------------------------------------------
String __fastcall GetPropertyName(TPersistent *Property)
{
	PPropList List=NULL;
	PPropInfo PropInfo=NULL;
	int propCount=0;
	TPersistent *Owner = Property->GetOwner();
	if(Owner != NULL)
	{
		propCount = GetPropList(Owner,List);
		for(int i=0;i<propCount;i++)
		{
			PropInfo = List->data[i];
			TTypeInfo *TypeInfo = *(PropInfo->PropType);
			String name = PropInfo->Name.operator AnsiString();

			if(TypeInfo->Kind == tkClass)
			{
				TObject *SubClass = GetObjectProp(Owner,name);
				if(int(SubClass) == int(Property))
				{
					return name;
				}
			}

		}
		delete List;
	}
}
//---------------------------------------------------------------------------
