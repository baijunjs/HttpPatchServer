#pragma once


// CPatchViewError �Ի���

class CPatchViewError : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchViewError)

public:
	CPatchViewError(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchViewError();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ERROR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	bool InitDui();

	ISkinObjResBase		*m_pDuiError;
	IDUIListView		*m_pErrorView;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
