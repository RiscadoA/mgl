#ifdef _WIN32

#include <mgl/network/network.h>
#include <mgl/network/ipv4_address.h>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

mgl_error_t MGL_API mgl_network_init(void)
{
	// Init IP addresses
	mgl_create_ipv4_address_bytes(&mgl_ipv4_address_any, 0, 0, 0, 0);
	mgl_create_ipv4_address_bytes(&mgl_ipv4_address_local_host, 127, 0, 0, 1);
	mgl_create_ipv4_address_bytes(&mgl_ipv4_address_broadcast, 255, 255, 255, 255);

	// Init winsock
	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		return MGL_ERROR_EXTERNAL;
	return MGL_ERROR_NONE;
}

void MGL_API mgl_network_terminate(void)
{
	MGL_DEBUG_ASSERT(WSACleanup() == 0);
}

#endif