//---------------------------------------------------------------------------

#ifndef SerializeToolsH
#define SerializeToolsH
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
void __fastcall WriteObjListBegin(TWriter *Writer);
void __fastcall WriteObjListEnd(TWriter *Writer);
void __fastcall WriteObjListItem(TWriter *Writer, TPersistent *Item);
void __fastcall ReadObjListBegin(TReader *Reader);
void __fastcall ReadObjListEnd(TReader *Reader);
void __fastcall ReadObjListItem(TReader *Reader, TPersistent *Item);
String __fastcall FindMethodName(TWriter *Writer, TMethod Method);
TMethod __fastcall FindMethodInstance(TReader *Reader, String Name);
String __fastcall GetPropertyName(TPersistent *Property);
#endif
