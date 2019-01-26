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
		case MGL_ERROR_EOF: return u8"MGL_ERROR_EOF: End of file reached";
		case MGL_ERROR_FAILED_TO_PARSE: return u8"MGL_ERROR_FAILED_TO_PARSE: Failed to parse";
		case MGL_ERROR_TIMEOUT: return u8"MGL_ERROR_TIMEOUT: Time out";
		case MGL_ERROR_THREAD_STILL_RUNNING: return u8"MGL_ERROR_THREAD_STILL_RUNNING: Thread is still running";
		case MGL_ERROR_MUTEX_ALREADY_LOCKED: return u8"MGL_ERROR_MUTEX_ALREADY_LOCKED: Mutex is already locked";
		case MGL_ERROR_FILE_NOT_FOUND: return u8"MGL_ERROR_FILE_NOT_FOUND: Couldn't find a file";
		case MGL_ERROR_ARCHIVE_NOT_FOUND: return u8"MGL_ERROR_ARCHIVE_NOT_FOUND: Couldn't find an archive";
		case MGL_ERROR_FILE_ALREADY_EXISTS: return u8"MGL_ERROR_FILE_ALREADY_EXISTS: The file already exists"; 
		case MGL_ERROR_UNSUPPORTED_PARENT_ATTRIBUTES: return u8"MGL_ERROR_UNSUPPORTED_PARENT_ATTRIBUTES: The parent file has unsupported attributes";
		case MGL_ERROR_INVALID_ADDRESS: return u8"MGL_ERROR_INVALID_ADDRESS: Invalid IP address";
		case MGL_ERROR_DISCONNECTED: return u8"MGL_ERROR_DISCONNECTED: Socket disconnected";
		case MGL_ERROR_NOT_READY: return u8"MGL_ERROR_NOT_READY: Non-blocking operation not completed";
		case MGL_ERROR_NOT_LISTENING: return u8"MGL_ERROR_NOT_LISTENING: Listener is not listening";
		default: return u8"???: Unknown error";
	}
}
