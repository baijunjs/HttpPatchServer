#pragma once

#include "../Include/sdkbase/IeHomePageUrlBase.h"
#include "../include/SdkBase/VRVEdpDialog.h"

using namespace VRVSDK;

#ifdef _cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////
	//��������GetCVrvTestUnit()
	//��  �ܣ��������IE��ҳ��ָ��
	//��  ��������
	//����ֵ��IeHomePageUrlBase ָ��
	//��  ע����
	//////////////////////////////////////////////////////////////////////////
	IeHomePageUrlBase * WINAPI GetCIeHomePageUrl(  const TCHAR * pClassName = NULL );

	CVRVEdpDialog* WINAPI CreateEdpDialog (UINT iDlgID, HWND pParentWnd);

#ifdef _cplusplus
}

#endif

