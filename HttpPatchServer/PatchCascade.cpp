// PatchCascade.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchCascade.h"
#include "afxdialogex.h"
#include <regex>
#include <sstream>
#include "SqlConfig.h"
#include "MessageBox.h"

// CPatchCascade 对话框

IMPLEMENT_DYNAMIC(CPatchCascade, CDUIDialog)

CPatchCascade::CPatchCascade(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_CASCADE, pParent)
{

}

CPatchCascade::~CPatchCascade()
{
}

void CPatchCascade::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchCascade, CDUIDialog)
	ON_WM_CREATE()
	ON_MESSAGE(DUISM_LBUTTONUP, &CPatchCascade::OnButtonUp)
END_MESSAGE_MAP()


BOOL CPatchCascade::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUICascadeCfg");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


// CPatchCascade 消息处理程序
int CPatchCascade::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL CPatchCascade::PreTranslateMessage(MSG* pMsg)
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


BOOL CPatchCascade::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitControlLang();
	InitControlData();
	EnableControl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void GetIntervalTime(std::tstring &szTime, std::tstring &szBegin, std::tstring &szEnd)
{
	std::tsmatch sm;
	std::tregex rgx(_T("(\\d{1,2}:\\d{1,2}:\\d{1,2})-(\\d{1,2}:\\d{1,2}:\\d{1,2})"));
	if (std::regex_match(szTime, sm, rgx))
	{
		if (sm.size() >= 3)
		{
			szBegin = sm[1];
			szEnd = sm[2];
		}
	}
}


void CPatchCascade::InitControlData()
{
	std::tstringstream ss;
	DEdit(EditDbIp)->SetText(appconfig.m_cascade_cfg.szdbip);
	DEdit(EditDbSrc)->SetText(appconfig.m_cascade_cfg.szdbsrc);
	DEdit(EditDbUser)->SetText(appconfig.m_cascade_cfg.szdbuser);
	DEdit(EditDbPwd)->SetText(appconfig.m_cascade_cfg.szdbpwd);
	DCheck(ChkBox-Cascade)->SetValue(appconfig.m_cascade_cfg.cascade ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);
	DEdit(EditUpIp)->SetText(appconfig.m_cascade_cfg.szupserverip);
	DEdit(EditUpPort)->SetText(appconfig.m_cascade_cfg.szupserverport);
	switch (appconfig.m_cascade_cfg.mode)
	{
	case period_mode:
		DRadio(RadioBox_Period)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		DEdit(EditPerid)->SetText(appconfig.m_cascade_cfg.sznettime);
		break;
	case interval_mode:
		DRadio(RadioBox_Interval)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		{
			std::tstring szBegin, szEnd;
			GetIntervalTime(appconfig.m_cascade_cfg.sznettime, szBegin, szEnd);
			DEdit(EditBegin)->SetText(szBegin);
			DEdit(EditEnd)->SetText(szEnd);
		}
		break;
	default:
		DRadio(RadioBox_AllTime)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		break;
	}

	DCheck(ChkBox-Flux)->SetValue(appconfig.m_cascade_cfg.flux ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);
	ss << appconfig.m_cascade_cfg.fluxspeed;
	DEdit(EditSpeed)->SetText(ss.str());
	DEdit(EditPath)->SetText(appconfig.m_cascade_cfg.szPatchPath);
}


void CPatchCascade::EnableControl()
{
	DCheck(ChkBox-Cascade)->EnableObject(FALSE, TRUE);
	DEdit(EditUpIp)->EnableObject(FALSE, TRUE);
	DEdit(EditUpPort)->EnableObject(FALSE, TRUE);
	DRadio(RadioBox_AllTime)->EnableObject(FALSE, TRUE);
	DRadio(RadioBox_Period)->EnableObject(FALSE, TRUE);
	DRadio(RadioBox_Interval)->EnableObject(FALSE, TRUE);
	DEdit(EditPerid)->EnableObject(FALSE, TRUE);
	DEdit(EditBegin)->EnableObject(FALSE, TRUE);
	DEdit(EditEnd)->EnableObject(FALSE, TRUE);
	DCheck(ChkBox-Flux)->EnableObject(FALSE, TRUE);
	DEdit(EditSpeed)->EnableObject(FALSE, TRUE);
}


