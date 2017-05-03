// PatchViewStatics.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchViewStatics.h"
#include "afxdialogex.h"


// CPatchViewStatics �Ի���

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


// CPatchViewStatics ��Ϣ�������


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
	// TODO: �ڴ����ר�ô����/����û���

	if (-1 == CDialogEx::OnCreate(lpCreateStruct))
		return -1;

	if (!InitDui())
		return -1;

	return 0;
}
