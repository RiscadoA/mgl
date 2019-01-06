#include <mgl/entry.h>
#include <mgl/stream/stream.h>
#include <mgl/math/perlin_noise.h>

int main(int argc, char** argv)
{
	if (mgl_init() != MGL_ERROR_NONE)
		return 1;

	for (mgl_u64_t x = 0; x < 10; ++x)
	{
		mgl_print_f64(mgl_stdout_stream, mgl_perlin_noise_2d(x, 0.0f, 0), 10, 2);
		mgl_put_char(mgl_stdout_stream, '\n');
	}

	mgl_terminate();
	return 0;
}
