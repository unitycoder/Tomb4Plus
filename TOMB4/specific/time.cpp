#include "../tomb4/pch.h"
#include "../specific/time.h"	//there's some other time.h
#include "function_stubs.h"

#ifdef USE_SDL
#include <SDL.h>
static Uint64 counter, frequency;

long Sync()
{
	Uint64 PerformanceCount;
	long n;

	PerformanceCount = SDL_GetPerformanceCounter();
	Uint64 f = (PerformanceCount - counter) / frequency;
	counter += frequency * f;
	n = (long)f;
	return n;
}

void TIME_Reset()
{
	counter = SDL_GetPerformanceCounter();
}

bool TIME_Init()
{
	Log(2, "TIME_Init");

	Uint64 pfq = SDL_GetPerformanceFrequency();
	if (!pfq)
		return false;

	frequency = pfq / 60;
	TIME_Reset();
	return true;
}
#else
static __int64 counter, frequency;

long Sync()
{
	__int64 PerformanceCount, f;
	long n;

	QueryPerformanceCounter((LARGE_INTEGER*)&PerformanceCount);
	f = (PerformanceCount - counter) / frequency;
	counter += frequency * f;
	n = (long)f;
	return n;
}

void TIME_Reset()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
}

bool TIME_Init()
{
	__int64 pfq;

	Log(2, "TIME_Init");

	if (!QueryPerformanceFrequency((LARGE_INTEGER*)&pfq))
		return 0;

	frequency = pfq / 60;
	TIME_Reset();
	return 1;
}
#endif