// PathDownloadListView.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PathDownloadListView.h"
#include "afxdialogex.h"
#include <sstream>
#include <fstream>
#include <regex>
#include <iostream>
#include <iomanip>
// CPathDownloadListView 对话框

#include "PatchView.h"

IDUITVItem* m_curItem;

#define MESSAGE_TIMEOUT			1000

bool g_bstop = false;

IMPLEMENT_DYNAMIC(CPatchDownView, CDUIDialog)

#define DUI_pDownView DList(ListViewDownTask)

CPatchDownView::CPatchDownView(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DOWNLOAD_LISTVIEW, pParent)
{
	m_pParent = pParent;
}

CPatchDownView::~CPatchDownView()
{
}

void CPatchDownView::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchDownView, CDUIDialog)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(UM_DOWNVIEW_INDEXITEM, &CPatchDownView::InsertIndexItem)
	ON_MESSAGE(UM_DOWNVIEW_PATCHITEM, &CPatchDownView::InsertPatchItem)
	ON_MESSAGE(UM_DOWNVIEW_CLEANITEMS, &CPatchDownView::CleanItems)
	ON_MESSAGE(UM_DOWNVIEW_REFRESH, &CPatchDownView::RefreshListView)
END_MESSAGE_MAP()

// CPathDownloadListView 消息处理程序

std::string ConvertSpeedUnit(unsigned long speed)
{
	std::stringstream ss;
	std::string szUnit;
	double dspeed = speed;
	if (dspeed > 1024 * 1024 * 1024)
	{
		szUnit = "G";
		dspeed /= 1024 * 1024 * 1024;
	}
	else if (dspeed > 1024 * 1024)
	{
		szUnit = "MB";
		dspeed /= 1024 * 1024;
	}
	else if (dspeed > 1024)
	{
		szUnit = "KB";
		dspeed /= 1024;
	}
	ss << std::setprecision(2) << std::setiosflags(ios::fixed | ios::showpoint) << dspeed << szUnit;
	return ss.str();
}


int CurlProgress(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	Curl *pCurl = static_cast<Curl *>(clientp);
	//char timeFormat[9] = "Unknow";

	// Defaults to bytes/second  
	//double speed;
	//string unit = "B";

	//curl_easy_getinfo(easy_handle, CURLINFO_SPEED_DOWNLOAD, &speed); // curl_get_info必须在curl_easy_perform之后调用  
//
//	if (speed != 0)
//	{
//		// Time remaining  
//		double leftTime = (downloadFileLength - dlnow - resumeByte) / speed;
//		int hours = leftTime / 3600;
//		int minutes = (leftTime - hours * 3600) / 60;
//		int seconds = leftTime - hours * 3600 - minutes * 60;
//
//#ifdef _WIN32  
//		sprintf_s(timeFormat, 9, "%02d:%02d:%02d", hours, minutes, seconds);
//#else  
//		sprintf(timeFormat, "%02d:%02d:%02d", hours, minutes, seconds);
//#endif  
//	}
//
//	if (speed > 1024 * 1024 * 1024)
//	{
//		unit = "G";
//		speed /= 1024 * 1024 * 1024;
//	}
//	else if (speed > 1024 * 1024)
//	{
//		unit = "M";
//		speed /= 1024 * 1024;
//	}
//	else if (speed > 1024)
//	{
//		unit = "kB";
//		speed /= 1024;
//	}
//
//	printf("speed:%.2f%s/s", speed, unit.c_str());

	if (dltotal != 0 && !g_bstop)
	{
		double p = (dlnow + pCurl->m_curLength) / (double)pCurl->m_filesize;
		short pos = p * 100;
		if (pCurl->m_pProgressCtrl)
		{
			IDUIProgressbar * pDUIProgressBar = (IDUIProgressbar*)pCurl->m_pProgressCtrl;
			short curPos = pDUIProgressBar->GetPos();
			if (curPos != pos)
			{
				pDUIProgressBar->SetPos(pos);
			}
		}
	}

	return 0;
}


void onFileTransferProgress(const RCF::FileTransferProgress & progress)
{
	//RCF::RcfSession &session = RCF::getCurrentRcfSession();
	std::cout << "Total bytes to transfer: " << progress.mBytesTotalToTransfer << std::endl;
	std::cout << "Bytes transferred so far: " << progress.mBytesTransferredSoFar << std::endl;
	std::cout << "Server-side bandwidth limit (if any): " << progress.mServerLimitBps << std::endl;

	double p = progress.mBytesTransferredSoFar / (double)progress.mBytesTotalToTransfer;
	short pos = p * 100;

	if (g_bstop)
		throw RCF::Exception("停止下载");

	if (m_curItem)
	{
		IDUIControlBase* pItemBase = (IDUIControlBase*)m_curItem->GetCustomObj();
		IDUIProgressbar *pItemProgress = (IDUIProgressbar *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
		short curPos = pItemProgress->GetPos();
		if (curPos != pos)
		{
			pItemProgress->SetPos(pos);
		}
	}

}


BOOL CPatchDownView::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




int CPatchDownView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}



