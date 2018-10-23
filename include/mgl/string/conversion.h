#ifndef MGL_STRING_CONVERSION_H
#define MGL_STRING_CONVERSION_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Converts an unsigned 8-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_u8_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_u8_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an unsigned 16-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_u16_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_u16_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an unsigned 32-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_u32_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_u32_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an unsigned 64-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_u64_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_u64_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an signed 8-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_i8_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_i8_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an signed 16-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_i16_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_i16_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an signed 32-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_i32_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_i32_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an signed 64-bit value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_i64_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_i64_t value, mgl_u8_t base, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an 32-bit floating point value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="decimal_places">Number of decimal places to round to</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_f32_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_f32_t value, mgl_u8_t base, mgl_u64_t decimal_places, mgl_u64_t* out_size);

	/// <summary>
	///		Converts an 64-bit floating point value into a string.
	/// </summary>
	/// <param name="buffer">Buffer to store result in</param>
	/// <param name="buffer_size">Buffer size</param>
	/// <param name="value">Value to convert</param>
	/// <param name="base">Base (2-16)</param>
	/// <param name="decimal_places">Number of decimal places to round to</param>
	/// <param name="out_size">Out string size (optional, can be NULL)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_f64_to_str(mgl_u8_t* buffer, mgl_u64_t buffer_size, mgl_f64_t value, mgl_u8_t base, mgl_u64_t decimal_places, mgl_u64_t* out_size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_STRING_CONVERSION_H
