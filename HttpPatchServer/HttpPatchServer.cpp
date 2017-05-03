
// HttpPatchServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "HttpPatchServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHttpPatchServerApp

BEGIN_MESSAGE_MAP(CHttpPatchServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

Fun_OpenSkinA OpenSkinA = nullptr;
Fun_FreeSkin FreeSkin = nullptr;
app_config appconfig;


// CHttpPatchServerApp ����

IDUIRes *AfxGetDuiRes()
{
	return theApp.m_pDuiRes;
}

LPCSTR AfxGetAppTitle()
{
	//return theApp.m_szWindowText.c_str();
	return "";
}


// Ψһ��һ�� CHttpPatchServerApp ����

CHttpPatchServerApp theApp;


CHttpPatchServerApp::CHttpPatchServerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	m_pDuiRes = nullptr;


	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��

	GetAppRootPath();
}


// CHttpPatchDownLoaderApp ��ʼ��
void CHttpPatchServerApp::Initlog()
{
	int lvl = GetPrivateProfileIntA("DEBUG", "LEVEL", -1, appconfig.m_szConfigFile.c_str());
	if (lvl >= 0)
	{
		if (vrvlog::log::get().init(appconfig.m_szLogPath))
		{
			vrvlog::log::get().get_log()->flush_on((spdlog::level::level_enum)lvl);
			vrvlog::log::get().get_log()->set_level((spdlog::level::level_enum)lvl);
		}
	}
}




// CHttpPatchServerApp ��ʼ��

BOOL CHttpPatchServerApp::GetAppRootPath()
{
	CHAR szAppPath[MAX_PATH] = { 0 };
	if (GetModuleFileNameA(NULL, szAppPath, MAX_PATH) == 0)
		return FALSE;
	CHAR * pTail = strrchr(szAppPath, '\\');
	if (NULL != pTail)
		strcpy_s(pTail, 1, "");
	m_szPath = szAppPath;
	return TRUE;
}

void StringtoMapOfProduct(std::string str, const char* szDelim, m_publishers& op_products)
{
	char* sztok = nullptr, *sznxt = nullptr;
	sztok = strtok_s(const_cast<char*>(str.c_str()), szDelim, &sznxt);
	while (sztok)
	{
		std::string szCompany, szProduct, szPackage;
		std::string szItem = sztok;
		auto pos1 = szItem.find_first_of('-');
		if (pos1 != std::string::npos)
		{
			szCompany = szItem.substr(0, pos1);
			std::transform(szCompany.begin(), szCompany.end(), szCompany.begin(), toupper);
		}

		auto pos2 = szItem.find_first_of('-', pos1 + 1);
		if (pos2 != std::string::npos)
		{
			szProduct = szItem.substr(pos1 + 1, pos2 - pos1 - 1);
			std::transform(szProduct.begin(), szProduct.end(), szProduct.begin(), toupper);
		}

		szPackage = szItem.substr(pos2 + 1);

		auto iter = op_products._inner_companys.find(szCompany);
		if (iter == op_products._inner_companys.end())
		{
			auto _pair = op_products._inner_companys.insert(std::make_pair(szCompany, m_familys()));
			iter = _pair.first;
		}

		m_familys &familys = iter->second;

		auto iter_ = familys._inner_familys.find(szProduct);
		if (iter_ == familys._inner_familys.end())
		{
			auto _pair = familys._inner_familys.insert(std::make_pair(szProduct, v_products()));
			iter_ = _pair.first;
		}

		v_products &pdu = iter_->second;
		pdu._inner_products.push_back(szPackage);

		sztok = strtok_s(NULL, ";", &sznxt);
	}
}


