#pragma once


// CPatchCascade �Ի���

class CPatchCascade : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchCascade)

public:
	CPatchCascade(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchCascade();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CASCADE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	bool InitDui();
	ISkinObjResBase		*m_pDuiCascade;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
