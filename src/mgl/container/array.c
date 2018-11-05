#include <mgl/container/array.h>

typedef struct
{
	mgl_u64_t index;
	mgl_array_t* arr;
} mgl_array_iterator_t;

MGL_STATIC_ASSERT(sizeof(mgl_array_iterator_t) <= MGL_ITERATOR_AVAILABLE_SIZE, "Array iterator too big");

static mgl_error_t mgl_array_iterator_next(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	out->functions = it->functions;
	
	if (((mgl_array_iterator_t*)it->data)->index + 1 >= ((mgl_array_iterator_t*)it->data)->arr->element_count)
	{
		((mgl_array_iterator_t*)out->data)->index = ((mgl_array_iterator_t*)it->data)->arr->element_count;
		((mgl_array_iterator_t*)out->data)->arr = ((mgl_array_iterator_t*)it->data)->arr;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_array_iterator_t*)out->data)->index = ((mgl_array_iterator_t*)it->data)->index + 1;
	((mgl_array_iterator_t*)out->data)->arr = ((mgl_array_iterator_t*)it->data)->arr;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_array_iterator_prev(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	out->functions = it->functions;
	
	if (((mgl_array_iterator_t*)it->data)->index == 0)
	{
		((mgl_array_iterator_t*)out->data)->index = ((mgl_array_iterator_t*)it->data)->arr->element_count;
		((mgl_array_iterator_t*)out->data)->arr = ((mgl_array_iterator_t*)it->data)->arr;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_array_iterator_t*)out->data)->index = ((mgl_array_iterator_t*)it->data)->index - 1;
	((mgl_array_iterator_t*)out->data)->arr = ((mgl_array_iterator_t*)it->data)->arr;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_array_iterator_move(const mgl_iterator_t * it, mgl_iterator_t * out, mgl_i64_t move)
{
	out->functions = it->functions;
	
	if (move > 0)
	{
		if (((mgl_array_iterator_t*)it->data)->index + (mgl_u64_t)move >= ((mgl_array_iterator_t*)it->data)->arr->element_count)
		{
			((mgl_array_iterator_t*)out->data)->index = ((mgl_array_iterator_t*)it->data)->arr->element_count;
			((mgl_array_iterator_t*)out->data)->arr = ((mgl_array_iterator_t*)it->data)->arr;
			return MGL_ERROR_OUT_OF_BOUNDS;
		}
	}
	else
	{
		if (((mgl_array_iterator_t*)it->data)->index < (mgl_u64_t)(-move))
		{
			((mgl_array_iterator_t*)out->data)->index = ((mgl_array_iterator_t*)it->data)->arr->element_count;
			((mgl_array_iterator_t*)out->data)->arr = ((mgl_array_iterator_t*)it->data)->arr;
			return MGL_ERROR_OUT_OF_BOUNDS;
		}
	}
	
	((mgl_array_iterator_t*)out->data)->index = ((mgl_array_iterator_t*)it->data)->index + move;
	((mgl_array_iterator_t*)out->data)->arr = ((mgl_array_iterator_t*)it->data)->arr;
	return MGL_ERROR_NONE;
}

static mgl_bool_t mgl_array_iterator_is_null(const mgl_iterator_t * it)
{
	return ((mgl_array_iterator_t*)it->data)->index >= ((mgl_array_iterator_t*)it->data)->arr->element_count;
}

static void * mgl_array_iterator_get(const mgl_iterator_t * it)
{
	MGL_ASSERT(!mgl_array_iterator_is_null(it));
	return ((mgl_array_iterator_t*)it->data)->arr->buffer + ((mgl_array_iterator_t*)it->data)->index * ((mgl_array_iterator_t*)it->data)->arr->element_size;
}

static void * mgl_array_iterator_get_raw(const mgl_iterator_t * it)
{
	if (((mgl_array_iterator_t*)it->data)->index >= ((mgl_array_iterator_t*)it->data)->arr->element_count)
		return NULL;
	return ((mgl_array_iterator_t*)it->data)->arr->buffer + ((mgl_array_iterator_t*)it->data)->index * ((mgl_array_iterator_t*)it->data)->arr->element_size;
}

static mgl_iterator_functions_t mgl_array_iterator_functions =
{
	&mgl_array_iterator_next,
	&mgl_array_iterator_prev,
	&mgl_array_iterator_move,
	&mgl_array_iterator_is_null,
	&mgl_array_iterator_get,
	&mgl_array_iterator_get_raw,
};

void MGL_API mgl_init_array(mgl_array_t * arr, mgl_u64_t element_count, mgl_u64_t element_size, mgl_u8_t * buffer)
{
	MGL_DEBUG_ASSERT(arr != NULL && element_count > 0 && element_size > 0 && buffer != NULL);

	arr->element_count = element_count;
	arr->element_size = element_size;
	arr->buffer = buffer;
}

void MGL_API mgl_get_array_begin_it(mgl_array_t * arr, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(arr != NULL && it != NULL);
	it->functions = &mgl_array_iterator_functions;
	((mgl_array_iterator_t*)it->data)->arr = arr;
	((mgl_array_iterator_t*)it->data)->index = 0;
}

void MGL_API mgl_get_array_end_it(mgl_array_t * arr, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(arr != NULL && it != NULL);
	it->functions = &mgl_array_iterator_functions;
	((mgl_array_iterator_t*)it->data)->arr = arr;
	((mgl_array_iterator_t*)it->data)->index = arr->element_count - 1;
}

void MGL_API mgl_get_array_element_it(mgl_array_t * arr, mgl_u64_t index, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(arr != NULL && it != NULL);
	it->functions = &mgl_array_iterator_functions;
	((mgl_array_iterator_t*)it->data)->arr = arr;
	((mgl_array_iterator_t*)it->data)->index = index;
}

void * MGL_API mgl_access_array(mgl_array_t * arr, mgl_u64_t index)
{
	MGL_DEBUG_ASSERT(arr != NULL);
	MGL_ASSERT(index < arr->element_count);
	return arr->buffer + arr->element_size * index;
}
