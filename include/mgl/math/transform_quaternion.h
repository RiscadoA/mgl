#ifndef MGL_MATH_TRANSFORM_QUATERNION_H
#define MGL_MATH_TRANSFORM_QUATERNION_H

#include <mgl/math/quaternion.h>
#include <mgl/math/vector4.h>
#include <mgl/math/scalar.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Generates a quaternion from an axis and an angle.
	/// </summary>
	/// <param name="angle">Angle (in radians)</param>
	/// <param name="x">Rotation axis X</param>
	/// <param name="y">Rotation axis Y</param>
	/// <param name="z">Rotation axis Z</param>
	/// <param name="r">Out result quaternion</param>
	inline void mgl_f32q4_angle_axis(mgl_f32_t angle, mgl_f32_t x, mgl_f32_t y, mgl_f32_t z, mgl_f32q4_t* r)
	{
		MGL_DEBUG_ASSERT(r != NULL);

		r->x = x * mgl_f32_sin(angle / 2.0f);
		r->y = y * mgl_f32_sin(angle / 2.0f);
		r->z = z * mgl_f32_sin(angle / 2.0f);
		r->s = mgl_f32_cos(angle / 2.0f);
	}

	/// <summary>
	///		Multiplies a 4 component vector by a quaternion.
	/// </summary>
	/// <param name="lhs">Quaternion</param>
	/// <param name="rhs">Vector</param>
	/// <param name="r">Out result vector</param>
	inline void mgl_f32q4_mul_v4(const mgl_f32q4_t* lhs, const mgl_f32v4_t* rhs, mgl_f32v4_t* r)
	{
		MGL_DEBUG_ASSERT(lhs != NULL && rhs != NULL && r != NULL);

		mgl_f32q4_t c;
		mgl_f32q4_conjugate(lhs, &c);
		mgl_f32q4_t qv;
		qv.x = rhs->x;
		qv.y = rhs->y;
		qv.z = rhs->z;
		qv.s = 0.0f;
		mgl_f32q4_mul(lhs, &qv, &qv);
		mgl_f32q4_mul(&qv, &c, &qv);
		r->x = qv.x;
		r->y = qv.y;
		r->z = qv.z;
		r->w = rhs->w;
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_TRANSFORM_QUATERNION_H
