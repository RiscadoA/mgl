#include <mgl/time/clock.h>
#include <mgl/error.h>

#ifdef MGL_SYSTEM_WINDOWS

#include <Windows.h>

typedef struct
{
	mgl_time_t start_time;
	mgl_time_t end_time;
} mgl_windows_clock_t;

MGL_STATIC_ASSERT(sizeof(mgl_windows_clock_t) <= MGL_MAX_CLOCK_DATA_SIZE, "Clock struct too big");

static mgl_time_t get_time(void)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return mgl_from_microseconds(1000000 * time.QuadPart / frequency.QuadPart);
}

void MGL_API mgl_clock_start(mgl_clock_t * clock)
{
	MGL_DEBUG_ASSERT(clock != NULL);
	((mgl_windows_clock_t*)clock->data)->start_time = get_time();
	((mgl_windows_clock_t*)clock->data)->end_time = MGL_U64_MAX;
}

void MGL_API mgl_clock_pause(mgl_clock_t * clock)
{
	MGL_DEBUG_ASSERT(clock != NULL);
	((mgl_windows_clock_t*)clock->data)->end_time = get_time();
}

void MGL_API mgl_clock_resume(mgl_clock_t * clock)
{
	MGL_DEBUG_ASSERT(clock != NULL);
	((mgl_windows_clock_t*)clock->data)->start_time += get_time() - ((mgl_windows_clock_t*)clock->data)->end_time;
	((mgl_windows_clock_t*)clock->data)->end_time = MGL_U64_MAX;
}

mgl_time_t MGL_API mgl_clock_get_elapsed_time(mgl_clock_t * clock)
{
	MGL_DEBUG_ASSERT(clock != NULL);
	if (((mgl_windows_clock_t*)clock->data)->end_time == MGL_U64_MAX)
		return get_time() - ((mgl_windows_clock_t*)clock->data)->start_time;
	return ((mgl_windows_clock_t*)clock->data)->end_time - ((mgl_windows_clock_t*)clock->data)->start_time;
}
#endif