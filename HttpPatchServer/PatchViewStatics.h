#pragma once


// CPatchViewStatics �Ի���

class CPatchViewStatics : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchViewStatics)

public:
	CPatchViewStatics(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchViewStatics();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STATICS };
#endif
	bool InitDui();
private:
	ISkinObjResBase		*m_pDuiStatic;
	IDUIListView		*m_pStaticView;
	IDUIProgressbar		*m_pProgressbar;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
