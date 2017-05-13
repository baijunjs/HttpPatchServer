#ifndef __HEAD__OFFICEALL__
#define __HEAD__OFFICEALL__
#include <comdef.h>

#include <xstring>
using namespace std;
#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

struct IDUI3DMenu;
struct __declspec(uuid("9c9442d3-b45a-4756-9d60-7c322300b441")) IDUI3DMenu_;
struct __declspec(uuid("414c8067-09a0-49c0-b1c9-acd1d4b1f45f")) DUI3DMenu;
struct __declspec(uuid("0f726133-8242-4508-995b-878607296f25")) _IDUI3DMenuEvents;
enum DUI_ROTATEMENU_TYPE;

struct IDUI3DRotateMenu;
struct __declspec(uuid("82766421-d32c-4599-a54b-bfbb3d999c8c")) IDUI3DRotateMenu_;
struct __declspec(uuid("27133c46-bb84-4564-bf1b-202b9e1d4d11")) DUI3DRotateMenu;
struct __declspec(uuid("ed203efa-78df-4f3e-a3e4-45196240d7dc")) _IDUI3DRotateMenuEvents;
struct ICDuiPicker;
struct __declspec(uuid("d9e2b401-e937-40e7-82be-1656a01b3b25")) ICDuiPicker_;
struct __declspec(uuid("44629cda-f385-456b-bf06-235ef2a5681b")) CDuiPicker;
struct __declspec(uuid("2e46ce40-82ba-4550-b459-aa40da69e80d")) _ICDuiPickerEvents;
struct IDUIWebKit;
struct __declspec(uuid("e4f56d1e-7e6e-4b19-b3a2-93a1ca1183ee")) IDUIWebKit_;
struct __declspec(uuid("fb875747-56f4-4ec7-aa46-bdced42c0102")) DUIWebKit;
struct __declspec(uuid("7b8f207d-ea8a-444b-b9e4-65d4dbe308ee")) _IDUIWebKitEvents;
enum DUIOUTLOOKBAR_STATE;

struct IDUIOutLookBar;
struct __declspec(uuid("3c1d27c1-58f7-40c6-84d4-a69cbc2f97b2")) IDUIOutLookBar_;
struct __declspec(uuid("9e6512f9-e199-40ec-b81b-1c88ed5aaa5e")) DUIOutLookBar;
struct __declspec(uuid("e98cf5c2-e5c8-489d-af1b-b8e35e12e79a")) _IDUIOutLookBarEvents;
struct __declspec(uuid("cc43d690-b051-42c0-9316-ff2007cc77f0")) IDUITreeToolStatic;
struct __declspec(uuid("c135371b-1f27-45c9-9ccb-395009d05bfa")) DUITreeToolStatic;
struct __declspec(uuid("4730a708-998b-42c9-8164-ab0f192adc59")) _IDUITreeToolStaticEvents;
struct __declspec(uuid("7bbd7549-4606-4729-ba4c-74ef96f5bb9d")) IDUITreeToolRadio;
struct __declspec(uuid("41f41c81-1efb-4415-ba23-d99233a209d4")) DUITreeToolRadio;
struct __declspec(uuid("dee5198d-7275-4b6c-89e0-1195a948b9f6")) _IDUITreeToolRadioEvents;
struct __declspec(uuid("3b044072-ff13-4aaa-bddb-98cbfaf98e3a")) IDUITreeToolCheck;
struct __declspec(uuid("0c2110fc-0635-4ce8-9919-d90e44e2e4e1")) DUITreeToolCheck;
struct __declspec(uuid("137e3e83-76ca-4829-a398-eda5410a6eba")) _IDUITreeToolCheckEvents;
struct __declspec(uuid("17d327e6-4fc8-4c59-81f7-88b7b7ca45e9")) IDUITreeToolButton;
struct __declspec(uuid("ce51ec67-3131-417c-a234-9038bd7e844d")) DUITreeToolButton;
struct __declspec(uuid("58703b69-ba83-4ce0-8676-57bff7d3cbe0")) _IDUITreeToolButtonEvents;
struct __declspec(uuid("aec41f8e-7a8b-4b2d-8507-707e0a51e80e")) DUITreeToolItemBase;
struct __declspec(uuid("4dd5e499-31d7-437b-8e05-96afbc6f3ec4")) _IDUITreeToolItemBaseEvents;
struct __declspec(uuid("513a3d4f-90c3-4786-84e0-84f0f7ce8192")) DUITreeToolBar;
struct __declspec(uuid("de28ba00-7cc1-480a-934e-2035303fdd5c")) _IDUITreeToolBarEvents;
struct __declspec(uuid("c11426e8-4ca4-4260-8db2-92a4c0eeda46")) DUITreeItem;
struct __declspec(uuid("ceb77c1b-6883-4c1c-9815-804d363caebd")) _IDUITreeItemEvents;
enum ItemState;

struct __declspec(uuid("6efb8ac6-61ba-4d3f-a599-bad68068fd5b")) IDUITreeItem;
struct __declspec(uuid("aa068e64-2cde-434a-8b85-8b42682597cc")) IDUITreeToolItemBase;
enum DUI_TREETOOL_STYLE;

struct __declspec(uuid("626d297c-dc98-410c-8e56-b0408e1581c0")) IDUITreeToolBar;
enum DUISIMPLETREE_STATE;

struct IDUISimpleTree;
struct __declspec(uuid("88a3196a-3223-4f58-874b-5d6fc4b7d74e")) IDUISimpleTree_;
struct __declspec(uuid("90ab8e99-205a-404d-9870-357bf0bd7607")) DUISimpleTree;
struct __declspec(uuid("4def30a4-bd8f-4054-af9f-b999ff79f223")) _IDUISimpleTreeEvents;
struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) DUITreeTool_MsgInfo;
enum DUITREE_NOTIFY;

enum DUITREE_NOTIFY
{ 
	DUITREE_CHECKITEM = 2972,
	DUITREE_CUSTOMCLICK = 2973,
	DUITREE_CUSTOMITEM_MOUSELEAVE = 2975,
	DUITREE_CUSTOMITEM_MOUSEMOVE = 2974,
	DUITREE_EXPANDCHANGE = 2970,
	DUITREE_HEADLBUTTONUP = 2966,
	DUITREE_ITEMCHANGE = 2969,
	DUITREE_ITEMDRAG = 2967,
	DUITREE_LBUTTONDBLCLK = 2961,
	DUITREE_LBUTTONDOWN = 2963,
	DUITREE_LBUTTONUP = 2962,
	DUITREE_MOUSELEAVE = 2971,
	DUITREE_MOUSEMOVE = 2960,
	DUITREE_RBUTTONDOWN = 2965,
	DUITREE_RBUTTONUP = 2964,
	DUITREE_TOOL_COMMAND = 2968,
	DUITREE_UPDATEITEM = 2976 
};

struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) DUITreeTool_MsgInfo
{
	long 	lParam1;
	long 	lParam2;
	long 	lParam3;
	long 	lParam4;
	long 	lParam5;
};

struct __declspec(uuid("4def30a4-bd8f-4054-af9f-b999ff79f223")) _IDUISimpleTreeEvents : IDispatch
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