BOOL CHttpPatchServerApp::InitAppConfig()
{
	CHAR szModulePath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, szModulePath, MAX_PATH);
	appconfig.m_szAppPath = szModulePath;
	std::string &apppath = appconfig.m_szAppPath;
	apppath = apppath.substr(0, apppath.find_last_of('\\'));
	appconfig.m_szConfigFile = apppath + "\\Cfig\\HttpPatchCfig.ini";
	appconfig.m_szLogPath = apppath + "\\httplog";
	appconfig.m_downloadcfg.tmode = (time_mode)GetPrivateProfileIntA("DOWNOPTION", "MODE", -1, appconfig.m_szConfigFile.c_str());
	/*if (appconfig.m_downloadcfg.tmode == period_mode)*/
	{
		appconfig.m_downloadcfg.time.period.period_min = \
			GetPrivateProfileIntA("DOWNOPTION", "PERIOD", 0, appconfig.m_szConfigFile.c_str());
	}
	/*else if (appconfig.m_downloadcfg.tmode == interval_mode)*/
	{
		appconfig.m_downloadcfg.time.interval.hour_start = \
			GetPrivateProfileIntA("DOWNOPTION", "BEGIN_HOUR", 0, appconfig.m_szConfigFile.c_str());
		appconfig.m_downloadcfg.time.interval.min_start = \
			GetPrivateProfileIntA("DOWNOPTION", "BEGIN_MIN", 0, appconfig.m_szConfigFile.c_str());
		appconfig.m_downloadcfg.time.interval.hour_end = \
			GetPrivateProfileIntA("DOWNOPTION", "END_HOUR", 0, appconfig.m_szConfigFile.c_str());
		appconfig.m_downloadcfg.time.interval.min_end = \
			GetPrivateProfileIntA("DOWNOPTION", "END_MIN", 0, appconfig.m_szConfigFile.c_str());
	}

	appconfig.m_downloadcfg.rate = GetPrivateProfileIntA("DOWNOPTION", "RATE", 0, appconfig.m_szConfigFile.c_str());

	appconfig.m_downloadcfg.bproxy = (bool)GetPrivateProfileIntA("DOWNOPTION", "PROXY", 0, appconfig.m_szConfigFile.c_str());
	if (appconfig.m_downloadcfg.bproxy == 1)
	{
		CHAR szparam[100] = { 0 };
		GetPrivateProfileStringA("DOWNOPTION", "PROXY_IP", "", szparam, 100, appconfig.m_szConfigFile.c_str());
		appconfig.m_downloadcfg.proxyparam.szIp = szparam;
		appconfig.m_downloadcfg.proxyparam.uPort = \
			GetPrivateProfileIntA("DOWNOPTION", "PROXY_PORT", 0, appconfig.m_szConfigFile.c_str());
		GetPrivateProfileStringA("DOWNOPTION", "PROXY_USER", "", szparam, 100, appconfig.m_szConfigFile.c_str());
		appconfig.m_downloadcfg.proxyparam.szUser = szparam;
		GetPrivateProfileStringA("DOWNOPTION", "PROXY_PWD", "", szparam, 100, appconfig.m_szConfigFile.c_str());
		appconfig.m_downloadcfg.proxyparam.szPwd = szparam;
	}
	CHAR szopt[MAX_PATH] = { 0 };
	GetPrivateProfileStringA("PATCHOPTION", "PATCH_PATH", "", szopt, MAX_PATH, appconfig.m_szConfigFile.c_str());
	appconfig.m_patch_opt.m_szPatchPath = szopt;
	if (!appconfig.m_patch_opt.m_szPatchPath.empty())
		appconfig.m_patch_opt.m_szIndexPath = appconfig.m_patch_opt.m_szPatchPath + "\\Tools";

	GetPrivateProfileStringA("PATCHOPTION", "INDEX_URL", "", szopt, MAX_PATH, appconfig.m_szConfigFile.c_str());
	appconfig.m_patch_opt.szUrl = szopt;
	std::replace(appconfig.m_patch_opt.szUrl.begin(), appconfig.m_patch_opt.szUrl.end(), '\\', '/');
	appconfig.m_patch_opt.szPackIndex = appconfig.m_patch_opt.szUrl.substr(appconfig.m_patch_opt.szUrl.find_last_of('/') + 1);

	CHAR szProducts[1024 * 5] = { 0 };
	GetPrivateProfileStringA("PATCHOPTION", "PATCH_PRODUCTS", "", szProducts, 1024 * 5, appconfig.m_szConfigFile.c_str());

	StringtoMapOfProduct(szProducts, ";", appconfig.m_patch_opt.m_inst_products);

	GetPrivateProfileStringA("PATCHOPTION", "PATCH_LANG", "", szProducts, 1024 * 5, appconfig.m_szConfigFile.c_str());
	StringtoMapOfProduct(szProducts, ";", appconfig.m_patch_opt.m_inst_products);

	CHAR szWndTitle[200] = { 0 };
	GetPrivateProfileStringA("TITLE", "MAINTITLE", "", szWndTitle, 200, appconfig.m_szConfigFile.c_str());
	appconfig.m_szAppTitle = szWndTitle;
	return TRUE;
}


BOOL CHttpPatchServerApp::InitDUI()
{
	std::string szDuiDllPath = m_szPath + "\\DirectUI.dll";
	std::string szDuiPath = m_szPath + "\\skin\\PatchDown.dui";
	std::string szSknPath = m_szPath + "\\skin\\PatchDown.skn";
	HMODULE hDuiDll = LoadLibraryA(szDuiDllPath.c_str());
	if (NULL == hDuiDll)
	{
		::MessageBox(NULL, _T("LoadLibrary DirectUI.dll Fail!"), _T("ERROR"), MB_OK);
		return FALSE;
	}
	OpenSkinA = (Fun_OpenSkinA)GetProcAddress(hDuiDll, "OpenSkinA");
	FreeSkin = (Fun_FreeSkin)GetProcAddress(hDuiDll, "FreeSkin");
	if (NULL == OpenSkinA || NULL == FreeSkin)
	{
		::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Get DUI FUN Fail!"), _T("ERROR"), MB_OK);
		return FALSE;
	}

	m_pDuiRes = OpenSkinA(const_cast<char*>(szDuiPath.c_str()), const_cast<char*>(szSknPath.c_str()), FALSE, FALSE, TRUE);
	if (NULL == m_pDuiRes)
	{
		::MessageBox(NULL, _T("LoadLibrary Skin Fail!"), _T("ERROR"), MB_OK);
		return FALSE;
	}
	return TRUE;
}

BOOL CHttpPatchServerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	curl_global_init(CURL_GLOBAL_WIN32);

	InitAppConfig();

	Initlog();

	if (!CPackInterface::init())
		return FALSE;

	if (!InitDUI())
		return FALSE;


	CHttpPatchServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CHttpPatchServerApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	curl_global_cleanup();
	if(FreeSkin)
		FreeSkin();
	return CWinApp::ExitInstance();
}
