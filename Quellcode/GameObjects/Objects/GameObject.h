//---------------------------------------------------------------------------

#ifndef GameObjectH
#define GameObjectH
#include "../Stuff.h"
#include "GameFlow.h"
#include "XmlSerialize.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Media.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Platform.Win.hpp>
//---------------------------------------------------------------------------
enum class TFixedSide {Width, Height};
//---------------------------------------------------------------------------
typedef _di_IXMLNode TGameXmlNode;
class PACKAGE TGameBase : public TControl, public IXmlSerializable
{
private:


protected:
	virtual String __fastcall GetResourcePath(void)=0;
	void __fastcall SetName(const TComponentName NewName);
	void __fastcall BeforeDestruction(void);

public:
	__fastcall TGameBase(TComponent *Owner);

	TGameXmlNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(TGameXmlNode Node);

	String __fastcall Path(void);
	String __fastcall ResourceRoot(void);

	static String __fastcall DesignPath(void);
	static String __fastcall RunPath(void);
__published:
	__property String ResourcePath = {read=GetResourcePath};
};
//---------------------------------------------------------------------------
class TBackground;
class TGameFlowList;
class PACKAGE TGameObject : public TGameBase
{
friend TGameFlowList;
private:
	TFixedSide FFixedSide;
	TImage *imgObj;
	bool FIsRunning;

	TArrayClass<TGameFlowList*> FObjFlows;

	void __fastcall AddFlowToList(TGameFlowList* List);
	void __fastcall DeleteFlowFromList(TGameFlowList* List);

	void __fastcall CheckObjForReference(TGameObject *Obj);

	float FOriginalWidth;
	float FOriginalHeight;
	void __fastcall SetOriginalWidth(const float Value);
	void __fastcall SetOriginalHeight(const float Value);

	TBackground* __fastcall GetBackground(void);

	float __fastcall GetLeft(void){ return Position->X; };
	float __fastcall GetTop(void){ return Position->Y; };

protected:
	virtual void __fastcall Resize(void);

	virtual String __fastcall GetResourcePath(void);

	void __fastcall BeforeDestruction(void);
	void __fastcall Loaded(void);

	virtual void __fastcall DoStart(void){};
	virtual void __fastcall DoStop(void){};

	virtual void __fastcall DoRealign(void);
	virtual bool __fastcall GetChildrenMatrix(System::Math::Vectors::TMatrix &Matrix, bool &Simple);
	virtual void __fastcall SetHeight(const float Value);
	virtual void __fastcall SetWidth(const float Value);
	virtual void __fastcall Paint(void);

	virtual void __fastcall PicLoaded(TImage *ImgObj){};

	virtual void __fastcall SetLeft(float Value){ Position->X = Value; };
	virtual void __fastcall SetTop(float Value){ Position->Y = Value; };

	virtual void __fastcall FlowListStarted(TGameFlowList *List){};
	virtual void __fastcall FlowListStopped(TGameFlowList *List){};
	virtual void __fastcall FlowListPaused(TGameFlowList *List){};
	virtual void __fastcall FlowListFinished(TGameFlowList *List){};

public:
	void __fastcall Start(void);
	void __fastcall Stop(void);

	bool __fastcall IsRunning(void){ return FIsRunning; };

	bool __fastcall IsOwnerRunning(void);

	void __fastcall LoadPic(String FileName);

	__fastcall TGameObject(TComponent *Owner);
	__fastcall ~TGameObject(void);

	__property TBackground* Background = {read=GetBackground};

__published:
	__property TFixedSide FixedSide = {read=FFixedSide,write=FFixedSide};
	__property float OriginalWidth = {read=FOriginalWidth, write=SetOriginalWidth};
	__property float OriginalHeight = {read=FOriginalHeight, write=SetOriginalHeight};
	__property Width;
	__property Height;
	__property float Left = {read=GetLeft,write=SetLeft};
	__property float Top = {read=GetTop,write=SetTop};
	__property CanFocus = {default=1};
	__property TabStop = {default=1};

};
#endif
