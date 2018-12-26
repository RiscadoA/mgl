#include <mgl/memory/pool_allocator.h>

static mgl_error_t mgl_pool_allocator_allocate(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && out_ptr != NULL);
	
	mgl_pool_allocator_t* pool = (mgl_pool_allocator_t*)allocator;
	if (size > pool->slot_size)
		return MGL_ERROR_TOO_BIG;

	for (mgl_u64_t i = 0; i < pool->slot_count; ++i)
		if (pool->slot_status[i] != MGL_FALSE)
		{
			*out_ptr = (void*)((mgl_uptr_t)pool->slot_memory + i * pool->slot_size);
			pool->slot_status[i] = MGL_FALSE;
			return MGL_ERROR_NONE;
		}

	return MGL_ERROR_OVERFLOW;
}

static mgl_error_t mgl_pool_allocator_reallocate(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && ptr != NULL && out_ptr != NULL);

	mgl_pool_allocator_t* pool = (mgl_pool_allocator_t*)allocator;
	if (new_size > pool->slot_size)
		return MGL_ERROR_TOO_BIG;
	*out_ptr = ptr; // Do not change anything

	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_pool_allocator_deallocate(mgl_allocator_t* allocator, void* ptr)
{
	mgl_pool_allocator_t* pool = (mgl_pool_allocator_t*)allocator;

	if (ptr < pool->slot_memory)
		return MGL_ERROR_OUT_OF_BOUNDS;
	mgl_u64_t i = ((mgl_uptr_t)ptr - (mgl_uptr_t)pool->slot_memory) / pool->slot_size;
	if (i > pool->slot_count)
		return MGL_ERROR_OUT_OF_BOUNDS;
	pool->slot_status[i] = MGL_TRUE;
	return MGL_ERROR_NONE;
}

static mgl_allocator_functions_t mgl_pool_allocator_functions =
{
	&mgl_pool_allocator_allocate,
	&mgl_pool_allocator_reallocate,
	&mgl_pool_allocator_deallocate,
	NULL,
	NULL,
	NULL,
};

void MGL_API mgl_init_pool_allocator(mgl_pool_allocator_t * allocator, mgl_u64_t slot_count, mgl_u64_t slot_size, void * memory, mgl_u64_t memory_size)
{
	MGL_DEBUG_ASSERT(allocator != NULL && memory != NULL && memory_size != 0);
	MGL_ASSERT(memory_size >= MGL_POOL_ALLOCATOR_SIZE(slot_count, slot_size));

	allocator->base.functions = &mgl_pool_allocator_functions;
	allocator->slot_count = slot_count;
	allocator->slot_size = slot_size;
	allocator->slot_memory = memory;
	allocator->slot_status = (mgl_bool_t*)((mgl_uptr_t)memory + slot_size * slot_count);
	
	for (mgl_u64_t i = 0; i < slot_count; ++i)
		allocator->slot_status[i] = MGL_TRUE;
}
