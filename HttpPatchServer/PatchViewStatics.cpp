// PatchViewStatics.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewStatics.h"
#include "afxdialogex.h"
#include "PatchBus.h"
#include <sstream>
#include "PatchView.h"
#include "MessageBox.h"
// CPatchViewStatics �Ի���


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
END_MESSAGE_MAP()


// CPatchViewStatics ��Ϣ�������

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
	// TODO: �ڴ����ר�ô����/����û���

	if (-1 == CDUIDialog::OnCreate(lpCreateStruct))
		return -1;
	return 0;
}


BOOL CPatchViewStatics::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	InsertIndexItem(0, 0);
	SetTimer(CHECKPATCH, 5000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



LRESULT CPatchViewStatics::InsertIndexItem(WPARAM wparam, LPARAM lparam)
{
	//����ģʽ���������Ǵ��ϼ���ȡ��
	if (appconfig.m_mode_cfg.mode == cascade_mode)
	{
		short nitem = DUI_pStatisticView->InsertItem(0, "����", 0, TRUE);
		IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
		IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
		IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
		pTaskName->SetText(_T("����"));
		pTaskSize->SetText("0/0");
		pTaskError->SetText(_T("0"));
	}
	else if (appconfig.m_mode_cfg.mode == http_mode)
	{
		int indexcount = bus.CalcIndexCount();
		std::stringstream ss;
		ss << "0/" << indexcount;

		short nitem = DUI_pStatisticView->InsertItem(0, "����", 0, TRUE);
		IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
		IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
		IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
		pTaskName->SetText(_T("����"));
		pTaskSize->SetText(ss.str());
		pTaskError->SetText(_T("0"));
	}
	DUI_pStatisticView->RefreshView();
	return 0;
}


void CPatchViewStatics::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDUIDialog::OnShowWindow(bShow, nStatus);
	// TODO: �ڴ˴������Ϣ����������
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
		short nitem = DUI_pStatisticView->InsertItem(nIndex++, "��������", 0, TRUE);
		IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
		IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
		IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);

		pTaskName->SetText("��������");
		pTaskSize->SetText("0/0");
		pTaskError->SetText("0");
	}
	else if (appconfig.m_mode_cfg.mode == http_mode)
	{
		std::string szProducts = appconfig.m_http_cfg.m_szProducts;
		char* pProduct = nullptr, *nxtProduct = nullptr;
		pProduct = strtok_s(const_cast<char*>(szProducts.c_str()), ";", &nxtProduct);
		while (pProduct)
		{
			std::string szProduct = pProduct;
			if (!szProduct.empty())
			{
				short nitem = DUI_pStatisticView->InsertItem(nIndex++, szProduct, 0, TRUE);
				IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
				IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
				IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
				IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
				IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);

				pTaskName->SetText(szProduct);
				pTaskSize->SetText("0/0");
				pTaskError->SetText("0");
				DUI_pStatisticView->RefreshView();
			}
			pProduct = strtok_s(NULL, ";", &nxtProduct);
		}
	}
	DUI_pStatisticView->RefreshView();
	return 0;
}


