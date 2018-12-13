//---------------------------------------------------------------------------

#ifndef FlowTreeH
#define FlowTreeH
#include "../CustomTree.h"
#include "FlowLists.h"
#include "ConversationGUI.h"
//---------------------------------------------------------------------------
class PACKAGE TConvGUIFlowList : public TVariadicFlowList
{
private:
	bool FOpenGUIOnFinish;
protected:
	void __fastcall Finished(void)
	{
		if(FOpenGUIOnFinish)
			TConversationGUI::Instance()->Open();
	};
public:
	__fastcall TConvGUIFlowList(TGameObject* Owner): TVariadicFlowList(Owner), FOpenGUIOnFinish(false){};
__published:
	__property bool OpenGUIOnFinish = {read=FOpenGUIOnFinish,write=FOpenGUIOnFinish};
};
//---------------------------------------------------------------------------
class PACKAGE TFlowTreeItem : public TVectorTreeItem, public IXmlSerializable
{
private:
	TConvGUIFlowList *flowList;
	String text;

	bool FHidden;
	bool FHideItem;

	void __fastcall SetFlowList(TConvGUIFlowList *FlowList){ flowList->Assign(FlowList); };

	bool __fastcall GetOpenGUI(void){ return flowList->OpenGUIOnFinish; };
	void __fastcall SetOpenGUI(bool value){ flowList->OpenGUIOnFinish = value; };
public:
	__fastcall TFlowTreeItem(TBasicCustomList *Owner);
	__fastcall ~TFlowTreeItem(void){ delete flowList; };
	String __fastcall DisplayName(void);

	TGameXmlNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(TGameXmlNode Node);

__published:
	__property TConvGUIFlowList *FlowList = {read=flowList,write=SetFlowList};
	__property String Text = {read=text,write=text};

	__property bool Hidden = {read=FHidden,write=FHidden};
	__property bool HideItem = {read=FHideItem,write=FHideItem};
	__property bool OpenGUIOnFinish = {read=GetOpenGUI,write=SetOpenGUI};
};
//---------------------------------------------------------------------------
class PACKAGE TFlowTreeList : public TVectorTree, public IXmlSerializable
{
private:
	void __fastcall SetAllowedClasses(TClassList *ClassList);
public:
	__fastcall TFlowTreeList(TGameObject *Owner);

	TGameXmlNode __fastcall ToXmlNode(void);
	void __fastcall FromXmlNode(TGameXmlNode Node);
};
#endif
