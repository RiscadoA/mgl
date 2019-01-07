#ifndef MGL_ERROR_H
#define MGL_ERROR_H

#include <mgl/type.h>
#include <mgl/api_utils.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <assert.h>

	enum
	{
		MGL_ERROR_NONE							= 0x00000000,
		MGL_ERROR_EXTERNAL						= 0x00000001,
		MGL_ERROR_OVERFLOW						= 0x00000002,
		MGL_ERROR_UNDERFLOW						= 0x00000003,
		MGL_ERROR_TOO_BIG						= 0x00000004,
		MGL_ERROR_OUT_OF_BOUNDS					= 0x00000005,
		MGL_ERROR_UNSUPPORTED					= 0x00000006,
		MGL_ERROR_INVALID_PARAMS				= 0x00000007,
		MGL_ERROR_EOF							= 0x00000008,
		MGL_ERROR_FAILED_TO_PARSE				= 0x00000009,
		MGL_ERROR_TIMEOUT						= 0x0000000A,
		MGL_ERROR_THREAD_STILL_RUNNING			= 0x0000000B,
		MGL_ERROR_MUTEX_ALREADY_LOCKED			= 0x0000000C,
		MGL_ERROR_FILE_NOT_FOUND				= 0x0000000D,
		MGL_ERROR_ARCHIVE_NOT_FOUND				= 0x0000000E,
		MGL_ERROR_FILE_ALREADY_EXISTS			= 0x0000000F,
		MGL_ERROR_UNSUPPORTED_PARENT_ATTRIBUTES	= 0x00000010,
		MGL_ERROR_INVALID_ADDRESS				= 0x00000011,
		MGL_ERROR_DISCONNECTED                  = 0x00000012,
		MGL_ERROR_NOT_READY                     = 0x00000013,
		MGL_ERROR_NOT_LISTENING                 = 0x00000014,
	};

	typedef mgl_enum_t mgl_error_t;

	/// <summary>
	///		Aborts the program execution.
	/// </summary>
	MGL_API void mgl_abort(void);

	/// <summary>
	///		Converts an error enum value into an UTF-8 error string.
	/// </summary>
	/// <param name="error">Error code</param>
	/// <returns>UTF-8 string that represents the error</returns>
	MGL_API const mgl_chr8_t* mgl_get_error_string(mgl_error_t error);

	/// <summary>
	///		Makes sure an expression evaluates to true.
	///		If the expression does not evaluate to true, mgl_abort() is called. 
	/// </summary>
#define MGL_ASSERT(condition) do { if (!(condition)) mgl_abort(); } while (MGL_FALSE)

#ifdef MGL_BUILD_DEBUG
	/// <summary>
	///		Makes sure an expression evaluates to true.
	///		If the expression does not evaluate to true, mgl_abort() is called. 
	///		Only checks if NDEBUG is not defined.
	/// </summary>
#	define MGL_DEBUG_ASSERT(condition) MGL_ASSERT(condition)
#else
	/// <summary>
	///		Makes sure an expression evaluates to true.
	///		If the expression does not evaluate to true, mgl_abort() is called. 
	///		Only checks if NDEBUG is not defined.
	/// </summary>
#	define MGL_DEBUG_ASSERT(condition) do {} while (MGL_FALSE)
#endif

#define MGL_STATIC_ASSERT(check, msg) static_assert(check, msg)

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_ERROR_H
