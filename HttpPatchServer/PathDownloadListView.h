#pragma once


// CPathDownloadListView �Ի���

class CPatchDownView : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchDownView)

public:
	CPatchDownView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchDownView();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOWNLOAD_LISTVIEW };
#endif

private:
	bool InitListViewDui();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	ISkinObjResBase *m_pDuiListForm;
	IDUIListView	*m_pDuiListView;
	IDUIProgressbar *m_pDuiProgressBar;
public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
