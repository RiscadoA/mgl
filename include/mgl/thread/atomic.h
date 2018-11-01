#ifndef MGL_THREAD_ATOMIC_H
#define MGL_THREAD_ATOMIC_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_ATOMIC_I8_SIZE 4
#define MGL_ATOMIC_I16_SIZE 6
#define MGL_ATOMIC_I32_SIZE 8

	/// <summary>
	///		Contains information about an atomic signed 8 bit integer.
	///		Do not access members directly.
	/// </summary>
	typedef struct { mgl_u8_t data[MGL_ATOMIC_I8_SIZE]; } mgl_atomic_i8_t;

	/// <summary>
	///		Contains information about an atomic signed 16 bit integer.
	///		Do not access members directly.
	/// </summary>
	typedef struct { mgl_u8_t data[MGL_ATOMIC_I16_SIZE]; } mgl_atomic_i16_t;

	/// <summary>
	///		Contains information about an atomic signed 32 bit integer.
	///		Do not access members directly.
	/// </summary>
	typedef struct { mgl_u8_t data[MGL_ATOMIC_I32_SIZE]; } mgl_atomic_i32_t;

	/// <summary>
	///		Stores a value on a signed 8 bit integer atomic variable.
	/// </summary>
	/// <param name="dst">Destination atomic</param>
	/// <param name="src">Source value</param>
	void MGL_API mgl_store_atomic_i8(mgl_atomic_i8_t* dst, mgl_i8_t src);
	
	/// <summary>
	///		Loads a value from a signed 8 bit integer atomic variable.
	/// </summary>
	/// <param name="src">Source atomic</param>
	/// <returns>Atomic value</returns>
	mgl_i8_t MGL_API mgl_load_atomic_i8(mgl_atomic_i8_t* src);

	/// <summary>
	///		ANDs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_and_atomic_i8(mgl_atomic_i8_t* dst, mgl_i8_t value);

	/// <summary>
	///		ORs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_or_atomic_i8(mgl_atomic_i8_t* dst, mgl_i8_t value);

	/// <summary>
	///		XORs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_xor_atomic_i8(mgl_atomic_i8_t* dst, mgl_i8_t value);

	/// <summary>
	///		Stores a value on a signed 16 bit integer atomic variable.
	/// </summary>
	/// <param name="dst">Destination atomic</param>
	/// <param name="src">Source value</param>
	void MGL_API mgl_store_atomic_i16(mgl_atomic_i16_t* dst, mgl_i16_t src);
	
	/// <summary>
	///		Loads a value from a signed 16 bit integer atomic variable.
	/// </summary>
	/// <param name="src">Source atomic</param>
	/// <returns>Atomic value</returns>
	mgl_i16_t MGL_API mgl_load_atomic_i16(mgl_atomic_i16_t* src);

	/// <summary>
	///		Increments an atomic.
	/// </summary>
	/// <param name="dst">Destination atomic</param>
	/// <returns>New value</returns>
	mgl_i16_t MGL_API mgl_increment_atomic_i16(mgl_atomic_i16_t* dst);

	/// <summary>
	///		Increments an atomic.
	/// </summary>
	/// <param name="dst">Destination atomic</param>
	/// <returns>New value</returns>
	mgl_i16_t MGL_API mgl_decrement_atomic_i16(mgl_atomic_i16_t* dst);

	/// <summary>
	///		ANDs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_and_atomic_i16(mgl_atomic_i16_t* dst, mgl_i16_t value);

	/// <summary>
	///		ORs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_or_atomic_i16(mgl_atomic_i16_t* dst, mgl_i16_t value);

	/// <summary>
	///		XORs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_xor_atomic_i16(mgl_atomic_i16_t* dst, mgl_i16_t value);

	/// <summary>
	///		Stores a value on a signed 32 bit integer atomic variable.
	/// </summary>
	/// <param name="dst">Destination atomic</param>
	/// <param name="src">Source value</param>
	void MGL_API mgl_store_atomic_i32(mgl_atomic_i32_t* dst, mgl_i32_t src);

	/// <summary>
	///		Loads a value from a signed 32 bit integer atomic variable.
	/// </summary>
	/// <param name="src">Source atomic</param>
	/// <returns>Atomic value</returns>
	mgl_i32_t MGL_API mgl_load_atomic_i32(mgl_atomic_i32_t* src);

	/// <summary>
	///		Increments an atomic.
	/// </summary>
	/// <param name="dst">Destination atomic</param>
	/// <returns>New value</returns>
	mgl_i32_t MGL_API mgl_increment_atomic_i32(mgl_atomic_i32_t* dst);

	/// <summary>
	///		Increments an atomic.
	/// </summary>
	/// <param name="dst">Destination atomic</param>
	/// <returns>New value</returns>
	mgl_i32_t MGL_API mgl_decrement_atomic_i32(mgl_atomic_i32_t* dst);

	/// <summary>
	///		Adds a value to an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_add_atomic_i32(mgl_atomic_i32_t* dst, mgl_i32_t value);

	/// <summary>
	///		ANDs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_and_atomic_i32(mgl_atomic_i32_t* dst, mgl_i32_t value);

	/// <summary>
	///		ORs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_or_atomic_i32(mgl_atomic_i32_t* dst, mgl_i32_t value);

	/// <summary>
	///		XORs a value with an atomic.
	/// </summary>
	/// <param name="value">Value</param>
	/// <param name="dst">Destination atomic</param>
	void MGL_API mgl_xor_atomic_i32(mgl_atomic_i32_t* dst, mgl_i32_t value);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_THREAD_ATOMIC_H
