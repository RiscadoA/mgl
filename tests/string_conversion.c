#include <mgl/entry.h>
#include <mgl/string/conversion.h>
#include <mgl/string/manipulation.h>
#include <mgl/memory/manipulation.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	mgl_u64_t sz;
	mgl_u8_t buffer[256];
	mgl_mem_set(buffer, sizeof(buffer), 0);
	
	// Test u8_to_str
	TEST_REQUIRE_PASS(mgl_u8_to_str(buffer, sizeof(buffer) - 1, 53, 10, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"53"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u8_to_str(buffer, sizeof(buffer) - 1, 0xff, 16, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"ff"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u8_to_str(buffer, sizeof(buffer) - 1, 4, 2, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 3);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"100"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u8_to_str(buffer, 2, 4, 2, &sz) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(sz == 2);
	mgl_mem_set(buffer, sizeof(buffer), 0);

	// Test u16_to_str
	TEST_REQUIRE_PASS(mgl_u16_to_str(buffer, sizeof(buffer) - 1, 53, 10, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"53"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u16_to_str(buffer, sizeof(buffer) - 1, 0xff, 16, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"ff"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u16_to_str(buffer, sizeof(buffer) - 1, 4, 2, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 3);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"100"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u16_to_str(buffer, 2, 4, 2, &sz) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(sz == 2);
	mgl_mem_set(buffer, sizeof(buffer), 0);

	// Test u32_to_str
	TEST_REQUIRE_PASS(mgl_u32_to_str(buffer, sizeof(buffer) - 1, 53, 10, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"53"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u32_to_str(buffer, sizeof(buffer) - 1, 0xff, 16, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"ff"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u32_to_str(buffer, sizeof(buffer) - 1, 4, 2, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 3);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"100"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u32_to_str(buffer, 2, 4, 2, &sz) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(sz == 2);
	mgl_mem_set(buffer, sizeof(buffer), 0);

	// Test u64_to_str
	TEST_REQUIRE_PASS(mgl_u64_to_str(buffer, sizeof(buffer) - 1, 53, 10, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"53"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u64_to_str(buffer, sizeof(buffer) - 1, 0xff, 16, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 2);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"ff"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u64_to_str(buffer, sizeof(buffer) - 1, 4, 2, &sz) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(sz == 3);
	TEST_REQUIRE_PASS(mgl_str_equal(buffer, u8"100"));
	mgl_mem_set(buffer, sizeof(buffer), 0);
	TEST_REQUIRE_PASS(mgl_u64_to_str(buffer, 2, 4, 2, &sz) == MGL_ERROR_EOF);
	TEST_REQUIRE_PASS(sz == 2);
	mgl_mem_set(buffer, sizeof(buffer), 0);

	mgl_terminate();
	EXIT_PASS();
}