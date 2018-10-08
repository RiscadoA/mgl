#ifndef MGL_MATH_VECTOR_H
#define MGL_MATH_VECTOR_H

#ifdef MGL_MATH_USE_SIMD
#include <mgl/math/simd.h>
#endif

#include <mgl/type.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		union
		{
			struct { mgl_f32_t x, y, z, w; };
			mgl_f32_t data[4];
		};
	} mgl_f32v4_t;

	/// <summary>
	///		Adds two vectors (only the first three components, the fourth component is set to 1.0f, always).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32v4_add3(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_add(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
		r->w = 1.0f;
#else
		r->x = lhs->x + rhs->x;
		r->y = lhs->y + rhs->y;
		r->z = lhs->z + rhs->z;
		r->w = 1.0f;
#endif
	}

	/// <summary>
	///		Adds two vectors (all components).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32v4_add4(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_add(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
#else
		r->x = lhs->x + rhs->x;
		r->y = lhs->y + rhs->y;
		r->z = lhs->z + rhs->z;
		r->w = lhs->w + rhs->w;
#endif
	}

	/// <summary>
	///		Subtracts two vectors (only the first three components, the fourth component is set to 0.0f, always).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32v4_sub3(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_sub(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
		r->w = 0.0f;
#else
		r->x = lhs->x - rhs->x;
		r->y = lhs->y - rhs->y;
		r->z = lhs->z - rhs->z;
		r->w = 0.0f;
#endif
	}

	/// <summary>
	///		Subtracts two vectors (all components).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32v4_sub4(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_sub(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
#else
		r->x = lhs->x - rhs->x;
		r->y = lhs->y - rhs->y;
		r->z = lhs->z - rhs->z;
		r->w = lhs->w - rhs->w;
#endif
	}

	/// <summary>
	///		Multiplies two vectors (all components).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32v4_mul(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_mul(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
#else
		r->x = lhs->x * rhs->x;
		r->y = lhs->y * rhs->y;
		r->z = lhs->z * rhs->z;
		r->w = lhs->w * rhs->w;
#endif
	}

	/// <summary>
	///		Divides two vectors (all components).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32v4_div(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_div(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
#else
		r->x = lhs->x / rhs->x;
		r->y = lhs->y / rhs->y;
		r->z = lhs->z / rhs->z;
		r->w = lhs->w / rhs->w;
#endif
	}

	/// <summary>
	///		Checks if two vectors are equal to each other.
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <returns>Returns MGL_FALSE if the vectors are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32v4_equal(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		return mgl_f128_equal(lhs_128, rhs_128);
#else
		if (lhs->x != rhs->x)
			return MGL_FALSE;
		if (lhs->y != rhs->y)
			return MGL_FALSE;
		if (lhs->z != rhs->z)
			return MGL_FALSE;
		if (lhs->w != rhs->w)
			return MGL_FALSE;
		return MGL_TRUE;
#endif
	}

	/// <summary>
	///		Checks if two vectors are different from each other.
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <returns>Returns MGL_FALSE if the vectors are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32v4_nequal(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		return mgl_f128_nequal(lhs_128, rhs_128);
#else
		if (lhs->x != rhs->x)
			return MGL_TRUE;
		if (lhs->y != rhs->y)
			return MGL_TRUE;
		if (lhs->z != rhs->z)
			return MGL_TRUE;
		if (lhs->w != rhs->w)
			return MGL_TRUE;
		return MGL_FALSE;
#endif
	}

	/// <summary>
	///		Checks if two vectors are equal to each other (roughly).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>Returns MGL_FALSE if the vectors are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32v4_equal_e(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32_t epsilon)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		return mgl_f128_equal_e(lhs_128, rhs_128, epsilon);
#else
		mgl_f32_t dif = lhs->x - rhs->x;
		if (dif < -epsilon || dif > epsilon)
			return MGL_FALSE;
		dif = lhs->y - rhs->y;
		if (dif < -epsilon || dif > epsilon)
			return MGL_FALSE;
		dif = lhs->z - rhs->z;
		if (dif < -epsilon || dif > epsilon)
			return MGL_FALSE;
		dif = lhs->w - rhs->w;
		if (dif < -epsilon || dif > epsilon)
			return MGL_FALSE;
		return MGL_TRUE;
#endif
	}

	/// <summary>
	///		Checks if two vectors are different from each other (roughly).
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>Returns MGL_FALSE if the vectors are equal, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32v4_nequal_e(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32_t epsilon)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		return mgl_f128_equal_e(lhs_128, rhs_128, epsilon);
#else
		mgl_f32_t dif = lhs->x - rhs->x;
		if (dif < -epsilon || dif > epsilon)
			return MGL_TRUE;
		dif = lhs->y - rhs->y;
		if (dif < -epsilon || dif > epsilon)
			return MGL_TRUE;
		dif = lhs->z - rhs->z;
		if (dif < -epsilon || dif > epsilon)
			return MGL_TRUE;
		dif = lhs->w - rhs->w;
		if (dif < -epsilon || dif > epsilon)
			return MGL_TRUE;
		return MGL_FALSE;
#endif
	}

	/// <summary>
	///		Calculates the cross product between two vectors.
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32v4_cross(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_cross(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
#else
		r->x = lhs->y * rhs->z - lhs->z * rhs->y;
		r->y = lhs->z * rhs->x - lhs->x * rhs->z;
		r->z = lhs->x * rhs->y - lhs->y * rhs->x;
		r->w = 0.0f;
#endif
	}

	/// <summary>
	///		Calculates the dot product between two vectors.
	/// </summary>
	/// <param name="lhs">First vector</param>
	/// <param name="rhs">Second vector</param>
	/// <returns>Result</returns>
	inline mgl_f32_t mgl_f32v4_dot(const mgl_f32v4_t* lhs, const mgl_f32v4_t* rhs)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		return mgl_f128_dot_scalar(lhs_128, rhs_128);
#else
		return lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z;
#endif
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_VECTOR_H
