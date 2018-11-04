#include <mgl/memory/crc.h>

mgl_u8_t MGL_API mgl_crc8(mgl_u8_t prev_crc, const void * buffer, mgl_u64_t size)
{
	static const mgl_u8_t polynomial = 0xE7;

	mgl_u8_t crc = ~prev_crc;
	const mgl_u8_t* current = (const mgl_u8_t*)buffer;

	while (size--)
	{
		crc ^= *current++;
		for (mgl_u64_t i = 0; i < 8; ++i)
			crc = (crc >> 1) ^ (-(mgl_u8_t)(crc & 1) & polynomial);
	}

	return ~crc;
}

mgl_u16_t MGL_API mgl_crc16(mgl_u16_t prev_crc, const void * buffer, mgl_u64_t size)
{
	static const uint16_t polynomial = 0x9EB2;

	uint16_t crc = ~prev_crc;
	const mgl_u8_t* current = (const mgl_u8_t*)buffer;

	while (size--)
	{
		crc ^= *current++;
		for (mgl_u64_t i = 0; i < 8; ++i)
			crc = (crc >> 1) ^ (-(uint16_t)(crc & 1) & polynomial);
	}

	return ~crc;
}

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
