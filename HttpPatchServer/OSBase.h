#pragma once
#ifndef OSBASE_H
#define OSBASE_H

#include <string>
#include <iostream>

#include <vector>
#include <list>
#include <map>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

#include <time.h>
#include <stdio.h>

#include <intrin.h>


/************************************************************************/
/*	宏定义部分
/************************************************************************/

#if !defined(MAKELDWORD)
#define MAKELDWORD(low,high) \
	((DWORDLONG)(((DWORD)(low)) | ((DWORDLONG)((DWORD)(high))) << 32))
#endif



//	申请内存通用宏
# define NEW(POINTER, CONSTRUCTOR) \
	do \
	{ \
		try \
		{ \
			POINTER = new CONSTRUCTOR; \
		} \
		catch (...) \
		{ POINTER = NULL; } \
	} while (0)








/************************************************************************/
/*	通用模板部分
/************************************************************************/

/*
 *	指针循环删除
 */
template<class TYPE>
struct Del_Pointer
{
	void operator()(TYPE& _X) const
	{
		delete (_X);
	}
};

/*
 *	指针小于比较
 */
template<class _Ty>
struct Less_Pointer
{
	bool operator()(const _Ty& _X, const _Ty& _Y) const
	{
		return (*_X) < (*_Y);
	}
};

struct StdStringCompare
{
	bool operator()(const std::string &_X, const std::string &_Y) const
	{
		return _stricmp(_X.c_str(), _Y.c_str()) < 0;
	}
};


typedef std::vector<std::string>                 STRINGVECTOR;
typedef std::vector<DWORD>                       DWORDVECTOR;
typedef std::vector<DWORD>                       IPADDRVECTOR;
typedef std::list<std::string>                   STRINGLIST;
typedef std::map<std::string, std::string, StdStringCompare>	STRINGMAP;
typedef std::set<DWORD>							IPADDRSET;
typedef std::set<std::string>					STRINGSET;
/**
* 该模板实现对申请的内存的自动释放
*/
template <class TYPE>
class TMatrix
{
public:
	/**
	* @param nSize 要申请多大内存.
	*/
	TMatrix(int nSize) : _nSize(nSize),
		_lpResult(NULL)
	{
		if (nSize > 0)
		{
			NEW(_lpResult, TYPE[nSize]);
			Init();
		}
	}

	TMatrix(TYPE* Result) : _nSize(0), _lpResult(Result)
	{}

	~TMatrix()
	{
		if (IsRight()) delete[]_lpResult;
	}

	//	是否成功申请到内存
	bool IsRight() { return _lpResult ? true : false; }

	//	数组(矩阵)的大小
	int  Size() { return _nSize; }

	//	初始化
	void Init() { if (_lpResult) ZeroMemory(_lpResult, Size() * sizeof(TYPE)); }

	TYPE& operator[](int nIndex) const
	{
		return  _lpResult[nIndex];
	}

	TYPE * operator* ()
	{
		return _lpResult;
	}

protected:
	TYPE*   _lpResult;
	int     _nSize;
};

typedef TMatrix<CHAR> TMatrixString;



/*
* 主要是处理句柄,退出时自动关闭句柄
*/
template <class TYPE, class FUN>
class THandleManager
{
public:
	THandleManager(TYPE handle) : _handle(handle) {}
	~THandleManager()
	{
		if (Handle()) _fun.close(Handle());
	}
	TYPE Handle() { return _handle; }
protected:
	TYPE	_handle;
	FUN		_fun;
};





/************************************************************************/
/*	锁部分
/************************************************************************/

/*
*	本进程线程使用
*/
class ACE_Thread_Mutex
{
public:
	ACE_Thread_Mutex()
	{
		::InitializeCriticalSection(&_handle);
	}

	~ACE_Thread_Mutex(void)
	{
		::DeleteCriticalSection(&_handle);
	}

	void Lock()
	{
		::EnterCriticalSection(&_handle);
	}

	void UnLock()
	{
		::LeaveCriticalSection(&_handle);
	}

	LPCRITICAL_SECTION get_handle()
	{
		return &_handle;
	}

protected:
	CRITICAL_SECTION _handle;

};

/*
*	进程间使用
*/
class ACE_Process_Mutex
{
#ifdef WIN32
public:
	ACE_Process_Mutex(LPCSTR i)
	{
		_handle = ::CreateMutexA(NULL, FALSE, i);
	}

	~ACE_Process_Mutex(void)
	{
		::CloseHandle(_handle);
	}

