
// HttpPatchServer.cpp : 定义应用程序的类行为。
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


// CHttpPatchServerApp 构造

IDUIRes *AfxGetDuiRes()
{
	return theApp.m_pDuiRes;
}

LPCSTR AfxGetAppTitle()
{
	//return theApp.m_szWindowText.c_str();
	return "";
}


// 唯一的一个 CHttpPatchServerApp 对象

CHttpPatchServerApp theApp;


CHttpPatchServerApp::CHttpPatchServerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	m_pDuiRes = nullptr;


	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中

	GetAppRootPath();
}


// CHttpPatchDownLoaderApp 初始化
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




// CHttpPatchServerApp 初始化

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
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CHttpPatchServerApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	curl_global_cleanup();
	if(FreeSkin)
		FreeSkin();
	return CWinApp::ExitInstance();
}
