#ifndef __HEAD__INDUSTRYALL__
#define __HEAD__INDUSTRYALL__
#include <comdef.h>

#include <xstring>
using namespace std;
#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

enum enumCHANGE_IMAGE_FROM;

struct IMeter;
struct __declspec(uuid("73509c26-5026-4fcc-8535-e421988ebac3")) IMeter_;
struct __declspec(uuid("aa6244f3-d066-4b1a-867b-39d43c2deb35")) Meter;
struct __declspec(uuid("6343553e-5d23-4e9e-b484-1511000a2fe2")) _IMeterEvents;
struct IDUIGraphicLine;
struct __declspec(uuid("22590266-e34f-48a4-83ab-80393a3ef811")) IDUIGraphicLine_;
struct __declspec(uuid("b5996fb9-f2c9-4297-af58-2706a2a6a9d5")) DUIGraphicLine;
struct __declspec(uuid("0379254a-da49-45e0-ae27-0ca2fbd11b7a")) _IDUIGraphicLineEvents;
struct IDUIThermometer;
struct __declspec(uuid("b415356e-02b0-40ec-9869-f45fdf005a95")) IDUIThermometer_;
struct __declspec(uuid("f6e54718-56bb-4088-b1d3-368ff7447a28")) DUIThermometer;
struct __declspec(uuid("2188fe95-d812-479c-ad6e-542959d7707c")) _IDUIThermometerEvents;
struct IDUILedCtrl;
struct __declspec(uuid("c3dec320-8629-4f47-944f-1574ca0eeb39")) IDUILedCtrl_;
struct __declspec(uuid("47f75c27-8252-4a9c-b449-01e55d4744c4")) DUILedCtrl;
struct __declspec(uuid("9f4f883b-85cc-429d-9657-c176801e54ff")) _IDUILedCtrlEvents;
struct IDUIKnobCtrl;
struct __declspec(uuid("976570de-c162-4205-b294-45e5feb02cc4")) IDUIKnobCtrl_;
struct __declspec(uuid("3a477441-4f7b-41b9-ad69-4cebd4a3ad86")) DUIKnobCtrl;
struct __declspec(uuid("9e4bd844-5831-409d-99ce-7e62e6ca14f8")) _IDUIKnobCtrlEvents;
struct IDUIIndicatorCtrl;
struct __declspec(uuid("a01348a9-85ee-462d-8c75-e251aaff99f9")) IDUIIndicatorCtrl_;
struct __declspec(uuid("648a799c-4150-451f-8e30-302db85ae32c")) DUIIndicatorCtrl;
struct __declspec(uuid("ca9005f6-44af-4509-97f6-7be112dbd8bd")) _IDUIIndicatorCtrlEvents;
enum DUIINDICATORCTRL_STATE;

struct IDUIDialCtrl;
struct __declspec(uuid("bb656c51-7d48-496f-8fc0-6d1e12b73df2")) IDUIDialCtrl_;
struct __declspec(uuid("66d12239-5a0a-4dc9-8b54-39c5dfc228c1")) DUIDialCtrl;
struct __declspec(uuid("95021ef9-a152-4e28-8765-1d860e022c91")) _IDUIDialCtrlEvents;
enum DUI_KNOBCTRL_MSGID;

enum DUI_KNOBCTRL_MSGID
{ 
	DUI_KNOBMSG_CHANGEVALUE = 3200 
};

struct __declspec(uuid("95021ef9-a152-4e28-8765-1d860e022c91")) _IDUIDialCtrlEvents : IDispatch
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