LRESULT CPatchViewStatics::OnSMLButtonUp(WPARAM wparam, LPARAM lparam)
{
	std::thread thread([=]()->void 
	{
		if (DBtn(BtnStart) == (ICmdButton*)wparam)
		{
			std::string szText = DBtn(BtnStart)->GetText();
			if (szText == "����")
			{
				DBtn(BtnStart)->SetText("��������");
				DBtn(BtnStart)->RedrawWindow(TRUE);
				DBtn(BtnStart)->EnableObject(FALSE, TRUE);

				//�������ﴦ������õ�
				if (theApp._thread.joinable())
					theApp._thread.join();

				::SendMessageTimeout(m_hWnd, UM_STATICVIEW_CLEANITEMS, 0, 0, SMTO_ABORTIFHUNG, 1500, 0);
				::SendMessageTimeout(m_hWnd, UM_STATICVIEW_INDEXITEM, 0, 0, SMTO_ABORTIFHUNG, 1500, 0);
				::SendMessageTimeout(m_hWnd, UM_STATICVIEW_PATCHITEM, 0, 0, SMTO_ABORTIFHUNG, 1500, 0);

				if (appconfig.m_mode_cfg.mode == http_mode)
				{
					if (appconfig.m_http_cfg.m_szPatchPath.empty())
					{
						CMessageBox msg;
						msg.ShowMessage("��ѡ�񲹶�����Ŀ¼");
						DBtn(BtnStart)->SetText("����");
						DBtn(BtnStart)->EnableObject(TRUE, TRUE);
						return;
					}
					else
					{
						OnHttpStart();
					}
				}
				else if (appconfig.m_mode_cfg.mode == cascade_mode)
				{
					if (appconfig.m_cascade_cfg.cascade)
					{
						OnCasStart();
					}
					else
					{
						CMessageBox msg;
						msg.ShowMessage("Webƽ̨δ��������ѡ��, �����ú����»�ȡ��������");
						DBtn(BtnStart)->SetText("����");
						DBtn(BtnStart)->EnableObject(TRUE, TRUE);
						return;
					}
				}

			}
			else if (szText == "ֹͣ")
			{
				int iRet = 1;
				if (lparam == 0)
				{
					CMessageBox msg;
					iRet = msg.ShowMessage("ȷ��ֹͣ������?", MB_OKCANCEL);
				}

				if (iRet == 1)
				{
					DBtn(BtnStart)->SetText("����ֹͣ");
					DBtn(BtnStart)->EnableObject(FALSE, TRUE);
					if (appconfig.m_mode_cfg.mode == http_mode)
					{
						OnHttpStop();
					}
					else if (appconfig.m_mode_cfg.mode == cascade_mode)
					{
						OnCasStop();
					}
					DBtn(BtnStart)->SetText("����");
					DBtn(BtnStart)->EnableObject(TRUE, TRUE);
				}

			}
		}
	});
	
	thread.detach();
	return 0;
}


void CPatchViewStatics::OnHttpStart()
{
	DBtn(BtnStart)->SetText("ֹͣ");
	DBtn(BtnStart)->EnableObject(TRUE, TRUE);
	g_bstop = false;

	theApp._thread = std::thread([p = this]()->void
	{
		CPatchViewStatics* pThis = (CPatchViewStatics*)p;
		CPatchView * pParent = (CPatchView*)pThis->GetParent();
		CPatchDownView *pDownView = (CPatchDownView *)pParent->GetDownView();
		CPatchViewError *pErrorView = (CPatchViewError *)pParent->GetErrorView();
		::SendMessage(pErrorView->m_hWnd, UM_ERRORVIEW_CLEANITEMS, 0, 0);
		ICmdButton* pBtnStart = (ICmdButton*)pThis->GetObjPtr("BtnStart", TRUE);
		IDUIListView* pListView = (IDUIListView*)pThis->GetObjPtr("ListViewDownCenter", TRUE);
		int cnt = pListView->GetItemCount();
		for (int i = 0; i < cnt; ++i)
		{
			IDUITVItem *pItem = (IDUITVItem *)pListView->GetAt(i);
			if (0 == i)
			{
				vrv::patch::PatchIndexVectorPtr indexes = bus.GetAllPatchIndexes();
				if (!pDownView->DownloadIndexesByCurl(pItem, indexes))
					break;
			}
			else
			{
				IDUIControlBase *pItemBase = pItem->GetCustomObj();
				IDUIStatic *pItemName = (IDUIStatic *)pItemBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
				std::string szName = pItemName->GetText();
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

					if (!pDownView->DownloadPatchesByCurl(pItem, patches))
						break;
				}
			}
		}
		pBtnStart->SetText("����");
	});
}

void CPatchViewStatics::OnHttpStop()
{
	g_bstop = true;
	theApp.StopByCurl();
}


