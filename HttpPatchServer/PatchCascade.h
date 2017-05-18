#pragma once


// CPatchCascade �Ի���

class CPatchCascade : public CDUIDialog
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
	BOOL InitSknPath();

private:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void InitControlData();
	void EnableControl();

	LRESULT OnButtonUp(WPARAM, LPARAM);
	void GetCascadeConfig();

	BOOL OnApply();
	void OnRestore();
	void InitControlLang();
};
