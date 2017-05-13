
// HttpPatchServer.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "PatchService.h"


// CHttpPatchServerApp: 
// 有关此类的实现，请参阅 HttpPatchServer.cpp
//

class CPatchServiceImpl
{
public:

	int add(int a, int b);
	void RequestPatchInfo(std::vector<vrv::patch::PatchInfo> &patches);
	void RequestIndexInfo(std::vector<vrv::patch::IndexInfo> &indexes);
	void DownloadFiles(std::string& szFile, RCF::FileDownload &fileDownload);
	void DownloadIndexFile(std::string& szFile, RCF::FileDownload &fileDownload);
	void DownloadPatchFile(std::string& szFile, RCF::FileDownload &fileDownload);
	void DownloadIndex1xml(RCF::FileDownload &fileDownload);

private:
	void TravelIndexPath(std::string &szPath, std::vector<vrv::patch::IndexInfo> &indexes);
	void GetIndexInfo(std::string &szFile, vrv::patch::IndexInfo& indexinfo);
	void TravelPatchPath(std::string &szPath, std::vector<vrv::patch::PatchInfo> &patches);
	void GetPatchInfo(std::string &szFile, vrv::patch::PatchInfo& patchInfo);

private:
	std::string szPatchpath;
	std::string szToolpath;
	std::mutex mtxforindex;
	std::mutex mtxforpatch;
};


class CHttpPatchServerApp : public CWinApp
{
public:
	CHttpPatchServerApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	BOOL GetAppRootPath();
	//BOOL InitDUI();
	virtual int ExitInstance();
	void Initlog();
	BOOL InitAppConfig();
	void ReadConfig();
	void InitPatchClient();
	void InitPatchServer();
	void StopByCurl();
	void StopByRcf();
	std::thread _thread;

	std::shared_ptr<RCF::RcfServer> server;
	std::shared_ptr<RcfClient<MyService>> client;
	std::shared_ptr<RCF::FileDownload> fileDownload;
	std::shared_ptr<Curl> m_curlptr;
	CPatchServiceImpl myservice;

public:
	//IDUIRes *m_pDuiRes;

	DECLARE_MESSAGE_MAP()

};


extern CHttpPatchServerApp theApp;
//IDUIRes *AfxGetDuiRes();
LPCSTR AfxGetAppTitle();
BOOL MakeSureDirectoryExist(const TCHAR * szDirectoryPath, BOOL bFilePath);