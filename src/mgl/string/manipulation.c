#include <mgl/string/manipulation.h>
#include <string.h>

mgl_u64_t MGL_API mgl_str_size(const mgl_chr8_t * str)
{
	MGL_DEBUG_ASSERT(str != NULL);
	mgl_u64_t length;
	for (length = 0; *str != '\0'; ++str, ++length);
	return length;
}

mgl_bool_t MGL_API mgl_str_equal(const mgl_chr8_t * s0, const mgl_chr8_t * s1)
{
	MGL_DEBUG_ASSERT(s0 != NULL && s1 != NULL);
	return (strcmp(s0, s1) == 0) ? MGL_TRUE : MGL_FALSE;
}

mgl_u64_t MGL_API mgl_str_copy(const mgl_chr8_t * src, mgl_chr8_t * dst, mgl_u64_t max_dst_size)
{
	MGL_DEBUG_ASSERT(src != NULL && dst != NULL && max_dst_size > 0);
	for (mgl_u64_t i = 0;; ++i, ++dst, ++src)
	{
		if (i == max_dst_size - 1 || *src == '\0')
		{
			*dst = '\0';
			return i;
		}

		*dst = *src;
	}
}
