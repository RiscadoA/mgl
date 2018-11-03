#include <mgl/entry.h>
#include <mgl/container/vector.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	mgl_vector_t vec;
	mgl_init_vector(&vec, 4, sizeof(mgl_u32_t), mgl_standard_allocator);

	for (mgl_u32_t i = 0; i < 4; ++i)
		*(mgl_u32_t*)mgl_access_vector(&vec, i) = i;

	mgl_iterator_t it;
	mgl_get_vector_begin_it(&vec, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 3)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_get_vector_end_it(&vec, &it);
	for (mgl_u32_t i = 3; !mgl_iterator_is_null(&it); --i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_prev(&it, &it);
		if (i == 0)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_vector_clear(&vec);
	mgl_get_vector_begin_it(&vec, &it);
	TEST_REQUIRE_PASS(mgl_iterator_is_null(&it));
	mgl_get_vector_end_it(&vec, &it);
	TEST_REQUIRE_PASS(mgl_iterator_is_null(&it));

	TEST_REQUIRE_PASS(mgl_vector_resize(&vec, 1) == MGL_ERROR_NONE);
	mgl_get_vector_begin_it(&vec, &it);
	TEST_REQUIRE_PASS(!mgl_iterator_is_null(&it));
	mgl_get_vector_end_it(&vec, &it);
	TEST_REQUIRE_PASS(!mgl_iterator_is_null(&it));

	TEST_REQUIRE_PASS(mgl_vector_resize(&vec, 8) == MGL_ERROR_NONE);
	mgl_get_vector_begin_it(&vec, &it);
	TEST_REQUIRE_PASS(!mgl_iterator_is_null(&it));
	mgl_get_vector_end_it(&vec, &it);
	TEST_REQUIRE_PASS(!mgl_iterator_is_null(&it));

	for (mgl_u32_t i = 0; i < 8; ++i)
		*(mgl_u32_t*)mgl_access_vector(&vec, i) = i;

	mgl_get_vector_begin_it(&vec, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 7)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_get_vector_end_it(&vec, &it);
	for (mgl_u32_t i = 7; !mgl_iterator_is_null(&it); --i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_prev(&it, &it);
		if (i == 0)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	TEST_REQUIRE_PASS(mgl_vector_resize(&vec, 0) == MGL_ERROR_NONE);
	mgl_get_vector_begin_it(&vec, &it);
	TEST_REQUIRE_PASS(mgl_iterator_is_null(&it));
	mgl_get_vector_end_it(&vec, &it);
	TEST_REQUIRE_PASS(mgl_iterator_is_null(&it));

	for (mgl_u32_t i = 0; i < 16; ++i)
		TEST_REQUIRE_PASS(mgl_vector_push_end(&vec, &i, NULL) == MGL_ERROR_NONE);

	mgl_get_vector_begin_it(&vec, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 15)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	for (mgl_u32_t i = 0; i < 4; ++i)
		mgl_vector_pop_end(&vec);

	mgl_get_vector_begin_it(&vec, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 11)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	for (mgl_u32_t i = 0; i < 4; ++i)
		mgl_vector_pop_begin(&vec);

	mgl_get_vector_begin_it(&vec, &it);
	for (mgl_u32_t i = 4; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 11)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	for (mgl_u32_t i = 0, j = 3; i < 4; ++i, --j)
		TEST_REQUIRE_PASS(mgl_vector_push_begin(&vec, &j, NULL) == MGL_ERROR_NONE);

	mgl_get_vector_begin_it(&vec, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 11)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_vector_clear(&vec);
	
	mgl_u32_t x = 0;
	TEST_REQUIRE_PASS(mgl_vector_insert_before(&vec, NULL, &x, NULL) == MGL_ERROR_NONE);
	// 0
	x = 1;
	TEST_REQUIRE_PASS(mgl_vector_insert_before(&vec, NULL, &x, NULL) == MGL_ERROR_NONE);
	// 1 0
	mgl_get_vector_element_it(&vec, 1, &it);
	x = 2;
	TEST_REQUIRE_PASS(mgl_vector_insert_before(&vec, &it, &x, NULL) == MGL_ERROR_NONE);
	// 1 2 0
	mgl_get_vector_element_it(&vec, 1, &it);
	x = 3;
	TEST_REQUIRE_PASS(mgl_vector_insert_after(&vec, &it, &x, NULL) == MGL_ERROR_NONE);
	// 1 2 3 0

	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 0) == 1);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 1) == 2);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 2) == 3);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 3) == 0);

	mgl_get_vector_element_it(&vec, 1, &it);
	mgl_vector_remove(&vec, &it);
	// 1 3 0

	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 0) == 1);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 1) == 3);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 2) == 0);

	x = 0;
	mgl_vector_set(&vec, &x);

	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 0) == 0);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 1) == 0);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_access_vector(&vec, 2) == 0);
	TEST_REQUIRE_PASS(mgl_get_vector_element_count(&vec) == 3);
	TEST_REQUIRE_PASS(mgl_get_vector_element_size(&vec) == sizeof(mgl_u32_t));

	mgl_terminate();
	EXIT_PASS();
}