#pragma once


// CMessageBox �Ի���

class CMessageBox : public CDUIDialog
{
	DECLARE_DYNAMIC(CMessageBox)

public:
	CMessageBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageBox();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MSGBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL InitSknPath();

	//ISkinObjResBase	*m_pDuiMsgBox;
	//ICmdButton		*m_pBtnYes;
	//ICmdButton		*m_pBtnOk;
	//ICmdButton		*m_pBtnCancel;
	//IDUIStatic		*m_pMessage;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	UINT m_uflag;
	std::string m_szMessage;
	int ShowMessage(LPCSTR, UINT flag = MB_OK);
	virtual BOOL OnInitDialog();
	LRESULT OnButtonDispatcher(WPARAM, LPARAM);
};
