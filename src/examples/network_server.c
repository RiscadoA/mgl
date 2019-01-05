#include <mgl/network/tcp_listener.h>
#include <mgl/network/tcp_socket.h>
#include <mgl/stream/stream.h>
#include <mgl/entry.h>

#define SERVER_PORT 34197

int main(int argc, char** argv)
{
	if (mgl_init() != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to init MGL");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 1;
	}

	mgl_tcp_listener_t listener;
	if (mgl_create_tcp_listener(&listener) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to create listener");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 3;
	}

	if (mgl_tcp_listen_ipv4(&listener, SERVER_PORT, NULL) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Couldn't listen to incoming connections");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 4;
	}
	else mgl_print(mgl_stdout_stream, u8"Listening for incoming connections...\n");

	mgl_tcp_socket_t socket;
	if (mgl_tcp_accept(&listener, &socket) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to accept client connection");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 4;
	}
	else mgl_print(mgl_stdout_stream, u8"Client connected\n");

	mgl_chr8_t send_msg[] = u8"Hello client!";
	mgl_u64_t ssize;
	if (mgl_tcp_send(&socket, send_msg, sizeof(send_msg), &ssize) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to send message to client");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 6;
	}

	mgl_chr8_t msg[256];
	mgl_u64_t rsize;
	if (mgl_tcp_receive(&socket, msg, 256, &rsize) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to receive message from client");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 5;
	}

	mgl_print(mgl_stdout_stream, u8"Received message from client: ");
	mgl_print(mgl_stdout_stream, msg);

	mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
	mgl_terminate();
	return 0;
}
