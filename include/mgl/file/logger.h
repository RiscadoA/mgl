#ifndef MGL_FILE_LOGGER_H
#define MGL_FILE_LOGGER_H

#include <mgl/type.h>
#include <mgl/api_utils.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct mgl_logger_t mgl_logger_t;

	/// <summary>
	///		Opens a logger.
	/// </summary>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="name">Log file name</param>
	/// <returns>Pointer to logger</returns>
	mgl_logger_t* MGL_API mgl_logger_open(void* allocator, const mgl_chr8_t* name);

	/// <summary>
	///		Outputs the log file.
	/// </summary>
	/// <param name="logger">Logger</param>
	/// <param name="text">Text</param>
	void MGL_API mgl_logger_add(mgl_logger_t* logger, const mgl_chr8_t* text);

	/// <summary>
	///		Closes a logger.
	/// </summary>
	/// <param name="logger">Logger</param>
	void MGL_API mgl_logger_close(mgl_logger_t* logger);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_FILE_LOGGER_H
