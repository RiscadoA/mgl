#include <mgl/entry.h>
#include <mgl/math/quaternion.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);


	// Test member access operations
	{
		mgl_f32q4_t q;
		q.s = 3.0f;
		q.x = 0.0f;
		q.y = 1.0f;
		q.z = 2.0f;
		TEST_REQUIRE_PASS(q.data[0] == 3.0f);
		TEST_REQUIRE_PASS(q.data[1] == 0.0f);
		TEST_REQUIRE_PASS(q.data[2] == 1.0f);
		TEST_REQUIRE_PASS(q.data[3] == 2.0f);
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

	mgl_terminate();
	EXIT_PASS();
}