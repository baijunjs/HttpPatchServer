#pragma once
#include "PathDownloadListView.h"
#include "PatchViewStatics.h"
#include "PatchViewError.h"

// CPatchView �Ի���

class CPatchView : public CDialogEx
{
	DECLARE_DYNAMIC(CPatchView)

public:
	CPatchView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchView();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOWNLOADVIEW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	bool InitPatchViewDui();

private:
	ISkinObjResBase *m_pDuiPatchView;
	IDUITabCtrl	*m_pDuiTabView;
	IDUIHwndObj *m_pDuiListOwner;

	CPatchViewStatics	m_hPatchStatics;			//ͳ�ƽ���
	CPatchDownView		m_hPatchDown;				//���ؽ���
	CPatchViewError		m_hPatchError;				//�������	

public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnTabPageChanged(WPARAM, LPARAM);
};