// PathDownloadListView.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PathDownloadListView.h"
#include "afxdialogex.h"
#include <sstream>

// CPathDownloadListView 对话框

IMPLEMENT_DYNAMIC(CPatchDownView, CDialogEx)

CPatchDownView::CPatchDownView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DOWNLOAD_LISTVIEW, pParent)
{

}

CPatchDownView::~CPatchDownView()
{
}

void CPatchDownView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchDownView, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPathDownloadListView 消息处理程序


BOOL CPatchDownView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


#if 0
		m_pDuiListView->InsertColumn(0, "名称", 200);
		m_pDuiListView->InsertColumn(1, "进度", 100);
		m_pDuiListView->InsertColumn(2, "大小", 50);

		m_pDuiListView->SetColumnUserModule(1, m_pDuiProgressBar);
	std::ostringstream Num;
	for (size_t i = 0; i < 100; ++i)
	{
		Num.str("");
		Num << (int)i;
		short nItem = m_pDuiListView->InsertItem(i, "", 0, TRUE);
		//m_pDuiListView->AppendItemText(nItem, 0, Num.str(), "", TRUE);
		m_pDuiListView->AppendItemText(nItem, 0, "123456.txt", "", TRUE);
		//m_pDuiListView->AppendItemText(nItem, 2, "100", "", TRUE);
		m_pDuiListView->AppendItemText(nItem, 2, "947896", "", TRUE);
	}


	//nItem = m_pDuiListView->InsertItem(1, "", 0, TRUE);
	//m_pDuiListView->AppendItemText(nItem, 0, "123456.txt", "", TRUE);
	//m_pDuiListView->AppendItemText(nItem, 1, "100", "", TRUE);
	//m_pDuiListView->AppendItemText(nItem, 2, "947896", "", TRUE);
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


int CPatchDownView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!InitListViewDui())
		return -1;

	return 0;
}

bool CPatchDownView::InitListViewDui()
{
	m_pDuiListForm = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIDownTask", HandleToLong(m_hWnd));
	ASSERT(m_pDuiListForm);

	m_pDuiListView = (IDUIListView*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ListViewDownTask", m_pDuiListForm, TRUE);
	ASSERT(m_pDuiListView);

	m_pDuiProgressBar = (IDUIProgressbar*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ProgressBar", m_pDuiListForm, TRUE);
	ASSERT(m_pDuiProgressBar);
	//m_pDuiProgressBar->SetVisible(FALSE, FALSE, TRUE);
	return true;
}