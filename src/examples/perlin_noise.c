#include <mgl/entry.h>
#include <mgl/stream/stream.h>
#include <mgl/math/perlin_noise.h>
#include <mgl/time/clock.h>

#define CALL_COUNT 10000000

int main(int argc, char** argv)
{
	if (mgl_init() != MGL_ERROR_NONE)
		return 1;

	mgl_clock_t clock;
	mgl_clock_start(&clock);

	mgl_f32_t x = 0.0f;
	for (mgl_u32_t n = 0; n < CALL_COUNT; ++n)
		x = mgl_perlin_noise_2d(n, n, 0);

	mgl_clock_pause(&clock);
	mgl_u64_t elapsed_time = mgl_to_microseconds(mgl_clock_get_elapsed_time(&clock));
	mgl_f64_t time_per_call = elapsed_time / (mgl_f64_t)CALL_COUNT;

	mgl_print_u64(mgl_stdout_stream, CALL_COUNT, 10);
	mgl_print(mgl_stdout_stream, u8" calls to mgl_perlin_noise_2d took ");
	mgl_print_u64(mgl_stdout_stream, elapsed_time, 10);
	mgl_print(mgl_stdout_stream, u8" microseconds\n");
	mgl_print(mgl_stdout_stream, u8"Each call took in average ");
	mgl_print_f64(mgl_stdout_stream, time_per_call, 10, 4);
	mgl_print(mgl_stdout_stream, u8" microseconds\n");

	mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");

	mgl_terminate();
	return 0;
}
