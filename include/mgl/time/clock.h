#ifndef MGL_TIME_CLOCK_H
#define MGL_TIME_CLOCK_H

#include <mgl/time/time.h>
#include <mgl/api_utils.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_MAX_CLOCK_DATA_SIZE 16

	typedef struct 
	{
		mgl_u8_t data[MGL_MAX_CLOCK_DATA_SIZE];
	} mgl_clock_t;

	void MGL_API mgl_clock_start(mgl_clock_t* clock);

	void MGL_API mgl_clock_pause(mgl_clock_t* clock);

	void MGL_API mgl_clock_resume(mgl_clock_t* clock);

	mgl_time_t MGL_API mgl_clock_get_elapsed_time(mgl_clock_t* clock);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_TIME_CLOCK_H
