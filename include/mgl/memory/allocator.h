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

	extern mgl_allocator_t* mgl_standard_allocator;

	mgl_error_t mgl_allocate(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr);

	mgl_error_t mgl_reallocate(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr);

	mgl_error_t mgl_deallocate(mgl_allocator_t* allocator, void* ptr);
	
	mgl_error_t mgl_allocate_aligned(mgl_allocator_t* allocator, mgl_u64_t size, mgl_u64_t alignment, void** out_ptr);
	
	mgl_error_t mgl_deallocate_aligned(mgl_allocator_t* allocator, void* ptr);

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
