#include <mgl/file/logger.h>
#include <mgl/memory/allocator.h>
#include <mgl/stream/buffer_stream.h>

#include <stdio.h>
#include <time.h>

#define MGL_LOGGER_BUFFER_SIZE 4096

#ifdef MGL_SYSTEM_WINDOWS
#include <Windows.h>
#endif

struct mgl_logger_t
{
	void* allocator;
	mgl_chr8_t buffer[MGL_LOGGER_BUFFER_SIZE];
	mgl_u64_t size;
	FILE* file;
};

mgl_logger_t *MGL_API mgl_logger_open(void * allocator, const mgl_chr8_t* name)
{
	MGL_DEBUG_ASSERT(allocator != NULL);
	mgl_logger_t* logger;

	mgl_chr8_t file_name[256] = { 0 };

	{
		mgl_buffer_stream_t stream;
		mgl_init_buffer_stream(&stream, file_name, sizeof(file_name));

		time_t tm;
		time(&tm);

#ifdef MGL_SYSTEM_WINDOWS
		CreateDirectory(u8"log/", NULL);
#endif
		mgl_print(&stream, u8"log/");
		mgl_print(&stream, name);
		mgl_print(&stream, u8"_");
		mgl_print_u64(&stream, tm, 10);
		mgl_print(&stream, u8".txt");
	}

	FILE* file = fopen(file_name, "w");

	MGL_DEBUG_ASSERT(file != NULL);

	MGL_DEBUG_ASSERT(mgl_allocate(allocator, sizeof(mgl_logger_t), (void**)&logger) == MGL_ERROR_NONE);
	logger->allocator = allocator;
	logger->size = 0;
	logger->file = file;

	return logger;
}

void MGL_API mgl_logger_add(mgl_logger_t * logger, const mgl_chr8_t * text)
{
	MGL_DEBUG_ASSERT(logger != NULL && text != NULL);
	fputs(text, logger->file);
}

void MGL_API mgl_logger_close(mgl_logger_t * logger)
{
	MGL_DEBUG_ASSERT(logger != NULL);
	fclose(logger->file);
	MGL_DEBUG_ASSERT(mgl_deallocate(logger->allocator, logger) == MGL_ERROR_NONE);
}
