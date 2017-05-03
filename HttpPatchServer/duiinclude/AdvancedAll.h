#ifndef __HEAD__ADVANCEDALL__
#define __HEAD__ADVANCEDALL__
#include <comdef.h>

#include <xstring>
using namespace std;
#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

struct IDUI3DControl;
struct __declspec(uuid("ecce67c6-c02d-43da-b766-ef3a93c69ebe")) IDUI3DControl_;
struct __declspec(uuid("41af8285-2753-4696-983f-a5d30dcb2a53")) DUI3DControl;
struct __declspec(uuid("4802dbe6-b56f-486b-ba04-7471f39190ec")) _IDUI3DControlEvents;
struct IDUIGanT;
struct __declspec(uuid("efc158cd-54db-4cba-90cc-7e7104e2697e")) IDUIGanT_;
struct __declspec(uuid("1141e07e-06b0-4849-8545-ae489117b404")) DUIGanT;
struct __declspec(uuid("54c1cfff-2310-4229-a447-306ef0f2a2fb")) _IDUIGanTEvents;
struct IDUIIP;
struct __declspec(uuid("6cc53057-29dd-4ac2-8551-00de3f94a97f")) IDUIIP_;
struct __declspec(uuid("01ed6b3c-6182-4584-9993-d80a101c3def")) DUIIP;
struct __declspec(uuid("352c2358-843e-4e7c-8597-1cfb603b821f")) _IDUIIPEvents;
struct IDUIGridCtrl;
struct __declspec(uuid("e96b5390-f231-4665-8f7c-78105db5a68e")) IDUIGridCtrl_;
struct __declspec(uuid("68acef89-4362-4dbd-9c42-598a41103b00")) DUIGridCtrl;
struct __declspec(uuid("9be58092-c224-4960-a8db-589f493da577")) _IDUIGridCtrlEvents;
struct IDUIColumn;
struct __declspec(uuid("4f1c741b-b785-4994-bbbb-6064bb421695")) IDUIColumn_;
struct __declspec(uuid("9e25b123-5f16-4a4b-9fb9-1bcaab284e65")) DUIColumn;
struct __declspec(uuid("46ae9967-10cd-4eda-81e5-cb2b47c142a4")) _IDUIColumnEvents;
struct IDUIPie;
struct __declspec(uuid("cf0c1a4c-4d93-4f4a-8d31-2dfbc248efcf")) IDUIPie_;
struct __declspec(uuid("632b8cf0-6563-4a1f-aff4-26b0c9aba4ff")) DUIPie;
struct __declspec(uuid("c3232e9b-3533-46b1-8e8e-a2f662d42c9f")) _IDUIPieEvents;
struct __declspec(uuid("982fd89f-876a-4341-b9c7-cc50d5b4786b")) DUITimeChannel;
struct __declspec(uuid("836b3ae2-f64b-46ec-b05a-8ee58cbf03fb")) DUITimeLine;
struct __declspec(uuid("edcf8004-4dd0-468f-ad35-bb2489430591")) DUITimePointer;
struct __declspec(uuid("59cff00d-2f92-44a7-be9c-a103c6bcb710")) DUITimerRuler;
struct __declspec(uuid("59c87a87-46eb-41bc-b41b-fb115d17a4ef")) IDUITimerRuler;
struct __declspec(uuid("b94df411-f294-4571-883b-db7fe11d9724")) IDUITimeLine;
struct __declspec(uuid("daf492c9-289a-4b7d-bea1-f8ab94fd3fe5")) IDUITimePointer;
struct __declspec(uuid("1cd60734-18b3-4911-b6e4-0cf7c70b2be0")) IDUITimeChannel;
struct IDUITimeAxis;
struct __declspec(uuid("d1b9df53-3df9-40e4-970c-04e571528b70")) IDUITimeAxis_;
struct __declspec(uuid("e44fc9e5-37c6-4797-977f-2c15de5e7867")) DUITimeAxis;
struct __declspec(uuid("6b69bb10-40bd-4c31-abb4-e0030686f77b")) _IDUITimeAxisEvents;
struct IDUIChrome;
struct __declspec(uuid("41aa8b53-456f-4cdb-bb9a-ff691fe19461")) IDUIChrome_;
struct __declspec(uuid("4f862d1d-4045-4a5a-bcd2-e4c8587a5aab")) DUIChrome;
struct __declspec(uuid("4396ac06-7a00-4762-a8b3-b5ae3913d4b6")) _IDUIChromeEvents;
struct IDUICurve;
struct __declspec(uuid("9a414be1-26d0-4fa3-815f-29851080c23a")) IDUICurve_;
struct __declspec(uuid("b166bb51-7e0e-49f2-8896-d4e7aa71d45f")) DUICurve;
struct __declspec(uuid("31e21492-7537-4b2a-8ab6-8fcfc03d74e7")) _IDUICurveEvents;
enum DUI_CURVEPOINTCLICK;

struct __declspec(uuid("fb708cd7-1e12-4754-bb90-97729dab2f5b")) IDUIDateTime;
struct IDUITimeRuler;
struct __declspec(uuid("44fce1b5-1401-4c31-9b26-4f17b6f773f4")) IDUITimeRuler_;
struct __declspec(uuid("22eac3cd-f118-4f4a-817a-e8a6a9a7fc1e")) DUITimeRuler;
struct __declspec(uuid("816bb4e4-9383-4f2a-a0b4-86a81105b754")) _IDUITimeRulerEvents;
struct IDUIBasicLine;
struct __declspec(uuid("fc041a68-fc6a-46ef-843a-1015ec820b4e")) IDUIBasicLine_;
struct __declspec(uuid("33708b11-7963-434d-95e7-fe59d19bd0ab")) DUIBasicLine;
struct __declspec(uuid("87ef27ad-439e-4e5d-8ae3-b7aee1714bf5")) _IDUIBasicLineEvents;
struct __declspec(uuid("700a4353-9892-4de1-b816-a7d164f9d802")) DUISpaceItem;
struct __declspec(uuid("3f1abd8b-79cc-4e6b-8a28-0bb21ab765e1")) _IDUISpaceItemEvents;
struct __declspec(uuid("c5911d8e-ae30-455c-924a-c51e75d54c77")) DUIItemGroup;
struct __declspec(uuid("12e375df-5bcd-4372-92af-fe9ffe5d0d20")) _IDUIItemGroupEvents;
struct __declspec(uuid("231484e9-26d2-4888-b31b-8d8b063c4dea")) DUIScrollItem;
struct __declspec(uuid("213eae81-f74e-4b1f-8f00-a85dcacbe76d")) _IDUIScrollItemEvents;
struct __declspec(uuid("83b16de0-d4fd-43be-973d-465f8cdbd665")) IDUISpaceItem;
enum DUISCROLLITEM_STATE;

struct __declspec(uuid("7cb83b49-4601-4c76-a3f8-333bca07be0b")) IDUIScrollItem;
struct __declspec(uuid("2f348557-e1c7-44bd-a23b-9b2de83bbedf")) IDUIItemGroup;
struct IDUIScrollFairy;
struct __declspec(uuid("dd56cd5b-b096-410d-a3e4-ff2b879f1466")) IDUIScrollFairy_;
struct __declspec(uuid("d9dde5e9-0959-4f63-b2d3-da7905c63b68")) DUIScrollFairy;
struct __declspec(uuid("771ade72-7aae-45b6-9499-2073af0d3b76")) _IDUIScrollFairyEvents;
enum ScrollFairyMsgID;

struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) DUIScrollfairyNotifyInfo;
enum DUI_AXISMSGID;

struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) DUIAxisNotifyInfo;
enum PlayMode;

struct __declspec(uuid("370f1d24-4ddd-4f49-80bc-77ebe70be992")) DataTime;
enum TIMEAXIS_HITTEST;

enum TimeAxisMsgID;

enum ChannelState;

enum DUITIMERULER_NOTIFY;

enum DUISCROLLFAIRY_NOTIFY;

enum DUISCROLLFAIRY_NOTIFY
{ 
	DUISF_NOTIFY = 3217 
};

enum DUITIMERULER_NOTIFY
{ 
	DUIGANT_INITSUCCESE = 6662,
	DUIGANT_LBUTTONDOWN = 6659,
	DUIGANT_MBUTTONDOWN = 6660,
	DUIGANT_RBUTTONDOWN = 6661,
	DUITR_MOUSEIN = 6657,
	DUITR_MOUSEOUT = 6658,
	DUITR_TIMECHANGE = 6656 
};

enum ChannelState
{ 
	CHANNEL_DISABLED = 3,
	CHANNEL_HOT = 1,
	CHANNEL_LAST = 4,
	CHANNEL_NORMAL = 0,
	CHANNEL_PRESS = 2 
};

enum TimeAxisMsgID
{ 
	DUI_TIMEAXIS_BTNLBUTTONDOWN = 6031,
	DUI_TIMEAXIS_BTNLBUTTONUP = 6032,
	DUI_TIMEAXIS_CHANNELRBUTTONDOWN = 6039,
	DUI_TIMEAXIS_CHECKBOXLBUTTONDOWN = 6050,
	DUI_TIMEAXIS_ENDMARQUEE = 6043,
	DUI_TIMEAXIS_HORSCROLL_LBUTTONDOWN = 6047,
	DUI_TIMEAXIS_HORSCROLL_LBUTTONUP = 6048,
	DUI_TIMEAXIS_HORSCROLL_NOTIFY = 6045,
	DUI_TIMEAXIS_LBUTTONDOWN = 6024,
	DUI_TIMEAXIS_LBUTTONUP = 6025,
	DUI_TIMEAXIS_MOUSEHOVER = 6049,
	DUI_TIMEAXIS_MOUSEWHEEL = 6026,
	DUI_TIMEAXIS_MOUSEWHEEL_SCROLLCHANNEL = 6041,
	DUI_TIMEAXIS_POINTERDBCLICK = 6033,
	DUI_TIMEAXIS_POINTERDRAGING = 6034,
	DUI_TIMEAXIS_POINTERENDDRAG = 6036,
	DUI_TIMEAXIS_POINTERSTARTDRAG = 6037,
	DUI_TIMEAXIS_POINTOUTRANG = 6035,
	DUI_TIMEAXIS_STARTMARQUEE = 6042,
	DUI_TIMEAXIS_SYNCTIPLBUTTONDOWN = 6044,
	DUI_TIMEAXIS_TAGLBUTTONDOWN = 6028,
	DUI_TIMEAXIS_TAGLBUTTONUP = 6029,
	DUI_TIMEAXIS_TAGLDBCLICK = 6030,
	DUI_TIMEAXIS_TAGMOUSEMOVE = 6027,
	DUI_TIMEAXIS_TAGRBUTTONDOWN = 6038,
	DUI_TIMEAXIS_UNCHECKEDTAG = 6040,
	DUI_TIMEAXIS_VERSCROLL_NOTIFY = 6046 
};

