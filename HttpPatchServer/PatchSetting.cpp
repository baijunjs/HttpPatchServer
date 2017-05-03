// PatchSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchSetting.h"
#include "afxdialogex.h"


// CPatchSetting 对话框

IMPLEMENT_DYNAMIC(CPatchSetting, CDialogEx)

CPatchSetting::CPatchSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PATCHSETTING, pParent)
{

}

CPatchSetting::~CPatchSetting()
{
}

void CPatchSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchSetting, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPatchSetting 消息处理程序


bool CPatchSetting::InitDui()
{
	m_pDuiPatchSetting = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIPatchCfg", HandleToLong(m_hWnd));
	ASSERT(m_pDuiPatchSetting);

	return true;
}

int CPatchSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!InitDui())
		return -1;

	return 0;
}
