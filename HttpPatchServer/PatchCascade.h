#pragma once


// CPatchCascade �Ի���

class CPatchCascade : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchCascade)

public:
	CPatchCascade(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPatchCascade();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CASCADE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//bool InitDui();
	BOOL InitSknPath();

private:
	//ISkinObjResBase		*m_pDuiCascade;
	//IDUIEditCtrl		*m_pEditDbIp;
	//IDUIEditCtrl		*m_pEditDbName;
	//IDUIEditCtrl		*m_pEditDbUser;
	//IDUIEditCtrl		*m_pEditDbPwd;

	//IDUICheckBox		*m_pChkCascade;
	//IDUIEditCtrl		*m_pEditServerIp;
	//IDUIEditCtrl		*m_pEditServerPort;

	//IRadioBox			*m_pRadioAll;
	//IRadioBox			*m_pRadioPerid;
	//IRadioBox			*m_pRadioInteval;
	//IDUIEditCtrl		*m_pEditPerid;
	//IDUIEditCtrl		*m_pEditBegin;
	//IDUIEditCtrl		*m_pEditEnd;

	//IDUICheckBox		*m_pChkFlux;
	//IDUIEditCtrl		*m_pEditFluxSpeed;

	//IDUIEditCtrl		*m_pEditPath;

	//ICmdButton			*m_pBtnCascade;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void InitControlData();
	void EnableControl();

	LRESULT OnButtonUp(WPARAM, LPARAM);
	void GetCascadeConfig();

	void GetIntervalTime(std::string &szTime, std::string &szBegin, std::string &szEnd);
	BOOL OnApply();
	void OnRestore();
};
