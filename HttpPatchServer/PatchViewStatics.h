#pragma once


// CPatchViewStatics 对话框

class CPatchViewStatics : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchViewStatics)

public:
	CPatchViewStatics(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchViewStatics();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STATICS };
#endif
	bool InitDui();
private:
	ISkinObjResBase		*m_pDuiStatic;
	IDUIListView		*m_pStaticView;
	IDUIProgressbar		*m_pProgressbar;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
