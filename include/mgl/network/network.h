#ifndef MGL_NETWORK_NETWORK_H
#define MGL_NETWORK_NETWORK_H

#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Inits the network library.
	/// </summary>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_network_init(void);

	/// <summary>
	///		Terminates the network library.
	/// </summary>
	void MGL_API mgl_network_terminate(void);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_NETWORK_NETWORK_H
