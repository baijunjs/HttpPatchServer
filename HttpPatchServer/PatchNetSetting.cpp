// PatchNetSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchNetSetting.h"
#include "afxdialogex.h"
#include <regex>
#include <sstream>
#include "MessageBox.h"
#include "Clibcurl.h"
#include "PatchBus.h"
#include "PatchViewStatics.h"
#include "HttpPatchServerDlg.h"

// CPatchNetSetting 对话框

IMPLEMENT_DYNAMIC(CPatchNetSetting, CDUIDialog)

CPatchNetSetting::CPatchNetSetting(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_DOWNSETTING, pParent)
{
	m_pParent = pParent;
}

CPatchNetSetting::~CPatchNetSetting()
{
}

void CPatchNetSetting::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchNetSetting, CDUIDialog)
	ON_WM_CREATE()
	ON_MESSAGE(DUI_EDIT_KILLFOCUS, &CPatchNetSetting::OnKillFocus)
	ON_MESSAGE(DUI_EDIT_PRERETURN, &CPatchNetSetting::OnPreReturn)
	ON_MESSAGE(DUISM_RADIOCHANGE, &CPatchNetSetting::OnRadioChange)
	ON_MESSAGE(DUISM_VALUECHANGED, &CPatchNetSetting::OnCheckBoxChanged)
	ON_MESSAGE(DUISM_LBUTTONUP, &CPatchNetSetting::OnButtonDispatcher)
	ON_MESSAGE(DUITREE_CHECKITEM, &CPatchNetSetting::OnTreeCheckItem)
END_MESSAGE_MAP()


// CPatchNetSetting 消息处理程序


//bool CPatchNetSetting::InitDui()
//{
//	m_pDuiDownSetting = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIHttpCfg", HandleToLong(m_hWnd));
//	ASSERT(m_pDuiDownSetting);
//
//	m_pEditUrl = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditUrl", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditUrl);
//
//	m_pEditPath = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditPath", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditPath);
//
//	m_pCmdBtnTest = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnTest", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pCmdBtnTest);
//
//	m_pCmdBtnBrowser = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnBrowser", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pCmdBtnBrowser);
//
//	m_pProductsTree = (IDUISimpleTree*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ProductTree", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pProductsTree);
//
//	m_pLansTree = (IDUISimpleTree*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "LanTree", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pLansTree);
//
//	m_pRadioAll = (IRadioBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "RadioBox_AllTime", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pRadioAll);
//
//	m_pRadioPerid = (IRadioBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "RadioBox_Period", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pRadioPerid);
//
//	m_pRadioInteval = (IRadioBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "RadioBox_Interval", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pRadioInteval);
//
//	m_pEditPerid = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditPerid", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditPerid);
//
//	m_pEditBegin = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditBegin", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditBegin);
//
//	m_pEditEnd = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditEnd", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditEnd);
//
//	m_pChkFlux = (IDUICheckBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ChkBox-Flux", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pChkFlux);
//
//	m_pEditFluxSpeed = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditSpeed", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditFluxSpeed);
//
//	m_pChkProxy = (IDUICheckBox*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ChkBox-NetProxy", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pChkProxy);
//
//	m_pEditIp = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditIp", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditIp);
//
//	m_pEditPort = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditPort", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditPort);
//
//	m_pEditUser = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditUser", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditUser);
//
//	m_pEditPwd = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditPwd", m_pDuiDownSetting, TRUE);
//	ASSERT(m_pEditPwd);
//
//	return true;
//}

BOOL CPatchNetSetting::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIHttpCfg");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}

int CPatchNetSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//if (!InitDui())
	//	return -1;

	return 0;
}

void CPatchNetSetting::GetIntevalTime(std::string& src, std::string &szbH, std::string &szbM, 
	std::string &szeH, std::string &szeM)
{
	std::regex rgx("(\\d{1,2}):(\\d{0,2})-(\\d{1,2}):(\\d{0,2})");
	std::smatch sm;
	if (std::regex_match(src, sm, rgx))
	{
		if (sm.size() >= 5)
		{
			szbH = sm[1];
			szbM = sm[2];
			szeH = sm[3];
			szeM = sm[4];
		}
	}

	if (szbH.empty()) szbH = "00";
	if (szbM.empty()) szbM = "00";
	if (szeH.empty()) szeH = "00";
	if (szeM.empty()) szeM = "00";
}

