#pragma once

#include "../Include/sdkbase/IeHomePageUrlBase.h"
#include "../include/SdkBase/VRVEdpDialog.h"

using namespace VRVSDK;

#ifdef _cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////
	//函数名：GetCVrvTestUnit()
	//功  能：获得设置IE首页类指针
	//参  数：函数
	//返回值：IeHomePageUrlBase 指针
	//备  注：无
	//////////////////////////////////////////////////////////////////////////
	IeHomePageUrlBase * WINAPI GetCIeHomePageUrl(  const TCHAR * pClassName = NULL );

	CVRVEdpDialog* WINAPI CreateEdpDialog (UINT iDlgID, HWND pParentWnd);

#ifdef _cplusplus
}

#endif

