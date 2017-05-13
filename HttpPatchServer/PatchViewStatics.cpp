// PatchViewStatics.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewStatics.h"
#include "afxdialogex.h"
#include "PatchBus.h"
#include <sstream>
#include "PatchView.h"
// CPatchViewStatics 对话框


#define DUI_pStatisticView DList(ListViewDownCenter)


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
	ON_MESSAGE(DUISM_LBUTTONUP, &CPatchViewStatics::OnButtonDispatcher)
END_MESSAGE_MAP()


// CPatchViewStatics 消息处理程序


//bool CPatchViewStatics::InitDui()
//{
//	m_pDuiStatic = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIDownStatics", HandleToLong(m_hWnd));
//	ASSERT(m_pDuiStatic);
//
//	m_pStaticView = (IDUIListView*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ListViewDownCenter", m_pDuiStatic, TRUE);
//	ASSERT(m_pStaticView);
//
//	m_pProgressbar = (IDUIProgressbar*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ProgressBar", m_pDuiStatic, TRUE);
//	ASSERT(m_pProgressbar);
//
//	m_pbtnStart = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnStart", m_pDuiStatic, TRUE);
//	ASSERT(m_pbtnStart);
//
//	return true;
//}


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
	//m_pProgressbar->SetPos(0);
	//m_pProgressbar->SetVisible(FALSE, TRUE, TRUE);
	//m_pStaticView->InsertColumn(0, "名称", 150);
	//m_pStaticView->InsertColumn(1, "已下载/总数", 100);
	//m_pStaticView->InsertColumn(2, "进度", 150);
	//m_pStaticView->InsertColumn(3, "错误数", 100);
	//m_pStaticView->InsertColumn(4, "消息", 300);
	//m_pStaticView->SetColumnUserModule(2, m_pProgressbar);

	InsertIndexItem();

	InsertProductsItems();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CPatchViewStatics::InsertIndexItem()
{
	int indexcount = bus.CalcIndexCount();
	std::stringstream ss;
	ss << "0/" << indexcount;

	short nitem = DUI_pStatisticView->InsertItem(0, "索引", 0, TRUE);
	IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
	IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
	IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
	IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
	IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);
	pTaskName->SetText(_T("索引"));
	pTaskSize->SetText(ss.str());
	pTaskError->SetText(_T("0"));
	DUI_pStatisticView->RefreshView();
}


void CPatchViewStatics::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDUIDialog::OnShowWindow(bShow, nStatus);
	// TODO: 在此处添加消息处理程序代码
	//if (bShow)
		//m_pStaticView->RefreshView();
}

void CPatchViewStatics::DeleteAllItems()
{
	DUI_pStatisticView->DeleteAllItems();
}


