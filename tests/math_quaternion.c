#include <mgl/entry.h>
#include <mgl/math/quaternion.h>
#include <mgl/math/scalar.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);


	// Test member access operations
	{
		mgl_f32q4_t q;
		q.x = 0.0f;
		q.y = 1.0f;
		q.z = 2.0f;
		q.s = 3.0f;
		TEST_REQUIRE_PASS(q.data[0] == 0.0f);
		TEST_REQUIRE_PASS(q.data[1] == 1.0f);
		TEST_REQUIRE_PASS(q.data[2] == 2.0f);
		TEST_REQUIRE_PASS(q.data[3] == 3.0f);
	}

	// Test mgl_f32q4_equal
	{
		mgl_f32q4_t q1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32q4_t q2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		TEST_REQUIRE_FAIL(mgl_f32q4_equal(&q1, &q2));
		q1 = (mgl_f32q4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		q2 = (mgl_f32q4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		TEST_REQUIRE_PASS(mgl_f32q4_equal(&q1, &q2));
	}

	// Test mgl_f32q4_nequal
	{
		mgl_f32q4_t q1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32q4_t q2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		TEST_REQUIRE_PASS(mgl_f32q4_nequal(&q1, &q2));
		q1 = (mgl_f32q4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		q2 = (mgl_f32q4_t) { 1.0f, 2.0f, 3.0f, 4.0f };
		TEST_REQUIRE_FAIL(mgl_f32q4_nequal(&q1, &q2));
	}

	// Test mgl_f32q4_add
	{
		mgl_f32q4_t q1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32q4_t q2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		mgl_f32q4_t q3;
		mgl_f32q4_add(&q1, &q2, &q3);
		mgl_f32q4_t q4 = { 4.0f, 6.0f, 8.0f, 10.0f };
		TEST_REQUIRE_PASS(mgl_f32q4_equal(&q3, &q4));
	}

	// Test mgl_f32q4_sub
	{
		mgl_f32q4_t q1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32q4_t q2 = { 3.0f, 4.0f, 5.0f, 6.0f };
		mgl_f32q4_t q3;
		mgl_f32q4_sub(&q1, &q2, &q3);
		mgl_f32q4_t q4 = { -2.0f, -2.0f, -2.0f, -2.0f };
		TEST_REQUIRE_PASS(mgl_f32q4_equal(&q3, &q4));
	}

	// Test mgl_f32q4_scale
	{
		mgl_f32q4_t q1 = { 1.0f, 2.0f, 3.0f, 4.0f };
		mgl_f32q4_t q2 = { 2.0f, 4.0f, 6.0f, 8.0f };
		mgl_f32q4_t q3;
		mgl_f32q4_scale(&q1, 2.0f, &q3);
		TEST_REQUIRE_PASS(mgl_f32q4_equal(&q2, &q3));
	}

	// Test mgl_f32q4_conjugate
	{
		mgl_f32q4_t q1 = { -1.0f, -1.0f, -1.0f, 1.0f };
		mgl_f32q4_t q2;
		mgl_f32q4_conjugate(&q1, &q2);

		mgl_f32q4_t q3 = { 1.0f, 1.0f, 1.0f, 1.0f };
		TEST_REQUIRE_PASS(mgl_f32q4_equal_e(&q2, &q3, 0.001f));
	}

	// Test mgl_f32q4_mul
	{
		mgl_f32q4_t q1 = { 1.0f / mgl_f32_sqrt(2.0f), 0.0f, 0.0f, 1.0f / mgl_f32_sqrt(2.0f) };
		mgl_f32q4_t q2 = { 0.0f, 1.0f / mgl_f32_sqrt(2.0f), 0.0f, 1.0f / mgl_f32_sqrt(2.0f) };
		mgl_f32q4_t q3;
		mgl_f32q4_mul(&q1, &q2, &q3);

		mgl_f32q4_t q4 = { 0.5f, 0.5f, 0.5f, 0.5f };
		TEST_REQUIRE_PASS(mgl_f32q4_equal_e(&q3, &q4, 0.001f));

		q4 = (mgl_f32q4_t) { 0.0f, 0.0f, 0.0f, 1.0f };
		mgl_f32q4_conjugate(&q1, &q2);
		mgl_f32q4_mul(&q1, &q2, &q3);
		TEST_REQUIRE_PASS(mgl_f32q4_equal_e(&q3, &q4, 0.001f));
	}

	// Test mgl_f32q4_norm_squared
	{
		mgl_f32q4_t q1 = { 1.0f, 0.0f, 1.0f, 2.0f };
		TEST_REQUIRE_PASS(mgl_f32_equal_e(6.0f, mgl_f32q4_norm_squared(&q1), 0.001f));
	}

	// Test mgl_f32q4_norm
	{
		mgl_f32q4_t q1 = { 0.0f, 0.0f, 0.0f, 4.0f };
		TEST_REQUIRE_PASS(mgl_f32_equal_e(4.0f, mgl_f32q4_norm(&q1), 0.001f));
	}

	// Test mgl_f32q4_normalize
	{
		mgl_f32q4_t q1 = { 0.0f, 0.0f, 0.0f, 4.0f };
		mgl_f32q4_t q2;
		mgl_f32q4_t q3 = { 0.0f, 0.0f, 0.0f, 1.0f };
		mgl_f32q4_normalize(&q1, &q2);
		TEST_REQUIRE_PASS(mgl_f32q4_equal_e(&q2, &q3, 0.001f));
	}

	mgl_terminate();
	EXIT_PASS();
}