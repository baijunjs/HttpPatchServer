#include "stdafx.h"
#include "config.h"
#include "clock_t.h"


typedef ULONGLONG(*f_compatible_get_tick_count64)();

static mutex_t compatible_get_tick_count64_mutex;

ULONGLONG compatible_get_tick_count64()
{
	scoped_lock_t locker(compatible_get_tick_count64_mutex);

	static DWORD s_wrap = 0;
	static DWORD s_last_tick = 0;
	const DWORD current_tick = ::GetTickCount();

	if (current_tick < s_last_tick)
		++s_wrap;

	s_last_tick = current_tick;
	const ULONGLONG result = (static_cast<ULONGLONG>(s_wrap) << 32) + static_cast<ULONGLONG>(current_tick);

	return result;
}

f_compatible_get_tick_count64 init_compatible_get_tick_count64()
{
	f_compatible_get_tick_count64 func = NULL;
	HMODULE module = ::LoadLibraryA("Kernel32.dll");
	if (module != NULL)
		func = reinterpret_cast<f_compatible_get_tick_count64>(::GetProcAddress(module, "GetTickCount64"));

	if (func == NULL)
		func = compatible_get_tick_count64;

	::FreeLibrary(module);

	return func;
}

static f_compatible_get_tick_count64 my_get_tick_count64 = init_compatible_get_tick_count64();


cclock_t::cclock_t() :
last_tsc(rdtsc()),
last_time(static_cast<uint64_t>((*my_get_tick_count64)()))
{
}

cclock_t::~cclock_t()
{
}

uint64_t cclock_t::now_us()
{
	//  Get the high resolution counter's accuracy.
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceFrequency(&ticksPerSecond);

	//  What time is it?
	LARGE_INTEGER tick;
	QueryPerformanceCounter(&tick);

	//  Convert the tick number into the number of seconds
	//  since the system was started.
	double ticks_div = ticksPerSecond.QuadPart / 1000000.0;
	return (uint64_t)(tick.QuadPart / ticks_div);
}

uint64_t cclock_t::now_ms()
{
	uint64_t tsc = rdtsc();

	//  If TSC is not supported, get precise time and chop off the microseconds.
	if (!tsc)
	{
		// Under Windows, now_us is not so reliable since QueryPerformanceCounter
		// does not guarantee that it will use a hardware that offers a monotonic timer.
		// So, lets use GetTickCount when GetTickCount64 is not available with an workaround
		// to its 32 bit limitation.
		return static_cast<uint64_t>((*my_get_tick_count64)());
	}

	//  If TSC haven't jumped back (in case of migration to a different
	//  CPU core) and if not too much time elapsed since last measurement,
	//  we can return cached time value.
	if ((tsc - last_tsc <= (clock_precision / 2) && tsc >= last_tsc))
		return last_time;

	last_tsc = tsc;
	last_time = static_cast<uint64_t>((*my_get_tick_count64)());
	return last_time;
}

uint64_t cclock_t::rdtsc()
{
	return __rdtsc();
}