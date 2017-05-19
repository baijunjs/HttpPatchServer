
// HttpPatchServer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "HttpPatchServerDlg.h"
#include "sha1.h"
#include "Base64.h"
#include <boost/make_shared.hpp>
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern bool g_bstop;

void onServerFileDownload(RCF::RcfSession & session, const RCF::FileDownloadInfo & uploadInfo)
{
	// Which files are being downloaded.
	const RCF::FileManifest& manifest = uploadInfo.mManifest;
	// How far has the download progressed.
	boost::uint32_t currentFile = uploadInfo.mCurrentFile;
	boost::uint64_t currentFilePos = uploadInfo.mCurrentPos;
}


// CHttpPatchServerApp

BEGIN_MESSAGE_MAP(CHttpPatchServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

app_config appconfig;

RCF::RcfInitDeinit rcfInit;

// CHttpPatchServerApp 构造

LPCTSTR AfxGetAppTitle()
{
	return _T("");
}


BOOL GetFileSHA1(std::tstring szFile, OUT std::tstring &szSha)
{
	size_t stlen = 0;
	TCHAR szSHA1Value[0x80] = { 0 };
	CHAR szHash[20] = { 0 };
	CHAR szBase64Out[0x80] = { 0 };
	CSHA1 calcSha;
	if (calcSha.HashFile(szFile.c_str()))
	{
		calcSha.Final();
		if (calcSha.ReportHash(szSHA1Value, calcSha.REPORT_DIGIT))
		{
			calcSha.GetHash((unsigned char *)szHash);
			encode_base64((const char*)szHash, 20, (char*)szBase64Out, 0x80 , &stlen);
			szSha = (const TCHAR*)_bstr_t(szBase64Out);
			return TRUE;
		}
	}
	return FALSE;
}


// 唯一的一个 CHttpPatchServerApp 对象

CHttpPatchServerApp theApp;


CHttpPatchServerApp::CHttpPatchServerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中

	GetAppRootPath();
}


// CHttpPatchDownLoaderApp 初始化
void CHttpPatchServerApp::Initlog()
{
	if (appconfig.m_other_cfg.enable)
	{
		if (vrvlog::log::get().init((const char*)_bstr_t(appconfig.m_szLogPath.c_str())))
		{
			vrvlog::log::get().get_log()->flush_on((spdlog::level::level_enum)appconfig.m_other_cfg.level);
			vrvlog::log::get().get_log()->set_level((spdlog::level::level_enum)appconfig.m_other_cfg.level);
		}
	}
}


void CHttpPatchServerApp::InitPatchServer()
{
	try
	{
		server = std::make_shared<RCF::RcfServer>(RCF::TcpEndpoint("0.0.0.0",
			appconfig.m_cascade_cfg.localserverport));
		server->bind<MyService>(myservice);
		server->setOnFileDownloadProgress(&onServerFileDownload);
		server->getServerTransport().setConnectionLimit(50);
		RCF::ThreadPoolPtr tpPtr = boost::make_shared<RCF::ThreadPool>(1, 10);
		server->setThreadPool(tpPtr);
		server->start();
	}
	catch (RCF::Exception &e)
	{
		vrvlog::SPD_LOG_CRITICAL("Init rcf server failed ({0})", e.getErrorId());
		exit(-1);
	}

}


bool CHttpPatchServerApp::InitPatchClient()
{
	int port;
	std::tstringstream ss;
	ss << appconfig.m_cascade_cfg.szupserverport;
	ss >> port;
	std::tstring &szip = appconfig.m_cascade_cfg.szupserverip;
	client = std::make_shared<RcfClient<MyService>>(RCF::TcpEndpoint((const char*)_bstr_t(szip.c_str()), port));
	client->getClientStub().setRemoteCallTimeoutMs(120000);
	client->getClientStub().setConnectTimeoutMs(20000);
	client->getClientStub().setTransferWindowS(1);
	fileDownload = std::make_shared<RCF::FileDownload>();
	//测试远端服务器能否正常连接
	try
	{
		int c = theApp.client->add(1, 2);
	}
	catch (RCF::Exception& e)
	{
		vrvlog::SPD_LOG_ERROR("Remote call failed {0} {1}",
			e.getErrorId(), e.getWhat());
		return false;
	}
	return true;
}



