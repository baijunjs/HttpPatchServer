#pragma once


// CPatchViewError 对话框

class CPatchViewError : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchViewError)

public:
	CPatchViewError(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchViewError();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ERROR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	bool InitDui();

	ISkinObjResBase		*m_pDuiError;
	IDUIListView		*m_pErrorView;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
