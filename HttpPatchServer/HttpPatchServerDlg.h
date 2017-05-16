
// HttpPatchServerDlg.h : ͷ�ļ�
//

#pragma once

#include "PatchBus.h"
#include "PatchView.h"
#include "PatchViewSetting.h"


// CHttpPatchServerDlg �Ի���
class CHttpPatchServerDlg : public CDUIDialog
{
// ����
public:
	CHttpPatchServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPPATCHSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//bool InitDui();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnTabPageChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnAddIconToTaskbar(WPARAM wParam, LPARAM lParam);
	void AddTaskbarIcons();
	BOOL InitSknPath();
public:
	vrv::patch::CPatchBus  m_patchbus;


protected:
	LRESULT OnButtonUp(WPARAM, LPARAM);

private:
	NOTIFYICONDATA			m_NotifyIconData;
	//ICmdButton*				m_pDUIBtnClose;
	//ICmdButton*				m_pDUIBtnMini;
	//IDUICheckBox *			m_pDUIchkMax;

	//IDUITabCtrl *			m_pTabMain;
	//IDUIHwndObj *			m_pHwndSubWnd;

	//IDUILogoObj*			m_pDUILogo;
	CPatchView				m_patchview;		//��������
	CPatchViewSetting		m_patchsetting;		//��������


public:
	virtual void OnOK();
	virtual void OnCancel();
	LRESULT OnTrayIcon(WPARAM, LPARAM);
};
