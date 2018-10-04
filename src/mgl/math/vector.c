#include <mgl/math/vector.h>
#include <smmintrin.h>

MGL_API mgl_f32v4_t mgl_f32v4_load(const mgl_f32_t value[4])
{
	return _mm_loadu_ps(value);
}

MGL_API mgl_f32v4_t mgl_f32v4_load_aligned(const mgl_f32_t value[4])
{
	return _mm_load_ps(value);
}

MGL_API void mgl_f32v4_store(const mgl_f32v4_t * v, mgl_f32_t value[4])
{
	_mm_storeu_ps(value, *v);
}

MGL_API void mgl_f32v4_store_aligned(const mgl_f32v4_t * v, mgl_f32_t value[4])
{
	_mm_store_ps(value, *v);
}

MGL_API mgl_f32v4_t mgl_f32v4_set(mgl_f32_t x, mgl_f32_t y, mgl_f32_t z, mgl_f32_t w)
{
	return _mm_setr_ps(x, y, z, w);
}

MGL_API mgl_f32v4_t mgl_f32v4_add(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	return _mm_add_ps(lhs, rhs);
}

MGL_API mgl_f32v4_t mgl_f32v4_sub(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	return _mm_sub_ps(lhs, rhs);
}

MGL_API mgl_f32v4_t mgl_f32v4_mul(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	return _mm_mul_ps(lhs, rhs);
}

MGL_API mgl_f32v4_t mgl_f32v4_div(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	return _mm_div_ps(lhs, rhs);
}

MGL_API mgl_f32v4_t mgl_f32v4_min(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	return _mm_min_ps(lhs, rhs);
}

MGL_API mgl_f32v4_t mgl_f32v4_max(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	return _mm_max_ps(lhs, rhs);
}

MGL_API mgl_f32v4_t mgl_f32v4_sqrt(mgl_f32v4_t v)
{
	return _mm_sqrt_ps(v);
}

MGL_API mgl_f32v4_t mgl_f32v4_rsqrt(mgl_f32v4_t v)
{
	return _mm_rsqrt_ps(v);
}

MGL_API mgl_f32v4_t mgl_f32v4_rcp(mgl_f32v4_t v)
{
	return _mm_rcp_ps(v);
}

MGL_API mgl_f32v4_t mgl_f32v4_cross(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	// TO DO
}

MGL_API mgl_f32_t mgl_f32v4_dot(mgl_f32v4_t lhs, mgl_f32v4_t rhs)
{
	// TO DO
}
