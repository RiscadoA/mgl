#ifndef MGL_STREAM_STREAM_H
#define MGL_STREAM_STREAM_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	enum
	{
		MGL_STREAM_SEEK_BEGIN,
		MGL_STREAM_SEEK_CURRENT,
		MGL_STREAM_SEEK_END,
	};

	typedef struct mgl_stream_t mgl_stream_t;

	typedef struct
	{
		mgl_error_t(*write)(mgl_stream_t* stream, const void* memory, mgl_u64_t size, mgl_u64_t* out_write_size);
		mgl_error_t(*read)(mgl_stream_t* stream, void* memory, mgl_u64_t size, mgl_u64_t* out_read_size);
		mgl_error_t(*flush)(mgl_stream_t* stream);
		mgl_bool_t(*eof)(mgl_stream_t* stream);
		mgl_u64_t(*tell_r)(mgl_stream_t* stream);
		mgl_u64_t(*tell_w)(mgl_stream_t* stream);
		mgl_error_t(*seek_r)(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction);
		mgl_error_t(*seek_w)(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction);
	} mgl_stream_functions_t;

	struct mgl_stream_t
	{
		mgl_stream_functions_t* functions;
	};

	MGL_API extern mgl_stream_t* mgl_stdin_stream;
	MGL_API extern mgl_stream_t* mgl_stdout_stream;
	MGL_API extern mgl_stream_t* mgl_stderr_stream;

	/// <summary>
	///		Writes to a stream.
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <param name="memory">Memory pointer</param>
	/// <param name="size">Memory size</param>
	/// <param name="out_write_size">Out write size</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_write(mgl_stream_t* stream, const void* memory, mgl_u64_t size, mgl_u64_t* out_write_size);

	/// <summary>
	///		Reads from a stream.
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <param name="memory">Memory pointer</param>
	/// <param name="size">Memory size</param>
	/// <param name="out_read_size">Out read size</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_read(mgl_stream_t* stream, void* memory, mgl_u64_t size, mgl_u64_t* out_read_size);

	/// <summary>
	///		Flushes the stream output buffer (if any).
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_flush(mgl_stream_t* stream);

	/// <summary>
	///		Checks if a stream reached EOF.
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <returns>MGL_TRUE if it did, otherwise MGL_FALSE</returns>
	mgl_bool_t MGL_API mgl_eof(mgl_stream_t* stream);
	
	/// <summary>
	///		Gets the current reading position on a stream.
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <returns>Current reading position</returns>
	mgl_u64_t MGL_API mgl_tell_r(mgl_stream_t* stream);

	/// <summary>
	///		Gets the current writing position on a stream.
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <returns>Current writing position</returns>
	mgl_u64_t MGL_API mgl_tell_w(mgl_stream_t* stream);

	/// <summary>
	///		Seeks a reading position on a stream.
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <param name="position">Desired offset</param>
	/// <param name="direction">Offset direction (MGL_STREAM_SEEK_BEGIN, MGL_STREAM_SEEK_CURRENT or MGL_STREAM_SEEK_END)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_seek_r(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction);

	/// <summary>
	///		Seeks a writing position on a stream.
	/// </summary>
	/// <param name="stream">Stream pointer</param>
	/// <param name="position">Desired offset</param>
	/// <param name="direction">Offset direction (MGL_STREAM_SEEK_BEGIN, MGL_STREAM_SEEK_CURRENT or MGL_STREAM_SEEK_END)</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_seek_w(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction);

	/// <summary>
	///		Initializes the MGL streams library.
	/// </summary>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_streams_init(void);

	/// <summary>
	///		Terminates the MGL streams library.
	/// </summary>
	void MGL_API mgl_streams_terminate(void);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_STREAM_STREAM_H
