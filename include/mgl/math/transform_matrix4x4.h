#ifndef MGL_MATH_TRANSFORM4X4_H
#define MGL_MATH_TRANSFORM4X4_H

#include <mgl/math/matrix4x4.h>
#include <mgl/math/vector4.h>
#include <mgl/math/scalar.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Multiplies a 4 component vector by a 4x4 matrix.
	/// </summary>
	/// <param name="lhs">Matrix</param>
	/// <param name="rhs">Vector</param>
	/// <param name="r">Out result vector</param>
	static inline void mgl_f32m4x4_mul_v4(const mgl_f32m4x4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);

#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_0 = mgl_f128_load_aligned(lhs->cols[0]);
		mgl_f128_t lhs_1 = mgl_f128_load_aligned(lhs->cols[1]);
		mgl_f128_t lhs_2 = mgl_f128_load_aligned(lhs->cols[2]);
		mgl_f128_t lhs_3 = mgl_f128_load_aligned(lhs->cols[3]);
		mgl_f128_t rhs_0 = mgl_f128_load_aligned(rhs->data);

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

	/// <summary>
	///		Generates a 4x4 matrix that scales a vector.
	/// </summary>
	/// <param name="x">X scale</param>
	/// <param name="y">Y scale</param>
	/// <param name="z">Z scale</param>
	/// <param name="r">Out result matrix</param>
	static inline void mgl_f32m4x4_scale(mgl_f32_t x, mgl_f32_t y, mgl_f32_t z, mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(r != NULL);

		r->cols[0][0] = x;
		r->cols[0][1] = 0.0f;
		r->cols[0][2] = 0.0f;
		r->cols[0][3] = 0.0f;
		r->cols[1][0] = 0.0f;
		r->cols[1][1] = y;
		r->cols[1][2] = 0.0f;
		r->cols[1][3] = 0.0f;
		r->cols[2][0] = 0.0f;
		r->cols[2][1] = 0.0f;
		r->cols[2][2] = z;
		r->cols[2][3] = 0.0f;
		r->cols[3][0] = 0.0f;
		r->cols[3][1] = 0.0f;
		r->cols[3][2] = 0.0f;
		r->cols[3][3] = 1.0f;
	}

	/// <summary>
	///		Generates a 4x4 matrix that translates a vector.
	/// </summary>
	/// <param name="x">X translation</param>
	/// <param name="y">Y translation</param>
	/// <param name="z">Z translation</param>
	/// <param name="r">Out result matrix</param>
	static inline void mgl_f32m4x4_translate(mgl_f32_t x, mgl_f32_t y, mgl_f32_t z, mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(r != NULL);

		r->cols[0][0] = 1.0f;
		r->cols[0][1] = 0.0f;
		r->cols[0][2] = 0.0f;
		r->cols[0][3] = x;
		r->cols[1][0] = 0.0f;
		r->cols[1][1] = 1.0f;
		r->cols[1][2] = 0.0f;
		r->cols[1][3] = y;
		r->cols[2][0] = 0.0f;
		r->cols[2][1] = 0.0f;
		r->cols[2][2] = 1.0f;
		r->cols[2][3] = z;
		r->cols[3][0] = 0.0f;
		r->cols[3][1] = 0.0f;
		r->cols[3][2] = 0.0f;
		r->cols[3][3] = 1.0f;
	}

	/// <summary>
	///		Generates a 4x4 matrix that rotates a vector in the X axis (YZ plane).
	/// </summary>
	/// <param name="angle">Rotation angle in radians</param>
	/// <param name="r">Out result matrix</param>
	static inline void mgl_f32m4x4_rotate_x(mgl_f32_t angle, mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(r != NULL);

		r->cols[0][0] = 1.0f;
		r->cols[0][1] = 0.0f;
		r->cols[0][2] = 0.0f;
		r->cols[0][3] = 0.0f;
		r->cols[1][0] = 0.0f;
		r->cols[1][1] = mgl_f32_cos(angle);
		r->cols[1][2] = mgl_f32_sin(angle);
		r->cols[1][3] = 0.0f;
		r->cols[2][0] = 0.0f;
		r->cols[2][1] = -mgl_f32_sin(angle);
		r->cols[2][2] = mgl_f32_cos(angle);
		r->cols[2][3] = 0.0f;
		r->cols[3][0] = 0.0f;
		r->cols[3][1] = 0.0f;
		r->cols[3][2] = 0.0f;
		r->cols[3][3] = 1.0f;
	}

	/// <summary>
	///		Generates a 4x4 matrix that rotates a vector in the Y axis (XZ plane).
	/// </summary>
	/// <param name="angle">Rotation angle in radians</param>
	/// <param name="r">Out result matrix</param>
	static inline void mgl_f32m4x4_rotate_y(mgl_f32_t angle, mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(r != NULL);

		r->cols[0][0] = mgl_f32_cos(angle);
		r->cols[0][1] = 0.0f;
		r->cols[0][2] = -mgl_f32_sin(angle);
		r->cols[0][3] = 0.0f;
		r->cols[1][0] = 0.0f;
		r->cols[1][1] = 1.0f;
		r->cols[1][2] = 0.0f;
		r->cols[1][3] = 0.0f;
		r->cols[2][0] = mgl_f32_sin(angle);
		r->cols[2][1] = 0.0f;
		r->cols[2][2] = mgl_f32_cos(angle);
		r->cols[2][3] = 0.0f;
		r->cols[3][0] = 0.0f;
		r->cols[3][1] = 0.0f;
		r->cols[3][2] = 0.0f;
		r->cols[3][3] = 1.0f;
	}

	/// <summary>
	///		Generates a 4x4 matrix that rotates a vector in the Z axis (XY plane).
	/// </summary>
	/// <param name="angle">Rotation angle in radians</param>
	/// <param name="r">Out result matrix</param>
	static inline void mgl_f32m4x4_rotate_z(mgl_f32_t angle, mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(r != NULL);

		r->cols[0][0] = mgl_f32_cos(angle);
		r->cols[0][1] = mgl_f32_sin(angle);
		r->cols[0][2] = 0.0f;
		r->cols[0][3] = 0.0f;
		r->cols[1][0] = -mgl_f32_sin(angle);
		r->cols[1][1] = mgl_f32_cos(angle);
		r->cols[1][2] = 0.0f;
		r->cols[1][3] = 0.0f;
		r->cols[2][0] = 0.0f;
		r->cols[2][1] = 0.0f;
		r->cols[2][2] = 1.0f;
		r->cols[2][3] = 0.0f;
		r->cols[3][0] = 0.0f;
		r->cols[3][1] = 0.0f;
		r->cols[3][2] = 0.0f;
		r->cols[3][3] = 1.0f;
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_TRANSFORM4X4_H
