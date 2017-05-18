#pragma once

#include "PatchNetSetting.h"
#include "PatchCascade.h"


// CPatchMode �Ի���

class CPatchMode : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchMode)

public:
	CPatchMode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchMode();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
