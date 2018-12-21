#include <mgl/entry.h>
#include <mgl/thread/thread.h>
#include "test.h"

typedef struct
{
    mgl_bool_t success;
} params_t;

void thread_func(void* arg)
{
    params_t* params = (params_t*)arg;
    params->success = MGL_TRUE;
}

int main(int argc, char** argv)
{
	TEST_REQUIRE_PASS(mgl_init() == MGL_ERROR_NONE);

    params_t params;
    params.success = MGL_FALSE;

    mgl_thread_t thread;
    TEST_REQUIRE_PASS(mgl_create_thread(&thread, &thread_func, &params) == MGL_ERROR_NONE);
    TEST_REQUIRE_PASS(mgl_wait_for_thread(&thread, 0) == MGL_ERROR_NONE);
    TEST_REQUIRE_PASS(mgl_destroy_thread(&thread) == MGL_ERROR_NONE);
    TEST_REQUIRE_PASS(params.success == MGL_TRUE);
	mgl_terminate();
	EXIT_PASS();
}