CWnd * CPatchNetSetting::GetParent()
{
	return m_pParent;
}


void CPatchNetSetting::InitControlData()
{
	DEdit(EditUrl)->SetText(appconfig.m_http_cfg.m_szIndexUrl);
	DEdit(EditPath)->SetText(appconfig.m_http_cfg.m_szPatchPath);

	RedrawSimpleTree();
	RestoreTreeCheckItems(producttree);
	RestoreTreeCheckItems(languagetree);

	switch (appconfig.m_http_cfg.mode)
	{
	case period_mode:
		DRadio(RadioBox_Period)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		DEdit(EditPerid)->SetText(appconfig.m_http_cfg.sznettime);
		DEdit(EditPerid)->DUISetToolTip(appconfig.m_http_cfg.sznettime);
		break;
	case interval_mode:
		DRadio(RadioBox_Interval)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		{
			std::string szbegin, szend;
			std::string szbegH, szbegM, szendH, szendM;
			GetIntevalTime(appconfig.m_http_cfg.sznettime, szbegH, szbegM,
				szendH, szendM);
			szbegin = szbegH + ":" + szbegM;
			szend = szendH + ":" + szendM;
			DEdit(EditBegin)->SetText(szbegin);
			DEdit(EditEnd)->SetText(szend);
			DEdit(EditBegin)->DUISetToolTip(szbegin);
			DEdit(EditEnd)->DUISetToolTip(szend);
		}
		break;
	default:
		DRadio(RadioBox_AllTime)->SetValue(DUIRADIOBOX_CHECKED, TRUE);
		break;
	}

	DCheck(ChkBox-Flux)->SetValue(appconfig.m_http_cfg.flux ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);
	std::stringstream ss;
	ss << appconfig.m_http_cfg.fluxspeed;
	DEdit(EditSpeed)->SetText(ss.str());

	DCheck(ChkBox-NetProxy)->SetValue(appconfig.m_http_cfg.proxy ? DUICHECKBOX_CHECKED : DUICHECKBOX_UNCHECKED);
	DEdit(EditIp)->SetText(appconfig.m_http_cfg.szip);
	DEdit(EditPort)->SetText(appconfig.m_http_cfg.szport);
	DEdit(EditUser)->SetText(appconfig.m_http_cfg.szuser);
	DEdit(EditPwd)->SetText(appconfig.m_http_cfg.szpwd);
}

void CPatchNetSetting::EnbaleControl()
{
	if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_Period)->GetValue())
		DEdit(EditPerid)->EnableObject(TRUE, TRUE);
	else
		DEdit(EditPerid)->EnableObject(FALSE, TRUE);

	if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_Interval)->GetValue())
	{
		DEdit(EditBegin)->EnableObject(TRUE, TRUE);
		DEdit(EditEnd)->EnableObject(TRUE, TRUE);
	}
	else
	{
		DEdit(EditBegin)->EnableObject(FALSE, TRUE);
		DEdit(EditEnd)->EnableObject(FALSE, TRUE);
	}

	if (DUICHECKBOX_CHECKED == DCheck(ChkBox-Flux)->GetValue())
		DEdit(EditSpeed)->EnableObject(TRUE, TRUE);
	else
		DEdit(EditSpeed)->EnableObject(FALSE, TRUE);

	if (DUICHECKBOX_CHECKED == DCheck(ChkBox-NetProxy)->GetValue())
	{
		DEdit(EditIp)->EnableObject(TRUE, TRUE);
		DEdit(EditPort)->EnableObject(TRUE, TRUE);
		DEdit(EditUser)->EnableObject(TRUE, TRUE);
		DEdit(EditPwd)->EnableObject(TRUE, TRUE);
	}
	else
	{
		DEdit(EditIp)->EnableObject(FALSE, TRUE);
		DEdit(EditPort)->EnableObject(FALSE, TRUE);
		DEdit(EditUser)->EnableObject(FALSE, TRUE);
		DEdit(EditPwd)->EnableObject(FALSE, TRUE);
	}
}