BOOL CPatchDownView::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIDownTask");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


std::string MakePatchSubPathFromDate(std::string &szUrl, std::string &szPubDate)
{
	std::string szSubPath;
	std::regex rgx("http://.*(/\\d{4}/\\d{2})/.+\\.*\\w*");
	std::smatch sm;
	if (std::regex_match(szUrl, sm, rgx))
	{
		if (sm.size() > 0)
			szSubPath = *(sm.end() - 1);
	}
	else
	{
		std::regex rgx("(\\d{4}[-/]\\d{2}).*");
		std::smatch sm;
		if (std::regex_match(szPubDate, sm, rgx))
		{
			if (sm.size() > 0)
				szSubPath = *(sm.end() - 1);
		}
	}

	std::regex r("[-/]");
	std::string rep = "\\";
	szSubPath = std::regex_replace(szSubPath, r, rep);
	if (szSubPath[0] != '\\')
		szSubPath = szSubPath.insert(0, "\\");

	return szSubPath;
}

void CPatchDownView::InsertErrorTaskToView(void *pTask, TASK_TYPE type)
{
	CWnd *pErrorView = ((CPatchView*)m_pParent)->GetErrorView();
	if (INDEX == type)
	{
		::SendMessageTimeout(pErrorView->m_hWnd, UM_ERRORVIEW_INDEXITEM, (WPARAM)pTask, type, SMTO_ABORTIFHUNG , 5000, 0);
	}
	else if (PATCH == type)
	{
		::SendMessageTimeout(pErrorView->m_hWnd, UM_ERRORVIEW_PATCHITEM, (WPARAM)pTask, type, SMTO_ABORTIFHUNG , 5000, 0);
	}
}


