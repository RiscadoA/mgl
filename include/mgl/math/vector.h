#ifndef MGL_MATH_VECTOR_H
#define MGL_MATH_VECTOR_H

#include <mgl/error.h>
#include <xmmintrin.h>
#include <emmintrin.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef __m128	mgl_f32v4_t;
	typedef __m128i	mgl_i32v4_t;
	typedef __m128i	mgl_u32v4_t;

	/// <summary>
	///		Loads 4 mgl_f32_t's into a mgl_f32v4_t (unaligned).
	/// </summary>
	/// <param name="value">Value</param>
	/// <returns>mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_load(const mgl_f32_t value[4]);

	/// <summary>
	///		Loads 4 mgl_f32_t's into a mgl_f32v4_t (aligned to 16 bytes).
	/// </summary>
	/// <param name="value">Value</param>
	/// <returns>mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_load_aligned(const mgl_f32_t value[4]);

	/// <summary>
	///		Stores the values in a mgl_f32v4_t into 4 mgl_f32_t's.
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <param name="value">Out values</param>
	MGL_API void mgl_f32v4_store(const mgl_f32v4_t* v, mgl_f32_t value[4]);

	/// <summary>
	///		Stores the values in a mgl_f32v4_t into 4 mgl_f32_t's (aligned to 16 bytes).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <param name="value">Out values</param>
	MGL_API void mgl_f32v4_store_aligned(const mgl_f32v4_t* v, mgl_f32_t value[4]);

	/// <summary>
	///		Loads 4 separate mgl_f32_t into a mgl_f32v4_t.
	/// </summary>
	/// <param name="x">X component</param>
	/// <param name="y">Y component</param>
	/// <param name="z">Z component</param>
	/// <param name="w">W component</param>
	/// <returns>mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_set(mgl_f32_t x, mgl_f32_t y, mgl_f32_t z, mgl_f32_t w);

	/// <summary>
	///		Adds two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_add(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

	/// <summary>
	///		Subtracts two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_sub(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

	/// <summary>
	///		Multiplies two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_mul(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

	/// <summary>
	///		Divides two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_div(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

	/// <summary>
	///		Returns the mgl_f32v4_t with the lowest value (compoonent-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_min(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

	/// <summary>
	///		Returns the mgl_f32v4_t with the lowest value (compoonent-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_max(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

	/// <summary>
	///		Calculates the square root of a mgl_f32v4_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_sqrt(mgl_f32v4_t v);

	/// <summary>
	///		Calculates the reciprocal square root of a mgl_f32v4_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_rsqrt(mgl_f32v4_t v);

	/// <summary>
	///		Calculates the reciprocal of a mgl_f32v4_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	MGL_API mgl_f32v4_t mgl_f32v4_rcp(mgl_f32v4_t v);

	MGL_API mgl_f32v4_t mgl_f32v4_cross(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

	MGL_API mgl_f32_t mgl_f32v4_dot(mgl_f32v4_t lhs, mgl_f32v4_t rhs);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_VECTOR_H
