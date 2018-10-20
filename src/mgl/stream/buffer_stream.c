#include <mgl/stream/buffer_stream.h>
#include <mgl/memory/manipulation.h>

static mgl_error_t mgl_buffer_stream_write(mgl_stream_t* stream, const void* memory, mgl_u64_t size, mgl_u64_t* out_write_size)
{
	mgl_buffer_stream_t* buf = (mgl_buffer_stream_t*)stream;

	MGL_DEBUG_ASSERT(memory != NULL && size != 0);

	if (buf->buffer_size == buf->w_head)
	{
		if (out_write_size != NULL)
			*out_write_size = 0;
		buf->eof = MGL_TRUE;
		return MGL_ERROR_EOF;
	}
	else if (buf->buffer_size - buf->w_head < size)
	{
		mgl_u64_t w_size = buf->buffer_size - buf->w_head;
		mgl_mem_copy((void*)((mgl_uptr_t)buf->buffer + buf->w_head), memory, w_size);
		buf->w_head += w_size;
		if (out_write_size != NULL)
			*out_write_size = w_size;
		buf->eof = MGL_TRUE;
		return MGL_ERROR_EOF;
	}
	else
	{
		mgl_mem_copy((void*)((mgl_uptr_t)buf->buffer + buf->w_head), memory, size);
		buf->w_head += size;
		if (out_write_size != NULL)
			*out_write_size = size;
	}

	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_buffer_stream_read(mgl_stream_t* stream, void* memory, mgl_u64_t size, mgl_u64_t* out_read_size)
{
	mgl_buffer_stream_t* buf = (mgl_buffer_stream_t*)stream;
	
	MGL_DEBUG_ASSERT(memory != NULL && size != 0);

	if (buf->buffer_size == buf->r_head)
	{
		if (out_read_size != NULL)
			*out_read_size = 0;
		buf->eof = MGL_TRUE;
		return MGL_ERROR_EOF;
	}
	else if (buf->buffer_size - buf->r_head < size)
	{
		mgl_u64_t r_size = buf->buffer_size - buf->r_head;
		mgl_mem_copy(memory, (void*)((mgl_uptr_t)buf->buffer + buf->r_head), r_size);
		buf->r_head += r_size;
		if (out_read_size != NULL)
			*out_read_size = r_size;
		buf->eof = MGL_TRUE;
		return MGL_ERROR_EOF;
	}
	else
	{
		mgl_mem_copy(memory, (void*)((mgl_uptr_t)buf->buffer + buf->r_head), size);
		buf->r_head += size;
		if (out_read_size != NULL)
			*out_read_size = size;
	}

	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_buffer_stream_flush(mgl_stream_t* stream)
{
	return MGL_ERROR_NONE; // Do nothing
}

static mgl_bool_t mgl_buffer_stream_eof(mgl_stream_t* stream)
{
	mgl_buffer_stream_t* buf = (mgl_buffer_stream_t*)stream;
	if (buf->eof == MGL_TRUE)
	{
		buf->eof = MGL_FALSE;
		return MGL_TRUE;
	}
	return MGL_FALSE;
}

static mgl_u64_t mgl_buffer_stream_tell_r(mgl_stream_t* stream)
{
	mgl_buffer_stream_t* buf = (mgl_buffer_stream_t*)stream;
	return buf->r_head;
}

static mgl_u64_t mgl_buffer_stream_tell_w(mgl_stream_t* stream)
{
	mgl_buffer_stream_t* buf = (mgl_buffer_stream_t*)stream;
	return buf->w_head;
}

static mgl_error_t mgl_buffer_stream_seek_r(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction)
{
	mgl_buffer_stream_t* buf = (mgl_buffer_stream_t*)stream;
	if (direction == MGL_STREAM_SEEK_BEGIN)
	{
		if (position < 0)
			position = 0;

		if ((mgl_u64_t)position >= buf->buffer_size)
		{
			buf->r_head = buf->buffer_size;
			buf->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}
		
		buf->r_head = position;
	}
	else if (direction == MGL_STREAM_SEEK_CURRENT)
	{
		if (position + buf->r_head >= buf->buffer_size)
		{
			buf->r_head = buf->buffer_size;
			buf->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}
		else if (position + buf->r_head < 0)
			buf->r_head = 0;
		else
			buf->r_head += position;
	}
	else if (direction == MGL_STREAM_SEEK_END)
	{
		if (position > 0)
			position = 0;

		if ((mgl_u64_t)-position >= buf->buffer_size)
		{
			buf->r_head = 0;
			buf->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}

		buf->r_head = buf->buffer_size + position - 1;
	}
	else
		return MGL_ERROR_INVALID_PARAMS;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_buffer_stream_seek_w(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction)
{
	mgl_buffer_stream_t* buf = (mgl_buffer_stream_t*)stream;
	if (direction == MGL_STREAM_SEEK_BEGIN)
	{
		if (position < 0)
			position = 0;

		if ((mgl_u64_t)position >= buf->buffer_size)
		{
			buf->w_head = buf->buffer_size;
			buf->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}

		buf->w_head = position;
	}
	else if (direction == MGL_STREAM_SEEK_CURRENT)
	{
		if (position + buf->w_head >= buf->buffer_size)
		{
			buf->w_head = buf->buffer_size;
			buf->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}
		else if (position + buf->w_head < 0)
			buf->w_head = 0;
		else
			buf->w_head += position;
	}
	else if (direction == MGL_STREAM_SEEK_END)
	{
		if (position > 0)
			position = 0;

		if ((mgl_u64_t)-position >= buf->buffer_size)
		{
			buf->w_head = 0;
			buf->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}

		buf->w_head = buf->buffer_size + position - 1;
	}
	else
		return MGL_ERROR_INVALID_PARAMS;
	return MGL_ERROR_NONE;
}

static mgl_stream_functions_t mgl_buffer_stream_functions =
{
	&mgl_buffer_stream_write,
	&mgl_buffer_stream_read,
	&mgl_buffer_stream_flush,
	&mgl_buffer_stream_eof,
	&mgl_buffer_stream_tell_r,
	&mgl_buffer_stream_tell_w,
	&mgl_buffer_stream_seek_r,
	&mgl_buffer_stream_seek_w
};

void MGL_API mgl_init_buffer_stream(mgl_buffer_stream_t * stream, void * buffer, mgl_u64_t buffer_size)
{
	MGL_DEBUG_ASSERT(stream != NULL && buffer != NULL);
	stream->buffer = buffer;
	stream->buffer_size = buffer_size;
	stream->eof = MGL_FALSE;
	stream->r_head = 0;
	stream->w_head = 0;
	stream->base.functions = &mgl_buffer_stream_functions;
}
