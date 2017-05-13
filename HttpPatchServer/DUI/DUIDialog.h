/****************************************************************************/
/* 版本：  2012.12.03.01
/* 类描述：封装DirectUI的加载方法，使继承它的类不再关注DirectUI的调用
/* 类使用说明： 1）子类必须重载InitSknPath方法，此函数在LoadSkin中被加载，子类中不必再次调用
/*              实现即可。InitSknPath需要初始化的信息见函数说明
/*              2）OnSMLButtonUp已经在BEGIN_MESSAGE_MAP中声明，子类重载实现即可。
/*              3）OnDUIMsg是一个消息函数，建议子类重载。
/*                 建议在此函数集中处理需要对DirectUI控件操作的消息
/*              4）建议使用 DList  DCombo DBtn等宏去获取控件指针，而不去定义控件指针          
/*                 如果一个皮肤中定义控件太多，如果定义控件指针，则需定义太多的指针    
/*                 使用此宏可以避免此问题；另外建议在皮肤中定义控件的名字尽量简洁，这样可
/*                 使代码更加简洁易懂
/*              5）重载 WindowProc和 OnInitDialog函数，请在子类中调用父类函数            
/**/
#pragma once

#include "DirectUIInc.h" // 根据实际文件位置设置
#include "vrvsdk/include/SdkBase/VRVEdpDialog.h"
#include <map>
#include <string>
#include <GdiPlus.h>
#pragma comment(lib,"GdiPlus.lib")
using namespace Gdiplus;
using namespace VRVSDK;

#define   WM_DUI_MSG     WM_USER+9999  // 发给主线程操作DUI控件的消息
// CDUIDialog
#define GET_PROC_ADDR(h,x)					\
	My##x pfn##x;							\
	pfn##x = (My##x)GetProcAddress(h,#x)	\

// 获取类型为T名为Name的控件指针，如果控件不存在,弹出提示对话框
// 并且程序退出，如果退出不成功，则程序可能会崩溃
#define IDUIObjPtr( Name, T ) \
	((T*)GetObjPtr (_T(#Name), FALSE))

// 检测名为Name的控件是否存在
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
	/* 函数功能：获取皮肤控件对象指针
	/* 参数：    lpszName   控件对象名字
	/* 参数：    bFail	    结果，如果为0，则获取控件对象成功
	/* 返回值：  控件指针
	/*/
	IDUIObj* GetDUISingleObjcet ( LPCTSTR lpszName, BOOL& bFail ) ;

	/*
	/* 函数功能：获取皮肤控件对象指针
	/* 参数：    lpszName   控件对象名字
	/*           IsCheck    如果为FALSE，在控件为NULL的时候弹出警告对话框并退出程序，否则返回NULL
	/* 返回值：  控件指针
	/*/
	IDUIObj* GetObjPtr ( LPCTSTR lpszName, BOOL IsCheck ) ;

	/*
	/* 函数功能：获取皮肤控件对象指针
	/* 参数：    lpszName   控件对象名字
	/* 参数：    bFail	    结果，如果为0，则获取控件对象成功
	/* 返回值：  控件指针
	/*/
	virtual BOOL GetDUIObjcets() ;

	/*
	/* 函数功能：加载皮肤
	/* 返回值：  0：成功； 1：失败
	/*/
	DWORD    LoadSkin () ;
	
	/*
	/* 函数功能：获取皮肤控件对象指针，建议重载此函数在此函数中处理一切消息
	/* 根据wParam判断消息类型，lParam中放入消息处理用到的参数
	/*/
	virtual LRESULT  OnDUIMsg( WPARAM wParam, LPARAM lParam ) ;

	/*
	/* 函数功能：初始化皮肤路径设置信息，此函数中要设置下列变量信息
	/* m_strDUIDllPath 
	/* m_strDUIFile
	/* m_strSknFile 
	/* m_strDUIName 
	/* m_nSkinCtrl
	/* 备注：如果与默认设置不同，请重写此函数
	/*/
	virtual BOOL InitSknPath () ;

	/*
	/* 函数功能：按钮点击响应函数
	/* 此函数已经与DUISM_LBUTTONUP关联，在继承类中重写此函数不需要再次注册DUISM_LBUTTONUP消息
	/*/
	virtual LRESULT OnSMLButtonUp(WPARAM wParam,LPARAM lParam) ;

	/*
	/* 函数功能响应按回车键esc键退出Dialog
	*/
	void IsAnswerOnOkAndOnCancel( BOOL bValue = FALSE ){ m_IsAnswerOnOkAndOnCancel = bValue ;} ;

	/*
	/* 函数功能：获取窗口句柄
	/*/
	HWND      GetHWND(){ return GetSafeHwnd(); } ;

	/*
	/* 函数功能：获取IDUIRes*对象指针
	/*/
	static  IDUIRes* GetStaticDUIRes(){ return m_pDUIRes; };

	/*
	/* 函数功能：设置IDUIRes*对象指针
	/*/
	static  void SetStaticDUIRes(IDUIRes* pDUIRes){ m_pDUIRes = pDUIRes; };

	/*
	/* 函数功能：执行CDialog::OnOK
	/*/
	void OnBtnClickOK();

	/*
	/* 函数功能：执行CDialog::OnCancel
	/*/
	void OnBtnClickCancel();

	/*
	/* 函数功能：获取一张图片的句柄
	/*/
	HBITMAP GetImageHandle ( LPCTSTR lpszImageFile ) ;

	static int     GetLangId () ;

	static BOOL    SetLangId ( int nLang, BOOL IsChange=FALSE ) ;

	static tstring  GetDUIStr ( tstring strID, int nLang=-1 ) ;
private:
	/*
	/* 函数功能：获取真实路径
	/* 函数路径包含 “..\”和“.\”目前不支持宏定义
	/*/
	CString GetRealPath ( CString strPath ) ;

	/*
	/* 函数功能：获取皮肤文件夹
	/*/
	CString GetSkinPath() ;

	/*
	/* 函数功能：获取DirectUI.dll的文件夹
	/*/
	CString GetDirectUIDllPath () ;

	/*
	/* 函数功能：获取DirectUI.dll的文件名，应用在DirectUI.dll改名的情景下
	/*/
	CString GetDirectUIDllName() ;

	inline int IsUseSkinCtrl () ;

public:
	CString m_strDUIIniFile ;     // 配置文件
	CString m_strCurPath ;        // 程序所在文件夹
	CString m_strSysDir ;         // 系统文件夹
	CString m_strSkinDir ;        // 皮肤文件文件夹
	CString m_strDUIDllPath ;     // DirectUI.dll路径
	CString m_strDUIFile ;        // 后缀名字dui文件
	CString m_strSknFile ;        // 后缀名字Skn文件
	CString m_strDUIName ;        // 加载的DUI模块名字，使用皮肤编辑器打开皮肤，可找到所使用DUI的名字
	int     m_nSkinCtrl ;         // 是否使用标准换肤
	int     m_nAbsPath ;          // 是否是绝对路径，OpenSkinA参数
	static  IDUIRes*   m_pDUIRes ;// 皮肤资源指针对象，静态对象，此类的缺点是一个模块只能加载一个皮肤
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


