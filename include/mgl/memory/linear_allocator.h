#ifndef MGL_MEMORY_LINEAR_ALLOCATOR_H
#define MGL_MEMORY_LINEAR_ALLOCATOR_H

#include <mgl/memory/allocator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_allocator_t base;
		mgl_uptr_t begin, end, head;
	} mgl_linear_allocator_t;

	/// <summary>
	///		Inits a linear allocator (no destructor call is needed).
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="memory">Memory to be used on the allocator</param>
	/// <param name="memory_size">Memory size</param>
	void MGL_API mgl_init_linear_allocator(mgl_linear_allocator_t* allocator, void* memory, mgl_u64_t memory_size);

	/// <summary>
	///		Clears a linear allocator.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	void MGL_API mgl_clear_linear_allocator(mgl_linear_allocator_t* allocator);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_LINEAR_ALLOCATOR_H
