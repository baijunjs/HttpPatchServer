#pragma once


// CPathDownloadListView 对话框
#include "PatchIndex.h"
#include "PatchBus.h"
#include "PatchService.h"

enum TASK_TYPE
{
	INDEX,
	PATCH
};


class CPatchDownView : public CDUIDialog
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
	BOOL InitSknPath();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
private:
	CWnd *m_pParent;

public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	LRESULT CleanItems(WPARAM, LPARAM);
	LRESULT RefreshListView(WPARAM wapram, LPARAM lparam);
	CWnd* GetParent();
	LRESULT InsertIndexItem(WPARAM wpram, LPARAM lparam);
	LRESULT InsertPatchItem(WPARAM wparam, LPARAM lparam);

	bool DownloadIndexesByCurl(HWND topHwnd, int topIndex, vrv::patch::PatchIndexVectorPtr indexes);
	bool DownloadPatchesByCurl(HWND topHwnd, int topIndex, vrv::patch::PatchInfoVec &patches);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void InsertErrorTaskToView(void *pTask, TASK_TYPE type);
	bool DownloadIndexesByRcf(HWND topHwnd, int topIndex);
	bool DownloadPatchesByRcf(HWND topHwnd, int topIndex);
	bool DownloadIndex1xmlByRcf(HWND topHwnd, int topIndex);
	LRESULT OnSetText(WPARAM, LPARAM);
};
