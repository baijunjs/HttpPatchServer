#pragma once
#include "PathDownloadListView.h"
#include "PatchViewStatics.h"
#include "PatchViewError.h"

// CPatchView 对话框


class CPatchView : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchView)

public:
	CPatchView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOWNLOADVIEW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL InitSknPath();

	CWnd* GetStaticView()
	{
		return &m_hPatchStatics;
	}

	CWnd* GetDownView()
	{
		return &m_hPatchDown;
	}

	CWnd* GetErrorView()
	{
		return &m_hPatchError;
	}

private:
	CPatchViewStatics	m_hPatchStatics;			//统计界面
	CPatchDownView		m_hPatchDown;				//下载界面
	CPatchViewError		m_hPatchError;				//错误界面	

public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnTabPageChanged(WPARAM, LPARAM);
	virtual void OnCancel();
	afx_msg void OnClose();
	void InitControlLang();
};
