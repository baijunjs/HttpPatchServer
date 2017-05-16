
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

LPCSTR AfxGetAppTitle()
{
	return "";
}


BOOL GetFileSHA1(std::string szFile, OUT std::string &szSha)
{
	size_t stlen = 0;
	char szSHA1Value[0x80] = { 0 };
	char szBase64Out[0x80] = { 0 };
	CSHA1 calcSha;
	if (calcSha.HashFile(szFile.c_str()))
	{
		calcSha.Final();
		if (calcSha.ReportHash(szSHA1Value, calcSha.REPORT_DIGIT))
		{
			calcSha.GetHash((unsigned char *)szSHA1Value);
			encode_base64(szSHA1Value, 20, szBase64Out, 0x80, &stlen);
			szSha = szBase64Out;
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
		if (vrvlog::log::get().init(appconfig.m_szLogPath))
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
	std::stringstream ss;
	ss << appconfig.m_cascade_cfg.szupserverport;
	ss >> port;
	client = std::make_shared<RcfClient<MyService>>(RCF::TcpEndpoint(appconfig.m_cascade_cfg.szupserverip, port));
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
	CHAR szAppPath[MAX_PATH] = { 0 };
	if (GetModuleFileNameA(NULL, szAppPath, MAX_PATH) == 0)
		return FALSE;
	CHAR * pTail = strrchr(szAppPath, '\\');
	if (NULL != pTail)
		strcpy_s(pTail, 1, "");
	appconfig.m_szAppPath = szAppPath;
	return TRUE;
}

BOOL CHttpPatchServerApp::InitAppConfig()
{
	CHAR szPath[MAX_PATH] = { 0 };
	if (!SHGetSpecialFolderPathA(NULL, szPath, CSIDL_APPDATA, TRUE))
	{
		return FALSE;
	}

	std::string szTempPath = szPath;
	szTempPath.append("\\PatchServer");
	if (!PathFileExistsA(szTempPath.c_str()))
	{
		CreateDirectoryA(szTempPath.c_str(), NULL);
	}

	appconfig.m_szConfigFile = szTempPath + "\\setup.ini";
	if (!PathFileExistsA(appconfig.m_szConfigFile.c_str()))
	{
		std::string &szconfig = appconfig.m_szConfigFile;

		WritePrivateProfileStringA("PATCH", "URL", "http://www.vrvsoft.com/update/patch/newpatch/PackIndex.dat", szconfig.c_str());
		WritePrivateProfileStringA("PATCH", "PATH", "", szconfig.c_str());
		WritePrivateProfileStringA("PATCH", "PRODUCTS", "", szconfig.c_str());
		WritePrivateProfileStringA("PATCH", "LAN", "", szconfig.c_str());

		WritePrivateProfileStringA("NET", "TIMEMODE", "0", szconfig.c_str());
		WritePrivateProfileStringA("NET", "NETTIME", "", szconfig.c_str());
		WritePrivateProfileStringA("NET", "FLUX", "0", szconfig.c_str());
		WritePrivateProfileStringA("NET", "FLUXSPEED", "0", szconfig.c_str());
		WritePrivateProfileStringA("NET", "PROXY", "0", szconfig.c_str());
		WritePrivateProfileStringA("NET", "PROXYIP", "", szconfig.c_str());
		WritePrivateProfileStringA("NET", "PROXYPORT", "", szconfig.c_str());
		WritePrivateProfileStringA("NET", "PROXYUSER", "", szconfig.c_str());
		WritePrivateProfileStringA("NET", "PROXYPWD", "", szconfig.c_str());

		WritePrivateProfileStringA("CASCADE", "DBIP", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "DBSRC", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "DBUSER", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "DBPWD", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "CASCADE", "0", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "UPSERVERIP", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "UPSERVERPORT", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "TIMEMODE", "0", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "NETTIME", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "FLUX", "0", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "FLUXSPEED", "0", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "PATH", "", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "LOCALPORT", "6998", szconfig.c_str());
		WritePrivateProfileStringA("CASCADE", "INDEX1", "1", szconfig.c_str());

		WritePrivateProfileStringA("SWITCHMODE", "MODE", "0", szconfig.c_str());

		WritePrivateProfileStringA("DEBUG", "LOG", "1", szconfig.c_str());
		WritePrivateProfileStringA("DEBUG", "LEVEL", "4", szconfig.c_str());
		WritePrivateProfileStringA("LANGUAGE", "DEFAULT", "ZHCN", szconfig.c_str());

	}

	appconfig.m_szLogPath = szTempPath + "\\log";

	return TRUE;
}


void  CHttpPatchServerApp::ReadConfig()
{
#define MAX_LEN			500

	std::string &szconfig = appconfig.m_szConfigFile;
	CHAR szBuff[500] = { 0 };
	GetPrivateProfileStringA("PATCH", "URL", "http://www.vrvsoft.com/update/patch/newpatch/PackIndex.dat", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szIndexUrl = szBuff;

	GetPrivateProfileStringA("PATCH", "PATH", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szPatchPath = szBuff;

	GetPrivateProfileStringA("PATCH", "PRODUCTS", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szProducts = szBuff;

	GetPrivateProfileStringA("PATCH", "LAN", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.m_szLans = szBuff;

	appconfig.m_http_cfg.mode = (timemode)GetPrivateProfileIntA("NET", "TIMEMODE", 0, szconfig.c_str());

	GetPrivateProfileStringA("NET", "NETTIME", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.sznettime = szBuff;

	appconfig.m_http_cfg.flux = (bool)GetPrivateProfileIntA("NET", "FLUX", 0, szconfig.c_str());

	appconfig.m_http_cfg.fluxspeed = GetPrivateProfileIntA("NET", "FLUXSPEED", 0, szconfig.c_str());

	appconfig.m_http_cfg.proxy = GetPrivateProfileIntA("NET", "PROXY", 0, szconfig.c_str());

	GetPrivateProfileStringA("NET", "PROXYIP", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szip = szBuff;

	GetPrivateProfileStringA("NET", "PROXYPORT", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szport = szBuff;

	GetPrivateProfileStringA("NET", "PROXYUSER", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szuser = szBuff;

	GetPrivateProfileStringA("NET", "PROXYPWD", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_http_cfg.szpwd = szBuff;

	GetPrivateProfileStringA("CASCADE", "DBIP", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbip = szBuff;

	GetPrivateProfileStringA("CASCADE", "DBSRC", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbsrc = szBuff;

	GetPrivateProfileStringA("CASCADE", "DBUSER", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbuser = szBuff;

	GetPrivateProfileStringA("CASCADE", "DBPWD", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szdbpwd = szBuff;

	appconfig.m_cascade_cfg.cascade = (bool)GetPrivateProfileIntA("CASCADE", "CASCADE", 0, szconfig.c_str());

	GetPrivateProfileStringA("CASCADE", "UPSERVERIP", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szupserverip = szBuff;

	GetPrivateProfileStringA("CASCADE", "UPSERVERPORT", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szupserverport = szBuff;

	appconfig.m_cascade_cfg.mode = (timemode)GetPrivateProfileIntA("CASCADE", "TIMEMODE", 0, szconfig.c_str());

	GetPrivateProfileStringA("CASCADE", "NETTIME", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.sznettime = szBuff;

	appconfig.m_cascade_cfg.flux = (bool)GetPrivateProfileIntA("CASCADE", "FLUX", 0, szconfig.c_str());

	appconfig.m_cascade_cfg.fluxspeed = GetPrivateProfileIntA("CASCADE", "FLUXSPEED", 0, szconfig.c_str());

	GetPrivateProfileStringA("CASCADE", "PATH", "", szBuff, MAX_LEN, szconfig.c_str());
	appconfig.m_cascade_cfg.szPatchPath = szBuff;

	appconfig.m_cascade_cfg.localserverport = GetPrivateProfileIntA("CASCADE", "LOCALPORT", 6998, szconfig.c_str());
	appconfig.m_cascade_cfg.index1 = GetPrivateProfileIntA("CASCADE", "INDEX1", 1, szconfig.c_str());


	appconfig.m_mode_cfg.mode = (switchmode)GetPrivateProfileIntA("SWITCHMODE", "MODE", 0, szconfig.c_str());

	appconfig.m_other_cfg.enable = (bool)GetPrivateProfileIntA("DEBUG", "LOG", 1, szconfig.c_str());
	appconfig.m_other_cfg.level = GetPrivateProfileIntA("DEBUG", "LEVEL", 4, szconfig.c_str());

	GetPrivateProfileStringA("LANGUAGE", "DEFAULT", "ZHCN", szBuff, MAX_LEN, szconfig.c_str());
	if (_stricmp(szBuff, "ZHCN") == 0)
		appconfig.m_other_cfg.lang = ZHCN;
	else
		appconfig.m_other_cfg.lang = EN;

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
	std::string szPath = pszPath;
	if (bFilePath)
		szPath = szPath.substr(0, szPath.find_last_of('\\'));

	if (!PathIsDirectoryA(szPath.c_str()))
	{
		std::string szParentPath;
		std::string szFullPath = szPath;
		auto pos = szFullPath.find_last_of("\\");
		if (pos != std::string::npos)
			szParentPath = szFullPath.substr(0, pos);
		if (MakeSureDirectoryExist(szParentPath.c_str(), FALSE))
			return CreateDirectoryA(szPath.c_str(), NULL);
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

	TravelPatchPath(szPatchpath + "\\chinese", patches);
	TravelPatchPath(szPatchpath + "\\english", patches);
}


void CPatchServiceImpl::RequestPatchInfo(vrv::patch::PatchInfo &patch)
{
	std::string szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath;

	std::string szPatchFile = szPath + "\\" + patch.szPatchName;
	std::stringstream ss;
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
		szToolpath = appconfig.m_http_cfg.m_szPatchPath + "\\Tools";

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szToolpath = appconfig.m_cascade_cfg.szPatchPath + "\\Tools";

	TravelIndexPath(szToolpath, indexes);
}

void  CPatchServiceImpl::DownloadFiles(std::string& szFile, RCF::FileDownload &fileDownload)
{
	fileDownload = RCF::FileDownload(szFile);
}

void  CPatchServiceImpl::DownloadIndexFile(std::string& szFile, RCF::FileDownload &fileDownload)
{
	std::string szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath + "\\Tools";

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath + "\\Tools";

	std::string szIndexFile = szPath + "\\" + szFile;
	fileDownload = RCF::FileDownload(szIndexFile);
}

void  CPatchServiceImpl::DownloadPatchFile(std::string& szFile, RCF::FileDownload &fileDownload)
{
	std::string szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath;

	std::string szPatchFile = szPath + "\\" + szFile;
	fileDownload = RCF::FileDownload(szPatchFile);
}

void  CPatchServiceImpl::DownloadIndex1xml(RCF::FileDownload &fileDownload)
{
	std::string szPath;
	if (appconfig.m_mode_cfg.mode == http_mode)
		szPath = appconfig.m_http_cfg.m_szPatchPath;

	else if (appconfig.m_mode_cfg.mode == cascade_mode)
		szPath = appconfig.m_cascade_cfg.szPatchPath;

	std::string szIndex1Xml = szPath + "\\" + "index1.xml";
	std::string szIndex1Zip = szPath + "\\" + "index1.zip";
	if (PathFileExistsA(szIndex1Zip.c_str()))
		fileDownload = RCF::FileDownload(szIndex1Xml);
	else
		throw RCF::Exception(RCF::_RcfError_FileOpen(szIndex1Zip));
}

void  CPatchServiceImpl::TravelIndexPath(std::string &szPath, std::vector<vrv::patch::IndexInfo> &indexes)
{
	std::string szFindPath = szPath + "\\*.*";
	_finddata32_t data = { 0 };
	intptr_t handle = _findfirst32(szFindPath.c_str(), &data);
	if (handle == 0)
		return;
	do
	{
		if (data.attrib & _A_SUBDIR)
		{
			if (_stricmp(data.name, ".")
				&& _stricmp(data.name, ".."))
				TravelIndexPath(szPath + "\\" + data.name, indexes);
		}
		else
		{
			std::string szName = data.name;
			if (!szName.empty() && szName.back() != '~')
			{
				vrv::patch::IndexInfo indexInfo;
				indexInfo.size = data.size;
				indexInfo.szIndexName = szPath + "\\" + data.name;
				indexInfo.dwCrc = GetFileCrc(indexInfo.szIndexName.c_str());
				indexInfo.szIndexName = indexInfo.szIndexName.substr(szToolpath.length() + 1);
				indexes.push_back(indexInfo);
			}
		}

	} while (!_findnext32(handle, &data));
	_findclose(handle);
}

void  CPatchServiceImpl::GetIndexInfo(std::string &szFile, vrv::patch::IndexInfo& indexinfo)
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

void  CPatchServiceImpl::TravelPatchPath(std::string &szPath, std::vector<vrv::patch::PatchInfo> &patches)
{
	std::string szFindPath = szPath + "\\*.*";
	_finddata32_t data = { 0 };
	intptr_t handle = _findfirst32(szFindPath.c_str(), &data);
	if (handle == 0)
		return;
	do
	{
		if (data.attrib & _A_SUBDIR)
		{
			if (_stricmp(data.name, ".")
				&& _stricmp(data.name, ".."))
				TravelPatchPath(szPath + "\\" + data.name, patches);
		}
		else
		{
			std::string szName = data.name;
			if (!szName.empty() && szName.back() != '~')
			{
				std::stringstream ss;
				ss << data.size;
				vrv::patch::PatchInfo patchInfo;
				patchInfo.szPatchSize = ss.str();
				patchInfo.szPatchName = szPath + "\\" + data.name;
				GetFileSHA1(patchInfo.szPatchName, patchInfo.szMd5);
				patchInfo.szPatchName = patchInfo.szPatchName.substr(szPatchpath.length() + 1);
				patches.push_back(patchInfo);
			}
		}

	} while (!_findnext32(handle, &data));
	_findclose(handle);
}

void  CPatchServiceImpl::GetPatchInfo(std::string &szFile, vrv::patch::PatchInfo& patchInfo)
{
	std::stringstream ss;
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