#include <mgl/memory/crc32.h>

mgl_u32_t MGL_API mgl_crc32(mgl_u32_t prev_crc, const void * buffer, mgl_u64_t size)
{
	static const uint32_t polynomial = 0xEDB88320;

	mgl_u32_t crc = ~prev_crc;
	const mgl_u8_t* current = (const mgl_u8_t*)buffer;

	while (size--)
	{
		crc ^= *current++;
		for (mgl_u64_t i = 0; i < 8; ++i)
			crc = (crc >> 1) ^ (-(mgl_i32_t)(crc & 1) & polynomial);
	}
	
	return ~crc;
}