enum TIMEAXIS_HITTEST
{ 
	TIMEAXIS_SCROLLCHANNEL = 1,
	TIMEAXIS_TIMECHANNEL = 2,
	TIMEAXIS_TIMERULER = 0 
};

struct __declspec(uuid("370f1d24-4ddd-4f49-80bc-77ebe70be992")) DataTime
{
	long 	nYear;
	long 	nMonth;
	long 	nDay;
	long 	nHour;
	long 	nMinute;
	long 	nSecond;
};

enum PlayMode
{ 
	AsyncMode = 1,
	SyncMode = 0 
};

struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) DUIAxisNotifyInfo
{
	enum TimeAxisMsgID 	eDUIAxisMsgId;
	OLE_HANDLE 	lParam1;
	OLE_HANDLE 	lParam2;
	OLE_HANDLE 	lParam3;
	OLE_HANDLE 	lParam4;
	OLE_HANDLE 	lParam5;
};

enum DUI_AXISMSGID
{ 
	DUIAXIS_NOTIFY = 3473 
};

struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) DUIScrollfairyNotifyInfo
{
	enum ScrollFairyMsgID 	eDUIMsgId;
	long 	lParam1;
	long 	lParam2;
	long 	lParam3;
	long 	lParam4;
	long 	lParam5;
};

enum ScrollFairyMsgID
{ 
	DUISCROLLITEM_CHANGE = 5,
	DUISCROLLITEM_CHANGING = 6,
	DUISCROLLITEM_CUSTOMCLICK = 14,
	DUISCROLLITEM_DBLBUTTONUP = 4,
	DUISCROLLITEM_DRAGGING = 11,
	DUISCROLLITEM_ENDDRAG = 12,
	DUISCROLLITEM_LBUTTONDOWN = 3,
	DUISCROLLITEM_LBUTTONUP = 2,
	DUISCROLLITEM_MOSEMOVE = 1,
	DUISCROLLITEM_MOUSELEAVE = 13,
	DUISCROLLITEM_RBUTTONDOWN = 15,
	DUISCROLLITEM_REMOVE = 7,
	DUISCROLLITEM_STARTDRAG = 10,
	DUISCROLLSPACEITEM_LBUTTONDOWN = 8,
	DUISCROLLSPACEITEM_LBUTTONUP = 9 
};

