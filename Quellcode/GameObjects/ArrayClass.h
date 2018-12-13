//---------------------------------------------------------------------------

#ifndef ArrayClassH
#define ArrayClassH
#include <vector>
#include <typeinfo>
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Dialogs.hpp>
class EArrayException : public Exception
{

public:

	EArrayException(String Msg, String TypeName) : Exception("[TArrayClass<"+TypeName+">] "+Msg) {};

};
class EOutOfArrayRange : public EArrayException
{
public:
	EOutOfArrayRange(String Msg, String TypeName) : EArrayException("Out of Range ! ("+Msg+")", TypeName){};
	EOutOfArrayRange(__int64 Pos, __int64 Count, String TypeName) : EArrayException("Index '"+String(Pos)+"' out of Range! [0-"+String(Count-1)+"]", TypeName){};
	EOutOfArrayRange(__int64 Begin, __int64 End, __int64 Count, String TypeName) : EArrayException("Interval ["+String(Begin)+"-"+String(End)+"] out of Range! [0-"+String(Count)+"]", TypeName){};
};
template <typename Type>
class PACKAGE TArrayClass
{
typedef void __fastcall (__closure *TArrayEvent)(TArrayClass<Type> &Object);
private:

public:

	Type& __fastcall Last(void);
	const Type __fastcall Last(void) const;

	int __fastcall Count(void) const;

private:

	std::vector<Type> elements;

public:

	template<typename T> TArrayClass<T> __fastcall Convert(void);
	int __fastcall Add(Type s);
	int __fastcall Add(TArrayClass<Type> Array);
	void __fastcall Overwrite(TArrayClass<Type> Array, int Pos);
	void __fastcall Delete(int Index) ;
	void __fastcall Delete(int Begin, int End) ;
	void __fastcall Insert(int Position, Type s) ;
	void __fastcall Insert(int Position, TArrayClass<Type> Array) ;

	void __fastcall Pop(void)
	{
		if(Count() == 0)
			throw EOutOfArrayRange("Array empty", typeid(Type).name());
		elements.pop_back();
	};

	void __fastcall Clear(void);

	TArrayClass<Type> __fastcall Interval(int PosStart, int PosEnd) const ;
    TArrayClass<Type> __fastcall SubArr(int Pos, int Count) const ;
	Type* __fastcall Pointer(void);

	Type& __fastcall operator[](int index);
	const Type __fastcall operator[](int index) const;
	TArrayClass<Type>& __fastcall operator=(const TArrayClass<Type> &array);

