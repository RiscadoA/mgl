#ifndef MGL_THREAD_MUTEX_H
#define MGL_THREAD_MUTEX_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_MUTEX_SIZE 64

	/// <summary>
	///		Contains information about a mutex.
	///		Do not access members directly.
	/// </summary>
	typedef struct { mgl_u8_t data[MGL_MUTEX_SIZE]; } mgl_mutex_t;

	/// <summary>
	///		Creates a new mutex.
	/// </summary>
	/// <param name="mutex">Pointer to mutex object</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_create_mutex(mgl_mutex_t* mutex);

	/// <summary>
	///		Destroys a mutex.
	/// </summary>
	/// <param name="mutex">Pointer to mutex object previously created with mgl_create_mutex</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_destroy_mutex(mgl_mutex_t* mutex);

	/// <summary>
	///		Locks a mutex.
	/// </summary>
	/// <param name="mutex">Pointer to mutex object</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_lock_mutex(mgl_mutex_t* mutex);

	/// <summary>
	///		Tries to locks a mutex without waiting it to be unlocked.
	/// </summary>
	/// <param name="mutex">Pointer to mutex object</param>
	/// <returns>MGL_ERROR_NONE if everything went fine. MGL_ERROR_MUTEX_ALREADY_LOCKED if the mutex was already locked</returns>
	mgl_error_t MGL_API mgl_try_lock_mutex(mgl_mutex_t* mutex);

	/// <summary>
	///		Unlocks a mutex.
	/// </summary>
	/// <param name="mutex">Pointer to mutex object</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_unlock_mutex(mgl_mutex_t* mutex);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_THREAD_MUTEX_H
