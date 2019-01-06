#include <mgl/math/bezier_curve.h>
#include <mgl/math/scalar.h>

void MGL_API mgl_bezier_quad_2d_point(const mgl_bq_spline_t* spline,
									  mgl_f32_t t,
									  mgl_point_2d_t* out)
{
	mgl_point_2d_t a, b;
	a.x = mgl_f32_lerp(spline->p0.x, spline->p1.x, t);
	a.y = mgl_f32_lerp(spline->p0.y, spline->p1.y, t);
	b.x = mgl_f32_lerp(spline->p1.x, spline->p2.x, t);
	b.y = mgl_f32_lerp(spline->p1.y, spline->p2.y, t);
	out->x = mgl_f32_lerp(a.x, b.x, t);
	out->y = mgl_f32_lerp(a.y, b.y, t);
}

mgl_f32_t MGL_API mgl_bezier_quad_2d_dist(const mgl_bq_spline_t * spline, const mgl_point_2d_t * p)
{
	return 0.0f;
}
