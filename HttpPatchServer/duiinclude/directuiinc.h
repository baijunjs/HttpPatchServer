#ifndef __HEAD__DIRECTUIINC__
#define __HEAD__DIRECTUIINC__
#pragma once

#pragma warning(push)
#pragma warning(disable : 4278)
#pragma warning(disable : 4996)
#pragma warning(disable:4189)


//extern "C" __declspec(dllimport) void* CALLBACK GetCtrlBase(void* hDataBlock);
//extern "C" __declspec(dllimport) void* CALLBACK GetDUIControlFromDataBlock(void* hDataBlock);

typedef void* (CALLBACK *pfnGetCtrlBase)(void* hDataBlock);
typedef void* (CALLBACK *pfnGetDUIControlFromDataBlock)(void* hDataBlock);
typedef void  (CALLBACK *pfnSetUseMultiLanguage)(BOOL bEnable);

void* CALLBACK GetCtrlBase(void* hDataBlock);
void* CALLBACK GetDUIControlFromDataBlock(void* hDataBlock);
void  CALLBACK SetUseMultiLanguage(BOOL bEnable);

#include "DirectUI.h"
#include "KernelAll.h"
#include "OfficeAll.h"
#include "AdvancedAll.h"
#include "IndustryAll.h"


typedef void(CALLBACK * Fun_FreeSkin)();
typedef IDUIRes*(CALLBACK * Fun_OpenSkinA)(char * szSkinPath, char * szSknPath, BOOL bSkinCtrls, BOOL bAddRef, BOOL bAbsPath);
//typedef IDUIRes*(CALLBACK * Fun_OpenSkinW)(WCHAR * szSkinPath, WCHAR * szSknPath, BOOL bSkinCtrls, BOOL bAddRef, BOOL bAbsPath);

//#pragma warning(pop)
//
//#define DIRECTUI_GETCONTROL(objname) \
//	(IDUIControlBase*)theApp.m_pDUIRes->GetResObject(DUIOBJTYPE_PLUGIN,objname,(ISkinObjResBase*)m_pDirectUI,TRUE)
//
//
//extern "C" __declspec(dllimport) IDUIRes* CALLBACK OpenSkinW(wchar_t* strSkinPath,wchar_t *strSknPath, BOOL bSkinCtrls = FALSE, BOOL bAddRef = FALSE, BOOL bAbsPath = FALSE);
//
//extern "C" __declspec(dllimport) IDUIRes* CALLBACK OpenSkinA(char* strSkinPath,char*strSknPath, BOOL bSkinCtrls = FALSE, BOOL bAddRef = FALSE, BOOL bAbsPath = FALSE);
//
//#ifdef _UNICODE
//#define OpenSkin OpenSkinW
//#else
//#define OpenSkin OpenSkinA
//#endif

//extern "C" __declspec(dllimport) void CALLBACK FreeSkin();
//extern "C" __declspec(dllimport) unsigned int CALLBACK DUIGetLastError();
//extern "C" __declspec(dllimport) void CALLBACK EnableDebugInfo(BOOL bEnable);
//extern "C" __declspec(dllimport) void CALLBACK SetUseMultiLanguage(BOOL bEnable);

//#pragma comment(lib,"kdui32.lib") 

#endif //__HEAD__DIRECTUI__
