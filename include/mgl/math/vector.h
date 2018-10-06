#ifndef MGL_MATH_VECTOR_H
#define MGL_MATH_VECTOR_H

#include <mgl/error.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>

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
	inline mgl_f32v4_t mgl_f32v4_load(const mgl_f32_t value[4])
	{
		return _mm_loadu_ps(value);
	}

	/// <summary>
	///		Loads 4 mgl_f32_t's into a mgl_f32v4_t (aligned to 16 bytes).
	/// </summary>
	/// <param name="value">Value</param>
	/// <returns>mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_load_aligned(const mgl_f32_t value[4])
	{
		return _mm_load_ps(value);
	}

	/// <summary>
	///		Stores the values in a mgl_f32v4_t into 4 mgl_f32_t's.
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <param name="value">Out values</param>
	inline void mgl_f32v4_store(const mgl_f32v4_t* v, mgl_f32_t value[4])
	{
		_mm_storeu_ps(value, *v);
	}

	/// <summary>
	///		Stores the values in a mgl_f32v4_t into 4 mgl_f32_t's (aligned to 16 bytes).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <param name="value">Out values</param>
	inline void mgl_f32v4_store_aligned(const mgl_f32v4_t* v, mgl_f32_t value[4])
	{
		_mm_store_ps(value, *v);
	}

	/// <summary>
	///		Loads 4 separate mgl_f32_t into a mgl_f32v4_t.
	/// </summary>
	/// <param name="x">X component</param>
	/// <param name="y">Y component</param>
	/// <param name="z">Z component</param>
	/// <param name="w">W component</param>
	/// <returns>mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_set(mgl_f32_t x, mgl_f32_t y, mgl_f32_t z, mgl_f32_t w)
	{
		return _mm_setr_ps(x, y, z, w);
	}

	/// <summary>
	///		Adds two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_add(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_add_ps(lhs, rhs);
	}

	/// <summary>
	///		Subtracts two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_sub(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_sub_ps(lhs, rhs);
	}

	/// <summary>
	///		Multiplies two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_mul(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_mul_ps(lhs, rhs);
	}

	/// <summary>
	///		Divides two mgl_f32v4_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_div(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_div_ps(lhs, rhs);
	}

	/// <summary>
	///		Returns the mgl_f32v4_t with the lowest value (compoonent-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_min(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_min_ps(lhs, rhs);
	}

	/// <summary>
	///		Returns the mgl_f32v4_t with the lowest value (compoonent-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_max(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_max_ps(lhs, rhs);
	}

	/// <summary>
	///		Calculates the square root of a mgl_f32v4_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_sqrt(mgl_f32v4_t v)
	{
		return _mm_sqrt_ps(v);
	}

	/// <summary>
	///		Calculates the reciprocal square root of a mgl_f32v4_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_rsqrt(mgl_f32v4_t v)
	{
		return _mm_rsqrt_ps(v);
	}

	/// <summary>
	///		Calculates the reciprocal of a mgl_f32v4_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_rcp(mgl_f32v4_t v)
	{
		return _mm_rcp_ps(v);
	}

	/// <summary>
	///		Calculates the cross product between two mgl_f32v4_t.
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result mgl_f32v4_t</returns>
	inline mgl_f32v4_t mgl_f32v4_cross(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_sub_ps(
			_mm_mul_ps(_mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 1, 0, 2))),
			_mm_mul_ps(_mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 0, 2, 1)))
		);
	}

	/// <summary>
	///		Calculates the dot product between two mgl_f32v4_t.
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>Result</returns>
	inline mgl_f32_t mgl_f32v4_dot(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_cvtss_f32(_mm_dp_ps(lhs, rhs, 0x71));
	}

	/// <summary>
	///		Checks if two mgl_f32v4_t are equal.
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>MGL_FALSE if different, otherwise equal</returns>
	inline mgl_bool_t mgl_f32v4_equal(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) == 0xF;
	}

	/// <summary>
	///		Checks if two mgl_f32v4_t are different.
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <returns>MGL_FALSE if equal, otherwise equal</returns>
	inline mgl_bool_t mgl_f32v4_nequal(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
	{
		return _mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) != 0xF;
	}

	/// <summary>
	///		Checks if two mgl_f32v4_t are equal (roughly).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>MGL_FALSE if different, otherwise equal</returns>
	inline mgl_bool_t mgl_f32v4_equal_e(mgl_f32v4_t lhs, mgl_f32v4_t rhs, mgl_f32_t epsilon)
	{
		mgl_f32v4_t eps = _mm_set1_ps(epsilon);
		mgl_f32v4_t abd = _mm_andnot_ps(_mm_set1_ps(-0.0f), _mm_sub_ps(lhs, rhs));
		return _mm_movemask_ps(_mm_cmplt_ps(abd, eps)) == 0xF;
	}

	/// <summary>
	///		Checks if two mgl_f32v4_t are different (roughly).
	/// </summary>
	/// <param name="lhs">Left mgl_f32v4_t</param>
	/// <param name="rhs">Right mgl_f32v4_t</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>MGL_FALSE if equal, otherwise equal</returns>
	inline mgl_bool_t mgl_f32v4_nequal_e(mgl_f32v4_t lhs, mgl_f32v4_t rhs, mgl_f32_t epsilon)
	{
		mgl_f32v4_t eps = _mm_set1_ps(epsilon);
		mgl_f32v4_t abd = _mm_andnot_ps(_mm_set1_ps(-0.0f), _mm_sub_ps(lhs, rhs));
		return _mm_movemask_ps(_mm_cmplt_ps(abd, eps)) != 0xF;
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_VECTOR_H
