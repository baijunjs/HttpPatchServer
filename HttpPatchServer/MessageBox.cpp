// MessageBox.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "MessageBox.h"
#include "afxdialogex.h"


// CMessageBox 对话框

IMPLEMENT_DYNAMIC(CMessageBox, CDUIDialog)

CMessageBox::CMessageBox(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_DIALOG_MSGBOX, pParent)
{
	//Create(IDD_DIALOG_MSGBOX, pParent);
}

CMessageBox::~CMessageBox()
{
}

void CMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageBox, CDUIDialog)
	ON_WM_CREATE()
	ON_MESSAGE(DUISM_LBUTTONUP, &CMessageBox::OnButtonDispatcher)
END_MESSAGE_MAP()


// CMessageBox 消息处理程序


//bool CMessageBox::InitDui()
//{
//	m_pDuiMsgBox = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIMessage", HandleToLong(m_hWnd));
//	ASSERT(m_pDuiMsgBox);
//
//	m_pBtnOk = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnOk", m_pDuiMsgBox, TRUE);
//	ASSERT(m_pBtnOk);
//
//	m_pBtnCancel = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnCancel", m_pDuiMsgBox, TRUE);
//	ASSERT(m_pBtnCancel);
//
//	m_pBtnYes = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnYes", m_pDuiMsgBox, TRUE);
//	ASSERT(m_pBtnYes);
//
//	m_pMessage = (IDUIStatic*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "StaticMessage", m_pDuiMsgBox, TRUE);
//	ASSERT(m_pMessage);
//
//	return true;
//}

int CMessageBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

BOOL CMessageBox::InitSknPath()
{

	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIMessage");
	return TRUE;
}


int CMessageBox::ShowMessage(LPCSTR msg, UINT flag)
{
	m_uflag = flag;
	m_szMessage = msg;

	return DoModal() == IDOK ? 1 : 0;
}

BOOL CMessageBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_uflag == MB_OK)
	{
		DBtn(BtnOk)->SetVisible(TRUE, TRUE, TRUE);
		DBtn(BtnYes)->SetVisible(FALSE, TRUE, TRUE);
		DBtn(BtnCancel)->SetVisible(FALSE, TRUE, TRUE);
	}
	else if (m_uflag == MB_OKCANCEL)
	{
		DBtn(BtnOk)->SetVisible(FALSE, TRUE, TRUE);
		DBtn(BtnYes)->SetVisible(TRUE, TRUE, TRUE);
		DBtn(BtnCancel)->SetVisible(TRUE, TRUE, TRUE);
	}

	DStatic(StaticMessage)->SetText(m_szMessage);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


LRESULT CMessageBox::OnButtonDispatcher(WPARAM wparam, LPARAM lparam)
{
	IsAnswerOnOkAndOnCancel(TRUE);
	if (DBtn(BtnOk) == (ICmdButton*)wparam
		|| DBtn(BtnYes) == (ICmdButton*)wparam)
		OnOK();

	else if (DBtn(BtnCancel) == (ICmdButton*)wparam)
		OnCancel();

	return 0;
}