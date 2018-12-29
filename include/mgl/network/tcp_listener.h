#ifndef MGL_NETWORK_TCP_LISTENER_H
#define MGL_NETWORK_TCP_LISTENER_H

#include <mgl/error.h>
#include <mgl/network/tcp_socket.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_TCP_LISTENER_MAX_DATA_SIZE 32

	typedef struct
	{
		mgl_u8_t data[MGL_TCP_LISTENER_MAX_DATA_SIZE];
	} mgl_tcp_listener_t;
	
	/// <summary>
	///		Creates a new TCP listener.
	/// </summary>
	/// <param name="listener">Listener pointer</param>
	/// <param name="port">Port to listen on</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_create_tcp_listener(mgl_tcp_listener_t* listener, mgl_u16_t port);

	/// <summary>
	///		Destroys a TCP listener.
	/// </summary>
	/// <param name="listener">Listener pointer</param>
	void MGL_API mgl_destroy_tcp_listener(mgl_tcp_listener_t* listener);

	/// <summary>
	///		Makes a TCP listener listen to incoming connections.
	/// </summary>
	/// <param name="listener">Listener pointer</param>
	/// <param name="queue_max_size">Max incoming connections queue size</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_tcp_listen(mgl_tcp_listener_t* listener, mgl_u64_t queue_max_size);

	/// <summary>
	///		Accepts an incoming connection.
	/// </summary>
	/// <param name="listener">Listener</param>
	/// <param name="socket">Out socket</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_tcp_accept(mgl_tcp_listener_t* listener, mgl_tcp_socket_t* socket);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_NETWORK_TCP_LISTENER_H