bool CPatchDownView::DownloadIndexesByCurl(IDUITVItem *pTopItem, vrv::patch::PatchIndexVectorPtr indexes)
{
	int taskdone = 0, taskerror = 0;
	std::string szurlPrefix, sztoolpath;
	int indxcount = indexes->GetIndexCount();

	IDUIControlBase *pTopBase = pTopItem->GetCustomObj();
	IDUIStatic *pTopSize = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
	IDUIStatic *pTopError = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
	IDUIProgressbar *pTopProgress = (IDUIProgressbar *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);

	std::stringstream ss;
	ss << "0/" << indxcount;
	pTopSize->SetText(ss.str());
	pTopError->SetText(_T("0"));

	::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_CLEANITEMS, 0, 0, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
	size_t pos = appconfig.m_http_cfg.m_szIndexUrl.find_last_of("//");
	if (pos == std::string::npos)
	{
		vrvlog::SPD_LOG_ERROR("URL:{0} format error", appconfig.m_http_cfg.m_szIndexUrl);
		return false;
	}
	szurlPrefix = appconfig.m_http_cfg.m_szIndexUrl.substr(0, pos + 1);
	sztoolpath = appconfig.m_http_cfg.m_szPatchPath + "\\Tools\\";

	vrv::patch::PatchIndexVector::_iterator iter = indexes->patchindexes.begin();
	for (; iter != indexes->patchindexes.end() && !g_bstop; ++iter)
	{
		vrv::patch::PatchIndexPtr patchindex = *iter;

		vrv::patch::IndexInfoVec TmpContainer;
		if (!patchindex->m_szIndexPath.empty())
		{
			vrv::patch::IndexInfoPtr indexptr = std::make_shared<vrv::patch::IndexInfo>();
			indexptr->dwCrc = patchindex->dwIndexCrc;
			indexptr->szIndexName = patchindex->m_szIndexPath;
			TmpContainer.push_back(indexptr);
		}

		if (!patchindex->m_szSubIndexPath.empty())
		{
			vrv::patch::IndexInfoPtr indexptr = std::make_shared<vrv::patch::IndexInfo>();
			indexptr->dwCrc = patchindex->dwSubIndexCrc;
			indexptr->szIndexName = patchindex->m_szSubIndexPath;
			TmpContainer.push_back(indexptr);
		}

		for (size_t idx = 0; idx < TmpContainer.size() && !g_bstop; ++idx)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			vrv::patch::IndexInfoPtr indexptr = TmpContainer[idx];
			IDUITVItem *pItem = nullptr;
			::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_INDEXITEM, (WPARAM)indexptr.get(), (LPARAM)&pItem, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
			if (pItem == nullptr)
			{
				InsertErrorTaskToView(&indexptr, INDEX);
				continue;
			}

			IDUIControlBase* pItemBase = (IDUIControlBase*)pItem->GetCustomObj();
			IDUIStatic *pItemSize = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
			IDUIProgressbar *pItemProgress = (IDUIProgressbar *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
			IDUIStatic *pItemCrc = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskCrc"), TRUE);
			IDUIStatic *pItemDate = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);

			std::string szIndexUrl = szurlPrefix + indexptr->szIndexName;
			std::string szIndexPath = sztoolpath + indexptr->szIndexName;
			if (!MakeSureDirectoryExist(szIndexPath.c_str(), TRUE))
			{
				std::stringstream serr;
				serr << ++taskerror;
				pTopError->SetText(serr.str());
				vrvlog::SPD_LOG_ERROR("Index path create failed {0}", szIndexPath.c_str());
				InsertErrorTaskToView(&indexptr, INDEX);
				continue;
			}

			theApp.m_curlptr = std::make_shared<Curl>();

			if (GetFileCrc(szIndexPath.c_str()) == indexptr->dwCrc)
			{
				std::ifstream ifs(szIndexPath);
				ifs.seekg(0, ifs.end);
				std::streamoff len = ifs.tellg();
				if (pItemProgress)
					pItemProgress->SetPos(100);
				pItemSize->SetText(ConvertSpeedUnit(len));
				++taskdone;
			}
			else
			{
				size_t size = 0;
				std::string szTmpFile = szIndexPath + "~";

				if (appconfig.m_http_cfg.flux)
					theApp.m_curlptr->SetDownloadSpeed(appconfig.m_http_cfg.fluxspeed);

				if (appconfig.m_http_cfg.proxy)
					theApp.m_curlptr->SetProxy(
						appconfig.m_http_cfg.szip,
						appconfig.m_http_cfg.szport,
						appconfig.m_http_cfg.szuser,
						appconfig.m_http_cfg.szpwd);

				theApp.m_curlptr->SetUrlFile(szIndexUrl, szTmpFile);

				theApp.m_curlptr->SetProgressCallback(CurlProgress, theApp.m_curlptr.get(), pItemProgress);
				long code = 0l;
				if (0 == (code = theApp.m_curlptr->GetFileSize(size)))
				{
					pItemSize->SetText(ConvertSpeedUnit(size));

					if (0 == (code = theApp.m_curlptr->StartDownload()))
					{
						MoveFileExA(szTmpFile.c_str(), szIndexPath.c_str(), MOVEFILE_REPLACE_EXISTING);
						vrvlog::SPD_LOG_INFO("{0} download succeed", szIndexPath.c_str());
					}
				}

				code == 0 ? ++taskdone : ++taskerror;
				if (code)
				{
					InsertErrorTaskToView(&indexptr, INDEX);
					vrvlog::SPD_LOG_ERROR("Index File: {0} download failed ({1})", szIndexPath.c_str(), code);
				}
			}

			pItemDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());

			//::SendMessage(m_hWnd, UM_DOWNVIEW_REFRESH, 0, 0);
			pItem->Refresh();

			std::stringstream scount, serr;
			scount << taskdone << "/" << indxcount;
			pTopSize->SetText(scount.str());

			serr << taskerror;
			pTopError->SetText(serr.str());

			if (pTopProgress)
			{
				short pos = (taskdone / (double)indxcount) * 100;
				pTopProgress->SetPos(pos);
			}
		}
	}

	if (g_bstop)
	{
		vrvlog::SPD_LOG_INFO("Http download thread has been stopped.");
		return false;
	}

	return true;
}

