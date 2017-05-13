// PatchViewError.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewError.h"
#include "afxdialogex.h"
#include "PatchBus.h"

// CPatchViewError �Ի���

#define DUI_pErrorView	DList(ListViewError)

IMPLEMENT_DYNAMIC(CPatchViewError, CDUIDialog)

CPatchViewError::CPatchViewError(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_ERROR, pParent)
	, m_pParent(pParent)
{

}

CPatchViewError::~CPatchViewError()
{
}

void CPatchViewError::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchViewError, CDUIDialog)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(UM_ERRORVIEW_INDEXITEM, &CPatchViewError::InsertIndexItem)
	ON_MESSAGE(UM_ERRORVIEW_PATCHITEM, &CPatchViewError::InsertPatchItem)
	ON_MESSAGE(UM_ERRORVIEW_CLEANITEMS, &CPatchViewError::CleanItems)
END_MESSAGE_MAP()

// CPatchViewError ��Ϣ�������

//bool CPatchViewError::InitDui()
//{
//	m_pDuiError = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUITaskError", HandleToLong(m_hWnd));
//	ASSERT(m_pDuiError);
//
//	m_pErrorView = (IDUIListView*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ListViewError", m_pDuiError, TRUE);
//	ASSERT(m_pErrorView);
//
//	return true;
//}
LRESULT CPatchViewError::InsertIndexItem(WPARAM wparam, LPARAM lparam)
{
	if (0 == wparam)
		return 0;

	vrv::patch::IndexInfoPtr indexptr = *(vrv::patch::IndexInfoPtr*)wparam;
	if (nullptr == indexptr)
		return 0;

	bus.m_taskErrorIndex.push_back(indexptr);
	std::string szIndexName;
	size_t pos = indexptr->szIndexName.find_last_of("\\");
	if (pos == std::string::npos)
		szIndexName = indexptr->szIndexName;
	else
		szIndexName = indexptr->szIndexName.substr(pos + 1);

	int nIndex = DUI_pErrorView->InsertItem(0, indexptr->szIndexName, 0, TRUE);
	IDUITVItem *pItem = (IDUITVItem *)DUI_pErrorView->GetAt(nIndex);
	IDUIControlBase* pCtrlBase = (IDUIControlBase*)pItem->GetCustomObj();
	IDUIStatic *pStcName = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
	IDUIStatic *pStcDate = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);
	pItem->SetData((OLE_HANDLE)indexptr.get());
	pStcName->SetText(szIndexName);
	pStcDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());
	DUI_pErrorView->RefreshView();
	return 0;
}


LRESULT CPatchViewError::InsertPatchItem(WPARAM wparam, LPARAM lparam)
{
	if (0 == wparam)
		return 0;

	vrv::patch::PatchInfoPtr patchptr = *(vrv::patch::PatchInfoPtr*)wparam;
	if (patchptr == nullptr)
		return 0;

	int nIndex = DUI_pErrorView->InsertItem(0, patchptr->szPatchName, 0, TRUE);
	IDUITVItem *pItem = (IDUITVItem *)DUI_pErrorView->GetAt(nIndex);
	IDUIControlBase* pCtrlBase = (IDUIControlBase*)pItem->GetCustomObj();
	IDUIStatic *pStcName = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskName"), TRUE);
	IDUIStatic *pStcDate = (IDUIStatic *)pCtrlBase->GetObjectByCaption(DUIOBJTYPE_PLUGIN, _T("TaskDate"), TRUE);
	pItem->SetData((OLE_HANDLE)patchptr.get());
	pStcName->SetText(patchptr->szPatchName);
	pStcName->SetTooltip(patchptr->MakeToolTipText());
	pStcDate->SetText(CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S").GetString());
	DUI_pErrorView->RefreshView();
	return 0;
}

LRESULT CPatchViewError::CleanItems(WPARAM wparam, LPARAM lparam)
{
	DUI_pErrorView->DeleteAllItems();
	return 0;
}

BOOL CPatchViewError::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(-1 == CDUIDialog::OnCreate(lpCreateStruct))
		return -1;

	return 0;
}

BOOL CPatchViewError::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUITaskError");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


CWnd* CPatchViewError::GetParent()
{
	return m_pParent;
}

void CPatchViewError::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDUIDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
}
