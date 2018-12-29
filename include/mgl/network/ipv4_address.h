#ifndef MGL_NETWORK_IPV4_ADDRESS_H
#define MGL_NETWORK_IPV4_ADDRESS_H

#include <mgl/error.h>
#include <mgl/string/manipulation.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_IPV4_ADDRESS_MAX_DATA_SIZE 32

	typedef struct
	{
		mgl_u32_t ip;
		mgl_bool_t valid;
	} mgl_ipv4_address_t;

	mgl_ipv4_address_t mgl_ipv4_address_none;
	mgl_ipv4_address_t mgl_ipv4_address_any;
	mgl_ipv4_address_t mgl_ipv4_address_local_host;
	mgl_ipv4_address_t mgl_ipv4_address_broadcast;

	/// <summary>
	///		Creates an IPV4 address.
	/// </summary>
	/// <param name="address">Out IPV4 address struct</param>
	/// <param name="ip">IPV4 address string</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_create_ipv4_address(mgl_ipv4_address_t* address, const mgl_chr8_t* ip);

	/// <summary>
	///		Creates an IPV4 address from four bytes.
	/// </summary>
	/// <param name="address">Out IPV4 address struct</param>
	/// <param name="b0">Byte 0</param>
	/// <param name="b1">Byte 1</param>
	/// <param name="b2">Byte 2</param>
	/// <param name="b3">Byte 3</param>
	void MGL_API mgl_create_ipv4_address_bytes(mgl_ipv4_address_t* address, mgl_u8_t b0, mgl_u8_t b1, mgl_u8_t b2, mgl_u8_t b3);

	/// <summary>
	///		Creates an IPV4 address from four bytes.
	/// </summary>
	/// <param name="address">Out IPV4 address struct</param>
	/// <param name="b0">Byte 0</param>
	/// <param name="b1">Byte 1</param>
	/// <param name="b2">Byte 2</param>
	/// <param name="b3">Byte 3</param>
	void MGL_API mgl_create_ipv4_address_u32(mgl_ipv4_address_t* address, mgl_u32_t ip);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_NETWORK_IPV4_ADDRESS_H
