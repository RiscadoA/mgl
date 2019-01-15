#ifndef MGL_MEMORY_MANIPULATION_H
#define MGL_MEMORY_MANIPULATION_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdlib.h>

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

	/// <summary>
	///		Checks if the current native endianness is big endianness.
	/// </summary>
	/// <returns>MGL_TRUE if it is, otherwise MGL_FALSE</returns>
	inline mgl_bool_t mgl_is_big_endian(void)
	{
		union
		{
			mgl_u16_t i;
			mgl_u8_t  b[2];
		} e = { 0x0100 };
		return e.b[0];
	}

	/// <summary>
	///		Converts a 2 byte value to big-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_to_big_endian_2(const void* in, void* out)
	{
		const mgl_u16_t* i = (const mgl_u16_t*)in;
		mgl_u16_t* o = (mgl_u16_t*)out;
		if (mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ushort(*i);
#else
			*o = ((*i & 0x00FF) << 8) | ((*i & 0xFF00) >> 8);
#endif
		}
	}

	/// <summary>
	///		Converts a 4 byte value to big-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_to_big_endian_4(const void* in, void* out)
	{
		const mgl_u32_t* i = (const mgl_u32_t*)in;
		mgl_u32_t* o = (mgl_u32_t*)out;
		if (mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ulong(*i);
#else
			*o = ((*i & 0x000000FF) << 24) |
				 ((*i & 0x0000FF00) << 8) |
				 ((*i & 0x00FF0000) >> 8) |
				 ((*i & 0xFF000000) >> 24);
#endif
		}	
	}

	/// <summary>
	///		Converts a 8 byte value to big-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_to_big_endian_8(const void* in, void* out)
	{
		const mgl_u64_t* i = (const mgl_u64_t*)in;
		mgl_u64_t* o = (mgl_u64_t*)out;
		if (mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_uint64(*i);
#else
			*o = ((*i & 0x00000000000000FFULL) << 56) |
				 ((*i & 0x000000000000FF00ULL) << 40) |
				 ((*i & 0x0000000000FF0000ULL) << 24) |
			 	 ((*i & 0x00000000FF000000ULL) << 8) |
			 	 ((*i & 0x000000FF00000000ULL) >> 8) |
				 ((*i & 0x0000FF0000000000ULL) >> 24) |
				 ((*i & 0x00FF000000000000ULL) >> 40) |
				 ((*i & 0xFF00000000000000ULL) >> 56);
#endif
		}	
	}

	/// <summary>
	///		Converts a 2 byte value from big-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_from_big_endian_2(const void* in, void* out)
	{
		const mgl_u16_t* i = (const mgl_u16_t*)in;
		mgl_u16_t* o = (mgl_u16_t*)out;
		if (mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ushort(*i);
#else
			*o = ((*i & 0x00FF) << 8) | ((*i & 0xFF00) >> 8);
#endif
		}
	}

	/// <summary>
	///		Converts a 4 byte value from big-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_from_big_endian_4(const void* in, void* out)
	{
		const mgl_u32_t* i = (const mgl_u32_t*)in;
		mgl_u32_t* o = (mgl_u32_t*)out;
		if (mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ulong(*i);
#else
			*o = ((*i & 0x000000FF) << 24) |
				((*i & 0x0000FF00) << 8) |
				((*i & 0x00FF0000) >> 8) |
				((*i & 0xFF000000) >> 24);
#endif
		}
	}

	/// <summary>
	///		Converts a 8 byte value from big-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_from_big_endian_8(const void* in, void* out)
	{
		const mgl_u64_t* i = (const mgl_u64_t*)in;
		mgl_u64_t* o = (mgl_u64_t*)out;
		if (mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_uint64(*i);
#else
			*o = ((*i & 0x00000000000000FFULL) << 56) |
				((*i & 0x000000000000FF00ULL) << 40) |
				((*i & 0x0000000000FF0000ULL) << 24) |
				((*i & 0x00000000FF000000ULL) << 8) |
				((*i & 0x000000FF00000000ULL) >> 8) |
				((*i & 0x0000FF0000000000ULL) >> 24) |
				((*i & 0x00FF000000000000ULL) >> 40) |
				((*i & 0xFF00000000000000ULL) >> 56);
#endif
		}
	}

	/// <summary>
	///		Converts a 2 byte value to little-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_to_little_endian_2(const void* in, void* out)
	{
		const mgl_u16_t* i = (const mgl_u16_t*)in;
		mgl_u16_t* o = (mgl_u16_t*)out;
		if (!mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ushort(*i);
#else
			*o = ((*i & 0x00FF) << 8) | ((*i & 0xFF00) >> 8);
#endif
		}
	}

	/// <summary>
	///		Converts a 4 byte value to little-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_to_little_endian_4(const void* in, void* out)
	{
		const mgl_u32_t* i = (const mgl_u32_t*)in;
		mgl_u32_t* o = (mgl_u32_t*)out;
		if (!mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ulong(*i);
#else
			*o = ((*i & 0x000000FF) << 24) |
				 ((*i & 0x0000FF00) << 8) |
				 ((*i & 0x00FF0000) >> 8) |
				 ((*i & 0xFF000000) >> 24);
#endif
		}
	}

	/// <summary>
	///		Converts a 8 byte value to little-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_to_little_endian_8(const void* in, void* out)
	{
		const mgl_u64_t* i = (const mgl_u64_t*)in;
		mgl_u64_t* o = (mgl_u64_t*)out;
		if (!mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_uint64(*i);
#else
			*o = ((*i & 0x00000000000000FFULL) << 56) |
				 ((*i & 0x000000000000FF00ULL) << 40) |
				 ((*i & 0x0000000000FF0000ULL) << 24) |
				 ((*i & 0x00000000FF000000ULL) << 8) |
				 ((*i & 0x000000FF00000000ULL) >> 8) |
				 ((*i & 0x0000FF0000000000ULL) >> 24) |
				 ((*i & 0x00FF000000000000ULL) >> 40) |
				 ((*i & 0xFF00000000000000ULL) >> 56);
#endif
		}
	}

	/// <summary>
	///		Converts a 2 byte value to little-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_from_little_endian_2(const void* in, void* out)
	{
		const mgl_u16_t* i = (const mgl_u16_t*)in;
		mgl_u16_t* o = (mgl_u16_t*)out;
		if (!mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ushort(*i);
#else
			*o = ((*i & 0x00FF) << 8) | ((*i & 0xFF00) >> 8);
#endif
		}
	}

	/// <summary>
	///		Converts a 4 byte value from little-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_from_little_endian_4(const void* in, void* out)
	{
		const mgl_u32_t* i = (const mgl_u32_t*)in;
		mgl_u32_t* o = (mgl_u32_t*)out;
		if (!mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_ulong(*i);
#else
			*o = ((*i & 0x000000FF) << 24) |
				((*i & 0x0000FF00) << 8) |
				((*i & 0x00FF0000) >> 8) |
				((*i & 0xFF000000) >> 24);
#endif
		}
	}

	/// <summary>
	///		Converts a 8 byte value from little-endian.
	/// </summary>
	/// <param name="in">Input value</param>
	/// <param name="out">Output value</param>
	inline void mgl_from_little_endian_8(const void* in, void* out)
	{
		const mgl_u64_t* i = (const mgl_u64_t*)in;
		mgl_u64_t* o = (mgl_u64_t*)out;
		if (!mgl_is_big_endian())
			*o = *i;
		else
		{
#ifdef _MSC_VER
			*o = _byteswap_uint64(*i);
#else
			*o = ((*i & 0x00000000000000FFULL) << 56) |
				((*i & 0x000000000000FF00ULL) << 40) |
				((*i & 0x0000000000FF0000ULL) << 24) |
				((*i & 0x00000000FF000000ULL) << 8) |
				((*i & 0x000000FF00000000ULL) >> 8) |
				((*i & 0x0000FF0000000000ULL) >> 24) |
				((*i & 0x00FF000000000000ULL) >> 40) |
				((*i & 0xFF00000000000000ULL) >> 56);
#endif
		}
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MEMORY_MANIPULATION_H
