#ifndef MGL_MATH_SIMD_H
#define MGL_MATH_SIMD_H

// SSE
#ifdef MGL_BUILD_SSE

#include <mgl/error.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>

/// <summary>
///		Creates a mask used to pass into mgl_f128_shuffle param 'shuffle'.
/// </summary>
/// <param name="fp3">Index of the component (0-3) from the left vector that will be placed on the fourth component</param>
/// <param name="fp2">Index of the component (0-3) from the left vector that will be placed on the third component</param>
/// <param name="fp1">Index of the component (0-3) from the right vector that will be placed on the second component</param>
/// <param name="fp0">Index of the component (0-3) from the right vector that will be placed on the first component</param>
/// <returns>Shuffle mask to pass to mgl_f128_shuffle param 'shuffle'</returns>
#define MGL_SIMD_SHUFFLE(fp3, fp2, fp1, fp0) (_MM_SHUFFLE(fp3, fp2, fp1, fp0))

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef __m128	mgl_f128_t;
	// TO IMPLEMENT:
	// typedef __m128i	mgl_i128_t;
	// typedef __m128i	mgl_u128_t;

	/// <summary>
	///		Loads 4 mgl_f32_t's into a mgl_f128_t (unaligned).
	/// </summary>
	/// <param name="value">Value</param>
	/// <returns>mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_load(const mgl_f32_t value[4])
	{
		MGL_DEBUG_ASSERT(value != NULL);
		return _mm_loadu_ps(value);
	}

	/// <summary>
	///		Loads 4 mgl_f32_t's into a mgl_f128_t (aligned to 16 bytes).
	/// </summary>
	/// <param name="value">Value</param>
	/// <returns>mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_load_aligned(const mgl_f32_t value[4])
	{
		MGL_DEBUG_ASSERT(value != NULL);
		return _mm_load_ps(value);
	}

	/// <summary>
	///		Stores the values in a mgl_f128_t into 4 mgl_f32_t's.
	/// </summary>
	/// <param name="v">mgl_f128_t</param>
	/// <param name="value">Out values</param>
	static inline void mgl_f128_store(mgl_f128_t v, mgl_f32_t value[4])
	{
		MGL_DEBUG_ASSERT(value != NULL);
		_mm_storeu_ps(value, v);
	}

	/// <summary>
	///		Stores the values in a mgl_f128_t into 4 mgl_f32_t's (aligned to 16 bytes).
	/// </summary>
	/// <param name="v">mgl_f128_t</param>
	/// <param name="value">Out values</param>
	static inline void mgl_f128_store_aligned(mgl_f128_t v, mgl_f32_t value[4])
	{
		MGL_DEBUG_ASSERT(value != NULL);
		_mm_store_ps(value, v);
	}

	/// <summary>
	///		Loads 4 separate mgl_f32_t into a mgl_f128_t.
	/// </summary>
	/// <param name="x">X component</param>
	/// <param name="y">Y component</param>
	/// <param name="z">Z component</param>
	/// <param name="w">W component</param>
	/// <returns>mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_set(mgl_f32_t x, mgl_f32_t y, mgl_f32_t z, mgl_f32_t w)
	{
		return _mm_setr_ps(x, y, z, w);
	}

	/// <summary>
	///		Loads a mgl_f32_t into a mgl_f128_t (scalar).
	/// </summary>
	/// <param name="v">Scalar value</param>
	/// <returns>mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_set_scalar(mgl_f32_t v)
	{
		return _mm_set1_ps(v);
	}

	/// <summary>
	///		Shuffles two mgl_f128_t and returns the result.
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <param name="shuffle">Value returned by MGL_SIMD_SHUFFLE</param>
	/// <returns>Result mgl_f128_t</returns>
#define mgl_f128_shuffle(lhs, rhs, shuffle) _mm_shuffle_ps(lhs, rhs, shuffle)

	/// <summary>
	///		Transposes a 4x4 matrix stored in 4 mgl_f128_t's.
	/// </summary>
	/// <param name="col0">Column 0</param>
	/// <param name="col1">Column 1</param>
	/// <param name="col2">Column 2</param>
	/// <param name="col3">Column 3</param>