// CHttpPatchServerApp 初始化

BOOL CHttpPatchServerApp::GetAppRootPath()
{
	TCHAR szAppPath[MAX_PATH] = { 0 };
	if (GetModuleFileName(NULL, szAppPath, MAX_PATH) == 0)
		return FALSE;
	TCHAR * pTail = _tcsrchr(szAppPath, _T('\\'));
	if (NULL != pTail)
		_tcscpy_s(pTail, 1, _T(""));
	appconfig.m_szAppPath = szAppPath;
	return TRUE;
}

BOOL CHttpPatchServerApp::InitAppConfig()
{
	TCHAR szPath[MAX_PATH] = { 0 };
	if (!SHGetSpecialFolderPath(NULL, szPath, CSIDL_APPDATA, TRUE))
		return FALSE;

	std::tstring szTempPath = szPath;
	szTempPath.append(_T("\\PatchServer"));
	if (!PathFileExists(szTempPath.c_str()))
	{
		CreateDirectory(szTempPath.c_str(), NULL);
	}

	appconfig.m_szConfigFile = szTempPath + _T("\\setup.ini");
	if (!PathFileExists(appconfig.m_szConfigFile.c_str()))
	{
		std::tstring &szconfig = appconfig.m_szConfigFile;

		WritePrivateProfileString(_T("PATCH"), _T("URL"), _T("http://www.vrvsoft.com/update/patch/newpatch/PackIndex.dat"), szconfig.c_str());
		WritePrivateProfileString(_T("PATCH"), _T("PATH"), _T("C:\\vrv\\RegionManage\\Distribute\\Patch"), szconfig.c_str());
		WritePrivateProfileString(_T("PATCH"), _T("PRODUCTS"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("PATCH"), _T("LAN"), _T(""), szconfig.c_str());

		WritePrivateProfileString(_T("NET"), _T("TIMEMODE"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("NETTIME"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("FLUX"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("FLUXSPEED"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("PROXY"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("PROXYIP"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("PROXYPORT"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("PROXYUSER"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("NET"), _T("PROXYPWD"), _T(""), szconfig.c_str());

		WritePrivateProfileString(_T("CASCADE"), _T("DBIP"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("DBSRC"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("DBUSER"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("DBPWD"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("CASCADE"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("UPSERVERIP"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("UPSERVERPORT"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("TIMEMODE"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("NETTIME"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("FLUX"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("FLUXSPEED"), _T("0"), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("PATH"), _T(""), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("LOCALPORT"), _T("6998"), szconfig.c_str());
		WritePrivateProfileString(_T("CASCADE"), _T("INDEX1"), _T("1"), szconfig.c_str());

		WritePrivateProfileString(_T("SWITCHMODE"), _T("MODE"), _T("0"), szconfig.c_str());

		WritePrivateProfileString(_T("DEBUG"), _T("LOG"), _T("1"), szconfig.c_str());
		WritePrivateProfileString(_T("DEBUG"), _T("LEVEL"), _T("4"), szconfig.c_str());
		WritePrivateProfileString(_T("LANGUAGE"), _T("DEFAULT"), _T("EN"), szconfig.c_str());

	}

	appconfig.m_szLogPath = szTempPath + _T("\\log");

	return TRUE;
}


void  CHttpPatchServerApp::ReadConfig()
{
#define MAX_LEN			500

	std::tstring &szconfig = appconfig.m_szConfigFile;
	TCHAR szBuff[500] = { 0 };
	GetPrivateProfileString(_T("PATCH"), _T("URL"), _T("http://www.vrvsoft.com/update/patch/newpatch/PackIndex.dat"), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szIndexUrl = szBuff;

	GetPrivateProfileString(_T("PATCH"), _T("PATH"), _T("C:\\vrv\\RegionManage\\Distribute\\Patch"), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szPatchPath = szBuff;

	GetPrivateProfileString(_T("PATCH"), _T("PRODUCTS"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szProducts = szBuff;

	GetPrivateProfileString(_T("PATCH"), _T("LAN"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szLans = szBuff;

	appconfig.m_http_cfg.mode = (timemode)GetPrivateProfileInt(_T("NET"), _T("TIMEMODE"), 0, szconfig.c_str());

	GetPrivateProfileString(_T("NET"), _T("NETTIME"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.sznettime = szBuff;

	appconfig.m_http_cfg.flux = (bool)GetPrivateProfileInt(_T("NET"), _T("FLUX"), 0, szconfig.c_str());

	appconfig.m_http_cfg.fluxspeed = GetPrivateProfileInt(_T("NET"), _T("FLUXSPEED"), 0, szconfig.c_str());

	appconfig.m_http_cfg.proxy = GetPrivateProfileInt(_T("NET"), _T("PROXY"), 0, szconfig.c_str());

	GetPrivateProfileString(_T("NET"), _T("PROXYIP"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szip = szBuff;

	GetPrivateProfileString(_T("NET"), _T("PROXYPORT"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szport = szBuff;

	GetPrivateProfileString(_T("NET"), _T("PROXYUSER"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szuser = szBuff;

	GetPrivateProfileString(_T("NET"), _T("PROXYPWD"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szpwd = szBuff;

	GetPrivateProfileString(_T("CASCADE"), _T("DBIP"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbip = szBuff;

	GetPrivateProfileString(_T("CASCADE"), _T("DBSRC"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbsrc = szBuff;

	GetPrivateProfileString(_T("CASCADE"), _T("DBUSER"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbuser = szBuff;

	GetPrivateProfileString(_T("CASCADE"), _T("DBPWD"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbpwd = szBuff;

	appconfig.m_cascade_cfg.cascade = (bool)GetPrivateProfileInt(_T("CASCADE"), _T("CASCADE"), 0, szconfig.c_str());

	GetPrivateProfileString(_T("CASCADE"), _T("UPSERVERIP"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szupserverip = szBuff;

	GetPrivateProfileString(_T("CASCADE"), _T("UPSERVERPORT"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szupserverport = szBuff;

	appconfig.m_cascade_cfg.mode = (timemode)GetPrivateProfileInt(_T("CASCADE"), _T("TIMEMODE"), 0, szconfig.c_str());

	GetPrivateProfileString(_T("CASCADE"), _T("NETTIME"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.sznettime = szBuff;

	appconfig.m_cascade_cfg.flux = (bool)GetPrivateProfileInt(_T("CASCADE"), _T("FLUX"), 0, szconfig.c_str());

	appconfig.m_cascade_cfg.fluxspeed = GetPrivateProfileInt(_T("CASCADE"), _T("FLUXSPEED"), 0, szconfig.c_str());

	GetPrivateProfileString(_T("CASCADE"), _T("PATH"), _T(""), szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szPatchPath = szBuff;

	appconfig.m_cascade_cfg.localserverport = GetPrivateProfileInt(_T("CASCADE"), _T("LOCALPORT"), 6998, szconfig.c_str());
	appconfig.m_cascade_cfg.index1 = GetPrivateProfileInt(_T("CASCADE"), _T("INDEX1"), 1, szconfig.c_str());


	appconfig.m_mode_cfg.mode = (switchmode)GetPrivateProfileInt(_T("SWITCHMODE"), _T("MODE"), 0, szconfig.c_str());

	appconfig.m_other_cfg.enable = (bool)GetPrivateProfileInt(_T("DEBUG"), _T("LOG"), 1, szconfig.c_str());
	appconfig.m_other_cfg.level = GetPrivateProfileInt(_T("DEBUG"), _T("LEVEL"), 4, szconfig.c_str());

	GetPrivateProfileString(_T("LANGUAGE"), _T("DEFAULT"), _T("EN"), szBuff, MAX_LEN, szconfig.c_str());
	if (_tcsicmp(szBuff, _T("ZHCN")) == 0)
		appconfig.m_other_cfg.lang = ZHCN;
	else
		appconfig.m_other_cfg.lang = EN;

}

void CHttpPatchServerApp::InitLanguage()
{
	std::tstring szLangPro = appconfig.m_szAppPath + _T("\\Skin\\lang.ini");
	language lang = (language)appconfig.m_other_cfg.lang;
	g_lang.ReadProfile(szLangPro, lang);
}

#define SYNSVR_RPT_DOWN_PATCH	196

BOOL CHttpPatchServerApp::ReportToManager(std::string &szlog)
{
	static HMODULE h_log = LoadLibrary(_T("EdpCMCore.dll"));
	if (h_log)
	{
		static AcquireContext m_pAcquireContext = (AcquireContext)GetProcAddress(h_log, "AcquireContext");
		static SendCmdAndData m_pSendCmdAndData = (SendCmdAndData)GetProcAddress(h_log, "SendCmdAndData");
		static RecvEcho m_pRecvEcho = (RecvEcho)GetProcAddress(h_log, "RecvEcho");
		static CloseContext m_pCloseContext = (CloseContext)GetProcAddress(h_log, "CloseContext");

		if (!m_pAcquireContext || !m_pSendCmdAndData || !m_pRecvEcho || !m_pCloseContext)
			return FALSE;

		HANDLE hctx = NULL;
		do
		{
			hctx = m_pAcquireContext("127.0.0.1", 88, 3000, 3000);
			if (hctx == NULL)
				break;

			if (!m_pSendCmdAndData(hctx, SYNSVR_RPT_DOWN_PATCH, 0, TRUE, (LPVOID)szlog.c_str(), szlog.length(), TRUE))
				break;

			if (!m_pRecvEcho(hctx, 0, 0, TRUE, NULL, NULL))
				break;

			m_pCloseContext(hctx);

			return TRUE;
		} while (false);

		if (hctx)
			m_pCloseContext(hctx);
	}
	return FALSE;
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

	if (!InitAppConfig())
		return FALSE;

	ReadConfig();

	Initlog();

	InitPatchServer();

	InitLanguage();

	if (!CPackInterface::init())
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
		TRACE(traceAppMsg, 0, _T("警告: 对话框创建失败，应用程序将意外终止。\n"));
		TRACE(traceAppMsg, 0, _T("警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n"));
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
	if (server)
		server->stop();
	//if(FreeSkin)
		//FreeSkin();
	return CWinApp::ExitInstance();
}



void CHttpPatchServerApp::StopByCurl()
{
	if (theApp.m_curlptr)
		theApp.m_curlptr->StopDownload();
}


void CHttpPatchServerApp::StopByRcf()
{
	try
	{
		if (theApp.client)
			theApp.client->getClientStub().disconnect();
	}
	catch (RCF::Exception &e)
	{
		vrvlog::SPD_LOG_ERROR("RcfClient disconnect error({0})", e.getErrorId());
	}
}


BOOL MakeSureDirectoryExist(const TCHAR *pszPath, BOOL bFilePath)
{
	std::tstring szPath = pszPath;
	if (bFilePath)
		szPath = szPath.substr(0, szPath.find_last_of('\\'));

	if (!PathIsDirectory(szPath.c_str()))
	{
		std::tstring szParentPath;
		std::tstring szFullPath = szPath;
		auto pos = szFullPath.find_last_of(_T("\\"));
		if (pos != std::tstring::npos)
			szParentPath = szFullPath.substr(0, pos);
		if (MakeSureDirectoryExist(szParentPath.c_str(), FALSE))
			return CreateDirectory(szPath.c_str(), NULL);
		else
			return FALSE;
	}
	return TRUE;
}



int CPatchServiceImpl::add(int a, int b)
{
	return a + b;
}

void  CPatchServiceImpl::RequestPatchInfo(std::vector<vrv::patch::PatchInfo> &patches)
{
	std::lock_guard<std::mutex> locker(mtxforpatch);

	if (appconfig.m_mode_cfg.mode == http_mode)
		szPatchpath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPatchpath = appconfig.m_cascade_cfg.szPatchPath;

	TravelPatchPath(szPatchpath + _T("\\chinese"), patches);
	TravelPatchPath(szPatchpath + _T("\\english"), patches);
}


void CPatchServiceImpl::RequestPatchInfo(vrv::patch::PatchInfo &patch)
{
	std::tstring szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath;

	std::tstring szPatchFile = szPath + _T("\\") + patch.szPatchName;
	std::tstringstream ss;
	std::ifstream ifs(szPatchFile);
	if (ifs.is_open())
	{
		ifs.seekg(0, ifs.end);
		std::streamoff len = ifs.tellg();
		ss << len;
		patch.szPatchSize = ss.str();
	}

	GetFileSHA1(patch.szPatchName, patch.szMd5);
}

void CPatchServiceImpl::RequestIndexInfo(std::vector<vrv::patch::IndexInfo> &indexes)
{
	std::lock_guard<std::mutex> locker(mtxforindex);

	if (appconfig.m_mode_cfg.mode == http_mode)
		szToolpath = appconfig.m_http_cfg.m_szPatchPath + _T("\\Tools");

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szToolpath = appconfig.m_cascade_cfg.szPatchPath + _T("\\Tools");

	TravelIndexPath(szToolpath, indexes);
}

void  CPatchServiceImpl::DownloadFiles(std::tstring& szFile, RCF::FileDownload &fileDownload)
{
	fileDownload = RCF::FileDownload((const char*)_bstr_t(szFile.c_str()));
}

void  CPatchServiceImpl::DownloadIndexFile(std::tstring& szFile, RCF::FileDownload &fileDownload)
{
	std::tstring szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath + _T("\\Tools");

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath + _T("\\Tools");

	std::tstring szIndexFile = szPath + _T("\\") + szFile;
	fileDownload = RCF::FileDownload((const char*)_bstr_t(szIndexFile.c_str()));
}

void  CPatchServiceImpl::DownloadPatchFile(std::tstring& szFile, RCF::FileDownload &fileDownload)
{
	std::tstring szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath;

	std::tstring szPatchFile = szPath + _T("\\") + szFile;
	fileDownload = RCF::FileDownload((const char*)_bstr_t(szPatchFile.c_str()));
}

void  CPatchServiceImpl::DownloadIndex1xml(RCF::FileDownload &fileDownload)
{
	std::tstring szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath;

	std::tstring szIndex1Xml = szPath + _T("\\index1.xml");
	std::tstring szIndex1Zip = szPath + _T("\\index1.zip");
	if (PathFileExists(szIndex1Zip.c_str()))
		fileDownload = RCF::FileDownload((const char*)_bstr_t(szIndex1Xml.c_str()));
	else
		throw RCF::Exception(RCF::_RcfError_FileOpen((const char*)_bstr_t(szIndex1Zip.c_str())));
}

void  CPatchServiceImpl::TravelIndexPath(std::tstring &szPath, std::vector<vrv::patch::IndexInfo> &indexes)
{
	std::tstring szFindPath = szPath + _T("\\*.*");
	_tfinddata32_t data = { 0 };
	intptr_t handle = _tfindfirst32(szFindPath.c_str(), &data);
	if (handle == -1)
		return;
	do
	{
		if (data.attrib & _A_SUBDIR)
		{
			if (_tcsicmp(data.name, _T(".")) && _tcsicmp(data.name, _T("..")))
				TravelIndexPath(szPath + _T("\\") + data.name, indexes);
		}
		else
		{
			std::tstring szName = data.name;
			if (!szName.empty() && szName.back() != '~')
			{
				vrv::patch::IndexInfo indexInfo;
				indexInfo.size = data.size;
				indexInfo.szIndexName = szPath + _T("\\") + data.name;
				indexInfo.dwCrc = GetFileCrc(indexInfo.szIndexName.c_str());
				indexInfo.szIndexName = indexInfo.szIndexName.substr(szToolpath.length() + 1);
				indexes.push_back(indexInfo);
			}
		}

	} while (!_tfindnext32(handle, &data));
	_findclose(handle);
}

void  CPatchServiceImpl::GetIndexInfo(std::tstring &szFile, vrv::patch::IndexInfo& indexinfo)
{
	std::ifstream ifs(szFile);
	if (ifs.is_open())
	{
		ifs.seekg(0, ifs.end);
		std::streamoff len = ifs.tellg();
		indexinfo.size = len;
		indexinfo.szIndexName = szFile;
	}
	indexinfo.dwCrc = GetFileCrc(szFile.c_str());
}

void  CPatchServiceImpl::TravelPatchPath(std::tstring &szPath, std::vector<vrv::patch::PatchInfo> &patches)
{
	std::tstring szFindPath = szPath + _T("\\*.*");
	_tfinddata32_t data = { 0 };
	intptr_t handle = _tfindfirst32(szFindPath.c_str(), &data);
	if (handle == -1)
		return;
	do
	{
		if (data.attrib & _A_SUBDIR)
		{
			if (_tcsicmp(data.name, _T(".")) && _tcsicmp(data.name, _T("..")))
				TravelPatchPath(szPath + _T("\\") + data.name, patches);
		}
		else
		{
			std::tstring szName = data.name;
			if (!szName.empty() && szName.back() != '~')
			{
				std::tstringstream ss;
				ss << data.size;
				vrv::patch::PatchInfo patchInfo;
				patchInfo.szPatchSize = ss.str();
				patchInfo.szPatchName = szPath + _T("\\") + data.name;
				GetFileSHA1(patchInfo.szPatchName, patchInfo.szMd5);
				patchInfo.szPatchName = patchInfo.szPatchName.substr(szPatchpath.length() + 1);
				patches.push_back(patchInfo);
			}
		}

	} while (!_tfindnext32(handle, &data));
	_findclose(handle);
}

void  CPatchServiceImpl::GetPatchInfo(std::tstring &szFile, vrv::patch::PatchInfo& patchInfo)
{
	std::tstringstream ss;
	std::ifstream ifs(szFile);
	if (ifs.is_open())
	{
		ifs.seekg(0, ifs.end);
		std::streamoff len = ifs.tellg();
		ss << len;
		patchInfo.szPatchSize = ss.str();
		patchInfo.szPatchName = szFile;
	}

	GetFileSHA1(patchInfo.szPatchName, patchInfo.szMd5);
}


BOOL CPatchServiceImpl::ReportToServer(std::tstring& szUpdateId, std::tstring &szPatchName)
{
	std::tstring szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath;

	RCF::RcfSession &session = RCF::getCurrentRcfSession();
	std::string szIpAddress = session.getClientAddress().string();
	std::string::size_type pos = szIpAddress.find(":");
	if (pos != std::string::npos)
		szIpAddress = szIpAddress.substr(0, pos);
	std::tstringstream ss;
	ss << _T("IP=") << (const TCHAR*)_bstr_t(szIpAddress.c_str()) 
		<< _T("\r\nUpdateId=") << szUpdateId 
		<< _T("\r\nPatchName=") << szPath + _T("\\") + szPatchName << _T("\r\n");

	return theApp.ReportToManager(std::string((const char*)_bstr_t(ss.str().c_str())));
}