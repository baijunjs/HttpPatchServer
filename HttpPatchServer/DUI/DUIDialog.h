/****************************************************************************/
/* �汾��  2012.12.03.01
/* ����������װDirectUI�ļ��ط�����ʹ�̳������಻�ٹ�עDirectUI�ĵ���
/* ��ʹ��˵���� 1�������������InitSknPath�������˺�����LoadSkin�б����أ������в����ٴε���
/*              ʵ�ּ��ɡ�InitSknPath��Ҫ��ʼ������Ϣ������˵��
/*              2��OnSMLButtonUp�Ѿ���BEGIN_MESSAGE_MAP����������������ʵ�ּ��ɡ�
/*              3��OnDUIMsg��һ����Ϣ�����������������ء�
/*                 �����ڴ˺������д�����Ҫ��DirectUI�ؼ���������Ϣ
/*              4������ʹ�� DList  DCombo DBtn�Ⱥ�ȥ��ȡ�ؼ�ָ�룬����ȥ����ؼ�ָ��          
/*                 ���һ��Ƥ���ж���ؼ�̫�࣬�������ؼ�ָ�룬���趨��̫���ָ��    
/*                 ʹ�ô˺���Ա�������⣻���⽨����Ƥ���ж���ؼ������־�����࣬������
/*                 ʹ������Ӽ���׶�
/*              5������ WindowProc�� OnInitDialog���������������е��ø��ຯ��            
/**/
#pragma once

#include "DirectUIInc.h" // ����ʵ���ļ�λ������
#include "vrvsdk/include/SdkBase/VRVEdpDialog.h"
#include <map>
#include <string>
#include <GdiPlus.h>
#pragma comment(lib,"GdiPlus.lib")
using namespace Gdiplus;
using namespace VRVSDK;

#define   WM_DUI_MSG     WM_USER+9999  // �������̲߳���DUI�ؼ�����Ϣ
// CDUIDialog
#define GET_PROC_ADDR(h,x)					\
	My##x pfn##x;							\
	pfn##x = (My##x)GetProcAddress(h,#x)	\

