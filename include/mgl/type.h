#ifndef MGL_TYPE_H
#define MGL_TYPE_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>
#include <float.h>
#include <uchar.h>

	typedef int8_t		mgl_i8_t;
	typedef int16_t		mgl_i16_t;
	typedef int32_t		mgl_i32_t;
	typedef int64_t		mgl_i64_t;
	typedef uint8_t		mgl_u8_t;
	typedef uint16_t	mgl_u16_t;
	typedef uint32_t	mgl_u32_t;
	typedef uint64_t	mgl_u64_t;
	typedef float		mgl_f32_t;
	typedef double		mgl_f64_t;
	typedef intptr_t	mgl_iptr_t;
	typedef uintptr_t	mgl_uptr_t;
	typedef mgl_i32_t	mgl_enum_t;
	typedef mgl_i8_t	mgl_bool_t;
	typedef char		mgl_chr8_t;
	typedef char32_t	mgl_chr32_t;

#define MGL_I8_MAX		INT8_MAX
#define MGL_I16_MAX		INT16_MAX
#define MGL_I32_MAX		INT32_MAX
#define MGL_I64_MAX		INT64_MAX
#define MGL_I8_MIN		INT8_MIN
#define MGL_I16_MIN		INT16_MIN
#define MGL_I32_MIN		INT32_MIN
#define MGL_I64_MIN		INT64_MIN
#define MGL_U8_MAX		UINT8_MAX
#define MGL_U16_MAX		UINT16_MAX
#define MGL_U32_MAX		UINT32_MAX
#define MGL_U64_MAX		UINT64_MAX
#define MGL_F32_MAX		FLT_MAX
#define MGL_F32_MIN		FLT_MIN
#define MGL_F32_RAD		FLT_RADIX
#define MGL_F64_MAX		DBL_MAX
#define MGL_F64_MIN		DBL_MIN
#define MGL_F64_RAD		FLT_RADIX
#define MGL_IPTR_MAX	INTPTR_MAX
#define MGL_IPTR_MIN	INTPTR_MIN
#define MGL_UPTR_MAX	UINTPTR_MAX

#define MGL_TRUE		(1)
#define MGL_FALSE		(0)

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_TYPE_H
