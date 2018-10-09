#include <mgl/entry.h>
#include <mgl/math/quaternion_matrix4x4.h>
#include <mgl/math/transform_quaternion.h>
#include <mgl/math/transform_matrix4x4.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

	// Test mgl_f32q4_to_m4x4
	{
		mgl_f32q4_t q1;
		mgl_f32m4x4_t m1;
		mgl_f32m4x4_t m2;

		mgl_f32q4_angle_axis(mgl_f32_deg_to_rad(45.0f), 0.0f, 1.0f, 0.0f, &q1);
		mgl_f32q4_to_m4x4(&q1, &m2);
		mgl_f32m4x4_rotate_y(mgl_f32_deg_to_rad(45.0f), &m1);
		TEST_REQUIRE_PASS(mgl_f32m4x4_equal_e(&m1, &m2, 0.001f));

		mgl_f32q4_angle_axis(mgl_f32_deg_to_rad(45.0f), 1.0f, 0.0f, 0.0f, &q1);
		mgl_f32q4_to_m4x4(&q1, &m2);
		mgl_f32m4x4_rotate_x(mgl_f32_deg_to_rad(45.0f), &m1);
		TEST_REQUIRE_PASS(mgl_f32m4x4_equal_e(&m1, &m2, 0.001f));

		mgl_f32q4_angle_axis(mgl_f32_deg_to_rad(45.0f), 0.0f, 0.0f, 1.0f, &q1);
		mgl_f32q4_to_m4x4(&q1, &m2);
		mgl_f32m4x4_rotate_z(mgl_f32_deg_to_rad(45.0f), &m1);
		TEST_REQUIRE_PASS(mgl_f32m4x4_equal_e(&m1, &m2, 0.001f));
	}

	mgl_terminate();
	EXIT_PASS();
}