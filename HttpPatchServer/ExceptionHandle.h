#pragma once

class CExceptionHandle
{
public:
	CExceptionHandle(void);
	~CExceptionHandle(void);
public:
	static LONG WINAPI UnhandledExceptionFilter(
		__in          struct _EXCEPTION_POINTERS* ExceptionInfo
		);
	static HANDLE GetDmpFileHandle();
};
