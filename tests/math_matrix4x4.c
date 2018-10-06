#include <mgl/entry.h>
#include <mgl/math/matrix4x4.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	// Test mgl_f32m4x4_equal
	{
		mgl_f32m4x4_t m1 = { 
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m2 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m3 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
		};

		TEST_REQUIRE_FAIL(mgl_f32m4x4_equal(&m1, &m3));
		TEST_REQUIRE_PASS(mgl_f32m4x4_equal(&m1, &m2));
	}

	// Test mgl_f32m4x4_nequal
	{
		mgl_f32m4x4_t m1 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m2 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m3 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
		};

		TEST_REQUIRE_PASS(mgl_f32m4x4_nequal(&m1, &m3));
		TEST_REQUIRE_FAIL(mgl_f32m4x4_nequal(&m1, &m2));
	}

	// Test mgl_f32m4x4_equal_e
	{
		mgl_f32m4x4_t m1 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m2 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.05f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m3 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
		};

		TEST_REQUIRE_FAIL(mgl_f32m4x4_equal_e(&m1, &m3, 0.1f));
		TEST_REQUIRE_PASS(mgl_f32m4x4_equal_e(&m1, &m2, 0.1f));
	}

	// Test mgl_f32m4x4_nequal_e
	{
		mgl_f32m4x4_t m1 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m2 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.05f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 
		};

		mgl_f32m4x4_t m3 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
		};

		TEST_REQUIRE_PASS(mgl_f32m4x4_nequal_e(&m1, &m3, 0.1f));
		TEST_REQUIRE_FAIL(mgl_f32m4x4_nequal_e(&m1, &m2, 0.1f));
	}

	// Test mgl_f32m4x4_mulmat
	{
		mgl_f32m4x4_t m1 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m2 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m3;

		mgl_f32m4x4_mulmat(&m1, &m2, &m3);
		TEST_REQUIRE_PASS(mgl_f32m4x4_equal(&m2, &m3));
	}

	mgl_terminate();
	EXIT_PASS();
}