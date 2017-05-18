// PatchMode.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchMode.h"
#include "afxdialogex.h"


// CPatchMode 对话框

IMPLEMENT_DYNAMIC(CPatchMode, CDUIDialog)

CPatchMode::CPatchMode(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_MODE, pParent),
	m_patchNetSetting(this),
	m_patchCascade(this)
{

}

CPatchMode::~CPatchMode()
{
}

void CPatchMode::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchMode, CDUIDialog)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(DUISM_RADIOCHANGE, &CPatchMode::OnRadioChange)
END_MESSAGE_MAP()


// CPatchMode 消息处理程序

BOOL CPatchMode::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIMode");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}

int CPatchMode::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_patchNetSetting.Create(IDD_DIALOG_DOWNSETTING, this);
	m_patchCascade.Create(IDD_DIALOG_CASCADE, this);
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	// TODO:  在此添加您专用的创建代码
	return 0;
}


BOOL CPatchMode::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam)
		{
			return TRUE;
		}
	}
	return CDUIDialog::PreTranslateMessage(pMsg);
}


BOOL CPatchMode::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	DHwnd(HwndObj18)->Attach(HandleToLong(m_patchNetSetting.GetSafeHwnd()));
	DHwnd(HwndObj18)->Attach(HandleToLong(m_patchCascade.GetSafeHwnd()));

	InitControlLang();
	InitControlData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPatchMode::InitControlData()
{
	switch (appconfig.m_mode_cfg.mode)
	{
	case http_mode:
		DRadio(RadioBox_Http)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		m_patchNetSetting.ShowWindow(SW_SHOWNORMAL);
		break;
	case cascade_mode:
		m_patchCascade.ShowWindow(SW_SHOWNORMAL);
		DRadio(RadioBox_Cascade)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		break;
	}
}



BOOL CPatchMode::OnApply()
{
	IDUIRadioGroup *pGroup = DRadio(RadioBox_Http)->GetGroup();
	IDUIControlBase	*pCtrl = pGroup->GetRadio();

	switchmode mode;
	if (DRadio(RadioBox_Http) == pCtrl)
	{
		mode = http_mode;
		m_patchNetSetting.OnApply();
	}
	else if (DRadio(RadioBox_Cascade) == pCtrl)
	{
		mode = cascade_mode;
		m_patchCascade.OnApply();
	}
	appconfig.m_mode_cfg.mode = mode;
	std::tstring &szconfig = appconfig.m_szConfigFile;
	WritePrivateProfileString(_T("SWITCHMODE"), _T("MODE"), mode == http_mode ? _T("0") : _T("1"), szconfig.c_str());
	return TRUE;
}

void CPatchMode::OnRestore()
{
	InitControlData();
	m_patchNetSetting.OnRestore();
	m_patchCascade.OnRestore();
}

void CPatchMode::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDUIDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码

}


LRESULT CPatchMode::OnRadioChange(WPARAM wparam, LPARAM lparam)
{
	if (DRadio(RadioBox_Http) == (IRadioBox*)lparam)
	{
		m_patchNetSetting.ShowWindow(SW_SHOWNORMAL);
		m_patchCascade.ShowWindow(SW_HIDE);
	}
	else if (DRadio(RadioBox_Cascade) == (IRadioBox*)lparam)
	{
		m_patchCascade.ShowWindow(SW_HIDE);
		m_patchCascade.ShowWindow(SW_SHOWNORMAL);
	}

	return 0;
}

void CPatchMode::SetPatchView(CWnd* pView)
{
	m_pPatchView = pView;
}

CWnd* CPatchMode::GetPatchView()
{
	return m_pPatchView;
}

void CPatchMode::InitControlLang()
{
	DStatic(StaticMode)->SetText(g_lang.GetText(10006));
	DRadio(RadioBox_Http)->SetText(g_lang.GetText(10008), TRUE);
	DRadio(RadioBox_Cascade)->SetText(g_lang.GetText(10009), TRUE);
}