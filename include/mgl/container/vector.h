#ifndef MGL_CONTAINER_VECTOR_H
#define MGL_CONTAINER_VECTOR_H

#include <mgl/container/iterator.h>
#include <mgl/memory/allocator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Vector header.
	/// </summary>
	typedef struct
	{ 
		mgl_u64_t element_count;
		mgl_u64_t element_size;
		mgl_u64_t internal_count;
		mgl_allocator_t* allocator;
		mgl_u8_t* buffer;
	} mgl_vector_t;

	/// <summary>
	///		Initializes a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="element_count">Element count</param>
	/// <param name="element_size">Element size</param>
	/// <param name="allocator">Allocator</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_init_vector(mgl_vector_t* vec, mgl_u64_t element_count, mgl_u64_t element_size, mgl_allocator_t* allocator);

	/// <summary>
	///		Terminates a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	void MGL_API mgl_terminate_vector(mgl_vector_t* vec);

	/// <summary>
	///		Gets a vector's element count.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <returns>Vector's element count</returns>
	mgl_u64_t MGL_API mgl_get_vector_element_count(const mgl_vector_t* vec);

	/// <summary>
	///		Gets a vector's element size.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <returns>Vector's element size</returns>
	mgl_u64_t MGL_API mgl_get_vector_element_size(const mgl_vector_t* vec);

	/// <summary>
	///		Inits an iterator pointing to the first element of the vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_vector_begin_it(mgl_vector_t* vec, mgl_iterator_t* it);

	/// <summary>
	///		Inits an iterator pointing to the last element of the vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_vector_end_it(mgl_vector_t* vec, mgl_iterator_t* it);

	/// <summary>
	///		Inits an iterator pointing to an element at a specified index of the vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="index">Element index</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_vector_element_it(mgl_vector_t* vec, mgl_u64_t index, mgl_iterator_t* it);

	/// <summary>
	///		Accesses a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="index">Element index</param>
	/// <returns>Pointer to element</returns>
	void* MGL_API mgl_access_vector(mgl_vector_t* vec, mgl_u64_t index);

	/// <summary>
	///		Pushes an element to the end of a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <param name="out_ptr">Out pointer to new element</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_vector_push_end(mgl_vector_t* vec, const void* data, void** out_ptr);

	/// <summary>
	///		Pops an element from the end of a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	void MGL_API mgl_vector_pop_end(mgl_vector_t* vec);

	/// <summary>
	///		Pushes an element to the begin of a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <param name="out_ptr">Out pointer to new element</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_vector_push_begin(mgl_vector_t* vec, const void* data, void** out_ptr);

	/// <summary>
	///		Pops an element from the begin of a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	void MGL_API mgl_vector_pop_begin(mgl_vector_t* vec);

	/// <summary>
	///		Inserts an element on a vector after the element which the iterator points to.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="it">Iterator</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <returns>Pointer to new element</returns>
	void* MGL_API mgl_vector_insert_after(mgl_vector_t* vec, const mgl_iterator_t* it, const void* data);

	/// <summary>
	///		Inserts an element on a vector before the element which the iterator points to.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="it">Iterator</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <returns>Pointer to new element</returns>
	void* MGL_API mgl_vector_insert_before(mgl_vector_t* vec, const mgl_iterator_t* it, const void* data);

	/// <summary>
	///		Removes an element on a vector which the iterator points to.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="it">Iterator</param>
	void MGL_API mgl_vector_remove(mgl_vector_t* vec, const mgl_iterator_t* it);

	/// <summary>
	///		Resizes a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	/// <param name="element_count">New vector element count</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_vector_resize(mgl_vector_t* vec, mgl_u64_t element_count);

	/// <summary>
	///		Clears a vector.
	/// </summary>
	/// <param name="vec">Vector pointer</param>
	void MGL_API mgl_vector_clear(mgl_vector_t* vec);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_CONTAINER_VECTOR_H
