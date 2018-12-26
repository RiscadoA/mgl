#include <mgl/memory/debug_allocator.h>
#include <mgl/memory/manipulation.h>

typedef struct
{
	void* ptr;
	mgl_u64_t size;
} mgl_debug_allocator_info_node_t;

static mgl_error_t mgl_debug_allocator_allocate(mgl_allocator_t* allocator, mgl_u64_t size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	mgl_error_t e = mgl_allocate(((mgl_debug_allocator_t*)allocator)->wrapped, size, out_ptr);
	if (e != MGL_ERROR_NONE)
		return e;

	((mgl_debug_allocator_t*)allocator)->allocated_count += 1;
	((mgl_debug_allocator_t*)allocator)->allocated_memory += size;

	mgl_debug_allocator_info_node_t node;
	node.ptr = *out_ptr;
	node.size = size;
	MGL_ASSERT(mgl_singly_linked_list_push_begin(&((mgl_debug_allocator_t*)allocator)->list, &node, NULL) == MGL_ERROR_NONE);

	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_debug_allocator_reallocate(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	mgl_error_t e = mgl_reallocate(((mgl_debug_allocator_t*)allocator)->wrapped, ptr, prev_size, new_size, out_ptr);
	if (e != MGL_ERROR_NONE)
		return e;

	((mgl_debug_allocator_t*)allocator)->allocated_memory -= prev_size;
	((mgl_debug_allocator_t*)allocator)->allocated_memory += new_size;

	mgl_iterator_t it;
	mgl_get_singly_linked_list_begin_it(&((mgl_debug_allocator_t*)allocator)->list, &it);
	while (!mgl_iterator_is_null(&it))
	{
		mgl_debug_allocator_info_node_t* node = (mgl_debug_allocator_info_node_t*)mgl_iterator_get(&it);
		if (node->ptr == ptr)
		{
			node->ptr = *out_ptr;
			node->size = new_size;
			break;
		}
		mgl_iterator_next(&it, &it);
	}

	return e;
}

static mgl_error_t mgl_debug_allocator_deallocate(mgl_allocator_t* allocator, void* ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	mgl_error_t e = mgl_deallocate(((mgl_debug_allocator_t*)allocator)->wrapped, ptr);
	if (e != MGL_ERROR_NONE)
		return e;

	((mgl_debug_allocator_t*)allocator)->allocated_count -= 1;

	mgl_iterator_t it;
	mgl_get_singly_linked_list_begin_it(&((mgl_debug_allocator_t*)allocator)->list, &it);
	while (!mgl_iterator_is_null(&it))
	{
		mgl_debug_allocator_info_node_t* node = (mgl_debug_allocator_info_node_t*)mgl_iterator_get(&it);
		if (node->ptr == ptr)
		{
			((mgl_debug_allocator_t*)allocator)->allocated_memory -= node->size;
			mgl_singly_linked_list_remove(&((mgl_debug_allocator_t*)allocator)->list, &it);
			break;
		}
		mgl_iterator_next(&it, &it);
	}

	return e;
}

static mgl_error_t mgl_debug_allocator_allocate_aligned(mgl_allocator_t* allocator, mgl_u64_t size, mgl_u64_t alignment, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	mgl_error_t e = mgl_allocate_aligned(((mgl_debug_allocator_t*)allocator)->wrapped, size, alignment, out_ptr);
	if (e != MGL_ERROR_NONE)
		return e;

	((mgl_debug_allocator_t*)allocator)->allocated_count += 1;
	((mgl_debug_allocator_t*)allocator)->allocated_memory += size;

	mgl_debug_allocator_info_node_t node;
	node.ptr = *out_ptr;
	node.size = size;
	MGL_ASSERT(mgl_singly_linked_list_push_begin(&((mgl_debug_allocator_t*)allocator)->list, &node, NULL) == MGL_ERROR_NONE);

	return e;
}

static mgl_error_t mgl_debug_allocator_reallocate_aligned(mgl_allocator_t* allocator, void* ptr, mgl_u64_t prev_size, mgl_u64_t new_size, mgl_u64_t alignment, void** out_ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	mgl_error_t e = mgl_reallocate_aligned(((mgl_debug_allocator_t*)allocator)->wrapped, ptr, prev_size, new_size, alignment, out_ptr);
	if (e != MGL_ERROR_NONE)
		return e;

	((mgl_debug_allocator_t*)allocator)->allocated_memory -= prev_size;
	((mgl_debug_allocator_t*)allocator)->allocated_memory += new_size;

	mgl_iterator_t it;
	mgl_get_singly_linked_list_begin_it(&((mgl_debug_allocator_t*)allocator)->list, &it);
	while (!mgl_iterator_is_null(&it))
	{
		mgl_debug_allocator_info_node_t* node = (mgl_debug_allocator_info_node_t*)mgl_iterator_get(&it);
		if (node->ptr == ptr)
		{
			node->ptr = *out_ptr;
			node->size = new_size;
			break;
		}
		mgl_iterator_next(&it, &it);
	}

	return e;
}

static mgl_error_t mgl_debug_allocator_deallocate_aligned(mgl_allocator_t* allocator, void* ptr)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	mgl_error_t e = mgl_deallocate_aligned(((mgl_debug_allocator_t*)allocator)->wrapped, ptr);
	if (e != MGL_ERROR_NONE)
		return e;

	((mgl_debug_allocator_t*)allocator)->allocated_count -= 1;

	mgl_iterator_t it;
	mgl_get_singly_linked_list_begin_it(&((mgl_debug_allocator_t*)allocator)->list, &it);
	while (!mgl_iterator_is_null(&it))
	{
		mgl_debug_allocator_info_node_t* node = (mgl_debug_allocator_info_node_t*)mgl_iterator_get(&it);
		if (node->ptr == ptr)
		{
			((mgl_debug_allocator_t*)allocator)->allocated_memory -= node->size;
			mgl_singly_linked_list_remove(&((mgl_debug_allocator_t*)allocator)->list, &it);
			break;
		}
		mgl_iterator_next(&it, &it);
	}

	return e;
}

static mgl_allocator_functions_t mgl_debug_allocator_functions =
{
	&mgl_debug_allocator_allocate,
	&mgl_debug_allocator_reallocate,
	&mgl_debug_allocator_deallocate,
	&mgl_debug_allocator_allocate_aligned,
	&mgl_debug_allocator_reallocate_aligned,
	&mgl_debug_allocator_deallocate_aligned,
};

void MGL_API mgl_init_debug_allocator(mgl_debug_allocator_t * allocator, mgl_allocator_t * wrapped)
{
	MGL_DEBUG_ASSERT(allocator != NULL && wrapped != NULL);

	allocator->base.functions = &mgl_debug_allocator_functions;
	allocator->wrapped = wrapped;
	allocator->allocated_memory = 0;
	allocator->allocated_count = 0;

	mgl_init_singly_linked_list(&allocator->list, sizeof(mgl_debug_allocator_info_node_t), mgl_standard_allocator);
}

mgl_allocator_t *MGL_API mgl_get_debug_allocator_wrapped(mgl_debug_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return allocator->wrapped;
}

mgl_u64_t MGL_API mgl_get_debug_allocator_allocated_memory(mgl_debug_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return allocator->allocated_memory;
}

mgl_u64_t MGL_API mgl_get_debug_allocator_allocation_count(mgl_debug_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	return allocator->allocated_count;
}
