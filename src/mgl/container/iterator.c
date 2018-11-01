#include <mgl/container/iterator.h>

mgl_error_t MGL_API mgl_iterator_next(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	MGL_DEBUG_ASSERT(it != NULL && out != NULL);
	if (it->functions->next == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return it->functions->next(it, out);
}

mgl_error_t MGL_API mgl_iterator_prev(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	MGL_DEBUG_ASSERT(it != NULL && out != NULL);
	if (it->functions->prev == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return it->functions->prev(it, out);
}

mgl_error_t MGL_API mgl_iterator_move(const mgl_iterator_t * it, mgl_iterator_t * out, mgl_i64_t move)
{
	MGL_DEBUG_ASSERT(it != NULL && out != NULL);
	if (it->functions->move == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return it->functions->move(it, out, move);
}

mgl_bool_t MGL_API mgl_iterator_is_null(const mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(it != NULL);
	if (it->functions->is_null == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return it->functions->is_null(it);
}

void * MGL_API mgl_iterator_get(const mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(it != NULL);
	if (it->functions->get == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return it->functions->get(it);
}

void * MGL_API mgl_iterator_get_raw(const mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(it != NULL);
	if (it->functions->get_raw == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return it->functions->get_raw(it);
}
