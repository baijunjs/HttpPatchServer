#include "StdAfx.h"
#include "ExceptionHandle.h"
#include <DbgHelp.h>

//#pragma comment(lib,"Dbghelp.lib")

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
									 __in          struct _EXCEPTION_POINTERS* ExceptionInfo
									 )
{

	HANDLE hFile = GetDmpFileHandle();
	if (hFile == INVALID_HANDLE_VALUE)
		return 1;
	MINIDUMP_EXCEPTION_INFORMATION mei = {0};
	mei.ExceptionPointers = ExceptionInfo;
	mei.ThreadId = GetCurrentThreadId();
	mei.ClientPointers = TRUE;
	HMODULE hModule = LoadLibraryA("DbgHelp.dll");
	if (hModule)
	{
		_TMiniDumpWriteDump MiniDumpWriteDump = (_TMiniDumpWriteDump)GetProcAddress(hModule, "MiniDumpWriteDump");
		if (MiniDumpWriteDump)
			MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &mei, NULL, NULL);
		CloseHandle(hFile);
	}

	return 0;
}

HANDLE CExceptionHandle::GetDmpFileHandle()
{
	std::string szDumpFile = appconfig.m_szAppPath + "\\patchdown.dmp";
	HANDLE hFile = CreateFileA(
		szDumpFile.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	return hFile;
}