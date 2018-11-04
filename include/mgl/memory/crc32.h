#ifndef MGL_MEMORY_CRC32_H
#define MGL_MEMORY_CRC32_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Calculates the CRC-32 hash of a memory region.
	/// </summary>
	/// <param name="prev_crc">Previous CRC-32 value (default is 0)</param>
	/// <param name="buffer">Buffer</param>
	/// <param name="size">Buffer size</param>
	/// <returns>CRC-32 value</returns>
	mgl_u32_t MGL_API mgl_crc32(mgl_u32_t prev_crc, const void* buffer, mgl_u64_t size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_CRC32_H
