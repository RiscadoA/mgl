#ifndef MGL_MATH_MATRIX4X4_H
#define MGL_MATH_MATRIX4X4_H

#ifdef MGL_MATH_USE_SIMD
#include <mgl/math/simd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		union
		{
			struct { mgl_f32_t x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3; };
			mgl_f32_t rows[4][4];
			mgl_f32_t data[16];
		};
	} mgl_f32m4x4_t;

	/// <summary>
	///		Sets a 4x4 matrix as identity.
	/// </summary>
	/// <param name="r">Out result matrix</param>
	inline void mgl_f32m4x4_identity(mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(r != NULL);

		r->rows[0][0] = 1.0f;
		r->rows[0][1] = 0.0f;
		r->rows[0][2] = 0.0f;
		r->rows[0][3] = 0.0f;
		r->rows[1][0] = 0.0f;
		r->rows[1][1] = 1.0f;
		r->rows[1][2] = 0.0f;
		r->rows[1][3] = 0.0f;
		r->rows[2][0] = 0.0f;
		r->rows[2][1] = 0.0f;
		r->rows[2][2] = 1.0f;
		r->rows[2][3] = 0.0f;
		r->rows[3][0] = 0.0f;
		r->rows[3][1] = 0.0f;
		r->rows[3][2] = 0.0f;
		r->rows[3][3] = 1.0f;
	}

	/// <summary>
	///		Muliplies two 4x4 matrices.
	/// </summary>
	/// <param name="lhs">First matrix</param>
	/// <param name="rhs">Second matrix</param>
	/// <param name="r">Out result matrix</param>
	inline void mgl_f32m4x4_mulmat(const mgl_f32m4x4_t* lhs, const mgl_f32m4x4_t* rhs, mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
	}

	/// <summary>
	///		Checks if two 4x4 matrices are equal to each other.
	/// </summary>
	/// <param name="lhs">First matrix</param>
	/// <param name="rhs">Second matrix</param>
	/// <returns>Returns MGL_FALSE if the matrices are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32m4x4_equal(const mgl_f32m4x4_t* lhs, const mgl_f32m4x4_t* rhs)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->rows[0]);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->rows[0]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_FALSE;
		lhs_128 = mgl_f128_load(lhs->rows[1]);
		rhs_128 = mgl_f128_load(rhs->rows[1]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_FALSE;
		lhs_128 = mgl_f128_load(lhs->rows[2]);
		rhs_128 = mgl_f128_load(rhs->rows[2]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_FALSE;
		lhs_128 = mgl_f128_load(lhs->rows[3]);
		rhs_128 = mgl_f128_load(rhs->rows[3]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_FALSE;
		return MGL_TRUE;
#else
		if (lhs->x0 != rhs->x0)
			return MGL_FALSE;
		if (lhs->y0 != rhs->y0)
			return MGL_FALSE;
		if (lhs->z0 != rhs->z0)
			return MGL_FALSE;
		if (lhs->w0 != rhs->w0)
			return MGL_FALSE;
		if (lhs->x1 != rhs->x1)
			return MGL_FALSE;
		if (lhs->y1 != rhs->y1)
			return MGL_FALSE;
		if (lhs->z1 != rhs->z1)
			return MGL_FALSE;
		if (lhs->w1 != rhs->w1)
			return MGL_FALSE;
		if (lhs->x2 != rhs->x2)
			return MGL_FALSE;
		if (lhs->y2 != rhs->y2)
			return MGL_FALSE;
		if (lhs->z2 != rhs->z2)
			return MGL_FALSE;
		if (lhs->w2 != rhs->w2)
			return MGL_FALSE;
		if (lhs->x3 != rhs->x3)
			return MGL_FALSE;
		if (lhs->y3 != rhs->y3)
			return MGL_FALSE;
		if (lhs->z3 != rhs->z3)
			return MGL_FALSE;
		if (lhs->w3 != rhs->w3)
			return MGL_FALSE;
		return MGL_TRUE;
#endif
	}

	/// <summary>
	///		Checks if two 4x4 matrices are different from each other.
	/// </summary>
	/// <param name="lhs">First matrix</param>
	/// <param name="rhs">Second matrix</param>
	/// <returns>Returns MGL_FALSE if the matrices are equal, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32m4x4_nequal(const mgl_f32m4x4_t* lhs, const mgl_f32m4x4_t* rhs)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->rows[0]);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->rows[0]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_TRUE;
		lhs_128 = mgl_f128_load(lhs->rows[1]);
		rhs_128 = mgl_f128_load(rhs->rows[1]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_TRUE;
		lhs_128 = mgl_f128_load(lhs->rows[2]);
		rhs_128 = mgl_f128_load(rhs->rows[2]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_TRUE;
		lhs_128 = mgl_f128_load(lhs->rows[3]);
		rhs_128 = mgl_f128_load(rhs->rows[3]);
		if (mgl_f128_nequal(lhs_128, rhs_128))
			return MGL_TRUE;
		return MGL_FALSE;
#else
		if (lhs->x0 != rhs->x0)
			return MGL_TRUE;
		if (lhs->y0 != rhs->y0)
			return MGL_TRUE;
		if (lhs->z0 != rhs->z0)
			return MGL_TRUE;
		if (lhs->w0 != rhs->w0)
			return MGL_TRUE;
		if (lhs->x1 != rhs->x1)
			return MGL_TRUE;
		if (lhs->y1 != rhs->y1)
			return MGL_TRUE;
		if (lhs->z1 != rhs->z1)
			return MGL_TRUE;
		if (lhs->w1 != rhs->w1)
			return MGL_TRUE;
		if (lhs->x2 != rhs->x2)
			return MGL_TRUE;
		if (lhs->y2 != rhs->y2)
			return MGL_TRUE;
		if (lhs->z2 != rhs->z2)
			return MGL_TRUE;
		if (lhs->w2 != rhs->w2)
			return MGL_TRUE;
		if (lhs->x3 != rhs->x3)
			return MGL_TRUE;
		if (lhs->y3 != rhs->y3)
			return MGL_TRUE;
		if (lhs->z3 != rhs->z3)
			return MGL_TRUE;
		if (lhs->w3 != rhs->w3)
			return MGL_TRUE;
		return MGL_FALSE;
#endif
	}

	/// <summary>
	///		Checks if two 4x4 matrices are equal to each other (roughly).
	/// </summary>
	/// <param name="lhs">First matrix</param>
	/// <param name="rhs">Second matrix</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>Returns MGL_FALSE if the matrices are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32m4x4_equal_e(const mgl_f32m4x4_t* lhs, const mgl_f32m4x4_t* rhs, mgl_f32_t epsilon)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->rows[0]);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->rows[0]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_FALSE;
		lhs_128 = mgl_f128_load(lhs->rows[1]);
		rhs_128 = mgl_f128_load(rhs->rows[1]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_FALSE;
		lhs_128 = mgl_f128_load(lhs->rows[2]);
		rhs_128 = mgl_f128_load(rhs->rows[2]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_FALSE;
		lhs_128 = mgl_f128_load(lhs->rows[3]);
		rhs_128 = mgl_f128_load(rhs->rows[3]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_FALSE;
		return MGL_TRUE;
#else
		mgl_f32_t dif = lhs->x0 - rhs->x0; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->x1 - rhs->x1; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->x2 - rhs->x2; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->x3 - rhs->x3; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->y0 - rhs->y0; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->y1 - rhs->y1; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->y2 - rhs->y2; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->y3 - rhs->y3; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->z0 - rhs->z0; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->z1 - rhs->z1; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->z2 - rhs->z2; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->z3 - rhs->z3; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->w0 - rhs->w0; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->w1 - rhs->w1; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->w2 - rhs->w2; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		dif = lhs->w3 - rhs->w3; if (dif < -epsilon || dif > epsilon) return MGL_FALSE;
		return MGL_TRUE;
#endif
	}

	/// <summary>
	///		Checks if two 4x4 matrices are different from each other (roughly).
	/// </summary>
	/// <param name="lhs">First matrix</param>
	/// <param name="rhs">Second matrix</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>Returns MGL_FALSE if the matrices are equal, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32m4x4_nequal_e(const mgl_f32m4x4_t* lhs, const mgl_f32m4x4_t* rhs, mgl_f32_t epsilon)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->rows[0]);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->rows[0]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_TRUE;
		lhs_128 = mgl_f128_load(lhs->rows[1]);
		rhs_128 = mgl_f128_load(rhs->rows[1]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_TRUE;
		lhs_128 = mgl_f128_load(lhs->rows[2]);
		rhs_128 = mgl_f128_load(rhs->rows[2]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_TRUE;
		lhs_128 = mgl_f128_load(lhs->rows[3]);
		rhs_128 = mgl_f128_load(rhs->rows[3]);
		if (mgl_f128_nequal_e(lhs_128, rhs_128, epsilon))
			return MGL_TRUE;
		return MGL_FALSE;
#else
		mgl_f32_t dif = lhs->x0 - rhs->x0; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->x1 - rhs->x1; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->x2 - rhs->x2; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->x3 - rhs->x3; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->y0 - rhs->y0; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->y1 - rhs->y1; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->y2 - rhs->y2; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->y3 - rhs->y3; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->z0 - rhs->z0; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->z1 - rhs->z1; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->z2 - rhs->z2; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->z3 - rhs->z3; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->w0 - rhs->w0; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->w1 - rhs->w1; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->w2 - rhs->w2; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		dif = lhs->w3 - rhs->w3; if (dif < -epsilon || dif > epsilon) return MGL_TRUE;
		return MGL_FALSE;
#endif
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_MATRIX4X4_H