	__fastcall TArrayClass(void);
	__fastcall TArrayClass(Type t[],int size);
	__fastcall TArrayClass(int Count);
	__fastcall TArrayClass(int Count, Type Inserted);
	template<typename T> __fastcall TArrayClass(const TArrayClass<T> &array);

};
//---------------------------------------------------------------------------
template <typename Type>
__fastcall TArrayClass<Type>::TArrayClass(void)
{
}
//---------------------------------------------------------------------------
template <typename Type>
__fastcall TArrayClass<Type>::TArrayClass(Type t[],int size)
{
	for(int i=0;i<size/sizeof(Type);i++)
	{
		Add(t[i]);
    }
}
//---------------------------------------------------------------------------
template <typename Type>
__fastcall TArrayClass<Type>::TArrayClass(int Count)
	: elements(Count)
{
	if(Count < 0)
		throw EArgumentException("'Count' must not be smaller than zero!");
}
//---------------------------------------------------------------------------
template <typename Type>
__fastcall TArrayClass<Type>::TArrayClass(int Count, Type Inserted)
	: elements(Count, Inserted)
{
	if(Count < 0)
		throw EArgumentException("'Count' must not be smaller than zero!");
}
//---------------------------------------------------------------------------
template <typename Type>
template<typename T> __fastcall TArrayClass<Type>::TArrayClass(const TArrayClass<T> &array)
{
	for(int i=0;i<array.Count();i++)
		Add(array[i]);
}
//---------------------------------------------------------------------------
template <typename Type>
TArrayClass<Type>& __fastcall TArrayClass<Type>::operator=(const TArrayClass<Type> &array)
{
	elements = array.elements;
	return *this;
}
//---------------------------------------------------------------------------
template <typename Type>
template<typename T>TArrayClass<T> __fastcall TArrayClass<Type>::Convert(void)
{
	return TArrayClass<T>(*this);
}
//---------------------------------------------------------------------------
template <typename Type>
void __fastcall TArrayClass<Type>::Overwrite(TArrayClass<Type> Array, int Pos)
{
	for(int i=0;i<Array.Count;i++)
	{
		if(Pos+i >= Count)
		{
			Add(Array.elements[i]);
		}
		else
		{
            elements[Pos+i] = Array.elements[i];
        }
    }
}
//---------------------------------------------------------------------------
template <typename Type>
Type& __fastcall TArrayClass<Type>::Last(void)
{
	if(Count() == 0)
	{
		throw EOutOfArrayRange("Last Element", typeid(Type).name());
	}
	return elements[elements.size()-1];
}
//---------------------------------------------------------------------------
template <typename Type>
const Type __fastcall TArrayClass<Type>::Last(void) const
{
	if(Count() == 0)
	{
		throw EOutOfArrayRange("Last Element", typeid(Type).name());
	}
	return elements[elements.size()-1];
}
//---------------------------------------------------------------------------
template <typename Type>
int __fastcall TArrayClass<Type>::Count(void) const
{
	return elements.size();
}
//---------------------------------------------------------------------------
template <typename Type>
int __fastcall TArrayClass<Type>::Add(Type s)
{
	//if(onChanging != NULL) try{ onChanging(*this);}catch(...){}
	elements.push_back(s);
	//if(onChange != NULL) try{ onChange(*this);}catch(...){}
	return Count()-1;
}
//---------------------------------------------------------------------------
template <typename Type>
int __fastcall TArrayClass<Type>::Add(TArrayClass<Type> Array)
{
	//if(onChanging != NULL) try{ onChanging(*this);}catch(...){}
	elements.insert(elements.end(),Array.elements.begin(),Array.elements.end());
	//if(onChange != NULL) try{ onChange(*this);}catch(...){}
	return Count()-1;
}
//---------------------------------------------------------------------------
template <typename Type>
void __fastcall TArrayClass<Type>::Delete(int Index)
{
	//if(onChanging != NULL) try{ onChanging(*this);}catch(...){}
	if(Index >= Count() || Index < 0)
	{
		throw EOutOfArrayRange(Index,Count(), typeid(Type).name());
	}
	elements.erase(elements.begin() + Index);
	//if(onChange != NULL) try{ onChange(*this);}catch(...){}
}
//---------------------------------------------------------------------------
template <typename Type>
void __fastcall TArrayClass<Type>::Delete(int Begin, int End)
{
	//if(onChanging != NULL) try{ onChanging(*this);}catch(...){}
	if(Begin < 0 || End >= Count || Begin > End)
	{
		throw EOutOfArrayRange(Begin,End,Count, typeid(Type).name());
	}
	elements.erase(elements.begin()+Begin,elements.begin()+End+1);
	//if(onChange != NULL) try{ onChange(*this);}catch(...){}
}
//---------------------------------------------------------------------------
template <typename Type>
void __fastcall TArrayClass<Type>::Insert(int Position, Type s)
{
	//if(onChanging != NULL) try{ onChanging(*this);}catch(...){}
	if(Position >= Count() || Position < 0)
	{
		throw EOutOfArrayRange(Position,Count(), typeid(Type).name());
	}
	elements.insert(elements.begin()+Position,s);
	//if(onChange != NULL) try{ onChange(*this);}catch(...){}
}
//---------------------------------------------------------------------------
template <typename Type>
void __fastcall TArrayClass<Type>::Insert(int Position, TArrayClass<Type> Array)
{
	////if(onChanging != NULL) try{ onChanging(*this);}catch(...){}
	if(Position >= Count || Position < 0)
	{
		throw EOutOfArrayRange(Position,Count, typeid(Type).name());
	}
	elements.insert(elements.begin()+Position,Array.elements.begin(),Array.elements.end());
	////if(onChange != NULL) try{ onChange(*this);}catch(...){}
}
//---------------------------------------------------------------------------
template <typename Type>
void __fastcall TArrayClass<Type>::Clear(void)
{
	////if(onChanging != NULL) try{ onChanging(*this);}catch(...){}
	elements.clear();
	//if(onChange != NULL) try{ onChange(*this);}catch(...){}
}
//---------------------------------------------------------------------------
template <typename Type>
TArrayClass<Type> __fastcall TArrayClass<Type>::Interval(int PosStart, int PosEnd) const
{
	TArrayClass<Type> temp;
	if(PosStart < 0 || PosEnd >= Count || PosEnd < PosStart)
	{
		throw EOutOfArrayRange(PosStart,PosEnd,Count, typeid(Type).name());
	}
	temp.Add(*this,PosStart,PosEnd);
	return temp;
}
//---------------------------------------------------------------------------
template <typename Type>
TArrayClass<Type> __fastcall TArrayClass<Type>::SubArr(int Pos, int Count) const
{
	return Interval(Pos,Pos+Count-1);
}
//---------------------------------------------------------------------------
template <typename Type>
Type* __fastcall TArrayClass<Type>::Pointer(void)
{
	if(Count() == 0)
		throw EOutOfArrayRange("Array is empty", typeid(Type).name());
	return &elements[0];
}
//---------------------------------------------------------------------------
template <typename Type>
Type& __fastcall TArrayClass<Type>::operator[](int index)
{
	if(index < 0 || index >= Count())
		throw EOutOfArrayRange(index,Count(), typeid(Type).name());
	return elements[index];
}
//---------------------------------------------------------------------------
template <typename Type>
const Type __fastcall TArrayClass<Type>::operator[](int index) const
{
	if(index < 0 || index >= Count())
		throw EOutOfArrayRange(index,Count(), typeid(Type).name());
	return elements[index];
}
//---------------------------------------------------------------------------
#endif
