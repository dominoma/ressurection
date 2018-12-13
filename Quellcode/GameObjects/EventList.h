//---------------------------------------------------------------------------

#ifndef EventListH
#define EventListH
#include <System.Classes.hpp>
#include "ArrayClass.h"
//Makro zur Vereinfachung der Implementierung einer Event-List und eines Callback-Events
//PROPNAME: Name des Events
//PROPTYPE: Methodentyp des Events (Bsp: TNotifyEvent)
//LIST_PROPERTY_VISIBILITTY: Sichtbarkeit (private, protected, public) der Event-List
//EVENT_PROPERTY_VISIBILITTY: Sichtbarkeit (private, protected, public, __published) des Callback-Events
//Anmerkung: Nach Aufruf des Makros in der Klassendefinition ist die Sichtbarkeit auf private gesetzt
#define DEFINE_EVENTLIST_PROPERTIES(PROPNAME,PROPTYPE,LIST_PROPERTY_VISIBILITTY,EVENT_PROPERTY_VISIBILITTY) 	\
	private:                                                                                        \
		TEventList<PROPTYPE> F##PROPNAME##List;   													\
		TEventList<PROPTYPE>& __fastcall Get##PROPNAME##List(void) { return F##PROPNAME##List; }; 	\
		PROPTYPE __fastcall Get##PROPNAME(void){ return F##PROPNAME##List.Event; };               	\
		void __fastcall Set##PROPNAME(PROPTYPE Event){ F##PROPNAME##List.Event = Event; };        	\
	LIST_PROPERTY_VISIBILITTY: 																		\
		__property TEventList<PROPTYPE> PROPNAME##List = {read=Get##PROPNAME##List}; 				\
	EVENT_PROPERTY_VISIBILITTY:																		\
		__property PROPTYPE PROPNAME = {read=Get##PROPNAME,write=Set##PROPNAME};     				\
	private:
//---------------------------------------------------------------------------
class PACKAGE TEventListBase
{
private:
	TArrayClass<TMethod> FEventListeners;

	int __fastcall IndexOf(TMethod Method);
protected:
	typedef void __fastcall (__closure *TParamPtrEvent)(void* &Pointer);

	template<typename OutFunc>
	static OutFunc __fastcall ConvertFunc(void *Func){ return *((OutFunc*)Func); };
	template<typename OutFunc>
	static OutFunc __fastcall ConvertFunc(TParamPtrEvent Func){ return *((OutFunc*)&Func); };

	virtual void __fastcall EventCaller(void* &Pointer);

	void __fastcall AddEventListener(TMethod Method);
	void __fastcall RemoveEventListener(TMethod Method);
public:
	void __fastcall Clear(void){ FEventListeners.Clear(); };
};
//---------------------------------------------------------------------------
template<typename EventType>
class TEventList : public TEventListBase
{
private:
	EventType __fastcall GetEventCaller(void){ return ConvertFunc<EventType>(EventCaller); };
	EventType FEvent;
public:
	__property EventType CallEvents = {read=GetEventCaller};

	void __fastcall EventCaller(void* &Pointer)
	{
		if(FEvent != NULL)
			ConvertFunc<TParamPtrEvent>(&FEvent)(Pointer);
		TEventListBase::EventCaller(Pointer);
	};

	void __fastcall AddEventListener(EventType Func)
	{
		TEventListBase::AddEventListener(ConvertFunc<TMethod>(&Func));
	};
	void __fastcall RemoveEventListener(EventType Func)
	{
		TEventListBase::RemoveEventListener(ConvertFunc<TMethod>(&Func));
	};
	__property EventType Event = {read=FEvent,write=FEvent};

	__fastcall TEventList(void) : FEvent(NULL){};
};
//---------------------------------------------------------------------------
typedef TEventList<TNotifyEvent> TNotifyEventList;
#endif
