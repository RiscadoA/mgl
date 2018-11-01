#ifndef MGL_CONTAINER_ITERATOR_H
#define MGL_CONTAINER_ITERATOR_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_ITERATOR_AVAILABLE_SIZE 8

	typedef struct mgl_iterator_functions_t mgl_iterator_functions_t;

	struct mgl_iterator_functions_t
	{
		mgl_error_t(*next)(const mgl_iterator_t* it, mgl_iterator_t* out);
		mgl_error_t(*prev)(const mgl_iterator_t* it, mgl_iterator_t* out);
		mgl_error_t(*move)(const mgl_iterator_t* it, mgl_iterator_t* out, mgl_i64_t move);
		mgl_bool_t(*is_null)(const mgl_iterator_t* it);
		void*(*get)(const mgl_iterator_t* it);
		void*(*get_raw)(const mgl_iterator_t* it);
	};

	/// <summary>
	///		Contains information about a thread.
	///		Do not access members directly.
	/// </summary>
	typedef struct { mgl_iterator_functions_t* functions; mgl_u8_t data[MGL_ITERATOR_AVAILABLE_SIZE]; } mgl_iterator_t;

	/// <summary>
	///		Moves an iterator to next element.
	/// </summary>
	/// <param name="it">Iterator</param>
	/// <param name="out">New iterator</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_iterator_next(const mgl_iterator_t* it, mgl_iterator_t* out);

	/// <summary>
	///		Moves an iterator to previous element.
	/// </summary>
	/// <param name="it">Iterator</param>
	/// <param name="out">New iterator</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_iterator_prev(const mgl_iterator_t* it, mgl_iterator_t* out);

	/// <summary>
	///		Moves an iterator.
	/// </summary>
	/// <param name="it">Iterator</param>
	/// <param name="out">New iterator</param>
	/// <param name="move">Movement</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_iterator_move(const mgl_iterator_t* it, mgl_iterator_t* out, mgl_i64_t move);

	/// <summary>
	///		Checks if an iterator points to NULL.
	/// </summary>
	/// <param name="it">Iterator</param>
	/// <returns>MGL_TRUE or MGL_FALSE</returns>
	mgl_bool_t MGL_API mgl_iterator_is_null(const mgl_iterator_t* it);

	/// <summary>
	///		Gets the pointer to value which the iterator is currently on.
	///		Guaranteed to not be NULL.
	/// </summary>
	/// <param name="it">Iterator</param>
	/// <returns>Pointer</returns>
	void* MGL_API mgl_iterator_get(const mgl_iterator_t* it);

	/// <summary>
	///		Gets the raw pointer to value which the iterator is currently on.
	///		Can be NULL.
	/// </summary>
	/// <param name="it">Iterator</param>
	/// <returns>Pointer</returns>
	void* MGL_API mgl_iterator_get_raw(const mgl_iterator_t* it);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_CONTAINER_ITERATOR_H
