#include <mgl/time/sleep.h>

#ifdef MGL_SYSTEM_WINDOWS
#include <Windows.h>

void MGL_API mgl_sleep(mgl_time_t time)
{
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	timeBeginPeriod(tc.wPeriodMin);
	Sleep(mgl_to_milliseconds(time));
	timeEndPeriod(tc.wPeriodMin);
}

#endif