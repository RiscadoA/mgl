#include <mgl/stream/stream.h>
#include <stdio.h>

typedef struct
{
	mgl_stream_t base;
	FILE* file;
} mgl_std_file_stream_t;

MGL_API mgl_stream_t* mgl_stdin_stream = NULL;
MGL_API mgl_stream_t* mgl_stdout_stream = NULL;
MGL_API mgl_stream_t* mgl_stderr_stream = NULL;
static mgl_std_file_stream_t mgl_stdin_stream_s;
static mgl_std_file_stream_t mgl_stdout_stream_s;
static mgl_std_file_stream_t mgl_stderr_stream_s;

mgl_error_t MGL_API mgl_streams_init(void)
{
	mgl_stdin_stream = (mgl_stream_t*)&mgl_stdin_stream_s;
	mgl_stdout_stream = (mgl_stream_t*)&mgl_stdout_stream_s;
	mgl_stderr_stream = (mgl_stream_t*)&mgl_stderr_stream_s;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_streams_terminate(void)
{
	mgl_stdin_stream_s.base.functions = NULL;
	mgl_stdin_stream_s.file = NULL;
	mgl_stdin_stream = NULL;
	mgl_stdout_stream_s.base.functions = NULL;
	mgl_stdout_stream_s.file = NULL;
	mgl_stdout_stream = NULL;
	mgl_stderr_stream_s.base.functions = NULL;
	mgl_stderr_stream_s.file = NULL;
	mgl_stderr_stream = NULL;
}
