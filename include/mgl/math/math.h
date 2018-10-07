#ifndef MGL_MATH_TRIGONOMETRY_H
#define MGL_MATH_TRIGONOMETRY_H

#include <mgl/type.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Calculates the cosine of an angle in radians.
	/// </summary>
	/// <param name="angle">Angle in radians</param>
	/// <returns>Cosine value</returns>
	inline mgl_f32_t mgl_f32_cos(mgl_f32_t angle)
	{
		return cosf(angle);
	}

	/// <summary>
	///		Calculates the sine of an angle in radians.
	/// </summary>
	/// <param name="angle">Angle in radians</param>
	/// <returns>Sine value</returns>
	inline mgl_f32_t mgl_f32_sin(mgl_f32_t angle)
	{
		return sinf(angle);
	}

	/// <summary>
	///		Calculates the tangent of an angle in radians.
	/// </summary>
	/// <param name="angle">Angle in radians</param>
	/// <returns>Tangent value</returns>
	inline mgl_f32_t mgl_f32_tan(mgl_f32_t angle)
	{
		return tanf(angle);
	}

	/// <summary>
	///		Calculates the arc of the cosine of an angle in radians.
	/// </summary>
	/// <param name="angle">Angle in radians</param>
	/// <returns>Arc cosine value</returns>
	inline mgl_f32_t mgl_f32_acos(mgl_f32_t angle)
	{
		return acosf(angle);
	}

	/// <summary>
	///		Calculates the arc of the sine of an angle in radians.
	/// </summary>
	/// <param name="angle">Angle in radians</param>
	/// <returns>Arc sine value</returns>
	inline mgl_f32_t mgl_f32_asin(mgl_f32_t angle)
	{
		return asinf(angle);
	}

	/// <summary>
	///		Calculates the arc of the tangent of an angle in radians.
	/// </summary>
	/// <param name="angle">Angle in radians</param>
	/// <returns>Arc tangent value</returns>
	inline mgl_f32_t mgl_f32_atan(mgl_f32_t angle)
	{
		return atanf(angle);
	}

	/// <summary>
	///		Calculates the power of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <param name="y">Power</param>
	/// <returns>Value square</returns>
	inline mgl_f32_t mgl_f32_pow(mgl_f32_t x, mgl_f32_t y)
	{
		return powf(x, y);
	}

	/// <summary>
	///		Squares a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Value square</returns>
	inline mgl_f32_t mgl_f32_square(mgl_f32_t x)
	{
		return x * x;
	}

	/// <summary>
	///		Calculates the square root of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Value square root</returns>
	inline mgl_f32_t mgl_f32_sqrt(mgl_f32_t x)
	{
		return sqrtf(x);
	}

	/// <summary>
	///		Calculates the square of the distance between 2 1D points.
	/// </summary>
	/// <param name="x0">Point 0 X position</param>
	/// <param name="x1">Point 1 X position</param>
	/// <returns>Distance squared</returns>
	inline mgl_f32_t mgl_f32_distance_1d(mgl_f32_t x0, mgl_f32_t x1)
	{
		return mgl_f32_square(x1 - x0);
	}

	/// <summary>
	///		Calculates the square of the distance between 2 2D points.
	/// </summary>
	/// <param name="x0">Point 0 X position</param>
	/// <param name="y0">Point 0 Y position</param>
	/// <param name="x1">Point 1 X position</param>
	/// <param name="y1">Point 1 Y position</param>
	/// <returns>Distance squared</returns>
	inline mgl_f32_t mgl_f32_distance_2d(mgl_f32_t x0, mgl_f32_t y0, mgl_f32_t x1, mgl_f32_t y1)
	{
		return mgl_f32_square(x1 - x0) + mgl_f32_square(y1 - y0);
	}

	/// <summary>
	///		Calculates the square of the distance between 2 3D points.
	/// </summary>
	/// <param name="x0">Point 0 X position</param>
	/// <param name="y0">Point 0 Y position</param>
	/// <param name="z0">Point 0 Z position</param>
	/// <param name="x1">Point 1 X position</param>
	/// <param name="y1">Point 1 Y position</param>
	/// <param name="z1">Point 1 Z position</param>
	/// <returns>Distance squared</returns>
	inline mgl_f32_t mgl_f32_distance_3d(mgl_f32_t x0, mgl_f32_t y0, mgl_f32_t z0, mgl_f32_t x1, mgl_f32_t y1, mgl_f32_t z1)
	{
		return mgl_f32_square(x1 - x0) + mgl_f32_square(y1 - y0) + mgl_f32_square(z1 - z0);
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_TRIGONOMETRY_H
