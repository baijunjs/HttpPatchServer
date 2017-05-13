#pragma once
#include "PatchBus.h"


// CPatchSetting 对话框

class CPatchSetting : public CDialogEx
{

	enum tree
	{
		producttree,
		languagetree
	};
	DECLARE_DYNAMIC(CPatchSetting)

public:
	CPatchSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PATCHSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	bool InitDui();


	ISkinObjResBase			*m_pDuiPatchSetting;
	IDUIEditCtrl			*m_pEditUrl;
	IDUIEditCtrl			*m_pEditPath;
	ICmdButton				*m_pCmdBtnTest;
	ICmdButton				*m_pCmdBtnBrowser;
	IDUISimpleTree			*m_pProductsTree;
	IDUISimpleTree			*m_pLansTree;
	IDUIStatic				*m_pWarnStatic;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	void RedrawSimpleTree();
	LRESULT OnButtonDispatcher(WPARAM wparam, LPARAM lparam);
	LRESULT OnTreeCheckItem(WPARAM wparam, LPARAM lparam);
	LRESULT OnButtonTest(WPARAM wparam, LPARAM lparam);
	LRESULT OnButtonBrowser(WPARAM wparam, LPARAM lparam);
	void RedrawTreeImpl(tree whichtree);
	void CheckChildItem(IDUISimpleTree *tree, OLE_HANDLE hParent);
	void OnApply();
	std::string GetCheckedItemString(IDUISimpleTree* pTree);
	void OnRestore();
	void RestoreTreeCheckItems(tree);
	void TravelTree(IDUISimpleTree* pTree, OLE_HANDLE hParent, std::string& szChecked);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
