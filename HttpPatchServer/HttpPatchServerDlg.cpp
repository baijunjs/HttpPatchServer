
// HttpPatchServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "HttpPatchServerDlg.h"
#include "afxdialogex.h"
#include "Clibcurl.h"
#include "MessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHttpPatchServerDlg �Ի���

const UINT WM_ADDICON_TOTASKBAR = ::RegisterWindowMessage(_T("TaskbarCreated"));

CHttpPatchServerDlg::CHttpPatchServerDlg(CWnd* pParent /*=NULL*/)
	: CDUIDialog(IDD_HTTPPATCHSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpPatchServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDUIDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpPatchServerDlg, CDUIDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHttpPatchServerDlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_MESSAGE(DUI_TABMSG_SELCHANGED, &CHttpPatchServerDlg::OnTabPageChanged)
	ON_MESSAGE(DUISM_LBUTTONUP, &CHttpPatchServerDlg::OnButtonUp)
	ON_REGISTERED_MESSAGE(WM_ADDICON_TOTASKBAR, &CHttpPatchServerDlg::OnAddIconToTaskbar)
	ON_MESSAGE(UM_CUSTOM_TRAY, &CHttpPatchServerDlg::OnTrayIcon)
END_MESSAGE_MAP()


// CHttpPatchServerDlg ��Ϣ�������

BOOL CHttpPatchServerDlg::OnInitDialog()
{
	CDUIDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	if (!appconfig.m_szLogo.empty())
	{
		std::tstring szLogoPath = appconfig.m_szAppPath + _T("\\Skin\\Logo\\") + appconfig.m_szLogo;
		IDUIImageBase* pImgBase = GetImageBaseFromFile(szLogoPath.c_str());
		if (pImgBase)
		{
			
			IDUIRect* prc = DLogo(LogoWeb)->GetRect();
			SkinRect rc = pImgBase->get_rect();
			long left = prc->get_left();
			long right = left + rc.right;
			long top = prc->get_top() - 15;
			long bottom = top + rc.bottom;
			
			prc->put_left(left);
			prc->put_right(right);
			prc->put_top(top);
			prc->put_bottom(bottom);
			DLogo(LogoWeb)->SetRect(prc);
			DLogo(LogoWeb)->SetBackImage(pImgBase, TRUE);

		}
	}
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	DHwnd(HwndObj14)->Attach((OLE_HANDLE)HandleToLong(m_patchview.GetSafeHwnd()));
	DHwnd(HwndObj14)->Attach((OLE_HANDLE)HandleToLong(m_patchsetting.GetSafeHwnd()));
	m_patchsetting.SetPatchView(&m_patchview);
	m_patchview.ShowWindow(SW_SHOW);

	DCheck(ChkMax)->SetValue(DUICHECKBOX_UNCHECKED);

	AddTaskbarIcons();

	InitControlLang();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



void CHttpPatchServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDUIDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHttpPatchServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDUIDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHttpPatchServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpPatchServerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


int CHttpPatchServerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_patchview.Create(IDD_DOWNLOADVIEW_DIALOG, this);
	m_patchsetting.Create(IDD_DIALOG_SETTING, this);
	if (CDUIDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}

BOOL CHttpPatchServerDlg::InitSknPath()
{

	CDUIDialog::InitSknPath();
	m_strDUIName = _T("DUIMain");
	m_strSkinDir = appconfig.m_szAppPath.c_str();
	m_strDUIFile = m_strSkinDir + _T("\\Skin\\PatchDown.dui");
	m_strSknFile = m_strSkinDir + _T("\\Skin\\PatchDown.skn");
	return TRUE;
}


LRESULT CHttpPatchServerDlg::OnButtonUp(WPARAM wparam, LPARAM lparam)
{
	if (DBtn(BtnClose) == (ICmdButton*)wparam)
	{
		OnCancel();
	}
	else if (DBtn(BtnMin) == (ICmdButton*)wparam)
	{
		ShowWindow(SW_HIDE);
	}

	return 0;
}


LRESULT CHttpPatchServerDlg::OnTabPageChanged(WPARAM wparam, LPARAM lparam)
{
	if (0 == wparam)
	{
		m_patchview.ShowWindow(SW_SHOWNORMAL);
		m_patchsetting.ShowWindow(SW_HIDE);
	}

	else if (1 == wparam)
	{
		m_patchview.ShowWindow(SW_HIDE);
		m_patchsetting.ShowWindow(SW_SHOWNORMAL);
	}

	return 0;
}


void CHttpPatchServerDlg::OnOK()
{
	CDUIDialog::OnOK();
}

void CHttpPatchServerDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (theApp._thread.joinable())
	{
		CMessageBox msg;
		if (IDOK == msg.ShowMessage(g_lang.GetText(10061), MB_OKCANCEL))
		{
			m_patchview.OnClose();
			m_patchsetting.OnClose();
			Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData); //ʹ���½�ͼ���ڳ������е�ʱ��ͱ�ע��
			IsAnswerOnOkAndOnCancel(TRUE);
			CDUIDialog::OnCancel();
			theApp._thread.join();
		}
	}
	else
	{
		m_patchview.OnClose();
		m_patchsetting.OnClose();
		Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData); //ʹ���½�ͼ���ڳ������е�ʱ��ͱ�ע��
		IsAnswerOnOkAndOnCancel(TRUE);
		CDUIDialog::OnCancel();
	}
}


LRESULT CHttpPatchServerDlg::OnAddIconToTaskbar(WPARAM wParam, LPARAM lParam)
{
	AddTaskbarIcons();
	return 0;
}

void CHttpPatchServerDlg::AddTaskbarIcons()
{
	//set tray_icon
	ZeroMemory(&m_NotifyIconData, sizeof(m_NotifyIconData));
	m_NotifyIconData.cbSize = sizeof(m_NotifyIconData);
	m_NotifyIconData.hWnd = m_hWnd;
	m_NotifyIconData.uID = IDI_APP_ICON;
	m_NotifyIconData.hIcon = AfxGetApp()->LoadIcon(IDI_APP_ICON);
	m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_NotifyIconData.uCallbackMessage = UM_CUSTOM_TRAY;
	_tcscpy_s(m_NotifyIconData.szTip, 128, AfxGetAppTitle());//_T(WND_SHOW_TEXT));
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData); //ʹ���½�ͼ���ڳ������е�ʱ��ͱ�ע��
}

LRESULT CHttpPatchServerDlg::OnTrayIcon(WPARAM wparam, LPARAM lparam)
{
	switch (lparam)
	{
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		ShowWindow(SW_SHOWNORMAL);
		break;
	}
	return 0;
}

void CHttpPatchServerDlg::InitControlLang()
{
	long nItems = DTab(TabMain)->GetItemCount();
	IDUITabCtrlItem *pItem1 = DTab(TabMain)->GetItemByIndex(0);
	IDUITabCtrlItem *pItem2 = DTab(TabMain)->GetItemByIndex(1);
	pItem1->SetText(g_lang.GetText(10001));
	pItem2->SetText(g_lang.GetText(10005));
	DTab(TabMain)->RedrawWindow(TRUE);
}