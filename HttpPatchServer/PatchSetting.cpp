// PatchSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchSetting.h"
#include "afxdialogex.h"


// CPatchSetting �Ի���

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


// CPatchSetting ��Ϣ�������


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

	// TODO:  �ڴ������ר�õĴ�������
	if (!InitDui())
		return -1;

	return 0;
}
