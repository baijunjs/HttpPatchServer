// PatchViewStatics.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewStatics.h"
#include "afxdialogex.h"


// CPatchViewStatics 对话框

IMPLEMENT_DYNAMIC(CPatchViewStatics, CDialogEx)

CPatchViewStatics::CPatchViewStatics(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_STATICS, pParent)
{

}

CPatchViewStatics::~CPatchViewStatics()
{
}

void CPatchViewStatics::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchViewStatics, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPatchViewStatics 消息处理程序


bool CPatchViewStatics::InitDui()
{
	m_pDuiStatic = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIDownStatics", HandleToLong(m_hWnd));
	ASSERT(m_pDuiStatic);

	m_pStaticView = (IDUIListView*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ListViewDownCenter", m_pDuiStatic, TRUE);
	ASSERT(m_pStaticView);

	m_pProgressbar = (IDUIProgressbar*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ProgressBar", m_pDuiStatic, TRUE);
	ASSERT(m_pProgressbar);

	return true;
}


int CPatchViewStatics::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (-1 == CDialogEx::OnCreate(lpCreateStruct))
		return -1;

	if (!InitDui())
		return -1;

	return 0;
}
