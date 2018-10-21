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

	/// <summary>
	///		Writes a single byte into a stream.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="x">Byte</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_put_byte(mgl_stream_t* stream, mgl_u8_t x);

	/// <summary>
	///		Writes an 8-bit character into a stream.
	///		This method differs from mgl_put_byte because it automatically converts LF (10, 0x0A) into CR-LF (13-10, 0x0D-0x0A) on Windows. 
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="x">8-bit character</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_put_char(mgl_stream_t* stream, mgl_u8_t x);

	/// <summary>
	///		Writes a null terminated byte string into a stream.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="byte_str">Null terminated byte string</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_put_string(mgl_stream_t* stream, const mgl_u8_t* byte_str);

	/// <summary>
	///		Prints a null terminated UTF-8 string into a stream.
	///		This method differs from mgl_put_string because it will use mgl_put_char instead of mgl_put_byte.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="str">Null terminated UTF-8 string</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_print(mgl_stream_t* stream, const mgl_u8_t* str);

	/// <summary>
	///		Reads a single byte from a stream.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="out">Out byte</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_get_byte(mgl_stream_t* stream, mgl_u8_t* out);

	/// <summary>
	///		Reads an 8-bit character from a stream.
	///		This method differs from mgl_get_byte because it ignores carriage returns.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="out">Out 8-bit character</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_get_char(mgl_stream_t* stream, mgl_u8_t* out);

	/// <summary>
	///		Reads bytes from a stream until the buffer is filled or a certain sequence of bytes is found.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="memory">Buffer</param>
	/// <param name="size">Buffer size</param>
	/// <param name="out_read_size">Out read size</param>
	/// <param name="end_sequence">Sequence to end on</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_read_bytes_until(mgl_stream_t* stream, void* memory, mgl_u64_t size, mgl_u64_t* out_read_size, const mgl_u8_t* end_sequence);

	/// <summary>
	///		Reads characters from a stream until the buffer is filled or a certain sequence of bytes is found.
	///		Differs from mgl_read_bytes_until because it uses mgl_get_char instead of mgl_get_byte.
	/// </summary>
	/// <param name="stream">Stream</param>
	/// <param name="memory">Buffer</param>
	/// <param name="size">Buffer size</param>
	/// <param name="out_read_size">Out read size</param>
	/// <param name="end_sequence">Sequence to end on</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_read_chars_until(mgl_stream_t* stream, void* memory, mgl_u64_t size, mgl_u64_t* out_read_size, const mgl_u8_t* end_sequence);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_STREAM_STREAM_H
