#include <mgl/container/vector.h>

typedef struct
{
	mgl_u64_t index;
	mgl_vector_t* vec;
} mgl_vector_iterator_t;

MGL_STATIC_ASSERT(sizeof(mgl_vector_iterator_t) <= MGL_ITERATOR_AVAILABLE_SIZE, "Vector iterator too big");

static mgl_error_t mgl_vector_iterator_next(const mgl_iterator_t * it, mgl_iterator_t * out)
{
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

void MGL_API mgl_get_vector_begin_it(mgl_vector_t * vec, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(vec != NULL && it != NULL);
	((mgl_vector_iterator_t*)it->data)->vec = vec;
	((mgl_vector_iterator_t*)it->data)->index = 0;
}

void MGL_API mgl_get_vector_end_it(mgl_vector_t * vec, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(vec != NULL && it != NULL);
	((mgl_vector_iterator_t*)it->data)->vec = vec;
	((mgl_vector_iterator_t*)it->data)->index = vec->element_count - 1;
}

void MGL_API mgl_get_vector_element_it(mgl_vector_t * vec, mgl_u64_t index, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(vec != NULL && it != NULL);
	((mgl_vector_iterator_t*)it->data)->vec = vec;
	((mgl_vector_iterator_t*)it->data)->index = index;
}

void *MGL_API mgl_access_vector(mgl_vector_t * vec, mgl_u64_t index)
{
	MGL_DEBUG_ASSERT(vec != NULL);
	MGL_ASSERT(index < vec->element_count);
}
