// PatchViewSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewSetting.h"
#include "afxdialogex.h"


// CPatchViewSetting 对话框

IMPLEMENT_DYNAMIC(CPatchViewSetting, CDUIDialog)

CPatchViewSetting::CPatchViewSetting(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_SETTING, pParent)
{

}

CPatchViewSetting::~CPatchViewSetting()
{
}

void CPatchViewSetting::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchViewSetting, CDUIDialog)
	ON_WM_CREATE()
	ON_MESSAGE(DUI_TABMSG_SELCHANGED, &CPatchViewSetting::OnTabPageChanged)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPatchViewSetting 消息处理程序


BOOL CPatchViewSetting::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUICfigView");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


int CPatchViewSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_patchMode.Create(IDD_DIALOG_MODE, this);
	m_patchOtherSetting.Create(IDD_DIALOG_OTHER, this);
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	return 0;
}


BOOL CPatchViewSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitControlLang();
	DHwnd(HwndSubObj)->Attach(HandleToLong(m_patchMode.GetSafeHwnd()));
	DHwnd(HwndSubObj)->Attach(HandleToLong(m_patchOtherSetting.GetSafeHwnd()));
	m_patchMode.ShowWindow(SW_SHOWNORMAL);
	return TRUE;  // return TRUE unless you set the focus to a control
}


LRESULT CPatchViewSetting::OnTabPageChanged(WPARAM wparam, LPARAM lparam)
{
	if (0 == wparam)
	{
		m_patchMode.ShowWindow(SW_SHOWNORMAL);
		m_patchOtherSetting.ShowWindow(SW_HIDE);
	}

	else if (1 == wparam)
	{
		m_patchMode.ShowWindow(SW_HIDE);
		m_patchOtherSetting.ShowWindow(SW_SHOWNORMAL);
	}

	return 0;
}

LRESULT CPatchViewSetting::OnSMLButtonUp(WPARAM wparam, LPARAM lparam)
{
	if (DBtn(BtnApply) == (ICmdButton*)wparam)
	{
		SaveSetting();
	}
	else if (DBtn(BtnCancel) == (ICmdButton*)wparam)
	{
		RestoreSetitng();
	}

	return 0;
}


void CPatchViewSetting::SaveSetting()
{
	m_patchMode.OnApply();
	m_patchOtherSetting.OnApply();
}

void CPatchViewSetting::RestoreSetitng()
{
	m_patchMode.OnRestore();
	m_patchOtherSetting.OnRestore();
}

void CPatchViewSetting::SetPatchView(CWnd* pView)
{
	m_pPatchView = pView;
	m_patchMode.SetPatchView(pView);
}

CWnd* CPatchViewSetting::GetPatchView()
{
	return m_pPatchView;
}

void CPatchViewSetting::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDUIDialog::OnClose();
}


void CPatchViewSetting::InitControlLang()
{
	DStatic(StaticTitle)->SetText(g_lang.GetText(10005));
	IDUITabCtrlItem *pItem1 = DTab(SettingTabCtrl)->GetItemByIndex(0);
	IDUITabCtrlItem *pItem2 = DTab(SettingTabCtrl)->GetItemByIndex(1);
	pItem1->SetText(g_lang.GetText(10006));
	pItem2->SetText(g_lang.GetText(10007));
	DBtn(BtnApply)->SetText(g_lang.GetText(10035));
	DBtn(BtnCancel)->SetText(g_lang.GetText(10036));
}