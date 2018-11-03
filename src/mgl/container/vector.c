#include <mgl/container/vector.h>
#include <mgl/memory/manipulation.h>

typedef struct
{
	mgl_u64_t index;
	mgl_vector_t* vec;
} mgl_vector_iterator_t;

MGL_STATIC_ASSERT(sizeof(mgl_vector_iterator_t) <= MGL_ITERATOR_AVAILABLE_SIZE, "Vector iterator too big");

static mgl_error_t mgl_vector_iterator_next(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	out->functions = it->functions;
	
	if (((mgl_vector_iterator_t*)it->data)->index + 1 >= ((mgl_vector_iterator_t*)it->data)->vec->element_count)
	{
		((mgl_vector_iterator_t*)out->data)->index = ((mgl_vector_iterator_t*)it->data)->vec->element_count;
		((mgl_vector_iterator_t*)out->data)->vec = ((mgl_vector_iterator_t*)it->data)->vec;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_vector_iterator_t*)out->data)->index = ((mgl_vector_iterator_t*)it->data)->index + 1;
	((mgl_vector_iterator_t*)out->data)->vec = ((mgl_vector_iterator_t*)it->data)->vec;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_vector_iterator_prev(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	out->functions = it->functions;
	
	if (((mgl_vector_iterator_t*)it->data)->index == 0)
	{
		((mgl_vector_iterator_t*)out->data)->index = ((mgl_vector_iterator_t*)it->data)->vec->element_count;
		((mgl_vector_iterator_t*)out->data)->vec = ((mgl_vector_iterator_t*)it->data)->vec;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_vector_iterator_t*)out->data)->index = ((mgl_vector_iterator_t*)it->data)->index - 1;
	((mgl_vector_iterator_t*)out->data)->vec = ((mgl_vector_iterator_t*)it->data)->vec;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_vector_iterator_move(const mgl_iterator_t * it, mgl_iterator_t * out, mgl_i64_t move)
{
	out->functions = it->functions;
	
	if (move > 0)
	{
		if (((mgl_vector_iterator_t*)it->data)->index + (mgl_u64_t)move >= ((mgl_vector_iterator_t*)it->data)->vec->element_count)
		{
			((mgl_vector_iterator_t*)out->data)->index = ((mgl_vector_iterator_t*)it->data)->vec->element_count;
			((mgl_vector_iterator_t*)out->data)->vec = ((mgl_vector_iterator_t*)it->data)->vec;
			return MGL_ERROR_OUT_OF_BOUNDS;
		}
	}
	else
	{
		if (((mgl_vector_iterator_t*)it->data)->index < (mgl_u64_t)(-move))
		{
			((mgl_vector_iterator_t*)out->data)->index = ((mgl_vector_iterator_t*)it->data)->vec->element_count;
			((mgl_vector_iterator_t*)out->data)->vec = ((mgl_vector_iterator_t*)it->data)->vec;
			return MGL_ERROR_OUT_OF_BOUNDS;
		}
	}
	
	((mgl_vector_iterator_t*)out->data)->index = ((mgl_vector_iterator_t*)it->data)->index + move;
	((mgl_vector_iterator_t*)out->data)->vec = ((mgl_vector_iterator_t*)it->data)->vec;
	return MGL_ERROR_NONE;
}

static mgl_bool_t mgl_vector_iterator_is_null(const mgl_iterator_t * it)
{
	return ((mgl_vector_iterator_t*)it->data)->index >= ((mgl_vector_iterator_t*)it->data)->vec->element_count;
}

static void * mgl_vector_iterator_get(const mgl_iterator_t * it)
{
	MGL_ASSERT(!mgl_vector_iterator_is_null(it));
	return ((mgl_vector_iterator_t*)it->data)->vec->buffer + ((mgl_vector_iterator_t*)it->data)->index * ((mgl_vector_iterator_t*)it->data)->vec->element_size;
}

static void * mgl_vector_iterator_get_raw(const mgl_iterator_t * it)
{
	if (((mgl_vector_iterator_t*)it->data)->index >= ((mgl_vector_iterator_t*)it->data)->vec->element_count)
		return NULL;
	return ((mgl_vector_iterator_t*)it->data)->vec->buffer + ((mgl_vector_iterator_t*)it->data)->index * ((mgl_vector_iterator_t*)it->data)->vec->element_size;
}

static mgl_iterator_functions_t mgl_vector_iterator_functions =
{
	&mgl_vector_iterator_next,
	&mgl_vector_iterator_prev,
	&mgl_vector_iterator_move,
	&mgl_vector_iterator_is_null,
	&mgl_vector_iterator_get,
	&mgl_vector_iterator_get_raw,
};

