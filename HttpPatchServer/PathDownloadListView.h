#pragma once


// CPathDownloadListView 对话框

class CPatchDownView : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchDownView)

public:
	CPatchDownView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchDownView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOWNLOAD_LISTVIEW };
#endif

private:
	bool InitListViewDui();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	ISkinObjResBase *m_pDuiListForm;
	IDUIListView	*m_pDuiListView;
	IDUIProgressbar *m_pDuiProgressBar;
public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
