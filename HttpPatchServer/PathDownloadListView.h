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
	//bool InitListViewDui();
	BOOL InitSknPath();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
private:
	CWnd *m_pParent;

public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//void InsertPatchIndexItem(vrv::patch::CPatchIndex*);
	LRESULT CleanItems(WPARAM, LPARAM);
	//void SetItemProgressbarPosition(short nItem, short pos);
	LRESULT RefreshListView(WPARAM wapram, LPARAM lparam);
	CWnd* GetParent();
	LRESULT InsertIndexItem(WPARAM wpram, LPARAM lparam);
	LRESULT InsertPatchItem(WPARAM wparam, LPARAM lparam);

	bool DownloadIndexesByCurl(IDUITVItem *pTopItem, vrv::patch::PatchIndexVectorPtr indexes);
	bool DownloadPatchesByCurl(IDUITVItem *pTopItem, vrv::patch::PatchInfoVec &patches);
	//void SetTaskStatusTip(IDUITVItem *pItem, Task_Status st, long lcode);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void InsertErrorTaskToView(void *pTask, TASK_TYPE type);
	bool DownloadIndexesByRcf(IDUITVItem *pTopItem);
	bool DownloadPatchesByRcf(IDUITVItem *pTopItem);
};
