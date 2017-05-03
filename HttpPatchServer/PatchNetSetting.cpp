// PatchNetSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchNetSetting.h"
#include "afxdialogex.h"


// CPatchNetSetting �Ի���

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


// CPatchNetSetting ��Ϣ�������


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

	// TODO:  �ڴ������ר�õĴ�������
	if (!InitDui())
		return -1;

	return 0;
}
