#pragma once

#include "PatchNetSetting.h"
#include "PatchSetting.h"
#include "PatchCascade.h"

// CPatchViewSetting 对话框

class CPatchViewSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchViewSetting)

public:
	CPatchViewSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchViewSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	bool InitDui();


	ISkinObjResBase			*m_pDuiSetting;
	IDUITabCtrl				*m_pTabSetting;
	IDUIHwndObj				*m_pHwndOwner;
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	LRESULT OnTabPageChanged(WPARAM, LPARAM);

	CPatchNetSetting		m_patchNetSetting;
	CPatchSetting			m_patchSetting;
	CPatchCascade			m_patchCascade;
};
