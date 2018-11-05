#ifndef MGL_MEMORY_CRC_H
#define MGL_MEMORY_CRC_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Calculates the CRC-8 hash of a memory region.
	/// </summary>
	/// <param name="prev_crc">Previous CRC-8 value (default is 0)</param>
	/// <param name="buffer">Buffer</param>
	/// <param name="size">Buffer size</param>
	/// <returns>CRC-8 value</returns>
	mgl_u8_t MGL_API mgl_crc8(mgl_u8_t prev_crc, const void* buffer, mgl_u64_t size);

	/// <summary>
	///		Calculates the CRC-16 hash of a memory region.
	/// </summary>
	/// <param name="prev_crc">Previous CRC-16 value (default is 0)</param>
	/// <param name="buffer">Buffer</param>
	/// <param name="size">Buffer size</param>
	/// <returns>CRC-16 value</returns>
	mgl_u16_t MGL_API mgl_crc16(mgl_u16_t prev_crc, const void* buffer, mgl_u64_t size);

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
#endif // MGL_MEMORY_CRC_H
