#ifndef MGL_MEMORY_STACK_ALLOCATOR_H
#define MGL_MEMORY_STACK_ALLOCATOR_H

#include <mgl/memory/allocator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_allocator_t base;
		mgl_uptr_t begin, end, head;
	} mgl_stack_allocator_t;

	/// <summary>
	///		Inits a stack allocator (no destructor call is needed).
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="memory">Memory to be used on the allocator</param>
	/// <param name="memory_size">Memory size</param>
	void MGL_API mgl_init_stack_allocator(mgl_stack_allocator_t* allocator, void* memory, mgl_u64_t memory_size);

	/// <summary>
	///		Gets a stack allocators' head.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <returns>Stack allocator's head</returns>
	mgl_uptr_t MGL_API mgl_get_stack_allocator_head(mgl_stack_allocator_t* allocator);

	/// <summary>
	///		Sets a stack allocators' head.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="head">Stack allocator's head</param>
	void MGL_API mgl_set_stack_allocator_head(mgl_stack_allocator_t* allocator, mgl_uptr_t head);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_STACK_ALLOCATOR_H
