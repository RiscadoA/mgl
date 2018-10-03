#ifndef MGL_ENTRY_H
#define MGL_ENTRY_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Initializes the Magma Game Library.
	/// </summary>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_init(void);

	/// <summary>
	///		Terminates the Magma Game Library.
	/// </summary>
	void MGL_API mgl_terminate(void);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_ENTRY_H
