#ifndef MGL_STREAM_BUFFER_STREAM_H
#define MGL_STREAM_BUFFER_STREAM_H

#include <mgl/stream/stream.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_stream_t base;
		mgl_u64_t buffer_size;
		mgl_u64_t r_head;
		mgl_u64_t w_head;
		void* buffer;
		mgl_bool_t eof;
	} mgl_buffer_stream_t;

	/// <summary>
	///		Inits a buffer stream.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="buffer">Buffer</param>
	/// <param name="buffer_size">Buffer size</param>
	void MGL_API mgl_init_buffer_stream(mgl_buffer_stream_t* stream, void* buffer, mgl_u64_t buffer_size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_STREAM_BUFFER_STREAM_H
