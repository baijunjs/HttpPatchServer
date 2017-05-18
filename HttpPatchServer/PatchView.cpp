// PatchView.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchView.h"
#include "afxdialogex.h"



// CPatchView 对话框

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


// CPatchView 消息处理程序


int CPatchView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	m_hPatchStatics.Create(IDD_DIALOG_STATICS, this);
	m_hPatchDown.Create(IDD_DOWNLOAD_LISTVIEW, this);
	m_hPatchError.Create(IDD_DIALOG_ERROR, this);
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
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

	// TODO:  在此添加额外的初始化
	InitControlLang();
	DHwnd(HwndSubObj)->Attach((OLE_HANDLE)HandleToLong(m_hPatchStatics.GetSafeHwnd()));
	DHwnd(HwndSubObj)->Attach((OLE_HANDLE)HandleToLong(m_hPatchDown.GetSafeHwnd()));
	DHwnd(HwndSubObj)->Attach((OLE_HANDLE)HandleToLong(m_hPatchError.GetSafeHwnd()));
	m_hPatchStatics.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
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
	// TODO: 在此添加专用代码和/或调用基类

	CDUIDialog::OnCancel();
}


void CPatchView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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