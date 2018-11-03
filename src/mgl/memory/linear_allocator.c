#include <mgl/memory/linear_allocator.h>
#include <mgl/memory/manipulation.h>

static mgl_error_t mgl_linear_allocator_allocate(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && out_ptr != NULL);
	
	mgl_linear_allocator_t* linear = (mgl_linear_allocator_t*)allocator;
	if (linear->head + size > linear->end)
		return MGL_ERROR_OVERFLOW;
	*out_ptr = (void*)linear->head;
	linear->head += size;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_linear_allocator_reallocate(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && ptr != NULL && out_ptr != NULL);
	
	mgl_linear_allocator_t* linear = (mgl_linear_allocator_t*)allocator;
	if (linear->head - prev_size == (mgl_uptr_t)ptr)
	{
		if (linear->head - prev_size < linear->begin)
			return MGL_ERROR_UNDERFLOW;
		if (linear->head - prev_size + new_size > linear->end)
			return MGL_ERROR_OVERFLOW;
		linear->head -= prev_size;
		linear->head += new_size;
		*out_ptr = ptr;
		return MGL_ERROR_NONE;
	}
	else
	{
		mgl_error_t e = mgl_linear_allocator_allocate(allocator, new_size, out_ptr);
		if (e != MGL_ERROR_NONE)
			return e;
		if (prev_size <= new_size)
			mgl_mem_copy(*out_ptr, ptr, prev_size);
		else
			mgl_mem_copy(*out_ptr, ptr, new_size);
		return MGL_ERROR_NONE;
	}
}

static mgl_error_t mgl_linear_allocator_deallocate(mgl_allocator_t* allocator, void* ptr)
{
	return MGL_ERROR_NONE; // Do nothing, memory on linear allocators is deallocated through mgl_clear_linear_allocator.
}

static mgl_allocator_functions_t mgl_linear_allocator_functions =
{
	&mgl_linear_allocator_allocate,
	&mgl_linear_allocator_reallocate,
	&mgl_linear_allocator_deallocate,
	NULL,
	NULL,
};

void MGL_API mgl_init_linear_allocator(mgl_linear_allocator_t * allocator, void * memory, mgl_u64_t memory_size)
{
	MGL_DEBUG_ASSERT(allocator != NULL && memory != NULL && memory_size != 0);

	allocator->base.functions = &mgl_linear_allocator_functions;
	allocator->begin = (mgl_uptr_t)memory;
	allocator->end = allocator->begin + memory_size;
	allocator->head = allocator->begin;
}

void MGL_API mgl_clear_linear_allocator(mgl_linear_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	allocator->head = allocator->begin;
}
