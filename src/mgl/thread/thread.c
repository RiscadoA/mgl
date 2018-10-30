#include <mgl/thread/thread.h>

#ifdef _WIN32
#include <Windows.h>
#include <process.h>

typedef struct
{
	HANDLE handle;
	void* argument;
	void (*function)(void*);
	unsigned int id;
	volatile mgl_bool_t running;
} mgl_win32_thread_t;

MGL_STATIC_ASSERT(sizeof(mgl_win32_thread_t) <= MGL_THREAD_SIZE, "MGL thread type too big");

static unsigned int mgl_win32_thread_func(void* arg)
{
	mgl_win32_thread_t* thread = (mgl_win32_thread_t*)arg;
	thread->running = MGL_TRUE;
	thread->function(thread->argument);
	thread->running = MGL_FALSE;
	return 0;
}

#endif // _WIN32

mgl_error_t MGL_API mgl_create_thread(mgl_thread_t * thread, void(*function)(void *), void * argument)
{
#ifdef _WIN32
	MGL_DEBUG_ASSERT(thread != NULL && function != NULL);	
	mgl_win32_thread_t* win32_thread = (mgl_win32_thread_t*)thread->data;
	win32_thread->argument = argument;
	win32_thread->function = function;
	win32_thread->running = MGL_FALSE;
	win32_thread->handle = (HANDLE)_beginthreadex(NULL, 0, &mgl_win32_thread_func, win32_thread, 0, &win32_thread->id);
	if (win32_thread->handle == NULL)
		return MGL_ERROR_EXTERNAL;
	return MGL_ERROR_NONE;
#else // _WIN32
#	error Unsupported platform (mgl_create_thread)
#endif // _WIN32
}

mgl_error_t MGL_API mgl_destroy_thread(mgl_thread_t * thread)
{
#ifdef _WIN32
	MGL_DEBUG_ASSERT(thread != NULL);
	mgl_win32_thread_t* win32_thread = (mgl_win32_thread_t*)thread->data;
	if (win32_thread->running != MGL_FALSE)
		return MGL_ERROR_THREAD_STILL_RUNNING;
	if (CloseHandle(win32_thread->handle) == FALSE)
		return MGL_ERROR_EXTERNAL;
	return MGL_ERROR_NONE;
#else // _WIN32
#	error Unsupported platform (mgl_destroy_thread)
#endif // _WIN32
}

mgl_error_t MGL_API mgl_wait_for_thread(mgl_thread_t * thread, mgl_u32_t timeout)
{
#ifdef _WIN32
	mgl_win32_thread_t* win32_thread = (mgl_win32_thread_t*)thread->data;
	DWORD ret;
	if (timeout == 0)
		ret = WaitForSingleObject(win32_thread->handle, INFINITE);
	else
		ret = WaitForSingleObject(win32_thread->handle, timeout);
	if (ret == WAIT_TIMEOUT)
		return MGL_ERROR_TIMEOUT;
	else if (ret == WAIT_FAILED)
		return MGL_ERROR_EXTERNAL;
	else
		return MGL_ERROR_NONE;
#else // _WIN32
#	error Unsupported platform (mgl_wait_for_thread)
#endif // _WIN32
}
