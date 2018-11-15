#include <mgl/entry.h>
#include <mgl/memory/allocator.h>
#include <mgl/stream/stream.h>
#include <mgl/file/archive.h>

mgl_error_t MGL_API mgl_init(void)
{
	mgl_error_t e;

	e = mgl_allocators_init();
	if (e != MGL_ERROR_NONE)
		return e;

	e = mgl_streams_init();
	if (e != MGL_ERROR_NONE)
		return e;

	e = mgl_archives_init();
	if (e != MGL_ERROR_NONE)
		return e;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_terminate(void)
{
	mgl_archives_terminate();
	mgl_streams_terminate();
	mgl_allocators_terminate();
}
