// PatchCascade.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchCascade.h"
#include "afxdialogex.h"


// CPatchCascade �Ի���

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


// CPatchCascade ��Ϣ�������
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

	// TODO:  �ڴ������ר�õĴ�������
	if (!InitDui())
		return -1;

	return 0;
}
