#pragma once


// CPatchSetting �Ի���

class CPatchSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchSetting)

public:
	CPatchSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchSetting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PATCHSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	bool InitDui();


	ISkinObjResBase			*m_pDuiPatchSetting;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