struct __declspec(uuid("bb656c51-7d48-496f-8fc0-6d1e12b73df2")) IDUIDialCtrl_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetRange(short *pnMin, short *pnMax  ) = 0;
	virtual HRESULT __stdcall raw_SetRange(short nMin, short nMax, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetPos(float nPos  ) = 0;
	virtual HRESULT __stdcall raw_GetPos(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCriticalVal(short nValue  ) = 0;
	virtual HRESULT __stdcall raw_GetCriticalVal(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBigFrequency(long nFre  ) = 0;
	virtual HRESULT __stdcall raw_GetBigFrequency(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetSmallFrequency(long nFre  ) = 0;
	virtual HRESULT __stdcall raw_GetSmallFrequency(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetPointPath(BSTR strPath  ) = 0;
	virtual HRESULT __stdcall raw_GetPointPath(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_AddKeyString(short nValue, BSTR strKeyString, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveKeyString(short nValue  ) = 0;
	virtual HRESULT __stdcall raw_DrawKeyString(VARIANT_BOOL bDraw  ) = 0;
	virtual HRESULT __stdcall raw_IsDrawKeyString(VARIANT_BOOL *pResult) = 0;

	//
	//Method Wrapper
	//
	void GetRange(short * pnMin, short * pnMax  );
	BOOL  SetRange(short  nMin, short  nMax, BOOL  bRedraw  );
	void SetPos(float  nPos  );
	float  GetPos();
	void SetCriticalVal(short  nValue  );
	short  GetCriticalVal();
	void SetBigFrequency(long  nFre  );
	long  GetBigFrequency();
	void SetSmallFrequency(long  nFre  );
	long  GetSmallFrequency();
	void SetPointPath(tstring  strPath  );
	tstring  GetPointPath();
	BOOL  AddKeyString(short  nValue, tstring  strKeyString  );
	void RemoveKeyString(short  nValue  );
	void DrawKeyString(BOOL  bDraw  );
	BOOL  IsDrawKeyString();
};

struct IDUIDialCtrl : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void GetRange(short * pnMin, short * pnMax  );
	BOOL  SetRange(short  nMin, short  nMax, BOOL  bRedraw  );
	void SetPos(float  nPos  );
	float  GetPos();
	void SetCriticalVal(short  nValue  );
	short  GetCriticalVal();
	void SetBigFrequency(long  nFre  );
	long  GetBigFrequency();
	void SetSmallFrequency(long  nFre  );
	long  GetSmallFrequency();
	void SetPointPath(tstring  strPath  );
	tstring  GetPointPath();
	BOOL  AddKeyString(short  nValue, tstring  strKeyString  );
	void RemoveKeyString(short  nValue  );
	void DrawKeyString(BOOL  bDraw  );
	BOOL  IsDrawKeyString();
};

enum DUIINDICATORCTRL_STATE
{ 
	DUIINDICATORCTRL_STATE_GREEN = 2,
	DUIINDICATORCTRL_STATE_LAST = 4,
	DUIINDICATORCTRL_STATE_NORMAL = 0,
	DUIINDICATORCTRL_STATE_RED = 1,
	DUIINDICATORCTRL_STATE_YELLOW = 3 
};

struct __declspec(uuid("ca9005f6-44af-4509-97f6-7be112dbd8bd")) _IDUIIndicatorCtrlEvents : IDispatch
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

struct __declspec(uuid("a01348a9-85ee-462d-8c75-e251aaff99f9")) IDUIIndicatorCtrl_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetState(enum DUIINDICATORCTRL_STATE eState  ) = 0;
	virtual HRESULT __stdcall raw_GetState(enum DUIINDICATORCTRL_STATE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBlink(VARIANT_BOOL bBlink  ) = 0;
	virtual HRESULT __stdcall raw_IsBlink(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBlinkState(enum DUIINDICATORCTRL_STATE eState1, enum DUIINDICATORCTRL_STATE eState2  ) = 0;
	virtual HRESULT __stdcall raw_SetBlinkSpace(long lSpace  ) = 0;
	virtual HRESULT __stdcall raw_GetBlinkSpace(long *pResult) = 0;
	virtual HRESULT __stdcall raw_ShowText(VARIANT_BOOL bShow  ) = 0;
	virtual HRESULT __stdcall raw_IsShowText(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetText(BSTR strText  ) = 0;
	virtual HRESULT __stdcall raw_GetText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBackImage(BSTR strPath, enum DUIINDICATORCTRL_STATE eState1  ) = 0;
	virtual HRESULT __stdcall raw_GetTextColor(OLE_COLOR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTextColor(OLE_COLOR color  ) = 0;

	//
	//Method Wrapper
	//
	void SetState(enum DUIINDICATORCTRL_STATE  eState  );
	enum DUIINDICATORCTRL_STATE  GetState();
	void SetBlink(BOOL  bBlink  );
	BOOL  IsBlink();
	void SetBlinkState(enum DUIINDICATORCTRL_STATE  eState1, enum DUIINDICATORCTRL_STATE  eState2  );
	void SetBlinkSpace(long  lSpace  );
	long  GetBlinkSpace();
	void ShowText(BOOL  bShow  );
	BOOL  IsShowText();
	void SetText(tstring  strText  );
	tstring  GetText();
	void SetBackImage(tstring  strPath, enum DUIINDICATORCTRL_STATE  eState1  );
	OLE_COLOR  GetTextColor();
	void SetTextColor(OLE_COLOR  color  );
};

struct IDUIIndicatorCtrl : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetState(enum DUIINDICATORCTRL_STATE  eState  );
	enum DUIINDICATORCTRL_STATE  GetState();
	void SetBlink(BOOL  bBlink  );
	BOOL  IsBlink();
	void SetBlinkState(enum DUIINDICATORCTRL_STATE  eState1, enum DUIINDICATORCTRL_STATE  eState2  );
	void SetBlinkSpace(long  lSpace  );
	long  GetBlinkSpace();
	void ShowText(BOOL  bShow  );
	BOOL  IsShowText();
	void SetText(tstring  strText  );
	tstring  GetText();
	void SetBackImage(tstring  strPath, enum DUIINDICATORCTRL_STATE  eState1  );
	OLE_COLOR  GetTextColor();
	void SetTextColor(OLE_COLOR  color  );
};

struct __declspec(uuid("9e4bd844-5831-409d-99ce-7e62e6ca14f8")) _IDUIKnobCtrlEvents : IDispatch
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

struct __declspec(uuid("976570de-c162-4205-b294-45e5feb02cc4")) IDUIKnobCtrl_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetCycle(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCycle(VARIANT_BOOL bCycle  ) = 0;
	virtual HRESULT __stdcall raw_GetValue(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetValue(long lValue  ) = 0;
	virtual HRESULT __stdcall raw_GetMinValue(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMinValue(long lMinValue  ) = 0;
	virtual HRESULT __stdcall raw_GetMaxValue(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMaxValue(long lMaxValue  ) = 0;
	virtual HRESULT __stdcall raw_SetForePath(BSTR strPath  ) = 0;
	virtual HRESULT __stdcall raw_GetForePath(BSTR *pResult) = 0;

	//
	//Method Wrapper
	//
	BOOL  GetCycle();
	void SetCycle(BOOL  bCycle  );
	long  GetValue();
	void SetValue(long  lValue  );
	long  GetMinValue();
	void SetMinValue(long  lMinValue  );
	long  GetMaxValue();
	void SetMaxValue(long  lMaxValue  );
	void SetForePath(tstring  strPath  );
	tstring  GetForePath();
};

struct IDUIKnobCtrl : IDUIControlBase
{

	//
	//Method Wrapper
	//
	BOOL  GetCycle();
	void SetCycle(BOOL  bCycle  );
	long  GetValue();
	void SetValue(long  lValue  );
	long  GetMinValue();
	void SetMinValue(long  lMinValue  );
	long  GetMaxValue();
	void SetMaxValue(long  lMaxValue  );
	void SetForePath(tstring  strPath  );
	tstring  GetForePath();
};

struct __declspec(uuid("9f4f883b-85cc-429d-9657-c176801e54ff")) _IDUILedCtrlEvents : IDispatch
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

struct __declspec(uuid("c3dec320-8629-4f47-944f-1574ca0eeb39")) IDUILedCtrl_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetValue(BSTR *pResult  ) = 0;
	virtual HRESULT __stdcall raw_SetValue(BSTR strValue  ) = 0;

	//
	//Method Wrapper
	//
	void GetValue(BSTR * pResult  );
	void SetValue(tstring  strValue  );
};

struct IDUILedCtrl : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void GetValue(BSTR * pResult  );
	void SetValue(tstring  strValue  );
};

struct __declspec(uuid("2188fe95-d812-479c-ad6e-542959d7707c")) _IDUIThermometerEvents : IDispatch
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

struct __declspec(uuid("b415356e-02b0-40ec-9869-f45fdf005a95")) IDUIThermometer_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetRange(short *pnMin, short *pnMax  ) = 0;
	virtual HRESULT __stdcall raw_SetRange(short nMin, short nMax, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetPos(short nPos  ) = 0;
	virtual HRESULT __stdcall raw_GetPos(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBigFrequency(long nFre  ) = 0;
	virtual HRESULT __stdcall raw_GetBigFrequency(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetSmallFrequency(long nFre  ) = 0;
	virtual HRESULT __stdcall raw_GetSmallFrequency(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetUnitString(BSTR strUnit  ) = 0;
	virtual HRESULT __stdcall raw_GetUnitString(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTickColor(struct IFillColor *pColor  ) = 0;
	virtual HRESULT __stdcall raw_SetBackColor(struct IFillColor *pColor  ) = 0;
	virtual HRESULT __stdcall raw_GetTickColor(struct IFillColor **pResult) = 0;
	virtual HRESULT __stdcall raw_GetBackColor(struct IFillColor **pResult) = 0;

	//
	//Method Wrapper
	//
	void GetRange(short * pnMin, short * pnMax  );
	BOOL  SetRange(short  nMin, short  nMax, BOOL  bRedraw  );
	void SetPos(short  nPos  );
	short  GetPos();
	void SetBigFrequency(long  nFre  );
	long  GetBigFrequency();
	void SetSmallFrequency(long  nFre  );
	long  GetSmallFrequency();
	void SetUnitString(tstring  strUnit  );
	tstring  GetUnitString();
	void SetTickColor(struct IFillColor * pColor  );
	void SetBackColor(struct IFillColor * pColor  );
	struct IFillColor * GetTickColor();
	struct IFillColor * GetBackColor();
};

struct IDUIThermometer : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void GetRange(short * pnMin, short * pnMax  );
	BOOL  SetRange(short  nMin, short  nMax, BOOL  bRedraw  );
	void SetPos(short  nPos  );
	short  GetPos();
	void SetBigFrequency(long  nFre  );
	long  GetBigFrequency();
	void SetSmallFrequency(long  nFre  );
	long  GetSmallFrequency();
	void SetUnitString(tstring  strUnit  );
	tstring  GetUnitString();
	void SetTickColor(struct IFillColor * pColor  );
	void SetBackColor(struct IFillColor * pColor  );
	struct IFillColor * GetTickColor();
	struct IFillColor * GetBackColor();
};

struct __declspec(uuid("0379254a-da49-45e0-ae27-0ca2fbd11b7a")) _IDUIGraphicLineEvents : IDispatch
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

struct __declspec(uuid("22590266-e34f-48a4-83ab-80393a3ef811")) IDUIGraphicLine_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_PushValue(float fValue  ) = 0;
	virtual HRESULT __stdcall raw_Clear() = 0;

	//
	//Method Wrapper
	//
	void PushValue(float  fValue  );
	void Clear();
};

struct IDUIGraphicLine : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void PushValue(float  fValue  );
	void Clear();
};

struct __declspec(uuid("6343553e-5d23-4e9e-b484-1511000a2fe2")) _IMeterEvents : IDispatch
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

struct __declspec(uuid("73509c26-5026-4fcc-8535-e421988ebac3")) IMeter_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetMeterBack(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterBack(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterFrontPointer(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterFrontPointer(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterAfterPointer(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterAfterPointer(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterLowerRuler(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterLowerRuler(long lowerRuler  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterHighRuler(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterHighRuler(long highRuler  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterSpaceRuler(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterSpaceRuler(long spaceRuler  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterFrontPointerRuler(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterFrontPointerRuler(long pointerRuler  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterAfterPointerRuler(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterAfterPointerRuler(long pointerRuler  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarPenelBack(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarPenelTextStyle(struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarPenelText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarPenelBack(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarPenelTextStyle(struct IDUITextStyle *pTextStyle  ) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarPenelText(BSTR text  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarDataBack(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarDataTextStyle(struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarDataText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarDataBack(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarDataTextStyle(struct IDUITextStyle *pTextStyle  ) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarDataText(BSTR text  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarPenelBack(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarPenelTextStyle(struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarPenelText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarPenelBack(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarPenelTextStyle(struct IDUITextStyle *pTextStyle  ) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarPenelText(BSTR text  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarDataBack(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarDataTextStyle(struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarDataText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarDataBack(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarDataTextStyle(struct IDUITextStyle *pTextStyle  ) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarDataText(BSTR text  ) = 0;
	virtual HRESULT __stdcall raw_GetTestBack(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTestTextStyle(struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_GetTestText(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTestBack(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_SetTestTextStyle(struct IDUITextStyle *pTextStyle  ) = 0;
	virtual HRESULT __stdcall raw_SetTestText(BSTR text  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarToCtrlTop(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarToCtrlTop(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarToCtrlRight(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarToCtrlRight(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarHeight(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarHeight(long height  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarPenelWidth(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarPenelWidth(long width  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarDataWidth(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarDataWdith(long width  ) = 0;
	virtual HRESULT __stdcall raw_GetMotorCarPenelDataOffset(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMotorCarPenelDataOffset(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarToMotor(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarToMotor(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarToCtrlRight(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarToCtrlRight(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarPenelWidth(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarPenelWdith(long width  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarDataWidth(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarDataWidth(long width  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarHeight(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarHeight(long height  ) = 0;
	virtual HRESULT __stdcall raw_GetTrailCarPenelDataOffset(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTrailCarPenelDataOffset(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetTestToTrailCarLeft(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTestToTrailCarLeft(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetTestToTrailCarBottom(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTestToTrailCarBottom(long offset  ) = 0;
	virtual HRESULT __stdcall raw_GetTestWidth(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTestWidth(long width  ) = 0;
	virtual HRESULT __stdcall raw_GetTestHeight(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTestHeight(long height  ) = 0;
	virtual HRESULT __stdcall raw_GetMeterCenterEllpise(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetMeterCenterEllipse(OLE_HANDLE hBitmap, BSTR bstrPath, struct IDUIImageBase *pImageBase, enum enumCHANGE_IMAGE_FROM enumFrom  ) = 0;
	virtual HRESULT __stdcall raw_GetFrontPointerYOfset(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFrontPointerYOfset(float yOffset  ) = 0;
	virtual HRESULT __stdcall raw_GetAfterPointerYOfset(float *pResult) = 0;
	virtual HRESULT __stdcall raw_SetAfterPointerYOfset(float yOffset  ) = 0;

	//
	//Method Wrapper
	//
	struct IDUIImageBase * GetMeterBack();
	void SetMeterBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	struct IDUIImageBase * GetMeterFrontPointer();
	void SetMeterFrontPointer(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	struct IDUIImageBase * GetMeterAfterPointer();
	void SetMeterAfterPointer(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	long  GetMeterLowerRuler();
	void SetMeterLowerRuler(long  lowerRuler  );
	long  GetMeterHighRuler();
	void SetMeterHighRuler(long  highRuler  );
	long  GetMeterSpaceRuler();
	void SetMeterSpaceRuler(long  spaceRuler  );
	long  GetMeterFrontPointerRuler();
	void SetMeterFrontPointerRuler(long  pointerRuler  );
	long  GetMeterAfterPointerRuler();
	void SetMeterAfterPointerRuler(long  pointerRuler  );
	struct IDUIImageBase * GetMotorCarPenelBack();
	struct IDUITextStyle * GetMotorCarPenelTextStyle();
	tstring  GetMotorCarPenelText();
	void SetMotorCarPenelBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetMotorCarPenelTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetMotorCarPenelText(tstring  text  );
	struct IDUIImageBase * GetMotorCarDataBack();
	struct IDUITextStyle * GetMotorCarDataTextStyle();
	tstring  GetMotorCarDataText();
	void SetMotorCarDataBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetMotorCarDataTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetMotorCarDataText(tstring  text  );
	struct IDUIImageBase * GetTrailCarPenelBack();
	struct IDUITextStyle * GetTrailCarPenelTextStyle();
	tstring  GetTrailCarPenelText();
	void SetTrailCarPenelBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetTrailCarPenelTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetTrailCarPenelText(tstring  text  );
	struct IDUIImageBase * GetTrailCarDataBack();
	struct IDUITextStyle * GetTrailCarDataTextStyle();
	tstring  GetTrailCarDataText();
	void SetTrailCarDataBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetTrailCarDataTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetTrailCarDataText(tstring  text  );
	struct IDUIImageBase * GetTestBack();
	struct IDUITextStyle * GetTestTextStyle();
	tstring  GetTestText();
	void SetTestBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetTestTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetTestText(tstring  text  );
	long  GetMotorCarToCtrlTop();
	void SetMotorCarToCtrlTop(long  offset  );
	long  GetMotorCarToCtrlRight();
	void SetMotorCarToCtrlRight(long  offset  );
	long  GetMotorCarHeight();
	void SetMotorCarHeight(long  height  );
	long  GetMotorCarPenelWidth();
	void SetMotorCarPenelWidth(long  width  );
	long  GetMotorCarDataWidth();
	void SetMotorCarDataWdith(long  width  );
	long  GetMotorCarPenelDataOffset();
	void SetMotorCarPenelDataOffset(long  offset  );
	long  GetTrailCarToMotor();
	void SetTrailCarToMotor(long  offset  );
	long  GetTrailCarToCtrlRight();
	void SetTrailCarToCtrlRight(long  offset  );
	long  GetTrailCarPenelWidth();
	void SetTrailCarPenelWdith(long  width  );
	long  GetTrailCarDataWidth();
	void SetTrailCarDataWidth(long  width  );
	long  GetTrailCarHeight();
	void SetTrailCarHeight(long  height  );
	long  GetTrailCarPenelDataOffset();
	void SetTrailCarPenelDataOffset(long  offset  );
	long  GetTestToTrailCarLeft();
	void SetTestToTrailCarLeft(long  offset  );
	long  GetTestToTrailCarBottom();
	void SetTestToTrailCarBottom(long  offset  );
	long  GetTestWidth();
	void SetTestWidth(long  width  );
	long  GetTestHeight();
	void SetTestHeight(long  height  );
	struct IDUIImageBase * GetMeterCenterEllpise();
	void SetMeterCenterEllipse(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	float  GetFrontPointerYOfset();
	void SetFrontPointerYOfset(float  yOffset  );
	float  GetAfterPointerYOfset();
	void SetAfterPointerYOfset(float  yOffset  );
};

struct IMeter : IDUIControlBase
{

	//
	//Method Wrapper
	//
	struct IDUIImageBase * GetMeterBack();
	void SetMeterBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	struct IDUIImageBase * GetMeterFrontPointer();
	void SetMeterFrontPointer(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	struct IDUIImageBase * GetMeterAfterPointer();
	void SetMeterAfterPointer(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	long  GetMeterLowerRuler();
	void SetMeterLowerRuler(long  lowerRuler  );
	long  GetMeterHighRuler();
	void SetMeterHighRuler(long  highRuler  );
	long  GetMeterSpaceRuler();
	void SetMeterSpaceRuler(long  spaceRuler  );
	long  GetMeterFrontPointerRuler();
	void SetMeterFrontPointerRuler(long  pointerRuler  );
	long  GetMeterAfterPointerRuler();
	void SetMeterAfterPointerRuler(long  pointerRuler  );
	struct IDUIImageBase * GetMotorCarPenelBack();
	struct IDUITextStyle * GetMotorCarPenelTextStyle();
	tstring  GetMotorCarPenelText();
	void SetMotorCarPenelBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetMotorCarPenelTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetMotorCarPenelText(tstring  text  );
	struct IDUIImageBase * GetMotorCarDataBack();
	struct IDUITextStyle * GetMotorCarDataTextStyle();
	tstring  GetMotorCarDataText();
	void SetMotorCarDataBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetMotorCarDataTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetMotorCarDataText(tstring  text  );
	struct IDUIImageBase * GetTrailCarPenelBack();
	struct IDUITextStyle * GetTrailCarPenelTextStyle();
	tstring  GetTrailCarPenelText();
	void SetTrailCarPenelBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetTrailCarPenelTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetTrailCarPenelText(tstring  text  );
	struct IDUIImageBase * GetTrailCarDataBack();
	struct IDUITextStyle * GetTrailCarDataTextStyle();
	tstring  GetTrailCarDataText();
	void SetTrailCarDataBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetTrailCarDataTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetTrailCarDataText(tstring  text  );
	struct IDUIImageBase * GetTestBack();
	struct IDUITextStyle * GetTestTextStyle();
	tstring  GetTestText();
	void SetTestBack(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	void SetTestTextStyle(struct IDUITextStyle * pTextStyle  );
	void SetTestText(tstring  text  );
	long  GetMotorCarToCtrlTop();
	void SetMotorCarToCtrlTop(long  offset  );
	long  GetMotorCarToCtrlRight();
	void SetMotorCarToCtrlRight(long  offset  );
	long  GetMotorCarHeight();
	void SetMotorCarHeight(long  height  );
	long  GetMotorCarPenelWidth();
	void SetMotorCarPenelWidth(long  width  );
	long  GetMotorCarDataWidth();
	void SetMotorCarDataWdith(long  width  );
	long  GetMotorCarPenelDataOffset();
	void SetMotorCarPenelDataOffset(long  offset  );
	long  GetTrailCarToMotor();
	void SetTrailCarToMotor(long  offset  );
	long  GetTrailCarToCtrlRight();
	void SetTrailCarToCtrlRight(long  offset  );
	long  GetTrailCarPenelWidth();
	void SetTrailCarPenelWdith(long  width  );
	long  GetTrailCarDataWidth();
	void SetTrailCarDataWidth(long  width  );
	long  GetTrailCarHeight();
	void SetTrailCarHeight(long  height  );
	long  GetTrailCarPenelDataOffset();
	void SetTrailCarPenelDataOffset(long  offset  );
	long  GetTestToTrailCarLeft();
	void SetTestToTrailCarLeft(long  offset  );
	long  GetTestToTrailCarBottom();
	void SetTestToTrailCarBottom(long  offset  );
	long  GetTestWidth();
	void SetTestWidth(long  width  );
	long  GetTestHeight();
	void SetTestHeight(long  height  );
	struct IDUIImageBase * GetMeterCenterEllpise();
	void SetMeterCenterEllipse(OLE_HANDLE  hBitmap, tstring  bstrPath, struct IDUIImageBase * pImageBase, enum enumCHANGE_IMAGE_FROM  enumFrom  );
	float  GetFrontPointerYOfset();
	void SetFrontPointerYOfset(float  yOffset  );
	float  GetAfterPointerYOfset();
	void SetAfterPointerYOfset(float  yOffset  );
};

enum enumCHANGE_IMAGE_FROM
{ 
	FROM_BASE = 102,
	FROM_HBITMAP = 100,
	FROM_PATH = 101 
};


#include "IndustryAll.tli"
#endif //__HEAD__INDUSTRYALL__