#ifndef MGL_MATH_QUATERNION_H
#define MGL_MATH_QUATERNION_H

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
			struct { mgl_f32_t s, x, y, z; };
			mgl_f32_t data[4];
		};
	} mgl_f32q4_t;

	/// <summary>
	///		Checks if two quaternions are equal to each other.
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternion</param>
	/// <returns>Returns MGL_FALSE if the quaternions are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32q4_equal(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs)
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
		if (lhs->s != rhs->s)
			return MGL_FALSE;
		return MGL_TRUE;
#endif
	}

	/// <summary>
	///		Checks if two quaternions are different from each other.
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternion</param>
	/// <returns>Returns MGL_FALSE if the quaternions are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32q4_nequal(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs)
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
		if (lhs->s != rhs->s)
			return MGL_TRUE;
		return MGL_FALSE;
#endif
	}

	/// <summary>
	///		Checks if two quaternions are equal to each other (roughly).
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternion</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>Returns MGL_FALSE if the quaternions are different, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32q4_equal_e(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32_t epsilon)
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
		dif = lhs->s - rhs->s;
		if (dif < -epsilon || dif > epsilon)
			return MGL_FALSE;
		return MGL_TRUE;
#endif
	}

	/// <summary>
	///		Checks if two quaternions are different from each other (roughly).
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternions</param>
	/// <param name="epsilon">Maximum difference</param>
	/// <returns>Returns MGL_FALSE if the quaternions are equal, otherwise returns MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32q4_nequal_e(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32_t epsilon)
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
		dif = lhs->s - rhs->s;
		if (dif < -epsilon || dif > epsilon)
			return MGL_TRUE;
		return MGL_FALSE;
#endif
	}

	/// <summary>
	///		Adds two quaternions.
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternion</param>
	/// <param name="r">Out result quaternion</param>
	inline mgl_f32q4_t mgl_f32q4_add(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32q4_t* r)
	{
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_add(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
#else
		r->s = lhs->s + rhs->s;
		r->x = lhs->x + rhs->x;
		r->y = lhs->y + rhs->y;
		r->z = lhs->z + rhs->z;
#endif
	}

	/// <summary>
	///		Subtracts two quaternions.
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternion</param>
	/// <param name="r">Out result quaternion</param>
	inline mgl_f32q4_t mgl_f32q4_sub(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32q4_t* r)
	{
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);
		lhs_128 = mgl_f128_sub(lhs_128, rhs_128);
		mgl_f128_store(lhs_128, r->data);
#else
		r->s = lhs->s - rhs->s;
		r->x = lhs->x - rhs->x;
		r->y = lhs->y - rhs->y;
		r->z = lhs->z - rhs->z;
#endif
	}

	/// <summary>
	///		Mutliplies two quaternions.
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternion</param>
	/// <param name="r">Out result quaternion</param>
	inline mgl_f32q4_t mgl_f32q4_mul(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32q4_t* r)
	{
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load(rhs->data);

		// TO DO
#else

#endif
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_QUATERNION_H
