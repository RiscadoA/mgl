#ifndef MGL_CONTAINER_ARRAY_H
#define MGL_CONTAINER_ARRAY_H

#include <mgl/container/iterator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Array header.
	/// </summary>
	typedef struct
	{ 
		mgl_u64_t element_count;
		mgl_u64_t element_size;
		mgl_u8_t* buffer;
	} mgl_array_t;

	/// <summary>
	///		Initializes an array.
	/// </summary>
	/// <param name="arr">Array pointer</param>
	/// <param name="element_count">Element count</param>
	/// <param name="element_size">Element size</param>
	/// <param name="buffer">Array buffer</param>
	void MGL_API mgl_init_array(mgl_array_t* arr, mgl_u64_t element_count, mgl_u64_t element_size, mgl_u8_t* buffer);

	/// <summary>
	///		Inits an iterator pointing to the first element of the array.
	/// </summary>
	/// <param name="arr">Array pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_array_begin_it(mgl_array_t* arr, mgl_iterator_t* it);

	/// <summary>
	///		Inits an iterator pointing to the last element of the array.
	/// </summary>
	/// <param name="arr">Array pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_array_end_it(mgl_array_t* arr, mgl_iterator_t* it);

	/// <summary>
	///		Inits an iterator pointing to an element at a specified index of the array.
	/// </summary>
	/// <param name="arr">Array pointer</param>
	/// <param name="index">Element index</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_array_element_it(mgl_array_t* arr, mgl_u64_t index, mgl_iterator_t* it);

	/// <summary>
	///		Accesses an array.
	/// </summary>
	/// <param name="arr">Array pointer</param>
	/// <param name="index">Element index</param>
	/// <returns>Pointer to element</returns>
	void* MGL_API mgl_access_array(mgl_array_t* arr, mgl_u64_t index);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_CONTAINER_ARRAY_H
