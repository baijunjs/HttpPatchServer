#pragma once


// CPatchCascade 对话框

class CPatchCascade : public CDUIDialog
{
	DECLARE_DYNAMIC(CPatchCascade)

public:
	CPatchCascade(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchCascade();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CASCADE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
