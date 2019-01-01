#ifdef _WIN32
#include <mgl/network/tcp_socket.h>
#include <mgl/memory/manipulation.h>

#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")

mgl_error_t MGL_API mgl_create_tcp_socket(mgl_tcp_socket_t * s)
{
	MGL_DEBUG_ASSERT(s != NULL);
	*(SOCKET*)s->data = INVALID_SOCKET;
	return MGL_ERROR_NONE;
}

void MGL_API mgl_destroy_tcp_socket(mgl_tcp_socket_t * s)
{
	MGL_DEBUG_ASSERT(s != NULL);

	if (*(SOCKET*)s->data != INVALID_SOCKET)
	{
		closesocket(*(SOCKET*)s->data);
		*(SOCKET*)s->data = INVALID_SOCKET;
	}
}

mgl_error_t MGL_API mgl_tcp_connect_ipv4(mgl_tcp_socket_t * s, const mgl_ipv4_address_t * address, mgl_u16_t port)
{
	MGL_DEBUG_ASSERT(s != NULL && address != NULL);
	if (!address->valid)
		return MGL_ERROR_INVALID_ADDRESS;

	SOCKET rs = *(SOCKET*)s->data;
	if (rs != INVALID_SOCKET)
		closesocket(rs);
	rs = socket(PF_INET, SOCK_STREAM, 0);
	if (rs == INVALID_SOCKET)
		return MGL_ERROR_EXTERNAL;
	int v = 1;
	if (setsockopt(rs, IPPROTO_TCP, TCP_NODELAY, (const char*)&v, sizeof(v)) == -1)
		return MGL_ERROR_EXTERNAL;
	*(SOCKET*)s->data = rs;

	struct sockaddr_in addr;
	mgl_mem_set(&addr, sizeof(addr), 0);
	addr.sin_addr.s_addr = address->ip;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (connect(rs, (struct scokaddr*)&addr, sizeof(addr)) == -1)
	{
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
	}

	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_tcp_send(mgl_tcp_socket_t * s, const void * data, mgl_u64_t size, mgl_u64_t * sent_size)
{
	MGL_DEBUG_ASSERT(s != NULL && data != NULL && size != 0);
	SOCKET rs = *(SOCKET*)s->data;
	if (rs == INVALID_SOCKET)
		return MGL_ERROR_INVALID_PARAMS;

	int result = send(rs, (const char*)data, size, 0);
	if (result < 0)
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

	if (sent_size != NULL)
		*sent_size = result;

	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_tcp_receive(mgl_tcp_socket_t * s, void * data, mgl_u64_t size, mgl_u64_t * received_size)
{
	MGL_DEBUG_ASSERT(s != NULL && data != NULL && size != 0);
	SOCKET rs = *(SOCKET*)s->data;
	if (rs == INVALID_SOCKET)
		return MGL_ERROR_INVALID_PARAMS;

	int result = recv(rs, (char*)data, size, 0);
	if (result == 0)
		return MGL_ERROR_DISCONNECTED;
	else if (result < 0)
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

	if (received_size != NULL)
		*received_size = result;

	return MGL_ERROR_NONE;
}

#endif