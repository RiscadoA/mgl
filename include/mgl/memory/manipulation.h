#ifndef MGL_MEMORY_LINEAR_ALLOCATOR_H
#define MGL_MEMORY_LINEAR_ALLOCATOR_H

#include <mgl/memory/allocator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Copies memory from a place to another.
	/// </summary>
	/// <param name="dst">Destination pointer</param>
	/// <param name="src">Source pointer</param>
	/// <param name="size">Memory amount in bytes</param>
	void MGL_API mgl_memcpy(void* dst, const void* src, mgl_u64_t size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_LINEAR_ALLOCATOR_H
