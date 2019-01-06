#include <mgl/math/bezier_curve.h>
#include <mgl/math/scalar.h>

void MGL_API mgl_bezier_quad_2d(const mgl_point_2d_t* p0,
								const mgl_point_2d_t* p1,
								const mgl_point_2d_t* p2,
								mgl_f32_t t,
								mgl_point_2d_t* out)
{
	mgl_point_2d_t a, b;
	a.x = mgl_f32_lerp(p0->x, p1->x, t);
	a.y = mgl_f32_lerp(p0->y, p1->y, t);
	b.x = mgl_f32_lerp(p1->x, p2->x, t);
	b.y = mgl_f32_lerp(p1->y, p2->y, t);
	out->x = mgl_f32_lerp(a.x, b.x, t);
	out->y = mgl_f32_lerp(a.y, b.y, t);
}
