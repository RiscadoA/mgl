#include <mgl/memory/allocator.h>
#include <malloc.h>

mgl_allocator_t* mgl_standard_allocator = NULL;
static mgl_allocator_t mgl_standard_allocator_s;

static mgl_error_t mgl_standard_allocator_allocate(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && out_ptr != NULL);
	*out_ptr = malloc(size);
	if (*out_ptr == NULL)
		return MGL_ERROR_EXTERNAL;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_standard_allocator_reallocate(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && ptr != NULL && out_ptr != NULL);
	*out_ptr = realloc(ptr, new_size);
	if (*out_ptr == NULL)
		return MGL_ERROR_EXTERNAL;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_standard_allocator_deallocate(mgl_allocator_t* allocator, void* ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && ptr != NULL);
	free(ptr);
	return MGL_ERROR_NONE;
}

mgl_allocator_functions_t mgl_standard_allocator_functions =
{
	&mgl_standard_allocator_allocate,
	&mgl_standard_allocator_reallocate,
	&mgl_standard_allocator_deallocate,
	NULL,
	NULL
};

mgl_error_t mgl_allocate(mgl_allocator_t * allocator, mgl_u64_t size, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return allocator->functions->allocate(allocator, size, out_ptr);
}

mgl_error_t mgl_reallocate(mgl_allocator_t * allocator, void * ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	if (ptr == NULL)
		return mgl_allocate(allocator, new_size, out_ptr);
	return allocator->functions->reallocate(allocator, ptr, prev_size, new_size, out_ptr);
}

mgl_error_t mgl_deallocate(mgl_allocator_t * allocator, void * ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return allocator->functions->deallocate(allocator, ptr);
}

mgl_error_t mgl_allocate_aligned(mgl_allocator_t * allocator, mgl_u64_t size, mgl_u64_t alignment, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	if (allocator->functions->allocate_aligned == NULL)
	{
		MGL_DEBUG_ASSERT((alignment & (alignment - 1)) == 0);
		mgl_u64_t needed_size = size + alignment;
		void* raw_ptr = NULL;
		mgl_error_t err = allocator->functions->allocate(allocator, needed_size, &raw_ptr);
		if (err != MGL_ERROR_NONE)
			return err;
		mgl_uptr_t adjustment = alignment - ((mgl_uptr_t)raw_ptr & (alignment - 1));
		mgl_uptr_t aligned_address = (mgl_uptr_t)raw_ptr + adjustment;

		MGL_DEBUG_ASSERT(adjustment <= MGL_U8_MAX);
		mgl_u8_t* aligned_mem = (mgl_u8_t*)aligned_address;
		aligned_mem[-1] = (mgl_u8_t)adjustment;
		*out_ptr = aligned_mem;
		return MGL_ERROR_NONE;
	}
	else return allocator->functions->allocate_aligned(allocator, size, alignment, out_ptr);
}

mgl_error_t mgl_deallocate_aligned(mgl_allocator_t * allocator, void * ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && ptr != NULL);
	if (allocator->functions->deallocate_aligned == NULL)
	{
		void* raw_mem = (void*)((mgl_uptr_t)ptr - ((mgl_u8_t*)ptr)[-1]);
		return allocator->functions->deallocate(allocator, raw_mem);
	}
	else return allocator->functions->deallocate_aligned(allocator, ptr);
}

mgl_error_t MGL_API mgl_allocators_init(void)
{
	mgl_standard_allocator_s.functions = &mgl_standard_allocator_functions;
	mgl_standard_allocator = &mgl_standard_allocator_s;
	return MGL_ERROR_NONE;
}

void MGL_API mgl_allocators_terminate(void)
{
	mgl_standard_allocator_s.functions = NULL;
	mgl_standard_allocator = NULL;
}
