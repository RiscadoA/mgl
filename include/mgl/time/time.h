#ifndef MGL_TIME_TIME_H
#define MGL_TIME_TIME_H

#include <mgl/type.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef mgl_i64_t mgl_time_t;

	inline mgl_i64_t mgl_to_microseconds(mgl_time_t time)
	{
		return time;
	}

	inline mgl_i64_t mgl_to_milliseconds(mgl_time_t time)
	{
		return time / 1000;
	}

	inline mgl_i64_t mgl_to_seconds(mgl_time_t time)
	{
		return time / 1000000;
	}

	inline mgl_time_t mgl_from_microseconds(mgl_i64_t t)
	{
		return t;
	}

	inline mgl_time_t mgl_from_milliseconds(mgl_i64_t t)
	{
		return t * 1000;
	}

	inline mgl_time_t mgl_from_seconds(mgl_i64_t t)
	{
		return t * 1000000;
	}


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_TIME_TIME_H
