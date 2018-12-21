#ifndef MGL_MEMORY_ALLOCATOR_H
#define MGL_MEMORY_ALLOCATOR_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct mgl_allocator_t mgl_allocator_t;

	typedef struct
	{
		mgl_error_t(*allocate)(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr);
		mgl_error_t(*reallocate)(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr);
		mgl_error_t(*deallocate)(mgl_allocator_t* allocator, void* ptr);
		mgl_error_t(*allocate_aligned)(mgl_allocator_t* allocator, mgl_u64_t size, mgl_u64_t alignment, void** out_ptr);
		mgl_error_t(*deallocate_aligned)(mgl_allocator_t* allocator, void* ptr);
	} mgl_allocator_functions_t;

	struct mgl_allocator_t
	{
		mgl_allocator_functions_t* functions;
	};

	MGL_API extern mgl_allocator_t* mgl_standard_allocator;

	/// <summary>
	///		Allocates memory on an allocator.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="size">Allocation size</param>
	/// <param name="out_ptr">Out allocated pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_allocate(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr);

	/// <summary>
	///		Reallocates memory on an allocator.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="ptr">Previous memory pointer</param>
	/// <param name="prev_size">Previous allocation size</param>
	/// <param name="new_size">New allocation size</param>
	/// <param name="out_ptr">Out allocated pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_reallocate(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr);

	/// <summary>
	///		Deallocates memory allocated by mgl_allocate or mgl_reallocate.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="ptr">Memory pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_deallocate(mgl_allocator_t* allocator, void* ptr);

	/// <summary>
	///		Allocates aligned memory on an allocator.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="size">Allocation size</param>
	/// <param name="alignment">Allocation alignment</param>
	/// <param name="out_ptr">Out allocated pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_allocate_aligned(mgl_allocator_t* allocator, mgl_u64_t size, mgl_u64_t alignment, void** out_ptr);

	/// <summary>
	///		Deallocates aligned memory allocated by mgl_allocate_aligned.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="ptr">Memory pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_deallocate_aligned(mgl_allocator_t* allocator, void* ptr);

	/// <summary>
	///		Initializes the MGL allocators library.
	/// </summary>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_allocators_init(void);

	/// <summary>
	///		Terminates the MGL allocators library.
	/// </summary>
	void MGL_API mgl_allocators_terminate(void);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_ALLOCATOR_H
