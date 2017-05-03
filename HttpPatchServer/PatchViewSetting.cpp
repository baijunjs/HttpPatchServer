// PatchViewSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewSetting.h"
#include "afxdialogex.h"


// CPatchViewSetting 对话框

IMPLEMENT_DYNAMIC(CPatchViewSetting, CDialogEx)

CPatchViewSetting::CPatchViewSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CPatchViewSetting::~CPatchViewSetting()
{
}

void CPatchViewSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchViewSetting, CDialogEx)
	ON_WM_CREATE()
	ON_MESSAGE(DUI_TABMSG_SELCHANGED, &CPatchViewSetting::OnTabPageChanged)
END_MESSAGE_MAP()


// CPatchViewSetting 消息处理程序


bool CPatchViewSetting::InitDui()
{
	m_pDuiSetting = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUICfigView", HandleToLong(m_hWnd));
	ASSERT(m_pDuiSetting);

	m_pTabSetting = (IDUITabCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "SettingTabCtrl", m_pDuiSetting, TRUE);
	ASSERT(m_pTabSetting);

	m_pHwndOwner = (IDUIHwndObj*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "HwndSubObj", m_pDuiSetting, TRUE);
	ASSERT(m_pHwndOwner);

	return true;
}

int CPatchViewSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!InitDui())
		return -1;

	return 0;
}


BOOL CPatchViewSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_patchNetSetting.Create(IDD_DIALOG_DOWNSETTING, this);
	m_pHwndOwner->Attach(HandleToLong(m_patchNetSetting.GetSafeHwnd()));

	m_patchSetting.Create(IDD_DIALOG_PATCHSETTING, this);
	m_pHwndOwner->Attach(HandleToLong(m_patchSetting.GetSafeHwnd()));

	m_patchCascade.Create(IDD_DIALOG_CASCADE, this);
	m_pHwndOwner->Attach(HandleToLong(m_patchCascade.GetSafeHwnd()));

	m_patchSetting.ShowWindow(SW_SHOWNORMAL);
	return TRUE;  // return TRUE unless you set the focus to a control
}


LRESULT CPatchViewSetting::OnTabPageChanged(WPARAM wparam, LPARAM lparam)
{
	if (0 == wparam)
	{
		m_patchSetting.ShowWindow(SW_SHOWNORMAL);
		m_patchNetSetting.ShowWindow(SW_HIDE);
		m_patchCascade.ShowWindow(SW_HIDE);
	}

	else if (1 == wparam)
	{
		m_patchSetting.ShowWindow(SW_HIDE);
		m_patchNetSetting.ShowWindow(SW_SHOWNORMAL);
		m_patchCascade.ShowWindow(SW_HIDE);
	}
	else if (2 == wparam)
	{
		m_patchSetting.ShowWindow(SW_HIDE);
		m_patchNetSetting.ShowWindow(SW_HIDE);
		m_patchCascade.ShowWindow(SW_SHOWNORMAL);
	}

	return 0;
}