#ifndef MGL_MATH_BEZIER_CURVE_H
#define MGL_MATH_BEZIER_CURVE_H

#include <mgl/api_utils.h>
#include <mgl/math/point.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Calculates a point in a quad bezier curve.
	/// </summary>
	/// <param name="p0">First point</param>
	/// <param name="p1">Second point</param>
	/// <param name="p2">Third point</param>
	/// <param name="t">Interpolating value (from 0 to 1)</param>
	/// <param name="out">Out point</param>
	void MGL_API mgl_bezier_quad_2d(const mgl_point_2d_t* p0,
									const mgl_point_2d_t* p1,
									const mgl_point_2d_t* p2, 
									mgl_f32_t t,
									mgl_point_2d_t* out);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_BEZIER_CURVE_H
