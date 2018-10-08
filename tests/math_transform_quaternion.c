#include <mgl/entry.h>
#include <mgl/math/transform_quaternion.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	// Test mgl_f32q4_angle_axis and mgl_f32q4_mul_v4
	{
		mgl_f32v4_t v1 = { 0.0f, 1.0f, 0.0f, 0.0f };
		mgl_f32v4_t v2 = { 0.0f, -1.0f, 0.0f, 0.0f };
		mgl_f32v4_t v3;
		mgl_f32q4_t q1;

		mgl_f32q4_angle_axis(MGL_PI_F32, 0.0f, 0.0f, 1.0f, &q1);
		mgl_f32q4_normalize(&q1, &q1);
		mgl_f32q4_mul_v4(&q1, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(&v2, &v3, 0.001f));

		mgl_f32q4_angle_axis(MGL_PI_F32 * 2.0f, 0.0f, 0.0f, 1.0f, &q1);
		mgl_f32q4_normalize(&q1, &q1);
		mgl_f32q4_mul_v4(&q1, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(&v1, &v3, 0.001f));

		v2 = (mgl_f32v4_t) { -1.0f, 0.0f, 0.0f, 0.0f };
		mgl_f32q4_angle_axis(MGL_PI_F32 * 0.5f, 0.0f, 0.0f, 1.0f, &q1);
		mgl_f32q4_normalize(&q1, &q1);
		mgl_f32q4_mul_v4(&q1, &v1, &v3);
		TEST_REQUIRE_PASS(mgl_f32v4_equal_e(&v2, &v3, 0.001f));
	}

	mgl_terminate();
	EXIT_PASS();
}