bool CPatchDownView::DownloadPatchesByCurl(IDUITVItem *pTopItem, vrv::patch::PatchInfoVec &patches)
{
	int taskdone = 0, taskerror = 0;
	std::string szurlPrefix, szpatchpath;
	int patchcount = patches.size();

	IDUIControlBase *pTopBase = pTopItem->GetCustomObj();
	IDUIStatic *pTopSize = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
	IDUIStatic *pTopError = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
	IDUIProgressbar *pTopProgress = (IDUIProgressbar *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);

	std::stringstream ss;
	ss << "0/" << patchcount;
	pTopSize->SetText(ss.str());
	pTopError->SetText(_T("0"));

	::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_CLEANITEMS, 0, 0, SMTO_ABORTIFHUNG, MESSAGE_TIMEOUT, 0);
	szpatchpath = appconfig.m_http_cfg.m_szPatchPath;

	vrv::patch::_patchiter iter = patches.begin();
	for (; iter != patches.end() && !g_bstop; ++iter)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		vrv::patch::PatchInfoPtr patch = *iter;

		IDUITVItem *pItem = nullptr;
		::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_PATCHITEM, (WPARAM)patch.get(), (LPARAM)&pItem, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
		if (pItem == nullptr)
		{
			InsertErrorTaskToView(&patch, PATCH);
			continue;
		}
		IDUIControlBase* pItemBase = (IDUIControlBase*)pItem->GetCustomObj();
		IDUIStatic *pItemSize = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIProgressbar *pItemProgress = (IDUIProgressbar *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
		IDUIStatic *pItemCrc = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskCrc"), TRUE);
		IDUIStatic *pItemDate = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);

		std::string szPathLan = "\\chinese";
		if (patch->szLans.find(".en.") != std::string::npos
			&& patch->szLans.find(".zhcn.") == std::string::npos)
			szPathLan = "\\english";

		std::string szfilePath = szpatchpath + szPathLan +
			MakePatchSubPathFromDate(patch->szUrl, patch->szDatePublish) +
			"\\" + patch->szPatchName;

		if (!MakeSureDirectoryExist(szfilePath.c_str(), TRUE))
		{
			std::stringstream serr;
			serr << ++taskerror;
			pTopError->SetText(serr.str());
			vrvlog::SPD_LOG_ERROR("Patch path create failed {0}", szfilePath.c_str());
			InsertErrorTaskToView(&patch, PATCH);
			continue;
		}

		theApp.m_curlptr = std::make_shared<Curl>();

		std::string szSha;
		if (GetFileSHA1(szfilePath.c_str(), szSha) &&
			szSha == patch->szMd5)
		{
			++taskdone;
			if (pItemProgress)
				pItemProgress->SetPos(100);
		}
		else
		{
			size_t size = 0;
			std::string szTmpFile = szfilePath + "~";

			if (appconfig.m_http_cfg.flux)
				theApp.m_curlptr->SetDownloadSpeed(appconfig.m_http_cfg.fluxspeed);

			if (appconfig.m_http_cfg.proxy)
				theApp.m_curlptr->SetProxy(
					appconfig.m_http_cfg.szip,
					appconfig.m_http_cfg.szport,
					appconfig.m_http_cfg.szuser,
					appconfig.m_http_cfg.szpwd);

			theApp.m_curlptr->SetUrlFile(patch->szUrl, szTmpFile);

			theApp.m_curlptr->SetProgressCallback(CurlProgress, theApp.m_curlptr.get(), pItemProgress);
			long code = 0l;
			if (0 == (code = theApp.m_curlptr->GetFileSize(size)))
			{
				pItemSize->SetText(ConvertSpeedUnit(size));

				if (0 == (code = theApp.m_curlptr->StartDownload()))
				{
					MoveFileExA(szTmpFile.c_str(), szfilePath.c_str(), MOVEFILE_REPLACE_EXISTING);
					vrvlog::SPD_LOG_INFO("{0} download succeed", szfilePath.c_str());
				}
			}

			code == 0 ? ++taskdone : ++taskerror;
			if (code)
			{
				InsertErrorTaskToView(&patch, PATCH);
				vrvlog::SPD_LOG_ERROR("{0} download failed ({1})", patch->szUrl.c_str(), code);
			}
		}

		pItemDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());

		//::SendMessage(m_hWnd, UM_DOWNVIEW_REFRESH, 0, 0);
		//DUI_pDownView->RefreshView();
		pItem->Refresh();

		std::stringstream scount, serr;
		scount << taskdone << "/" << patchcount;
		pTopSize->SetText(scount.str());

		serr << taskerror;
		pTopError->SetText(serr.str());

		if (pTopProgress)
		{
			short pos = (taskdone / (double)patchcount) * 100;
			pTopProgress->SetPos(pos);
		}
	}

	if (g_bstop)
	{
		vrvlog::SPD_LOG_INFO("Http download thread has been stopped.");
		return false;
	}

	return true;
}



