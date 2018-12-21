#include <mgl/thread/thread.h>

#ifdef __unix__
#include <errno.h>
#include <pthread.h>

typedef struct
{
	pthread_t thread;
	void(*function)(void *);
	void* argument;
	volatile mgl_bool_t running;
} mgl_posix_thread_t;

static void* mgl_posix_thread_func(void* arg)
{
	mgl_posix_thread_t* posix_thread = (mgl_posix_thread_t*)arg;
	posix_thread->running = MGL_TRUE;
	posix_thread->function(posix_thread->argument);
	posix_thread->running = MGL_FALSE;
	return NULL;
}

MGL_STATIC_ASSERT(sizeof(mgl_posix_thread_t) <= MGL_THREAD_SIZE, "MGL thread type too big");

mgl_error_t MGL_API mgl_create_thread(mgl_thread_t * thread, void(*function)(void *), void * argument)
{
	MGL_DEBUG_ASSERT(thread != NULL && function != NULL);
	mgl_posix_thread_t* posix_thread = (mgl_posix_thread_t*)thread->data;
	posix_thread->argument = argument;
	posix_thread->running = MGL_FALSE;
	posix_thread->function = function;

	int ret = pthread_create(&posix_thread->thread, NULL, &mgl_posix_thread_func, posix_thread);
	if (ret)
		return MGL_ERROR_EXTERNAL;

	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_destroy_thread(mgl_thread_t * thread)
{
	MGL_DEBUG_ASSERT(thread != NULL);
	mgl_posix_thread_t* posix_thread = (mgl_posix_thread_t*)thread->data;
	if (posix_thread->running != MGL_FALSE)
			return MGL_ERROR_THREAD_STILL_RUNNING;
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_wait_for_thread(mgl_thread_t * thread, mgl_u32_t timeout)
{
	MGL_DEBUG_ASSERT(thread != NULL);
	mgl_posix_thread_t* posix_thread = (mgl_posix_thread_t*)thread->data;
	if (timeout == 0)
	{
        int ret = pthread_join(posix_thread->thread, NULL);
        if (ret)
            return MGL_ERROR_EXTERNAL;
    }
    else
    {
        struct timespec t;
        t.tv_nsec = timeout * 1000;
        t.tv_sec = 0;
        int ret = pthread_timedjoin_np(posix_thread->thread, NULL, &t);
        if (ret == ETIMEDOUT)
            return MGL_ERROR_TIMEOUT;
        else if (ret)
            return MGL_ERROR_EXTERNAL;
    }
	return MGL_ERROR_NONE;
}

#endif // __unix__
