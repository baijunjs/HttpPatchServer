// DUIDialog.cpp : 实现文件
//

#include "stdafx.h"
//#include "DUIDialog.h"

/*
/* DUIDialog使用到的函数
*/
void DebugPrintf( const TCHAR* szMsg,...)
{
	if ( NULL == szMsg || 0 == _tcslen (szMsg) )
		return ;
	if ( _taccess( _T("DebugOut.txt"), 0 )== 0 )
	{
		FILE* fp = _tfopen ( _T("DebugOut_UI.txt"), _T("a+")) ;
		if (fp)
		{
			TCHAR chLen[10] = {0} ;
			TCHAR szBuf[2048] = {0} ;
			va_list ap;
			if ( _tcslen(szMsg) >= 2048)
			{
				_ftprintf(fp,_T("size>=2048\n") ) ;
				fclose(fp) ;
				va_end(ap);
				return ;
			}
			va_start(ap,szMsg);
			_vstprintf(szBuf+_tcslen(szBuf),szMsg,ap);
			_ftprintf(fp,_T("%s\n"),szBuf) ;
			fclose(fp) ;
			va_end(ap);
		}
	}
}

CString GetUpFolder(LPCTSTR lpCurFolder)
{
	CString strPath = TEXT("");
	TCHAR   tcTemp[500] = {0};
	TCHAR   *p = NULL ;

	if (NULL == lpCurFolder )
	{
		return strPath ;
	}
	_tcscpy( tcTemp, lpCurFolder ) ;

	p = _tcsrchr( tcTemp, TEXT('\\')) ;
	if (p)
	{
		ZeroMemory( p, _tcslen(p)*sizeof(TCHAR) ) ;
		strPath = tcTemp ;
	}

	return strPath ;
}
CString GetModuleFolder( HMODULE hModule )
{
	CString strPath ;
	TCHAR   tcDir[MAX_PATH] = {0} ;

	GetModuleFileName( hModule, tcDir, MAX_PATH ) ;

	ZeroMemory(_tcsrchr(tcDir,_T('\\')), _tcslen(_tcsrchr(tcDir,_T('\\') ) )*sizeof(TCHAR)) ;

	strPath = tcDir ;

	return strPath ;
}
CString GetFilePath(HMODULE hModule, const CString strFileName )
{
	CString strPath ;
	TCHAR   tcDir[MAX_PATH] = {0} ;

	GetModuleFileName( hModule, tcDir, MAX_PATH ) ;
	ZeroMemory( _tcsrchr(tcDir,_T('\\'))+sizeof(TCHAR), _tcslen(_tcsrchr(tcDir,_T('\\'))+1)*sizeof(TCHAR) ) ;

	strPath = tcDir ;
	strPath+=strFileName;
	return strPath ;
}
CString GetSysFolder ()
{
	TCHAR chPath[100] ={0};

	GetSystemDirectory ( chPath, 100 ) ;

	return (CString)chPath ;
}

IDUIRes* CDUIDialog::m_pDUIRes = NULL ;
DUI_LANGUAGE CDUIDialog::m_eLang = DUI_ZH_CN;
// CDUIDialog

IMPLEMENT_DYNAMIC(CDUIDialog, CDialogEx)

CDUIDialog::CDUIDialog( UINT nIDTemplate, CWnd* pParentWnd )
: CDialogEx ( nIDTemplate, pParentWnd)
{
	TCHAR chSysDir[MAX_PATH] = {0} ;
	m_strCurPath = GetModuleFolder(NULL) ;
	GetSystemDirectory ( chSysDir, MAX_PATH ) ;
	m_strSysDir = chSysDir ;
	m_strDUIIniFile = m_strCurPath + _T("\\DUIPath.ini") ;
	m_IsAnswerOnOkAndOnCancel = 0 ;
}

CDUIDialog::CDUIDialog(void)
{

}

CDUIDialog::~CDUIDialog()
{
	m_mapCtrls.clear() ;
}


BEGIN_MESSAGE_MAP(CDUIDialog, CDialogEx)
	ON_MESSAGE( WM_DUI_MSG, OnDUIMsg )
	ON_MESSAGE( DUISM_LBUTTONUP, OnSMLButtonUp )
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CDUIDialog 消息处理程序