LRESULT CPatchDownView::InsertPatchItem(WPARAM wparam, LPARAM lparam)
{
	vrv::patch::PatchInfo* patch = (vrv::patch::PatchInfo*)wparam;
	if (patch == nullptr)
		return 0;
	std::string szPatchName;
	size_t pos = patch->szPatchName.find_last_of("\\");
	if (pos == std::string::npos)
		szPatchName = patch->szPatchName;
	else
		szPatchName = patch->szPatchName.substr(pos + 1);

	int nIndex = DUI_pDownView->GetItemCount();
	nIndex = DUI_pDownView->InsertItem(nIndex, patch->szPatchName, 0, TRUE);
	IDUITVItem *pItem = (IDUITVItem *)DUI_pDownView->GetAt(nIndex);
	IDUIControlBase* pCtrlBase = (IDUIControlBase*)pItem->GetCustomObj();
	IDUIStatic *pStcName = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
	IDUIStatic *pStcSize = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
	IDUIProgressbar *pProgress = (IDUIProgressbar *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
	IDUIStatic *pStcCrc = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskCrc"), TRUE);
	IDUIStatic *pStcDate = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);

	pStcName->SetText(szPatchName);
	pStcName->DUISetToolTip(patch->MakeToolTipText());
	unsigned long speed;
	std::stringstream ss;
	ss << patch->szPatchSize;
	ss >> speed;
	pStcSize->SetText(ConvertSpeedUnit(speed));
	pStcCrc->SetText(patch->szMd5);
	pStcDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());
	DUI_pDownView->RefreshView();
	//pItem->Refresh();
	*(IDUITVItem **)lparam = pItem;
	return 0;
}


LRESULT CPatchDownView::InsertIndexItem(WPARAM wparam, LPARAM lparam)
{
	vrv::patch::IndexInfo* pIndex = (vrv::patch::IndexInfo*)wparam;
	if (pIndex == nullptr)
		return 0;

	std::string szIndexName;
	size_t pos = pIndex->szIndexName.find_last_of("\\");
	if (pos == std::string::npos)
		szIndexName = pIndex->szIndexName;
	else
		szIndexName = pIndex->szIndexName.substr(pos + 1);

	std::stringstream ss;
	ss << pIndex->dwCrc;
	int nIndex = DUI_pDownView->GetItemCount();
	nIndex = DUI_pDownView->InsertItem(nIndex, pIndex->szIndexName, 0, TRUE);
	IDUITVItem *pItem = (IDUITVItem *)DUI_pDownView->GetAt(nIndex);
	IDUIControlBase* pCtrlBase = (IDUIControlBase*)pItem->GetCustomObj();
	IDUIStatic *pStcName = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
	IDUIStatic *pStcSize = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
	IDUIProgressbar *pProgress = (IDUIProgressbar *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
	IDUIStatic *pStcCrc = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskCrc"), TRUE);
	IDUIStatic *pStcDate = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);

	pStcName->SetText(szIndexName);
	pStcSize->SetText(ConvertSpeedUnit(pIndex->size));
	pStcCrc->SetText(ss.str());
	pStcDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());
	DUI_pDownView->RefreshView();
	//pItem->Refresh();
	*(IDUITVItem **)lparam = pItem;
	return 0;
}

LRESULT CPatchDownView::RefreshListView(WPARAM wapram, LPARAM lparam)
{
	DUI_pDownView->RefreshView();
	return 0;
}

LRESULT CPatchDownView::CleanItems(WPARAM wparam, LPARAM lparam)
{
	DUI_pDownView->RefreshView();
	DUI_pDownView->DeleteAllItems();
	DUI_pDownView->RefreshView();
	return 0;
}



CWnd* CPatchDownView::GetParent()
{
	return m_pParent;
}

void CPatchDownView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}