BOOL CPatchNetSetting::OnInitDialog()
{
	CDUIDialog::OnInitDialog();


	// TODO:  在此添加额外的初始化
	
	InitControlData();

	EnbaleControl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL IsTimeValid(std::string &sztime)
{
	std::regex rgx("(\\d{1,2}):(\\d{0,2})");
	std::smatch sm;
	if (std::regex_match(sztime, sm, rgx))
	{
		if (sm.size() >= 3)
		{
			std::string szHour = sm[1];
			std::string szMin = sm[2];
			int iHour = atoi(szHour.c_str());
			int iMin = atoi(szMin.c_str());
			if ((iHour >= 0 && iHour < 24)
				&& (iMin >= 0 && iMin <= 59))
			{
				return TRUE;
			}

		}
	}

	return FALSE;
}

BOOL IsIpValid(std::string &szIp)
{
	std::regex rgx("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})");
	std::smatch sm;
	if (std::regex_match(szIp, sm, rgx))
	{
		if (sm.size() >= 5)
		{
			std::string f1 = sm[1];
			std::string f2 = sm[2];
			std::string f3 = sm[3];
			std::string f4 = sm[4];
			int s1 = atoi(f1.c_str());
			int s2 = atoi(f2.c_str());
			int s3 = atoi(f3.c_str());
			int s4 = atoi(f4.c_str());
			if ((s1 > 0 && s1 <= 255) && (s2 >= 0 && s2 <= 255)
				&& (s3 >= 0 && s3 <= 255) && (s4 >= 0 && s4 <= 255))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}


BOOL CPatchNetSetting::OnApply()
{
	timemode mode = default_mode;
	std::string sztime = "0";
	bool flux = false, proxy = false;
	std::string szfluxspeed;
	std::string szip, szport, szuser, szpwd;

	if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_AllTime)->GetValue())
		mode = default_mode;

	else if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_Period)->GetValue())
	{
		mode = period_mode;
		sztime = DEdit(EditPerid)->GetText();
		int itime = atoi(sztime.c_str());
		if (itime <= 0)
		{
			CMessageBox msg;
			msg.ShowMessage("\"按周期下载\"指定时间值无效(value>0)");
			return FALSE;
		}
	}

	else if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_Interval)->GetValue())
	{
		mode = interval_mode;
		std::string szbegin = DEdit(EditBegin)->GetText();
		std::string szend = DEdit(EditEnd)->GetText();
		if (!IsTimeValid(szbegin))
		{
			CMessageBox msg;
			msg.ShowMessage("\"按时间下载\"指定开始时间范围无效(00:00~23:59)");
			return FALSE;
		}
		if (!IsTimeValid(szend))
		{
			CMessageBox msg;
			msg.ShowMessage("\"按时间下载\"指定结束时间范围无效(00:00~23:59)");
			return FALSE;
		}
		sztime = szbegin + "-" + szend;
	}

	if (DUICHECKBOX_CHECKED == DCheck(ChkBox-Flux)->GetValue())
	{
		flux = true;
		szfluxspeed = DEdit(EditSpeed)->GetText();
		if (atoi(szfluxspeed.c_str()) < 0)
		{
			CMessageBox msg;
			msg.ShowMessage("\"流量限制\"指定流量值无效(value>=0)");
			return FALSE;
		}
	}

	if (DUICHECKBOX_CHECKED == DCheck(ChkBox-NetProxy)->GetValue())
	{
		proxy = true;
		szip = DEdit(EditIp)->GetText();
		szport = DEdit(EditPort)->GetText();
		szuser = DEdit(EditUser)->GetText();
		szpwd = DEdit(EditPwd)->GetText();
		if (!IsIpValid(szip))
		{
			CMessageBox msg;
			msg.ShowMessage("\"代理\"指定IP无效(1.1.1.1~255.255.255.255)");
			return FALSE;
		}
		int iport = atoi(szport.c_str());
		if (iport <= 0 || iport > 65535)
		{
			CMessageBox msg;
			msg.ShowMessage("\"代理\"指定端口无效(1~65535)");
			return FALSE;
		}
	}

	std::string szlastProducts = appconfig.m_http_cfg.m_szProducts, szlastlans = appconfig.m_http_cfg.m_szLans;
	std::string &szurl = appconfig.m_http_cfg.m_szIndexUrl = DEdit(EditUrl)->GetText();
	std::string &szpath = appconfig.m_http_cfg.m_szPatchPath = DEdit(EditPath)->GetText();
	std::string &szproducts = appconfig.m_http_cfg.m_szProducts = GetCheckedItemString(DTree(ProductTree));
	std::string &szlans = appconfig.m_http_cfg.m_szLans = GetCheckedItemString(DTree(LanTree));
	std::string &szcfgpath = appconfig.m_szConfigFile;

	std::string szPackName;
	size_t pos = szurl.find_last_of('/');
	if (pos != std::string::npos)
		appconfig.m_http_cfg.m_szPackName = szurl.substr(pos + 1);
	std::string szPackPath = szpath + "\\Tools\\" + appconfig.m_http_cfg.m_szPackName;
	std::string szPackSha;

	CPatchMode *pMode = (CPatchMode*)GetParent();
	CPatchView *pPatchView = (CPatchView *)pMode->GetPatchView();
	CPatchViewStatics *pStaticView = (CPatchViewStatics *)pPatchView->GetStaticView();
	CPatchDownView *pDownView = (CPatchDownView*)pPatchView->GetDownView();

	if (GetFileSHA1(szPackPath, szPackSha))
	{

		if (szPackSha != bus.GetPackSha1() || szproducts != szlastProducts)
		{
			pStaticView->DeleteAllItems();
			pStaticView->InsertIndexItem();
			pStaticView->InsertProductsItems();
			bus.SetPackSha1(szPackSha);
		}
	}


	std::string &szcfgfile = appconfig.m_szConfigFile;
	timemode &_mode = appconfig.m_http_cfg.mode = mode;
	std::string &_time = appconfig.m_http_cfg.sznettime = sztime;
	bool &_flux = appconfig.m_http_cfg.flux = flux;
	int  &_fluxspeed = appconfig.m_http_cfg.fluxspeed = atoi(szfluxspeed.c_str());
	bool &_proxy = appconfig.m_http_cfg.proxy = proxy;
	std::string &_ip = appconfig.m_http_cfg.szip = szip;
	std::string &_port = appconfig.m_http_cfg.szport = szport;
	std::string &_user = appconfig.m_http_cfg.szuser = szuser;
	std::string &_pwd = appconfig.m_http_cfg.szpwd = szpwd;

	if (_flux)
	{
		std::weak_ptr<Curl> weak_curl = theApp.m_curlptr;
		if (!weak_curl.expired())
		{
			std::shared_ptr<Curl> strong_curl = weak_curl.lock();
			strong_curl->SetDownloadSpeed(_fluxspeed);
		}
	}
	else
	{
		std::weak_ptr<Curl> weak_curl = theApp.m_curlptr;
		if (!weak_curl.expired())
		{
			std::shared_ptr<Curl> strong_curl = weak_curl.lock();
			strong_curl->SetDownloadSpeed(0);
		}
	}

	std::string szMode;
	std::stringstream ss;
	ss << (int)_mode;
	ss >> szMode;

	WritePrivateProfileStringA("PATCH", "URL", szurl.c_str(), szcfgpath.c_str());
	WritePrivateProfileStringA("PATCH", "PATH", szpath.c_str(), szcfgpath.c_str());
	WritePrivateProfileStringA("PATCH", "PRODUCTS", szproducts.c_str(), szcfgpath.c_str());
	WritePrivateProfileStringA("PATCH", "LAN", szlans.c_str(), szcfgpath.c_str());

	WritePrivateProfileStringA("NET", "TIMEMODE", szMode.c_str(), szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "NETTIME", _time.c_str(), szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "FLUX", _flux ? "1" : "0", szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "FLUXSPEED", szfluxspeed.c_str(), szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "PROXY", _proxy ? "1" : "0", szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "PROXYIP", _ip.c_str(), szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "PROXYPORT", _port.c_str(), szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "PROXYUSER", _user.c_str(), szcfgfile.c_str());
	WritePrivateProfileStringA("NET", "PROXYPWD", _pwd.c_str(), szcfgfile.c_str());

	return TRUE;
}

