#include <mgl/thread/mutex.h>

#ifdef _WIN32
#include <Windows.h>
#include <process.h>

typedef struct
{
	CRITICAL_SECTION critical_section;
} mgl_win32_mutex_t;

MGL_STATIC_ASSERT(sizeof(mgl_win32_mutex_t) <= MGL_MUTEX_SIZE, "MGL mutex type too big");

mgl_error_t MGL_API mgl_create_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_win32_mutex_t* win32_mutex = (mgl_win32_mutex_t*)mutex->data;
	InitializeCriticalSection(&win32_mutex->critical_section);
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_destroy_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_win32_mutex_t* win32_mutex = (mgl_win32_mutex_t*)mutex->data;
	DeleteCriticalSection(&win32_mutex->critical_section);
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_lock_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_win32_mutex_t* win32_mutex = (mgl_win32_mutex_t*)mutex->data;
	EnterCriticalSection(&win32_mutex->critical_section);
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_try_lock_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_win32_mutex_t* win32_mutex = (mgl_win32_mutex_t*)mutex->data;
	if (!TryEnterCriticalSection(&win32_mutex->critical_section))
		return MGL_ERROR_MUTEX_ALREADY_LOCKED;
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_unlock_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_win32_mutex_t* win32_mutex = (mgl_win32_mutex_t*)mutex->data;
	LeaveCriticalSection(&win32_mutex->critical_section);
	return MGL_ERROR_NONE;
}

#endif // _WIN32
