#include <mgl/entry.h>
#include <mgl/math/vector.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);


	// Test member access operations
	{
		mgl_f32v4_t vec;
		vec.x = 0.0f;
		vec.y = 1.0f;
		vec.z = 2.0f;
		vec.w = 3.0f;
		TEST_REQUIRE_PASS(vec.data[0] == 0.0f);
		TEST_REQUIRE_PASS(vec.data[1] == 1.0f);
		TEST_REQUIRE_PASS(vec.data[2] == 2.0f);
		TEST_REQUIRE_PASS(vec.data[3] == 3.0f);
	}

	// Test mgl_f32v4_equal
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		TEST_REQUIRE_FAIL(mgl_f32v4_equal(&v1, &v2));
		v1 = (mgl_f32v4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		v2 = (mgl_f32v4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v1,& v2));
	}

	// Test mgl_f32v4_nequal
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_nequal(&v1, &v2));
		v1 = (mgl_f32v4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		v2 = (mgl_f32v4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		TEST_REQUIRE_FAIL(mgl_f32v4_nequal(&v1, &v2));
	}

	// Test mgl_f32v4_add4
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		mgl_f32v4_t v3;
		mgl_f32v4_add4(&v1, &v2, &v3);
		mgl_f32v4_t v4 = { 4.0f, 6.0f, 8.0f, 10.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32v4_add3
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 1.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		mgl_f32v4_t v3;
		mgl_f32v4_add3(&v1, &v2, &v3);
		mgl_f32v4_t v4 = { 4.0f, 6.0f, 8.0f, 1.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32v4_sub4
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 1.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		mgl_f32v4_t v3;
		mgl_f32v4_sub4(&v1, &v2, &v3);
		mgl_f32v4_t v4 = { -2.0f, -2.0f, -2.0f, -5.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32v4_sub3
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 1.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 1.0f };
		mgl_f32v4_t v3;
		mgl_f32v4_sub3(&v1, &v2, &v3);
		mgl_f32v4_t v4 = { -2.0f, -2.0f, -2.0f, 0.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32v4_mul
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 1.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		mgl_f32v4_t v3;
		mgl_f32v4_mul(&v1, &v2, &v3);
		mgl_f32v4_t v4 = { 3.0f, 8.0f, 15.0f, 6.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32v4_div
	{
		mgl_f32v4_t v1 = { 1.0f, 2.0f, 3.0f, 1.0f };
		mgl_f32v4_t v2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		mgl_f32v4_t v3;
		mgl_f32v4_div(&v1, &v2, &v3);
		mgl_f32v4_t v4 = { 1.0f/3.0f, 2.0f/4.0f, 3.0f/5.0f, 1.0f/6.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32v4_cross
	{
		mgl_f32v4_t v1 = { 1.0f, 0.0f, 0.0f, 0.0f };
		mgl_f32v4_t v2 = { 0.0f, 1.0f, 0.0f, 0.0f };
		mgl_f32v4_t v3;
		mgl_f32v4_cross(&v1, &v2, &v3);
		mgl_f32v4_t v4 = { 0.0f, 0.0f, 1.0f, 0.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32v4_dot
	{
		mgl_f32v4_t v1 = { 1.0f, 0.0f, 0.0f, 0.0f };
		mgl_f32v4_t v2 = { 0.0f, 1.0f, 0.0f, 0.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_dot(&v1, &v2) == 0.0f);
		v1 = (mgl_f32v4_t) { 1.0f, 0.0f, 0.0f, 0.0f };
		v2 = (mgl_f32v4_t) { 1.0f, 0.0f, 0.0f, 0.0f };
		TEST_REQUIRE_PASS(mgl_f32v4_dot(&v1, &v2) == 1.0f);
	}

	mgl_terminate();
	EXIT_PASS();
}