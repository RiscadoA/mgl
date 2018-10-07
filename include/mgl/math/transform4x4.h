#ifndef MGL_MATH_TRANSFORM4X4_H
#define MGL_MATH_TRANSFORM4X4_H

#include <mgl/math/matrix4x4.h>
#include <mgl/math/vector4.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Multiplies a 4 component vector by a 4x4 matrix.
	/// </summary>
	/// <param name="lhs">Matrix</param>
	/// <param name="rhs">Vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32m4x4_mulvec(const mgl_f32m4x4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);

#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_0 = mgl_f128_load(lhs->cols[0]);
		mgl_f128_t lhs_1 = mgl_f128_load(lhs->cols[1]);
		mgl_f128_t lhs_2 = mgl_f128_load(lhs->cols[2]);
		mgl_f128_t lhs_3 = mgl_f128_load(lhs->cols[3]);
		mgl_f128_t rhs_0 = mgl_f128_load(rhs->data);

		lhs_0 = mgl_f128_mul(lhs_0, rhs_0);
		lhs_1 = mgl_f128_mul(lhs_1, rhs_0);
		lhs_2 = mgl_f128_mul(lhs_2, rhs_0);
		lhs_3 = mgl_f128_mul(lhs_3, rhs_0);

		rhs_0 = mgl_f128_hadd(mgl_f128_hadd(lhs_0, lhs_1), mgl_f128_hadd(lhs_2, lhs_3));
		mgl_f128_store(rhs_0, r->data);
#else
		for (mgl_u32_t i = 0; i < 4; ++i)
		{
			r->data[i] = 0.0f;
			for (mgl_u32_t n = 0; n < 4; ++n)
				r->data[i] += rhs->data[n] * lhs->cols[i][n];
		}
#endif
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_TRANSFORM4X4_H
