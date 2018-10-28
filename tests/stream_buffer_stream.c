#include <mgl/entry.h>
#include <mgl/stream/buffer_stream.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	// Init buffer stream
	mgl_u8_t buffer[4];
	mgl_buffer_stream_t buffer_stream;
	mgl_init_buffer_stream(&buffer_stream, buffer, sizeof(buffer));
	mgl_stream_t* stream = &buffer_stream.base;

	// Test writing functionality
	mgl_u64_t w_size;
	TEST_REQUIRE_PASS(mgl_write(stream, u8"test", 4, &w_size) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(w_size == 4);
	TEST_REQUIRE_PASS(buffer[0] == 't' && buffer[1] == 'e' && buffer[2] == 's' && buffer[3] == 't');
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE);

	TEST_REQUIRE_PASS(mgl_write(stream, u8"t", 1, &w_size) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(w_size == 0);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_TRUE);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE);

	TEST_REQUIRE_PASS(mgl_seek_w(stream, 4, MGL_STREAM_SEEK_BEGIN) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_TRUE);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE); 
	TEST_REQUIRE_PASS(mgl_seek_w(stream, 2, MGL_STREAM_SEEK_BEGIN) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_write(stream, u8"mp", 2, &w_size) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(w_size == 2);
	TEST_REQUIRE_PASS(buffer[0] == 't' && buffer[1] == 'e' && buffer[2] == 'm' && buffer[3] == 'p');
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE);

	// Test reading functionality
	mgl_u64_t r_size;
	mgl_u8_t r_buffer[4];
	TEST_REQUIRE_PASS(mgl_read(stream, r_buffer, 2, &r_size) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(r_size == 2);
	TEST_REQUIRE_PASS(r_buffer[0] == 't' && r_buffer[1] == 'e');
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE);

	TEST_REQUIRE_PASS(mgl_read(stream, r_buffer, 3, &r_size) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(r_size == 2);
	TEST_REQUIRE_PASS(r_buffer[0] == 'm' && r_buffer[1] == 'p');
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_TRUE);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE);

	TEST_REQUIRE_PASS(mgl_read(stream, r_buffer, 1, &r_size) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(r_size == 0);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_TRUE);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE);
	TEST_REQUIRE_PASS(mgl_seek_r(stream, 2, MGL_STREAM_SEEK_BEGIN) == MGL_ERROR_NONE);

	TEST_REQUIRE_PASS(mgl_read(stream, r_buffer, 3, &r_size) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(r_size == 2);
	TEST_REQUIRE_PASS(r_buffer[0] == 'm' && r_buffer[1] == 'p');
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_TRUE);
	TEST_REQUIRE_PASS(mgl_eof(stream) == MGL_FALSE);

	mgl_terminate();
	EXIT_PASS();
}