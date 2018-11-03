#ifndef MGL_MEMORY_DEBUG_ALLOCATOR_H
#define MGL_MEMORY_DEBUG_ALLOCATOR_H

#include <mgl/memory/allocator.h>
#include <mgl/container/singly_linked_list.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_allocator_t base;
		mgl_allocator_t* wrapped;
		mgl_singly_linked_list_t list;
		mgl_u64_t allocated_memory;
		mgl_u64_t allocated_count;
	} mgl_debug_allocator_t;

	/// <summary>
	///		Inits a debug allocator wrapper.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="wrapped">Allocator to wrap</param>
	void MGL_API mgl_init_debug_allocator(mgl_debug_allocator_t* allocator, mgl_allocator_t* wrapped);

	/// <summary>
	///		Gets the wrapped allocator on this debug allocator.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <returns>Wrapped allocator</returns>
	mgl_allocator_t* MGL_API mgl_get_debug_allocator_wrapped(mgl_debug_allocator_t* allocator);

	/// <summary>
	///		Gets the number of bytes currently allocated on this allocator.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <returns>Size in bytes</returns>
	mgl_u64_t MGL_API mgl_get_debug_allocator_allocated_memory(mgl_debug_allocator_t* allocator);

	/// <summary>
	///		Gets the of current allocations on this allocator.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <returns>Count</returns>
	mgl_u64_t MGL_API mgl_get_debug_allocator_allocation_count(mgl_debug_allocator_t* allocator);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_DEBUG_ALLOCATOR_H