void CPatchNetSetting::OnRestore()
{
	InitControlData();
	EnbaleControl();
}

LRESULT CPatchNetSetting::OnPreReturn(WPARAM wparam, LPARAM lparam)
{
	return 1;
}

LRESULT CPatchNetSetting::OnKillFocus(WPARAM wparam, LPARAM lparam)
{
	if (DEdit(EditPerid) == (IDUIEditCtrl*)wparam)
	{
		std::string sztime = DEdit(EditPerid)->GetText();
		int itime = atoi(sztime.c_str());
		if (itime <= 0)
		{
			DEdit(EditPerid)->DUISetToolTip("\"按周期下载\"指定时间值无效(value>0)");
		}
		else
		{
			DEdit(EditPerid)->DUISetToolTip(sztime);
		}
	}
	else if (DEdit(EditBegin) == (IDUIEditCtrl*)wparam)
	{
		std::string szbegin = DEdit(EditBegin)->GetText();
		if (!IsTimeValid(szbegin))
		{
			DEdit(EditBegin)->DUISetToolTip("\"按时间下载\"指定开始时间范围无效(00:00~23:59)");
		}
		else
		{
			DEdit(EditBegin)->DUISetToolTip(szbegin);
		}
	}
	else if (DEdit(EditEnd) == (IDUIEditCtrl*)wparam)
	{
		std::string szend = DEdit(EditEnd)->GetText();
		if (!IsTimeValid(szend))
		{
			DEdit(EditEnd)->DUISetToolTip("\"按时间下载\"指定结束时间范围无效(00:00~23:59)");
		}
		else
		{
			DEdit(EditEnd)->DUISetToolTip(szend);
		}
	}
	else if (DEdit(EditIp) == (IDUIEditCtrl*)wparam)
	{
		std::string szip = DEdit(EditIp)->GetText();
		if (!IsIpValid(szip))
		{
			DEdit(EditIp)->DUISetToolTip("\"代理\"指定IP无效(1.1.1.1~255.255.255.255)");
		}
		else
		{
			DEdit(EditIp)->DUISetToolTip(szip);
		}
	}
	else if (DEdit(EditPort) == (IDUIEditCtrl*)wparam)
	{
		std::string szport = DEdit(EditPort)->GetText();
		int iport = atoi(szport.c_str());
		if (iport <= 0 || iport > 65535)
		{
			DEdit(EditPort)->DUISetToolTip("\"代理\"指定端口无效(1~65535)");
		}
		else
		{
			DEdit(EditPort)->DUISetToolTip(szport);
		}
	}
	else if (DEdit(EditSpeed) == (IDUIEditCtrl*)wparam)
	{
		int fluxspeed = atoi(DEdit(EditSpeed)->GetText().c_str());
		if (fluxspeed < 0)
		{
			DEdit(EditSpeed)->DUISetToolTip("\"流量限制\"指定流量值无效(value>=0)");
		}
		else
		{
			DEdit(EditSpeed)->DUISetToolTip(DEdit(EditSpeed)->GetText());
		}
	}
	return 0;
}


