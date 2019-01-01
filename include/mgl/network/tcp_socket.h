#ifndef MGL_NETWORK_TCP_SOCKET_H
#define MGL_NETWORK_TCP_SOCKET_H

#include <mgl/error.h>
#include <mgl/network/ipv4_address.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_TCP_SOCKET_MAX_DATA_SIZE 32

	typedef struct 
	{
		mgl_u8_t data[MGL_TCP_SOCKET_MAX_DATA_SIZE];
	} mgl_tcp_socket_t;
	
	/// <summary>
	///		Creates a TCP socket.
	/// </summary>
	/// <param name="socket">Socket pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_create_tcp_socket(mgl_tcp_socket_t* socket);

	/// <summary>
	///		Destroys a TCP socket.
	/// </summary>
	/// <param name="socket">Socket pointer</param>
	void MGL_API mgl_destroy_tcp_socket(mgl_tcp_socket_t* socket);

	/// <summary>
	///		Connects a TCP socket to an IPV4 address.
	/// </summary>
	/// <param name="socket">Socket pointer</param>
	/// <param name="address">Address pointer</param>
	/// <param name="port">Port</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_tcp_connect_ipv4(mgl_tcp_socket_t* socket, const mgl_ipv4_address_t* address, mgl_u16_t port);

	/// <summary>
	///		Sends data to a TCP connection.
	/// </summary>
	/// <param name="socket">Socket pointer</param>
	/// <param name="data">Data to send</param>
	/// <param name="size">Data size to send</param>
	/// <param name="sent_size">Sent size</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_tcp_send(mgl_tcp_socket_t* socket, const void* data, mgl_u64_t size, mgl_u64_t* sent_size);

	/// <summary>
	///		Receives data from a TCP connection.
	/// </summary>
	/// <param name="socket">Socket pointer</param>
	/// <param name="data">Data to receive</param>
	/// <param name="size">Data size to receive</param>
	/// <param name="received_size">Received size</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_tcp_receive(mgl_tcp_socket_t* socket, void* data, mgl_u64_t size, mgl_u64_t* received_size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_NETWORK_TCP_SOCKET_H