IDUIObj* CDUIDialog::GetDUISingleObjcet( LPCTSTR lpszName, BOOL& bFail )
{
	IDUIObj* pObj = NULL ;

	pObj = (IDUIObj *)m_pDUIRes->GetResObject(DUIOBJTYPE_PLUGIN, (tstring)lpszName, (ISkinObjResBase *)m_pDirectUI,TRUE);
	if ( NULL == pObj )
	{
		bFail = TRUE ;
		DebugPrintf( _T("GetDUIobj-[%s]-Fail"), lpszName ) ;
	}
	return pObj ;
}
IDUIObj* CDUIDialog::GetObjPtr ( LPCTSTR lpszName, BOOL IsCheck )
{
	IDUIObj* pObj = NULL ;

	if ( m_mapCtrls.end() == m_mapCtrls.find(lpszName) )
	{
		m_mapCtrls[lpszName] = (IDUIObj *)m_pDUIRes->GetResObject(DUIOBJTYPE_PLUGIN, (tstring)lpszName, (ISkinObjResBase *)m_pDirectUI,TRUE);
		if ( NULL == m_mapCtrls[lpszName] )
		{
			CString strErr ;
			DebugPrintf( _T("GetDUIobj-[%s]-Fail"), lpszName ) ;

			if ( FALSE == IsCheck )
			{
				strErr.Format (_T("获取皮肤控件[%s]失败，请检查软件皮肤文件！"), lpszName ) ;
			    MessageBox ( strErr,_T("皮肤错误"), MB_OK |MB_ICONERROR ) ;
			    SendMessage (WM_CLOSE, 0, 0 ) ;
			}
		}
	}
	return m_mapCtrls[lpszName] ;
}

BOOL CDUIDialog::InitSknPath ()
{
	m_strDUIDllPath = GetDirectUIDllPath() +  GetDirectUIDllName() ;
	m_strSkinDir    = GetSkinPath() ;
	m_nSkinCtrl     = IsUseSkinCtrl() ;
	m_nAbsPath      = TRUE ;
	return TRUE ;
}
DWORD CDUIDialog::LoadSkin ()
{
	DebugPrintf( _T("LoadSkin()-Start"));

	DWORD   dwRet = 0 ;
	if ( FALSE == InitSknPath () )
	{
		DebugPrintf( _T("LoadSkin()-InitSkinPath-Fail") );
		dwRet = 3 ;
		return dwRet ;
	}

	if ( NULL == GetStaticDUIRes() )
	{
		TCHAR    chCurDir[0x200] = {0} ;
		TCHAR    *p = NULL ;

		_tcscpy ( chCurDir, m_strDUIDllPath ) ;
		p = _tcsrchr ( chCurDir, '\\' ) ;
		if ( p )
		{
			*p = 0 ;
			SetCurrentDirectory(chCurDir);
		}

		m_hDUI = LoadLibrary ( m_strDUIDllPath ) ;

		if ( m_hDUI )
		{
#ifdef _UNICODE
			GET_PROC_ADDR ( m_hDUI, OpenSkinW) ;
			if ( pfnOpenSkinW )
			{
				IDUIRes* pDUIRes = pfnOpenSkinW ( (WCHAR*)(LPCTSTR)m_strDUIFile, (WCHAR*)(LPCTSTR)m_strSknFile, m_nSkinCtrl, 0, m_nAbsPath );
#else
			GET_PROC_ADDR ( m_hDUI, OpenSkinA) ;
			if ( pfnOpenSkinA )
			{
				IDUIRes* pDUIRes = pfnOpenSkinA ( (char*)(LPCTSTR)m_strDUIFile, (char*)(LPCTSTR)m_strSknFile, m_nSkinCtrl, 0, m_nAbsPath );
#endif
				if ( pDUIRes )
				{
					SetStaticDUIRes(pDUIRes) ;
					DebugPrintf(_T("Current language id [%d]"),m_eLang);
					if ( 0 != m_eLang )
					{
						m_pDUIRes->ChangeLanguage(m_eLang) ;
					}
					dwRet = 0 ;
				}
				else
				{
					DebugPrintf( _T("LoadSkin-Fail-DUI-[%s]-SKN-[%s]-SKINCTRL-[%d]-LastError-[%d]"),
						m_strDUIFile, m_strSknFile, m_nSkinCtrl, GetLastError() ) ;
					dwRet = 2 ;
				}
			}
		}
		else
		{
			DebugPrintf( _T("Load-[%s]-Fail-LastError-[%d]"), m_strDUIDllPath, GetLastError() ) ;
			dwRet = 1 ;
		}
		

		DebugPrintf ( _T("LoadSkin()-End"));
	}
	
	return dwRet ;
}
BOOL CDUIDialog::CreateDUI()
{
	ASSERT(m_pDUIRes) ;
	m_pDirectUI = (IDirectUI*)m_pDUIRes->CreateDirectUI( (tstring)m_strDUIName,HandleToLong(m_hWnd)) ;
	if ( NULL != m_pDirectUI )
	{
		return TRUE ;
	}
	else
	{
		DebugPrintf ( _T("CreateDirectUI_[%s]_Fail"), m_strDUIName ) ;
		return FALSE ;
	}
}
BOOL CDUIDialog::GetDUIObjcets()
{
	return TRUE ;
}
LRESULT CDUIDialog::OnDUIMsg( WPARAM wParam, LPARAM lParam )
{
	return 1 ;
}
void CDUIDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	if ( m_IsAnswerOnOkAndOnCancel )
	{
		CDialogEx::OnOK();
	}
}

