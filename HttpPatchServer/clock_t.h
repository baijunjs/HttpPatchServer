#pragma once

#include <stdint.h>
class mutex_t
{
public:
	inline mutex_t()
	{
		InitializeCriticalSection(&cs);
	}

	inline ~mutex_t()
	{
		DeleteCriticalSection(&cs);
	}

	inline void lock()
	{
		EnterCriticalSection(&cs);
	}

	inline bool try_lock()
	{
		return (TryEnterCriticalSection(&cs)) ? true : false;
	}

	inline void unlock()
	{
		LeaveCriticalSection(&cs);
	}

	inline CRITICAL_SECTION* get_cs()
	{
		return &cs;
	}

private:

	CRITICAL_SECTION cs;

	//  Disable copy construction and assignment.
	mutex_t(const mutex_t&);
	void operator = (const mutex_t&);
};


struct scoped_lock_t
{
	scoped_lock_t(mutex_t& mutex_)
		: mutex(mutex_)
	{
		mutex.lock();
	}

	~scoped_lock_t()
	{
		mutex.unlock();
	}

private:

	mutex_t& mutex;

	// Disable copy construction and assignment.
	scoped_lock_t(const scoped_lock_t&);
	const scoped_lock_t &operator = (const scoped_lock_t&);
};


struct scoped_optional_lock_t
{
	scoped_optional_lock_t(mutex_t* mutex_)
		: mutex(mutex_)
	{
		if (mutex != NULL)
			mutex->lock();
	}

	~scoped_optional_lock_t()
	{
		if (mutex != NULL)
			mutex->unlock();
	}

private:

	mutex_t* mutex;

	// Disable copy construction and assignment.
	scoped_optional_lock_t(const scoped_lock_t&);
	const scoped_optional_lock_t &operator = (const scoped_lock_t&);
};


class cclock_t
{
public:

	cclock_t();
	~cclock_t();

	//  CPU's timestamp counter. Returns 0 if it's not available.
	static uint64_t rdtsc();

	//  High precision timestamp.
	static uint64_t now_us();

	//  Low precision timestamp. In tight loops generating it can be
	//  10 to 100 times faster than the high precision timestamp.
	uint64_t now_ms();

private:

	//  TSC timestamp of when last time measurement was made.
	uint64_t last_tsc;

	//  Physical time corresponding to the TSC above (in milliseconds).
	uint64_t last_time;

	cclock_t(const cclock_t&);
	const cclock_t &operator = (const cclock_t&);
};
