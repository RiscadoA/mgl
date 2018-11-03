#include <mgl/entry.h>
#include <mgl/container/array.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	mgl_u8_t buffer[4 * sizeof(mgl_u32_t)];
	mgl_array_t arr;
	mgl_init_array(&arr, 4, sizeof(mgl_u32_t), buffer);

	for (mgl_u32_t i = 0; i < 4; ++i)
		*(mgl_u32_t*)mgl_access_array(&arr, i) = i;

	mgl_iterator_t it;
	mgl_get_array_begin_it(&arr, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 3)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_get_array_end_it(&arr, &it);
	for (mgl_u32_t i = 3; !mgl_iterator_is_null(&it); --i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_prev(&it, &it);
		if (i == 0)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_terminate();
	EXIT_PASS();
}