LRESULT CPatchCascade::OnButtonUp(WPARAM wparam, LPARAM lparam)
{
	if (DBtn(BtnTest) == (ICmdButton*)wparam)
	{
		GetCascadeConfig();
	}

	return 0;
}

void CPatchCascade::GetCascadeConfig()
{
	std::tstring szDbip = DEdit(EditDbIp)->GetText();
	std::tstring szDbName = DEdit(EditDbSrc)->GetText();
	std::tstring szDbuser = DEdit(EditDbUser)->GetText();
	std::tstring szDbpwd = DEdit(EditDbPwd)->GetText();
	if (!IsIpValid(szDbip))
	{
		CMessageBox msg;
		msg.ShowMessage(g_lang.GetText(10071));
		return;
	}
	CSqlConfig sql;
	if (!sql.InitDBValue((const char*)_bstr_t(szDbip.c_str()),
		(const char*)_bstr_t(szDbName.c_str()),
		(const char*)_bstr_t(szDbuser.c_str()),
		(const char*)_bstr_t(szDbpwd.c_str())))
	{
		CMessageBox msg;
		msg.ShowMessage(g_lang.GetText(10072));
		return;
	}

	std::tstring szPatchPath = sql.GetPatchPath();
	DEdit(EditPath)->SetText(szPatchPath);

	BOOL bEnable = sql.EnableUplink();
	DCheck(ChkBox-Cascade)->SetValue(bEnable ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);

	std::tstring szIp = sql.UplinkIp();
	DEdit(EditUpIp)->SetText(szIp);

	std::tstring szport = sql.UplinkPort();
	DEdit(EditUpPort)->SetText(szport);

	switch (sql.CycleType())
	{
	case period_mode:
		DRadio(RadioBox_Period)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		DEdit(EditPerid)->SetText(appconfig.m_cascade_cfg.sznettime);
		break;
	case interval_mode:
		DRadio(RadioBox_Interval)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		{
			std::tstring szBegin, szEnd;
			GetIntervalTime(appconfig.m_cascade_cfg.sznettime, szBegin, szEnd);
			DEdit(EditBegin)->SetText(szBegin);
			DEdit(EditEnd)->SetText(szEnd);
		}
		break;
	default:
		DRadio(RadioBox_AllTime)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		break;
	}

	std::tstring szPeriod = sql.GetPeriod();
	DEdit(EditPerid)->SetText(szPeriod);

	std::tstring szbegin, szend;
	std::tstring szTime = sql.GetTime();
	GetIntervalTime(szTime, szbegin, szend);
	DEdit(EditBegin)->SetText(szbegin);
	DEdit(EditEnd)->SetText(szend);

	BOOL bFlux = sql.EnableFluxCtrl();
	DCheck(ChkBox-Flux)->SetValue(bFlux ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);

	std::tstring szFluxSpeed = sql.GetFluxValue();
	DEdit(EditSpeed)->SetText(szFluxSpeed);
}

