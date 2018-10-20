#include <mgl/memory/manipulation.h>
#include <string.h>

void MGL_API mgl_memcpy(void* dst, const void* src, mgl_u64_t size)
{
	MGL_DEBUG_ASSERT(dst != NULL && src != NULL && size != 0);
	memcpy(dst, src, size);
}
