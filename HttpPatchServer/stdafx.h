
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

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