BOOL CPatchCascade::OnApply()
{
	if (!IsIpValid(DEdit(EditDbIp)->GetText()))
	{
		CMessageBox msg;
		msg.ShowMessage(g_lang.GetText(10071));
		return FALSE;
	}

	std::tstring &szDbip = appconfig.m_cascade_cfg.szdbip = DEdit(EditDbIp)->GetText();
	std::tstring &szDbName = appconfig.m_cascade_cfg.szdbsrc = DEdit(EditDbSrc)->GetText();
	std::tstring &szDbuser = appconfig.m_cascade_cfg.szdbuser = DEdit(EditDbUser)->GetText();
	std::tstring &szDbpwd = appconfig.m_cascade_cfg.szdbpwd = DEdit(EditDbPwd)->GetText();

	bool &bCas = appconfig.m_cascade_cfg.cascade = DCheck(ChkBox-Cascade)->GetValue() == DUICHECKBOX_CHECKED ? true : false;
	std::tstring &szUpServerIp = appconfig.m_cascade_cfg.szupserverip = DEdit(EditUpIp)->GetText();
	std::tstring &szUpServerPort = appconfig.m_cascade_cfg.szupserverport = DEdit(EditUpPort)->GetText();

	std::tstring sztime;
	timemode mode;
	IDUIRadioGroup *pGroup = DRadio(RadioBox_AllTime)->GetGroup();
	IDUIControlBase *pCtrl = pGroup->GetRadio();
	if (DRadio(RadioBox_AllTime) == pCtrl)
	{
		mode = appconfig.m_cascade_cfg.mode = default_mode;
	}
	else if (DRadio(RadioBox_Period) == pCtrl)
	{
		mode = appconfig.m_cascade_cfg.mode = period_mode;
		sztime = appconfig.m_cascade_cfg.sznettime = DEdit(EditPerid)->GetText();
	}
	else if (DRadio(RadioBox_Interval) == pCtrl)
	{
		mode = appconfig.m_cascade_cfg.mode = interval_mode;
		std::tstring szbegin = DEdit(EditBegin)->GetText();
		std::tstring szend = DEdit(EditEnd)->GetText();
		sztime = appconfig.m_cascade_cfg.sznettime = szbegin + _T("-") + szend;
	}

	bool &bFlux = appconfig.m_cascade_cfg.flux = DCheck(ChkBox-Flux)->GetValue() == DUICHECKBOX_CHECKED ? true : false;
	std::tstring szFluxSpeed = DEdit(EditSpeed)->GetText();
	appconfig.m_cascade_cfg.fluxspeed = _ttoi(szFluxSpeed.c_str());
	std::tstring &szPath = appconfig.m_cascade_cfg.szPatchPath = DEdit(EditPath)->GetText();

	std::tstring &szconfig = appconfig.m_szConfigFile;

	std::tstring szMode;
	std::tstringstream ss;
	ss << mode;
	ss >> szMode;

	WritePrivateProfileString(_T("CASCADE"), _T("DBIP"), szDbip.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("DBSRC"), szDbName.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("DBUSER"), szDbuser.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("DBPWD"), szDbpwd.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("CASCADE"), bCas ? _T("1") : _T("0"), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("UPSERVERIP"), szUpServerIp.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("UPSERVERPORT"), szUpServerPort.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("TIMEMODE"), szMode.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("NETTIME"), sztime.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("FLUX"), bFlux ? _T("1") : _T("0"), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("FLUXSPEED"), szFluxSpeed.c_str(), szconfig.c_str());
	WritePrivateProfileString(_T("CASCADE"), _T("PATH"), szPath.c_str(), szconfig.c_str());

	return TRUE;
}


void CPatchCascade::OnRestore()
{
	InitControlData();
}

void CPatchCascade::InitControlLang()
{
	DStatic(Static_DbIp)->SetText(g_lang.GetText(10027));
	DStatic(Static_DbSrc)->SetText(g_lang.GetText(10028));
	DStatic(Static_DbUser)->SetText(g_lang.GetText(10025));
	DStatic(Static_DbPwd)->SetText(g_lang.GetText(10026));
	DCheck(ChkBox-Cascade)->SetText(g_lang.GetText(10029));
	DCheck(ChkBox-Flux)->SetText(g_lang.GetText(10020));
	DStatic(Static_Ip)->SetText(g_lang.GetText(10030));
	DStatic(Static_Port)->SetText(g_lang.GetText(10031));
	DRadio(RadioBox_AllTime)->SetText(g_lang.GetText(10016), TRUE);
	DRadio(RadioBox_Period)->SetText(g_lang.GetText(10017), TRUE);
	DRadio(RadioBox_Interval)->SetText(g_lang.GetText(10018), TRUE);
	DStatic(Static_Min)->SetText(g_lang.GetText(10019));
	DStatic(Static_Unit)->SetText(g_lang.GetText(10021));
	DStatic(StaticPath)->SetText(g_lang.GetText(10032));
	DBtn(BtnTest)->SetText(g_lang.GetText(10034));
}