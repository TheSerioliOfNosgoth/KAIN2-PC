#include "CORE.H"
#include "TIMER.H"
#include "PSX/MAIN.H"

long gameTimer; // 0x800CE188
#ifdef PC_VERSION
LARGE_INTEGER PerformanceCount,
	Frequency;
#endif

#if defined(PSXPC_VERSION)
unsigned long long TIMER_GetTimeMS()
#else
unsigned long TIMER_GetTimeMS()
#endif
{
#if defined (PSXPC_VERSION)
	return (1000 * Emulator_GetPerformanceCounter()) / Emulator_GetPerformanceFrequency();
#elif defined(PSX_VERSION)
	unsigned long ticks;
	unsigned long mticks;

	EnterCriticalSection();
	ticks = GetRCnt(0xF2000000);
	mticks = gameTimer;
	ExitCriticalSection();
	return (mticks >> 16) * 126819 + (ticks & 0xFFFF | mticks << 16) / 33869;
#else
	unsigned __int64 result; // rax

	QueryPerformanceCounter(&PerformanceCount);
	QueryPerformanceFrequency(&Frequency);
	result = (unsigned __int64)(1000 * PerformanceCount.QuadPart) / Frequency.QuadPart;
	qword_C57FB0 = result;
	return result;
#endif
}

#if defined(PSXPC_VERSION)
unsigned long long TIMER_TimeDiff(long long x)
#else
unsigned long TIMER_TimeDiff(unsigned long x)
#endif
{
#if defined(PSXPC_VERSION)
	return Emulator_GetPerformanceCounter() / (Emulator_GetPerformanceFrequency() / 1000000) - x;

#elif defined(PSX_VERSION)
	unsigned long intrs;
	unsigned long ticks;
	unsigned long prevIntrs;
	unsigned long prevTicks;
	unsigned long diffIntrs;
	unsigned long diffTicks;
	unsigned long timeDiff;

	ticks = GetRCnt(0xF2000000) & 0xFFFF;
	prevIntrs = x >> 16;
	intrs = gameTimer & 0xFFFF;
	prevTicks = x & 0xFFFF;

	if (intrs < prevIntrs)
	{
		diffIntrs = (intrs + 65536) - prevIntrs;
	}
	else
	{
		diffIntrs = intrs - prevIntrs;
	}

	if (ticks < prevTicks)
	{
		diffTicks = (ticks + 65535) - prevTicks;
		diffIntrs--;
	}
	else
	{
		diffTicks = ticks - prevTicks;
	}

	if (diffIntrs >= 2259)
	{
		timeDiff = 4293263;
	}
	else
	{
		timeDiff = ((diffTicks * 29) + (diffIntrs * 1900515)) / 1000;
	}
	
	if (gTimerEnabled == 0)
	{
		timeDiff = 0;
	}

	return timeDiff;
#else
	unsigned __int16 RCnt; // ax
	unsigned int v2; // edx
	unsigned int v3; // ecx
	int v4; // eax
	unsigned int result; // eax

	RCnt = GetRCnt(0xF2000000);
	v2 = x >> 16;
	if (x <= (unsigned __int16)gameTimer)
		v3 = (unsigned __int16)gameTimer - v2;
	else
		v3 = (unsigned __int16)gameTimer - v2 + 65536;
	if ((unsigned __int16)x <= (unsigned int)RCnt)
	{
		v4 = RCnt - (unsigned __int16)x;
	}
	else
	{
		v4 = RCnt - (unsigned __int16)x + 65535;
		--v3;
	}
	if (v3 <= 2258)
		result = 29 * (v4 + 65535 * v3) / 1000;
	else
		result = 4293263;
	if (!gTimerEnabled)
		return 0;
	return result;
#endif
}

// pc exclusive, unused
#if defined(PC_VERSION)
void* __cdecl TIMER_TimeDiff2(unsigned int a1)
{

	unsigned __int16 RCnt; // ax
	unsigned int v3; // edx
	unsigned int v4; // ecx
	int v5; // eax

	if (!gTimerEnabled)
		return 0;
	RCnt = GetRCnt(0xF2000000);
	v3 = a1 >> 16;
	if (v3 <= (unsigned __int16)gameTimer)
		v4 = (unsigned __int16)gameTimer - v3;
	else
		v4 = (unsigned __int16)gameTimer - v3 + 65536;
	if ((unsigned __int16)a1 <= (unsigned int)RCnt)
	{
		v5 = RCnt - (unsigned __int16)a1;
	}
	else
	{
		v5 = RCnt - (unsigned __int16)a1 + 65535;
		--v4;
	}
	if (v4 <= 4516)
		return (void*)(14 * (v5 + 65535 * v4) / 1000);
	else
		return 4293263;
}
#endif
