// PatchNetSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchNetSetting.h"
#include "afxdialogex.h"


// CPatchNetSetting 对话框

IMPLEMENT_DYNAMIC(CPatchNetSetting, CDialogEx)

CPatchNetSetting::CPatchNetSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DOWNSETTING, pParent)
{

}

CPatchNetSetting::~CPatchNetSetting()
{
}

void CPatchNetSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchNetSetting, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPatchNetSetting 消息处理程序


bool CPatchNetSetting::InitDui()
{
	m_pDuiDownSetting = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIDownCfg", HandleToLong(m_hWnd));
	ASSERT(m_pDuiDownSetting);

	return true;
}

int CPatchNetSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!InitDui())
		return -1;

	return 0;
}
