#ifndef MGL_MATH_PERLIN_NOISE_H
#define MGL_MATH_PERLIN_NOISE_H

#include <mgl/api_utils.h>
#include <mgl/math/scalar.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	mgl_f64_t MGL_API mgl_perlin_noise_2d(mgl_f64_t x, mgl_f64_t y, mgl_i64_t seed);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_PERLIN_NOISE_H
