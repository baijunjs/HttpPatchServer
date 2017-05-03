// PatchViewError.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewError.h"
#include "afxdialogex.h"


// CPatchViewError 对话框

IMPLEMENT_DYNAMIC(CPatchViewError, CDialogEx)

CPatchViewError::CPatchViewError(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ERROR, pParent)
{

}

CPatchViewError::~CPatchViewError()
{
}

void CPatchViewError::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchViewError, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPatchViewError 消息处理程序

bool CPatchViewError::InitDui()
{
	m_pDuiError = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUITaskError", HandleToLong(m_hWnd));
	ASSERT(m_pDuiError);

	m_pErrorView = (IDUIListView*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ListViewError", m_pDuiError, TRUE);
	ASSERT(m_pErrorView);

	return true;
}

BOOL CPatchViewError::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(-1 == CDialogEx::OnCreate(lpCreateStruct))
		return -1;

	if (!InitDui())
		return -1;

	return 0;
}
