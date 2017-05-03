#pragma once


// CPatchCascade 对话框

class CPatchCascade : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchCascade)

public:
	CPatchCascade(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchCascade();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CASCADE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	bool InitDui();
	ISkinObjResBase		*m_pDuiCascade;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
