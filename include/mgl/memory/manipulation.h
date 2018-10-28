#ifndef MGL_MEMORY_MANIPULATION_H
#define MGL_MEMORY_MANIPULATION_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Copies memory from a place to another.
	/// </summary>
	/// <param name="dst">Destination pointer</param>
	/// <param name="src">Source pointer</param>
	/// <param name="size">Memory amount in bytes</param>
	void MGL_API mgl_mem_copy(void* dst, const void* src, mgl_u64_t size);

	/// <summary>
	///		Checks if two memory regions are equal.
	/// </summary>
	/// <param name="x">Memory region x</param>
	/// <param name="y">Memory region y</param>
	/// <param name="size">Memory region size in bytes</param>
	/// <returns>MGL_TRUE if they are equal, otherwise MGL_FALSE</returns>
	mgl_bool_t MGL_API mgl_mem_equal(const void* x, const void* y, mgl_u64_t size);

	/// <summary>
	///		Sets a whole memory region's bytes to a single value.
	/// </summary>
	/// <param name="buffer">Buffer</param>
	/// <param name="size">Buffer size</param>
	/// <param name="value">Value</param>
	void MGL_API mgl_mem_set(void* buffer, mgl_u64_t size, mgl_u8_t value);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_MANIPULATION_H