bool CPatchDownView::DownloadIndexesByRcf(IDUITVItem *pTopItem)
{
	std::vector<vrv::patch::IndexInfo> indexes;
	try
	{
		theApp.client->RequestIndexInfo(indexes);
	}
	catch (const RCF::Exception& e)
	{
		vrvlog::SPD_LOG_ERROR("Cascade request indexes failed, errorid({0}),what({1})",
			e.getErrorId(), e.getWhat());
		return false;
	}

	int taskdone = 0, taskerror = 0;
	std::string sztoolpath;
	int indxcount = indexes.size();

	IDUIControlBase *pTopBase = pTopItem->GetCustomObj();
	IDUIStatic *pTopSize = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
	IDUIStatic *pTopError = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
	IDUIProgressbar *pTopProgress = (IDUIProgressbar *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);

	std::stringstream ss;
	ss << "0/" << indxcount;
	pTopSize->SetText(ss.str());
	pTopError->SetText(_T("0"));

	::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_CLEANITEMS, 0, 0, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
	sztoolpath = appconfig.m_cascade_cfg.szPatchPath + "\\Tools\\";

	for (size_t idx = 0; idx < indexes.size() && !g_bstop; ++idx)
	{
		vrv::patch::IndexInfoPtr indexptr = std::make_shared<vrv::patch::IndexInfo>(indexes[idx]);

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		IDUITVItem *pItem = nullptr;
		::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_INDEXITEM, (WPARAM)indexptr.get(), (LPARAM)&pItem, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
		if (pItem == nullptr)
		{
			InsertErrorTaskToView(&indexptr, INDEX);
			continue;
		}

		m_curItem = pItem;
		IDUIControlBase* pItemBase = (IDUIControlBase*)pItem->GetCustomObj();
		IDUIStatic *pItemSize = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIProgressbar *pItemProgress = (IDUIProgressbar *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
		IDUIStatic *pItemCrc = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskCrc"), TRUE);
		IDUIStatic *pItemDate = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);

		std::string szIndexPath = sztoolpath + indexptr->szIndexName;
		if (!MakeSureDirectoryExist(szIndexPath.c_str(), TRUE))
		{
			std::stringstream serr;
			serr << ++taskerror;
			pTopError->SetText(serr.str());
			vrvlog::SPD_LOG_ERROR("Index path create failed ({0})", szIndexPath.c_str());
			InsertErrorTaskToView(&indexptr, INDEX);
			continue;
		}


		//pItemSize->SetText(ConvertSpeedUnit(indexptr->size));

		if (GetFileCrc(szIndexPath.c_str()) == indexptr->dwCrc)
		{
			if (pItemProgress)
				pItemProgress->SetPos(100);
			++taskdone;
		}
		else
		{
			std::string szPath = szIndexPath.substr(0, szIndexPath.find_last_of("\\"));

			theApp.client->getClientStub().setFileProgressCallback(&onFileTransferProgress);

			if (appconfig.m_cascade_cfg.flux)
				theApp.fileDownload->setTransferRateBps(appconfig.m_cascade_cfg.fluxspeed * 1024);

			theApp.fileDownload->setDownloadToPath(szPath);

			try
			{
				theApp.client->DownloadIndexFile(indexptr->szIndexName, *theApp.fileDownload);
				std::string szLocalpath = theApp.fileDownload->getLocalPath();
				++taskdone;
			}
			catch (RCF::Exception &e)
			{
				vrvlog::SPD_LOG_ERROR("Index File: {0} download failed ({1})", szIndexPath.c_str(), e.getErrorId());
				InsertErrorTaskToView(&indexptr, INDEX);
				++taskerror;
			}

			//code == 0 ? ++taskdone : ++taskerror;
			//if (code)
				//InsertErrorTaskToView(&indexptr, INDEX);
		}

		pItemDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());

		//::SendMessage(m_hWnd, UM_DOWNVIEW_REFRESH, 0, 0);
		pItem->Refresh();

		std::stringstream scount, serr;
		scount << taskdone << "/" << indxcount;
		pTopSize->SetText(scount.str());

		serr << taskerror;
		pTopError->SetText(serr.str());

		if (pTopProgress)
		{
			short pos = (taskdone / (double)indxcount) * 100;
			pTopProgress->SetPos(pos);
		}
	}

	if (g_bstop)
	{
		vrvlog::SPD_LOG_INFO("Cascade download thread has been stopped.");
		return false;
	}

	return true;
}