void CDUIDialog::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( m_IsAnswerOnOkAndOnCancel )
	{
		CDialogEx::OnCancel();
	}
}

int CDUIDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if ( 0 == LoadSkin() )
	{
		if ( CreateDUI() )
		{
			return 0 ;
		}
		else
		{
			CString strErr ;
			strErr.Format ( _T("加载[%s]失败"), m_strDUIName ) ;
			AfxMessageBox(strErr) ;
			exit(0) ;
			return 1 ;
		}
	}
	else
	{
		MessageBox (_T("加载皮肤失败"), _T("提示"), MB_OK ) ;
		exit(0) ;
		return 0 ;
	}
	return 0 ;
}
LRESULT CDUIDialog::OnSMLButtonUp(WPARAM wParam,LPARAM lParam)
{
	return 1 ;
}

void CDUIDialog::OnBtnClickOK()
{
	CDialogEx::OnOK () ;
}
void CDUIDialog::OnBtnClickCancel()
{
	CDialogEx::OnCancel () ;
}
LRESULT CDUIDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( WM_CLOSE == message )
	{
		OnBtnClickCancel () ;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}

BOOL CDUIDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CString CDUIDialog::GetRealPath ( CString strPath )
{
	int nIndex = 0 ;
	CString strRealPath ;
	CStringArray strArray ;

	do
	{
		int nOldIdx = nIndex ;
		CString strValue ;

		nIndex = strPath.Find ( _T('\\'), nIndex ) ;
		if ( -1 != nIndex )
		{
			strValue = strPath.Mid ( nOldIdx, nIndex-nOldIdx ) ;
			strArray.Add (strValue) ;
			nIndex++ ;
		}
		else
		{
			strValue = strPath.Mid ( nOldIdx ) ;
			strArray.Add (strValue) ;
		}
	}while(-1!=nIndex);

	for (int i = 0; i < strArray.GetSize(); ++i )
	{
		if ( _T("..") == strArray.GetAt(i) )
		{
			if ( 0 == i )
				strRealPath = m_strCurPath ;
			strRealPath = ( GetUpFolder (strRealPath)+_T("\\") )  ;
		}
		else if ( _T(".") == strArray.GetAt(i) )
		{
			if ( 0 == i )
				strRealPath = m_strCurPath+_T("\\") ;
		}
		else if ( _T("") == strArray.GetAt(i) )
		{
			if ( 0 == i )
				strRealPath = m_strCurPath+_T("\\") ;
		}
		else
		{
			strRealPath += (strArray.GetAt(i)+_T("\\"));
		}
	}

	return strRealPath ;
}
CString CDUIDialog::GetDirectUIDllPath ()
{
	TCHAR chValue[0x200] = {0} ;

	GetPrivateProfileString ( _T("DIRECTUI"), _T("DLL"), m_strCurPath, chValue, 0x200, m_strDUIIniFile ) ;

	return GetRealPath (chValue) ;
}
CString CDUIDialog::GetSkinPath()
{
	TCHAR chValue[0x200] = {0} ;

	GetPrivateProfileString ( _T("DIRECTUI"), _T("SKIN"), _T(""), chValue, 0x200,m_strDUIIniFile ) ;

	if ( 0 == _tcslen (chValue) )
		return m_strCurPath+_T("\\Skin\\") ;
	else
	    return GetRealPath (chValue) ;
}
CString CDUIDialog::GetDirectUIDllName()
{
	TCHAR chValue[0x200] = {0} ;
	CString strDll = _T("DirectUI.dll");

	GetPrivateProfileString ( _T("DIRECTUI"), _T("DLLNAME"), _T("DirectUI.dll"), chValue, 0x200,m_strDUIIniFile ) ;
	if ( _tcslen (chValue) >= 4 )
		strDll = chValue ;	

	return strDll ;
}
inline int CDUIDialog::IsUseSkinCtrl()
{
	return GetPrivateProfileInt ( _T("DIRECTUI"), _T("SKINCTRL"), 0, m_strDUIIniFile ) ;
}


