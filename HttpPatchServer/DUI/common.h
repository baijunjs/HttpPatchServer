#pragma once

#include "stdafx.h"


CString GetFilePath(HMODULE hModule, const CString strFileName ) ;
CString GetModuleFolder( HMODULE hModule ) ;
CString GetUpFolder(LPCTSTR lpCurFolder) ;
unsigned long GetOsVersion() ;
CString SeleteFile ( CWnd* pWnd,CString strType,int nType ) ;
void DebugPrintf(const char* szMsg,...);
BOOL Is64bitSystem();
std::string  GetCurtime() ;
void ShutDownSystem ( int nType ) ;
BOOL EnumFiles( IN LPCTSTR lpszDir, IN LPCTSTR lpszKey, OUT std::vector<std::string> &vtFiles ) ;
