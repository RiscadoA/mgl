#ifndef MGL_THREAD_THREAD_H
#define MGL_THREAD_THREAD_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_THREAD_SIZE 32

	/// <summary>
	///		Contains information about a thread.
	///		Do not access members directly.
	/// </summary>
	typedef struct { mgl_u8_t data[MGL_THREAD_SIZE]; } mgl_thread_t;

	/// <summary>
	///		Creates a new thread.
	/// </summary>
	/// <param name="thread">Pointer to thread object</param>
	/// <param name="function">Function to be called by the thread</param>
	/// <param name="argument">Argument to send to the function called by the thread</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_create_thread(mgl_thread_t* thread, void(*function)(void*), void* argument);

	/// <summary>
	///		Destroys a thread.
	/// </summary>
	/// <param name="thread">Pointer to thread object previously created with mgl_create_thread</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_destroy_thread(mgl_thread_t* thread);

	/// <summary>
	///		Waits for a thread work to finish.
	/// </summary>
	/// <param name="thread">Pointer to thread object</param>
	/// <param name="timeout">Wait timeout in milliseconds (set to 0 to disable timeout)</param>
	/// <returns>MGL_ERROR_NONE if everything went fine. MGL_ERROR_TIMEOUT if timeout was reached. Otherwise, an error code</returns>
	mgl_error_t MGL_API mgl_wait_for_thread(mgl_thread_t* thread, mgl_u32_t timeout);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_THREAD_THREAD_H
