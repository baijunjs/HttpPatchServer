
// HttpPatchServerDlg.h : 头文件
//

#pragma once

#include "PatchBus.h"
#include "PatchView.h"
#include "PatchViewSetting.h"


// CHttpPatchServerDlg 对话框
class CHttpPatchServerDlg : public CDUIDialog
{
// 构造
public:
	CHttpPatchServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPPATCHSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//bool InitDui();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	CPatchView				m_patchview;		//下载中心
	CPatchViewSetting		m_patchsetting;		//设置中心


public:
	virtual void OnOK();
	virtual void OnCancel();
	LRESULT OnTrayIcon(WPARAM, LPARAM);
};
