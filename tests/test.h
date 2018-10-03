#ifndef TEST_H
#define TEST_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

#define EXIT_FAIL() do { printf("Test failed"); exit(EXIT_FAILURE); } while (0)
#define EXIT_PASS() do { printf("Test passed"); exit(EXIT_SUCCESS); } while (0)

#ifdef __cplusplus
#define TEST_REQUIRE_PASS(condition) do { try { if (!(condition)) EXIT_FAIL(); } catch (...) { EXIT_FAIL(); } } while (0)
#define TEST_REQUIRE_FAIL(condition) do { try { if ((condition)) EXIT_FAIL(); } catch (...) { } } while (0)
#else
#define TEST_REQUIRE_PASS(condition) do { if (!(condition)) EXIT_FAIL(); } while (0)
#define TEST_REQUIRE_FAIL(condition) do { if ((condition)) EXIT_FAIL(); } while (0)
#endif

#ifdef __cplusplus
}
#endif
#endif // TEST_H