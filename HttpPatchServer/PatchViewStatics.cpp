// PatchViewStatics.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewStatics.h"
#include "afxdialogex.h"
#include "PatchBus.h"
#include <sstream>
#include "PatchView.h"
#include "MessageBox.h"
// CPatchViewStatics 对话框


#define DUI_pStatisticView DList(ListViewDownCenter)

#define CHECKPATCH			1
extern bool g_bstop;

IMPLEMENT_DYNAMIC(CPatchViewStatics, CDUIDialog)

CPatchViewStatics::CPatchViewStatics(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_STATICS, pParent)
{
	m_pParent = pParent;
}

CPatchViewStatics::~CPatchViewStatics()
{

}

void CPatchViewStatics::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CPatchViewStatics, CDUIDialog)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_MESSAGE(UM_STATICVIEW_INDEXITEM, &CPatchViewStatics::InsertIndexItem)
	ON_MESSAGE(UM_STATICVIEW_PATCHITEM, &CPatchViewStatics::InsertProductsItems)
	ON_MESSAGE(UM_STATICVIEW_CLEANITEMS, &CPatchViewStatics::CleanItems)
	ON_MESSAGE(UM_STATICVIEW_SETTEXT, &CPatchViewStatics::OnSetText)
END_MESSAGE_MAP()


// CPatchViewStatics 消息处理程序

BOOL CPatchViewStatics::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIDownStatics");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


int CPatchViewStatics::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (-1 == CDUIDialog::OnCreate(lpCreateStruct))
		return -1;
	return 0;
}


BOOL CPatchViewStatics::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitControlLang();
	InsertIndexItem(0, 0);
	SetTimer(CHECKPATCH, 5000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



LRESULT CPatchViewStatics::InsertIndexItem(WPARAM wparam, LPARAM lparam)
{
	//级联模式索引个数是从上级获取的
	if (appconfig.m_mode_cfg.mode == cascade_mode)
	{
		short nitem = DUI_pStatisticView->InsertItem(0, g_lang.GetText(10052), 0, TRUE);
		IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
		IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
		IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
		pTaskName->SetText(g_lang.GetText(10052));
		pTaskSize->SetText(_T("0/0"));
		pTaskError->SetText(_T("0"));
		DUI_pStatisticView->RefreshView();
	}
	else if (appconfig.m_mode_cfg.mode == http_mode)
	{
		int indexcount = bus.CalcIndexCount();
		std::tstringstream ss;
		ss << "0/" << indexcount;

		short nitem = DUI_pStatisticView->InsertItem(0, g_lang.GetText(10052), 0, TRUE);
		IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
		IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
		IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
		pTaskName->SetText(g_lang.GetText(10052));
		pTaskSize->SetText(ss.str());
		pTaskError->SetText(_T("0"));
		DUI_pStatisticView->RefreshView();
	}
	return 0;
}


void CPatchViewStatics::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDUIDialog::OnShowWindow(bShow, nStatus);
	// TODO: 在此处添加消息处理程序代码
}

LRESULT CPatchViewStatics::CleanItems(WPARAM wparam, LPARAM lparam)
{
	DUI_pStatisticView->DeleteAllItems();
	return 0;
}

LRESULT CPatchViewStatics::InsertProductsItems(WPARAM wparam, LPARAM lparam)
{
	int nIndex = DUI_pStatisticView->GetItemCount();
	if (appconfig.m_mode_cfg.mode == cascade_mode)
	{
		short nitem = DUI_pStatisticView->InsertItem(nIndex++, g_lang.GetText(10053), 0, TRUE);
		IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
		IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
		IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);

		pTaskName->SetText(g_lang.GetText(10053));
		pTaskSize->SetText(_T("0/0"));
		pTaskError->SetText(_T("0"));
		DUI_pStatisticView->RefreshView();
	}
	else if (appconfig.m_mode_cfg.mode == http_mode)
	{
		std::tstring szProducts = appconfig.m_http_cfg.m_szProducts;
		TCHAR* pProduct = nullptr, *nxtProduct = nullptr;
		pProduct = _tcstok_s(const_cast<TCHAR*>(szProducts.c_str()), _T(";"), &nxtProduct);
		while (pProduct)
		{
			std::tstring szProduct = pProduct;
			if (!szProduct.empty())
			{
				short nitem = DUI_pStatisticView->InsertItem(nIndex++, szProduct, 0, TRUE);
				IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
				IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
				IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
				IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
				IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);

				pTaskName->SetText(szProduct);
				pTaskSize->SetText(_T("0/0"));
				pTaskError->SetText(_T("0"));
				DUI_pStatisticView->RefreshView();
			}
			pProduct = _tcstok_s(NULL, _T(";"), &nxtProduct);
		}
	}
	return 0;
}


