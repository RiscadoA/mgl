#include <mgl/entry.h>
#include <mgl/memory/pool_allocator.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	mgl_pool_allocator_t allocator;
	mgl_u8_t allocator_memory[MGL_POOL_ALLOCATOR_SIZE(4, 4)];
	mgl_init_pool_allocator(&allocator, 4, 4, allocator_memory, sizeof(allocator_memory));

	void* ptr;
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 6, &ptr) == MGL_ERROR_TOO_BIG);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 4, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_deallocate(&allocator, ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 3, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 2, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 1, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 4, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 4, &ptr) == MGL_ERROR_OVERFLOW);

	mgl_terminate();
	EXIT_PASS();
}