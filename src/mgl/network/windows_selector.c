#ifdef _WIN32
#include <mgl/network/selector.h>
#include <mgl/memory/manipulation.h>
#include <mgl/string/conversion.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")

typedef struct
{
	FD_SET all_sockets;
	FD_SET socket_ready;
	int socket_count;
} mgl_windows_selector_t;

MGL_STATIC_ASSERT(sizeof(mgl_windows_selector_t) <= MGL_SELECTOR_MAX_DATA_SIZE, "Selector struct too big");

mgl_error_t MGL_API mgl_create_selector(mgl_selector_t * sl)
{
	MGL_DEBUG_ASSERT(sl != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	FD_ZERO(&wsl->all_sockets);
	FD_ZERO(&wsl->socket_ready);
	wsl->socket_count = 0;
	return MGL_ERROR_NONE;
}

void MGL_API mgl_destroy_selector(mgl_selector_t * sl)
{
	MGL_DEBUG_ASSERT(sl != NULL);
}

mgl_error_t MGL_API mgl_selector_add_tcp_socket(mgl_selector_t * sl, mgl_tcp_socket_t * s)
{
	MGL_DEBUG_ASSERT(sl != NULL && s != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	if (*(SOCKET*)s->data == INVALID_SOCKET)
		return MGL_ERROR_INVALID_PARAMS;
	if (wsl->socket_count >= FD_SETSIZE)
		return MGL_ERROR_OVERFLOW;
	if (FD_ISSET(*(SOCKET*)s->data, &wsl->all_sockets))
		return MGL_ERROR_NONE;

	wsl->socket_count += 1;
	FD_SET(*(SOCKET*)s->data, &wsl->all_sockets);

	return MGL_ERROR_NONE;
}

void MGL_API mgl_selector_remove_tcp_socket(mgl_selector_t * sl, mgl_tcp_socket_t * s)
{
	MGL_DEBUG_ASSERT(sl != NULL && s != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	if (*(SOCKET*)s->data == INVALID_SOCKET)
		return;
	if (!FD_ISSET(*(SOCKET*)s->data, &wsl->all_sockets))
		return;

	wsl->socket_count -= 1;
	FD_CLR(*(SOCKET*)s->data, &wsl->all_sockets);
	FD_CLR(*(SOCKET*)s->data, &wsl->socket_ready);
}

mgl_error_t MGL_API mgl_selector_add_tcp_listener(mgl_selector_t * sl, mgl_tcp_listener_t * l)
{
	MGL_DEBUG_ASSERT(sl != NULL && l != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	if (*(SOCKET*)l->data == INVALID_SOCKET)
		return MGL_ERROR_INVALID_PARAMS;
	if (wsl->socket_count >= FD_SETSIZE)
		return MGL_ERROR_OVERFLOW;
	if (FD_ISSET(*(SOCKET*)l->data, &wsl->all_sockets))
		return MGL_ERROR_NONE;

	wsl->socket_count += 1;
	FD_SET(*(SOCKET*)l->data, &wsl->all_sockets);

	return MGL_ERROR_NONE;
}

void MGL_API mgl_selector_remove_tcp_listener(mgl_selector_t * sl, mgl_tcp_listener_t * l)
{
	MGL_DEBUG_ASSERT(sl != NULL && l != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	if (*(SOCKET*)l->data == INVALID_SOCKET)
		return;
	if (!FD_ISSET(*(SOCKET*)l->data, &wsl->all_sockets))
		return;

	wsl->socket_count -= 1;
	FD_CLR(*(SOCKET*)l->data, &wsl->all_sockets);
	FD_CLR(*(SOCKET*)l->data, &wsl->socket_ready);
}

void MGL_API mgl_selector_clear(mgl_selector_t * sl)
{
	MGL_DEBUG_ASSERT(sl != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	FD_ZERO(&wsl->all_sockets);
	FD_ZERO(&wsl->socket_ready);
	wsl->socket_count = 0;
}

mgl_bool_t MGL_API mgl_selector_wait(mgl_selector_t * sl, mgl_u64_t timeout_microseconds)
{
	MGL_DEBUG_ASSERT(sl != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;

	wsl->socket_ready = wsl->all_sockets;

	if (timeout_microseconds == 0)
		return select(0, &wsl->socket_ready, NULL, NULL, NULL) > 0;

	TIMEVAL time;
	time.tv_sec = timeout_microseconds / 1000000;
	time.tv_usec = timeout_microseconds % 1000000;
	return select(0, &wsl->socket_ready, NULL, NULL, &time) > 0;
}

mgl_bool_t MGL_API mgl_selector_is_tcp_socket_ready(mgl_selector_t * sl, mgl_tcp_socket_t * s)
{
	MGL_DEBUG_ASSERT(sl != NULL && s != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	if (*(SOCKET*)s->data == INVALID_SOCKET)
		return MGL_FALSE;
	return FD_ISSET(*(SOCKET*)s->data, &wsl->socket_ready);
}

mgl_bool_t MGL_API mgl_selector_is_tcp_listener_ready(mgl_selector_t * sl, mgl_tcp_listener_t * l)
{
	MGL_DEBUG_ASSERT(sl != NULL && l != NULL);
	mgl_windows_selector_t* wsl = (mgl_windows_selector_t*)sl;
	if (*(SOCKET*)l->data == INVALID_SOCKET)
		return MGL_FALSE;
	return FD_ISSET(*(SOCKET*)l->data, &wsl->socket_ready);
}

#endif