#pragma once


// CPatchNetSetting �Ի���

class CPatchNetSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchNetSetting)

public:
	CPatchNetSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchNetSetting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DOWNSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	bool InitDui();

	ISkinObjResBase			*m_pDuiDownSetting;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