	void Lock()
	{
		::WaitForSingleObject(_handle, INFINITE);
	}

	void UnLock()
	{
		::ReleaseMutex(_handle);
	}

	HANDLE get_handle()
	{
		return &_handle;
	}

protected:
	HANDLE _handle;
#endif

};


class ACE_Thread_Spin
{
public:
	ACE_Thread_Spin() :m_spin(0) {}
	~ACE_Thread_Spin() {}
	void Lock()
	{
		LONG spincount = 0;
		while (_InterlockedCompareExchange(&m_spin, 1, 0) == 1)
		{
			_ReadWriteBarrier();
			if (spincount < 16)
				_mm_pause();
			else if (spincount < 32)
				Sleep(0);
			else
				Sleep(1);
			++spincount;
		}
	}

	void UnLock()
	{
		_ReadWriteBarrier();
		_InterlockedExchange(&m_spin, 0);
	}
private:
	volatile LONG m_spin;
};


template <class ACE_LOCK>
class ACE_Guard
{
public:
	ACE_Guard(ACE_LOCK &l)
		: _lpLock(&l)
	{
		_lpLock->Lock();
	}

	~ACE_Guard(void)
	{
		_lpLock->UnLock();
	}

protected:
	ACE_LOCK* _lpLock;
};


class ACE_Thread_RWLock
{
public:
	ACE_Thread_RWLock()
		: m_cnt(0)
		, m_evt(NULL)
		//, m_cs(NULL)
		, m_sem(NULL)
	{
		// 提倡的做法，在专门的初始化函数里创建和初始化这些变量

		::InitializeCriticalSection(&m_cs);

		// Event初始处于激活状态，且必须是手动重置，否则存在死锁隐患，即等待Event前，先被激活了
		m_evt = ::CreateEvent(NULL, TRUE, TRUE, NULL);
		m_sem = ::CreateSemaphore(NULL, 1, 1, NULL);
	}
	~ACE_Thread_RWLock()
	{
		::CloseHandle(m_sem);
		::CloseHandle(m_evt);
		::DeleteCriticalSection(&m_cs);
		m_sem = NULL;
		m_evt = NULL;
	}
public:
	virtual BOOL Initialize()
	{
		if (m_evt == NULL || m_sem == NULL)
		{
			return FALSE;
		}
		return TRUE;
	}
	virtual void AcquireReadLock()
	{
		::WaitForSingleObject(m_evt, INFINITE);

		::EnterCriticalSection(&m_cs);
		if (0 == m_cnt++)
			::WaitForSingleObject(m_sem, INFINITE);
		::LeaveCriticalSection(&m_cs);

	}
	virtual void ReleaseReadLock()
	{

		::EnterCriticalSection(&m_cs);
		if (0 == --m_cnt)
			::ReleaseSemaphore(m_sem, 1, NULL);
		::LeaveCriticalSection(&m_cs);
	}
	virtual void AcquireWriteLock()
	{
		::ResetEvent(m_evt);
		::WaitForSingleObject(m_sem, INFINITE);
	}
	virtual void ReleaseWriteLock()
	{
		::ReleaseSemaphore(m_sem, 1, NULL);
		::SetEvent(m_evt);

	}
	virtual void Release()
	{
		delete this;
	}
private:
	volatile DWORD      m_cnt;
	CRITICAL_SECTION    m_cs;
	HANDLE              m_evt;
	HANDLE              m_sem;
};


template<typename T = ACE_Thread_RWLock>
class ACE_Thread_ReadLock
{
public:
	ACE_Thread_ReadLock(T& a) :m_rwLock(&a)
	{
		lock();
	}
	~ACE_Thread_ReadLock()
	{
		unlock();
	}
	void lock()
	{
		m_rwLock->AcquireReadLock();
	}

	void unlock()
	{
		m_rwLock->ReleaseReadLock();
	}

private:
	ACE_Thread_RWLock* m_rwLock;
};


template<typename T = ACE_Thread_RWLock>
class ACE_Thread_WriteLock
{
public:
	ACE_Thread_WriteLock(T& a) :m_rwLock(&a)
	{
		lock();
	}
	~ACE_Thread_WriteLock()
	{
		unlock();
	}
	void lock()
	{
		m_rwLock->AcquireWriteLock();
	}

	void unlock()
	{
		m_rwLock->ReleaseWriteLock();
	}

private:
	ACE_Thread_RWLock* m_rwLock;
};

#endif
