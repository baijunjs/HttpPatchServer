#pragma once


// CPatchOther �Ի���

class CPatchOther : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchOther)

public:
	CPatchOther(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchOther();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OTHER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	//bool InitDui();
	//ISkinObjResBase		*m_pDuiOther;
	//IDUICheckBox		*m_pChkLog;
	//IDUIComboBox		*m_pLogLevel;
	//IDUIComboBox		*m_pComboLans;
	//IDUIStatic			*m_pLansLabel;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void InitControlData();
	BOOL OnApply();
	void OnRestore();
	void EnableControl();
	LRESULT OnCheckBoxChanged(WPARAM, LPARAM);
	BOOL InitSknPath();

};