LRESULT  CPatchNetSetting::OnRadioChange(WPARAM wparam, LPARAM lparam)
{
	if (DRadio(RadioBox_Period) == (IRadioBox*)lparam)
	{
		DEdit(EditPerid)->EnableObject(TRUE, TRUE);
		DEdit(EditBegin)->EnableObject(FALSE, TRUE);
		DEdit(EditEnd)->EnableObject(FALSE, TRUE);
	}
	else if (DRadio(RadioBox_Interval) == (IRadioBox*)lparam)
	{
		DEdit(EditPerid)->EnableObject(FALSE, TRUE);
		DEdit(EditBegin)->EnableObject(TRUE, TRUE);
		DEdit(EditEnd)->EnableObject(TRUE, TRUE);
	}
	return 0;
}


LRESULT CPatchNetSetting::OnCheckBoxChanged(WPARAM wparam, LPARAM lparam)
{
	if (DCheck(ChkBox-Flux) == (IDUICheckBox*)lparam)
	{
		if (DUICHECKBOX_CHECKED == (DUICHECKBOX_VALUE)wparam)
		{
			DEdit(EditSpeed)->EnableObject(TRUE, TRUE);
		}
		else if (DUICHECKBOX_UNCHECKED == (DUICHECKBOX_VALUE)wparam)
		{
			DEdit(EditSpeed)->EnableObject(FALSE, TRUE);
		}
	}
	else if (DCheck(ChkBox-NetProxy) == (IDUICheckBox*)lparam)
	{
		if (DUICHECKBOX_CHECKED == (DUICHECKBOX_VALUE)wparam)
		{
			DEdit(EditIp)->EnableObject(TRUE, TRUE);
			DEdit(EditPort)->EnableObject(TRUE, TRUE);
			DEdit(EditUser)->EnableObject(TRUE, TRUE);
			DEdit(EditPwd)->EnableObject(TRUE, TRUE);
		}
		else if (DUICHECKBOX_UNCHECKED == (DUICHECKBOX_VALUE)wparam)
		{
			DEdit(EditIp)->EnableObject(FALSE, TRUE);
			DEdit(EditPort)->EnableObject(FALSE, TRUE);
			DEdit(EditUser)->EnableObject(FALSE, TRUE);
			DEdit(EditPwd)->EnableObject(FALSE, TRUE);
		}
	}
	return 0;
}