// ��ȡ����ΪT��ΪName�Ŀؼ�ָ�룬����ؼ�������,������ʾ�Ի���
// ���ҳ����˳�������˳����ɹ����������ܻ����
#define IDUIObjPtr( Name, T ) \
	((T*)GetObjPtr (_T(#Name), FALSE))

// �����ΪName�Ŀؼ��Ƿ����
#define DNull (Name) \
	if ( NULL == GetObjPtr (_T(#Name), TRUE ) ) \
	    return TRUE ;\
	else return FALSE ;

#define DUISTR( Name ) \
	CDUIDialog::GetDUIStr ( _T(#Name) )

#define DUISTRPtr( Name ) \
	CDUIDialog::GetDUIStr ( _T(#Name) ).c_str()

#define DList(Name)      IDUIObjPtr ( Name, IDUIListView )
#define DCombo(Name)     IDUIObjPtr ( Name, IDUIComboBox )
#define DBtn(Name)       IDUIObjPtr ( Name, ICmdButton )
#define DHwnd(Name)      IDUIObjPtr ( Name, IDUIHwndObj )
#define DTree(Name)      IDUIObjPtr ( Name, IDUISimpleTree )
#define DRadio(Name)     IDUIObjPtr ( Name, IRadioBox )
#define DForm(Name)      IDUIObjPtr ( Name, IUIFormObj)
#define DCheck(Name)     IDUIObjPtr ( Name, IDUICheckBox )
#define DStatic(Name)    IDUIObjPtr ( Name, IDUIStatic )
#define DLogo(Name)      IDUIObjPtr ( Name, IDUILogoObj )
#define DProgress(Name)  IDUIObjPtr ( Name, IDUIProgressbar )
#define DSplit(Name)     IDUIObjPtr ( Name, IDUISplitter )
#define DSpin(Name)      IDUIObjPtr ( Name, IDUISpin )
#define DTab(Name)       IDUIObjPtr ( Name, IDUITabCtrl )
#define DEdit(Name)		 IDUIObjPtr ( Name, IDUIEditCtrl )

typedef IDUIRes* 
(CALLBACK *MyOpenSkinA)(
						char* strSkinPath,
						char*strSknPath, 
						BOOL bSkinCtrls, 
						BOOL bAddRef, 
						BOOL bAbsPath);
typedef IDUIRes* 
(CALLBACK *MyOpenSkinW)(
						wchar_t* strSkinPath,
						wchar_t*strSknPath, 
						BOOL bSkinCtrls, 
						BOOL bAddRef, 
						BOOL bAbsPath);

typedef void (CALLBACK *MyFreeSkin)();

class CDUIDialog : public CDialogEx, public VRVSDK::CVRVEdpDialog
{
	DECLARE_DYNAMIC(CDUIDialog)

public:
	CDUIDialog ( UINT nIDTemplate, CWnd* pParentWnd = NULL );
	CDUIDialog(void);

	virtual ~CDUIDialog();

protected:
	DECLARE_MESSAGE_MAP()
public:
	/*
	/* �������ܣ���ȡƤ���ؼ�����ָ��
	/* ������    lpszName   �ؼ���������
	/* ������    bFail	    ��������Ϊ0�����ȡ�ؼ�����ɹ�
	/* ����ֵ��  �ؼ�ָ��
	/*/
	IDUIObj* GetDUISingleObjcet ( LPCTSTR lpszName, BOOL& bFail ) ;

	/*
	/* �������ܣ���ȡƤ���ؼ�����ָ��
	/* ������    lpszName   �ؼ���������
	/*           IsCheck    ���ΪFALSE���ڿؼ�ΪNULL��ʱ�򵯳�����Ի����˳����򣬷��򷵻�NULL
	/* ����ֵ��  �ؼ�ָ��
	/*/
	IDUIObj* GetObjPtr ( LPCTSTR lpszName, BOOL IsCheck ) ;

	/*
	/* �������ܣ���ȡƤ���ؼ�����ָ��
	/* ������    lpszName   �ؼ���������
	/* ������    bFail	    ��������Ϊ0�����ȡ�ؼ�����ɹ�
	/* ����ֵ��  �ؼ�ָ��
	/*/
	virtual BOOL GetDUIObjcets() ;

	/*
	/* �������ܣ�����Ƥ��
	/* ����ֵ��  0���ɹ��� 1��ʧ��
	/*/
	DWORD    LoadSkin () ;
	
	/*
	/* �������ܣ���ȡƤ���ؼ�����ָ�룬�������ش˺����ڴ˺����д���һ����Ϣ
	/* ����wParam�ж���Ϣ���ͣ�lParam�з�����Ϣ�����õ��Ĳ���
	/*/
	virtual LRESULT  OnDUIMsg( WPARAM wParam, LPARAM lParam ) ;

	/*
	/* �������ܣ���ʼ��Ƥ��·��������Ϣ���˺�����Ҫ�������б�����Ϣ
	/* m_strDUIDllPath 
	/* m_strDUIFile
	/* m_strSknFile 
	/* m_strDUIName 
	/* m_nSkinCtrl
	/* ��ע�������Ĭ�����ò�ͬ������д�˺���
	/*/
	virtual BOOL InitSknPath () ;

	/*
	/* �������ܣ���ť�����Ӧ����
	/* �˺����Ѿ���DUISM_LBUTTONUP�������ڼ̳�������д�˺�������Ҫ�ٴ�ע��DUISM_LBUTTONUP��Ϣ
	/*/
	virtual LRESULT OnSMLButtonUp(WPARAM wParam,LPARAM lParam) ;

	/*
	/* ����������Ӧ���س���esc���˳�Dialog
	*/
	void IsAnswerOnOkAndOnCancel( BOOL bValue = FALSE ){ m_IsAnswerOnOkAndOnCancel = bValue ;} ;

	/*
	/* �������ܣ���ȡ���ھ��
	/*/
	HWND      GetHWND(){ return GetSafeHwnd(); } ;

	/*
	/* �������ܣ���ȡIDUIRes*����ָ��
	/*/
	static  IDUIRes* GetStaticDUIRes(){ return m_pDUIRes; };

	/*
	/* �������ܣ�����IDUIRes*����ָ��
	/*/
	static  void SetStaticDUIRes(IDUIRes* pDUIRes){ m_pDUIRes = pDUIRes; };

	/*
	/* �������ܣ�ִ��CDialog::OnOK
	/*/
	void OnBtnClickOK();

	/*
	/* �������ܣ�ִ��CDialog::OnCancel
	/*/
	void OnBtnClickCancel();

	/*
	/* �������ܣ���ȡһ��ͼƬ�ľ��
	/*/
	HBITMAP GetImageHandle ( LPCTSTR lpszImageFile ) ;

	static int     GetLangId () ;

	static BOOL    SetLangId ( int nLang, BOOL IsChange=FALSE ) ;

	static tstring  GetDUIStr ( tstring strID, int nLang=-1 ) ;
private:
	/*
	/* �������ܣ���ȡ��ʵ·��
	/* ����·������ ��..\���͡�.\��Ŀǰ��֧�ֺ궨��
	/*/
	CString GetRealPath ( CString strPath ) ;

	/*
	/* �������ܣ���ȡƤ���ļ���
	/*/
	CString GetSkinPath() ;

	/*
	/* �������ܣ���ȡDirectUI.dll���ļ���
	/*/
	CString GetDirectUIDllPath () ;

	/*
	/* �������ܣ���ȡDirectUI.dll���ļ�����Ӧ����DirectUI.dll�������龰��
	/*/
	CString GetDirectUIDllName() ;

	inline int IsUseSkinCtrl () ;

public:
	CString m_strDUIIniFile ;     // �����ļ�
	CString m_strCurPath ;        // ���������ļ���
	CString m_strSysDir ;         // ϵͳ�ļ���
	CString m_strSkinDir ;        // Ƥ���ļ��ļ���
	CString m_strDUIDllPath ;     // DirectUI.dll·��
	CString m_strDUIFile ;        // ��׺����dui�ļ�
	CString m_strSknFile ;        // ��׺����Skn�ļ�
	CString m_strDUIName ;        // ���ص�DUIģ�����֣�ʹ��Ƥ���༭����Ƥ�������ҵ���ʹ��DUI������
	int     m_nSkinCtrl ;         // �Ƿ�ʹ�ñ�׼����
	int     m_nAbsPath ;          // �Ƿ��Ǿ���·����OpenSkinA����
	static  IDUIRes*   m_pDUIRes ;// Ƥ����Դָ����󣬾�̬���󣬴����ȱ����һ��ģ��ֻ�ܼ���һ��Ƥ��
    static  DUI_LANGUAGE m_eLang ;
private:
	HMODULE m_hDUI ;
	IDirectUI* m_pDirectUI ;
	BOOL       m_IsAnswerOnOkAndOnCancel ;
	std::map<tstring, IDUIObj*> m_mapCtrls ;
protected:
	virtual void OnOK();
	virtual void OnCancel();

	BOOL    CreateDUI() ;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
};
//


