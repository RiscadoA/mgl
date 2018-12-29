#ifdef __unix__

#include <mgl/network/network.h>
#include <mgl/network/ipv4_address.h>

mgl_error_t MGL_API mgl_network_init(void)
{
	// Init IP addresses
	mgl_create_ipv4_address_bytes(&mgl_ipv4_address_any, 0, 0, 0, 0);
	mgl_create_ipv4_address_bytes(&mgl_ipv4_address_local_host, 127, 0, 0, 1);
	mgl_create_ipv4_address_bytes(&mgl_ipv4_address_broadcast, 255, 255, 255, 255);

	return MGL_ERROR_NONE;
}

void MGL_API mgl_network_terminate(void)
{
	// Do nothing
}

#endif
