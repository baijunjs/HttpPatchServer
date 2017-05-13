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
//bool CPatchCascade::InitDui()
//{
	//m_pDuiCascade = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUICascadeCfg", HandleToLong(m_hWnd));
	//ASSERT(m_pDuiCascade);

	//m_pEditDbIp = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditDbIp", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditDbIp);

	//m_pEditDbName = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditDbSrc", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditDbName);

	//m_pEditDbUser = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditDbUser", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditDbUser);

	//m_pEditDbPwd = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditDbPwd", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditDbPwd);

	//m_pChkCascade = (IDUICheckBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ChkBox-Cascade", m_pDuiCascade, TRUE);
	//ASSERT(m_pChkCascade);

	//m_pEditServerIp = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditUpIp", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditServerIp);

	//m_pEditServerPort = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditUpPort", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditServerPort);

	//m_pRadioAll = (IRadioBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "RadioBox_AllTime", m_pDuiCascade, TRUE);
	//ASSERT(m_pRadioAll);

	//m_pRadioPerid = (IRadioBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "RadioBox_Period", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditDbUser);

	//m_pRadioInteval = (IRadioBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "RadioBox_Interval", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditDbUser);

	//m_pEditPerid = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditPerid", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditPerid);

	//m_pEditBegin = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditBegin", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditBegin);

	//m_pEditEnd = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditEnd", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditEnd);

	//m_pChkFlux = (IDUICheckBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ChkBox-Flux", m_pDuiCascade, TRUE);
	//ASSERT(m_pChkFlux);

	//m_pEditFluxSpeed = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditSpeed", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditFluxSpeed);

	//m_pEditPath = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditPath", m_pDuiCascade, TRUE);
	//ASSERT(m_pEditPath);

	//m_pBtnCascade = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnTest", m_pDuiCascade, TRUE);
	//ASSERT(m_pBtnCascade);

	//return true;
//}

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
	InitControlData();
	EnableControl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPatchCascade::GetIntervalTime(std::string &szTime, std::string &szBegin, std::string &szEnd)
{
	std::smatch sm;
	std::regex rgx("(\\d{1,2}:\\d{1,2}:\\d{1,2})-(\\d{1,2}:\\d{1,2}:\\d{1,2})");
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
	std::stringstream ss;
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
			std::string szBegin, szEnd;
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
	std::string szDbip = DEdit(EditDbIp)->GetText();
	std::string szDbName = DEdit(EditDbSrc)->GetText();
	std::string szDbuser = DEdit(EditDbUser)->GetText();
	std::string szDbpwd = DEdit(EditDbPwd)->GetText();
	if (!IsIpValid(szDbip))
	{
		CMessageBox msg;
		msg.ShowMessage("\"数据库IP无效(1.1.1.1~255.255.255.255)\"");
		return;
	}
	CSqlConfig sql;
	if (!sql.InitDBValue(szDbip.c_str(), szDbName.c_str(), szDbuser.c_str(), szDbpwd.c_str()))
	{
		CMessageBox msg;
		msg.ShowMessage("数据库连接失败，请检查网络或者数据库配置");
		return;
	}

	std::string szPatchPath = sql.GetPatchPath();
	DEdit(EditPath)->SetText(szPatchPath);

	BOOL bEnable = sql.EnableUplink();
	DCheck(ChkBox-Cascade)->SetValue(bEnable ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);

	std::string szIp = sql.UplinkIp();
	DEdit(EditUpIp)->SetText(szIp);

	std::string szport = sql.UplinkPort();
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
			std::string szBegin, szEnd;
			GetIntervalTime(appconfig.m_cascade_cfg.sznettime, szBegin, szEnd);
			DEdit(EditBegin)->SetText(szBegin);
			DEdit(EditEnd)->SetText(szEnd);
		}
		break;
	default:
		DRadio(RadioBox_AllTime)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		break;
	}

	std::string szPeriod = sql.GetPeriod();
	DEdit(EditPerid)->SetText(szPeriod);

	std::string szbegin, szend;
	std::string szTime = sql.GetTime();
	GetIntervalTime(szTime, szbegin, szend);
	DEdit(EditBegin)->SetText(szbegin);
	DEdit(EditEnd)->SetText(szend);

	BOOL bFlux = sql.EnableFluxCtrl();
	DCheck(ChkBox-Flux)->SetValue(bFlux ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);

	std::string szFluxSpeed = sql.GetFluxValue();
	DEdit(EditSpeed)->SetText(szFluxSpeed);
}

BOOL CPatchCascade::OnApply()
{
	if (!IsIpValid(DEdit(EditDbIp)->GetText()))
	{
		CMessageBox msg;
		msg.ShowMessage("\"数据库IP无效(1.1.1.1~255.255.255.255)\"");
		return FALSE;
	}

	std::string &szDbip = appconfig.m_cascade_cfg.szdbip = DEdit(EditDbIp)->GetText();
	std::string &szDbName = appconfig.m_cascade_cfg.szdbsrc = DEdit(EditDbSrc)->GetText();
	std::string &szDbuser = appconfig.m_cascade_cfg.szdbuser = DEdit(EditDbUser)->GetText();
	std::string &szDbpwd = appconfig.m_cascade_cfg.szdbpwd = DEdit(EditDbPwd)->GetText();

	bool &bCas = appconfig.m_cascade_cfg.cascade = DCheck(ChkBox-Cascade)->GetValue() == DUICHECKBOX_CHECKED ? true : false;
	std::string &szUpServerIp = appconfig.m_cascade_cfg.szupserverip = DEdit(EditUpIp)->GetText();
	std::string &szUpServerPort = appconfig.m_cascade_cfg.szupserverport = DEdit(EditUpPort)->GetText();

	std::string sztime;
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
		std::string szbegin = DEdit(EditBegin)->GetText();
		std::string szend = DEdit(EditEnd)->GetText();
		sztime = appconfig.m_cascade_cfg.sznettime = szbegin + "-" + szend;
	}

	bool &bFlux = appconfig.m_cascade_cfg.flux = DCheck(ChkBox-Flux)->GetValue() == DUICHECKBOX_CHECKED ? true : false;
	std::string szFluxSpeed = DEdit(EditSpeed)->GetText();
	appconfig.m_cascade_cfg.fluxspeed = atoi(szFluxSpeed.c_str());
	std::string &szPath = appconfig.m_cascade_cfg.szPatchPath = DEdit(EditPath)->GetText();

	std::string &szconfig = appconfig.m_szConfigFile;

	std::string szMode;
	std::stringstream ss;
	ss << mode;
	ss >> szMode;

	WritePrivateProfileStringA("CASCADE", "DBIP", szDbip.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "DBSRC", szDbName.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "DBUSER", szDbuser.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "DBPWD", szDbpwd.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "CASCADE", bCas ? "1" : "0", szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "UPSERVERIP", szUpServerIp.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "UPSERVERPORT", szUpServerPort.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "TIMEMODE", szMode.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "NETTIME", sztime.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "FLUX", bFlux ? "1" : "0", szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "FLUXSPEED", szFluxSpeed.c_str(), szconfig.c_str());
	WritePrivateProfileStringA("CASCADE", "PATH", szPath.c_str(), szconfig.c_str());

	return TRUE;
}


void CPatchCascade::OnRestore()
{
	InitControlData();
}