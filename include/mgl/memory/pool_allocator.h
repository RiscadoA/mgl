#ifndef MGL_MEMORY_POOL_ALLOCATOR_H
#define MGL_MEMORY_POOL_ALLOCATOR_H

#include <mgl/memory/allocator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_allocator_t base;
		mgl_u64_t slot_count;
		mgl_u64_t slot_size;
		mgl_bool_t* slot_status;
		void* slot_memory;
	} mgl_pool_allocator_t;

#define MGL_POOL_ALLOCATOR_SIZE(slot_count, slot_size) (sizeof(mgl_bool_t) * slot_count + slot_size * slot_count)

	/// <summary>
	///		Inits a pool allocator (no destructor call is needed).
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="slot_count">Slot count</param>
	/// <param name="slot_size">Slot size</param>
	/// <param name="memory">Memory to be used on the allocator</param>
	/// <param name="memory_size">Memory size (MGL_POOL_ALLOCATOR_SIZE)</param>
	void MGL_API mgl_init_pool_allocator(mgl_pool_allocator_t* allocator, mgl_u64_t slot_count, mgl_u64_t slot_size, void* memory, mgl_u64_t memory_size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_POOL_ALLOCATOR_H
