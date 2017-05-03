#pragma once


// CPatchSetting 对话框

class CPatchSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchSetting)

public:
	CPatchSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PATCHSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	bool InitDui();


	ISkinObjResBase			*m_pDuiPatchSetting;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
