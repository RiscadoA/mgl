#ifdef _WIN32
#include <mgl/network/tcp_listener.h>
#include <mgl/memory/manipulation.h>
#include <mgl/string/conversion.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")

MGL_STATIC_ASSERT(sizeof(SOCKET) <= MGL_TCP_LISTENER_MAX_DATA_SIZE, "TCP listener struct too big");

mgl_error_t MGL_API mgl_create_tcp_listener(mgl_tcp_listener_t * l)
{
	MGL_DEBUG_ASSERT(l != NULL);
	
	*(SOCKET*)l->data = INVALID_SOCKET;
	
	return MGL_ERROR_NONE;
}

void MGL_API mgl_destroy_tcp_listener(mgl_tcp_listener_t * l)
{
	MGL_DEBUG_ASSERT(l != NULL);

	if (*(SOCKET*)l->data != INVALID_SOCKET)
	{
		closesocket(*(SOCKET*)l->data);
		*(SOCKET*)l->data = INVALID_SOCKET;
	}
}

mgl_error_t MGL_API mgl_tcp_listen_ipv4(mgl_tcp_listener_t * l, mgl_u16_t port, const mgl_ipv4_address_t* address)
{
	MGL_DEBUG_ASSERT(l != NULL && !(address != NULL && !address->valid));

	if (address == NULL)
		address = &mgl_ipv4_address_any;

	if (*(SOCKET*)l->data != INVALID_SOCKET)
	{
		closesocket(*(SOCKET*)l->data);
		*(SOCKET*)l->data = INVALID_SOCKET;
	}

	SOCKET             ls;
	SOCKADDR_IN        ServerAddr;

	ls = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ls == INVALID_SOCKET)
		return MGL_ERROR_EXTERNAL;


	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port);
	ServerAddr.sin_addr.s_addr = address->ip;

	if (bind(ls, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		closesocket(ls);
		return MGL_ERROR_EXTERNAL;
	}

	if (listen(ls, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(ls);
		return MGL_ERROR_EXTERNAL;
	}

	*(SOCKET*)l->data = ls;

	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_tcp_accept(mgl_tcp_listener_t * l, mgl_tcp_socket_t * s)
{
	MGL_DEBUG_ASSERT(l != NULL && s != NULL);

	if (*(SOCKET*)l->data == INVALID_SOCKET)
		return MGL_ERROR_NOT_LISTENING;
	if (*(SOCKET*)s->data != INVALID_SOCKET)
		closesocket(*(SOCKET*)s->data);

	*(SOCKET*)s->data = accept(*(SOCKET*)l->data, NULL, NULL);
	if (*(SOCKET*)s->data == INVALID_SOCKET)
		switch (WSAGetLastError())
		{
			case WSAEWOULDBLOCK:  return MGL_ERROR_NOT_READY;
			case WSAEALREADY:     return MGL_ERROR_NOT_READY;
			case WSAECONNABORTED: return MGL_ERROR_DISCONNECTED;
			case WSAECONNRESET:   return MGL_ERROR_DISCONNECTED;
			case WSAETIMEDOUT:    return MGL_ERROR_DISCONNECTED;
			case WSAENETRESET:    return MGL_ERROR_DISCONNECTED;
			case WSAENOTCONN:     return MGL_ERROR_DISCONNECTED;
			case WSAEISCONN:      return MGL_ERROR_NONE;
			default:              return MGL_ERROR_EXTERNAL;
		}

	/*u_long block = 0; // Block
	ioctlsocket(*(SOCKET*)s->data, FIONBIO, &block);

	int y = 1;
	if (setsockopt(*(SOCKET*)s->data, IPPROTO_TCP, TCP_NODELAY, (char*)&y, sizeof(y)) == SOCKET_ERROR)
		return MGL_ERROR_EXTERNAL;*/

	return MGL_ERROR_NONE;
}

void MGL_API mgl_tcp_listener_set_blocking(mgl_tcp_listener_t * l, mgl_bool_t blocking)
{
	MGL_DEBUG_ASSERT(l != NULL);
	l->is_blocking = blocking;
	u_long b = blocking ? 0 : 1;
	ioctlsocket(*(SOCKET*)l->data, FIONBIO, &b);
}

mgl_bool_t MGL_API mgl_tcp_listener_is_blocking(mgl_tcp_listener_t * l)
{
	MGL_DEBUG_ASSERT(l != NULL);
	return l->is_blocking;
}

#endif