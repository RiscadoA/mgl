#include <mgl/thread/mutex.h>

#ifdef __unix__
#include <pthread.h>
#include <errno.h>

typedef struct
{
	pthread_mutex_t mutex;
} mgl_posix_mutex_t;

MGL_STATIC_ASSERT(sizeof(mgl_posix_mutex_t) <= MGL_MUTEX_SIZE, "MGL mutex type too big");

mgl_error_t MGL_API mgl_create_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_posix_mutex_t* posix_mutex = (mgl_posix_mutex_t*)mutex->data;
	pthread_mutexattr_t attr;
	int ret = pthread_mutexattr_init(&attr);
	if (ret)
        return MGL_ERROR_EXTERNAL;
    ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    if (ret)
        return MGL_ERROR_EXTERNAL;
	ret = pthread_mutex_init(&posix_mutex->mutex, &attr);
	return ret ? MGL_ERROR_EXTERNAL : MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_destroy_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_posix_mutex_t* posix_mutex = (mgl_posix_mutex_t*)mutex->data;
	int ret = pthread_mutex_destroy(&posix_mutex->mutex);
	return ret ? MGL_ERROR_EXTERNAL : MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_lock_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_posix_mutex_t* posix_mutex = (mgl_posix_mutex_t*)mutex->data;
	int ret = pthread_mutex_lock(&posix_mutex->mutex);
	return ret ? MGL_ERROR_EXTERNAL : MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_try_lock_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_posix_mutex_t* posix_mutex = (mgl_posix_mutex_t*)mutex->data;
	int ret = pthread_mutex_trylock(&posix_mutex->mutex);
	if (ret == EBUSY)
		return MGL_ERROR_MUTEX_ALREADY_LOCKED;
	return ret ? MGL_ERROR_EXTERNAL : MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_unlock_mutex(mgl_mutex_t * mutex)
{
	MGL_DEBUG_ASSERT(mutex != NULL);
	mgl_posix_mutex_t* posix_mutex = (mgl_posix_mutex_t*)mutex->data;
	int ret = pthread_mutex_unlock(&posix_mutex->mutex);
	return ret ? MGL_ERROR_EXTERNAL : MGL_ERROR_NONE;
}

#endif // __unix__