bool CPatchDownView::DownloadPatchesByRcf(IDUITVItem *pTopItem)
{
	std::vector<vrv::patch::PatchInfo> patches;
	try
	{
		theApp.client->RequestPatchInfo(patches);
	}
	catch (const RCF::Exception& e)
	{
		vrvlog::SPD_LOG_ERROR("Cascade Patch info failed, errorid({0}),what({1})",
			e.getErrorId(), e.getWhat());
		return false;
	}

	int taskdone = 0, taskerror = 0;
	std::string szpatchpath;
	int indxcount = patches.size();

	IDUIControlBase *pTopBase = pTopItem->GetCustomObj();
	IDUIStatic *pTopSize = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
	IDUIStatic *pTopError = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
	IDUIProgressbar *pTopProgress = (IDUIProgressbar *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);

	std::stringstream ss;
	ss << "0/" << indxcount;
	pTopSize->SetText(ss.str());
	pTopError->SetText(_T("0"));

	::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_CLEANITEMS, 0, 0, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
	szpatchpath = appconfig.m_cascade_cfg.szPatchPath + "\\";

	for (size_t idx = 0; idx < patches.size() && !g_bstop; ++idx)
	{
		vrv::patch::PatchInfoPtr patchptr = std::make_shared<vrv::patch::PatchInfo>(patches[idx]);

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		IDUITVItem *pItem = nullptr;
		::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_PATCHITEM, (WPARAM)patchptr.get(), (LPARAM)&pItem, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
		if (pItem == nullptr)
		{
			InsertErrorTaskToView(&patchptr, PATCH);
			continue;
		}

		m_curItem = pItem;
		IDUIControlBase* pItemBase = (IDUIControlBase*)pItem->GetCustomObj();
		IDUIStatic *pItemSize = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIProgressbar *pItemProgress = (IDUIProgressbar *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
		IDUIStatic *pItemCrc = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskCrc"), TRUE);
		IDUIStatic *pItemDate = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);

		std::string szPatchFile = szpatchpath + patchptr->szPatchName;
		if (!MakeSureDirectoryExist(szPatchFile.c_str(), TRUE))
		{
			std::stringstream serr;
			serr << ++taskerror;
			pTopError->SetText(serr.str());
			vrvlog::SPD_LOG_ERROR("Patch path create failed ({0})", szPatchFile.c_str());
			InsertErrorTaskToView(&patchptr, PATCH);
			continue;
		}

		//size_t size;
		//std::stringstream ss;
		//ss << patchptr->szPatchSize;
		//ss >> size;
		//pItemSize->SetText(ConvertSpeedUnit(size));

		std::string szSha;
		if (GetFileSHA1(szPatchFile.c_str(), szSha) &&
			szSha == patchptr->szMd5)
		{
			++taskdone;
			if (pItemProgress)
				pItemProgress->SetPos(100);
		}
		else
		{
			std::string szPath = szPatchFile.substr(0, szPatchFile.find_last_of("\\"));
			try
			{
				theApp.client->getClientStub().setFileProgressCallback(&onFileTransferProgress);

				if (appconfig.m_cascade_cfg.flux)
					theApp.fileDownload->setTransferRateBps(appconfig.m_cascade_cfg.fluxspeed * 1024);

				theApp.fileDownload->setDownloadToPath(szPath);
				theApp.client->DownloadPatchFile(patchptr->szPatchName, *theApp.fileDownload);
				std::string szLocalpath = theApp.fileDownload->getLocalPath();
				++taskdone;
			}
			catch (RCF::Exception &e)
			{
				vrvlog::SPD_LOG_ERROR("Patch File: {0} download failed ({1})", szPatchFile.c_str(), e.getErrorId());
				InsertErrorTaskToView(&patchptr, PATCH);
				++taskerror;

			}

			//code == 0 ? ++taskdone : ++taskerror;
			//if (code)
			//InsertErrorTaskToView(&indexptr, INDEX);
		}

		pItemDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());

		//::SendMessage(m_hWnd, UM_DOWNVIEW_REFRESH, 0, 0);
		pItem->Refresh();

		std::stringstream scount, serr;
		scount << taskdone << "/" << indxcount;
		pTopSize->SetText(scount.str());

		serr << taskerror;
		pTopError->SetText(serr.str());

		if (pTopProgress)
		{
			short pos = (taskdone / (double)indxcount) * 100;
			pTopProgress->SetPos(pos);
		}
	}

	if (g_bstop)
	{
		vrvlog::SPD_LOG_INFO("Cascade download thread has been stopped.");
		return false;
	}

	return true;
}

