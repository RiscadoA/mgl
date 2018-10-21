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

static mgl_error_t mgl_std_stream_write(mgl_stream_t* stream, const void* memory, mgl_u64_t size, mgl_u64_t* out_write_size)
{
	mgl_std_file_stream_t* std = (mgl_std_file_stream_t*)stream;
	mgl_u64_t s = fwrite(memory, 1, size, std->file);
	if (out_write_size != NULL)
		*out_write_size = s;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_std_stream_read(mgl_stream_t* stream, void* memory, mgl_u64_t size, mgl_u64_t* out_read_size)
{
	mgl_std_file_stream_t* std = (mgl_std_file_stream_t*)stream;
	mgl_u64_t s = fread_s(memory, size, 1, size, std->file);
	if (out_read_size != NULL)
		*out_read_size = s;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_std_stream_flush(mgl_stream_t* stream)
{
	mgl_std_file_stream_t* std = (mgl_std_file_stream_t*)stream;
	if (fflush(std->file) != 0)
		return MGL_ERROR_EXTERNAL;
	return MGL_ERROR_NONE;
}

static mgl_bool_t mgl_std_stream_eof(mgl_stream_t* stream)
{
	mgl_std_file_stream_t* std = (mgl_std_file_stream_t*)stream;
	return feof(std->file);
}

static mgl_u64_t mgl_std_stream_tell(mgl_stream_t* stream)
{
	mgl_std_file_stream_t* std = (mgl_std_file_stream_t*)stream;
	return ftell(std->file);
}

static mgl_error_t mgl_std_stream_seek(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction)
{
	mgl_std_file_stream_t* std = (mgl_std_file_stream_t*)stream;
	int std_dir;
	if (direction == MGL_STREAM_SEEK_BEGIN)
		std_dir = SEEK_SET;
	else if (direction == MGL_STREAM_SEEK_CURRENT)
		std_dir = SEEK_CUR;
	else if (direction == MGL_STREAM_SEEK_END)
		std_dir = SEEK_END;
	else
		return MGL_ERROR_INVALID_PARAMS;
	if (fseek(std->file, (long)position, std_dir) != 0)
	{
		// Clear error
		ferror(std->file);
		return MGL_ERROR_EXTERNAL;
	}
	return MGL_ERROR_NONE;
}

static mgl_stream_functions_t mgl_std_stream_functions =
{
	&mgl_std_stream_write,
	&mgl_std_stream_read,
	&mgl_std_stream_flush,
	&mgl_std_stream_eof,
	&mgl_std_stream_tell,
	&mgl_std_stream_tell,
	&mgl_std_stream_seek,
	&mgl_std_stream_seek
};

mgl_error_t MGL_API mgl_streams_init(void)
{
	mgl_stdin_stream_s.base.functions = &mgl_std_stream_functions;
	mgl_stdin_stream_s.file = stdin;
	mgl_stdout_stream_s.base.functions = &mgl_std_stream_functions;
	mgl_stdout_stream_s.file = stdout;
	mgl_stderr_stream_s.base.functions = &mgl_std_stream_functions;
	mgl_stderr_stream_s.file = stderr;

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

mgl_error_t MGL_API mgl_put_byte(mgl_stream_t * stream, mgl_u8_t x)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	return mgl_write(stream, &x, sizeof(x), NULL);
}

mgl_error_t MGL_API mgl_put_char(mgl_stream_t * stream, mgl_u8_t x)
{
	MGL_DEBUG_ASSERT(stream != NULL);
#ifdef _WIN32
	if (x == '\n')
	{
		static const mgl_u8_t crlf[] = { '\r', '\n' };
		return mgl_write(stream, crlf, sizeof(crlf), NULL);
	}
#endif
	return mgl_write(stream, &x, sizeof(x), NULL);
}

mgl_error_t MGL_API mgl_put_string(mgl_stream_t * stream, const mgl_u8_t * byte_str)
{
	MGL_DEBUG_ASSERT(stream != NULL && byte_str != NULL);
	mgl_error_t err;
	for (; *byte_str != 0; ++byte_str)
	{
		err = mgl_put_byte(stream, *byte_str);
		if (err != MGL_ERROR_NONE)
			return err;
	}
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_print(mgl_stream_t * stream, const mgl_u8_t * str)
{
	MGL_DEBUG_ASSERT(stream != NULL && str != NULL);
	mgl_error_t err;
	for (; *str != 0; ++str)
	{
		err = mgl_put_char(stream, *str);
		if (err != MGL_ERROR_NONE)
			return err;
	}
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_get_byte(mgl_stream_t * stream, mgl_u8_t * out)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	return mgl_read(stream, out, sizeof(*out), NULL);
}

mgl_error_t MGL_API mgl_get_char(mgl_stream_t * stream, mgl_u8_t * out)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	mgl_error_t err = mgl_read(stream, out, sizeof(*out), NULL);
	if (err != MGL_ERROR_NONE)
		return err;
	if (*out == '\r')
		return mgl_read(stream, out, sizeof(*out), NULL);
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_read_bytes_until(mgl_stream_t * stream, void * memory, mgl_u64_t size, mgl_u64_t * out_read_size, const mgl_u8_t * end_sequence)
{
	MGL_DEBUG_ASSERT(stream != NULL && end_sequence != NULL);
	const mgl_u8_t* seq_it = end_sequence;
	mgl_u64_t seq_sz = 0;
	mgl_error_t err;

	if (memory == NULL)
		size = MGL_U64_MAX;

	for (mgl_u64_t i = 0; i < size; ++i)
	{
		mgl_u8_t r;
		err = mgl_get_byte(stream, &r);
		if (err != MGL_ERROR_NONE)
			return err;
		// Check if the sequence matches
		if (*seq_it == r)
		{
			++seq_it;
			++seq_sz;
			// Check if the sequence ended
			if (*seq_it == 0)
			{
				if (out_read_size != NULL)
					*out_read_size = (i + 1) - seq_sz;
				return MGL_ERROR_NONE;
			}
		}
		// Otherwise fill the buffer
		else
		{
			seq_it = end_sequence;
			if (memory != NULL)
			{
				for (mgl_u64_t n = 0, end = seq_sz; n < end; ++n, --seq_sz)
					((mgl_u8_t*)memory)[i - seq_sz] = end_sequence[n];
				((mgl_u8_t*)memory)[i] = r;
			}
		}
	}

	if (out_read_size != NULL)
		*out_read_size = size;
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_read_chars_until(mgl_stream_t * stream, void * memory, mgl_u64_t size, mgl_u64_t * out_read_size, const mgl_u8_t * end_sequence)
{
	MGL_DEBUG_ASSERT(stream != NULL && end_sequence != NULL);
	const mgl_u8_t* seq_it = end_sequence;
	mgl_u64_t seq_sz = 0;
	mgl_error_t err;

	if (memory == NULL)
		size = MGL_U64_MAX;

	for (mgl_u64_t i = 0; i < size; ++i)
	{
		mgl_u8_t r;
		err = mgl_get_char(stream, &r);
		if (err != MGL_ERROR_NONE)
			return err;
		// Check if the sequence matches
		if (*seq_it == r)
		{
			++seq_it;
			++seq_sz;
			// Check if the sequence ended
			if (*seq_it == 0)
			{
				if (out_read_size != NULL)
					*out_read_size = (i + 1) - seq_sz;
				return MGL_ERROR_NONE;
			}
		}
		// Otherwise fill the buffer
		else
		{
			seq_it = end_sequence;
			if (memory != NULL)
			{
				for (mgl_u64_t n = 0, end = seq_sz; n < end; ++n, --seq_sz)
					((mgl_u8_t*)memory)[i - seq_sz] = end_sequence[n];
				((mgl_u8_t*)memory)[i] = r;
			}
		}
	}

	if (out_read_size != NULL)
		*out_read_size = size;
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_write(mgl_stream_t * stream, const void * memory, mgl_u64_t size, mgl_u64_t * out_write_size)
{
	MGL_DEBUG_ASSERT(stream != NULL && memory != NULL);
	if (stream->functions->write == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return stream->functions->write(stream, memory, size, out_write_size);
}

mgl_error_t MGL_API mgl_read(mgl_stream_t * stream, void * memory, mgl_u64_t size, mgl_u64_t * out_read_size)
{
	MGL_DEBUG_ASSERT(stream != NULL && memory != NULL);
	if (stream->functions->read == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return stream->functions->read(stream, memory, size, out_read_size);
}

mgl_error_t MGL_API mgl_flush(mgl_stream_t * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (stream->functions->flush == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return stream->functions->flush(stream);
}

mgl_bool_t MGL_API mgl_eof(mgl_stream_t * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (stream->functions->eof == NULL)
		return MGL_FALSE;
	return stream->functions->eof(stream);
}

mgl_u64_t MGL_API mgl_tell_r(mgl_stream_t * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (stream->functions->tell_r == NULL)
		return 0;
	return stream->functions->tell_r(stream);
}

mgl_u64_t MGL_API mgl_tell_w(mgl_stream_t * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (stream->functions->tell_w == NULL)
		return 0;
	return stream->functions->tell_w(stream);
}

mgl_error_t MGL_API mgl_seek_r(mgl_stream_t * stream, mgl_i64_t position, mgl_enum_t direction)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (stream->functions->seek_r == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return stream->functions->seek_r(stream, position, direction);
}

mgl_error_t MGL_API mgl_seek_w(mgl_stream_t * stream, mgl_i64_t position, mgl_enum_t direction)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (stream->functions->seek_w == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return stream->functions->seek_w(stream, position, direction);
}
