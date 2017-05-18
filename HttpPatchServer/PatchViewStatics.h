#pragma once


// CPatchViewStatics �Ի���


class CPatchViewStatics : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchViewStatics)

public:
	CPatchViewStatics(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchViewStatics();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STATICS };
#endif
	BOOL InitSknPath();
private:

	CWnd* m_pParent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	LRESULT InsertProductsItems(WPARAM wparam, LPARAM lparam);
	LRESULT InsertIndexItem(WPARAM wparam, LPARAM lparam);
	LRESULT CleanItems(WPARAM wparam, LPARAM lparam);
	LRESULT OnSMLButtonUp(WPARAM, LPARAM);
	void OnHttpStart();
	void OnHttpStop();
	void OnCasStart();
	void OnCasStop();
	CWnd* GetParent();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void InitControlLang();
	LRESULT OnSetText(WPARAM, LPARAM);

};