void CPatchViewStatics::OnCasStart()
{
	DBtn(BtnStart)->SetText("ֹͣ");
	DBtn(BtnStart)->EnableObject(TRUE, TRUE);
	g_bstop = false;

	theApp._thread = std::thread([p = this]()->void
	{
		CPatchViewStatics* pThis = (CPatchViewStatics*)p;
		CPatchView * pParent = (CPatchView*)pThis->GetParent();
		CPatchDownView *pDownView = (CPatchDownView *)pParent->GetDownView();
		CPatchViewError *pErrorView = (CPatchViewError *)pParent->GetErrorView();
		::SendMessage(pErrorView->m_hWnd, UM_ERRORVIEW_CLEANITEMS, 0, 0);
		IDUIListView* pListView = (IDUIListView*)pThis->GetObjPtr("ListViewDownCenter", TRUE);
		ICmdButton* pBtnStart = (ICmdButton*)pThis->GetObjPtr("BtnStart", TRUE);
		if (!theApp.InitPatchClient())
		{
			if (!g_bstop)
			{
				CMessageBox msg;
				msg.ShowMessage("�����ϼ��������쳣,�����ϼ�����������");
			}
			pBtnStart->SetText("����");
			return;
		}

		if (pListView->GetItemCount() > 0)
		{
			//����Item
			IDUITVItem *pItem = (IDUITVItem *)pListView->GetAt(0);
			if (!pDownView->DownloadIndexesByRcf(pItem))
				return;

			//Ĭ��ģʽ��������Index1.xml������Index1.xml���ز�����Ϣ
			if (appconfig.m_cascade_cfg.index1)
			{
				IDUITVItem *pItem = (IDUITVItem *)pListView->GetAt(1);
				if (!pDownView->DownloadIndex1xmlByRcf(pItem))
					return;
			}
			else
			{
				IDUITVItem *pItem = (IDUITVItem *)pListView->GetAt(1);
				if (!pDownView->DownloadPatchesByRcf(pItem))
					return;
			}
		}
		pBtnStart->SetText("����");

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDUIDialog::OnTimer(nIDEvent);

	__time64_t long_time;
	_time64(&long_time);
	static __time64_t dwLastTime = long_time;

	timemode mTime = default_mode;
	std::string szNetTime = "0";
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
		std::stringstream ss;
		__time64_t dwTick;
		ss << szNetTime;
		ss >> dwTick;

		if (long_time - dwLastTime >= dwTick * 60)
		{
			std::string szText = DBtn(BtnStart)->GetText();
			if (szText == "����")
				OnSMLButtonUp((WPARAM)DBtn(BtnStart), 0);
			dwLastTime = long_time;
		}
	}
	break;
	case interval_mode:
	{
		int iDayoff = 0;
		std::stringstream ss;
		int iHour1, iMin1, iSec1, iHour2, iMin2, iSec2;
		std::string szBegin, szEnd, szHour1, szMin1, szSec1, szHour2, szMin2, szSec2;
		GetIntervalTime(szNetTime, szBegin, szEnd);
		GetTime(szBegin, szHour1, szMin1, szSec1);
		GetTime(szEnd, szHour2, szMin2, szSec2);
		iHour1 = atoi(szHour1.c_str());
		iMin1 = atoi(szMin1.c_str());
		iSec1 = atoi(szSec1.c_str());
		iHour2 = atoi(szHour2.c_str());
		iMin2 = atoi(szMin2.c_str());
		iSec2 = atoi(szSec2.c_str());

		if (iHour1 > iHour2)
			iDayoff = 1;
		CTime tmTimeNow = CTime::GetCurrentTime();
		CTime tmStart(tmTimeNow.GetYear(), tmTimeNow.GetMonth(), tmTimeNow.GetDay(), iHour1, iMin1, iSec1);
		CTime tmEnd = CTime(tmTimeNow.GetYear(), tmTimeNow.GetMonth(), tmTimeNow.GetDay(), 0, 0, 0)
			+ CTimeSpan(iDayoff, iHour2, iMin2, iSec2);
		CTimeSpan x1 = tmTimeNow - tmStart, x2 = tmEnd - tmTimeNow;

		std::string szText = DBtn(BtnStart)->GetText();
		if (x1.GetTotalSeconds() >= 0 && x2.GetTotalSeconds() >= 0)
		{
			if (szText == "����")
				OnSMLButtonUp((WPARAM)DBtn(BtnStart), 0);
		}
		else
		{
			if (szText == "ֹͣ")
				OnSMLButtonUp((WPARAM)DBtn(BtnStart), 1);
		}
		dwLastTime = long_time;
	}
	break;
	default:
		break;
	}
}
