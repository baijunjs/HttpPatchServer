// PatchOther.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchOther.h"
#include "afxdialogex.h"
#include <sstream>

// CPatchOther 对话框

IMPLEMENT_DYNAMIC(CPatchOther, CDUIDialog)

CPatchOther::CPatchOther(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_OTHER, pParent)
{

}

CPatchOther::~CPatchOther()
{
}

void CPatchOther::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchOther, CDUIDialog)
	ON_WM_CREATE()
	ON_MESSAGE(DUISM_VALUECHANGED, &CPatchOther::OnCheckBoxChanged)
END_MESSAGE_MAP()


// CPatchOther 消息处理程序

int CPatchOther::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


BOOL CPatchOther::PreTranslateMessage(MSG* pMsg)
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


BOOL CPatchOther::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitControlLang();
	InitControlData();
	EnableControl();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPatchOther::InitControlData()
{
	DCheck(ChkBox-Debug)->SetValue(appconfig.m_other_cfg.enable ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);
	DCombo(LogLevel)->SetCurSel(appconfig.m_other_cfg.level);
	DCombo(Launages)->SetCurSel(appconfig.m_other_cfg.lang);
}


void CPatchOther::EnableControl()
{
	if (DUICHECKBOX_CHECKED == DCheck(ChkBox-Debug)->GetValue())
	{
		DCombo(LogLevel)->EnableObject(TRUE, TRUE);
	}
	else if (DUICHECKBOX_UNCHECKED == DCheck(ChkBox-Debug)->GetValue())
	{
		DCombo(LogLevel)->EnableObject(FALSE, TRUE);
	}
}


BOOL CPatchOther::OnApply()
{
	appconfig.m_other_cfg.enable = DCheck(ChkBox-Debug)->GetValue() == DUICHECKBOX_CHECKED ? true : false;
	appconfig.m_other_cfg.level = DCombo(LogLevel)->GetCurSel();
	std::tstring &szconfig = appconfig.m_szConfigFile;
	std::tstring  szlan = DCombo(Launages)->GetCurSel() == 0 ? _T("ZHCN") : _T("EN");
	appconfig.m_other_cfg.lang = (LANS)DCombo(Launages)->GetCurSel();
	std::tstringstream ss;
	std::tstring szlevel;
	ss << appconfig.m_other_cfg.level;
	ss >> szlevel;
	WritePrivateProfileString(_T("DEBUG"), _T("LOG"), appconfig.m_other_cfg.enable ? _T("1"):_T("0"), szconfig.c_str());
	WritePrivateProfileString(_T("DEBUG"), _T("LEVEL"), szlevel.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("LANGUAGE"), _T("DEFAULT"), szlan.c_str(), szconfig.c_str());

	if (appconfig.m_other_cfg.enable)
	{
		if (!vrvlog::log::get().get_log())
			vrvlog::log::get().init((const char*)_bstr_t(appconfig.m_szLogPath.c_str()));

		if (vrvlog::log::get().get_log())
		{
			vrvlog::log::get().get_log()->flush_on((spdlog::level::level_enum)appconfig.m_other_cfg.level);
			vrvlog::log::get().get_log()->set_level((spdlog::level::level_enum)appconfig.m_other_cfg.level);
		}
	}
	else
	{
		if (vrvlog::log::get().get_log())
		{
			vrvlog::log::get().get_log()->flush_on(spdlog::level::off);
			vrvlog::log::get().get_log()->set_level(spdlog::level::off);
		}
	}

	return TRUE;
}


void CPatchOther::OnRestore()
{
	InitControlData();
}


LRESULT CPatchOther::OnCheckBoxChanged(WPARAM wparam, LPARAM lparam)
{
	if (DCheck(ChkBox-Debug) == (IDUICheckBox*)lparam)
	{
		if (DUICHECKBOX_CHECKED == (DUICHECKBOX_VALUE)wparam)
		{
			DCombo(LogLevel)->EnableObject(TRUE, TRUE);
		}
		else if (DUICHECKBOX_UNCHECKED == (DUICHECKBOX_VALUE)wparam)
		{
			DCombo(LogLevel)->EnableObject(FALSE, TRUE);
		}
	}
	return 0;
}


BOOL CPatchOther::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIOther");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


void CPatchOther::InitControlLang()
{
	DStatic(StaticTitle)->SetText(g_lang.GetText(10007));
	DCheck(ChkBox-Debug)->SetText(g_lang.GetText(10037));
	DStatic(StaticLevel)->SetText(g_lang.GetText(10038));
	DCombo(LogLevel)->SetItemText(0, g_lang.GetText(10039));
	DCombo(LogLevel)->SetItemText(1, g_lang.GetText(10040));
	DCombo(LogLevel)->SetItemText(2, g_lang.GetText(10041));
	DCombo(LogLevel)->SetItemText(3, g_lang.GetText(10042));
	DCombo(LogLevel)->SetItemText(4, g_lang.GetText(10043));
	DCombo(LogLevel)->SetItemText(5, g_lang.GetText(10044));
	DCombo(LogLevel)->SetItemText(6, g_lang.GetText(10045));
	DStatic(Static-Lans)->SetText(g_lang.GetText(10046));
	DCombo(Launages)->SetItemText(0, g_lang.GetText(10047));
	DCombo(Launages)->SetItemText(1, g_lang.GetText(10048));
}