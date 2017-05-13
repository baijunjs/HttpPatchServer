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

//bool CPatchOther::InitDui()
//{
//	m_pDuiOther = (ISkinObjResBase *)AfxGetDuiRes()->CreateDirectUI("DUIOther", HandleToLong(m_hWnd));
//	ASSERT(m_pDuiOther);
//
//	m_pChkLog = (IDUICheckBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ChkBox-Debug", m_pDuiOther, TRUE);
//	ASSERT(m_pChkLog);
//
//	m_pLogLevel = (IDUIComboBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "LogLevel", m_pDuiOther, TRUE);
//	ASSERT(m_pLogLevel);
//
//	m_pLansLabel = (IDUIStatic*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "Static-Lans", m_pDuiOther, TRUE);
//	ASSERT(m_pLansLabel);
//
//	m_pComboLans = (IDUIComboBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "Launages", m_pDuiOther, TRUE);
//	ASSERT(m_pComboLans);
//
//	return true;
//}

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
	std::string &szconfig = appconfig.m_szConfigFile;
	std::string  szlan = DCombo(Launages)->GetCurSel() == 0 ? "ZHCN" : "EN";
	appconfig.m_other_cfg.lang = (LANS)DCombo(Launages)->GetCurSel();
	std::stringstream ss;
	std::string szlevel;
	ss << appconfig.m_other_cfg.level;
	ss >> szlevel;
	WritePrivateProfileStringA("DEBUG", "LOG", appconfig.m_other_cfg.enable ? "1":"0", szconfig.c_str());
	WritePrivateProfileStringA("DEBUG", "LEVEL", szlevel.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("LANGUAGE", "DEFAULT", szlan.c_str(), szconfig.c_str());

	if (appconfig.m_other_cfg.enable)
	{
		if (vrvlog::log::get().enable_log())
		{
			vrvlog::log::get().get_log()->flush_on((spdlog::level::level_enum)appconfig.m_other_cfg.level);
			vrvlog::log::get().get_log()->set_level((spdlog::level::level_enum)appconfig.m_other_cfg.level);
		}
		else
		{
			theApp.Initlog();
		}
	}
	else
	{
		vrvlog::log::get().enable_log(false);
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