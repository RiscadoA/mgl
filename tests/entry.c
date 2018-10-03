#include <mgl/entry.h>
#include "test.h"

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);
	mgl_terminate();
	EXIT_PASS();
}