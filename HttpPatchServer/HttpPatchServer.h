
// HttpPatchServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHttpPatchServerApp: 
// �йش����ʵ�֣������ HttpPatchServer.cpp
//

class CHttpPatchServerApp : public CWinApp
{
public:
	CHttpPatchServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHttpPatchServerApp theApp;