BOOL CPatchNetSetting::PreTranslateMessage(MSG* pMsg)
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


void CPatchNetSetting::RedrawSimpleTree()
{

	std::string szpackindex = DEdit(EditPath)->GetText() + "\\Tools\\PackIndex.dat";
	if (PathFileExistsA(szpackindex.c_str()))
	{
		if (!CPackInterface::init())
			return;

		IPackIndex *packindex = CPackInterface::getPackIndexObject();
		if (!bus.analyze_main_index(packindex, szpackindex))
			vrvlog::SPD_LOG_ERROR("{0} 解析失败", szpackindex.c_str());

		else
			vrvlog::SPD_LOG_INFO("{0} 解析成功", szpackindex.c_str());
		CPackInterface::FreePackIndexObject(packindex);
	}

	RedrawTreeImpl(producttree);
	RedrawTreeImpl(languagetree);
}


void CPatchNetSetting::RedrawTreeImpl(tree whichtree)
{
	IDUISimpleTree *pTree = NULL;

	if (producttree == whichtree)
		pTree = DTree(ProductTree);

	else if (languagetree == whichtree)
		pTree = DTree(LanTree);

	pTree->DeleteAllItem();
	OLE_HANDLE hroot = pTree->GetRootItem(NULL);

	vrv::patch::PublishersMapPtr publishers = bus.GetPatchIndexMap();
	if (!publishers || publishers->Publishers.empty())
	{
		//pTree->AppendChild(hroot, "请点击\"测试连接\"", FALSE);
		return;
	}
	vrv::patch::PublishersMap::_iterator iter = publishers->Publishers.begin();
	for (; iter != publishers->Publishers.end(); ++iter)
	{
		std::string szPublisher = iter->first;
		OLE_HANDLE hpublisher = pTree->AppendChild(hroot, szPublisher, FALSE);
		vrv::patch::FamiliesMapPtr families = iter->second;
		if (pTree == DTree(ProductTree))
		{
			vrv::patch::FamiliesMap::_iterator _iter = families->ProductsFamily.begin();
			for (; _iter != families->ProductsFamily.end(); ++_iter)
			{
				std::string szFamily = _iter->first;
				OLE_HANDLE hfamily = pTree->AppendChild(hpublisher, szFamily, FALSE);
				vrv::patch::ProductsMapPtr products = _iter->second;
				vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
				for (; _iter_ != products->Products.end(); ++_iter_)
				{
					std::string szProduct = _iter_->first;
					OLE_HANDLE hproduct = pTree->AppendChild(hfamily, szProduct, FALSE);
					pTree->SetItemData(hproduct, (OLE_HANDLE)&_iter_->second);
				}
				pTree->Expand(hfamily, FALSE);
			}
		}
		else if (pTree == DTree(LanTree))
		{
			vrv::patch::FamiliesMap::_iterator _iter = families->LanguagesFamily.begin();
			for (; _iter != families->LanguagesFamily.end(); ++_iter)
			{
				std::string szFamily = _iter->first;
				OLE_HANDLE hfamily = pTree->AppendChild(hpublisher, szFamily, FALSE);
				vrv::patch::ProductsMapPtr products = _iter->second;
				vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
				for (; _iter_ != products->Products.end(); ++_iter_)
				{
					std::string szProduct = _iter_->first;
					OLE_HANDLE hproduct = pTree->AppendChild(hfamily, szProduct, FALSE);
					pTree->SetItemData(hproduct, (OLE_HANDLE)&_iter_->second);
				}
				pTree->Expand(hfamily, FALSE);
			}
		}
		pTree->Expand(hpublisher, FALSE);
	}
	pTree->RedrawWindow(TRUE);
}


