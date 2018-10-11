#include <mgl/memory/stack_allocator.h>

static mgl_error_t mgl_stack_allocator_allocate(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && out_ptr != NULL);
	
	mgl_stack_allocator_t* stack = (mgl_stack_allocator_t*)allocator;
	if (stack->head + size > stack->end)
		return MGL_ERROR_OVERFLOW;
	*out_ptr = (void*)stack->head;
	stack->head += size;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_stack_allocator_reallocate(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && ptr != NULL && out_ptr != NULL);
	
	mgl_stack_allocator_t* stack = (mgl_stack_allocator_t*)allocator;
	if (stack->head - prev_size == (mgl_uptr_t)ptr)
	{
		if (stack->head - prev_size < stack->begin)
			return MGL_ERROR_UNDERFLOW;
		if (stack->head - prev_size + new_size > stack->end)
			return MGL_ERROR_OVERFLOW;
		stack->head -= prev_size;
		stack->head += new_size;
		*out_ptr = ptr;
		return MGL_ERROR_NONE;
	}
	else return mgl_stack_allocator_allocate(allocator, new_size, out_ptr);
}

static mgl_error_t mgl_stack_allocator_deallocate(mgl_allocator_t* allocator, void* ptr)
{
	return MGL_ERROR_NONE; // Do nothing, memory on stack allocators is deallocated through mgl_set_stack_allocator_head.
}

static mgl_allocator_functions_t mgl_stack_allocator_functions =
{
	&mgl_stack_allocator_allocate,
	&mgl_stack_allocator_reallocate,
	&mgl_stack_allocator_deallocate,
	NULL,
	NULL,
};

void mgl_init_stack_allocator(mgl_stack_allocator_t * allocator, void * memory, mgl_u64_t memory_size)
{
	MGL_DEBUG_ASSERT(allocator != NULL && memory != NULL && memory_size != 0);

	allocator->base.functions = &mgl_stack_allocator_functions;
	allocator->begin = (mgl_uptr_t)memory;
	allocator->end = allocator->begin + memory_size;
	allocator->head = allocator->begin;
}

mgl_uptr_t mgl_get_stack_allocator_head(mgl_stack_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return allocator->head;
}

void mgl_set_stack_allocator_head(mgl_stack_allocator_t * allocator, mgl_uptr_t head)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	MGL_ASSERT(head >= allocator->begin && head <= allocator->end);
	allocator->head = head;
}
