#ifndef MGL_MATH_QUATERNION_MATRIX4X4_H
#define MGL_MATH_QUATERNION_MATRIX4X4_H

#include <mgl/math/quaternion.h>
#include <mgl/math/matrix4x4.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Converts a quaternion into a 4x4 rotation matrix.
	/// </summary>
	/// <param name="q">Quaternion</param>
	/// <param name="r">Out result matrix</param>
	inline void mgl_f32q4_to_m4x4(const mgl_f32q4_t* q, mgl_f32m4x4_t* r)
	{
		MGL_DEBUG_ASSERT(q != NULL && r != NULL);

		mgl_f32_t x2 = q->x * 2.0f;
		mgl_f32_t y2 = q->y * 2.0f;
		mgl_f32_t z2 = q->z * 2.0f;

		{
			mgl_f32_t xx2 = q->x * x2;
			mgl_f32_t yy2 = q->y * y2;
			mgl_f32_t zz2 = q->z * z2;

			r->x0 = 1.0f - yy2 - zz2;
			r->y1 = 1.0f - xx2 - zz2;
			r->z2 = 1.0f - xx2 - yy2;
		}

		{
			mgl_f32_t yz2 = q->y * z2;
			mgl_f32_t sx2 = q->s * x2;

			r->z1 = yz2 - sx2;
			r->y2 = yz2 + sx2;
		}

		{
			mgl_f32_t xy2 = q->x * y2;
			mgl_f32_t sz2 = q->s * z2;

			r->y0 = xy2 - sz2;
			r->x1 = xy2 + sz2;
		}

		{
			mgl_f32_t xz2 = q->x * z2;
			mgl_f32_t sy2 = q->s * y2;

			r->x2 = xz2 - sy2;
			r->z0 = xz2 + sy2;
		}

		r->x3 = 0.0f;
		r->y3 = 0.0f;
		r->z3 = 0.0f;
		r->w3 = 1.0f;
		r->w0 = 0.0f;
		r->w1 = 0.0f;
		r->w2 = 0.0f;
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_QUATERNION_MATRIX4X4_H