mgl_error_t MGL_API mgl_init_vector(mgl_vector_t * vec, mgl_u64_t element_count, mgl_u64_t element_size, mgl_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(vec != NULL && element_size > 0 && allocator != NULL);

	vec->allocator = allocator;
	vec->element_count = element_count;
	vec->element_size = element_size;

	if (element_count > 0)
	{
		vec->internal_count = element_count;
		mgl_error_t e = mgl_allocate(allocator, element_size * vec->internal_count, &vec->buffer);
		if (e != MGL_ERROR_NONE)
			return e;
	}
	else
	{
		vec->internal_count = 1;
		mgl_error_t e = mgl_allocate(allocator, element_size * 1, &vec->buffer);
		if (e != MGL_ERROR_NONE)
			return e;
	}

	return MGL_ERROR_NONE;
}

void MGL_API mgl_terminate_vector(mgl_vector_t * vec)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	MGL_ASSERT(mgl_deallocate(vec->allocator, vec->buffer) != MGL_ERROR_NONE);
}

mgl_u64_t MGL_API mgl_get_vector_element_count(const mgl_vector_t * vec)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	return vec->element_count;
}

mgl_u64_t MGL_API mgl_get_vector_element_size(const mgl_vector_t * vec)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	return vec->element_size;
}

void MGL_API mgl_get_vector_begin_it(mgl_vector_t * vec, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(vec != NULL && it != NULL);
	it->functions = &mgl_vector_iterator_functions;
	((mgl_vector_iterator_t*)it->data)->vec = vec;
	((mgl_vector_iterator_t*)it->data)->index = 0;
}

void MGL_API mgl_get_vector_end_it(mgl_vector_t * vec, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(vec != NULL && it != NULL);
	it->functions = &mgl_vector_iterator_functions;
	((mgl_vector_iterator_t*)it->data)->vec = vec;
	((mgl_vector_iterator_t*)it->data)->index = vec->element_count - 1;
}

void MGL_API mgl_get_vector_element_it(mgl_vector_t * vec, mgl_u64_t index, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(vec != NULL && it != NULL);
	it->functions = &mgl_vector_iterator_functions;
	((mgl_vector_iterator_t*)it->data)->vec = vec;
	((mgl_vector_iterator_t*)it->data)->index = index;
}

void *MGL_API mgl_access_vector(mgl_vector_t * vec, mgl_u64_t index)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	MGL_ASSERT(index < vec->element_count);
	return vec->buffer + vec->element_size * index;
}

mgl_error_t MGL_API mgl_vector_push_end(mgl_vector_t * vec, const void * data, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(vec != NULL);

	if (vec->element_count >= vec->internal_count)
	{
		mgl_u64_t previous_count = vec->internal_count;
		vec->internal_count *= 2;
		mgl_error_t e = mgl_reallocate(vec->allocator, vec->buffer, previous_count * vec->element_size, vec->internal_count * vec->element_size, &vec->buffer);
		if (e != MGL_ERROR_NONE)
			return e;
	}

	if (data != NULL)
		mgl_mem_copy(vec->buffer + vec->element_count * vec->element_size, data, vec->element_size);
	if (out_ptr != NULL)
		*out_ptr = vec->buffer + vec->element_count * vec->element_size;
	++vec->element_count;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_vector_pop_end(mgl_vector_t * vec)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	MGL_ASSERT(vec->element_count != 0);
	--vec->element_count;
}

mgl_error_t MGL_API mgl_vector_push_begin(mgl_vector_t * vec, const void * data, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(vec != NULL);

	if (vec->element_count >= vec->internal_count)
	{
		mgl_u64_t previous_count = vec->internal_count;
		vec->internal_count *= 2;
		mgl_error_t e = mgl_reallocate(vec->allocator, vec->buffer, previous_count * vec->element_size, vec->internal_count * vec->element_size, &vec->buffer);
		if (e != MGL_ERROR_NONE)
			return e;
	}

	mgl_mem_copy(vec->buffer + vec->element_size, vec->buffer, vec->element_count * vec->element_size);

	if (data != NULL)
		mgl_mem_copy(vec->buffer, data, vec->element_size);
	if (out_ptr != NULL)
		*out_ptr = vec->buffer;
	++vec->element_count;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_vector_pop_begin(mgl_vector_t * vec)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	MGL_ASSERT(vec->element_count != 0);
	--vec->element_count;
	if (vec->element_count != 0)
		mgl_mem_copy(vec->buffer, vec->buffer + vec->element_size, vec->element_count * vec->element_size);
}

mgl_error_t MGL_API mgl_vector_resize(mgl_vector_t * vec, mgl_u64_t element_count)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	MGL_DEBUG_ASSERT(element_count < MGL_U64_MAX / 2);
	
	if (element_count > vec->internal_count)
	{
		mgl_u64_t previous_count = vec->internal_count;
		while (element_count > vec->internal_count)
			vec->internal_count *= 2;
		mgl_error_t e = mgl_reallocate(vec->allocator, vec->buffer, previous_count * vec->element_size, vec->internal_count * vec->element_size, &vec->buffer);
		if (e != MGL_ERROR_NONE)
			return e;
	}

	vec->element_count = element_count;
	return MGL_ERROR_NONE;
}

void MGL_API mgl_vector_clear(mgl_vector_t * vec)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	vec->element_count = 0;
}
