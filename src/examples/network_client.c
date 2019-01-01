#include <mgl/network/tcp_socket.h>
#include <mgl/stream/stream.h>
#include <mgl/entry.h>

#define SERVER_PORT 6702

int main(int argc, char** argv)
{
	if (mgl_init() != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to init MGL");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 1;
	}

	mgl_print(mgl_stdout_stream, u8"Enter the server IPV4 address: ");
	mgl_ipv4_address_t ip;
	{
		mgl_chr8_t str[64] = { 0 };
		mgl_read_chars_until(mgl_stdin_stream, str, sizeof(str), NULL, u8"\n");
		if (mgl_create_ipv4_address(&ip, str) != MGL_ERROR_NONE)
		{
			mgl_print(mgl_stdout_stream, u8"Invalid address");
			mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
			return 2;
		}
		mgl_print(mgl_stdout_stream, u8"Connecting to server\n");
	}

	mgl_tcp_socket_t socket;
	if (mgl_create_tcp_socket(&socket) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to create socket");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 3;
	}

	if (mgl_tcp_connect_ipv4(&socket, &ip, SERVER_PORT) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Couldn't connect to server");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 4;
	}
	else mgl_print(mgl_stdout_stream, u8"Connected to server\n");

	mgl_chr8_t msg[256];
	mgl_u64_t rsize;
	if (mgl_tcp_receive(&socket, msg, 256, &rsize) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to receive message from server");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 5;
	}
	
	mgl_print(mgl_stdout_stream, u8"Received message from server: ");
	mgl_print(mgl_stdout_stream, msg);

	mgl_chr8_t send_msg[] = u8"Hello server!";
	mgl_u64_t ssize;
	if (mgl_tcp_send(&socket, send_msg, sizeof(send_msg), &ssize) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to send message to server");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 6;
	}

	mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
	mgl_terminate();
	return 0;
}
