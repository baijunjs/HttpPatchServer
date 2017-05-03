// PatchViewError.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewError.h"
#include "afxdialogex.h"


// CPatchViewError �Ի���

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


// CPatchViewError ��Ϣ�������

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
	// TODO: �ڴ����ר�ô����/����û���

	if(-1 == CDialogEx::OnCreate(lpCreateStruct))
		return -1;

	if (!InitDui())
		return -1;

	return 0;
}
