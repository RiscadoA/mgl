#include <mgl/stream/stream.h>
#include <mgl/string/conversion.h>
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
	mgl_u64_t s = fread(memory, size, 1, std->file);
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

mgl_error_t MGL_API mgl_put_byte(void * stream, mgl_u8_t x)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	return mgl_write(((mgl_stream_t*)stream), &x, sizeof(x), NULL);
}

mgl_error_t MGL_API mgl_put_char(void * stream, mgl_u8_t x)
{
	MGL_DEBUG_ASSERT(stream != NULL);
#ifdef _WIN32
	if (x == '\n')
	{
		static const mgl_u8_t crlf[] = { '\r', '\n' };
		return mgl_write(((mgl_stream_t*)stream), crlf, sizeof(crlf), NULL);
	}
#endif
	return mgl_write(((mgl_stream_t*)stream), &x, sizeof(x), NULL);
}

mgl_error_t MGL_API mgl_put_string(void * stream, const mgl_u8_t * byte_str)
{
	MGL_DEBUG_ASSERT(stream != NULL && byte_str != NULL);
	mgl_error_t err;
	for (; *byte_str != 0; ++byte_str)
	{
		err = mgl_put_byte(((mgl_stream_t*)stream), *byte_str);
		if (err != MGL_ERROR_NONE)
			return err;
	}
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_print(void * stream, const mgl_u8_t * str)
{
	MGL_DEBUG_ASSERT(stream != NULL && str != NULL);
	mgl_error_t err;
	for (; *str != 0; ++str)
	{
		err = mgl_put_char(((mgl_stream_t*)stream), *str);
		if (err != MGL_ERROR_NONE)
			return err;
	}
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_get_byte(void * stream, mgl_u8_t * out)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	return mgl_read(((mgl_stream_t*)stream), out, sizeof(*out), NULL);
}

mgl_error_t MGL_API mgl_get_char(void * stream, mgl_u8_t * out)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	mgl_error_t err = mgl_read(((mgl_stream_t*)stream), out, sizeof(*out), NULL);
	if (err != MGL_ERROR_NONE)
		return err;
	if (*out == '\r')
		return mgl_read(((mgl_stream_t*)stream), out, sizeof(*out), NULL);
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_read_bytes_until(void * stream, void * memory, mgl_u64_t size, mgl_u64_t * out_read_size, const mgl_u8_t * end_sequence)
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
		err = mgl_get_byte(((mgl_stream_t*)stream), &r);
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

mgl_error_t MGL_API mgl_read_chars_until(void * stream, void * memory, mgl_u64_t size, mgl_u64_t * out_read_size, const mgl_u8_t * end_sequence)
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
		err = mgl_get_char(((mgl_stream_t*)stream), &r);
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

mgl_error_t MGL_API mgl_print_u8(void * stream, mgl_u8_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[8];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_u8_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_u16(void * stream, mgl_u16_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[16];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_u16_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_u32(void * stream, mgl_u32_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[32];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_u32_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_u64(void * stream, mgl_u64_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[64];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_u64_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_i8(void * stream, mgl_i8_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[9];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_i8_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_i16(void * stream, mgl_i16_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[17];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_i16_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_i32(void * stream, mgl_i32_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[33];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_i32_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_i64(void * stream, mgl_i64_t value, mgl_u8_t base)
{
	mgl_u8_t buffer[65];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_i64_to_str(buffer, sizeof(buffer), value, base, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_f32(void * stream, mgl_f32_t value, mgl_u8_t base, mgl_u64_t decimal_places)
{
	mgl_u8_t buffer[128];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_f32_to_str(buffer, sizeof(buffer), value, base, decimal_places, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_print_f64(void * stream, mgl_f64_t value, mgl_u8_t base, mgl_u64_t decimal_places)
{
	mgl_u8_t buffer[128];
	mgl_u64_t sz = 0;
	mgl_error_t err = mgl_f64_to_str(buffer, sizeof(buffer), value, base, decimal_places, &sz);
	if (err != MGL_ERROR_NONE)
		return err;
	return mgl_write(((mgl_stream_t*)stream), buffer, sz, NULL);
}

mgl_error_t MGL_API mgl_parse_u8(void * stream, mgl_u8_t base, mgl_u8_t * out, const mgl_u8_t* separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_u8_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_u16(void * stream, mgl_u8_t base, mgl_u16_t * out, const mgl_u8_t* separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_u16_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_u32(void * stream, mgl_u8_t base, mgl_u32_t * out, const mgl_u8_t* separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_u32_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_u64(void * stream, mgl_u8_t base, mgl_u64_t * out, const mgl_u8_t* separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_u64_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_i8(void * stream, mgl_u8_t base, mgl_i8_t * out, const mgl_u8_t * separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_i8_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_i16(void * stream, mgl_u8_t base, mgl_i16_t * out, const mgl_u8_t * separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_i16_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_i32(void * stream, mgl_u8_t base, mgl_i32_t * out, const mgl_u8_t * separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_i32_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_i64(void * stream, mgl_u8_t base, mgl_i64_t * out, const mgl_u8_t * separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_i64_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_f32(void * stream, mgl_u8_t base, mgl_f32_t * out, const mgl_u8_t * separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_f32_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_parse_f64(void * stream, mgl_u8_t base, mgl_f64_t * out, const mgl_u8_t * separator)
{
	mgl_u8_t buffer[256];
	buffer[255] = 0;
	mgl_error_t e = mgl_read_chars_until(((mgl_stream_t*)stream), buffer, sizeof(buffer) - 1, NULL, separator);
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_f64_from_str(buffer, sizeof(buffer), out, base, NULL);
	return e;
}

mgl_error_t MGL_API mgl_write(void * stream, const void * memory, mgl_u64_t size, mgl_u64_t * out_write_size)
{
	MGL_DEBUG_ASSERT(stream != NULL && memory != NULL);
	if (((mgl_stream_t*)stream)->functions->write == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return ((mgl_stream_t*)stream)->functions->write(((mgl_stream_t*)stream), memory, size, out_write_size);
}

mgl_error_t MGL_API mgl_read(void * stream, void * memory, mgl_u64_t size, mgl_u64_t * out_read_size)
{
	MGL_DEBUG_ASSERT(stream != NULL && memory != NULL);
	if (((mgl_stream_t*)stream)->functions->read == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return ((mgl_stream_t*)stream)->functions->read(((mgl_stream_t*)stream), memory, size, out_read_size);
}

mgl_error_t MGL_API mgl_flush(void * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (((mgl_stream_t*)stream)->functions->flush == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return ((mgl_stream_t*)stream)->functions->flush(((mgl_stream_t*)stream));
}

mgl_bool_t MGL_API mgl_eof(void * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (((mgl_stream_t*)stream)->functions->eof == NULL)
		return MGL_FALSE;
	return ((mgl_stream_t*)stream)->functions->eof(((mgl_stream_t*)stream));
}

mgl_u64_t MGL_API mgl_tell_r(void * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (((mgl_stream_t*)stream)->functions->tell_r == NULL)
		return 0;
	return ((mgl_stream_t*)stream)->functions->tell_r(((mgl_stream_t*)stream));
}

mgl_u64_t MGL_API mgl_tell_w(void * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (((mgl_stream_t*)stream)->functions->tell_w == NULL)
		return 0;
	return ((mgl_stream_t*)stream)->functions->tell_w(((mgl_stream_t*)stream));
}

mgl_error_t MGL_API mgl_seek_r(void * stream, mgl_i64_t position, mgl_enum_t direction)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (((mgl_stream_t*)stream)->functions->seek_r == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return ((mgl_stream_t*)stream)->functions->seek_r(((mgl_stream_t*)stream), position, direction);
}

mgl_error_t MGL_API mgl_seek_w(void * stream, mgl_i64_t position, mgl_enum_t direction)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	if (((mgl_stream_t*)stream)->functions->seek_w == NULL)
		return MGL_ERROR_UNSUPPORTED;
	return ((mgl_stream_t*)stream)->functions->seek_w(((mgl_stream_t*)stream), position, direction);
}