void CPatchViewStatics::InsertProductsItems()
{
	int nIndex = DUI_pStatisticView->GetItemCount();
	if (appconfig.m_mode_cfg.mode == cascade_mode)
	{
		short nitem = DUI_pStatisticView->InsertItem(nIndex++, "级联补丁", 0, TRUE);
		IDUITVItem * pItem = (IDUITVItem *)DUI_pStatisticView->GetAt(nitem);
		IDUIControlBase *pCtrlBase = pItem->GetCustomObj();
		IDUIStatic* pTaskName = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
		IDUIStatic* pTaskSize = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskSize"), TRUE);
		IDUIStatic* pTaskError = (IDUIStatic*)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskError"), TRUE);

		pTaskName->SetText("级联补丁");
		pTaskSize->SetText("0/0");
		pTaskError->SetText("0");
		DUI_pStatisticView->RefreshView();
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
}

//void CPatchViewStatics::SetItemProgressbarPosition(short nItem, short pos)
//{
//	IDUITVItem *pItem = (IDUITVItem*)m_pStaticView->GetAt(nItem);
//	IDUIUnitItem *pUnitItem = pItem->GetUnitItem(2);
//	IDUIProgressbar * pDUIProgressBar = (IDUIProgressbar*)pUnitItem->GetControlBase();
//	if (pDUIProgressBar)
//		pDUIProgressBar->SetPos(pos);
//}

LRESULT CPatchViewStatics::OnButtonDispatcher(WPARAM wparam, LPARAM lparam)
{
	if (DBtn(BtnStart) == (ICmdButton*)wparam)
	{
		std::string szText = DBtn(BtnStart)->GetText();
		if (szText == "启动")
		{
			if (appconfig.m_mode_cfg.mode == http_mode)
			{
				OnHttpStart();
			}
			else
			{
				OnCasStart();
			}

			DBtn(BtnStart)->SetText("停止");
		}
		else if (szText == "停止")
		{
			DBtn(BtnStart)->EnableObject(FALSE, TRUE);
			DBtn(BtnStart)->SetText("正在停止");
			if (appconfig.m_mode_cfg.mode == http_mode)
			{
				OnHttpStop();
			}
			else
			{
				OnCasStop();
			}

		}
	}
	return 0;
}


void CPatchViewStatics::OnHttpStart()
{
	//AfxBeginThread([](LPVOID p)->unsigned int
	theApp._thread = std::thread([p=this]()->void
	{
		CPatchViewStatics* pThis = (CPatchViewStatics*)p;
		CPatchView * pParent = (CPatchView*)pThis->GetParent();
		CPatchDownView *pDownView = (CPatchDownView *)pParent->GetDownView();
		CPatchViewError *pErrorView = (CPatchViewError *)pParent->GetErrorView();
		::SendMessage(pErrorView->m_hWnd, UM_ERRORVIEW_CLEANITEMS, 0, 0);

		IDUIListView* pListView = (IDUIListView*)pThis->GetObjPtr("ListViewDownCenter", TRUE);
		int cnt = pListView->GetItemCount();
		for (int i = 0; i < cnt; ++i)
		{
			//std::this_thread::sleep_for(std::chrono::seconds(2));

			pThis->m_curitem = i;
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
					{
						
						break;
					}
				}
			}
		}
	});
}

void CPatchViewStatics::OnHttpStop()
{
	std::thread thread([p = this]()->void
	{
		CPatchViewStatics* pThis = (CPatchViewStatics*)p;
		theApp.StopByCurl();
		if (theApp._thread.joinable())
			theApp._thread.join();
		ICmdButton* pBtn = (ICmdButton*)pThis->GetObjPtr("BtnStart", TRUE);
		pBtn->SetText("停止");
		pBtn->EnableObject(TRUE, TRUE);

	});
	thread.detach();
}


void CPatchViewStatics::OnCasStart()
{
	theApp._thread = std::thread([p=this]()->void 
	{
		theApp.InitPatchClient();
		CPatchViewStatics* pThis = (CPatchViewStatics*)p;
		CPatchView * pParent = (CPatchView*)pThis->GetParent();
		CPatchDownView *pDownView = (CPatchDownView *)pParent->GetDownView();
		CPatchViewError *pErrorView = (CPatchViewError *)pParent->GetErrorView();
		::SendMessage(pErrorView->m_hWnd, UM_ERRORVIEW_CLEANITEMS, 0, 0);
		IDUIListView* pListView = (IDUIListView*)pThis->GetObjPtr("ListViewDownCenter", TRUE);
		int cnt = pListView->GetItemCount();
		for (int i = 0; i < cnt; ++i)
		{
			//std::this_thread::sleep_for(std::chrono::seconds(2));

			pThis->m_curitem = i;
			IDUITVItem *pItem = (IDUITVItem *)pListView->GetAt(i);
			if (0 == i)
			{
				if (!pDownView->DownloadIndexesByRcf(pItem))
					break;
			}
			else
			{
				if (!pDownView->DownloadPatchesByRcf(pItem))
					break;
			}
		}
	});
}

void CPatchViewStatics::OnCasStop()
{
	std::thread thread([p = this]()->void
	{
		CPatchViewStatics* pThis = (CPatchViewStatics*)p;
		theApp.StopByRcf();
		if (theApp._thread.joinable())
			theApp._thread.join();
		ICmdButton* pBtn = (ICmdButton*)pThis->GetObjPtr("BtnStart", TRUE);
		pBtn->SetText("停止");
		pBtn->EnableObject(TRUE, TRUE);
	});
	thread.detach();
}

CWnd* CPatchViewStatics::GetParent()
{
	return m_pParent;
}