#include <mgl/string/manipulation.h>
#include <string.h>

mgl_u64_t MGL_API mgl_str_size(const mgl_u8_t * str)
{
	MGL_DEBUG_ASSERT(str != NULL);
	mgl_u64_t length;
	for (length = 0; *str != '\0'; ++str, ++length);
	return length;
}

mgl_bool_t MGL_API mgl_str_equal(const mgl_u8_t * s0, const mgl_u8_t * s1)
{
	MGL_DEBUG_ASSERT(s0 != NULL && s1 != NULL);
	return (strcmp(s0, s1) == 0) ? MGL_TRUE : MGL_FALSE;
}
