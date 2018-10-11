#include <mgl/entry.h>
#include <mgl/memory/allocator.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	void* ptr;
	TEST_REQUIRE_PASS(mgl_allocate(mgl_standard_allocator, 256, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_deallocate(mgl_standard_allocator, ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_allocate_aligned(mgl_standard_allocator, 2048, 256, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS((((mgl_uptr_t)ptr) & (256 - 1)) == 0);
	TEST_REQUIRE_PASS(mgl_deallocate_aligned(mgl_standard_allocator, ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_reallocate(mgl_standard_allocator, NULL, 0, 256, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_reallocate(mgl_standard_allocator, ptr, 256, 2048, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_deallocate(mgl_standard_allocator, ptr) == MGL_ERROR_NONE);

	mgl_terminate();
	EXIT_PASS();
}