
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include "DUIDialog.h"
#include <sstream>
#include <string>
#include <regex>
#include <thread>
#include "curl.h"
#include "EDPPatchBase.h"
#include "PackInterface.h"
#include "AppConfig.h"
#include "log.hpp"
#include "crc.h"
#include <RCF/RCF.hpp>
#include "Language.h"

#pragma warning(disable:4244)
#pragma warning(disable:4091)


enum  CUSTOM_MESSAGE
{
	UM_CUSTOM_TRAY = (WM_USER + 1),
	UM_CUSTOM_DOWNCENTER,
	UM_CUSTOM_SETTING,
	UM_CUSTOM_STATICLIST,
	UM_CUSTOM_DOWNLIST,
	UM_DOWNVIEW_INDEXITEM,
	UM_DOWNVIEW_PATCHITEM,
	UM_DOWNVIEW_CLEANITEMS,
	UM_DOWNVIEW_REFRESH,
	UM_DOWNVIEW_SETTEXT,
	UM_ERRORVIEW_INDEXITEM,
	UM_ERRORVIEW_PATCHITEM,
	UM_ERRORVIEW_CLEANITEMS,
	UM_STATICVIEW_CLEANITEMS,
	UM_STATICVIEW_INDEXITEM,
	UM_STATICVIEW_PATCHITEM,
	UM_STATICVIEW_SETTEXT,
};

#ifdef _UNICODE
#define tregex				wregex
#define tsmatch				wsmatch
#define tstring				wstring
#define tstringstream		wstringstream
#else
#define tregex				regex
#define tsmatch				smatch
#define tstring				string
#define tstringstream		stringstream
#endif

#import "msado15.dll" no_namespace rename("EOF", "adoEOF") 

BOOL IsTimeValid(std::tstring &sztime);
BOOL IsIpValid(std::tstring &szIp);
BOOL GetFileSHA1(std::tstring szFile, OUT std::tstring &szSha);
void GetIntervalTime(std::tstring &szTime, std::tstring &szBegin, std::tstring &szEnd);
void GetTime(std::tstring& szTime, std::tstring &szHour, std::tstring &szMin, std::tstring &szSec);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


