
// HttpPatchServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "HttpPatchServerDlg.h"
#include "afxdialogex.h"
#include "Clibcurl.h"


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



CHttpPatchServerDlg::CHttpPatchServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HTTPPATCHSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpPatchServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpPatchServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHttpPatchServerDlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_MESSAGE(DUI_TABMSG_SELCHANGED, &CHttpPatchServerDlg::OnTabPageChanged)
END_MESSAGE_MAP()


// CHttpPatchServerDlg ��Ϣ�������

BOOL CHttpPatchServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_patchview.Create(IDD_DOWNLOADVIEW_DIALOG, this);
	m_pHwndSubWnd->Attach((OLE_HANDLE)HandleToLong(m_patchview.GetSafeHwnd()));

	m_patchsetting.Create(IDD_DIALOG_SETTING, this);
	m_pHwndSubWnd->Attach((OLE_HANDLE)HandleToLong(m_patchsetting.GetSafeHwnd()));

	m_patchview.ShowWindow(SW_SHOW);

	//m_pHwndSubWnd->Attach((OLE_HANDLE)HandleToLong(m_cfigView.GetSafeHwnd()));


	//set window title
	//m_pDUIHwndTitle->SetText(AfxGetAppTitle());//(_T(WND_SHOW_TEXT));


											   //set tray_icon
	ZeroMemory(&m_NotifyIconData, sizeof(m_NotifyIconData));
	m_NotifyIconData.cbSize = sizeof(m_NotifyIconData);
	m_NotifyIconData.hWnd = m_hWnd;
	m_NotifyIconData.uID = IDI_APP_ICON;
	m_NotifyIconData.hIcon = AfxGetApp()->LoadIcon(IDI_APP_ICON);
	m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_NotifyIconData.uCallbackMessage = UM_CUSTOM_TRAY;
	strcpy_s(m_NotifyIconData.szTip, 128, AfxGetAppTitle());//_T(WND_SHOW_TEXT));
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData); //ʹ���½�ͼ���ڳ������е�ʱ��ͱ�ע��


	//std::string szPngPath;
	//IDUITabCtrlItem *pItem = m_pTabMain->InsertItem(0, "��������", UM_CUSTOM_DOWNCENTER, "��������");
	//if (pItem == NULL) return FALSE;
	//szPngPath = appconfig.m_szAppPath + "\\Res\\download.png";
	//for (int itemstate = DUITABITEM_STATE_NORMAL; itemstate < DUITABITEM_STATE_LAST; itemstate++)
	//	pItem->SetIconFilePath(szPngPath, (DUITABITEM_STATE)itemstate);
	//pItem->SetTooltip("��������");

	//pItem = m_pTabMain->InsertItem(1, "��������", UM_CUSTOM_SETTING, "��������");
	//if (pItem == NULL) return FALSE;
	//szPngPath = appconfig.m_szAppPath + "\\Res\\setting.png";
	//for (int itemstate = DUITABITEM_STATE_NORMAL; itemstate < DUITABITEM_STATE_LAST; itemstate++)
	//	pItem->SetIconFilePath(szPngPath, (DUITABITEM_STATE)itemstate);
	//pItem->SetTooltip("��������");


	//pItem = m_pTabMain->InsertItem(2, "������ģʽ", HTTP_TABCTRL_SWITCH, "����ģʽ");
	//if (pItem == NULL) return FALSE;
	//szPngPath = appconfig.m_szAppPath + "\\Res\\ImExportView.png";
	//pItem->SetIconFilePath(szPngPath);
	//pItem->SetTooltip("����ģʽ");

	m_pTabMain->SetSelectedItem(0);

	//std::string szIconPath = appconfig.m_szAppPath + "\\Res\\Icon.png";
	//m_pDUILogIcon->SetLogoImage(szIconPath);

	//����LOGO
	int visible = GetPrivateProfileIntA("VISIBLE", "LOGO", 1, appconfig.m_szConfigFile.c_str());
	if (visible)
		m_pDUILogo->SetVisible(TRUE, TRUE, TRUE);
	else
		m_pDUILogo->SetVisible(FALSE, TRUE, TRUE);
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
		CDialogEx::OnSysCommand(nID, lParam);
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
		CDialogEx::OnPaint();
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

	std::thread patchthread([r = this]()->void
	{
		IPackIndex *indexobject = CPackInterface::getPackIndexObject();
		ILoadIndex *loadobject = CPackInterface::getLoadIndexObject();
		do
		{
			//if (!r->m_patchbus.download_main_index<Clibcurl>())
			//	break;

			if (!r->m_patchbus.analyze_main_index(indexobject))
				break;

			//if (!r->m_patchbus.download_sub_index<Clibcurl>())
			//	break;

			if (!r->m_patchbus.loadProductIndex(loadobject))
				break;

			if (!r->m_patchbus.loadLanuageIndex(loadobject))
				break;

			if (!r->m_patchbus.fetchPatchFile(loadobject))
				break;

		} while (false);

		indexobject->Release();
		loadobject->Release();
	});

	patchthread.detach();
}


int CHttpPatchServerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	if (!InitMainDui())
		return -1;

	return 0;
}


bool CHttpPatchServerDlg::InitMainDui()
{
	m_pDirectUI = (ISkinObjResBase  *)AfxGetDuiRes()->CreateDirectUI(_T("DUIMain"), HandleToLong(m_hWnd));
	if (NULL == m_pDirectUI) return FALSE;

	m_pTabMain = (IDUITabCtrl *)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, _T("TabMain"), m_pDirectUI, TRUE);
	ASSERT(m_pTabMain);

	m_pHwndSubWnd = (IDUIHwndObj *)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, _T("HwndObj14"), m_pDirectUI, TRUE);
	ASSERT(m_pHwndSubWnd);

	m_pDUILogo = (IDUILogoObj *)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, _T("LogoWeb"), m_pDirectUI, TRUE);
	ASSERT(m_pDUILogo);

	m_pDUIBtnClose = (ICmdButton *)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, _T("BtnClose"), m_pDirectUI, TRUE);
	ASSERT(m_pDUIBtnClose);

	m_pDUIBtnMini = (ICmdButton *)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, _T("BtnMin"), m_pDirectUI, TRUE);
	ASSERT(m_pDUIBtnMini);

	m_pDUIchkMax = (IDUICheckBox *)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, _T("ChkMax"), m_pDirectUI, TRUE);
	ASSERT(m_pDUIchkMax);

	m_pDUIchkMax->SetValue(DUICHECKBOX_UNCHECKED);

	return true;
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