#define mgl_f128m4x4_transpose(col0, col1, col2, col3) _MM_TRANSPOSE4_PS(col0, col1, col2, col3)

	/// <summary>
	///		Performs an horizontal addition between two mgl_f128_t and returns the result (component-wise).
	///		(A0, A1, A2, A3) hadd (B0, B1, B2, B3) =
	///		(B0 + B1, B2 + B3, A0 + A1, A2 + A3)
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_hadd(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_hadd_ps(lhs, rhs);
	}

	/// <summary>
	///		Performs an horizontal subtraction between two mgl_f128_t and returns the result (component-wise).
	///		(A0, A1, A2, A3) hsub (B0, B1, B2, B3) =
	///		(B0 - B1, B2 - B3, A0 - A1, A2 - A3)
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_hsub(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_hsub_ps(lhs, rhs);
	}

	/// <summary>
	///		Performs an addition on components 1 and 3 and a subtraction on components 0 and 2 between two mgl_f128_t and returns the result (component-wise).
	///		(A0, A1, A2, A3) addsub (B0, B1, B2, B3) =
	///		(A0 - B0, A1 + B1, A2 - B2, A3 + B3)
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_addsub(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_addsub_ps(lhs, rhs);
	}

	/// <summary>
	///		Adds two mgl_f128_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_add(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_add_ps(lhs, rhs);
	}

	/// <summary>
	///		Subtracts two mgl_f128_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_sub(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_sub_ps(lhs, rhs);
	}

	/// <summary>
	///		Multiplies two mgl_f128_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_mul(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_mul_ps(lhs, rhs);
	}

	/// <summary>
	///		Divides two mgl_f128_t and returns the result (component-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_div(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_div_ps(lhs, rhs);
	}

	/// <summary>
	///		Returns the mgl_f128_t with the lowest value (compoonent-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_min(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_min_ps(lhs, rhs);
	}

	/// <summary>
	///		Returns the mgl_f128_t with the lowest value (compoonent-wise).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_max(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_max_ps(lhs, rhs);
	}

	/// <summary>
	///		Calculates the square root of a mgl_f128_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_sqrt(mgl_f128_t v)
	{
		return _mm_sqrt_ps(v);
	}

	/// <summary>
	///		Calculates the reciprocal square root of a mgl_f128_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_rsqrt(mgl_f128_t v)
	{
		return _mm_rsqrt_ps(v);
	}

	/// <summary>
	///		Calculates the reciprocal of a mgl_f128_t (compoonent-wise).
	/// </summary>
	/// <param name="v">mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_rcp(mgl_f128_t v)
	{
		return _mm_rcp_ps(v);
	}

	/// <summary>
	///		Calculates the cross product between two mgl_f128_t.
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result mgl_f128_t</returns>
	static inline mgl_f128_t mgl_f128_cross(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_sub_ps(
			_mm_mul_ps(_mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 1, 0, 2))),
			_mm_mul_ps(_mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 0, 2, 1)))
		);
	}

	/// <summary>
	///		Calculates the dot product between two mgl_f128_t.
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result</returns>
	static inline mgl_f128_t mgl_f128_dot(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_dp_ps(lhs, rhs, 0xFF);
	}

	/// <summary>
	///		Calculates the dot product between two mgl_f128_t.
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>Result</returns>
	static inline mgl_f32_t mgl_f128_dot_scalar(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_cvtss_f32(_mm_dp_ps(lhs, rhs, 0xFF));
	}

	/// <summary>
	///		Checks if two mgl_f128_t are equal.
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>MGL_FALSE if different, otherwise equal</returns>
	static inline mgl_bool_t mgl_f128_equal(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) == 0xF;
	}

	/// <summary>
	///		Checks if two mgl_f128_t are different.
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <returns>MGL_FALSE if equal, otherwise equal</returns>
	static inline mgl_bool_t mgl_f128_nequal(mgl_f128_t lhs, mgl_f128_t rhs)
	{
		return _mm_movemask_ps(_mm_cmpeq_ps(lhs, rhs)) != 0xF;
	}

	/// <summary>
	///		Checks if two mgl_f128_t are equal (roughly).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>MGL_FALSE if different, otherwise equal</returns>
	static inline mgl_bool_t mgl_f128_equal_e(mgl_f128_t lhs, mgl_f128_t rhs, mgl_f32_t epsilon)
	{
		mgl_f128_t eps = _mm_set1_ps(epsilon);
		mgl_f128_t abd = _mm_andnot_ps(_mm_set1_ps(-0.0f), _mm_sub_ps(lhs, rhs));
		return _mm_movemask_ps(_mm_cmplt_ps(abd, eps)) == 0xF;
	}

	/// <summary>
	///		Checks if two mgl_f128_t are different (roughly).
	/// </summary>
	/// <param name="lhs">Left mgl_f128_t</param>
	/// <param name="rhs">Right mgl_f128_t</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>MGL_FALSE if equal, otherwise equal</returns>
	static inline mgl_bool_t mgl_f128_nequal_e(mgl_f128_t lhs, mgl_f128_t rhs, mgl_f32_t epsilon)
	{
		mgl_f128_t eps = _mm_set1_ps(epsilon);
		mgl_f128_t abd = _mm_andnot_ps(_mm_set1_ps(-0.0f), _mm_sub_ps(lhs, rhs));
		return _mm_movemask_ps(_mm_cmplt_ps(abd, eps)) != 0xF;
	}

	/// <summary>
	///		Converts a scalar mgl_f128_t to a mgl_f32_t
	/// </summary>
	/// <param name="v">Scalar mgl_f128_t</param>
	/// <returns>mgl_f32_t</returns>
	static inline mgl_f32_t mgl_f128_to_f32(mgl_f128_t v)
	{
		return _mm_cvtss_f32(v);
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_BUILD_SSE
#endif // MGL_MATH_SIMD_H
