#ifndef MGL_MATH_POINT_H
#define MGL_MATH_POINT_H

#include <mgl/type.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


	typedef struct
	{
		mgl_f32_t x, y;
	} mgl_point_2d_t;

	typedef struct
	{
		mgl_f32_t x, y, z;
	} mgl_point_3d_t;

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_POINT_H