LRESULT CPatchViewStatics::OnSMLButtonUp(WPARAM wparam, LPARAM lparam)
{
	if (DBtn(BtnStart) == (ICmdButton*)wparam)
	{
		std::tstring szText = DBtn(BtnStart)->GetText();
		if (szText == g_lang.GetText(10049))
		{
			if (appconfig.m_mode_cfg.mode == http_mode)
			{

				if (appconfig.m_http_cfg.m_szPatchPath.empty())
				{
					CMessageBox msg;
					msg.ShowMessage(g_lang.GetText(10057));
					return 0;
				}
			}
			else if (appconfig.m_mode_cfg.mode == cascade_mode)
			{
				if (!appconfig.m_cascade_cfg.cascade)
				{
					CMessageBox msg;
					msg.ShowMessage(g_lang.GetText(10058));
					return 0;
				}
			}

			DBtn(BtnStart)->SetText(g_lang.GetText(10051));
			DBtn(BtnStart)->RedrawWindow(TRUE);
			DBtn(BtnStart)->EnableObject(FALSE, TRUE);

			//放在这里处理是最好的
			if (theApp._thread.joinable())
				theApp._thread.join();

			CleanItems(0, 0);
			InsertIndexItem(0, 0);
			InsertProductsItems(0, 0);
			//::SendMessageTimeout(m_hWnd, UM_STATICVIEW_CLEANITEMS, 0, 0, SMTO_BLOCK , 1500, 0);
			//::SendMessageTimeout(m_hWnd, UM_STATICVIEW_INDEXITEM, 0, 0, SMTO_BLOCK , 1500, 0);
			//::SendMessageTimeout(m_hWnd, UM_STATICVIEW_PATCHITEM, 0, 0, SMTO_BLOCK , 1500, 0);

			if (appconfig.m_mode_cfg.mode == http_mode)
			{
				OnHttpStart();
			}
			else if (appconfig.m_mode_cfg.mode == cascade_mode)
			{
				OnCasStart();
			}

		}
		else if (szText == g_lang.GetText(10050))
		{
			int iRet = 1;
			if (lparam == 0)
			{
				CMessageBox msg;
				iRet = msg.ShowMessage(g_lang.GetText(10059), MB_OKCANCEL);
			}

			if (iRet == 1)
			{
				DBtn(BtnStart)->SetText(g_lang.GetText(10056));
				DBtn(BtnStart)->EnableObject(FALSE, TRUE);
				if (appconfig.m_mode_cfg.mode == http_mode)
				{
					OnHttpStop();
				}
				else if (appconfig.m_mode_cfg.mode == cascade_mode)
				{
					OnCasStop();
				}
				DBtn(BtnStart)->SetText(g_lang.GetText(10049));
				DBtn(BtnStart)->EnableObject(TRUE, TRUE);
			}

		}
	}
	return 0;
}


