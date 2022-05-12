#include "CORE.H"
#include "TIMER.H"

long gameTimer; // 0x800CE188
#ifdef PC_VERSION
LARGE_INTEGER PerformanceCount,
	Frequency;
#endif
// autogenerated function stub: 
// unsigned long /*$ra*/ TIMER_GetTimeMS()
unsigned long TIMER_GetTimeMS()
{ // line 41, offset 0x8003d7b0
#if defined(PSX_VERSION)
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


// autogenerated function stub: 
// unsigned long /*$ra*/ TIMER_TimeDiff(unsigned long x /*$s0*/)
unsigned long TIMER_TimeDiff(unsigned long x)
{ // line 72, offset 0x8003d840
#if defined(PSX_VERSION)
#if 0
	uint ticks;
	uint prevIntrs;
	uint timeDiff;
	ulong res;
	uint prevTicks;
	int diffTicks;

	ticks = GetRCnt(0xf2000000);
	ticks = ticks & 0xffff;
	timeDiff = x >> 0x10;
	prevIntrs = gameTimer & 0xffff;
	prevTicks = x & 0xffff;
	if (prevIntrs < timeDiff) {
		timeDiff = (prevIntrs + 0x10000) - timeDiff;
	}
	else {
		timeDiff = prevIntrs - timeDiff;
	}
	if (ticks < prevTicks) {
		diffTicks = (ticks + 0xffff) - prevTicks;
		timeDiff = timeDiff - 1;
	}
	else {
		diffTicks = ticks - prevTicks;
	}
	if (timeDiff < 2259) {
		res = ((diffTicks * 29 + timeDiff * 1900515) / 1000);
	}
	else {
		res = 4293263;
	}
	if (gTimerEnabled == 0) {
		res = 0x0;
	}
	return (ulong)res;
#endif
	return 0;
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
void* __cdecl TIMER_TimeDiff2(unsigned int a1)
{
#if defined(PC_VERSION)
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
#else
	return 0;
#endif
}