LRESULT CPatchNetSetting::OnButtonDispatcher(WPARAM wparam, LPARAM lparam)
{
	if (DBtn(BtnTest) == (ICmdButton*)wparam)
	{
		return OnButtonTest(wparam, lparam);
	}
	else if (DBtn(BtnBrowser) == (ICmdButton*)wparam)
	{
		return OnButtonBrowser(wparam, lparam);
	}

	return 0;
}

LRESULT CPatchNetSetting::OnTreeCheckItem(WPARAM wparam, LPARAM lparam)
{
	IDUISimpleTree *pTree = (IDUISimpleTree*)lparam;
	if (wparam != NULL)
	{
		CheckChildItem(pTree, wparam);
	}
	return 0;
}


void CPatchNetSetting::CheckChildItem(IDUISimpleTree *tree, OLE_HANDLE hParent)
{
	OLE_HANDLE hChild = tree->GetChildItem(hParent);
	while (hChild)
	{
		tree->CheckItem(hChild, tree->IsCheckItem(hParent));
		hChild = tree->GetNextSiblingItem(hChild);
	}
}

LRESULT CPatchNetSetting::OnButtonTest(WPARAM wparam, LPARAM lparam)
{
	std::string szurl = DEdit(EditUrl)->GetText();
	std::string szpatchpath = DEdit(EditPath)->GetText();
	std::regex rgx("^[A-Za-z]:[\\\\\\w]*");
	std::smatch sm;
	if (!std::regex_match(szpatchpath, sm, rgx))
	{
		CMessageBox msgbox;
		msgbox.ShowMessage("请选择有效的\"本地补丁路径\"");
		return 0;
	}

	std::string szPackName;
	size_t pos = szurl.find_last_of('/');
	if (pos != std::string::npos)
	{
		szPackName = szurl.substr(pos + 1);
	}

	std::string sztoolpath = szpatchpath + "\\Tools\\";
	if (!PathFileExists(sztoolpath.c_str()))
		CreateDirectoryA(sztoolpath.c_str(), NULL);

	std::string szpackindex = sztoolpath + szPackName;
	std::string sztmppackindex = szpackindex + "~";
	std::shared_ptr<Curl> m_curlptr = std::make_shared<Curl>();

	if (appconfig.m_http_cfg.flux)
		m_curlptr->SetDownloadSpeed(appconfig.m_http_cfg.fluxspeed);

	if (appconfig.m_http_cfg.proxy)
		m_curlptr->SetProxy(
			appconfig.m_http_cfg.szip,
			appconfig.m_http_cfg.szport,
			appconfig.m_http_cfg.szuser,
			appconfig.m_http_cfg.szpwd);

	m_curlptr->SetUrlFile(szurl, sztmppackindex);

	long code = 0l;
	if (0 == (code = m_curlptr->StartDownload()))
	{
		MoveFileExA(sztmppackindex.c_str(), szpackindex.c_str(), MOVEFILE_REPLACE_EXISTING);
		vrvlog::SPD_LOG_INFO("{0} 下载成功", szpackindex.c_str());
		RedrawSimpleTree();
		RestoreTreeCheckItems(producttree);
		RestoreTreeCheckItems(languagetree);
	}
	else
	{
		vrvlog::SPD_LOG_ERROR("{0} 下载失败", szpackindex.c_str());
		CMessageBox msg;
		msg.ShowMessage("测试连接失败,请检查网络或者URL配置");
	}

	return 0;
}