struct __declspec(uuid("88a3196a-3223-4f58-874b-5d6fc4b7d74e")) IDUISimpleTree_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetDrawBackColor(VARIANT_BOOL bDrawColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetDrawBackColor(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBackImage(struct IDUIImageBase *pImageBae, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetBackImage(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetBackColor(struct IFillColor *pFillColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetBackColor(struct IFillColor **pResult) = 0;
	virtual HRESULT __stdcall raw_SetDrawItemColor(VARIANT_BOOL bDrawColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetDrawItemColor(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemImage(enum DUISIMPLETREE_STATE eState, struct IDUIImageBase *pImageBase, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemImage(enum DUISIMPLETREE_STATE eState, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemColor(enum DUISIMPLETREE_STATE eState, struct IFillColor *pFillColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemColor(enum DUISIMPLETREE_STATE eState, struct IFillColor **pResult) = 0;
	virtual HRESULT __stdcall raw_SetTextStyle(enum DUISIMPLETREE_STATE eState, struct IDUITextStyle *pTextStyle, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetTextStyle(enum DUISIMPLETREE_STATE eState, struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_SetButtonImage(enum DUISIMPLETREE_STATE eState, VARIANT_BOOL bChecked, struct IDUIImageBase *pImageBase, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetButtonImage(enum DUISIMPLETREE_STATE eState, VARIANT_BOOL bChecked, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetHasLines(VARIANT_BOOL bHasLines, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_IsHasLines(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetHasButtons(VARIANT_BOOL bHasButtons, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_IsHasButtons(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetLineOnRoot(VARIANT_BOOL bLineOnRoot, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_IsLineOnRoot(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetLineColor(OLE_COLOR clrLine, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetLineColor(OLE_COLOR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetLineSize(short nSize, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetLineSize(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetIndent(short nIndent, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetIndent(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemHeight(short nHeight, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemHeight(short *pResult) = 0;
	virtual HRESULT __stdcall raw_InsertChild(OLE_HANDLE hParent, OLE_HANDLE hInsertAfter, BSTR strText, VARIANT_BOOL bRedraw, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_InsertSibling(OLE_HANDLE hpInsertAfter, BSTR strText, VARIANT_BOOL bRedraw, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetChildItem(OLE_HANDLE hParent, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_ItemHasChildren(OLE_HANDLE hParent, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetParentItem(OLE_HANDLE hItem, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetRootItem(OLE_HANDLE hItem, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_DeleteItem(OLE_HANDLE hItem, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_Expand(OLE_HANDLE hItem, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SelectItem(OLE_HANDLE hItem, VARIANT_BOOL bChangePos, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetSelectedItem(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemText(OLE_HANDLE hItem, BSTR strText, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemText(OLE_HANDLE hItem, BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_HitTest(long nX, long nY, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemRect(OLE_HANDLE hItem, struct SkinRect *pResult) = 0;
	virtual HRESULT __stdcall raw_SetScrollSize(long nSize  ) = 0;
	virtual HRESULT __stdcall raw_GetScrollSize(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetLeftScroll(VARIANT_BOOL bLeftScroll  ) = 0;
	virtual HRESULT __stdcall raw_IsLeftScroll(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_AppendChild(OLE_HANDLE hParent, BSTR strText, VARIANT_BOOL bRedraw, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemIconByPath(OLE_HANDLE hItem, BSTR strPath, BSTR strSelPath, OLE_COLOR clrTrans, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetIconOffset(short nOffsetX, short nOffsetY  ) = 0;
	virtual HRESULT __stdcall raw_GetIconOffset(short *pnOffsetX, short *pnOffsetY  ) = 0;
	virtual HRESULT __stdcall raw_SetShowIcon(VARIANT_BOOL bShowIcon  ) = 0;
	virtual HRESULT __stdcall raw_IsShowIcon(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemIconByImgBase(OLE_HANDLE hItem, struct IDUIImageBase *pImageBase, struct IDUIImageBase *pSelImageBase, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemIconByIcon(OLE_HANDLE hItem, OLE_HANDLE hIcon, OLE_HANDLE hSelIcon, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemImageIndex(OLE_HANDLE hItem, long nImage, long nSelImage, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetImageList(OLE_HANDLE hImageList, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemData(OLE_HANDLE hItem, OLE_HANDLE hData, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemData(OLE_HANDLE hItem, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetNextSiblingItem(OLE_HANDLE hItem, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetPrevSiblingItem(OLE_HANDLE hItem, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemTextStyle(OLE_HANDLE hItem, enum DUISIMPLETREE_STATE eState, struct IDUITextStyle *pTextStyle, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemTextStyle(OLE_HANDLE hItem, enum DUISIMPLETREE_STATE eState, struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemCount(short *pResult) = 0;
	virtual HRESULT __stdcall raw_GetChildItemCount(OLE_HANDLE hItem, short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetStateOffset(short nOffsetX, short nOffsetY  ) = 0;
	virtual HRESULT __stdcall raw_GetStateOffset(short *pnOffsetX, short *pnOffsetY  ) = 0;
	virtual HRESULT __stdcall raw_SetShowState(VARIANT_BOOL bShowIcon  ) = 0;
	virtual HRESULT __stdcall raw_IsShowState(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetStateImage(enum DUISIMPLETREE_STATE eState, struct IDUIImageBase *pImageBase, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetStateImage(enum DUISIMPLETREE_STATE eState, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetStateItem(OLE_HANDLE hItem, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetStateItem(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetChildList(OLE_HANDLE pItem, VARIANT_BOOL bIsChildList  ) = 0;
	virtual HRESULT __stdcall raw_IsChildList(OLE_HANDLE pItem, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetNodeItemText(OLE_HANDLE pItem, long nCols, BSTR strText, VARIANT_BOOL bRedraw  ) = 0;
	virtual HRESULT __stdcall raw_GetNodeItemText(OLE_HANDLE pItem, long nCols, BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetColsWidth(long nWidth, long nCols  ) = 0;
	virtual HRESULT __stdcall raw_GetColsWidth(long nCols, long *nResult  ) = 0;
	virtual HRESULT __stdcall raw_SetColsTextStyle(long nCols, enum DUISIMPLETREE_STATE eState, struct IDUITextStyle *pTextStyle  ) = 0;
	virtual HRESULT __stdcall raw_GetColsTextStyle(long nCols, enum DUISIMPLETREE_STATE eState, struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_InsertCols(short nCols, BSTR strText, short nWidth, short *pResult) = 0;
	virtual HRESULT __stdcall raw_Sort(OLE_HANDLE pCallBackFunc, OLE_HANDLE pParentNode  ) = 0;
	virtual HRESULT __stdcall raw_GetItemIconImgBase(OLE_HANDLE hItem, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_DeleteChildren(OLE_HANDLE hItem, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetChildNeedIndent(VARIANT_BOOL bNeedIndent  ) = 0;
	virtual HRESULT __stdcall raw_GetChildNeedIndent(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RefreshItem(OLE_HANDLE hItem  ) = 0;
	virtual HRESULT __stdcall raw_GetItemToolBar(OLE_HANDLE hItem, struct IDUITreeToolBar **pResult) = 0;
	virtual HRESULT __stdcall raw_SetCheckBoxStyle(VARIANT_BOOL bHasCheckBox, VARIANT_BOOL bRedraw  ) = 0;
	virtual HRESULT __stdcall raw_GetCheckBoxStyle(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetSupportMultiSel(VARIANT_BOOL bMutilSel  ) = 0;
	virtual HRESULT __stdcall raw_IsSupportMultiSel(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetCheckItemCount(short *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFirstCheckItem(struct IDUITreeItem **pResult) = 0;
	virtual HRESULT __stdcall raw_GetNextCheckItem(struct IDUITreeItem *pItem, struct IDUITreeItem **pResult) = 0;
	virtual HRESULT __stdcall raw_GetSelectedItemCount(short *pnResult  ) = 0;
	virtual HRESULT __stdcall raw_GetFirstSelectedItem(struct IDUITreeItem **pResult) = 0;
	virtual HRESULT __stdcall raw_GetNextSelectedItem(struct IDUITreeItem *pItem, struct IDUITreeItem **pResult) = 0;
	virtual HRESULT __stdcall raw_SetSupportToolBar(VARIANT_BOOL bSupport  ) = 0;
	virtual HRESULT __stdcall raw_IsSupportToolBar(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetToolBarOffset(short nOffset  ) = 0;
	virtual HRESULT __stdcall raw_GetToolBarOffset(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetToolMinSpaceWithText(short nSpace  ) = 0;
	virtual HRESULT __stdcall raw_GetToolMinSpaceWithText(short *pResult) = 0;
	virtual HRESULT __stdcall raw_IsNodeExpand(OLE_HANDLE hItem, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SortSingleNode(OLE_HANDLE pCallBackFunc, OLE_HANDLE pParentNode, OLE_HANDLE pSingleNode  ) = 0;
	virtual HRESULT __stdcall raw_SwapNode(OLE_HANDLE pNode1, OLE_HANDLE pNode2  ) = 0;
	virtual HRESULT __stdcall raw_SetItmeHBitmap(OLE_HANDLE hItem, OLE_HANDLE hBitmap, OLE_HANDLE hSelBitmap, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemHBitmap(OLE_HANDLE hItem, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemByIndex(short nIndex, OLE_HANDLE hParent, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetScrollTop() = 0;
	virtual HRESULT __stdcall raw_SetScrollBottom() = 0;
	virtual HRESULT __stdcall raw_CheckItem(OLE_HANDLE hItem, VARIANT_BOOL bCheck  ) = 0;
	virtual HRESULT __stdcall raw_IsCheckItem(OLE_HANDLE hItem, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemNodeRect(OLE_HANDLE hItem, struct SkinRect *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemHasCheckBox(OLE_HANDLE hItem, VARIANT_BOOL bHasCheck  ) = 0;
	virtual HRESULT __stdcall raw_SetItemState(OLE_HANDLE hItem, enum ItemState nState  ) = 0;
	virtual HRESULT __stdcall raw_GetItemModel(OLE_HANDLE hItem, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetDragSupport(VARIANT_BOOL bDragSupport, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemWidth(short nWidth, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemWidth(short *pResult) = 0;
	virtual HRESULT __stdcall raw_UnSelectItem(OLE_HANDLE hItem, VARIANT_BOOL bChangePos, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_ClearAllSelectItems(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemModel(IDispatch *pModelForm  ) = 0;
	virtual HRESULT __stdcall raw_DeleteAllItem() = 0;
	virtual HRESULT __stdcall raw_GetIsAutoCheck(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetAutoCheck(VARIANT_BOOL bAutoCheck  ) = 0;
	virtual HRESULT __stdcall raw_GetItemState(OLE_HANDLE hItem, enum ItemState *pResult) = 0;
	virtual HRESULT __stdcall raw_RefreshVirtual() = 0;

	//
	//Method Wrapper
	//
	BOOL  SetDrawBackColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawBackColor();
	BOOL  SetBackImage(struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetBackImage();
	BOOL  SetBackColor(struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetBackColor();
	BOOL  SetDrawItemColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawItemColor();
	BOOL  SetItemImage(enum DUISIMPLETREE_STATE  eState, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetItemImage(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetItemColor(enum DUISIMPLETREE_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetItemColor(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetTextStyle(enum DUISIMPLETREE_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetTextStyle(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetButtonImage(enum DUISIMPLETREE_STATE  eState, BOOL  bChecked, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetButtonImage(enum DUISIMPLETREE_STATE  eState, BOOL  bChecked  );
	BOOL  SetHasLines(BOOL  bHasLines, BOOL  bRedraw  );
	BOOL  IsHasLines();
	BOOL  SetHasButtons(BOOL  bHasButtons, BOOL  bRedraw  );
	BOOL  IsHasButtons();
	BOOL  SetLineOnRoot(BOOL  bLineOnRoot, BOOL  bRedraw  );
	BOOL  IsLineOnRoot();
	BOOL  SetLineColor(OLE_COLOR  clrLine, BOOL  bRedraw  );
	OLE_COLOR  GetLineColor();
	BOOL  SetLineSize(short  nSize, BOOL  bRedraw  );
	short  GetLineSize();
	BOOL  SetIndent(short  nIndent, BOOL  bRedraw  );
	short  GetIndent();
	BOOL  SetItemHeight(short  nHeight, BOOL  bRedraw  );
	short  GetItemHeight();
	OLE_HANDLE  InsertChild(OLE_HANDLE  hParent, OLE_HANDLE  hInsertAfter, tstring  strText, BOOL  bRedraw  );
	OLE_HANDLE  InsertSibling(OLE_HANDLE  hpInsertAfter, tstring  strText, BOOL  bRedraw  );
	OLE_HANDLE  GetChildItem(OLE_HANDLE  hParent  );
	BOOL  ItemHasChildren(OLE_HANDLE  hParent  );
	OLE_HANDLE  GetParentItem(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetRootItem(OLE_HANDLE  hItem  );
	BOOL  DeleteItem(OLE_HANDLE  hItem, BOOL  bRedraw  );
	BOOL  Expand(OLE_HANDLE  hItem, BOOL  bRedraw  );
	BOOL  SelectItem(OLE_HANDLE  hItem, BOOL  bChangePos  );
	OLE_HANDLE  GetSelectedItem();
	BOOL  SetItemText(OLE_HANDLE  hItem, tstring  strText, BOOL  bRedraw  );
	tstring  GetItemText(OLE_HANDLE  hItem  );
	OLE_HANDLE  HitTest(long  nX, long  nY  );
	struct SkinRect  GetItemRect(OLE_HANDLE  hItem  );
	void SetScrollSize(long  nSize  );
	long  GetScrollSize();
	void SetLeftScroll(BOOL  bLeftScroll  );
	BOOL  IsLeftScroll();
	OLE_HANDLE  AppendChild(OLE_HANDLE  hParent, tstring  strText, BOOL  bRedraw  );
	BOOL  SetItemIconByPath(OLE_HANDLE  hItem, tstring  strPath, tstring  strSelPath, OLE_COLOR  clrTrans  );
	void SetIconOffset(short  nOffsetX, short  nOffsetY  );
	void GetIconOffset(short * pnOffsetX, short * pnOffsetY  );
	void SetShowIcon(BOOL  bShowIcon  );
	BOOL  IsShowIcon();
	BOOL  SetItemIconByImgBase(OLE_HANDLE  hItem, struct IDUIImageBase * pImageBase, struct IDUIImageBase * pSelImageBase  );
	BOOL  SetItemIconByIcon(OLE_HANDLE  hItem, OLE_HANDLE  hIcon, OLE_HANDLE  hSelIcon  );
	BOOL  SetItemImageIndex(OLE_HANDLE  hItem, long  nImage, long  nSelImage  );
	BOOL  SetImageList(OLE_HANDLE  hImageList  );
	BOOL  SetItemData(OLE_HANDLE  hItem, OLE_HANDLE  hData  );
	OLE_HANDLE  GetItemData(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetNextSiblingItem(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetPrevSiblingItem(OLE_HANDLE  hItem  );
	BOOL  SetItemTextStyle(OLE_HANDLE  hItem, enum DUISIMPLETREE_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetItemTextStyle(OLE_HANDLE  hItem, enum DUISIMPLETREE_STATE  eState  );
	short  GetItemCount();
	short  GetChildItemCount(OLE_HANDLE  hItem  );
	void SetStateOffset(short  nOffsetX, short  nOffsetY  );
	void GetStateOffset(short * pnOffsetX, short * pnOffsetY  );
	void SetShowState(BOOL  bShowIcon  );
	BOOL  IsShowState();
	BOOL  SetStateImage(enum DUISIMPLETREE_STATE  eState, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetStateImage(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetStateItem(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetStateItem();
	void SetChildList(OLE_HANDLE  pItem, BOOL  bIsChildList  );
	BOOL  IsChildList(OLE_HANDLE  pItem  );
	void SetNodeItemText(OLE_HANDLE  pItem, long  nCols, tstring  strText, BOOL  bRedraw  );
	tstring  GetNodeItemText(OLE_HANDLE  pItem, long  nCols  );
	void SetColsWidth(long  nWidth, long  nCols  );
	void GetColsWidth(long  nCols, long * nResult  );
	void SetColsTextStyle(long  nCols, enum DUISIMPLETREE_STATE  eState, struct IDUITextStyle * pTextStyle  );
	struct IDUITextStyle * GetColsTextStyle(long  nCols, enum DUISIMPLETREE_STATE  eState  );
	short  InsertCols(short  nCols, tstring  strText, short  nWidth  );
	void Sort(OLE_HANDLE  pCallBackFunc, OLE_HANDLE  pParentNode  );
	struct IDUIImageBase * GetItemIconImgBase(OLE_HANDLE  hItem  );
	BOOL  DeleteChildren(OLE_HANDLE  hItem, BOOL  bRedraw  );
	void SetChildNeedIndent(BOOL  bNeedIndent  );
	BOOL  GetChildNeedIndent();
	void RefreshItem(OLE_HANDLE  hItem  );
	struct IDUITreeToolBar * GetItemToolBar(OLE_HANDLE  hItem  );
	void SetCheckBoxStyle(BOOL  bHasCheckBox, BOOL  bRedraw  );
	BOOL  GetCheckBoxStyle();
	void SetSupportMultiSel(BOOL  bMutilSel  );
	BOOL  IsSupportMultiSel();
	short  GetCheckItemCount();
	struct IDUITreeItem * GetFirstCheckItem();
	struct IDUITreeItem * GetNextCheckItem(struct IDUITreeItem * pItem  );
	void GetSelectedItemCount(short * pnResult  );
	struct IDUITreeItem * GetFirstSelectedItem();
	struct IDUITreeItem * GetNextSelectedItem(struct IDUITreeItem * pItem  );
	void SetSupportToolBar(BOOL  bSupport  );
	BOOL  IsSupportToolBar();
	void SetToolBarOffset(short  nOffset  );
	short  GetToolBarOffset();
	void SetToolMinSpaceWithText(short  nSpace  );
	short  GetToolMinSpaceWithText();
	BOOL  IsNodeExpand(OLE_HANDLE  hItem  );
	void SortSingleNode(OLE_HANDLE  pCallBackFunc, OLE_HANDLE  pParentNode, OLE_HANDLE  pSingleNode  );
	void SwapNode(OLE_HANDLE  pNode1, OLE_HANDLE  pNode2  );
	BOOL  SetItmeHBitmap(OLE_HANDLE  hItem, OLE_HANDLE  hBitmap, OLE_HANDLE  hSelBitmap  );
	OLE_HANDLE  GetItemHBitmap(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetItemByIndex(short  nIndex, OLE_HANDLE  hParent  );
	void SetScrollTop();
	void SetScrollBottom();
	void CheckItem(OLE_HANDLE  hItem, BOOL  bCheck  );
	BOOL  IsCheckItem(OLE_HANDLE  hItem  );
	struct SkinRect  GetItemNodeRect(OLE_HANDLE  hItem  );
	void SetItemHasCheckBox(OLE_HANDLE  hItem, BOOL  bHasCheck  );
	void SetItemState(OLE_HANDLE  hItem, enum ItemState  nState  );
	OLE_HANDLE  GetItemModel(OLE_HANDLE  hItem  );
	BOOL  SetDragSupport(BOOL  bDragSupport, BOOL  bRedraw  );
	BOOL  SetItemWidth(short  nWidth, BOOL  bRedraw  );
	short  GetItemWidth();
	BOOL  UnSelectItem(OLE_HANDLE  hItem, BOOL  bChangePos  );
	BOOL  ClearAllSelectItems();
	void SetItemModel(IDispatch * pModelForm  );
	void DeleteAllItem();
	BOOL  GetIsAutoCheck();
	void SetAutoCheck(BOOL  bAutoCheck  );
	enum ItemState  GetItemState(OLE_HANDLE  hItem  );
	void RefreshVirtual();
};

struct IDUISimpleTree : IDUIControlBase
{

	//
	//Method Wrapper
	//
	BOOL  SetDrawBackColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawBackColor();
	BOOL  SetBackImage(struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetBackImage();
	BOOL  SetBackColor(struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetBackColor();
	BOOL  SetDrawItemColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawItemColor();
	BOOL  SetItemImage(enum DUISIMPLETREE_STATE  eState, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetItemImage(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetItemColor(enum DUISIMPLETREE_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetItemColor(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetTextStyle(enum DUISIMPLETREE_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetTextStyle(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetButtonImage(enum DUISIMPLETREE_STATE  eState, BOOL  bChecked, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetButtonImage(enum DUISIMPLETREE_STATE  eState, BOOL  bChecked  );
	BOOL  SetHasLines(BOOL  bHasLines, BOOL  bRedraw  );
	BOOL  IsHasLines();
	BOOL  SetHasButtons(BOOL  bHasButtons, BOOL  bRedraw  );
	BOOL  IsHasButtons();
	BOOL  SetLineOnRoot(BOOL  bLineOnRoot, BOOL  bRedraw  );
	BOOL  IsLineOnRoot();
	BOOL  SetLineColor(OLE_COLOR  clrLine, BOOL  bRedraw  );
	OLE_COLOR  GetLineColor();
	BOOL  SetLineSize(short  nSize, BOOL  bRedraw  );
	short  GetLineSize();
	BOOL  SetIndent(short  nIndent, BOOL  bRedraw  );
	short  GetIndent();
	BOOL  SetItemHeight(short  nHeight, BOOL  bRedraw  );
	short  GetItemHeight();
	OLE_HANDLE  InsertChild(OLE_HANDLE  hParent, OLE_HANDLE  hInsertAfter, tstring  strText, BOOL  bRedraw  );
	OLE_HANDLE  InsertSibling(OLE_HANDLE  hpInsertAfter, tstring  strText, BOOL  bRedraw  );
	OLE_HANDLE  GetChildItem(OLE_HANDLE  hParent  );
	BOOL  ItemHasChildren(OLE_HANDLE  hParent  );
	OLE_HANDLE  GetParentItem(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetRootItem(OLE_HANDLE  hItem  );
	BOOL  DeleteItem(OLE_HANDLE  hItem, BOOL  bRedraw  );
	BOOL  Expand(OLE_HANDLE  hItem, BOOL  bRedraw  );
	BOOL  SelectItem(OLE_HANDLE  hItem, BOOL  bChangePos  );
	OLE_HANDLE  GetSelectedItem();
	BOOL  SetItemText(OLE_HANDLE  hItem, tstring  strText, BOOL  bRedraw  );
	tstring  GetItemText(OLE_HANDLE  hItem  );
	OLE_HANDLE  HitTest(long  nX, long  nY  );
	struct SkinRect  GetItemRect(OLE_HANDLE  hItem  );
	void SetScrollSize(long  nSize  );
	long  GetScrollSize();
	void SetLeftScroll(BOOL  bLeftScroll  );
	BOOL  IsLeftScroll();
	OLE_HANDLE  AppendChild(OLE_HANDLE  hParent, tstring  strText, BOOL  bRedraw  );
	BOOL  SetItemIconByPath(OLE_HANDLE  hItem, tstring  strPath, tstring  strSelPath, OLE_COLOR  clrTrans  );
	void SetIconOffset(short  nOffsetX, short  nOffsetY  );
	void GetIconOffset(short * pnOffsetX, short * pnOffsetY  );
	void SetShowIcon(BOOL  bShowIcon  );
	BOOL  IsShowIcon();
	BOOL  SetItemIconByImgBase(OLE_HANDLE  hItem, struct IDUIImageBase * pImageBase, struct IDUIImageBase * pSelImageBase  );
	BOOL  SetItemIconByIcon(OLE_HANDLE  hItem, OLE_HANDLE  hIcon, OLE_HANDLE  hSelIcon  );
	BOOL  SetItemImageIndex(OLE_HANDLE  hItem, long  nImage, long  nSelImage  );
	BOOL  SetImageList(OLE_HANDLE  hImageList  );
	BOOL  SetItemData(OLE_HANDLE  hItem, OLE_HANDLE  hData  );
	OLE_HANDLE  GetItemData(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetNextSiblingItem(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetPrevSiblingItem(OLE_HANDLE  hItem  );
	BOOL  SetItemTextStyle(OLE_HANDLE  hItem, enum DUISIMPLETREE_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetItemTextStyle(OLE_HANDLE  hItem, enum DUISIMPLETREE_STATE  eState  );
	short  GetItemCount();
	short  GetChildItemCount(OLE_HANDLE  hItem  );
	void SetStateOffset(short  nOffsetX, short  nOffsetY  );
	void GetStateOffset(short * pnOffsetX, short * pnOffsetY  );
	void SetShowState(BOOL  bShowIcon  );
	BOOL  IsShowState();
	BOOL  SetStateImage(enum DUISIMPLETREE_STATE  eState, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetStateImage(enum DUISIMPLETREE_STATE  eState  );
	BOOL  SetStateItem(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetStateItem();
	void SetChildList(OLE_HANDLE  pItem, BOOL  bIsChildList  );
	BOOL  IsChildList(OLE_HANDLE  pItem  );
	void SetNodeItemText(OLE_HANDLE  pItem, long  nCols, tstring  strText, BOOL  bRedraw  );
	tstring  GetNodeItemText(OLE_HANDLE  pItem, long  nCols  );
	void SetColsWidth(long  nWidth, long  nCols  );
	void GetColsWidth(long  nCols, long * nResult  );
	void SetColsTextStyle(long  nCols, enum DUISIMPLETREE_STATE  eState, struct IDUITextStyle * pTextStyle  );
	struct IDUITextStyle * GetColsTextStyle(long  nCols, enum DUISIMPLETREE_STATE  eState  );
	short  InsertCols(short  nCols, tstring  strText, short  nWidth  );
	void Sort(OLE_HANDLE  pCallBackFunc, OLE_HANDLE  pParentNode  );
	struct IDUIImageBase * GetItemIconImgBase(OLE_HANDLE  hItem  );
	BOOL  DeleteChildren(OLE_HANDLE  hItem, BOOL  bRedraw  );
	void SetChildNeedIndent(BOOL  bNeedIndent  );
	BOOL  GetChildNeedIndent();
	void RefreshItem(OLE_HANDLE  hItem  );
	struct IDUITreeToolBar * GetItemToolBar(OLE_HANDLE  hItem  );
	void SetCheckBoxStyle(BOOL  bHasCheckBox, BOOL  bRedraw  );
	BOOL  GetCheckBoxStyle();
	void SetSupportMultiSel(BOOL  bMutilSel  );
	BOOL  IsSupportMultiSel();
	short  GetCheckItemCount();
	struct IDUITreeItem * GetFirstCheckItem();
	struct IDUITreeItem * GetNextCheckItem(struct IDUITreeItem * pItem  );
	void GetSelectedItemCount(short * pnResult  );
	struct IDUITreeItem * GetFirstSelectedItem();
	struct IDUITreeItem * GetNextSelectedItem(struct IDUITreeItem * pItem  );
	void SetSupportToolBar(BOOL  bSupport  );
	BOOL  IsSupportToolBar();
	void SetToolBarOffset(short  nOffset  );
	short  GetToolBarOffset();
	void SetToolMinSpaceWithText(short  nSpace  );
	short  GetToolMinSpaceWithText();
	BOOL  IsNodeExpand(OLE_HANDLE  hItem  );
	void SortSingleNode(OLE_HANDLE  pCallBackFunc, OLE_HANDLE  pParentNode, OLE_HANDLE  pSingleNode  );
	void SwapNode(OLE_HANDLE  pNode1, OLE_HANDLE  pNode2  );
	BOOL  SetItmeHBitmap(OLE_HANDLE  hItem, OLE_HANDLE  hBitmap, OLE_HANDLE  hSelBitmap  );
	OLE_HANDLE  GetItemHBitmap(OLE_HANDLE  hItem  );
	OLE_HANDLE  GetItemByIndex(short  nIndex, OLE_HANDLE  hParent  );
	void SetScrollTop();
	void SetScrollBottom();
	void CheckItem(OLE_HANDLE  hItem, BOOL  bCheck  );
	BOOL  IsCheckItem(OLE_HANDLE  hItem  );
	struct SkinRect  GetItemNodeRect(OLE_HANDLE  hItem  );
	void SetItemHasCheckBox(OLE_HANDLE  hItem, BOOL  bHasCheck  );
	void SetItemState(OLE_HANDLE  hItem, enum ItemState  nState  );
	OLE_HANDLE  GetItemModel(OLE_HANDLE  hItem  );
	BOOL  SetDragSupport(BOOL  bDragSupport, BOOL  bRedraw  );
	BOOL  SetItemWidth(short  nWidth, BOOL  bRedraw  );
	short  GetItemWidth();
	BOOL  UnSelectItem(OLE_HANDLE  hItem, BOOL  bChangePos  );
	BOOL  ClearAllSelectItems();
	void SetItemModel(IDispatch * pModelForm  );
	void DeleteAllItem();
	BOOL  GetIsAutoCheck();
	void SetAutoCheck(BOOL  bAutoCheck  );
	enum ItemState  GetItemState(OLE_HANDLE  hItem  );
	void RefreshVirtual();
};

enum DUISIMPLETREE_STATE
{ 
	DUISIMPLETREE_STATE_DISABLED = 3,
	DUISIMPLETREE_STATE_HOT = 1,
	DUISIMPLETREE_STATE_LAST = 4,
	DUISIMPLETREE_STATE_NORMAL = 0,
	DUISIMPLETREE_STATE_SELECTED = 2 
};

struct __declspec(uuid("626d297c-dc98-410c-8e56-b0408e1581c0")) IDUITreeToolBar : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_AppendItem(long nID, BSTR strName, short nWidth, enum DUI_TREETOOL_STYLE eStyle, struct IDUITreeToolItemBase **pResult) = 0;
	virtual HRESULT __stdcall raw_InsertItem(short nIndex, long nID, BSTR strName, short nWidth, enum DUI_TREETOOL_STYLE eStyle, struct IDUITreeToolItemBase **pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveItem(long nItem  ) = 0;
	virtual HRESULT __stdcall raw_GetItem(long nID, struct IDUITreeToolItemBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemByName(BSTR strName, struct IDUITreeToolItemBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetAt(short nIndex, struct IDUITreeToolItemBase **pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemCount(short *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveAllItems() = 0;

	//
	//Method Wrapper
	//
	struct IDUITreeToolItemBase * AppendItem(long  nID, tstring  strName, short  nWidth, enum DUI_TREETOOL_STYLE  eStyle  );
	struct IDUITreeToolItemBase * InsertItem(short  nIndex, long  nID, tstring  strName, short  nWidth, enum DUI_TREETOOL_STYLE  eStyle  );
	void RemoveItem(long  nItem  );
	struct IDUITreeToolItemBase * GetItem(long  nID  );
	struct IDUITreeToolItemBase * GetItemByName(tstring  strName  );
	struct IDUITreeToolItemBase * GetAt(short  nIndex  );
	short  GetItemCount();
	void RemoveAllItems();
};

enum DUI_TREETOOL_STYLE
{ 
	TREETOOLSTYLE_BUTTON = 0,
	TREETOOLSTYLE_CHECK = 1,
	TREETOOLSTYLE_LAST = 4,
	TREETOOLSTYLE_RADIO = 2,
	TREETOOLSTYLE_STATIC = 3 
};

struct __declspec(uuid("aa068e64-2cde-434a-8b85-8b42682597cc")) IDUITreeToolItemBase : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetObjPtr(OLE_HANDLE pObjPtr  ) = 0;
	virtual HRESULT __stdcall raw_SetID(long nID  ) = 0;
	virtual HRESULT __stdcall raw_GetID(long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetName(BSTR strName  ) = 0;
	virtual HRESULT __stdcall raw_GetName(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetToolTip(BSTR strToolTip  ) = 0;
	virtual HRESULT __stdcall raw_GetToolTip(BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetWidth(short nWidth  ) = 0;
	virtual HRESULT __stdcall raw_GetWidth(short *pResult) = 0;
	virtual HRESULT __stdcall raw_GetStyle(enum DUI_TREETOOL_STYLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetImage(OLE_HANDLE hBmp  ) = 0;
	virtual HRESULT __stdcall raw_GetImage(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetImageFile(BSTR strImage  ) = 0;
	virtual HRESULT __stdcall raw_GetImageFile(BSTR *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetObjPtr(OLE_HANDLE  pObjPtr  );
	void SetID(long  nID  );
	long  GetID();
	void SetName(tstring  strName  );
	tstring  GetName();
	void SetToolTip(tstring  strToolTip  );
	tstring  GetToolTip();
	void SetWidth(short  nWidth  );
	short  GetWidth();
	enum DUI_TREETOOL_STYLE  GetStyle();
	void SetImage(OLE_HANDLE  hBmp  );
	OLE_HANDLE  GetImage();
	void SetImageFile(tstring  strImage  );
	tstring  GetImageFile();
};

struct __declspec(uuid("6efb8ac6-61ba-4d3f-a599-bad68068fd5b")) IDUITreeItem : IDispatch
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_GetTreeNode(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetTreeNode(OLE_HANDLE pTreeNode  ) = 0;
	virtual HRESULT __stdcall raw_SetHasCheckBox(VARIANT_BOOL bHasCheck  ) = 0;
	virtual HRESULT __stdcall raw_GetModel(struct IDUIControlBase **pResult) = 0;

	//
	//Method Wrapper
	//
	OLE_HANDLE  GetTreeNode();
	void SetTreeNode(OLE_HANDLE  pTreeNode  );
	void SetHasCheckBox(BOOL  bHasCheck  );
	struct IDUIControlBase * GetModel();
};

enum ItemState
{ 
	Disabled = 3,
	Hot = 1,
	Normal = 0,
	Selected = 2 
};

struct __declspec(uuid("ceb77c1b-6883-4c1c-9815-804d363caebd")) _IDUITreeItemEvents : IDispatch
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

struct __declspec(uuid("de28ba00-7cc1-480a-934e-2035303fdd5c")) _IDUITreeToolBarEvents : IDispatch
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

struct __declspec(uuid("4dd5e499-31d7-437b-8e05-96afbc6f3ec4")) _IDUITreeToolItemBaseEvents : IDispatch
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

struct __declspec(uuid("58703b69-ba83-4ce0-8676-57bff7d3cbe0")) _IDUITreeToolButtonEvents : IDispatch
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

struct __declspec(uuid("17d327e6-4fc8-4c59-81f7-88b7b7ca45e9")) IDUITreeToolButton : IDUITreeToolItemBase
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

struct __declspec(uuid("137e3e83-76ca-4829-a398-eda5410a6eba")) _IDUITreeToolCheckEvents : IDispatch
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

struct __declspec(uuid("3b044072-ff13-4aaa-bddb-98cbfaf98e3a")) IDUITreeToolCheck : IDUITreeToolItemBase
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetCheck(VARIANT_BOOL bCheck  ) = 0;
	virtual HRESULT __stdcall raw_GetCheck(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCheckImage(OLE_HANDLE hBmp  ) = 0;
	virtual HRESULT __stdcall raw_GetCheckImage(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCheckImageFile(BSTR strImage  ) = 0;
	virtual HRESULT __stdcall raw_GetCheckImageFile(BSTR *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetCheck(BOOL  bCheck  );
	BOOL  GetCheck();
	void SetCheckImage(OLE_HANDLE  hBmp  );
	OLE_HANDLE  GetCheckImage();
	void SetCheckImageFile(tstring  strImage  );
	tstring  GetCheckImageFile();
};

struct __declspec(uuid("dee5198d-7275-4b6c-89e0-1195a948b9f6")) _IDUITreeToolRadioEvents : IDispatch
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

struct __declspec(uuid("7bbd7549-4606-4729-ba4c-74ef96f5bb9d")) IDUITreeToolRadio : IDUITreeToolItemBase
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetRadio() = 0;
	virtual HRESULT __stdcall raw_GetValue(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCheckImage(OLE_HANDLE hBmp  ) = 0;
	virtual HRESULT __stdcall raw_GetCheckImage(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetCheckImageFile(BSTR strImage  ) = 0;
	virtual HRESULT __stdcall raw_GetCheckImageFile(BSTR *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetRadio();
	BOOL  GetValue();
	void SetCheckImage(OLE_HANDLE  hBmp  );
	OLE_HANDLE  GetCheckImage();
	void SetCheckImageFile(tstring  strImage  );
	tstring  GetCheckImageFile();
};

struct __declspec(uuid("4730a708-998b-42c9-8164-ab0f192adc59")) _IDUITreeToolStaticEvents : IDispatch
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

struct __declspec(uuid("cc43d690-b051-42c0-9316-ff2007cc77f0")) IDUITreeToolStatic : IDUITreeToolItemBase
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

struct __declspec(uuid("e98cf5c2-e5c8-489d-af1b-b8e35e12e79a")) _IDUIOutLookBarEvents : IDispatch
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

struct __declspec(uuid("3c1d27c1-58f7-40c6-84d4-a69cbc2f97b2")) IDUIOutLookBar_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetDrawBackColor(VARIANT_BOOL bDrawColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetDrawBackColor(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBackImage(struct IDUIImageBase *pImageBae, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetBackImage(struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetBackColor(struct IFillColor *pFillColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetBackColor(struct IFillColor **pResult) = 0;
	virtual HRESULT __stdcall raw_SetDrawFolderColor(VARIANT_BOOL bDrawColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetDrawFolderColor(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderBorderSize(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderBorderSize(short nSize, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderHeight(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderHeight(short nHeight, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase *pImageBae, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderBorderColor(enum DUIOUTLOOKBAR_STATE eState, struct IFillColor *pFillColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderBorderColor(enum DUIOUTLOOKBAR_STATE eState, struct IFillColor **pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderBackColor(enum DUIOUTLOOKBAR_STATE eState, struct IFillColor *pFillColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderBackColor(enum DUIOUTLOOKBAR_STATE eState, struct IFillColor **pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderTextStyle(enum DUIOUTLOOKBAR_STATE eState, struct IDUITextStyle *pTextStyle, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderTextStyle(enum DUIOUTLOOKBAR_STATE eState, struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_SetAnimationTickCount(short nCount, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetAnimationTickCount(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderSelected(OLE_HANDLE hFolder, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderSelected(OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_AddFolderBar(BSTR strText, OLE_HANDLE hChild, long exData, VARIANT_BOOL bRedraw, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_AddFolder(BSTR strText, long exData, VARIANT_BOOL bRedraw, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_DelFolderBar(OLE_HANDLE hFolderBar, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderGraphics(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase *pImageBae, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderGraphics(enum DUIOUTLOOKBAR_STATE eState, VARIANT_BOOL bExpand, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetUpDownMode(VARIANT_BOOL bUpDownMode, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_IsUpDownMode(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetGraphicOffset(short nOffsetX, short nOffsetY, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetGraphicOffset(short *pnOffsetX, short *pnOffsetY  ) = 0;
	virtual HRESULT __stdcall raw_SetGraphicsX(short nOffsetX, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetGraphicsX(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetGraphicsY(short nOffsetY, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetGraphicsY(short *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderCount(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderText(OLE_HANDLE hFolder, BSTR bstrText, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderText(OLE_HANDLE hFolder, BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderChild(OLE_HANDLE hFolder, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_GetFolderData(OLE_HANDLE hFolder, long *pResult) = 0;
	virtual HRESULT __stdcall raw_SetFolderChild(OLE_HANDLE hFolder, OLE_HANDLE hChild  ) = 0;
	virtual HRESULT __stdcall raw_SetFolderData(OLE_HANDLE hFolder, long dwData  ) = 0;
	virtual HRESULT __stdcall raw_AddItem(OLE_HANDLE hFolder, BSTR strText, BSTR strImagePath, short nImageCount, VARIANT_BOOL bHorz, long exData, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetDrawItemColor(VARIANT_BOOL bDrawColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetDrawItemColor(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemHeight(short nHeight, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemHeight(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemSpace(short nSpace, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemSpace(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemBackImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase *pImageBase, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemBackImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemBackColor(enum DUIOUTLOOKBAR_STATE eState, struct IFillColor *pFillColor, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemBackColor(enum DUIOUTLOOKBAR_STATE eState, struct IFillColor **pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemTextStyle(enum DUIOUTLOOKBAR_STATE eState, struct IDUITextStyle *pTextStyle, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemTextStyle(enum DUIOUTLOOKBAR_STATE eState, struct IDUITextStyle **pResult) = 0;
	virtual HRESULT __stdcall raw_SetUpArrowImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase *pImageBae, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetUpArrowImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetDownArrowImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase *pImageBae, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetDownArrowImage(enum DUIOUTLOOKBAR_STATE eState, struct IDUIImageBase **pResult) = 0;
	virtual HRESULT __stdcall raw_SetArrowSpace(short nOffsetX, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetArrowSpace(short *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveItem(OLE_HANDLE hFolder, OLE_HANDLE hItem, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemText(OLE_HANDLE hFolder, OLE_HANDLE hItem, BSTR *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemText(OLE_HANDLE hFolder, OLE_HANDLE hItem, BSTR text, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetItemCount(OLE_HANDLE hFolder, short *pResult) = 0;
	virtual HRESULT __stdcall raw_AddItemByText(OLE_HANDLE hFolder, BSTR strText, OLE_HANDLE *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemImage(OLE_HANDLE hFolder, OLE_HANDLE hItem, BSTR imagePath, short nImageCount, VARIANT_BOOL bIsHorz, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_GetBackBorderSize(short *pResult) = 0;
	virtual HRESULT __stdcall raw_SetBackBorderSize(short nSize, VARIANT_BOOL bRedraw, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetItemData(OLE_HANDLE hFolder, OLE_HANDLE hItem, long dwData  ) = 0;
	virtual HRESULT __stdcall raw_GetItemData(OLE_HANDLE hFolder, OLE_HANDLE hItem, long *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveAllItems(OLE_HANDLE hFolder, VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_RemoveAllFolders(VARIANT_BOOL *pResult) = 0;
	virtual HRESULT __stdcall raw_SetSelectedItem(OLE_HANDLE hItem  ) = 0;
	virtual HRESULT __stdcall raw_GetSelectedItem(OLE_HANDLE *phResult  ) = 0;
	virtual HRESULT __stdcall raw_SetSmallIconView(VARIANT_BOOL bSmallIcon  ) = 0;
	virtual HRESULT __stdcall raw_IsSmallIconView(VARIANT_BOOL *pbResult  ) = 0;
	virtual HRESULT __stdcall raw_SetItemIconOffset(short nOffset, VARIANT_BOOL bRedraw  ) = 0;

	//
	//Method Wrapper
	//
	BOOL  SetDrawBackColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawBackColor();
	BOOL  SetBackImage(struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetBackImage();
	BOOL  SetBackColor(struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetBackColor();
	BOOL  SetDrawFolderColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawFolderColor();
	short  GetFolderBorderSize();
	BOOL  SetFolderBorderSize(short  nSize, BOOL  bRedraw  );
	short  GetFolderHeight();
	BOOL  SetFolderHeight(short  nHeight, BOOL  bRedraw  );
	BOOL  SetFolderImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetFolderImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetFolderBorderColor(enum DUIOUTLOOKBAR_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetFolderBorderColor(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetFolderBackColor(enum DUIOUTLOOKBAR_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetFolderBackColor(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetFolderTextStyle(enum DUIOUTLOOKBAR_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetFolderTextStyle(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetAnimationTickCount(short  nCount, BOOL  bRedraw  );
	short  GetAnimationTickCount();
	BOOL  SetFolderSelected(OLE_HANDLE  hFolder, BOOL  bRedraw  );
	OLE_HANDLE  GetFolderSelected();
	OLE_HANDLE  AddFolderBar(tstring  strText, OLE_HANDLE  hChild, long  exData, BOOL  bRedraw  );
	OLE_HANDLE  AddFolder(tstring  strText, long  exData, BOOL  bRedraw  );
	BOOL  DelFolderBar(OLE_HANDLE  hFolderBar, BOOL  bRedraw  );
	BOOL  SetFolderGraphics(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetFolderGraphics(enum DUIOUTLOOKBAR_STATE  eState, BOOL  bExpand  );
	BOOL  SetUpDownMode(BOOL  bUpDownMode, BOOL  bRedraw  );
	BOOL  IsUpDownMode();
	BOOL  SetGraphicOffset(short  nOffsetX, short  nOffsetY, BOOL  bRedraw  );
	void GetGraphicOffset(short * pnOffsetX, short * pnOffsetY  );
	BOOL  SetGraphicsX(short  nOffsetX, BOOL  bRedraw  );
	short  GetGraphicsX();
	BOOL  SetGraphicsY(short  nOffsetY, BOOL  bRedraw  );
	short  GetGraphicsY();
	short  GetFolderCount();
	BOOL  SetFolderText(OLE_HANDLE  hFolder, tstring  bstrText  );
	tstring  GetFolderText(OLE_HANDLE  hFolder  );
	OLE_HANDLE  GetFolderChild(OLE_HANDLE  hFolder  );
	long  GetFolderData(OLE_HANDLE  hFolder  );
	void SetFolderChild(OLE_HANDLE  hFolder, OLE_HANDLE  hChild  );
	void SetFolderData(OLE_HANDLE  hFolder, long  dwData  );
	OLE_HANDLE  AddItem(OLE_HANDLE  hFolder, tstring  strText, tstring  strImagePath, short  nImageCount, BOOL  bHorz, long  exData  );
	BOOL  SetDrawItemColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawItemColor();
	BOOL  SetItemHeight(short  nHeight, BOOL  bRedraw  );
	short  GetItemHeight();
	BOOL  SetItemSpace(short  nSpace, BOOL  bRedraw  );
	short  GetItemSpace();
	BOOL  SetItemBackImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetItemBackImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetItemBackColor(enum DUIOUTLOOKBAR_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetItemBackColor(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetItemTextStyle(enum DUIOUTLOOKBAR_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetItemTextStyle(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetUpArrowImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetUpArrowImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetDownArrowImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetDownArrowImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetArrowSpace(short  nOffsetX, BOOL  bRedraw  );
	short  GetArrowSpace();
	BOOL  RemoveItem(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, BOOL  bRedraw  );
	tstring  GetItemText(OLE_HANDLE  hFolder, OLE_HANDLE  hItem  );
	BOOL  SetItemText(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, tstring  text  );
	short  GetItemCount(OLE_HANDLE  hFolder  );
	OLE_HANDLE  AddItemByText(OLE_HANDLE  hFolder, tstring  strText  );
	BOOL  SetItemImage(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, tstring  imagePath, short  nImageCount, BOOL  bIsHorz  );
	short  GetBackBorderSize();
	BOOL  SetBackBorderSize(short  nSize, BOOL  bRedraw  );
	void SetItemData(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, long  dwData  );
	long  GetItemData(OLE_HANDLE  hFolder, OLE_HANDLE  hItem  );
	BOOL  RemoveAllItems(OLE_HANDLE  hFolder  );
	BOOL  RemoveAllFolders();
	void SetSelectedItem(OLE_HANDLE  hItem  );
	void GetSelectedItem(OLE_HANDLE * phResult  );
	void SetSmallIconView(BOOL  bSmallIcon  );
	void IsSmallIconView(VARIANT_BOOL * pbResult  );
	void SetItemIconOffset(short  nOffset, BOOL  bRedraw  );
};

struct IDUIOutLookBar : IDUIControlBase
{

	//
	//Method Wrapper
	//
	BOOL  SetDrawBackColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawBackColor();
	BOOL  SetBackImage(struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetBackImage();
	BOOL  SetBackColor(struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetBackColor();
	BOOL  SetDrawFolderColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawFolderColor();
	short  GetFolderBorderSize();
	BOOL  SetFolderBorderSize(short  nSize, BOOL  bRedraw  );
	short  GetFolderHeight();
	BOOL  SetFolderHeight(short  nHeight, BOOL  bRedraw  );
	BOOL  SetFolderImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetFolderImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetFolderBorderColor(enum DUIOUTLOOKBAR_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetFolderBorderColor(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetFolderBackColor(enum DUIOUTLOOKBAR_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetFolderBackColor(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetFolderTextStyle(enum DUIOUTLOOKBAR_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetFolderTextStyle(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetAnimationTickCount(short  nCount, BOOL  bRedraw  );
	short  GetAnimationTickCount();
	BOOL  SetFolderSelected(OLE_HANDLE  hFolder, BOOL  bRedraw  );
	OLE_HANDLE  GetFolderSelected();
	OLE_HANDLE  AddFolderBar(tstring  strText, OLE_HANDLE  hChild, long  exData, BOOL  bRedraw  );
	OLE_HANDLE  AddFolder(tstring  strText, long  exData, BOOL  bRedraw  );
	BOOL  DelFolderBar(OLE_HANDLE  hFolderBar, BOOL  bRedraw  );
	BOOL  SetFolderGraphics(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetFolderGraphics(enum DUIOUTLOOKBAR_STATE  eState, BOOL  bExpand  );
	BOOL  SetUpDownMode(BOOL  bUpDownMode, BOOL  bRedraw  );
	BOOL  IsUpDownMode();
	BOOL  SetGraphicOffset(short  nOffsetX, short  nOffsetY, BOOL  bRedraw  );
	void GetGraphicOffset(short * pnOffsetX, short * pnOffsetY  );
	BOOL  SetGraphicsX(short  nOffsetX, BOOL  bRedraw  );
	short  GetGraphicsX();
	BOOL  SetGraphicsY(short  nOffsetY, BOOL  bRedraw  );
	short  GetGraphicsY();
	short  GetFolderCount();
	BOOL  SetFolderText(OLE_HANDLE  hFolder, tstring  bstrText  );
	tstring  GetFolderText(OLE_HANDLE  hFolder  );
	OLE_HANDLE  GetFolderChild(OLE_HANDLE  hFolder  );
	long  GetFolderData(OLE_HANDLE  hFolder  );
	void SetFolderChild(OLE_HANDLE  hFolder, OLE_HANDLE  hChild  );
	void SetFolderData(OLE_HANDLE  hFolder, long  dwData  );
	OLE_HANDLE  AddItem(OLE_HANDLE  hFolder, tstring  strText, tstring  strImagePath, short  nImageCount, BOOL  bHorz, long  exData  );
	BOOL  SetDrawItemColor(BOOL  bDrawColor, BOOL  bRedraw  );
	BOOL  GetDrawItemColor();
	BOOL  SetItemHeight(short  nHeight, BOOL  bRedraw  );
	short  GetItemHeight();
	BOOL  SetItemSpace(short  nSpace, BOOL  bRedraw  );
	short  GetItemSpace();
	BOOL  SetItemBackImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBase, BOOL  bRedraw  );
	struct IDUIImageBase * GetItemBackImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetItemBackColor(enum DUIOUTLOOKBAR_STATE  eState, struct IFillColor * pFillColor, BOOL  bRedraw  );
	struct IFillColor * GetItemBackColor(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetItemTextStyle(enum DUIOUTLOOKBAR_STATE  eState, struct IDUITextStyle * pTextStyle, BOOL  bRedraw  );
	struct IDUITextStyle * GetItemTextStyle(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetUpArrowImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetUpArrowImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetDownArrowImage(enum DUIOUTLOOKBAR_STATE  eState, struct IDUIImageBase * pImageBae, BOOL  bRedraw  );
	struct IDUIImageBase * GetDownArrowImage(enum DUIOUTLOOKBAR_STATE  eState  );
	BOOL  SetArrowSpace(short  nOffsetX, BOOL  bRedraw  );
	short  GetArrowSpace();
	BOOL  RemoveItem(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, BOOL  bRedraw  );
	tstring  GetItemText(OLE_HANDLE  hFolder, OLE_HANDLE  hItem  );
	BOOL  SetItemText(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, tstring  text  );
	short  GetItemCount(OLE_HANDLE  hFolder  );
	OLE_HANDLE  AddItemByText(OLE_HANDLE  hFolder, tstring  strText  );
	BOOL  SetItemImage(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, tstring  imagePath, short  nImageCount, BOOL  bIsHorz  );
	short  GetBackBorderSize();
	BOOL  SetBackBorderSize(short  nSize, BOOL  bRedraw  );
	void SetItemData(OLE_HANDLE  hFolder, OLE_HANDLE  hItem, long  dwData  );
	long  GetItemData(OLE_HANDLE  hFolder, OLE_HANDLE  hItem  );
	BOOL  RemoveAllItems(OLE_HANDLE  hFolder  );
	BOOL  RemoveAllFolders();
	void SetSelectedItem(OLE_HANDLE  hItem  );
	void GetSelectedItem(OLE_HANDLE * phResult  );
	void SetSmallIconView(BOOL  bSmallIcon  );
	void IsSmallIconView(VARIANT_BOOL * pbResult  );
	void SetItemIconOffset(short  nOffset, BOOL  bRedraw  );
};

enum DUIOUTLOOKBAR_STATE
{ 
	DUIOUTLOOKBAR_STATE_DISABLED = 3,
	DUIOUTLOOKBAR_STATE_HOT = 1,
	DUIOUTLOOKBAR_STATE_LAST = 4,
	DUIOUTLOOKBAR_STATE_NORMAL = 0,
	DUIOUTLOOKBAR_STATE_SELECTED = 2 
};

struct __declspec(uuid("7b8f207d-ea8a-444b-b9e4-65d4dbe308ee")) _IDUIWebKitEvents : IDispatch
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

struct __declspec(uuid("e4f56d1e-7e6e-4b19-b3a2-93a1ca1183ee")) IDUIWebKit_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetURL(BSTR strText  ) = 0;

	//
	//Method Wrapper
	//
	void SetURL(tstring  strText  );
};

struct IDUIWebKit : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetURL(tstring  strText  );
};

struct __declspec(uuid("2e46ce40-82ba-4550-b459-aa40da69e80d")) _ICDuiPickerEvents : IDispatch
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

struct __declspec(uuid("d9e2b401-e937-40e7-82be-1656a01b3b25")) ICDuiPicker_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_SetEditBorder(struct SkinRect *rcEditBorder  ) = 0;
	virtual HRESULT __stdcall raw_StartTimer() = 0;
	virtual HRESULT __stdcall raw_StopTimer() = 0;
	virtual HRESULT __stdcall raw_SetPickerBackImage(struct IDUIImageBase *pImagePickerBack  ) = 0;
	virtual HRESULT __stdcall raw_SetHour(int nHour  ) = 0;
	virtual HRESULT __stdcall raw_GetHour(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMin(int nMin  ) = 0;
	virtual HRESULT __stdcall raw_GetMin(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetSec(int nSec  ) = 0;
	virtual HRESULT __stdcall raw_GetSec(int *pResult) = 0;
	virtual HRESULT __stdcall raw_IsShowYMD(VARIANT_BOOL bShowYMD  ) = 0;
	virtual HRESULT __stdcall raw_IsShowSec(VARIANT_BOOL bShowSec  ) = 0;
	virtual HRESULT __stdcall raw_IsShowHMS(VARIANT_BOOL bShowHMS  ) = 0;
	virtual HRESULT __stdcall raw_SetYear(int nYear  ) = 0;
	virtual HRESULT __stdcall raw_GetYear(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetMonth(int nMonth  ) = 0;
	virtual HRESULT __stdcall raw_GetMonth(int *pResult) = 0;
	virtual HRESULT __stdcall raw_SetDay(int nDay  ) = 0;
	virtual HRESULT __stdcall raw_GetDay(int *pResult) = 0;

	//
	//Method Wrapper
	//
	void SetEditBorder(struct SkinRect * rcEditBorder  );
	void StartTimer();
	void StopTimer();
	void SetPickerBackImage(struct IDUIImageBase * pImagePickerBack  );
	void SetHour(int  nHour  );
	int  GetHour();
	void SetMin(int  nMin  );
	int  GetMin();
	void SetSec(int  nSec  );
	int  GetSec();
	void IsShowYMD(BOOL  bShowYMD  );
	void IsShowSec(BOOL  bShowSec  );
	void IsShowHMS(BOOL  bShowHMS  );
	void SetYear(int  nYear  );
	int  GetYear();
	void SetMonth(int  nMonth  );
	int  GetMonth();
	void SetDay(int  nDay  );
	int  GetDay();
};

struct ICDuiPicker : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void SetEditBorder(struct SkinRect * rcEditBorder  );
	void StartTimer();
	void StopTimer();
	void SetPickerBackImage(struct IDUIImageBase * pImagePickerBack  );
	void SetHour(int  nHour  );
	int  GetHour();
	void SetMin(int  nMin  );
	int  GetMin();
	void SetSec(int  nSec  );
	int  GetSec();
	void IsShowYMD(BOOL  bShowYMD  );
	void IsShowSec(BOOL  bShowSec  );
	void IsShowHMS(BOOL  bShowHMS  );
	void SetYear(int  nYear  );
	int  GetYear();
	void SetMonth(int  nMonth  );
	int  GetMonth();
	void SetDay(int  nDay  );
	int  GetDay();
};

struct __declspec(uuid("ed203efa-78df-4f3e-a3e4-45196240d7dc")) _IDUI3DRotateMenuEvents : IDispatch
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

struct __declspec(uuid("82766421-d32c-4599-a54b-bfbb3d999c8c")) IDUI3DRotateMenu_ : IDUIControlBase_
{
	//
	//Property
	//


	//
	//Method
	//
	virtual HRESULT __stdcall raw_StartAnimate(VARIANT_BOOL bStart  ) = 0;
	virtual HRESULT __stdcall raw_ShowDXHwnd(VARIANT_BOOL bShow  ) = 0;
	virtual HRESULT __stdcall raw_RotateStarPic() = 0;
	virtual HRESULT __stdcall raw_SetMode(enum DUI_ROTATEMENU_TYPE eType  ) = 0;
	virtual HRESULT __stdcall raw_SetBackImageBase(struct IDUIImageBase *pImageBase  ) = 0;
	virtual HRESULT __stdcall raw_SetImagePath(BSTR bstrPath  ) = 0;

	//
	//Method Wrapper
	//
	void StartAnimate(BOOL  bStart  );
	void ShowDXHwnd(BOOL  bShow  );
	void RotateStarPic();
	void SetMode(enum DUI_ROTATEMENU_TYPE  eType  );
	void SetBackImageBase(struct IDUIImageBase * pImageBase  );
	void SetImagePath(tstring  bstrPath  );
};

struct IDUI3DRotateMenu : IDUIControlBase
{

	//
	//Method Wrapper
	//
	void StartAnimate(BOOL  bStart  );
	void ShowDXHwnd(BOOL  bShow  );
	void RotateStarPic();
	void SetMode(enum DUI_ROTATEMENU_TYPE  eType  );
	void SetBackImageBase(struct IDUIImageBase * pImageBase  );
	void SetImagePath(tstring  bstrPath  );
};

enum DUI_ROTATEMENU_TYPE
{ 
	DUI_RT_3DMENU = 0,
	DUI_RT_ANIMATE = 1,
	DUI_RT_PIC = 2,
	DUI_RT_TEXT = 3 
};

struct __declspec(uuid("0f726133-8242-4508-995b-878607296f25")) _IDUI3DMenuEvents : IDispatch
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

struct __declspec(uuid("9c9442d3-b45a-4756-9d60-7c322300b441")) IDUI3DMenu_ : IDUIControlBase_
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

struct IDUI3DMenu : IDUIControlBase
{

	//
	//Method Wrapper
	//
};


#include "OfficeAll.tli"
#endif //__HEAD__OFFICEALL__