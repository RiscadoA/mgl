#ifndef MGL_MATH_QUATERNION_H
#define MGL_MATH_QUATERNION_H

#ifdef MGL_MATH_USE_SIMD
#include <mgl/math/simd.h>
#endif

#include <mgl/math/scalar.h>
#include <mgl/type.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct MGL_ALIGNED(16)
	{
		union
		{
			struct { mgl_f32_t x, y, z, s; };
			mgl_f32_t data[4];
		};
	} mgl_f32q4_t;

	/// <summary>
	///		Checks if two quaternions are equal to each other.
	/// </summary>
	/// <param name="lhs">First quaternion</param>
	/// <param name="rhs">Second quaternion</param>
	/// <returns>Returns MGL_FALSE if the quaternions are different, otherwise returns MGL_TRUE</returns>
	static inline mgl_bool_t mgl_f32q4_equal(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load_aligned(rhs->data);
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
	static inline mgl_bool_t mgl_f32q4_nequal(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load_aligned(rhs->data);
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
	static inline mgl_bool_t mgl_f32q4_equal_e(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32_t epsilon)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load_aligned(rhs->data);
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
	static inline mgl_bool_t mgl_f32q4_nequal_e(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32_t epsilon)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load_aligned(rhs->data);
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
	static inline void mgl_f32q4_add(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32q4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);

#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load_aligned(rhs->data);
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
	static inline void mgl_f32q4_sub(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32q4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);

#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t lhs_128 = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t rhs_128 = mgl_f128_load_aligned(rhs->data);
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
	static inline void mgl_f32q4_mul(const mgl_f32q4_t* lhs, const mgl_f32q4_t* rhs, mgl_f32q4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);

#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t xyzw = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t abcd = mgl_f128_load_aligned(rhs->data);
		mgl_f128_t wzyx = mgl_f128_shuffle(xyzw, xyzw, MGL_SIMD_SHUFFLE(0, 1, 2, 3));
		mgl_f128_t baba = mgl_f128_shuffle(abcd, abcd, MGL_SIMD_SHUFFLE(0, 1, 0, 1));
		mgl_f128_t dcdc = mgl_f128_shuffle(abcd, abcd, MGL_SIMD_SHUFFLE(2, 3, 2, 3));

		mgl_f128_t ZnXWY = mgl_f128_hsub(mgl_f128_mul(xyzw, baba), mgl_f128_mul(wzyx, dcdc));
		mgl_f128_t XZYnW = mgl_f128_hadd(mgl_f128_mul(xyzw, dcdc), mgl_f128_mul(wzyx, baba));
		mgl_f128_t XZWY = mgl_f128_addsub(mgl_f128_shuffle(XZYnW, ZnXWY, MGL_SIMD_SHUFFLE(3, 2, 1, 0)),
										  mgl_f128_shuffle(ZnXWY, XZYnW, MGL_SIMD_SHUFFLE(2, 3, 0, 1)));

		mgl_f128_t rv = mgl_f128_shuffle(XZWY, XZWY, MGL_SIMD_SHUFFLE(2, 1, 3, 0));
		mgl_f128_store(rv, r->data);
#else
		mgl_f32q4_t t;
		t.s = lhs->s * rhs->s - lhs->x * rhs->x - lhs->y * rhs->y - lhs->z * rhs->z;
		t.x = lhs->s * rhs->x + lhs->x * rhs->s + lhs->y * rhs->z - lhs->z * rhs->y;
		t.y = lhs->s * rhs->y - lhs->x * rhs->z + lhs->y * rhs->s + lhs->z * rhs->x;
		t.z = lhs->s * rhs->z + lhs->x * rhs->y - lhs->y * rhs->x + lhs->z * rhs->s;
		*r = t;
#endif
	}

	/// <summary>
	///		Mutliplies a quaternion by a scalar.
	/// </summary>
	/// <param name="lhs">Quaternion</param>
	/// <param name="rhs">Scalar</param>
	/// <param name="r">Out result quaternion</param>
	static inline void mgl_f32q4_scale(const mgl_f32q4_t* lhs, mgl_f32_t rhs, mgl_f32q4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && r != NULL);

#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t xyzw = mgl_f128_load_aligned(lhs->data);
		mgl_f128_t ssss = mgl_f128_set_scalar(rhs);
		xyzw = mgl_f128_mul(xyzw, ssss);
		mgl_f128_store(xyzw, r->data);
#else
		r->x = lhs->x * rhs;
		r->y = lhs->y * rhs;
		r->z = lhs->z * rhs;
		r->s = lhs->s * rhs;
#endif
	}

	/// <summary>
	///		Gets the conjugate of a quaternion.
	/// </summary>
	/// <param name="q">Quaternion</param>
	/// <param name="r">Out result quaternion</param>
	static inline void mgl_f32q4_conjugate(const mgl_f32q4_t* q, mgl_f32q4_t* r)
	{
		MGL_DEBUG_ASSERT(q != NULL && r != NULL);
		r->x = -q->x;
		r->y = -q->y;
		r->z = -q->z;
		r->s = q->s;
	}

	/// <summary>
	///		Gets the norm squared of a quaternion.
	/// </summary>
	/// <param name="q">Quaternion</param>
	/// <returns>Norm squared</returns>
	static inline mgl_f32_t mgl_f32q4_norm_squared(const mgl_f32q4_t* q)
	{
		MGL_DEBUG_ASSERT(q != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t xyzs = mgl_f128_load_aligned(q->data);
		return mgl_f128_dot_scalar(xyzs, xyzs);
#else
		return mgl_f32_square(q->x) + mgl_f32_square(q->y) + mgl_f32_square(q->z) + mgl_f32_square(q->s);
#endif
	}

	/// <summary>
	///		Gets the norm of a quaternion.
	/// </summary>
	/// <param name="q">Quaternion</param>
	/// <returns>Norm</returns>
	static inline mgl_f32_t mgl_f32q4_norm(const mgl_f32q4_t* q)
	{
		MGL_DEBUG_ASSERT(q != NULL);
		return mgl_f32_sqrt(mgl_f32q4_norm_squared(q));
	}

	/// <summary>
	///		Normalizes a quaternion,
	/// </summary>
	/// <param name="q">Quaternion</param>
	/// <param name="r">Out result quaternion</param>
	static inline void mgl_f32q4_normalize(const mgl_f32q4_t* q, mgl_f32q4_t* r)
	{
		MGL_DEBUG_ASSERT(q != NULL && r != NULL);
#ifdef MGL_MATH_USE_SIMD
		mgl_f128_t xyzs = mgl_f128_load_aligned(q->data);
		mgl_f128_t nnnn = mgl_f128_set_scalar(mgl_f32q4_norm(q));
		xyzs = mgl_f128_div(xyzs, nnnn);
		mgl_f128_store(xyzs, r->data);
#else
		mgl_f32_t n = mgl_f32q4_norm(q);
		r->x = q->x / n;
		r->y = q->y / n;
		r->z = q->z / n;
		r->s = q->s / n;
#endif
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_QUATERNION_H
