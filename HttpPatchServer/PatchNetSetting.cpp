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
	ON_MESSAGE(DUITREE_CHECKITEM, &CPatchNetSetting::OnTreeCheckItem)
END_MESSAGE_MAP()


// CPatchNetSetting 消息处理程序

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

	return 0;
}

void GetTime(std::tstring& szTime, std::tstring &szHour, std::tstring &szMin, std::tstring &szSec)
{
	std::tregex rgx(_T("(\\d{1,2}):(\\d{0,2}):(\\d{0,2})"));
	std::tsmatch sm;
	if (std::regex_match(szTime, sm, rgx))
	{
		if (sm.size() >= 4)
		{
			szHour = sm[1];
			szMin = sm[2];
			szSec = sm[3];
		}
	}

	if (szHour.empty()) szHour = _T("00");
	if (szMin.empty()) szMin = _T("00");
	if (szSec.empty()) szSec = _T("00");
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
			std::tstring szbegin, szend;
			//std::tstring szbegH, szbegM, szbegS, szendH, szendM, szendS;
			GetIntervalTime(appconfig.m_http_cfg.sznettime, szbegin, szend);
			//szbegin = szbegH + ":" + szbegM;
			//szend = szendH + ":" + szendM;
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
	std::tstringstream ss;
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
	InitControlLang();
	InitControlData();
	EnbaleControl();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL IsTimeValid(std::tstring &sztime)
{
	std::tregex rgx(_T("(\\d{1,2}):(\\d{0,2}):(\\d{0,2})"));
	std::tsmatch sm;
	if (std::regex_match(sztime, sm, rgx))
	{
		if (sm.size() >= 3)
		{
			std::tstring szHour = sm[1];
			std::tstring szMin = sm[2];
			std::tstring szSec = sm[3];

			int iHour = _ttoi(szHour.c_str());
			int iMin = _ttoi(szMin.c_str());
			int iSec = _ttoi(szMin.c_str());
			if ((iHour >= 0 && iHour < 24)
				&& (iMin >= 0 && iMin <= 59)
				&& (iSec >= 0 && iSec <= 59))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL IsIpValid(std::tstring &szIp)
{
	std::tregex rgx(_T("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})"));
	std::tsmatch sm;
	if (std::regex_match(szIp, sm, rgx))
	{
		if (sm.size() >= 5)
		{
			std::tstring f1 = sm[1];
			std::tstring f2 = sm[2];
			std::tstring f3 = sm[3];
			std::tstring f4 = sm[4];
			int s1 = _ttoi(f1.c_str());
			int s2 = _ttoi(f2.c_str());
			int s3 = _ttoi(f3.c_str());
			int s4 = _ttoi(f4.c_str());
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
	std::tstring sztime = _T("0");
	bool flux = false, proxy = false;
	std::tstring szfluxspeed;
	std::tstring szip, szport, szuser, szpwd;

	if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_AllTime)->GetValue())
		mode = default_mode;

	else if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_Period)->GetValue())
	{
		mode = period_mode;
		sztime = DEdit(EditPerid)->GetText();
		int itime = _ttoi(sztime.c_str());
		if (itime <= 0)
		{
			CMessageBox msg;
			msg.ShowMessage(g_lang.GetText(10070));
			return FALSE;
		}
	}

	else if (DUIRADIOBOX_CHECKED == DRadio(RadioBox_Interval)->GetValue())
	{
		mode = interval_mode;
		std::tstring szbegin = DEdit(EditBegin)->GetText();
		std::tstring szend = DEdit(EditEnd)->GetText();
		if (!IsTimeValid(szbegin))
		{
			CMessageBox msg;
			msg.ShowMessage(g_lang.GetText(10069));
			return FALSE;
		}
		if (!IsTimeValid(szend))
		{
			CMessageBox msg;
			msg.ShowMessage(g_lang.GetText(10068));
			return FALSE;
		}
		sztime = szbegin + _T("-") + szend;
	}

	if (DUICHECKBOX_CHECKED == DCheck(ChkBox-Flux)->GetValue())
	{
		flux = true;
		szfluxspeed = DEdit(EditSpeed)->GetText();
		if (_ttoi(szfluxspeed.c_str()) < 0)
		{
			CMessageBox msg;
			msg.ShowMessage(g_lang.GetText(10065));
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
			msg.ShowMessage(g_lang.GetText(10067));
			return FALSE;
		}
		int iport = _ttoi(szport.c_str());
		if (iport <= 0 || iport > 65535)
		{
			CMessageBox msg;
			msg.ShowMessage(g_lang.GetText(10066));
			return FALSE;
		}
	}

	std::tstring szlastProducts = appconfig.m_http_cfg.m_szProducts, szlastlans = appconfig.m_http_cfg.m_szLans;
	std::tstring &szurl = appconfig.m_http_cfg.m_szIndexUrl = DEdit(EditUrl)->GetText();
	std::tstring &szpath = appconfig.m_http_cfg.m_szPatchPath = DEdit(EditPath)->GetText();
	std::tstring &szproducts = appconfig.m_http_cfg.m_szProducts = GetCheckedItemString(DTree(ProductTree));
	std::tstring &szlans = appconfig.m_http_cfg.m_szLans = GetCheckedItemString(DTree(LanTree));
	std::tstring &szcfgpath = appconfig.m_szConfigFile;

	std::tstring szPackName;
	size_t pos = szurl.find_last_of('/');
	if (pos != std::tstring::npos)
		appconfig.m_http_cfg.m_szPackName = szurl.substr(pos + 1);
	std::tstring szPackPath = szpath + _T("\\Tools\\") + appconfig.m_http_cfg.m_szPackName;
	std::tstring szPackSha;

	CPatchMode *pMode = (CPatchMode*)GetParent();
	CPatchView *pPatchView = (CPatchView *)pMode->GetPatchView();
	CPatchViewStatics *pStaticView = (CPatchViewStatics *)pPatchView->GetStaticView();
	CPatchDownView *pDownView = (CPatchDownView*)pPatchView->GetDownView();

	//if (GetFileSHA1(szPackPath, szPackSha))
	//{

	//	if (szPackSha != bus.GetPackSha1() || szproducts != szlastProducts)
	//	{
	//		pStaticView->DeleteAllItems();
	//		pStaticView->InsertIndexItem();
	//		pStaticView->InsertProductsItems();
	//		bus.SetPackSha1(szPackSha);
	//	}
	//}


	std::tstring &szcfgfile = appconfig.m_szConfigFile;
	timemode &_mode = appconfig.m_http_cfg.mode = mode;
	std::tstring &_time = appconfig.m_http_cfg.sznettime = sztime;
	bool &_flux = appconfig.m_http_cfg.flux = flux;
	int  &_fluxspeed = appconfig.m_http_cfg.fluxspeed = _ttoi(szfluxspeed.c_str());
	bool &_proxy = appconfig.m_http_cfg.proxy = proxy;
	std::tstring &_ip = appconfig.m_http_cfg.szip = szip;
	std::tstring &_port = appconfig.m_http_cfg.szport = szport;
	std::tstring &_user = appconfig.m_http_cfg.szuser = szuser;
	std::tstring &_pwd = appconfig.m_http_cfg.szpwd = szpwd;

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

	std::tstring szMode;
	std::tstringstream ss;
	ss << (int)_mode;
	ss >> szMode;

	WritePrivateProfileString(_T("PATCH"), _T("URL"), szurl.c_str(), szcfgpath.c_str());
	WritePrivateProfileString(_T("PATCH"), _T("PATH"), szpath.c_str(), szcfgpath.c_str());
	WritePrivateProfileString(_T("PATCH"), _T("PRODUCTS"), szproducts.c_str(), szcfgpath.c_str());
	WritePrivateProfileString(_T("PATCH"), _T("LAN"), szlans.c_str(), szcfgpath.c_str());

	WritePrivateProfileString(_T("NET"), _T("TIMEMODE"), szMode.c_str(), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("NETTIME"), _time.c_str(), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("FLUX"), _flux ? _T("1") : _T("0"), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("FLUXSPEED"), szfluxspeed.c_str(), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("PROXY"), _proxy ? _T("1") : _T("0"), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("PROXYIP"), _ip.c_str(), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("PROXYPORT"), _port.c_str(), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("PROXYUSER"), _user.c_str(), szcfgfile.c_str());
	WritePrivateProfileString(_T("NET"), _T("PROXYPWD"), _pwd.c_str(), szcfgfile.c_str());

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
		std::tstring sztime = DEdit(EditPerid)->GetText();
		int itime = _ttoi(sztime.c_str());
		if (itime <= 0)
		{
			DEdit(EditPerid)->DUISetToolTip(g_lang.GetText(10070));
		}
		else
		{
			DEdit(EditPerid)->DUISetToolTip(sztime);
		}
	}
	else if (DEdit(EditBegin) == (IDUIEditCtrl*)wparam)
	{
		std::tstring szbegin = DEdit(EditBegin)->GetText();
		if (!IsTimeValid(szbegin))
		{
			DEdit(EditBegin)->DUISetToolTip(g_lang.GetText(10069));
		}
		else
		{
			DEdit(EditBegin)->DUISetToolTip(szbegin);
		}
	}
	else if (DEdit(EditEnd) == (IDUIEditCtrl*)wparam)
	{
		std::tstring szend = DEdit(EditEnd)->GetText();
		if (!IsTimeValid(szend))
		{
			DEdit(EditEnd)->DUISetToolTip(g_lang.GetText(10068));
		}
		else
		{
			DEdit(EditEnd)->DUISetToolTip(szend);
		}
	}
	else if (DEdit(EditIp) == (IDUIEditCtrl*)wparam)
	{
		std::tstring szip = DEdit(EditIp)->GetText();
		if (!IsIpValid(szip))
		{
			DEdit(EditIp)->DUISetToolTip(g_lang.GetText(10067));
		}
		else
		{
			DEdit(EditIp)->DUISetToolTip(szip);
		}
	}
	else if (DEdit(EditPort) == (IDUIEditCtrl*)wparam)
	{
		std::tstring szport = DEdit(EditPort)->GetText();
		int iport = _ttoi(szport.c_str());
		if (iport <= 0 || iport > 65535)
		{
			DEdit(EditPort)->DUISetToolTip(g_lang.GetText(10066));
		}
		else
		{
			DEdit(EditPort)->DUISetToolTip(szport);
		}
	}
	else if (DEdit(EditSpeed) == (IDUIEditCtrl*)wparam)
	{
		int fluxspeed = _ttoi(DEdit(EditSpeed)->GetText().c_str());
		if (fluxspeed < 0)
		{
			DEdit(EditSpeed)->DUISetToolTip(g_lang.GetText(10065));
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

	std::tstring szpackindex = DEdit(EditPath)->GetText() + _T("\\Tools\\PackIndex.dat");
	if (PathFileExists(szpackindex.c_str()))
	{
		if (!CPackInterface::init())
			return;

		IPackIndex *packindex = CPackInterface::getPackIndexObject();
		if (!bus.analyze_main_index(packindex, szpackindex))
			vrvlog::SPD_LOG_ERROR("{0}parse failed", (const char*)_bstr_t(szpackindex.c_str()));

		else
			vrvlog::SPD_LOG_INFO("{0} parse succeed", (const char*)_bstr_t(szpackindex.c_str()));
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
		std::tstring szPublisher = iter->first;
		OLE_HANDLE hpublisher = pTree->AppendChild(hroot, szPublisher, FALSE);
		vrv::patch::FamiliesMapPtr families = iter->second;
		if (pTree == DTree(ProductTree))
		{
			vrv::patch::FamiliesMap::_iterator _iter = families->ProductsFamily.begin();
			for (; _iter != families->ProductsFamily.end(); ++_iter)
			{
				std::tstring szFamily = _iter->first;
				OLE_HANDLE hfamily = pTree->AppendChild(hpublisher, szFamily, FALSE);
				vrv::patch::ProductsMapPtr products = _iter->second;
				vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
				for (; _iter_ != products->Products.end(); ++_iter_)
				{
					std::tstring szProduct = _iter_->first;
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
				std::tstring szFamily = _iter->first;
				OLE_HANDLE hfamily = pTree->AppendChild(hpublisher, szFamily, FALSE);
				vrv::patch::ProductsMapPtr products = _iter->second;
				vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
				for (; _iter_ != products->Products.end(); ++_iter_)
				{
					std::tstring szProduct = _iter_->first;
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


LRESULT CPatchNetSetting::OnSMLButtonUp(WPARAM wparam, LPARAM lparam)
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
	std::tstring szurl = DEdit(EditUrl)->GetText();
	std::tstring szpatchpath = DEdit(EditPath)->GetText();
	std::tregex rgx(_T("^[A-Za-z]:[\\\\\\w]*"));
	std::tsmatch sm;
	if (!std::regex_match(szpatchpath, sm, rgx))
	{
		CMessageBox msgbox;
		msgbox.ShowMessage(g_lang.GetText(10064));
		return 0;
	}

	std::tstring szPackName;
	size_t pos = szurl.find_last_of('/');
	if (pos != std::tstring::npos)
	{
		szPackName = szurl.substr(pos + 1);
	}

	std::tstring sztoolpath = szpatchpath + _T("\\Tools\\");
	if (!PathFileExists(sztoolpath.c_str()))
		MakeSureDirectoryExist(sztoolpath.c_str(), FALSE);

	std::tstring szpackindex = sztoolpath + szPackName;
	std::tstring sztmppackindex = szpackindex + _T("~");
	std::shared_ptr<Curl> m_curlptr = std::make_shared<Curl>();

	if (appconfig.m_http_cfg.flux)
		m_curlptr->SetDownloadSpeed(appconfig.m_http_cfg.fluxspeed);

	if (appconfig.m_http_cfg.proxy)
		theApp.m_curlptr->SetProxy(
		(const char*)_bstr_t(appconfig.m_http_cfg.szip.c_str()),
			(const char*)_bstr_t(appconfig.m_http_cfg.szport.c_str()),
			(const char*)_bstr_t(appconfig.m_http_cfg.szuser.c_str()),
			(const char*)_bstr_t(appconfig.m_http_cfg.szpwd.c_str()));

	m_curlptr->SetUrlFile((const char*)_bstr_t(szurl.c_str()),
		(const char*)_bstr_t(sztmppackindex.c_str()));

	long code = 0l;
	if (0 == (code = m_curlptr->StartDownload()))
	{
		MoveFileEx(sztmppackindex.c_str(), szpackindex.c_str(), MOVEFILE_REPLACE_EXISTING);
		vrvlog::SPD_LOG_INFO("{0} download succeed", (const char*)_bstr_t(szpackindex.c_str()));
		RedrawSimpleTree();
		RestoreTreeCheckItems(producttree);
		RestoreTreeCheckItems(languagetree);
	}
	else
	{
		vrvlog::SPD_LOG_ERROR("{0} download failed", (const char*)_bstr_t(szpackindex.c_str()));
		CMessageBox msg;
		msg.ShowMessage(g_lang.GetText(10063));
	}

	return 0;
}


LRESULT CPatchNetSetting::OnButtonBrowser(WPARAM wparam, LPARAM lparam)
{
	TCHAR szPath[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = g_lang.GetText(10062).c_str();
	bi.ulFlags = CSIDL_DRIVES;
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;

	LPITEMIDLIST lpIDList = SHBrowseForFolder(&bi);
	if (NULL != lpIDList)
	{
		SHGetPathFromIDList(lpIDList, szPath);
		DEdit(EditPath)->SetText(szPath);
		CreateDirectory(szPath, NULL);
		_tcscat_s(szPath, MAX_PATH, _T("\\Tools"));
		CreateDirectory(szPath, NULL);
		CoTaskMemFree(lpIDList);
	}

	return 0;
}


std::tstring CPatchNetSetting::GetCheckedItemString(IDUISimpleTree* pTree)
{
	std::tstring szChecked = _T(";");
	short schecked = pTree->GetCheckItemCount();

	IDUITreeItem *item = pTree->GetFirstCheckItem();
	while (item)
	{
		OLE_HANDLE hData = pTree->GetItemData(item->GetTreeNode());
		if (hData)
		{
			std::tstring szItemText = pTree->GetItemText(item->GetTreeNode());
			szChecked.append(szItemText);
			szChecked.append(_T(";"));
		}
		item = pTree->GetNextCheckItem(item);
	}

	return szChecked;
}


void CPatchNetSetting::RestoreTreeCheckItems(tree whichtree)
{
	IDUISimpleTree *pTree = NULL;
	std::tstring szXX;
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
	if (szXX.empty() || szXX == _T(";"))
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

void CPatchNetSetting::TravelTree(IDUISimpleTree* pTree, OLE_HANDLE hParent, std::tstring& szChecked)
{
	std::tstring szItemText = pTree->GetItemText(hParent);
	szItemText.append(_T(";")).insert(0, _T(";"));
	if (szChecked.find(szItemText) != std::tstring::npos)
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

void CPatchNetSetting::InitControlLang()
{
	DStatic(Static29)->SetText(g_lang.GetText(10010));
	DStatic(Static26)->SetText(g_lang.GetText(10011));
	DStatic(Sta_Products)->SetText(g_lang.GetText(10014));
	DStatic(Sta_Language)->SetText(g_lang.GetText(10015));
	DRadio(RadioBox_AllTime)->SetText(g_lang.GetText(10016), TRUE);
	DRadio(RadioBox_Period)->SetText(g_lang.GetText(10017), TRUE);
	DRadio(RadioBox_Interval)->SetText(g_lang.GetText(10018), TRUE);
	DStatic(StaticMin)->SetText(g_lang.GetText(10019));
	DCheck(ChkBox-Flux)->SetText(g_lang.GetText(10020));
	DStatic(Static51_Unit)->SetText(g_lang.GetText(10021));
	DCheck(ChkBox-NetProxy)->SetText(g_lang.GetText(10022));
	DStatic(Static_Ip)->SetText(g_lang.GetText(10023));
	DStatic(Static_Port)->SetText(g_lang.GetText(10024));
	DStatic(Static_User)->SetText(g_lang.GetText(10025));
	DStatic(Static_Pwd)->SetText(g_lang.GetText(10026));
	DBtn(BtnTest)->SetText(g_lang.GetText(10012));
	DBtn(BtnBrowser)->SetText(g_lang.GetText(10013));

}