void CPatchViewStatics::OnHttpStart()
{

	theApp._thread = std::thread([=]()->void
	{
		g_bstop = false;
		DBtn(BtnStart)->SetText(g_lang.GetText(10050));
		DBtn(BtnStart)->EnableObject(TRUE, TRUE);
		CPatchView * pParent = (CPatchView*)GetParent();
		CPatchDownView *pDownView = (CPatchDownView *)pParent->GetDownView();
		CPatchViewError *pErrorView = (CPatchViewError *)pParent->GetErrorView();
		::SendMessage(pErrorView->m_hWnd, UM_ERRORVIEW_CLEANITEMS, 0, 0);
		int cnt = DUI_pStatisticView->GetItemCount();
		for (int i = 0; i < cnt; ++i)
		{
			IDUITVItem *pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(i);
			pItem->Refresh();
			if (0 == i)
			{
				vrv::patch::PatchIndexVectorPtr indexes = bus.GetAllPatchIndexes();
				if (!pDownView->DownloadIndexesByCurl(m_hWnd, i, indexes))
					break;
			}
			else
			{
				IDUIControlBase *pItemBase = pItem->GetCustomObj();
				IDUIStatic *pItemName = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
				std::tstring szName = pItemName->GetText();
				vrv::patch::PatchIndexVectorPtr patches = bus.FindPatchIndexVecByProductName(szName);
				vrv::patch::PatchIndexVectorPtr lans = bus.FindLanguageIndexVec();

				ILoadIndex *pLoad = CPackInterface::getLoadIndexObject();
				for (size_t i = 0; i < patches->patchindexes.size(); i++)
				{
					vrv::patch::PatchIndexPtr patchIndex = patches->patchindexes[i];
					patchIndex->load_product_index(pLoad);
				}

				for (size_t i = 0; i < lans->patchindexes.size(); i++)
				{
					vrv::patch::PatchIndexPtr patchIndex = lans->patchindexes[i];
					patchIndex->load_language_index(pLoad);
				}

				TOptionCondition option;
				option.nUseIntranetPatch = 0;
				option.nMinLoad = 100;
				pLoad->SetOption(option);
				HRESULT hret = pLoad->LoadFile();
				if (hret == S_OK)
				{
					int icount = pLoad->GetCount();

					vrv::patch::PatchInfoVec patches;
					for (int i = 0; i < icount; ++i)
					{
						IPatchItem *pItem = pLoad->GetPatchByIndex(i);
						vrv::patch::PatchInfoPtr patch = bus.GetPatchInfo(pItem);
						patches.push_back(patch);
					}

					CPackInterface::FreeLoadIndexObject(pLoad);

					if (!pDownView->DownloadPatchesByCurl(m_hWnd, i, patches))
						break;
				}
			}
		}
		DBtn(BtnStart)->SetText(g_lang.GetText(10049));
	});
}

void CPatchViewStatics::OnHttpStop()
{
	g_bstop = true;
	theApp.StopByCurl();
}


void CPatchViewStatics::OnCasStart()
{
	theApp._thread = std::thread([=]()->void
	{
		g_bstop = false;
		DBtn(BtnStart)->SetText(g_lang.GetText(10050));
		DBtn(BtnStart)->EnableObject(TRUE, TRUE);
		CPatchView * pParent = (CPatchView*)GetParent();
		CPatchDownView *pDownView = (CPatchDownView *)pParent->GetDownView();
		CPatchViewError *pErrorView = (CPatchViewError *)pParent->GetErrorView();
		::SendMessage(pErrorView->m_hWnd, UM_ERRORVIEW_CLEANITEMS, 0, 0);
		if (!theApp.InitPatchClient())
		{
			if (!g_bstop)
			{
				CMessageBox msg;
				msg.ShowMessage(g_lang.GetText(10060));
			}
			DBtn(BtnStart)->SetText(g_lang.GetText(10049));
			return;
		}

		if (DUI_pStatisticView->GetItemCount() > 0)
		{
			//索引Item
			IDUITVItem *pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(0);
			if (!pDownView->DownloadIndexesByRcf(m_hWnd, 0))
				return;

			//默认模式，先请求Index1.xml，根据Index1.xml下载补丁信息
			if (appconfig.m_cascade_cfg.index1)
			{
				IDUITVItem *pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(1);
				if (!pDownView->DownloadIndex1xmlByRcf(m_hWnd, 1))
					return;
			}
			else
			{
				IDUITVItem *pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(1);
				if (!pDownView->DownloadPatchesByRcf(m_hWnd, 1))
					return;
			}
		}
		DBtn(BtnStart)->SetText(g_lang.GetText(10049));

	});
}

void CPatchViewStatics::OnCasStop()
{
	g_bstop = true;
	theApp.StopByRcf();
}

CWnd* CPatchViewStatics::GetParent()
{
	return m_pParent;
}

