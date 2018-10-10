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
	}
	return u8"???: Unknown error";
}
