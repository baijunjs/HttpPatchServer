#pragma once


// CPatchNetSetting 对话框

class CPatchNetSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchNetSetting)

public:
	CPatchNetSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchNetSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DOWNSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	bool InitDui();

	ISkinObjResBase			*m_pDuiDownSetting;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