void CPatchViewStatics::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDUIDialog::OnTimer(nIDEvent);

	__time64_t long_time;
	_time64(&long_time);
	static __time64_t dwLastTime = long_time;

	timemode mTime = default_mode;
	std::tstring szNetTime = _T("0");
	if (appconfig.m_mode_cfg.mode == cascade_mode)
	{
		mTime = appconfig.m_cascade_cfg.mode;
		szNetTime = appconfig.m_cascade_cfg.sznettime;
	}
	else if (appconfig.m_mode_cfg.mode == http_mode)
	{
		mTime = appconfig.m_http_cfg.mode;
		szNetTime = appconfig.m_http_cfg.sznettime;
	}

	switch (mTime)
	{
	case default_mode:
		dwLastTime = long_time;
		break;
	case period_mode:
	{
		std::tstringstream ss;
		__time64_t dwTick;
		ss << szNetTime;
		ss >> dwTick;

		if (long_time - dwLastTime >= dwTick * 60)
		{
			std::tstring szText = DBtn(BtnStart)->GetText();
			if (szText == g_lang.GetText(10049))
				OnSMLButtonUp((WPARAM)DBtn(BtnStart), 0);
			dwLastTime = long_time;
		}
	}
	break;
	case interval_mode:
	{
		int iDayoff = 0;
		std::tstringstream ss;
		int iHour1, iMin1, iSec1, iHour2, iMin2, iSec2;
		std::tstring szBegin, szEnd, szHour1, szMin1, szSec1, szHour2, szMin2, szSec2;
		GetIntervalTime(szNetTime, szBegin, szEnd);
		GetTime(szBegin, szHour1, szMin1, szSec1);
		GetTime(szEnd, szHour2, szMin2, szSec2);
		iHour1 = _ttoi(szHour1.c_str());
		iMin1 = _ttoi(szMin1.c_str());
		iSec1 = _ttoi(szSec1.c_str());
		iHour2 = _ttoi(szHour2.c_str());
		iMin2 = _ttoi(szMin2.c_str());
		iSec2 = _ttoi(szSec2.c_str());

		if (iHour1 > iHour2)
			iDayoff = 1;
		CTime tmTimeNow = CTime::GetCurrentTime();
		CTime tmStart(tmTimeNow.GetYear(), tmTimeNow.GetMonth(), tmTimeNow.GetDay(), iHour1, iMin1, iSec1);
		CTime tmEnd = CTime(tmTimeNow.GetYear(), tmTimeNow.GetMonth(), tmTimeNow.GetDay(), 0, 0, 0)
			+ CTimeSpan(iDayoff, iHour2, iMin2, iSec2);
		CTimeSpan x1 = tmTimeNow - tmStart, x2 = tmEnd - tmTimeNow;

		std::tstring szText = DBtn(BtnStart)->GetText();
		if (x1.GetTotalSeconds() >= 0 && x2.GetTotalSeconds() >= 0)
		{
			if (szText == g_lang.GetText(10049))
				OnSMLButtonUp((WPARAM)DBtn(BtnStart), 0);
		}
		else
		{
			if (szText == g_lang.GetText(10050))
				OnSMLButtonUp((WPARAM)DBtn(BtnStart), 1);
		}
		dwLastTime = long_time;
	}
	break;
	default:
		break;
	}
}


void CPatchViewStatics::InitControlLang()
{
	DBtn(BtnStart)->SetText(g_lang.GetText(10049));
}

LRESULT CPatchViewStatics::OnSetText(WPARAM wparam, LPARAM lparam)
{
	int nCol = HIWORD(wparam);
	int nRow = LOWORD(wparam);
	IDUITVItem *pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nRow);
	if (pItem == nullptr)
		return 0;

	IDUIControlBase* pItemBase = (IDUIControlBase*)pItem->GetCustomObj();
	if (pItemBase == nullptr)
		return 0;

	switch (nCol)
	{
	case 1:
	{
		IDUIStatic *pItemName = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		if (pItemName)
			pItemName->SetText((const TCHAR*)lparam);
	}
	break;
	case 2:
	{
		IDUIStatic *pItemSize = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		if (pItemSize)
			pItemSize->SetText((const TCHAR*)lparam);
	}
	break;
	case 3:
	{
		IDUIProgressbar *pItemProgress = (IDUIProgressbar *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("ProgressBar"), TRUE);
		if (pItemProgress)
			pItemProgress->SetPos((int)lparam);
	}
	break;
	case 4:
	{
		IDUIStatic *pItemError = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
		if (pItemError)
			pItemError->SetText((const TCHAR*)lparam);
	}
	break;
	default:
		break;
	}

	pItemBase->RedrawWindow(TRUE);
	return 0;
}