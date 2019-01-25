#include <mgl/memory/allocator.h>
#include <malloc.h>

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
	NULL,
	NULL,
};

static mgl_allocator_t mgl_standard_allocator_s = { &mgl_standard_allocator_functions };
MGL_API mgl_allocator_t* mgl_standard_allocator = &mgl_standard_allocator_s;

mgl_error_t MGL_API mgl_allocate(void * allocator, mgl_u64_t size, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return ((mgl_allocator_t*)allocator)->functions->allocate(allocator, size, out_ptr);
}

mgl_error_t MGL_API mgl_reallocate(void * allocator, void * ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	if (ptr == NULL)
		return mgl_allocate(((mgl_allocator_t*)allocator), new_size, out_ptr);
	return ((mgl_allocator_t*)allocator)->functions->reallocate(((mgl_allocator_t*)allocator), ptr, prev_size, new_size, out_ptr);
}

mgl_error_t MGL_API mgl_deallocate(void * allocator, void * ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return ((mgl_allocator_t*)allocator)->functions->deallocate(allocator, ptr);
}

mgl_error_t MGL_API mgl_allocate_aligned(void * allocator, mgl_u64_t size, mgl_u64_t alignment, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	if (((mgl_allocator_t*)allocator)->functions->allocate_aligned == NULL)
	{
		MGL_DEBUG_ASSERT((alignment & (alignment - 1)) == 0);
		mgl_u64_t needed_size = size + alignment;
		void* raw_ptr = NULL;
		mgl_error_t err = ((mgl_allocator_t*)allocator)->functions->allocate(((mgl_allocator_t*)allocator), needed_size, &raw_ptr);
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
	else return ((mgl_allocator_t*)allocator)->functions->allocate_aligned(((mgl_allocator_t*)allocator), size, alignment, out_ptr);
}

mgl_error_t MGL_API mgl_reallocate_aligned(void * allocator, void * ptr, mgl_u64_t prev_size, mgl_u64_t new_size, mgl_u64_t alignment, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	if (((mgl_allocator_t*)allocator)->functions->reallocate_aligned == NULL)
	{
		MGL_DEBUG_ASSERT((alignment & (alignment - 1)) == 0);
		mgl_u64_t needed_size = new_size + alignment;
		void* raw_ptr = (void*)((mgl_uptr_t)ptr - ((mgl_u8_t*)ptr)[-1]);
		mgl_error_t err = ((mgl_allocator_t*)allocator)->functions->reallocate(((mgl_allocator_t*)allocator), raw_ptr, prev_size + alignment, needed_size, &raw_ptr);
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
	else return ((mgl_allocator_t*)allocator)->functions->reallocate_aligned(((mgl_allocator_t*)allocator), ptr, prev_size, new_size, alignment, out_ptr);
}

mgl_error_t MGL_API mgl_deallocate_aligned(void * allocator, void * ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL && ptr != NULL);
	if (((mgl_allocator_t*)allocator)->functions->deallocate_aligned == NULL)
	{
		void* raw_mem = (void*)((mgl_uptr_t)ptr - ((mgl_u8_t*)ptr)[-1]);
		return ((mgl_allocator_t*)allocator)->functions->deallocate(((mgl_allocator_t*)allocator), raw_mem);
	}
	else return ((mgl_allocator_t*)allocator)->functions->deallocate_aligned(((mgl_allocator_t*)allocator), ptr);
}

