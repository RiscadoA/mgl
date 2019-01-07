#include <mgl/api_utils.h>

#ifdef MGL_SYSTEM_POSIX_COMPATIBLE

#include <mgl/network/ipv4_address.h>
#include <mgl/string/manipulation.h>
#include <mgl/memory/manipulation.h>

mgl_ipv4_address_t mgl_ipv4_address_none = { 0, MGL_FALSE };
mgl_ipv4_address_t mgl_ipv4_address_any = { 0, MGL_FALSE };
mgl_ipv4_address_t mgl_ipv4_address_local_host = { 0, MGL_FALSE };
mgl_ipv4_address_t mgl_ipv4_address_broadcast = { 0, MGL_FALSE };

#include <sys/socket.h>

mgl_error_t MGL_API mgl_create_ipv4_address(mgl_ipv4_address_t * address, const mgl_chr8_t * ip)
{
	MGL_DEBUG_ASSERT(address != NULL && ip != NULL);

	address->ip = 0;
	address->valid = MGL_FALSE;

	/*if (mgl_str_equal(ip, u8"255.255.255.255"))
	{
		address->ip = INADDR_BROADCAST;
		address->valid = MGL_TRUE;
	}
	else if (mgl_str_equal(ip, u8"0.0.0.0"))
	{
		address->ip = INADDR_ANY;
		address->valid = MGL_FALSE;
	}
	else
	{
		address->ip = inet_addr(ip);
		if (address->ip != INADDR_NONE)
			address->valid = MGL_TRUE;
		else
		{
			struct addrinfo hints;
			mgl_mem_set(&hints, sizeof(hints), 0);
			hints.ai_family = AF_INET;
			struct addrinfo* result = NULL;
			if (getaddrinfo(ip, NULL, &hints, &result) == 0)
				if (result)
				{
					address->ip = ((struct sockaddr_in*)result->ai_addr)->sin_addr.s_addr;
					address->valid = MGL_TRUE;
					freeaddrinfo(result);
					return MGL_ERROR_//NOT FOUND;
				}
		}
	}*/

	// TO DO
	return MGL_ERROR_NONE;
}

void MGL_API mgl_create_ipv4_address_bytes(mgl_ipv4_address_t * address, mgl_u8_t b0, mgl_u8_t b1, mgl_u8_t b2, mgl_u8_t b3)
{
	MGL_DEBUG_ASSERT(address != NULL);
	address->ip = htonl(((mgl_u32_t)b0 << 24) | ((mgl_u32_t)b1 << 16) | ((mgl_u32_t)b2 << 8) | (mgl_u32_t)b3);
	address->valid = MGL_TRUE;
}

void MGL_API mgl_create_ipv4_address_u32(mgl_ipv4_address_t * address, mgl_u32_t ip)
{
	MGL_DEBUG_ASSERT(address != NULL);
	address->ip = htonl(ip);
	address->valid = MGL_TRUE;
}

#endif
