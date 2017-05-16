#pragma once

#include "PatchNetSetting.h"
#include "PatchSetting.h"
#include "PatchCascade.h"
#include "PatchMode.h"
#include "PatchOther.h"

// CPatchViewSetting �Ի���

class CPatchViewSetting : public CDUIDialog
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
	//bool InitDui();
	BOOL InitSknPath();


	//ISkinObjResBase			*m_pDuiSetting;
	//IDUITabCtrl				*m_pTabSetting;
	//IDUIHwndObj				*m_pHwndOwner;
	//ICmdButton				*m_pBtnApply;
	//ICmdButton				*m_pBtnCancel;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	LRESULT OnTabPageChanged(WPARAM, LPARAM);
	LRESULT OnSMLButtonUp(WPARAM wparam, LPARAM lparam);
	void SaveSetting();
	void RestoreSetitng();
	void SetPatchView(CWnd*);
	CWnd* GetPatchView();
	CPatchMode				m_patchMode;
	CPatchOther				m_patchOtherSetting;
	CWnd*					m_pPatchView;
	afx_msg void OnClose();
};
