#pragma once

#include "PatchNetSetting.h"
#include "PatchSetting.h"
#include "PatchCascade.h"

// CPatchViewSetting �Ի���

class CPatchViewSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchViewSetting)

public:
	CPatchViewSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchViewSetting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
