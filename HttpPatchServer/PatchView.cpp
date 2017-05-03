// PatchView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchView.h"
#include "afxdialogex.h"


// CPatchView �Ի���

IMPLEMENT_DYNAMIC(CPatchView, CDialogEx)

CPatchView::CPatchView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DOWNLOADVIEW_DIALOG, pParent)
{

}

CPatchView::~CPatchView()
{
}

void CPatchView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchView, CDialogEx)
	ON_WM_CREATE()
	ON_MESSAGE(DUI_TABMSG_SELCHANGED, &CPatchView::OnTabPageChanged)
END_MESSAGE_MAP()


// CPatchView ��Ϣ�������


int CPatchView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	if (!InitPatchViewDui())
		return -1;

	return 0;
}

bool CPatchView::InitPatchViewDui()
{
	m_pDuiPatchView = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIDownView", HandleToLong(m_hWnd));
	ASSERT(m_pDuiPatchView);

	m_pDuiTabView = (IDUITabCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "DownTabCtrl", m_pDuiPatchView, TRUE);
	ASSERT(m_pDuiTabView);

	m_pDuiListOwner = (IDUIHwndObj*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "HwndSubObj", m_pDuiPatchView, TRUE);
	ASSERT(m_pDuiListOwner);

	return true;
}


BOOL CPatchView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_hPatchStatics.Create(IDD_DIALOG_STATICS, this);
	m_pDuiListOwner->Attach((OLE_HANDLE)HandleToLong(m_hPatchStatics.GetSafeHwnd()));

	m_hPatchDown.Create(IDD_DOWNLOAD_LISTVIEW, this);
	m_pDuiListOwner->Attach((OLE_HANDLE)HandleToLong(m_hPatchDown.GetSafeHwnd()));

	m_hPatchError.Create(IDD_DIALOG_ERROR, this);
	m_pDuiListOwner->Attach((OLE_HANDLE)HandleToLong(m_hPatchError.GetSafeHwnd()));

	m_hPatchStatics.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


LRESULT CPatchView::OnTabPageChanged(WPARAM wparam, LPARAM lparam)
{
	if (0 == wparam)
	{
		m_hPatchStatics.ShowWindow(SW_SHOWNORMAL);
		m_hPatchDown.ShowWindow(SW_HIDE);
		m_hPatchError.ShowWindow(SW_HIDE);
	}


	else if (1 == wparam)
	{
		m_hPatchStatics.ShowWindow(SW_HIDE);
		m_hPatchDown.ShowWindow(SW_SHOWNORMAL);
		m_hPatchError.ShowWindow(SW_HIDE);
	}

	else if (2 == wparam)
	{
		m_hPatchStatics.ShowWindow(SW_HIDE);
		m_hPatchDown.ShowWindow(SW_HIDE);
		m_hPatchError.ShowWindow(SW_SHOWNORMAL);
	}

	return 0;
}