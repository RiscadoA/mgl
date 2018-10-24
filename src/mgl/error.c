#include <mgl/error.h>
#include <stdlib.h>

MGL_API void mgl_abort(void)
{
	abort();
}

MGL_API const mgl_chr8_t* mgl_get_error_string(mgl_error_t error)
{
	switch (error)
	{
		case MGL_ERROR_NONE: return u8"MGL_ERROR_NONE: No error";
		case MGL_ERROR_EXTERNAL: return u8"MGL_ERROR_EXTERNAL: External error";
		case MGL_ERROR_OVERFLOW: return u8"MGL_ERROR_OVERFLOW: Overflow detected";
		case MGL_ERROR_UNDERFLOW: return u8"MGL_ERROR_UNDERFLOW: Underflow detected";
		case MGL_ERROR_TOO_BIG: return u8"MGL_ERROR_TOO_BIG: Too big";
		case MGL_ERROR_OUT_OF_BOUNDS: return u8"MGL_ERROR_TOO_BIG: Out of bounds";
		case MGL_ERROR_UNSUPPORTED: return u8"MGL_ERROR_UNSUPPORTED: Unsupported feature";
		case MGL_ERROR_INVALID_PARAMS: return u8"MGL_ERROR_INVALID_PARAMS: Invalid parameters";
		case MGL_ERROR_FAILED_TO_PARSE: return u8"MGL_ERROR_FAILED_TO_PARSE: Failed to parse";
		default: return u8"???: Unknown error";
	}
}
