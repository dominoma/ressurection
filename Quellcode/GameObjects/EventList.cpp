//---------------------------------------------------------------------------

#pragma hdrstop

#include "EventList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TEventListBase::EventCaller(void* &Pointer)
{
	for(int i=0;i<FEventListeners.Count();i++)
	{
		ConvertFunc<TParamPtrEvent>(&FEventListeners[i])(Pointer);
	};
}
//---------------------------------------------------------------------------
int __fastcall TEventListBase::IndexOf(TMethod Method)
{
	for(int i=0;i<FEventListeners.Count();i++)
	{
		if(Method.Code == FEventListeners[i].Code && Method.Data == FEventListeners[i].Data)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------
void __fastcall TEventListBase::AddEventListener(TMethod Method)
{
	if(IndexOf(Method) != -1)
		throw EArgumentException("Method is already in the list!");
    FEventListeners.Add(Method);
}
//---------------------------------------------------------------------------
void __fastcall TEventListBase::RemoveEventListener(TMethod Method)
{
	int Index = IndexOf(Method);
	if(Index == -1)
		throw EArgumentException("Method is not in the list!");
	FEventListeners.Delete(Index);
}
//---------------------------------------------------------------------------
