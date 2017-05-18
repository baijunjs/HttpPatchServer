#pragma once

#include "PatchNetSetting.h"
#include "PatchCascade.h"


// CPatchMode 对话框

class CPatchMode : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchMode)

public:
	CPatchMode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchMode();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL InitSknPath();

	CPatchNetSetting		m_patchNetSetting;
	CPatchCascade			m_patchCascade;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void InitControlData();
	BOOL OnApply();
	void OnRestore();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	LRESULT OnRadioChange(WPARAM, LPARAM);
	void SetPatchView(CWnd*);
	CWnd* GetPatchView();
	CWnd* m_pPatchView;
	void InitControlLang();
};
