// PatchView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchView.h"
#include "afxdialogex.h"



// CPatchView �Ի���

IMPLEMENT_DYNAMIC(CPatchView, CDUIDialog)

CPatchView::CPatchView(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DOWNLOADVIEW_DIALOG, pParent)
	, m_hPatchStatics(this)
	, m_hPatchDown(this)
	, m_hPatchError(this)
{

}

CPatchView::~CPatchView()
{
}

void CPatchView::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchView, CDUIDialog)
	ON_WM_CREATE()
	ON_MESSAGE(DUI_TABMSG_SELCHANGED, &CPatchView::OnTabPageChanged)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPatchView ��Ϣ�������


int CPatchView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	m_hPatchStatics.Create(IDD_DIALOG_STATICS, this);
	m_hPatchDown.Create(IDD_DOWNLOAD_LISTVIEW, this);
	m_hPatchError.Create(IDD_DIALOG_ERROR, this);
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}

BOOL CPatchView::InitSknPath()
{
	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIDownView");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


BOOL CPatchView::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitControlLang();
	DHwnd(HwndSubObj)->Attach((OLE_HANDLE)HandleToLong(m_hPatchStatics.GetSafeHwnd()));
	DHwnd(HwndSubObj)->Attach((OLE_HANDLE)HandleToLong(m_hPatchDown.GetSafeHwnd()));
	DHwnd(HwndSubObj)->Attach((OLE_HANDLE)HandleToLong(m_hPatchError.GetSafeHwnd()));
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

void CPatchView::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDUIDialog::OnCancel();
}


void CPatchView::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (appconfig.m_mode_cfg.mode == http_mode)
		m_hPatchStatics.OnHttpStop();
	else
		m_hPatchStatics.OnCasStop();

	CDUIDialog::OnClose();
}


void CPatchView::InitControlLang()
{
	DStatic(Static_Tree)->SetText(g_lang.GetText(10001));
	IDUITabCtrlItem *pItem1 = DTab(DownTabCtrl)->GetItemByIndex(0);
	IDUITabCtrlItem *pItem2 = DTab(DownTabCtrl)->GetItemByIndex(1);
	IDUITabCtrlItem *pItem3 = DTab(DownTabCtrl)->GetItemByIndex(2);
	pItem1->SetText(g_lang.GetText(10002));
	pItem2->SetText(g_lang.GetText(10003));
	pItem3->SetText(g_lang.GetText(10004));
}