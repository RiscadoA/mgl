#include <mgl/entry.h>
#include <mgl/math/vector.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	// Test mgl_f32v4_set
	{
		mgl_f32v4_t v = mgl_f32v4_set(1.0f, 2.0f, 4.0f, 8.0f);
		mgl_f32_t v_values[4];
		mgl_f32v4_store(&v, v_values);
		TEST_REQUIRE_PASS(v_values[0] == 1.0f);
		TEST_REQUIRE_PASS(v_values[1] == 2.0f);
		TEST_REQUIRE_PASS(v_values[2] == 4.0f);
		TEST_REQUIRE_PASS(v_values[3] == 8.0f);
	}

	// Test mgl_f32v4_load
	{
		mgl_f32_t v_values_1[4] = { 0.0f, 1.0f, 2.0f, 3.0f };
		mgl_f32v4_t v = mgl_f32v4_load(v_values_1);
		mgl_f32_t v_values[4];
		mgl_f32v4_store(&v, v_values);
		TEST_REQUIRE_PASS(v_values[0] == 0.0f);
		TEST_REQUIRE_PASS(v_values[1] == 1.0f);
		TEST_REQUIRE_PASS(v_values[2] == 2.0f);
		TEST_REQUIRE_PASS(v_values[3] == 3.0f);
	}
	
	// Test mgl_f32v4_equal
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(1.0f, 2.0f, 3.0f, 4.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(3.0f, 4.0f, 5.0f, 6.0f);
		TEST_REQUIRE_FAIL(mgl_f32v4_equal(v1, v2));
		v1 = mgl_f32v4_set(1.0f, 2.0f, 3.0f, 4.0f);
		v2 = mgl_f32v4_set(1.0f, 2.0f, 3.0f, 4.0f);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v1, v2));
	}

	// Test mgl_f32v4_add
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(1.0f, 2.0f, 3.0f, 4.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(3.0f, 4.0f, 5.0f, 6.0f);
		mgl_f32v4_t v3 = mgl_f32v4_add(v1, v2);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v3, mgl_f32v4_set(4.0f, 6.0f, 8.0f, 10.0f)));
	}

	// Test mgl_f32v4_sub
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(1.0f, 2.0f, 3.0f, 4.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(3.0f, 4.0f, 5.0f, 6.0f);
		mgl_f32v4_t v3 = mgl_f32v4_sub(v1, v2);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v3, mgl_f32v4_set(-2.0f, -2.0f, -2.0f, -2.0f)));
	}

	// Test mgl_f32v4_mul
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(1.0f, 2.0f, 3.0f, 4.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(3.0f, 4.0f, 5.0f, 6.0f);
		mgl_f32v4_t v3 = mgl_f32v4_mul(v1, v2);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v3, mgl_f32v4_set(3.0f, 8.0f, 15.0f, 24.0f)));
	}

	// Test mgl_f32v4_div
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(1.0f, 2.0f, 3.0f, 4.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(3.0f, 4.0f, 5.0f, 6.0f);
		mgl_f32v4_t v3 = mgl_f32v4_div(v1, v2);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v3, mgl_f32v4_set(1.0f/3.0f, 2.0f/4.0f, 3.0f/5.0f, 4.0f/6.0f)));
	}

	// Test mgl_f32v4_min
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(4.0f, 2.0f, 7.0f, 4.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(3.0f, 4.0f, 5.0f, 6.0f);
		mgl_f32v4_t v3 = mgl_f32v4_min(v1, v2);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v3, mgl_f32v4_set(3.0f, 2.0f, 5.0f, 4.0f)));
	}

	// Test mgl_f32v4_max
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(4.0f, 2.0f, 7.0f, 4.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(3.0f, 4.0f, 5.0f, 6.0f);
		mgl_f32v4_t v3 = mgl_f32v4_max(v1, v2);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v3, mgl_f32v4_set(4.0f, 4.0f, 7.0f, 6.0f)));
	}

	// Test mgl_f32v4_sqrt
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(4.0f, 16.0f, 25.0f, 36.0f);
		mgl_f32v4_t v2 = mgl_f32v4_sqrt(v1);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v2, mgl_f32v4_set(2.0f, 4.0f, 5.0f, 6.0f)));
	}

	// Test mgl_f32v4_rsqrt
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(4.0f, 16.0f, 25.0f, 36.0f);
		mgl_f32v4_t v2 = mgl_f32v4_rsqrt(v1);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(v2, mgl_f32v4_set(1.0f / 2.0f, 1.0f / 4.0f, 1.0f / 5.0f, 1.0f / 6.0f), 1.0e-3f));
	}

	// Test mgl_f32v4_rcp
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(2.0f, 4.0f, 5.0f, 6.0f);
		mgl_f32v4_t v2 = mgl_f32v4_rcp(v1);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(v2, mgl_f32v4_set(1.0f / 2.0f, 1.0f / 4.0f, 1.0f / 5.0f, 1.0f / 6.0f), 1.0e-3f));
	}

	// Test mgl_f32v4_cross
	{
		mgl_f32v4_t v1 = mgl_f32v4_set(1.0f, 0.0f, 0.0f, 0.0f);
		mgl_f32v4_t v2 = mgl_f32v4_set(0.0f, 1.0f, 0.0f, 0.0f);
		mgl_f32v4_t v3 = mgl_f32v4_cross(v1, v2);
		TEST_REQUIRE_PASS(mgl_f32v4_equal(v3, mgl_f32v4_set(0.0f, 0.0f, 1.0f, 0.0f)));
	}

	// Test mgl_f32v4_dot
	{
		{
			mgl_f32v4_t v1 = mgl_f32v4_set(1.0f, 0.0f, 0.0f, 0.0f);
			mgl_f32v4_t v2 = mgl_f32v4_set(0.0f, 1.0f, 0.0f, 0.0f);
			mgl_f32_t f1 = mgl_f32v4_dot(v1, v2);
			TEST_REQUIRE_PASS(f1 == 0.0f);
		}

		{
			mgl_f32v4_t v1 = mgl_f32v4_set(0.0f, 1.0f, 0.0f, 0.0f);
			mgl_f32v4_t v2 = mgl_f32v4_set(0.0f, 1.0f, 0.0f, 0.0f);
			mgl_f32_t f1 = mgl_f32v4_dot(v1, v2);
			TEST_REQUIRE_PASS(f1 == 1.0f);
		}
	}


	mgl_terminate();
	EXIT_PASS();
}