#include <mgl/entry.h>
#include <mgl/container/singly_linked_list.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	mgl_singly_linked_list_t list;
	mgl_init_singly_linked_list(&list, sizeof(mgl_u32_t), mgl_standard_allocator);

	mgl_u32_t x;
	x = 0;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_push_end(&list, &x, NULL) == MGL_ERROR_NONE);
	x = 1;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_push_end(&list, &x, NULL) == MGL_ERROR_NONE);
	x = 2;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_push_end(&list, &x, NULL) == MGL_ERROR_NONE);
	x = 3;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_push_end(&list, &x, NULL) == MGL_ERROR_NONE);

	mgl_iterator_t it;
	mgl_get_singly_linked_list_begin_it(&list, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 3)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_get_singly_linked_list_end_it(&list, &it);
	for (mgl_u32_t i = 3; !mgl_iterator_is_null(&it); --i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_prev(&it, &it);
		if (i == 0)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_singly_linked_list_clear(&list);
	mgl_get_singly_linked_list_begin_it(&list, &it);
	TEST_REQUIRE_PASS(mgl_iterator_is_null(&it));
	mgl_get_singly_linked_list_end_it(&list, &it);
	TEST_REQUIRE_PASS(mgl_iterator_is_null(&it));

	x = 0;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_push_end(&list, &x, NULL) == MGL_ERROR_NONE);
	mgl_get_singly_linked_list_begin_it(&list, &it);
	TEST_REQUIRE_PASS(!mgl_iterator_is_null(&it));
	mgl_get_singly_linked_list_end_it(&list, &it);
	TEST_REQUIRE_PASS(!mgl_iterator_is_null(&it));

	for (mgl_u32_t i = 1; i < 8; ++i)
		TEST_REQUIRE_PASS(mgl_singly_linked_list_push_end(&list, &i, NULL) == MGL_ERROR_NONE);

	mgl_get_singly_linked_list_begin_it(&list, &it);
	for (mgl_u32_t i = 0; !mgl_iterator_is_null(&it); ++i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_next(&it, &it);
		if (i == 7)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}

	mgl_get_singly_linked_list_end_it(&list, &it);
	for (mgl_u32_t i = 7; !mgl_iterator_is_null(&it); --i)
	{
		TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == i);
		mgl_error_t e = mgl_iterator_prev(&it, &it);
		if (i == 0)
			TEST_REQUIRE_PASS(e == MGL_ERROR_OUT_OF_BOUNDS);
		else
			TEST_REQUIRE_PASS(e == MGL_ERROR_NONE);
	}
	
	mgl_singly_linked_list_clear(&list);

	mgl_get_singly_linked_list_begin_it(&list, &it);
	x = 0;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_insert_before(&list, &it, &x, NULL) == MGL_ERROR_NONE);
	// 0
	mgl_get_singly_linked_list_begin_it(&list, &it);
	x = 1;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_insert_after(&list, &it, &x, NULL) == MGL_ERROR_NONE);
	// 0 1
	mgl_get_singly_linked_list_begin_it(&list, &it);
	x = 2;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_insert_after(&list, &it, &x, NULL) == MGL_ERROR_NONE);
	// 0 2 1
	mgl_get_singly_linked_list_end_it(&list, &it);
	x = 3;
	TEST_REQUIRE_PASS(mgl_singly_linked_list_insert_before(&list, &it, &x, NULL) == MGL_ERROR_NONE);
	// 0 2 3 1

	mgl_get_singly_linked_list_begin_it(&list, &it);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 0);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 2);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 3);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 1);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_OUT_OF_BOUNDS);

	mgl_get_singly_linked_list_begin_it(&list, &it);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	mgl_singly_linked_list_remove(&list, &it);
	// 0 3 1

	mgl_get_singly_linked_list_begin_it(&list, &it);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 0);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 3);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 1);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_OUT_OF_BOUNDS);

	x = 4;
	mgl_singly_linked_list_set(&list, &x);
	mgl_get_singly_linked_list_begin_it(&list, &it);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 4);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 4);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE);
	TEST_REQUIRE_PASS(*(mgl_u32_t*)mgl_iterator_get(&it) == 4);
	TEST_REQUIRE_PASS(mgl_iterator_next(&it, &it) == MGL_ERROR_OUT_OF_BOUNDS);

	mgl_terminate_singly_linked_list(&list);

	mgl_terminate();
	EXIT_PASS();
}