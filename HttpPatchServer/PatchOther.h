#pragma once


// CPatchOther 对话框

class CPatchOther : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchOther)

public:
	CPatchOther(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchOther();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OTHER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	void InitControlLang();

};
