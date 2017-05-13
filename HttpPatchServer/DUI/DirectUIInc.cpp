#include "stdafx.h"
#include "DirectUIInc.h"
#include <Shlwapi.h>
#include "../common/GetProcessImagePath.h"
static HINSTANCE g_hClearTraceDll = NULL;
static PopenSkinFunW OpenSkinFunW = NULL;
static PopenSkinFunA OpenSkinFunA = NULL;
static CString g_strPathCurrentDirectory;

BOOL InitDll( CString strDLLPath  )
{
	HINSTANCE g_hClearTraceDll = LoadLibrary(strDLLPath);
	DWORD err = GetLastError();
	if (NULL == g_hClearTraceDll)
	{
		return FALSE;
	}
#ifdef _UNICODE
	OpenSkinFunW = (PopenSkinFunW)GetProcAddress(g_hClearTraceDll, "OpenSkinW");
	if (NULL == OpenSkinFunW)
	{
		return FALSE;
	}
	
#else
	OpenSkinFunA = (PopenSkinFunA)GetProcAddress(g_hClearTraceDll, "OpenSkinA");
	if (NULL == OpenSkinFunA)
	{
		return FALSE;
	}
#endif

	return TRUE;
}

CString FindChangePath( CString strCurPath, CString strComparePath )
{
	if ( strCurPath.ReverseFind('\\')== ( strCurPath.GetLength()-1) )
	{
		strCurPath = strCurPath.Left(strCurPath.ReverseFind(_T('\\')) );
	}
	
	while ( strComparePath.Find(_T("../") )==0)
	{
		strComparePath = strComparePath.Right(strComparePath.GetLength()-3);
		strCurPath = strCurPath.Left(strCurPath.ReverseFind(_T('\\')) );
	}

	CString strPath = strCurPath +_T("\\") +strComparePath;
	return strPath;

}
IDUIRes*  GetOpenSkinA(char* strSkinPath1,char*strSknPath1, BOOL bSkinCtrls , BOOL bAddRef , BOOL bAbsPath)
{
	//设置路径
	

	if ( g_strPathCurrentDirectory.IsEmpty() )
	{
		TCHAR   szPath[MAX_PATH * 4] = {0};
		CString strSkinPath          = _T("");

		CGetProcessImagePath::GetModuleFileName_OS(NULL, szPath, MAX_PATH * 4);
		strSkinPath = szPath;
		strSkinPath = strSkinPath.Left(strSkinPath.ReverseFind(_T('\\')) );
		g_strPathCurrentDirectory = strSkinPath +_T("\\");;
		CString outPutStr;
		outPutStr.Format( _T("当前路径%s"),g_strPathCurrentDirectory);
	}
	
	CString strSkinpathNew	= FindChangePath(g_strPathCurrentDirectory,strSkinPath1);
	CString strSknpathNew	= FindChangePath(g_strPathCurrentDirectory,strSknPath1);
	CString iniPath = g_strPathCurrentDirectory + _T("DirectUiPath.ini");

	TCHAR  DirectUiPath[256] = {0};
	GetPrivateProfileString("DirectUiPath","Path","",DirectUiPath,256,iniPath); 
	CString  DllPath = DirectUiPath;

	if ( DllPath.CompareNoCase(_T("Local")) !=0&&DllPath.IsEmpty()!=TRUE)
	{
		DllPath =FindChangePath(g_strPathCurrentDirectory,DllPath);;
		SetCurrentDirectory(DllPath);
		DllPath +=_T("\\DirectUI.dll");
	}
	else
	{//Dll在当前文件夹
		DllPath=g_strPathCurrentDirectory+_T("DirectUI.dll");
	}
	
	if ( OpenSkinFunA == NULL )
	{
		if ( InitDll(DllPath) == FALSE)
		{
			return NULL;
		}
	}
	IDUIRes* pres = OpenSkinFunA(strSkinpathNew.GetBuffer(),strSknpathNew.GetBuffer(), bSkinCtrls ,  bAddRef ,  bAbsPath);

	SetCurrentDirectory(g_strPathCurrentDirectory);
	return pres;
}
VOID * GetOpenSkinW(wchar_t* strSkinPath1,wchar_t *strSknPath1, BOOL bSkinCtrls , BOOL bAddRef , BOOL bAbsPath)
{
	IDUIRes* pres = NULL;
#ifdef _UNICODE
	TCHAR   szPath[MAX_PATH * 4] = {0};
	CString strSkinPath          = _T("");
	CGetProcessImagePath::GetModuleFileName_OS(NULL, szPath, MAX_PATH * 4);
	strSkinPath = szPath;
	strSkinPath = strSkinPath.Left(strSkinPath.ReverseFind(_T('\\')) );
	TCHAR   szPath[MAX_PATH * 4] = {0};
	CString strSkinPath          = _T("");

	CGetProcessImagePath::GetModuleFileName_OS(NULL, szPath, MAX_PATH * 4);
	strSkinPath = szPath;
	strSkinPath = strSkinPath.Left(strSkinPath.ReverseFind(_T('\\')) );

	if ( g_strPathCurrentDirectory.IsEmpty() )
	{
		g_strPathCurrentDirectory = strSkinPath +_T("\\");;
		CString outPutStr;
		outPutStr.Format( _T("当前路径%s"),g_strPathCurrentDirectory);
	}

	CString strSkinpathNew = FindChangePath(strSkinPath,strSkinPath1);

	CString strSknpathNew = FindChangePath(strSkinPath,strSknPath1);

	CString iniPath = strSkinPath + _T("\\DirectUiPath.ini");

	TCHAR  DirectUiPath[256] = {0};
	GetPrivateProfileString("DirectUiPath","Path","",DirectUiPath,256,iniPath); 
	CString  DllPath = DirectUiPath;

	if ( DllPath.CompareNoCase(_T("Local")) !=0&&DllPath.IsEmpty()!=TRUE)
	{
		DllPath =FindChangePath(strSkinPath,DllPath);;
		SetCurrentDirectory(DllPath);
		DllPath +=_T("\\DirectUI.dll");
	}
	else
	{//Dll在当前文件夹
		DllPath=strSkinPath+_T("\\DirectUI.dll");
	}

	if ( OpenSkinFunA == NULL )
	{
		if ( InitDll(DllPath) == FALSE)
		{
			return NULL;
		}
	}
	pres = OpenSkinFunA(strSkinpathNew.GetBuffer(),strSknpathNew.GetBuffer(), bSkinCtrls ,  bAddRef ,  bAbsPath);

	SetCurrentDirectory(strSkinPath);
#endif
	
	return pres;
}

CString GetCurDirectry()
{
	if ( g_strPathCurrentDirectory.IsEmpty() )
	{
		TCHAR   szPath[MAX_PATH * 4] = {0};
		CString strSkinPath          = _T("");

		CGetProcessImagePath::GetModuleFileName_OS(NULL, szPath, MAX_PATH * 4);
		strSkinPath = szPath;
		strSkinPath = strSkinPath.Left(strSkinPath.ReverseFind(_T('\\')) );
		g_strPathCurrentDirectory = strSkinPath +_T("\\");;
		CString outPutStr;
		outPutStr.Format( _T("当前路径%s"),g_strPathCurrentDirectory);
	}
	return g_strPathCurrentDirectory;
}