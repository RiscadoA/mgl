#ifndef MGL_STRING_MANIPULATION_H
#define MGL_STRING_MANIPULATION_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Gets a null terminated string size in bytes.
	/// </summary>
	/// <param name="str">String pointer</param>
	/// <returns>String size in bytes</returns>
	mgl_u64_t MGL_API mgl_str_size(const mgl_chr8_t* str);

	/// <summary>
	///		Checks if two null terminated strings are equal.
	/// </summary>
	/// <param name="s0">First string</param>
	/// <param name="s1">Second string</param>
	/// <returns>MGL_TRUE if they are equal, otherwise MGL_FALSE</returns>
	mgl_bool_t MGL_API mgl_str_equal(const mgl_chr8_t* s0, const mgl_chr8_t* s1);

	/// <summary>
	///		Copies a string into another string.
	///		The terminating null character is included in the size.
	/// </summary>
	/// <param name="src">Source string</param>
	/// <param name="dst">Destination string</param>
	/// <param name="max_dst_size">Destination string buffer size (including the terminating null character)</param>
	/// <returns>Size copied (including the terminating null character)</returns>
	mgl_u64_t MGL_API mgl_str_copy(const mgl_chr8_t* src, mgl_chr8_t* dst, mgl_u64_t max_dst_size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_STRING_MANIPULATION_H
