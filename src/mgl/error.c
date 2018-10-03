#include <mgl/error.h>
#include <stdlib.h>

MGL_API void mgl_abort(void)
{
	abort();
}

MGL_API const mgl_chr8_t* mgl_get_error_string(mgl_error_t error)
{
	return u8"???: Unknown error";
}
