#include <mgl/memory/manipulation.h>
#include <string.h>

void MGL_API mgl_mem_copy(void* dst, const void* src, mgl_u64_t size)
{
	MGL_DEBUG_ASSERT(dst != NULL && src != NULL);
	if (size == 0)
		return;
	memcpy(dst, src, size);
}

mgl_bool_t MGL_API mgl_mem_equal(const void * x, const void * y, mgl_u64_t size)
{
	MGL_DEBUG_ASSERT(x != NULL && y != NULL && size != 0);
	return (memcmp(x, y, size) == 0) ? MGL_TRUE  : MGL_FALSE;
}

void MGL_API mgl_mem_set(void * buffer, mgl_u64_t size, mgl_u8_t value)
{
	MGL_DEBUG_ASSERT(buffer != NULL && size != 0);
	memset(buffer, value, size);
}