bool CPatchDownView::DownloadIndex1xmlByRcf(IDUITVItem *pTopItem)
{
	int taskdone = 0, taskerror = 0;
	vrv::patch::PatchInfoVec patches;
	std::string szPatchPath = appconfig.m_cascade_cfg.szPatchPath;
	while (!g_bstop)
	try
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		theApp.client->getClientStub().setFileProgressCallback(&onFileTransferProgress);
		if (appconfig.m_cascade_cfg.flux)
			theApp.fileDownload->setTransferRateBps(appconfig.m_cascade_cfg.fluxspeed * 1024);
		theApp.fileDownload->setDownloadToPath(szPatchPath);
		theApp.client->DownloadIndex1xml(*theApp.fileDownload);
		if (!bus.AnalyzeIndex1xml(szPatchPath + "\\index1.xml", patches))
		{
			vrvlog::SPD_LOG_CRITICAL("Analyze index1.xml failed");
			DeleteFileA((szPatchPath + "\\index1.xml").c_str());
		}
		else
			break;
	}
	catch (RCF::Exception& e)
	{
		vrvlog::SPD_LOG_ERROR("Download index1.xml failed ({0} {1})", 
			e.getErrorId(), e.getWhat());
	}

	if (!g_bstop)
	{
		int indxcount = patches.size();

		IDUIControlBase *pTopBase = pTopItem->GetCustomObj();
		IDUIStatic *pTopSize = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic *pTopError = (IDUIStatic *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
		IDUIProgressbar *pTopProgress = (IDUIProgressbar *)pTopBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);

		std::stringstream ss;
		ss << "0/" << indxcount;
		pTopSize->SetText(ss.str());
		pTopError->SetText(_T("0"));

		::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_CLEANITEMS, 0, 0, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
		szPatchPath = appconfig.m_cascade_cfg.szPatchPath + "\\";

		for (size_t idx = 0; idx < patches.size() && !g_bstop; ++idx)
		{
			vrv::patch::PatchInfoPtr patchptr = patches[idx];
			try
			{
				theApp.client->RequestPatchInfo(*patchptr);
			}
			catch (RCF::Exception& e)
			{
				vrvlog::SPD_LOG_WARN("Get patch file info failed ({0} {1})", 
					patches[idx]->szPatchName, e.getErrorId());
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			IDUITVItem *pItem = nullptr;
			::SendMessageTimeout(m_hWnd, UM_DOWNVIEW_PATCHITEM, (WPARAM)patchptr.get(), (LPARAM)&pItem, SMTO_ABORTIFHUNG , MESSAGE_TIMEOUT, 0);
			if (pItem == nullptr)
			{
				InsertErrorTaskToView(&patchptr, PATCH);
				continue;
			}

			m_curItem = pItem;
			IDUIControlBase* pItemBase = (IDUIControlBase*)pItem->GetCustomObj();
			IDUIStatic *pItemSize = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
			IDUIProgressbar *pItemProgress = (IDUIProgressbar *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
			IDUIStatic *pItemCrc = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskCrc"), TRUE);
			IDUIStatic *pItemDate = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);

			std::string szPatchFile = szPatchPath + patchptr->szPatchName;
			if (!MakeSureDirectoryExist(szPatchFile.c_str(), TRUE))
			{
				std::stringstream serr;
				serr << ++taskerror;
				pTopError->SetText(serr.str());
				vrvlog::SPD_LOG_ERROR("Patch path create failed ({0})", szPatchFile.c_str());
				InsertErrorTaskToView(&patchptr, PATCH);
				continue;
			}

			std::string szSha;
			if (GetFileSHA1(szPatchFile.c_str(), szSha) &&
				szSha == patchptr->szMd5)
			{
				++taskdone;
				if (pItemProgress)
					pItemProgress->SetPos(100);
			}
			else
			{
				std::string szPath = szPatchFile.substr(0, szPatchFile.find_last_of("\\"));

				try
				{
					theApp.client->getClientStub().setFileProgressCallback(&onFileTransferProgress);

					if (appconfig.m_cascade_cfg.flux)
						theApp.fileDownload->setTransferRateBps(appconfig.m_cascade_cfg.fluxspeed * 1024);

					theApp.fileDownload->setDownloadToPath(szPath);

					theApp.client->DownloadPatchFile(patchptr->szPatchName, *theApp.fileDownload);
					std::string szLocalpath = theApp.fileDownload->getLocalPath();
					++taskdone;
				}
				catch (RCF::Exception &e)
				{
					vrvlog::SPD_LOG_ERROR("Patch File: {0} download failed ({1})", szPatchFile.c_str(), e.getErrorId());
					InsertErrorTaskToView(&patchptr, PATCH);
					++taskerror;

				}

				//code == 0 ? ++taskdone : ++taskerror;
				//if (code)
				//InsertErrorTaskToView(&indexptr, INDEX);
			}

			pItemDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());

			//::SendMessage(m_hWnd, UM_DOWNVIEW_REFRESH, 0, 0);
			pItem->Refresh();

			std::stringstream scount, serr;
			scount << taskdone << "/" << indxcount;
			pTopSize->SetText(scount.str());

			serr << taskerror;
			pTopError->SetText(serr.str());

			if (pTopProgress)
			{
				short pos = (taskdone / (double)indxcount) * 100;
				pTopProgress->SetPos(pos);
			}
		}

	}

	if (g_bstop)
	{
		vrvlog::SPD_LOG_INFO("Cascade download thread has been stopped.");
		return false;
	}

	return true;
}