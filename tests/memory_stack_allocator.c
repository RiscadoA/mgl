#include <mgl/entry.h>
#include <mgl/memory/stack_allocator.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	mgl_stack_allocator_t allocator;
	mgl_u8_t allocator_memory[4];
	mgl_init_stack_allocator(&allocator, allocator_memory, sizeof(allocator_memory));

	mgl_uptr_t p_head = mgl_get_stack_allocator_head(&allocator);
	void* ptr;
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 6, &ptr) == MGL_ERROR_STACK_OVERFLOW);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 4, &ptr) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(mgl_deallocate(&allocator, ptr) == MGL_ERROR_NONE);
	mgl_set_stack_allocator_head(&allocator, p_head);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 3, &ptr) == MGL_ERROR_NONE);
	void* ptr_2;
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 2, &ptr_2) == MGL_ERROR_STACK_OVERFLOW);
	TEST_REQUIRE_PASS(mgl_allocate(&allocator, 1, &ptr_2) == MGL_ERROR_NONE);

	mgl_terminate();
	EXIT_PASS();
}