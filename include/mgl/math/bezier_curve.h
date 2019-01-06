#ifndef MGL_MATH_BEZIER_CURVE_H
#define MGL_MATH_BEZIER_CURVE_H

#include <mgl/api_utils.h>
#include <mgl/math/point.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_point_2d_t p0;
		mgl_point_2d_t p1;
		mgl_point_2d_t p2;
	} mgl_bq_spline_t;

	/// <summary>
	///		Calculates a point in a quad bezier curve.
	/// </summary>
	/// <param name="spline">Spline</param>
	/// <param name="t">Interpolating value (from 0 to 1)</param>
	/// <param name="out">Out point</param>
	void MGL_API mgl_bezier_quad_2d_point(const mgl_bq_spline_t* spline,
										  mgl_f32_t t,
										  mgl_point_2d_t* out);

	/// <summary>
	///		Calculates the distance of a point to a quad bezier curve.
	/// </summary>
	/// <param name="spline">Spline</param>
	/// <param name="p">Point</param>
	/// <returns>Distance squared</returns>
	mgl_f32_t MGL_API mgl_bezier_quad_2d_dist(const mgl_bq_spline_t* spline,
											  const mgl_point_2d_t* p);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_BEZIER_CURVE_H
