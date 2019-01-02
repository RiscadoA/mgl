#ifndef MGL_NETWORK_SELECTOR_H
#define MGL_NETWORK_SELECTOR_H

#include <mgl/error.h>
#include <mgl/network/tcp_socket.h>
#include <mgl/network/tcp_listener.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_SELECTOR_MAX_DATA_SIZE 1048

	typedef struct
	{
		mgl_u8_t data[MGL_SELECTOR_MAX_DATA_SIZE];
	} mgl_selector_t;
	
	/// <summary>
	///		Creates a new selector.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_create_selector(mgl_selector_t* sl);

	/// <summary>
	///		Destroys a selector.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	void MGL_API mgl_destroy_selector(mgl_selector_t* sl);

	/// <summary>
	///		Adds a TCP socket to a selector.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <param name="s">Socket pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_selector_add_tcp_socket(mgl_selector_t* sl, mgl_tcp_socket_t* s);
	
	/// <summary>
	///		Removes a TCP socket from a selector.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <param name="s">Socket pointer</param>
	void MGL_API mgl_selector_remove_tcp_socket(mgl_selector_t* sl, mgl_tcp_socket_t* s);

	/// <summary>
	///		Adds a TCP listener to a selector.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <param name="l">Listener pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_selector_add_tcp_listener(mgl_selector_t* sl, mgl_tcp_listener_t* l);

	/// <summary>
	///		Removes a TCP listener from a selector.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <param name="l">Listener pointer</param>
	void MGL_API mgl_selector_remove_tcp_listener(mgl_selector_t* sl, mgl_tcp_listener_t* l);

	/// <summary>
	///		Removes all added sockets and listeners.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	void MGL_API mgl_selector_clear(mgl_selector_t* sl);

	/// <summary>
	///		Waits for any of the added sockets and listeners to receive data or accept a new connection.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <param name="timeout_microseconds">Timeout in microseconds</param>
	/// <returns>MGL_TRUE if data was received or there was a connection accepted, otherwise returns MGL_FALSE</returns>
	mgl_bool_t MGL_API mgl_selector_wait(mgl_selector_t* sl, mgl_u64_t timeout_microseconds);

	/// <summary>
	/// /	Checks if a TCP socket is ready to receive new data.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <param name="s">Socket pointer</param>
	/// <returns>MGL_TRUE if ready, otherwise MGL_FALSE</returns>
	mgl_bool_t MGL_API mgl_selector_is_tcp_socket_ready(mgl_selector_t* sl, mgl_tcp_socket_t* s);

	/// <summary>
	/// /	Checks if a TCP listener is ready to accept a new connection.
	/// </summary>
	/// <param name="sl">Selector pointer</param>
	/// <param name="l">Listener pointer</param>
	/// <returns>MGL_TRUE if ready, otherwise MGL_FALSE</returns>
	mgl_bool_t MGL_API mgl_selector_is_tcp_listener_ready(mgl_selector_t* sl, mgl_tcp_listener_t* l);



#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_NETWORK_SELECTOR_H
