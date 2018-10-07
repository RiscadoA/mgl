#ifndef MGL_MATH_TRIGONOMETRY_H
#define MGL_MATH_TRIGONOMETRY_H

#include <mgl/type.h>
#include <math.h>

#define MGL_PI 3.14159265359

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Calculates the absolute of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Absolute value</returns>
	inline mgl_f32_t mgl_f32_abs(mgl_f32_t x)
	{
		return fabsf(x);
	}

	/// <summary>
	///		Checks if two values are equal (roughly).
	/// </summary>
	/// <param name="x">X value</param>
	/// <param name="y">Y value</param>
	/// <param name="epsilon">Maximum diference</param>
	/// <returns>MGL_FALSE if they are different, otherwise MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32_equal_e(mgl_f32_t x, mgl_f32_t y, mgl_f32_t epsilon)
	{
		mgl_f32_t dif = y - x;
		return (dif >= -epsilon && dif <= epsilon);
	}

	/// <summary>
	///		Checks if two values are different (roughly).
	/// </summary>
	/// <param name="x">X value</param>
	/// <param name="y">Y value</param>
	/// <param name="epsilon">Maximum diference</param>
	/// <returns>MGL_FALSE if they are equal, otherwise MGL_TRUE</returns>
	inline mgl_bool_t mgl_f32_nequal_e(mgl_f32_t x, mgl_f32_t y, mgl_f32_t epsilon)
	{
		mgl_f32_t dif = y - x;
		return dif < -epsilon || dif > epsilon;
	}

	/// <summary>
	///		Converts degrees into radians.
	/// </summary>
	/// <param name="degrees">Angle in degrees</param>
	/// <returns>Angle in radians</returns>
	inline mgl_f32_t mgl_f32_deg_to_rad(mgl_f32_t degrees)
	{
		return degrees * (MGL_PI / 180.0f);
	}

	/// <summary>
	///		Converts radians into degrees.
	/// </summary>
	/// <param name="radians">Angle in radians</param>
	/// <returns>Angle in degrees</returns>
	inline mgl_f32_t mgl_f32_rad_to_deg(mgl_f32_t radians)
	{
		return (180 * radians) / MGL_PI;
	}

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

	/// <summary>
	///		Gets the natural logarithm of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Value natural logarithm</returns>
	inline mgl_f32_t mgl_f32_log(mgl_f32_t x)
	{
		return logf(x);
	}

	/// <summary>
	///		Gets the base 2 logarithm of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Value base 2 logarithm</returns>
	inline mgl_f32_t mgl_f32_log2(mgl_f32_t x)
	{
		return log2f(x);
	}

	/// <summary>
	///		Gets the base 10 logarithm of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Value base 10 logarithm</returns>
	inline mgl_f32_t mgl_f32_log10(mgl_f32_t x)
	{
		return log10f(x);
	}

	/// <summary>
	///		Gets the natural exponent of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Value natural exponent</returns>
	inline mgl_f32_t mgl_f32_exp(mgl_f32_t x)
	{
		return expf(x);
	}

	/// <summary>
	///		Gets the base 2 exponent of a value.
	/// </summary>
	/// <param name="x">Value</param>
	/// <returns>Value base 2 logarithm</returns>
	inline mgl_f32_t mgl_f32_exp2(mgl_f32_t x)
	{
		return exp2f(x);
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_MATH_TRIGONOMETRY_H
