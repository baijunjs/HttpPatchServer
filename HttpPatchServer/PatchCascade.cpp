// PatchCascade.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchCascade.h"
#include "afxdialogex.h"


// CPatchCascade 对话框

IMPLEMENT_DYNAMIC(CPatchCascade, CDialogEx)

CPatchCascade::CPatchCascade(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CASCADE, pParent)
{

}

CPatchCascade::~CPatchCascade()
{
}

void CPatchCascade::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchCascade, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPatchCascade 消息处理程序
bool CPatchCascade::InitDui()
{
	m_pDuiCascade = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUICascade", HandleToLong(m_hWnd));
	ASSERT(m_pDuiCascade);

	return true;
}

int CPatchCascade::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!InitDui())
		return -1;

	return 0;
}
