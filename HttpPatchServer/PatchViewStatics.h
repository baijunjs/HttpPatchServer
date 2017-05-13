#pragma once


// CPatchViewStatics 对话框


class CPatchViewStatics : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchViewStatics)

public:
	CPatchViewStatics(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchViewStatics();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STATICS };
#endif
	//bool InitDui();
	BOOL InitSknPath();
private:
	//ISkinObjResBase		*m_pDuiStatic;
	//IDUIListView		*m_pStaticView;
	//IDUIProgressbar		*m_pProgressbar;
	//ICmdButton			*m_pbtnStart;
	short				 m_curitem;
	CWnd* m_pParent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void InsertProductsItems();
	//void SetItemProgressbarPosition(short nItem, short pos);
	void InsertIndexItem();
	void DeleteAllItems();
	LRESULT OnButtonDispatcher(WPARAM, LPARAM);
	void OnHttpStart();
	void OnHttpStop();
	void OnCasStart();
	void OnCasStop();
	CWnd* GetParent();
};
