#include <mgl/entry.h>
#include <mgl/math/transform_matrix4x4.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	// Test mgl_f32m4x4_mul_v4
	{
		mgl_f32v4_t v1 = { 0.0f, 0.0f, 0.0f, 1.0f };
		mgl_f32v4_t v2 = { 1.0f, 1.0f, 0.0f, 1.0f };

		mgl_f32m4x4_t m1 = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32m4x4_t m2 = {
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		mgl_f32v4_t v3;

		mgl_f32m4x4_mul_v4(&m1, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v1, &v3));

		mgl_f32m4x4_mul_v4(&m2, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v2, &v3));

		mgl_f32m4x4_mul_v4(&m1, &v2, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v2, &v3));
	}

	// Test mgl_f32m4x4_scale
	{
		mgl_f32v4_t v1 = { 0.0f, 0.0f, 0.0f, 1.0f };
		mgl_f32v4_t v2 = { 1.0f, 1.0f, 3.0f, 1.0f };
		mgl_f32v4_t v3 = { 1.0f, 0.0f, 6.0f, 1.0f };

		mgl_f32m4x4_t m1;
		mgl_f32m4x4_scale(1.0f, 0.0f, 2.0f, &m1);

		mgl_f32v4_t v4;

		mgl_f32m4x4_mul_v4(&m1, &v1, &v4);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v1, &v4));
		mgl_f32m4x4_mul_v4(&m1, &v2, &v4);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32m4x4_translate
	{
		mgl_f32v4_t v1 = { 0.0f, 0.0f, 0.0f, 1.0f };
		mgl_f32v4_t v2 = { 1.0f, 0.0f, 2.0f, 1.0f };
		mgl_f32v4_t v3 = { 2.0f, 0.0f, 4.0f, 1.0f };

		mgl_f32m4x4_t m1;
		mgl_f32m4x4_translate(1.0f, 0.0f, 2.0f, &m1);

		mgl_f32v4_t v4;

		mgl_f32m4x4_mul_v4(&m1, &v1, &v4);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v2, &v4));
		mgl_f32m4x4_mul_v4(&m1, &v2, &v4);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(&v3, &v4));
	}

	// Test mgl_f32m4x4_rotate_x
	{
		mgl_f32v4_t v1 = { 0.0f, 1.0f, 0.0f, 1.0f };
		mgl_f32v4_t v2 = { 0.0f, 0.0f, -1.0f, 1.0f };
		mgl_f32v4_t v3;

		mgl_f32m4x4_t m1;
		mgl_f32m4x4_rotate_x(MGL_PI_F32 / 2, &m1);

		mgl_f32m4x4_mul_v4(&m1, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(&v2, &v3, 0.01f));
	}

	// Test mgl_f32m4x4_rotate_y
	{
		mgl_f32v4_t v1 = { 1.0f, 0.0f, 0.0f, 1.0f };
		mgl_f32v4_t v2 = { 0.0f, 0.0f, 1.0f, 1.0f };
		mgl_f32v4_t v3;

		mgl_f32m4x4_t m1;
		mgl_f32m4x4_rotate_y(MGL_PI_F32 / 2, &m1);

		mgl_f32m4x4_mul_v4(&m1, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(&v2, &v3, 0.01f));
	}

	// Test mgl_f32m4x4_rotate_z
	{
		mgl_f32v4_t v1 = { 1.0f, 0.0f, 0.0f, 1.0f };
		mgl_f32v4_t v2 = { 0.0f, -1.0f, 0.0f, 1.0f };
		mgl_f32v4_t v3;

		mgl_f32m4x4_t m1;
		mgl_f32m4x4_rotate_z(MGL_PI_F32 / 2, &m1);

		mgl_f32m4x4_mul_v4(&m1, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(&v2, &v3, 0.01f));
	}

	mgl_terminate();
	EXIT_PASS();
}