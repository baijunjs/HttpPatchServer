#include "StdAfx.h"
#include "ExceptionHandle.h"
#include <DbgHelp.h>
#include <strsafe.h>

#pragma comment(lib,"Dbghelp.lib")

CExceptionHandle g_ExceptionHandle;

typedef BOOL (WINAPI *_TMiniDumpWriteDump)(
							  _In_ HANDLE                            hProcess,
							  _In_ DWORD                             ProcessId,
							  _In_ HANDLE                            hFile,
							  _In_ MINIDUMP_TYPE                     DumpType,
							  _In_ PMINIDUMP_EXCEPTION_INFORMATION   ExceptionParam,
							  _In_ PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
							  _In_ PMINIDUMP_CALLBACK_INFORMATION    CallbackParam
							  );



CExceptionHandle::CExceptionHandle(void)
{
	SetUnhandledExceptionFilter(CExceptionHandle::UnhandledExceptionFilter);
}

CExceptionHandle::~CExceptionHandle(void)
{
}


LONG WINAPI CExceptionHandle::UnhandledExceptionFilter(
									 __in          struct _EXCEPTION_POINTERS* pExceptionPointers
									 )
{

	SetErrorMode(SEM_NOGPFAULTERRORBOX);

	//收集信息
	CString strBuild;
	strBuild.Format(_T("Build: %s %s"), __DATE__, __TIME__);
	CString strError;
	HMODULE hModule;
	TCHAR szModuleName[MAX_PATH] = {0};
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)pExceptionPointers->ExceptionRecord->ExceptionAddress, &hModule);
	GetModuleFileName(hModule, szModuleName, ARRAYSIZE(szModuleName));
	strError.AppendFormat(_T("%s %d , %d ,%d."), szModuleName, pExceptionPointers->ExceptionRecord->ExceptionCode, 
		pExceptionPointers->ExceptionRecord->ExceptionFlags, 
		pExceptionPointers->ExceptionRecord->ExceptionAddress);

	PathRemoveFileSpec(szModuleName);

	//生成 mini crash dump
	BOOL bMiniDumpSuccessful;
	TCHAR szPath[MAX_PATH];
	TCHAR szFileName[MAX_PATH];
	TCHAR* szAppName = _T("PathDown");
	TCHAR* szVersion = _T("v1.0");
	DWORD dwBufferSize = MAX_PATH;
	HANDLE hDumpFile;
	SYSTEMTIME stLocalTime;
	MINIDUMP_EXCEPTION_INFORMATION ExpParam;
	GetLocalTime(&stLocalTime);
	GetTempPath(dwBufferSize, szPath);
	StringCchPrintf(szFileName, MAX_PATH, _T("%s%s"), szPath, szAppName);
	CreateDirectory(szFileName, NULL);
	StringCchPrintf(szFileName, MAX_PATH, _T("%s\\%s-%ld-%ld.dmp"),
		szModuleName, szAppName, GetCurrentProcessId(), GetCurrentThreadId());
	hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

	MINIDUMP_USER_STREAM UserStream[2];
	MINIDUMP_USER_STREAM_INFORMATION UserInfo;
	UserInfo.UserStreamCount = 1;
	UserInfo.UserStreamArray = UserStream;
	UserStream[0].Type = CommentStreamW;
	UserStream[0].BufferSize = strBuild.GetLength() * sizeof(TCHAR);
	UserStream[0].Buffer = strBuild.GetBuffer();
	UserStream[1].Type = CommentStreamW;
	UserStream[1].BufferSize = strError.GetLength() * sizeof(TCHAR);
	UserStream[1].Buffer = strError.GetBuffer();

	ExpParam.ThreadId = GetCurrentThreadId();
	ExpParam.ExceptionPointers = pExceptionPointers;
	ExpParam.ClientPointers = TRUE;

	int MiniDumpWithDataSegs = (int) MiniDumpNormal
		| MiniDumpWithHandleData
		| MiniDumpWithUnloadedModules
		| MiniDumpWithIndirectlyReferencedMemory
		| MiniDumpScanMemory
		| MiniDumpWithProcessThreadData
		| MiniDumpWithThreadInfo;

	bMiniDumpSuccessful = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, (MINIDUMP_TYPE)MiniDumpWithDataSegs, &ExpParam, NULL, NULL);
	// 上传mini dump 到自己服务器（略）


	return EXCEPTION_CONTINUE_SEARCH; //或者 EXCEPTION_EXECUTE_HANDLER 关闭程序
}