struct __declspec(uuid("771ade72-7aae-45b6-9499-2073af0d3b76")) _IDUIScrollFairyEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("dd56cd5b-b096-410d-a3e4-ff2b879f1466")) IDUIScrollFairy_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_AddGroup(long nID, BSTR strName, struct IDUIItemGroup **pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveGroupByID(long nID, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveGroupByName(BSTR strName, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveAllGroup() = 0;
	virtual HRESULT __stdcall raw_GetGroupByName(BSTR strName, struct IDUIItemGroup **pResult) = 0;
	virtual HRESULT __stdcall raw_GetGroupByID(long nID, struct IDUIItemGroup **pResult) = 0;
	virtual HRESULT __stdcall raw_GetCount(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFocusGroupByID(long nID, VARIANT_BOOL bRedraw  ) = 0;
	virtual HRESULT __stdcall raw_SetFocusGroupByName(BSTR strName, VARIANT_BOOL bRedraw  ) = 0;
	virtual HRESULT __stdcall raw_GetFocusGroup(struct IDUIItemGroup **pResult) = 0;
	virtual HRESULT __stdcall raw_SetScrollReCalcRgn(VARIANT_BOOL bSetRgn  ) = 0;
	virtual HRESULT __stdcall raw_ScrollOver(VARIANT_BOOL bEnd  ) = 0;

	//
	//Method Wrapper
	//
	struct IDUIItemGroup * AddGroup(long  nID, tstring  strName  );
	BOOL  RemoveGroupByID(long  nID  );
	BOOL  RemoveGroupByName(tstring  strName  );
	void RemoveAllGroup();
	struct IDUIItemGroup * GetGroupByName(tstring  strName  );
	struct IDUIItemGroup * GetGroupByID(long  nID  );
	long  GetCount();
	void SetFocusGroupByID(long  nID, BOOL  bRedraw  );
	void SetFocusGroupByName(tstring  strName, BOOL  bRedraw  );
	struct IDUIItemGroup * GetFocusGroup();
	void SetScrollReCalcRgn(BOOL  bSetRgn  );
	void ScrollOver(BOOL  bEnd  );
};

struct IDUIScrollFairy : IDUIControlBase
{

	//
	//Method Wrapper
	//
	struct IDUIItemGroup * AddGroup(long  nID, tstring  strName  );
	BOOL  RemoveGroupByID(long  nID  );
	BOOL  RemoveGroupByName(tstring  strName  );
	void RemoveAllGroup();
	struct IDUIItemGroup * GetGroupByName(tstring  strName  );
	struct IDUIItemGroup * GetGroupByID(long  nID  );
	long  GetCount();
	void SetFocusGroupByID(long  nID, BOOL  bRedraw  );
	void SetFocusGroupByName(tstring  strName, BOOL  bRedraw  );
	struct IDUIItemGroup * GetFocusGroup();
	void SetScrollReCalcRgn(BOOL  bSetRgn  );
	void ScrollOver(BOOL  bEnd  );
};

struct __declspec(uuid("2f348557-e1c7-44bd-a23b-9b2de83bbedf")) IDUIItemGroup : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_InsertItem(short nIndex, long nID, BSTR strName, struct IDUIScrollItem **pResult) = 0;
	virtual HRESULT __stdcall raw_AppendItem(long nID, BSTR strName, struct IDUIScrollItem **pResult) = 0;
	virtual HRESULT __stdcall raw_InsertItemWithImage(short nIndex, long nID, BSTR strName, BSTR strImagePath, short nFrames, VARIANT_BOOL bHorz, struct IDUIScrollItem **pResult) = 0;
	virtual HRESULT __stdcall raw_AppendItemWithImage(long nID, BSTR strName, BSTR strImagePath, short nFrames, VARIANT_BOOL bHorz, struct IDUIScrollItem **pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveItemByID(long nID, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveItemByName(BSTR strName, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveItem(struct IDUIScrollItem *pItem, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveAllItems() = 0;
	virtual HRESULT __stdcall raw_GetItemByID(long nID, struct IDUIScrollItem **pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemByName(BSTR strName, struct IDUIScrollItem **pResult) = 0;
	virtual HRESULT __stdcall raw_GetAt(short nIndex, struct IDUIScrollItem **pResult) = 0;
	virtual HRESULT __stdcall raw_GetCount(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetText(BSTR strName  ) = 0;
	virtual HRESULT __stdcall raw_GetText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetID(long nID  ) = 0;
	virtual HRESULT __stdcall raw_GetID(long *pResult) = 0;
	virtual HRESULT __stdcall raw_GetSpaceItem(short nIndex, struct IDUISpaceItem **pResult) = 0;
	virtual HRESULT __stdcall raw_SetSelectedItem(struct IDUIScrollItem *ppResult  ) = 0;
	virtual HRESULT __stdcall raw_SetScrollPos(long nPos  ) = 0;
	virtual HRESULT __stdcall raw_GetScrollPos(long *pResult) = 0;
	virtual HRESULT __stdcall raw_GetTotalLength(long *pResult) = 0;

	//
	//Method Wrapper
	//
	struct IDUIScrollItem * InsertItem(short  nIndex, long  nID, tstring  strName  );
	struct IDUIScrollItem * AppendItem(long  nID, tstring  strName  );
	struct IDUIScrollItem * InsertItemWithImage(short  nIndex, long  nID, tstring  strName, tstring  strImagePath, short  nFrames, BOOL  bHorz  );
	struct IDUIScrollItem * AppendItemWithImage(long  nID, tstring  strName, tstring  strImagePath, short  nFrames, BOOL  bHorz  );
	BOOL  RemoveItemByID(long  nID  );
	BOOL  RemoveItemByName(tstring  strName  );
	BOOL  RemoveItem(struct IDUIScrollItem * pItem  );
	void RemoveAllItems();
	struct IDUIScrollItem * GetItemByID(long  nID  );
	struct IDUIScrollItem * GetItemByName(tstring  strName  );
	struct IDUIScrollItem * GetAt(short  nIndex  );
	long  GetCount();
	void SetText(tstring  strName  );
	tstring  GetText();
	void SetID(long  nID  );
	long  GetID();
	struct IDUISpaceItem * GetSpaceItem(short  nIndex  );
	void SetSelectedItem(struct IDUIScrollItem * ppResult  );
	void SetScrollPos(long  nPos  );
	long  GetScrollPos();
	long  GetTotalLength();
};

struct __declspec(uuid("7cb83b49-4601-4c76-a3f8-333bca07be0b")) IDUIScrollItem : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetText(BSTR strName, VARIANT_BOOL bRefresh  ) = 0;
	virtual HRESULT __stdcall raw_GetText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetID(long nID  ) = 0;
	virtual HRESULT __stdcall raw_GetID(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetState(enum DUISCROLLITEM_STATE eState, VARIANT_BOOL bRefresh  ) = 0;
	virtual HRESULT __stdcall raw_GetState(enum DUISCROLLITEM_STATE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetImage(BSTR strImagePath, short nFrames, VARIANT_BOOL bHorz  ) = 0;
	virtual HRESULT __stdcall raw_GetImagePath(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBitmap(OLE_HANDLE hBmp, enum DUISCROLLITEM_STATE eState  ) = 0;
	virtual HRESULT __stdcall raw_GetBitmap(enum DUISCROLLITEM_STATE eState, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetInfoPanel(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetResObject(BSTR strName, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetRect(struct SkinRect *pResult) = 0;
	virtual HRESULT __stdcall raw_GetIndex(long *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetText(tstring  strName, BOOL  bRefresh  );
	tstring  GetText();
	void SetID(long  nID  );
	long  GetID();
	void SetState(enum DUISCROLLITEM_STATE  eState, BOOL  bRefresh  );
	enum DUISCROLLITEM_STATE  GetState();
	void SetImage(tstring  strImagePath, short  nFrames, BOOL  bHorz  );
	tstring  GetImagePath();
	void SetBitmap(OLE_HANDLE  hBmp, enum DUISCROLLITEM_STATE  eState  );
	OLE_HANDLE  GetBitmap(enum DUISCROLLITEM_STATE  eState  );
	IDUIControlBase* GetInfoPanel();
	OLE_HANDLE  GetResObject(tstring  strName  );
	struct SkinRect  GetRect();
	long  GetIndex();
};

enum DUISCROLLITEM_STATE
{ 
	DUISCROLLITEM_STATE_DISABLED = 3,
	DUISCROLLITEM_STATE_HOT = 1,
	DUISCROLLITEM_STATE_LAST = 4,
	DUISCROLLITEM_STATE_NORMAL = 0,
	DUISCROLLITEM_STATE_PRESS = 2 
};

struct __declspec(uuid("83b16de0-d4fd-43be-973d-465f8cdbd665")) IDUISpaceItem : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetIndex(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetImage(OLE_HANDLE hBitmap  ) = 0;
	virtual HRESULT __stdcall raw_GetRect(struct SkinRect *pResult) = 0;

	//
	//Method Wrapper
	//
	long  GetIndex();
	void SetImage(OLE_HANDLE  hBitmap  );
	struct SkinRect  GetRect();
};

struct __declspec(uuid("213eae81-f74e-4b1f-8f00-a85dcacbe76d")) _IDUIScrollItemEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("12e375df-5bcd-4372-92af-fe9ffe5d0d20")) _IDUIItemGroupEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("3f1abd8b-79cc-4e6b-8a28-0bb21ab765e1")) _IDUISpaceItemEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("87ef27ad-439e-4e5d-8ae3-b7aee1714bf5")) _IDUIBasicLineEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("fc041a68-fc6a-46ef-843a-1015ec820b4e")) IDUIBasicLine_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_InsertXData(long nIndex, BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_InsertYData(double dYoint  ) = 0;
	virtual HRESULT __stdcall raw_InsertPointData(long index, double yPoint  ) = 0;
	virtual HRESULT __stdcall raw_InsertIconData(unsigned long dR, unsigned long dG, unsigned long dB, BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_SetLeftText(BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_GetLeftText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTopText(BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_GetTopText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_EraseXData(int index  ) = 0;
	virtual HRESULT __stdcall raw_EraseXAllData() = 0;
	virtual HRESULT __stdcall raw_SetBasePointNdx(int index  ) = 0;
	virtual HRESULT __stdcall raw_GetBasePointNdx(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBasePointNdy(int index  ) = 0;
	virtual HRESULT __stdcall raw_GetBasePointNdy(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetRightLineNdx(int index  ) = 0;
	virtual HRESULT __stdcall raw_GetRightLineNdx(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetRightLineNdy(int index  ) = 0;
	virtual HRESULT __stdcall raw_GetRightLineNdy(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetRightLineLength(int index  ) = 0;
	virtual HRESULT __stdcall raw_GetRightLineLength(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTextTopHeight(long index  ) = 0;
	virtual HRESULT __stdcall raw_GetTextTopHeight(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTextRightWidth(long index  ) = 0;
	virtual HRESULT __stdcall raw_GetTextRightWidth(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTextLeftWidth(long index  ) = 0;
	virtual HRESULT __stdcall raw_GetTextLeftWidth(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetYHeight(int index  ) = 0;
	virtual HRESULT __stdcall raw_GetYHeight(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetLeftBackColor(unsigned long dR, unsigned long dG, unsigned long dB  ) = 0;
	virtual HRESULT __stdcall raw_SetTopBackColor(unsigned long dR, unsigned long dG, unsigned long dB  ) = 0;
	virtual HRESULT __stdcall raw_SetCenterBackColor(unsigned long dR, unsigned long dG, unsigned long dB  ) = 0;
	virtual HRESULT __stdcall raw_SetRightBackColor(unsigned long dR, unsigned long dG, unsigned long dB  ) = 0;
	virtual HRESULT __stdcall raw_SetMainBackColor(unsigned long dR, unsigned long dG, unsigned long dB  ) = 0;
	virtual HRESULT __stdcall raw_SetLeftFont(BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_GetLeftFont(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTopFont(BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_GetTopFont(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetRightFont(BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_GetRightFont(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetXFont(BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_GetXFont(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetYFont(BSTR bstr  ) = 0;
	virtual HRESULT __stdcall raw_GetYFont(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetLeftFontSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetLeftFontSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTopFontSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetTopFontSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetRightFontSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetRightFontSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetRightLineSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetRightLineSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetXLineSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetXLineSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetXFontSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetXFontSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetYLineSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetYLineSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetYFontSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetYFontSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetLineDataLineSize(float fsize  ) = 0;
	virtual HRESULT __stdcall raw_GetLineDataLineSize(float *pResult) = 0;
	virtual HRESULT __stdcall raw_CreateLine(int index, unsigned long dR, unsigned long dG, unsigned long dB  ) = 0;
	virtual HRESULT __stdcall raw_InsertLineData(int indexLine, int indexXpoint, double yPoint  ) = 0;
	virtual HRESULT __stdcall raw_InsertPillarData(int index, int xIndex, float yNum, unsigned long dR, unsigned long dG, unsigned long dB  ) = 0;
	virtual HRESULT __stdcall raw_InsertPillarSubData(int num, int index, int xIndex, float yNum  ) = 0;
	virtual HRESULT __stdcall raw_InsertXSubData(long nIndex, BSTR bstr  ) = 0;

	//
	//Method Wrapper
	//
	void InsertXData(long  nIndex, tstring  bstr  );
	void InsertYData(double  dYoint  );
	void InsertPointData(long  index, double  yPoint  );
	void InsertIconData(unsigned long  dR, unsigned long  dG, unsigned long  dB, tstring  bstr  );
	void SetLeftText(tstring  bstr  );
	tstring  GetLeftText();
	void SetTopText(tstring  bstr  );
	tstring  GetTopText();
	void EraseXData(int  index  );
	void EraseXAllData();
	void SetBasePointNdx(int  index  );
	int  GetBasePointNdx();
	void SetBasePointNdy(int  index  );
	int  GetBasePointNdy();
	void SetRightLineNdx(int  index  );
	int  GetRightLineNdx();
	void SetRightLineNdy(int  index  );
	int  GetRightLineNdy();
	void SetRightLineLength(int  index  );
	int  GetRightLineLength();
	void SetTextTopHeight(long  index  );
	long  GetTextTopHeight();
	void SetTextRightWidth(long  index  );
	long  GetTextRightWidth();
	void SetTextLeftWidth(long  index  );
	long  GetTextLeftWidth();
	void SetYHeight(int  index  );
	int  GetYHeight();
	void SetLeftBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetTopBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetCenterBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetRightBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetMainBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetLeftFont(tstring  bstr  );
	tstring  GetLeftFont();
	void SetTopFont(tstring  bstr  );
	tstring  GetTopFont();
	void SetRightFont(tstring  bstr  );
	tstring  GetRightFont();
	void SetXFont(tstring  bstr  );
	tstring  GetXFont();
	void SetYFont(tstring  bstr  );
	tstring  GetYFont();
	void SetLeftFontSize(float  fsize  );
	float  GetLeftFontSize();
	void SetTopFontSize(float  fsize  );
	float  GetTopFontSize();
	void SetRightFontSize(float  fsize  );
	float  GetRightFontSize();
	void SetRightLineSize(float  fsize  );
	float  GetRightLineSize();
	void SetXLineSize(float  fsize  );
	float  GetXLineSize();
	void SetXFontSize(float  fsize  );
	float  GetXFontSize();
	void SetYLineSize(float  fsize  );
	float  GetYLineSize();
	void SetYFontSize(float  fsize  );
	float  GetYFontSize();
	void SetLineDataLineSize(float  fsize  );
	float  GetLineDataLineSize();
	void CreateLine(int  index, unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void InsertLineData(int  indexLine, int  indexXpoint, double  yPoint  );
	void InsertPillarData(int  index, int  xIndex, float  yNum, unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void InsertPillarSubData(int  num, int  index, int  xIndex, float  yNum  );
	void InsertXSubData(long  nIndex, tstring  bstr  );
};

struct IDUIBasicLine : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void InsertXData(long  nIndex, tstring  bstr  );
	void InsertYData(double  dYoint  );
	void InsertPointData(long  index, double  yPoint  );
	void InsertIconData(unsigned long  dR, unsigned long  dG, unsigned long  dB, tstring  bstr  );
	void SetLeftText(tstring  bstr  );
	tstring  GetLeftText();
	void SetTopText(tstring  bstr  );
	tstring  GetTopText();
	void EraseXData(int  index  );
	void EraseXAllData();
	void SetBasePointNdx(int  index  );
	int  GetBasePointNdx();
	void SetBasePointNdy(int  index  );
	int  GetBasePointNdy();
	void SetRightLineNdx(int  index  );
	int  GetRightLineNdx();
	void SetRightLineNdy(int  index  );
	int  GetRightLineNdy();
	void SetRightLineLength(int  index  );
	int  GetRightLineLength();
	void SetTextTopHeight(long  index  );
	long  GetTextTopHeight();
	void SetTextRightWidth(long  index  );
	long  GetTextRightWidth();
	void SetTextLeftWidth(long  index  );
	long  GetTextLeftWidth();
	void SetYHeight(int  index  );
	int  GetYHeight();
	void SetLeftBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetTopBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetCenterBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetRightBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetMainBackColor(unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void SetLeftFont(tstring  bstr  );
	tstring  GetLeftFont();
	void SetTopFont(tstring  bstr  );
	tstring  GetTopFont();
	void SetRightFont(tstring  bstr  );
	tstring  GetRightFont();
	void SetXFont(tstring  bstr  );
	tstring  GetXFont();
	void SetYFont(tstring  bstr  );
	tstring  GetYFont();
	void SetLeftFontSize(float  fsize  );
	float  GetLeftFontSize();
	void SetTopFontSize(float  fsize  );
	float  GetTopFontSize();
	void SetRightFontSize(float  fsize  );
	float  GetRightFontSize();
	void SetRightLineSize(float  fsize  );
	float  GetRightLineSize();
	void SetXLineSize(float  fsize  );
	float  GetXLineSize();
	void SetXFontSize(float  fsize  );
	float  GetXFontSize();
	void SetYLineSize(float  fsize  );
	float  GetYLineSize();
	void SetYFontSize(float  fsize  );
	float  GetYFontSize();
	void SetLineDataLineSize(float  fsize  );
	float  GetLineDataLineSize();
	void CreateLine(int  index, unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void InsertLineData(int  indexLine, int  indexXpoint, double  yPoint  );
	void InsertPillarData(int  index, int  xIndex, float  yNum, unsigned long  dR, unsigned long  dG, unsigned long  dB  );
	void InsertPillarSubData(int  num, int  index, int  xIndex, float  yNum  );
	void InsertXSubData(long  nIndex, tstring  bstr  );
};

struct __declspec(uuid("816bb4e4-9383-4f2a-a0b4-86a81105b754")) _IDUITimeRulerEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("44fce1b5-1401-4c31-9b26-4f17b6f773f4")) IDUITimeRuler_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetBeginTime(struct IDUIDateTime begTime  ) = 0;
	virtual HRESULT __stdcall raw_GetBeginTime(struct IDUIDateTime *pResult) = 0;
	virtual HRESULT __stdcall raw_SetEndTime(struct IDUIDateTime endTime  ) = 0;
	virtual HRESULT __stdcall raw_GetEndTime(struct IDUIDateTime *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCurrentTimer(struct IDUIDateTime time  ) = 0;
	virtual HRESULT __stdcall raw_GetCurrentTimer(struct IDUIDateTime *pResult) = 0;
	virtual HRESULT __stdcall raw_SetRectBlockTime(struct IDUIDateTime begTime, struct IDUIDateTime endTime, long *cr  ) = 0;
	virtual HRESULT __stdcall raw_SetMargin(int firstMargin, int lastMargin  ) = 0;
	virtual HRESULT __stdcall raw_SetDefaultTime(struct IDUIDateTime time  ) = 0;
	virtual HRESULT __stdcall raw_SetTriangleWithHeight(int width, int height  ) = 0;
	virtual HRESULT __stdcall raw_SetTriangleBrushColor(long *cr  ) = 0;
	virtual HRESULT __stdcall raw_SetTrianglePen(long *cr, int iPen  ) = 0;
	virtual HRESULT __stdcall raw_ChangeBlockColor(int iNum, long *cr  ) = 0;
	virtual HRESULT __stdcall raw_ChangeBlockTime(int iNum, struct IDUIDateTime begTime, struct IDUIDateTime endTime  ) = 0;
	virtual HRESULT __stdcall raw_DeleteBlockTime(int iNum  ) = 0;
	virtual HRESULT __stdcall raw_SetTimePos(int iPos  ) = 0;
	virtual HRESULT __stdcall raw_GetTimePos(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCanMove(VARIANT_BOOL blBtnDown  ) = 0;
	virtual HRESULT __stdcall raw_SetTimeIntervel(int Hour, int Min, int Sec  ) = 0;
	virtual HRESULT __stdcall raw_SetPointHeight(int height  ) = 0;
	virtual HRESULT __stdcall raw_SetRectBlockTimeByImage(struct IDUIDateTime begTime, struct IDUIDateTime endTime, struct IDUIImageBase *pImageBase  ) = 0;

	//
	//Method Wrapper
	//
	void SetBeginTime(struct IDUIDateTime  begTime  );
	struct IDUIDateTime  GetBeginTime();
	void SetEndTime(struct IDUIDateTime  endTime  );
	struct IDUIDateTime  GetEndTime();
	void SetCurrentTimer(struct IDUIDateTime  time  );
	struct IDUIDateTime  GetCurrentTimer();
	void SetRectBlockTime(struct IDUIDateTime  begTime, struct IDUIDateTime  endTime, long * cr  );
	void SetMargin(int  firstMargin, int  lastMargin  );
	void SetDefaultTime(struct IDUIDateTime  time  );
	void SetTriangleWithHeight(int  width, int  height  );
	void SetTriangleBrushColor(long * cr  );
	void SetTrianglePen(long * cr, int  iPen  );
	void ChangeBlockColor(int  iNum, long * cr  );
	void ChangeBlockTime(int  iNum, struct IDUIDateTime  begTime, struct IDUIDateTime  endTime  );
	void DeleteBlockTime(int  iNum  );
	void SetTimePos(int  iPos  );
	int  GetTimePos();
	void SetCanMove(BOOL  blBtnDown  );
	void SetTimeIntervel(int  Hour, int  Min, int  Sec  );
	void SetPointHeight(int  height  );
	void SetRectBlockTimeByImage(struct IDUIDateTime  begTime, struct IDUIDateTime  endTime, struct IDUIImageBase * pImageBase  );
};

struct IDUITimeRuler : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetBeginTime(struct IDUIDateTime  begTime  );
	struct IDUIDateTime  GetBeginTime();
	void SetEndTime(struct IDUIDateTime  endTime  );
	struct IDUIDateTime  GetEndTime();
	void SetCurrentTimer(struct IDUIDateTime  time  );
	struct IDUIDateTime  GetCurrentTimer();
	void SetRectBlockTime(struct IDUIDateTime  begTime, struct IDUIDateTime  endTime, long * cr  );
	void SetMargin(int  firstMargin, int  lastMargin  );
	void SetDefaultTime(struct IDUIDateTime  time  );
	void SetTriangleWithHeight(int  width, int  height  );
	void SetTriangleBrushColor(long * cr  );
	void SetTrianglePen(long * cr, int  iPen  );
	void ChangeBlockColor(int  iNum, long * cr  );
	void ChangeBlockTime(int  iNum, struct IDUIDateTime  begTime, struct IDUIDateTime  endTime  );
	void DeleteBlockTime(int  iNum  );
	void SetTimePos(int  iPos  );
	int  GetTimePos();
	void SetCanMove(BOOL  blBtnDown  );
	void SetTimeIntervel(int  Hour, int  Min, int  Sec  );
	void SetPointHeight(int  height  );
	void SetRectBlockTimeByImage(struct IDUIDateTime  begTime, struct IDUIDateTime  endTime, struct IDUIImageBase * pImageBase  );
};

struct __declspec(uuid("fb708cd7-1e12-4754-bb90-97729dab2f5b")) IDUIDateTime
{
	int 	Year;
	int 	Month;
	int 	Day;
	int 	Hour;
	int 	Min;
	int 	Sec;
};

enum DUI_CURVEPOINTCLICK
{ 
	DUI_CURVE_DRAGSCOPE = 25857,
	DUI_CURVE_POINTCLICK = 3331,
	DUI_CURVE_SELECTRANGE = 25856,
	DUI_CURVE_WHEELSCOPE = 25858 
};

struct __declspec(uuid("31e21492-7537-4b2a-8ab6-8fcfc03d74e7")) _IDUICurveEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("9a414be1-26d0-4fa3-815f-29851080c23a")) IDUICurve_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_Clear() = 0;
	virtual HRESULT __stdcall raw_SetMaxSize(unsigned int nMaxPoint  ) = 0;
	virtual HRESULT __stdcall raw_InsertLine(unsigned int nIndex, unsigned int fXAxisTime, float fYAxisAmp  ) = 0;
	virtual HRESULT __stdcall raw_SetCurXShowScope(float fStartTime, float fEndTime  ) = 0;
	virtual HRESULT __stdcall raw_GetCurXShowScope(float *nStartTime, float *nEndTime  ) = 0;
	virtual HRESULT __stdcall raw_ShowXAxisGradByStep(unsigned int nStep  ) = 0;
	virtual HRESULT __stdcall raw_ShowXAxisGradByIndex(unsigned int index  ) = 0;
	virtual HRESULT __stdcall raw_SetGridLineVisible(VARIANT_BOOL isShow  ) = 0;
	virtual HRESULT __stdcall raw_SetXGradTextByIndex(unsigned int nRulerIndex, BSTR bstrRulerText  ) = 0;
	virtual HRESULT __stdcall raw_SetHeadName(BSTR bstrHeadName, unsigned long clrText, unsigned int nTextSize  ) = 0;
	virtual HRESULT __stdcall raw_DrawAssisLine(unsigned int nIndex, float fAssisPos, unsigned int DashStyle, OLE_COLOR clrAssisLine, unsigned int nPenSize, VARIANT_BOOL bDrawAssisText  ) = 0;
	virtual HRESULT __stdcall raw_SetAssisLineVisble(unsigned int index, VARIANT_BOOL isVisble  ) = 0;
	virtual HRESULT __stdcall raw_SetLineVisble(unsigned int index, VARIANT_BOOL isVisble  ) = 0;
	virtual HRESULT __stdcall raw_SetLineProp(unsigned int nIndex, unsigned int DashStyle, unsigned int nLineLength, OLE_COLOR ClrLine  ) = 0;
	virtual HRESULT __stdcall raw_SetAssiLineProp(unsigned int nIndex, unsigned int DashStyle, unsigned int nLineLength, OLE_COLOR ClrLine, unsigned int nTextSize  ) = 0;
	virtual HRESULT __stdcall raw_SetFormName(BSTR bstFormName, unsigned long clrText, unsigned int nTextSize  ) = 0;
	virtual HRESULT __stdcall raw_SetWhellSpeed(float nSpeed  ) = 0;
	virtual HRESULT __stdcall raw_GetWhellSpeed(float *nSpeed  ) = 0;
	virtual HRESULT __stdcall raw_AddState(unsigned int nIndex, unsigned int nStartIndex, unsigned int nEndIndex, unsigned long clr, BSTR strStateText  ) = 0;
	virtual HRESULT __stdcall raw_SetState(unsigned int nParentLine, unsigned int nStartIndex, unsigned int nEndIndex, unsigned long clr  ) = 0;
	virtual HRESULT __stdcall raw_SetXAxisUnit(BSTR bstrRangeUnit, OLE_COLOR clrUnit  ) = 0;
	virtual HRESULT __stdcall raw_SetBkImage(struct IDUIImageBase *pImageBase  ) = 0;
	virtual HRESULT __stdcall raw_SetStateHeight(long nStateHeight  ) = 0;
	virtual HRESULT __stdcall raw_SetGridMode(unsigned int nDashStyle, OLE_COLOR clrGrid, unsigned int nGridSize  ) = 0;
	virtual HRESULT __stdcall raw_SetYRangeUnit(BSTR bstrRangeUnit, OLE_COLOR clrUnit  ) = 0;
	virtual HRESULT __stdcall raw_SetDataPointValid(unsigned int index, unsigned int dataIndex, VARIANT_BOOL isValid  ) = 0;
	virtual HRESULT __stdcall raw_SetYAxisRange(float downVal, float upVal  ) = 0;
	virtual HRESULT __stdcall raw_ShowYAxisGradByStep(unsigned int index  ) = 0;
	virtual HRESULT __stdcall raw_ShowYAxisGradByIndex(int nIndex  ) = 0;
	virtual HRESULT __stdcall raw_ShowYAxisTextByIndex(int nIndex  ) = 0;
	virtual HRESULT __stdcall raw_ShowYAxisGradByVal(float fValue  ) = 0;
	virtual HRESULT __stdcall raw_ShowYAxisTextByVal(float fValue  ) = 0;
	virtual HRESULT __stdcall raw_SetFaultPos(unsigned int index, unsigned int FaultStartPos, unsigned int FaultEndPos  ) = 0;
	virtual HRESULT __stdcall raw_SaveToBitmap(BSTR iStep  ) = 0;
	virtual HRESULT __stdcall raw_GetMaxMinValue(unsigned int index, float *maxVal, float *minVal  ) = 0;
	virtual HRESULT __stdcall raw_GetXSpace() = 0;
	virtual HRESULT __stdcall raw_SetYSpace(unsigned int nYSpace  ) = 0;
	virtual HRESULT __stdcall raw_GetYSpace() = 0;
	virtual HRESULT __stdcall raw_SetSpaceTime(float fSpaceTime  ) = 0;
	virtual HRESULT __stdcall raw_SetXTime(float fStartTime, float fEndTime  ) = 0;
	virtual HRESULT __stdcall raw_SetStateSpace(long nStateSpace  ) = 0;
	virtual HRESULT __stdcall raw_SetPointRadius(int nPointRadius  ) = 0;
	virtual HRESULT __stdcall raw_LockDrag(VARIANT_BOOL bDrag  ) = 0;
	virtual HRESULT __stdcall raw_LockWheel(VARIANT_BOOL bCanWheel  ) = 0;
	virtual HRESULT __stdcall raw_ClearAllXAxisGradVisible() = 0;
	virtual HRESULT __stdcall raw_ClearXGradText() = 0;
	virtual HRESULT __stdcall raw_ClearAllYAxisGrad() = 0;
	virtual HRESULT __stdcall raw_ClearAllYAxisGradValText() = 0;
	virtual HRESULT __stdcall raw_SetBkLineSpace(unsigned int nBkLineSpace  ) = 0;
	virtual HRESULT __stdcall raw_SetXGridProperty(unsigned long clrGrad, unsigned int nGridHeight, unsigned int nGridWidth, int nDashStyle  ) = 0;
	virtual HRESULT __stdcall raw_SetYGridProperty(unsigned long clrGrad, unsigned int nGridHeight, unsigned int nGridWidth, int nDashStyle  ) = 0;
	virtual HRESULT __stdcall raw_SetMultiMove(unsigned int nStart, unsigned int nEnd  ) = 0;
	virtual HRESULT __stdcall raw_SetFrameSelection(unsigned long clrSel, int nDashStyle, int nSelWidth  ) = 0;
	virtual HRESULT __stdcall raw_ShowSelection(VARIANT_BOOL bShowSel  ) = 0;
	virtual HRESULT __stdcall raw_IsClone(VARIANT_BOOL bClone  ) = 0;
	virtual HRESULT __stdcall raw_SetXBottomSpace(int nBottomSpace  ) = 0;

	//
	//Method Wrapper
	//
	void Clear();
	void SetMaxSize(unsigned int  nMaxPoint  );
	void InsertLine(unsigned int  nIndex, unsigned int  fXAxisTime, float  fYAxisAmp  );
	void SetCurXShowScope(float  fStartTime, float  fEndTime  );
	void GetCurXShowScope(float * nStartTime, float * nEndTime  );
	void ShowXAxisGradByStep(unsigned int  nStep  );
	void ShowXAxisGradByIndex(unsigned int  index  );
	void SetGridLineVisible(BOOL  isShow  );
	void SetXGradTextByIndex(unsigned int  nRulerIndex, tstring  bstrRulerText  );
	void SetHeadName(tstring  bstrHeadName, unsigned long  clrText, unsigned int  nTextSize  );
	void DrawAssisLine(unsigned int  nIndex, float  fAssisPos, unsigned int  DashStyle, OLE_COLOR  clrAssisLine, unsigned int  nPenSize, BOOL  bDrawAssisText  );
	void SetAssisLineVisble(unsigned int  index, BOOL  isVisble  );
	void SetLineVisble(unsigned int  index, BOOL  isVisble  );
	void SetLineProp(unsigned int  nIndex, unsigned int  DashStyle, unsigned int  nLineLength, OLE_COLOR  ClrLine  );
	void SetAssiLineProp(unsigned int  nIndex, unsigned int  DashStyle, unsigned int  nLineLength, OLE_COLOR  ClrLine, unsigned int  nTextSize  );
	void SetFormName(tstring  bstFormName, unsigned long  clrText, unsigned int  nTextSize  );
	void SetWhellSpeed(float  nSpeed  );
	void GetWhellSpeed(float * nSpeed  );
	void AddState(unsigned int  nIndex, unsigned int  nStartIndex, unsigned int  nEndIndex, unsigned long  clr, tstring  strStateText  );
	void SetState(unsigned int  nParentLine, unsigned int  nStartIndex, unsigned int  nEndIndex, unsigned long  clr  );
	void SetXAxisUnit(tstring  bstrRangeUnit, OLE_COLOR  clrUnit  );
	void SetBkImage(struct IDUIImageBase * pImageBase  );
	void SetStateHeight(long  nStateHeight  );
	void SetGridMode(unsigned int  nDashStyle, OLE_COLOR  clrGrid, unsigned int  nGridSize  );
	void SetYRangeUnit(tstring  bstrRangeUnit, OLE_COLOR  clrUnit  );
	void SetDataPointValid(unsigned int  index, unsigned int  dataIndex, BOOL  isValid  );
	void SetYAxisRange(float  downVal, float  upVal  );
	void ShowYAxisGradByStep(unsigned int  index  );
	void ShowYAxisGradByIndex(int  nIndex  );
	void ShowYAxisTextByIndex(int  nIndex  );
	void ShowYAxisGradByVal(float  fValue  );
	void ShowYAxisTextByVal(float  fValue  );
	void SetFaultPos(unsigned int  index, unsigned int  FaultStartPos, unsigned int  FaultEndPos  );
	void SaveToBitmap(tstring  iStep  );
	void GetMaxMinValue(unsigned int  index, float * maxVal, float * minVal  );
	void GetXSpace();
	void SetYSpace(unsigned int  nYSpace  );
	void GetYSpace();
	void SetSpaceTime(float  fSpaceTime  );
	void SetXTime(float  fStartTime, float  fEndTime  );
	void SetStateSpace(long  nStateSpace  );
	void SetPointRadius(int  nPointRadius  );
	void LockDrag(BOOL  bDrag  );
	void LockWheel(BOOL  bCanWheel  );
	void ClearAllXAxisGradVisible();
	void ClearXGradText();
	void ClearAllYAxisGrad();
	void ClearAllYAxisGradValText();
	void SetBkLineSpace(unsigned int  nBkLineSpace  );
	void SetXGridProperty(unsigned long  clrGrad, unsigned int  nGridHeight, unsigned int  nGridWidth, int  nDashStyle  );
	void SetYGridProperty(unsigned long  clrGrad, unsigned int  nGridHeight, unsigned int  nGridWidth, int  nDashStyle  );
	void SetMultiMove(unsigned int  nStart, unsigned int  nEnd  );
	void SetFrameSelection(unsigned long  clrSel, int  nDashStyle, int  nSelWidth  );
	void ShowSelection(BOOL  bShowSel  );
	void IsClone(BOOL  bClone  );
	void SetXBottomSpace(int  nBottomSpace  );
};

struct IDUICurve : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void Clear();
	void SetMaxSize(unsigned int  nMaxPoint  );
	void InsertLine(unsigned int  nIndex, unsigned int  fXAxisTime, float  fYAxisAmp  );
	void SetCurXShowScope(float  fStartTime, float  fEndTime  );
	void GetCurXShowScope(float * nStartTime, float * nEndTime  );
	void ShowXAxisGradByStep(unsigned int  nStep  );
	void ShowXAxisGradByIndex(unsigned int  index  );
	void SetGridLineVisible(BOOL  isShow  );
	void SetXGradTextByIndex(unsigned int  nRulerIndex, tstring  bstrRulerText  );
	void SetHeadName(tstring  bstrHeadName, unsigned long  clrText, unsigned int  nTextSize  );
	void DrawAssisLine(unsigned int  nIndex, float  fAssisPos, unsigned int  DashStyle, OLE_COLOR  clrAssisLine, unsigned int  nPenSize, BOOL  bDrawAssisText  );
	void SetAssisLineVisble(unsigned int  index, BOOL  isVisble  );
	void SetLineVisble(unsigned int  index, BOOL  isVisble  );
	void SetLineProp(unsigned int  nIndex, unsigned int  DashStyle, unsigned int  nLineLength, OLE_COLOR  ClrLine  );
	void SetAssiLineProp(unsigned int  nIndex, unsigned int  DashStyle, unsigned int  nLineLength, OLE_COLOR  ClrLine, unsigned int  nTextSize  );
	void SetFormName(tstring  bstFormName, unsigned long  clrText, unsigned int  nTextSize  );
	void SetWhellSpeed(float  nSpeed  );
	void GetWhellSpeed(float * nSpeed  );
	void AddState(unsigned int  nIndex, unsigned int  nStartIndex, unsigned int  nEndIndex, unsigned long  clr, tstring  strStateText  );
	void SetState(unsigned int  nParentLine, unsigned int  nStartIndex, unsigned int  nEndIndex, unsigned long  clr  );
	void SetXAxisUnit(tstring  bstrRangeUnit, OLE_COLOR  clrUnit  );
	void SetBkImage(struct IDUIImageBase * pImageBase  );
	void SetStateHeight(long  nStateHeight  );
	void SetGridMode(unsigned int  nDashStyle, OLE_COLOR  clrGrid, unsigned int  nGridSize  );
	void SetYRangeUnit(tstring  bstrRangeUnit, OLE_COLOR  clrUnit  );
	void SetDataPointValid(unsigned int  index, unsigned int  dataIndex, BOOL  isValid  );
	void SetYAxisRange(float  downVal, float  upVal  );
	void ShowYAxisGradByStep(unsigned int  index  );
	void ShowYAxisGradByIndex(int  nIndex  );
	void ShowYAxisTextByIndex(int  nIndex  );
	void ShowYAxisGradByVal(float  fValue  );
	void ShowYAxisTextByVal(float  fValue  );
	void SetFaultPos(unsigned int  index, unsigned int  FaultStartPos, unsigned int  FaultEndPos  );
	void SaveToBitmap(tstring  iStep  );
	void GetMaxMinValue(unsigned int  index, float * maxVal, float * minVal  );
	void GetXSpace();
	void SetYSpace(unsigned int  nYSpace  );
	void GetYSpace();
	void SetSpaceTime(float  fSpaceTime  );
	void SetXTime(float  fStartTime, float  fEndTime  );
	void SetStateSpace(long  nStateSpace  );
	void SetPointRadius(int  nPointRadius  );
	void LockDrag(BOOL  bDrag  );
	void LockWheel(BOOL  bCanWheel  );
	void ClearAllXAxisGradVisible();
	void ClearXGradText();
	void ClearAllYAxisGrad();
	void ClearAllYAxisGradValText();
	void SetBkLineSpace(unsigned int  nBkLineSpace  );
	void SetXGridProperty(unsigned long  clrGrad, unsigned int  nGridHeight, unsigned int  nGridWidth, int  nDashStyle  );
	void SetYGridProperty(unsigned long  clrGrad, unsigned int  nGridHeight, unsigned int  nGridWidth, int  nDashStyle  );
	void SetMultiMove(unsigned int  nStart, unsigned int  nEnd  );
	void SetFrameSelection(unsigned long  clrSel, int  nDashStyle, int  nSelWidth  );
	void ShowSelection(BOOL  bShowSel  );
	void IsClone(BOOL  bClone  );
	void SetXBottomSpace(int  nBottomSpace  );
};

struct __declspec(uuid("4396ac06-7a00-4762-a8b3-b5ae3913d4b6")) _IDUIChromeEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("41aa8b53-456f-4cdb-bb9a-ff691fe19461")) IDUIChrome_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetCurrURL(BSTR strCurURL  ) = 0;
	virtual HRESULT __stdcall raw_OnShow() = 0;
	virtual HRESULT __stdcall raw_SetGanT(BSTR strCurURL  ) = 0;
	virtual HRESULT __stdcall raw_SendMesToWnd(int nID, int nButton  ) = 0;
	virtual HRESULT __stdcall raw_Set3DMenu(BSTR strText  ) = 0;

	//
	//Method Wrapper
	//
	void SetCurrURL(tstring  strCurURL  );
	void OnShow();
	void SetGanT(tstring  strCurURL  );
	void SendMesToWnd(int  nID, int  nButton  );
	void Set3DMenu(tstring  strText  );
};

struct IDUIChrome : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetCurrURL(tstring  strCurURL  );
	void OnShow();
	void SetGanT(tstring  strCurURL  );
	void SendMesToWnd(int  nID, int  nButton  );
	void Set3DMenu(tstring  strText  );
};

struct __declspec(uuid("6b69bb10-40bd-4c31-abb4-e0030686f77b")) _IDUITimeAxisEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("d1b9df53-3df9-40e4-970c-04e571528b70")) IDUITimeAxis_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetStartTime(struct DataTime tmData  ) = 0;
	virtual HRESULT __stdcall raw_SetEndTime(struct DataTime tmData  ) = 0;
	virtual HRESULT __stdcall raw_SetTimeTick(long nTimeTick  ) = 0;
	virtual HRESULT __stdcall raw_AppendTimeChannel(BSTR strText, VARIANT_BOOL bRedraw, struct IDUITimeChannel **pResult) = 0;
	virtual HRESULT __stdcall raw_SetPlayMode(enum PlayMode nMode  ) = 0;
	virtual HRESULT __stdcall raw_GetTimeRuler(struct IDUITimerRuler **pResult) = 0;
	virtual HRESULT __stdcall raw_SetRectangleSelectMode(VARIANT_BOOL bRectlange  ) = 0;
	virtual HRESULT __stdcall raw_GetTimeChannel(long nIndex, struct IDUITimeChannel **pResult) = 0;
	virtual HRESULT __stdcall raw_GetChannelCount(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTickPix(long nTickPix  ) = 0;
	virtual HRESULT __stdcall raw_RemoveTimeChannel(long nIndex  ) = 0;
	virtual HRESULT __stdcall raw_SetMultiSelect(VARIANT_BOOL bMultiSelect  ) = 0;
	virtual HRESULT __stdcall raw_IsMultiSelect(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetSelChannel(struct IDUITimeChannel **pResult) = 0;
	virtual HRESULT __stdcall raw_SetPointerShow(VARIANT_BOOL bShow  ) = 0;
	virtual HRESULT __stdcall raw_SetBackColor(struct IFillColor *pFillColor, VARIANT_BOOL bRedraw  ) = 0;
	virtual HRESULT __stdcall raw_SetRulerHeight(long nHeight  ) = 0;
	virtual HRESULT __stdcall raw_SetRulerBackColor(struct IFillColor *pFillColor  ) = 0;
	virtual HRESULT __stdcall raw_SetRulerBackImage(struct IDUIImageBase *pImageBase  ) = 0;
	virtual HRESULT __stdcall raw_SetRulerOffsetX(long nOffsetX  ) = 0;
	virtual HRESULT __stdcall raw_SetChannelHeight(long nHeight  ) = 0;
	virtual HRESULT __stdcall raw_SetContinueSelectMode(VARIANT_BOOL bEnable  ) = 0;
	virtual HRESULT __stdcall raw_SetChannelColor(enum ChannelState nState, struct IFillColor *pFillColor  ) = 0;
	virtual HRESULT __stdcall raw_SetChannelImage(enum ChannelState nState, struct IDUIImageBase *pImageBase  ) = 0;
	virtual HRESULT __stdcall raw_SetTimeTipFormat(BSTR strFormat  ) = 0;
	virtual HRESULT __stdcall raw_InsertTimeChannel(BSTR strText, long nIndex, VARIANT_BOOL bRedraw, struct IDUITimeChannel **pResult) = 0;
	virtual HRESULT __stdcall raw_GetCursorTime(struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_GetChectedTagId(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetDragCursor(OLE_HANDLE hCursor  ) = 0;
	virtual HRESULT __stdcall raw_EnableMouseScroll(VARIANT_BOOL bEnable  ) = 0;
	virtual HRESULT __stdcall raw_SetDrawTimeTag(VARIANT_BOOL bEnable  ) = 0;
	virtual HRESULT __stdcall raw_IsDrawTimeTag(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetExpandHeight(long nHeight  ) = 0;
	virtual HRESULT __stdcall raw_ExpandChannel(long nIndex, VARIANT_BOOL bExpand  ) = 0;
	virtual HRESULT __stdcall raw_GetExpandChannel(struct IDUITimeChannel **pResult) = 0;
	virtual HRESULT __stdcall raw_SetDragAllSelMode(VARIANT_BOOL bEnable  ) = 0;

	//
	//Method Wrapper
	//
	void SetStartTime(struct DataTime  tmData  );
	void SetEndTime(struct DataTime  tmData  );
	void SetTimeTick(long  nTimeTick  );
	struct IDUITimeChannel * AppendTimeChannel(tstring  strText, BOOL  bRedraw  );
	void SetPlayMode(enum PlayMode  nMode  );
	struct IDUITimerRuler * GetTimeRuler();
	void SetRectangleSelectMode(BOOL  bRectlange  );
	struct IDUITimeChannel * GetTimeChannel(long  nIndex  );
	long  GetChannelCount();
	void SetTickPix(long  nTickPix  );
	void RemoveTimeChannel(long  nIndex  );
	void SetMultiSelect(BOOL  bMultiSelect  );
	BOOL  IsMultiSelect();
	struct IDUITimeChannel * GetSelChannel();
	void SetPointerShow(BOOL  bShow  );
	void SetBackColor(struct IFillColor * pFillColor, BOOL  bRedraw  );
	void SetRulerHeight(long  nHeight  );
	void SetRulerBackColor(struct IFillColor * pFillColor  );
	void SetRulerBackImage(struct IDUIImageBase * pImageBase  );
	void SetRulerOffsetX(long  nOffsetX  );
	void SetChannelHeight(long  nHeight  );
	void SetContinueSelectMode(BOOL  bEnable  );
	void SetChannelColor(enum ChannelState  nState, struct IFillColor * pFillColor  );
	void SetChannelImage(enum ChannelState  nState, struct IDUIImageBase * pImageBase  );
	void SetTimeTipFormat(tstring  strFormat  );
	struct IDUITimeChannel * InsertTimeChannel(tstring  strText, long  nIndex, BOOL  bRedraw  );
	struct DataTime  GetCursorTime();
	long  GetChectedTagId();
	void SetDragCursor(OLE_HANDLE  hCursor  );
	void EnableMouseScroll(BOOL  bEnable  );
	void SetDrawTimeTag(BOOL  bEnable  );
	BOOL  IsDrawTimeTag();
	void SetExpandHeight(long  nHeight  );
	void ExpandChannel(long  nIndex, BOOL  bExpand  );
	struct IDUITimeChannel * GetExpandChannel();
	void SetDragAllSelMode(BOOL  bEnable  );
};

struct IDUITimeAxis : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetStartTime(struct DataTime  tmData  );
	void SetEndTime(struct DataTime  tmData  );
	void SetTimeTick(long  nTimeTick  );
	struct IDUITimeChannel * AppendTimeChannel(tstring  strText, BOOL  bRedraw  );
	void SetPlayMode(enum PlayMode  nMode  );
	struct IDUITimerRuler * GetTimeRuler();
	void SetRectangleSelectMode(BOOL  bRectlange  );
	struct IDUITimeChannel * GetTimeChannel(long  nIndex  );
	long  GetChannelCount();
	void SetTickPix(long  nTickPix  );
	void RemoveTimeChannel(long  nIndex  );
	void SetMultiSelect(BOOL  bMultiSelect  );
	BOOL  IsMultiSelect();
	struct IDUITimeChannel * GetSelChannel();
	void SetPointerShow(BOOL  bShow  );
	void SetBackColor(struct IFillColor * pFillColor, BOOL  bRedraw  );
	void SetRulerHeight(long  nHeight  );
	void SetRulerBackColor(struct IFillColor * pFillColor  );
	void SetRulerBackImage(struct IDUIImageBase * pImageBase  );
	void SetRulerOffsetX(long  nOffsetX  );
	void SetChannelHeight(long  nHeight  );
	void SetContinueSelectMode(BOOL  bEnable  );
	void SetChannelColor(enum ChannelState  nState, struct IFillColor * pFillColor  );
	void SetChannelImage(enum ChannelState  nState, struct IDUIImageBase * pImageBase  );
	void SetTimeTipFormat(tstring  strFormat  );
	struct IDUITimeChannel * InsertTimeChannel(tstring  strText, long  nIndex, BOOL  bRedraw  );
	struct DataTime  GetCursorTime();
	long  GetChectedTagId();
	void SetDragCursor(OLE_HANDLE  hCursor  );
	void EnableMouseScroll(BOOL  bEnable  );
	void SetDrawTimeTag(BOOL  bEnable  );
	BOOL  IsDrawTimeTag();
	void SetExpandHeight(long  nHeight  );
	void ExpandChannel(long  nIndex, BOOL  bExpand  );
	struct IDUITimeChannel * GetExpandChannel();
	void SetDragAllSelMode(BOOL  bEnable  );
};

struct __declspec(uuid("1cd60734-18b3-4911-b6e4-0cf7c70b2be0")) IDUITimeChannel : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetText(BSTR bStrText  ) = 0;
	virtual HRESULT __stdcall raw_GetTimePointer(struct IDUITimePointer **pResult) = 0;
	virtual HRESULT __stdcall raw_AppendTimeLine(struct DataTime tStart, struct DataTime tEnd, long nID, struct IFillColor *pFillColor, struct IDUIImageBase *pImageBase, VARIANT_BOOL bRedraw, struct IDUITimeLine **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTimeLine(long nIndex, struct IDUITimeLine **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTimeLineCount(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetPointerPos(struct DataTime tTime  ) = 0;
	virtual HRESULT __stdcall raw_RemoveAllTimeLine() = 0;
	virtual HRESULT __stdcall raw_RemoveTimeLineById(long nID  ) = 0;
	virtual HRESULT __stdcall raw_GetText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetState(enum ChannelState nState  ) = 0;
	virtual HRESULT __stdcall raw_IsCheck(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCheck(VARIANT_BOOL bCheck  ) = 0;
	virtual HRESULT __stdcall raw_SetBtnText(BSTR strText  ) = 0;
	virtual HRESULT __stdcall raw_GetTimeLineById(long nID, struct IDUITimeLine **pResult) = 0;
	virtual HRESULT __stdcall raw_AppendTimeTag(OLE_HANDLE hTagBitmap, OLE_HANDLE hCheckBitmap, struct IDUIImageBase *pImageBase, struct IDUIImageBase *pSelImageBase, struct DataTime tStartTimeData, struct DataTime tEndTimeData, long nID  ) = 0;
	virtual HRESULT __stdcall raw_RemoveAllTagTimeTag() = 0;
	virtual HRESULT __stdcall raw_RemoveTimeTagById(long nID  ) = 0;
	virtual HRESULT __stdcall raw_GetTimeTagRectById(long nID, struct SkinRect *pResult) = 0;
	virtual HRESULT __stdcall raw_GetTimeTagStartTimeById(long nIndex, struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_GetTimeTagEndTimeById(long nIndex, struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_IsTagCheck(long nID, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetColor(enum ChannelState nState, struct IFillColor *pFillColor  ) = 0;
	virtual HRESULT __stdcall raw_SetImageBase(enum ChannelState nState, struct IDUIImageBase *pImageBase  ) = 0;
	virtual HRESULT __stdcall raw_SetSelPointerCenter() = 0;
	virtual HRESULT __stdcall raw_GetSelStartTime(struct DataTime *tmData  ) = 0;
	virtual HRESULT __stdcall raw_GetSelEndTime(struct DataTime *tmData  ) = 0;
	virtual HRESULT __stdcall raw_SetSelStartTime(struct DataTime tmData  ) = 0;
	virtual HRESULT __stdcall raw_SetSelEndTime(struct DataTime tmData  ) = 0;
	virtual HRESULT __stdcall raw_CancelContinueSelect() = 0;
	virtual HRESULT __stdcall raw_SetPointerShow(VARIANT_BOOL bShow  ) = 0;
	virtual HRESULT __stdcall raw_AppendChannelTag(OLE_HANDLE hTagBitmap, OLE_HANDLE hCheckBitmap, struct IDUIImageBase *pImageBase, struct DataTime tStartTimeData, struct DataTime tEndTime  ) = 0;
	virtual HRESULT __stdcall raw_RemoveChannelTag() = 0;
	virtual HRESULT __stdcall raw_GetIndex(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetID(long nID  ) = 0;
	virtual HRESULT __stdcall raw_GetID(long *pResult) = 0;
	virtual HRESULT __stdcall raw_ClearSelections() = 0;
	virtual HRESULT __stdcall raw_IsHaveSelections(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTagSpecialHBitmap(OLE_HANDLE hBitmap, OLE_HANDLE hCheckBitmap  ) = 0;
	virtual HRESULT __stdcall raw_SetDrawTimeTag(VARIANT_BOOL bDrawTimeTag  ) = 0;
	virtual HRESULT __stdcall raw_IsDrawTimeTag(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetChannelRc(struct SkinRect *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTxtRightOffset(long nOffset  ) = 0;
	virtual HRESULT __stdcall raw_GetTxtRightOffset(long *pResult) = 0;
	virtual HRESULT __stdcall raw_GetCustomForm(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetExpandForm(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetHighLightTime(struct DataTime tStart, struct DataTime tEnd, VARIANT_BOOL bShow  ) = 0;
	virtual HRESULT __stdcall raw_SetHighLightShow(VARIANT_BOOL bShow  ) = 0;
	virtual HRESULT __stdcall raw_SetHeight(long nHeight  ) = 0;
	virtual HRESULT __stdcall raw_GetHeight(long *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetText(tstring  bStrText  );
	struct IDUITimePointer * GetTimePointer();
	struct IDUITimeLine * AppendTimeLine(struct DataTime  tStart, struct DataTime  tEnd, long  nID, struct IFillColor * pFillColor, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUITimeLine * GetTimeLine(long  nIndex  );
	long  GetTimeLineCount();
	void SetPointerPos(struct DataTime  tTime  );
	void RemoveAllTimeLine();
	void RemoveTimeLineById(long  nID  );
	tstring  GetText();
	void SetState(enum ChannelState  nState  );
	BOOL  IsCheck();
	void SetCheck(BOOL  bCheck  );
	void SetBtnText(tstring  strText  );
	struct IDUITimeLine * GetTimeLineById(long  nID  );
	void AppendTimeTag(OLE_HANDLE  hTagBitmap, OLE_HANDLE  hCheckBitmap, struct IDUIImageBase * pImageBase, struct IDUIImageBase * pSelImageBase, struct DataTime  tStartTimeData, struct DataTime  tEndTimeData, long  nID  );
	void RemoveAllTagTimeTag();
	void RemoveTimeTagById(long  nID  );
	struct SkinRect  GetTimeTagRectById(long  nID  );
	struct DataTime  GetTimeTagStartTimeById(long  nIndex  );
	struct DataTime  GetTimeTagEndTimeById(long  nIndex  );
	BOOL  IsTagCheck(long  nID  );
	void SetColor(enum ChannelState  nState, struct IFillColor * pFillColor  );
	void SetImageBase(enum ChannelState  nState, struct IDUIImageBase * pImageBase  );
	void SetSelPointerCenter();
	void GetSelStartTime(struct DataTime * tmData  );
	void GetSelEndTime(struct DataTime * tmData  );
	void SetSelStartTime(struct DataTime  tmData  );
	void SetSelEndTime(struct DataTime  tmData  );
	void CancelContinueSelect();
	void SetPointerShow(BOOL  bShow  );
	void AppendChannelTag(OLE_HANDLE  hTagBitmap, OLE_HANDLE  hCheckBitmap, struct IDUIImageBase * pImageBase, struct DataTime  tStartTimeData, struct DataTime  tEndTime  );
	void RemoveChannelTag();
	long  GetIndex();
	void SetID(long  nID  );
	long  GetID();
	void ClearSelections();
	BOOL  IsHaveSelections();
	void SetTagSpecialHBitmap(OLE_HANDLE  hBitmap, OLE_HANDLE  hCheckBitmap  );
	void SetDrawTimeTag(BOOL  bDrawTimeTag  );
	BOOL  IsDrawTimeTag();
	struct SkinRect  GetChannelRc();
	void SetTxtRightOffset(long  nOffset  );
	long  GetTxtRightOffset();
	OLE_HANDLE  GetCustomForm();
	OLE_HANDLE  GetExpandForm();
	void SetHighLightTime(struct DataTime  tStart, struct DataTime  tEnd, BOOL  bShow  );
	void SetHighLightShow(BOOL  bShow  );
	void SetHeight(long  nHeight  );
	long  GetHeight();
};

struct __declspec(uuid("daf492c9-289a-4b7d-bea1-f8ab94fd3fe5")) IDUITimePointer : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetStartTime(struct DataTime tmData  ) = 0;
	virtual HRESULT __stdcall raw_GetStartTime(struct DataTime *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetStartTime(struct DataTime  tmData  );
	struct DataTime  GetStartTime();
};

struct __declspec(uuid("b94df411-f294-4571-883b-db7fe11d9724")) IDUITimeLine : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetSelectionStartTime(long nIndex, struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_Deselect() = 0;
	virtual HRESULT __stdcall raw_GetStartTime(struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_GetEndTime(struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_GetSelectionEndTime(long nIndex, struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_GetSelectionCount(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetSelectionTime(struct DataTime tmStartData, struct DataTime tmEndData  ) = 0;
	virtual HRESULT __stdcall raw_GetID(long *pResult) = 0;
	virtual HRESULT __stdcall raw_GetIndex(long *pResult) = 0;

	//
	//Method Wrapper
	//
	struct DataTime  GetSelectionStartTime(long  nIndex  );
	void Deselect();
	struct DataTime  GetStartTime();
	struct DataTime  GetEndTime();
	struct DataTime  GetSelectionEndTime(long  nIndex  );
	long  GetSelectionCount();
	void SetSelectionTime(struct DataTime  tmStartData, struct DataTime  tmEndData  );
	long  GetID();
	long  GetIndex();
};

struct __declspec(uuid("59c87a87-46eb-41bc-b41b-fb115d17a4ef")) IDUITimerRuler : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetTimePointer(struct IDUITimePointer **pResult) = 0;
	virtual HRESULT __stdcall raw_GetStartTime(struct DataTime *pResult) = 0;
	virtual HRESULT __stdcall raw_SetNoDbClickHeight(long nHeight  ) = 0;

	//
	//Method Wrapper
	//
	struct IDUITimePointer * GetTimePointer();
	struct DataTime  GetStartTime();
	void SetNoDbClickHeight(long  nHeight  );
};

struct __declspec(uuid("c3232e9b-3533-46b1-8e8e-a2f662d42c9f")) _IDUIPieEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("cf0c1a4c-4d93-4f4a-8d31-2dfbc248efcf")) IDUIPie_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetTitle(BSTR strTitle  ) = 0;
	virtual HRESULT __stdcall raw_SetSubTitle(BSTR strSubTitle  ) = 0;
	virtual HRESULT __stdcall raw_ClearAllData() = 0;
	virtual HRESULT __stdcall raw_ShowPie() = 0;
	virtual HRESULT __stdcall raw_AddPieData(BSTR strName, BSTR strVal  ) = 0;

	//
	//Method Wrapper
	//
	void SetTitle(tstring  strTitle  );
	void SetSubTitle(tstring  strSubTitle  );
	void ClearAllData();
	void ShowPie();
	void AddPieData(tstring  strName, tstring  strVal  );
};

struct IDUIPie : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetTitle(tstring  strTitle  );
	void SetSubTitle(tstring  strSubTitle  );
	void ClearAllData();
	void ShowPie();
	void AddPieData(tstring  strName, tstring  strVal  );
};

struct __declspec(uuid("46ae9967-10cd-4eda-81e5-cb2b47c142a4")) _IDUIColumnEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("4f1c741b-b785-4994-bbbb-6064bb421695")) IDUIColumn_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetTitle(BSTR strTitle  ) = 0;
	virtual HRESULT __stdcall raw_SetSubTitle(BSTR strSubTitle  ) = 0;
	virtual HRESULT __stdcall raw_SetYTitle(BSTR strYTitle  ) = 0;
	virtual HRESULT __stdcall raw_ClearAllData() = 0;
	virtual HRESULT __stdcall raw_ShowColumn() = 0;
	virtual HRESULT __stdcall raw_AddData(BSTR strName, BSTR strVal  ) = 0;
	virtual HRESULT __stdcall raw_AddXAxis(BSTR strXAxis  ) = 0;

	//
	//Method Wrapper
	//
	void SetTitle(tstring  strTitle  );
	void SetSubTitle(tstring  strSubTitle  );
	void SetYTitle(tstring  strYTitle  );
	void ClearAllData();
	void ShowColumn();
	void AddData(tstring  strName, tstring  strVal  );
	void AddXAxis(tstring  strXAxis  );
};

struct IDUIColumn : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetTitle(tstring  strTitle  );
	void SetSubTitle(tstring  strSubTitle  );
	void SetYTitle(tstring  strYTitle  );
	void ClearAllData();
	void ShowColumn();
	void AddData(tstring  strName, tstring  strVal  );
	void AddXAxis(tstring  strXAxis  );
};

struct __declspec(uuid("9be58092-c224-4960-a8db-589f493da577")) _IDUIGridCtrlEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("e96b5390-f231-4665-8f7c-78105db5a68e")) IDUIGridCtrl_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_OnInsertRow(OLE_HANDLE pParent, BSTR strHeading, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetHeadRowCount(int nRow  ) = 0;
	virtual HRESULT __stdcall raw_SetRowCounts(int nRowCount  ) = 0;
	virtual HRESULT __stdcall raw_SetColumnCounts(int nColCount  ) = 0;
	virtual HRESULT __stdcall raw_SetCellText(int nRow, int nCol, BSTR str, VARIANT_BOOL bRightOrCenter  ) = 0;
	virtual HRESULT __stdcall raw_SetHeadCellText(int nRow, int nCol, BSTR str, VARIANT_BOOL bRightOrCenter  ) = 0;
	virtual HRESULT __stdcall raw_SetColWidth(int nCol, int nWidth  ) = 0;
	virtual HRESULT __stdcall raw_SetCellReadonly(int nRow, int nCol  ) = 0;
	virtual HRESULT __stdcall raw_DeleteAll() = 0;
	virtual HRESULT __stdcall raw_OnSetCellCombo(int nRow, int nCol, BSTR str  ) = 0;
	virtual HRESULT __stdcall raw_OnSetCellCheckBox(int nRow, int nCol, VARIANT_BOOL bl  ) = 0;
	virtual HRESULT __stdcall raw_OnMergeCells(int nStartRow, int nStartCol, int nEndRow, int nEndCol  ) = 0;
	virtual HRESULT __stdcall raw_OnUnMergeCells(int nStartRow, int nStartCol, int nEndRow, int nEndCol  ) = 0;
	virtual HRESULT __stdcall raw_OnDeleteRowByIndex(int nIndex  ) = 0;
	virtual HRESULT __stdcall raw_OnAddComboItem(int nRow, int nCol, BSTR strInfo, VARIANT_BOOL bFirstItem  ) = 0;

	//
	//Method Wrapper
	//
	OLE_HANDLE  OnInsertRow(OLE_HANDLE  pParent, tstring  strHeading  );
	void SetHeadRowCount(int  nRow  );
	void SetRowCounts(int  nRowCount  );
	void SetColumnCounts(int  nColCount  );
	void SetCellText(int  nRow, int  nCol, tstring  str, BOOL  bRightOrCenter  );
	void SetHeadCellText(int  nRow, int  nCol, tstring  str, BOOL  bRightOrCenter  );
	void SetColWidth(int  nCol, int  nWidth  );
	void SetCellReadonly(int  nRow, int  nCol  );
	void DeleteAll();
	void OnSetCellCombo(int  nRow, int  nCol, tstring  str  );
	void OnSetCellCheckBox(int  nRow, int  nCol, BOOL  bl  );
	void OnMergeCells(int  nStartRow, int  nStartCol, int  nEndRow, int  nEndCol  );
	void OnUnMergeCells(int  nStartRow, int  nStartCol, int  nEndRow, int  nEndCol  );
	void OnDeleteRowByIndex(int  nIndex  );
	void OnAddComboItem(int  nRow, int  nCol, tstring  strInfo, BOOL  bFirstItem  );
};

struct IDUIGridCtrl : IDUIControlBase
{

	//
	//Method Wrapper
	//
	OLE_HANDLE  OnInsertRow(OLE_HANDLE  pParent, tstring  strHeading  );
	void SetHeadRowCount(int  nRow  );
	void SetRowCounts(int  nRowCount  );
	void SetColumnCounts(int  nColCount  );
	void SetCellText(int  nRow, int  nCol, tstring  str, BOOL  bRightOrCenter  );
	void SetHeadCellText(int  nRow, int  nCol, tstring  str, BOOL  bRightOrCenter  );
	void SetColWidth(int  nCol, int  nWidth  );
	void SetCellReadonly(int  nRow, int  nCol  );
	void DeleteAll();
	void OnSetCellCombo(int  nRow, int  nCol, tstring  str  );
	void OnSetCellCheckBox(int  nRow, int  nCol, BOOL  bl  );
	void OnMergeCells(int  nStartRow, int  nStartCol, int  nEndRow, int  nEndCol  );
	void OnUnMergeCells(int  nStartRow, int  nStartCol, int  nEndRow, int  nEndCol  );
	void OnDeleteRowByIndex(int  nIndex  );
	void OnAddComboItem(int  nRow, int  nCol, tstring  strInfo, BOOL  bFirstItem  );
};

struct __declspec(uuid("352c2358-843e-4e7c-8597-1cfb603b821f")) _IDUIIPEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("6cc53057-29dd-4ac2-8551-00de3f94a97f")) IDUIIP_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetDisable(VARIANT_BOOL bDisable  ) = 0;
	virtual HRESULT __stdcall raw_SetIp(int nIP1, int nIP2, int nIP3, int nIP4  ) = 0;
	virtual HRESULT __stdcall raw_GetIp(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_GetDisable(VARIANT_BOOL *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetDisable(BOOL  bDisable  );
	void SetIp(int  nIP1, int  nIP2, int  nIP3, int  nIP4  );
	tstring  GetIp();
	BOOL  GetDisable();
};

struct IDUIIP : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetDisable(BOOL  bDisable  );
	void SetIp(int  nIP1, int  nIP2, int  nIP3, int  nIP4  );
	tstring  GetIp();
	BOOL  GetDisable();
};

struct __declspec(uuid("54c1cfff-2310-4229-a447-306ef0f2a2fb")) _IDUIGanTEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("efc158cd-54db-4cba-90cc-7e7104e2697e")) IDUIGanT_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_ClearAllData() = 0;
	virtual HRESULT __stdcall raw_AddItemInfo(int nID, BSTR strText, BSTR strStartData, int nDuration, VARIANT_BOOL bOpen, int nParent  ) = 0;
	virtual HRESULT __stdcall raw_AddTaskIcon(int nID, BSTR strData, BSTR strAdd  ) = 0;
	virtual HRESULT __stdcall raw_AddLink(int nID, int nSource, int nTarget, BSTR strType  ) = 0;
	virtual HRESULT __stdcall raw_DeleteItem(int nID  ) = 0;

	//
	//Method Wrapper
	//
	void ClearAllData();
	void AddItemInfo(int  nID, tstring  strText, tstring  strStartData, int  nDuration, BOOL  bOpen, int  nParent  );
	void AddTaskIcon(int  nID, tstring  strData, tstring  strAdd  );
	void AddLink(int  nID, int  nSource, int  nTarget, tstring  strType  );
	void DeleteItem(int  nID  );
};

struct IDUIGanT : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void ClearAllData();
	void AddItemInfo(int  nID, tstring  strText, tstring  strStartData, int  nDuration, BOOL  bOpen, int  nParent  );
	void AddTaskIcon(int  nID, tstring  strData, tstring  strAdd  );
	void AddLink(int  nID, int  nSource, int  nTarget, tstring  strType  );
	void DeleteItem(int  nID  );
};

struct __declspec(uuid("4802dbe6-b56f-486b-ba04-7471f39190ec")) _IDUI3DControlEvents : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//

	//
	//Method Wrapper
	//
};

struct __declspec(uuid("ecce67c6-c02d-43da-b766-ef3a93c69ebe")) IDUI3DControl_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_AddItem(BSTR strName, BSTR strText  ) = 0;
	virtual HRESULT __stdcall raw_DeleteItem(int nIndex  ) = 0;

	//
	//Method Wrapper
	//
	void AddItem(tstring  strName, tstring  strText  );
	void DeleteItem(int  nIndex  );
};

struct IDUI3DControl : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void AddItem(tstring  strName, tstring  strText  );
	void DeleteItem(int  nIndex  );
};


#include "AdvancedAll.tli"
#endif //__HEAD__ADVANCEDALL__