HBITMAP CDUIDialog::GetImageHandle ( LPCTSTR lpszImageFile  )
{
	if ( NULL == lpszImageFile )
		return NULL ;

	CString  strImageFile = lpszImageFile ;
	BSTR     bStrPng ;
	HBITMAP  pBitmap ;
	bStrPng = strImageFile.AllocSysString() ;
	Bitmap bitmap(bStrPng);
	SysFreeString(bStrPng) ;
	bitmap.GetHBITMAP(NULL, &pBitmap);

	return pBitmap ;
}

int CDUIDialog::GetLangId ()
{
   if (m_pDUIRes)
   {
	   DUI_LANGUAGE lang ;
	   m_pDUIRes->GetCurLanguage(&lang) ;
	   return (int)lang ;
   }

   return -1 ;
}

BOOL CDUIDialog::SetLangId ( int nLang, BOOL IsChange )
{
	m_eLang = (DUI_LANGUAGE)nLang ;
	DebugPrintf (_T("Set language id [%d]"), m_eLang) ;

	if (m_pDUIRes)
	{
		DUI_LANGUAGE lang ;
		m_pDUIRes->GetCurLanguage(&lang) ;
		if ( nLang != (int)lang )
		{
			m_eLang = (DUI_LANGUAGE)nLang ;
			if ( IsChange )
			    m_pDUIRes->ChangeLanguage(m_eLang) ;
		}

		return TRUE ;
	}

	return FALSE ;
}

tstring  CDUIDialog::GetDUIStr ( tstring strID, int nLang )
{
    tstring strText ;

	if ( m_pDUIRes )
	{
		if ( nLang == -1 )
			nLang = (int)m_eLang ;
		strText = m_pDUIRes->GetString ( (DUI_LANGUAGE)nLang, strID ) ; 
	}

	return strText ;
}

BOOL CDUIDialog::ChangeSkin(std::tstring szSknFile)
{
	VARIANT_BOOL bret = VARIANT_FALSE;
	if (m_pDUIRes)
	{
		m_pDUIRes->ChangeSkn(szSknFile, &bret);
	}
	return bret;
}

IDUIImageBase* CDUIDialog::GetImageBaseFromFile(LPCTSTR path)
{
	if (m_pDUIRes)
	{
		IDUIImageBase* pImage = m_pDUIRes->GetImageBaseFromFile(path);
		//修正图片的尺寸
		CImage image;
		if (S_OK == image.Load(path))
		{
			SkinRect rect;
			rect.left = rect.top = 0;
			rect.right = image.GetWidth();
			rect.bottom = image.GetHeight();
			pImage->put_rect(&rect);
			pImage->put_rcBorder(rect);
			image.Destroy();
		}

		return pImage;
	}
	return NULL;
}