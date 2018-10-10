#include <mgl/entry.h>
#include <mgl/math/scalar.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	// Test mgl_f32_abs
	{
		TEST_REQUIRE_PASS(mgl_f32_abs(1.0f) == 1.0f);
		TEST_REQUIRE_PASS(mgl_f32_abs(-1.0f) == 1.0f);
		TEST_REQUIRE_PASS(mgl_f32_abs(0.0f) == 0.0f);
	}

	// Test mgl_f32_equal_e
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(1.0f, 1.0f, 0.5f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(1.0f, 1.4f, 0.5f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(1.0f, 1.0f, 0.0f));
		TEST_REQUIRE_FAIL(mgl_f32_equal_e(1.0f, 1.6f, 0.5f));
		TEST_REQUIRE_FAIL(mgl_f32_equal_e(1.0f, 1.6f, 0.0f));
	}

	// Test mgl_f32_nequal_e
	{
		TEST_REQUIRE_PASS(mgl_f32_nequal_e(1.0f, 2.0f, 0.5f));
		TEST_REQUIRE_PASS(mgl_f32_nequal_e(1.0f, 1.01f, 0.0f));
		TEST_REQUIRE_FAIL(mgl_f32_nequal_e(1.0f, 1.4f, 0.5f));
		TEST_REQUIRE_FAIL(mgl_f32_nequal_e(1.0f, 1.0f, 0.0f));
	}

	// Test mgl_f32_deg_to_rad
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_deg_to_rad(360.0f), MGL_PI_F32 * 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_deg_to_rad(180.0f), MGL_PI_F32, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_deg_to_rad(-90.0f), -MGL_PI_F32 / 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_deg_to_rad(90.0f), MGL_PI_F32 / 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_deg_to_rad(45.0f), MGL_PI_F32 / 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_deg_to_rad(0.0f), 0.0f, 0.001f));
	}

	// Test mgl_f32_rad_to_deg
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(0.0f), 0.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(MGL_PI_F32 * 2), 360.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(-MGL_PI_F32 * 2), -360.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(MGL_PI_F32), 180.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(-MGL_PI_F32), -180.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(MGL_PI_F32 / 2), 90.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(-MGL_PI_F32 / 2), -90.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(MGL_PI_F32 / 4), 45.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_rad_to_deg(-MGL_PI_F32 / 4), -45.0f, 0.001f));
	}

	// Test mgl_f32_cos
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_cos(MGL_PI_F32), -1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_cos(0.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_cos(MGL_PI_F32 / 2.0f), 0.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_cos(-MGL_PI_F32 / 2.0f), 0.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_cos(MGL_PI_F32 / 4.0f), mgl_f32_sqrt(2.0f)/2.0f, 0.001f));
	}

	// Test mgl_f32_sin
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sin(MGL_PI_F32), 0.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sin(0.0f), 0.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sin(MGL_PI_F32 / 2.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sin(-MGL_PI_F32 / 2.0f), -1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sin(MGL_PI_F32 / 4.0f), mgl_f32_sqrt(2.0f) / 2.0f, 0.001f));
	}

	// Test mgl_f32_tan
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_tan(MGL_PI_F32), 0.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_tan(0.0f), 0.0f, 0.001f));
	}

	// Test mgl_f32_acos
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_acos(mgl_f32_cos(MGL_PI_F32)), MGL_PI_F32, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_acos(mgl_f32_cos(MGL_PI_F32 / 2.0f)), MGL_PI_F32 / 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_acos(mgl_f32_cos(0.0f)), 0.0f, 0.001f));
	}

	// Test mgl_f32_asin
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_asin(mgl_f32_sin(-MGL_PI_F32 / 2.0f)), -MGL_PI_F32 / 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_asin(mgl_f32_sin(MGL_PI_F32 / 2.0f)), MGL_PI_F32 / 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_asin(mgl_f32_sin(0.0f)), 0.0f, 0.001f));
	}

	// Test mgl_f32_atan
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_atan(mgl_f32_tan(MGL_PI_F32 / 4.0f)), MGL_PI_F32 / 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_atan(mgl_f32_tan(-MGL_PI_F32 / 4.0f)), -MGL_PI_F32 / 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_atan(mgl_f32_tan(0.0f)), 0.0f, 0.001f));
	}

	// Test mgl_f32_pow
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_pow(1.0f, 8.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_pow(2.0f, 8.0f), 256.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_pow(2.0f, 0.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_pow(10.0f, 4.0f), 10000.0f, 0.001f));
	}

	// Test mgl_f32_square
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_square(1.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_square(2.0f), 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_square(4.0f), 16.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_square(8.0f), 64.0f, 0.001f));
	}

	// Test mgl_f32_sqrt
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sqrt(1.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sqrt(4.0f), 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sqrt(16.0f), 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_sqrt(64.0f), 8.0f, 0.001f));
	}

	// Test mgl_f32_distance_1d
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_distance_1d(0.0f, 1.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_distance_1d(-2.0f, 1.0f), 9.0f, 0.001f));
	}

	// Test mgl_f32_distance_2d
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_distance_2d(0.0f, 0.0f, 1.0f, 1.0f), 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_distance_2d(-1.0f, 0.0f, 1.0f, 1.0f), 5.0f, 0.001f));
	}

	// Test mgl_f32_distance_3d
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_distance_3d(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f), 3.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_distance_3d(-1.0f, 0.0f, -2.0f, 1.0f, 1.0f, 0.0f), 9.0f, 0.001f));
	}

	// Test mgl_f32_log
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log(1.0f), logf(1.0f), 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log(2.0f), logf(2.0f), 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log(4.0f), logf(4.0f), 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log(8.0f), logf(8.0f), 0.001f));
	}

	// Test mgl_f32_log2
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log2(2.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log2(4.0f), 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log2(8.0f), 3.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log2(16.0f), 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log2(256.0f), 8.0f, 0.001f));
	}

	// Test mgl_f32_log10
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log10(100.0f), 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log10(10.0f), 1.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log10(1000.0f), 3.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log10(10000.0f), 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_log10(100000000.0f), 8.0f, 0.001f));
	}

	// Test mgl_f32_exp
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp(1.0f), expf(1.0f), 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp(2.0f), expf(2.0f), 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp(4.0f), expf(4.0f), 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp(8.0f), expf(8.0f), 0.001f));
	}

	// Test mgl_f32_exp2
	{
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp2(1.0f), 2.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp2(2.0f), 4.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp2(3.0f), 8.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp2(4.0f), 16.0f, 0.001f));
		TEST_REQUIRE_PASS(mgl_f32_equal_e(mgl_f32_exp2(8.0f), 256.0f, 0.001f));
	}

	mgl_terminate();
	EXIT_PASS();
}