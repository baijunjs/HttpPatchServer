#pragma once


// CPatchNetSetting 对话框

class CPatchNetSetting : public CDUIDialog
{

	enum tree
	{
		producttree,
		languagetree
	};

	DECLARE_DYNAMIC(CPatchNetSetting)

public:
	CPatchNetSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatchNetSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DOWNSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL InitSknPath();
	//bool InitDui();

	//ISkinObjResBase			*m_pDuiDownSetting;

	//IDUIEditCtrl			*m_pEditUrl;
	//IDUIEditCtrl			*m_pEditPath;
	//ICmdButton				*m_pCmdBtnTest;
	//ICmdButton				*m_pCmdBtnBrowser;
	//IDUISimpleTree			*m_pProductsTree;
	//IDUISimpleTree			*m_pLansTree;

	//IRadioBox				*m_pRadioAll;
	//IRadioBox				*m_pRadioPerid;
	//IRadioBox				*m_pRadioInteval;
	//IDUIEditCtrl			*m_pEditPerid;
	//IDUIEditCtrl			*m_pEditBegin;
	//IDUIEditCtrl			*m_pEditEnd;


	//IDUICheckBox			*m_pChkFlux;
	//IDUIEditCtrl			*m_pEditFluxSpeed;


	//IDUICheckBox			*m_pChkProxy;
	//IDUIEditCtrl			*m_pEditIp;
	//IDUIEditCtrl			*m_pEditPort;
	//IDUIEditCtrl			*m_pEditUser;
	//IDUIEditCtrl			*m_pEditPwd;

	CWnd* m_pParent;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	//void GetIntevalTime(std::string& src, std::string &szbH, std::string &szbM,
		//std::string &szeH, std::string &szeM);
	void InitControlData();
	void EnbaleControl();
	BOOL OnApply();
	CWnd *GetParent();
	LRESULT OnKillFocus(WPARAM, LPARAM);
	LRESULT OnRadioChange(WPARAM, LPARAM);
	LRESULT OnCheckBoxChanged(WPARAM, LPARAM);
	void OnRestore();
	LRESULT OnPreReturn(WPARAM, LPARAM);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void RedrawSimpleTree();
	LRESULT OnButtonDispatcher(WPARAM wparam, LPARAM lparam);
	LRESULT OnTreeCheckItem(WPARAM wparam, LPARAM lparam);
	LRESULT OnButtonTest(WPARAM wparam, LPARAM lparam);
	LRESULT OnButtonBrowser(WPARAM wparam, LPARAM lparam);
	void RedrawTreeImpl(tree whichtree);
	void CheckChildItem(IDUISimpleTree *tree, OLE_HANDLE hParent);
	std::string GetCheckedItemString(IDUISimpleTree* pTree);
	void RestoreTreeCheckItems(tree);
	void TravelTree(IDUISimpleTree* pTree, OLE_HANDLE hParent, std::string& szChecked);
};