LRESULT CPatchNetSetting::OnButtonBrowser(WPARAM wparam, LPARAM lparam)
{
	CHAR szPath[MAX_PATH] = { 0 };
	BROWSEINFOA bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = _T("请选择补丁文件存放路径");
	bi.ulFlags = CSIDL_DRIVES;
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;

	LPITEMIDLIST lpIDList = SHBrowseForFolderA(&bi);
	if (NULL != lpIDList)
	{
		SHGetPathFromIDListA(lpIDList, szPath);
		DEdit(EditPath)->SetText(szPath);
		CreateDirectoryA(szPath, NULL);
		strcat_s(szPath, MAX_PATH, "\\Tools");
		CreateDirectoryA(szPath, NULL);
		CoTaskMemFree(lpIDList);
	}

	return 0;
}


std::string CPatchNetSetting::GetCheckedItemString(IDUISimpleTree* pTree)
{
	std::string szChecked = ";";
	short schecked = pTree->GetCheckItemCount();

	IDUITreeItem *item = pTree->GetFirstCheckItem();
	while (item)
	{
		OLE_HANDLE hData = pTree->GetItemData(item->GetTreeNode());
		if (hData)
		{
			std::string szItemText = pTree->GetItemText(item->GetTreeNode());
			szChecked.append(szItemText);
			szChecked.append(";");
		}
		item = pTree->GetNextCheckItem(item);
	}

	return szChecked;
}


void CPatchNetSetting::RestoreTreeCheckItems(tree whichtree)
{
	IDUISimpleTree *pTree = NULL;
	std::string szXX;
	if (producttree == whichtree)
	{
		pTree = DTree(ProductTree);
		szXX = appconfig.m_http_cfg.m_szProducts;
	}
	else if (languagetree == whichtree)
	{
		pTree = DTree(LanTree);
		szXX = appconfig.m_http_cfg.m_szLans;
	}

	if (pTree == NULL)
		return;


	OLE_HANDLE hroot = pTree->GetRootItem(NULL);
	OLE_HANDLE hchild = pTree->GetChildItem(hroot);
	//pTree->CheckItem(hchild, FALSE);
	if (szXX.empty() || szXX == ";")
	{
		pTree->CheckItem(hchild, TRUE);
		return;
	}
	while (hchild)
	{
		TravelTree(pTree, hchild, szXX);
		hchild = pTree->GetNextSiblingItem(hchild);
	}

	pTree->RedrawWindow(TRUE);
}

void CPatchNetSetting::TravelTree(IDUISimpleTree* pTree, OLE_HANDLE hParent, std::string& szChecked)
{
	std::string szItemText = pTree->GetItemText(hParent);
	szItemText.append(";").insert(0, ";");
	if (szChecked.find(szItemText) != std::string::npos)
	{
		pTree->CheckItem(hParent, TRUE);
	}
	else
	{
		pTree->CheckItem(hParent, FALSE);
	}
	OLE_HANDLE hchild = pTree->GetChildItem(hParent);
	while (hchild)
	{
		TravelTree(pTree, hchild, szChecked);
		hchild = pTree->GetNextSiblingItem(hchild);
	}
}