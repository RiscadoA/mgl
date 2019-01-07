#include <mgl/network/tcp_socket.h>
#include <mgl/network/selector.h>
#include <mgl/thread/thread.h>
#include <mgl/thread/atomic.h>
#include <mgl/stream/stream.h>
#include <mgl/entry.h>

#define SERVER_PORT 34197

mgl_atomic_i8_t running;

void send_message_thread(void* param)
{
	mgl_tcp_socket_t* socket = (mgl_tcp_socket_t*)param;
	
	while (mgl_load_atomic_i8(&running))
	{
		mgl_chr8_t input[256] = { 0 };
		mgl_read_chars_until(mgl_stdin_stream, input, sizeof(input) - 1, NULL, u8"\n");

		if (mgl_str_equal(input, u8"/quit"))
			mgl_store_atomic_i8(&running, MGL_FALSE);
		else
		{
			mgl_error_t err = mgl_tcp_send(socket, input, sizeof(input), NULL);
			MGL_ASSERT(err == MGL_ERROR_NONE);
		}
	}
}

void receive_message_thread(void* param)
{
	mgl_tcp_socket_t* socket = (mgl_tcp_socket_t*)param;
	mgl_selector_t selector;
	MGL_ASSERT(mgl_create_selector(&selector) == MGL_ERROR_NONE);
	MGL_ASSERT(mgl_selector_add_tcp_socket(&selector, socket) == MGL_ERROR_NONE);

	mgl_chr8_t msg[256];

	while (mgl_load_atomic_i8(&running))
		if (mgl_selector_wait(&selector, 1000000))
		{
			mgl_error_t err = mgl_tcp_receive(socket, msg, sizeof(msg), NULL);
			if (err == MGL_ERROR_DISCONNECTED)
			{
				mgl_print(mgl_stdout_stream, u8"[CONNECTION CLOSED]\n");
				break;
			}

			mgl_print(mgl_stdout_stream, u8"RECV: ");
			mgl_print(mgl_stdout_stream, msg);
			mgl_print(mgl_stdout_stream, u8"\n");
		}

	mgl_destroy_selector(&selector);
}

int main(int argc, char** argv)
{
	if (mgl_init() != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to init MGL");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 1;
	}

	mgl_tcp_socket_t socket;
	
	mgl_print(mgl_stdout_stream, u8"Enter 'h' to host, anything else to connect: ");
	{
		mgl_chr8_t str[64] = { 0 };
		mgl_read_chars_until(mgl_stdin_stream, str, sizeof(str), NULL, u8"\n");
		if (mgl_str_equal(str, u8"h"))
		{
			// Listen
			mgl_tcp_listener_t listener;
			MGL_ASSERT(mgl_create_tcp_socket(&listener) == MGL_ERROR_NONE);

			mgl_print(mgl_stdout_stream, u8"Listening for incoming connections...\n");
			
			if (mgl_tcp_listen_ipv4(&listener, SERVER_PORT, &mgl_ipv4_address_any) != MGL_ERROR_NONE)
			{
				mgl_print(mgl_stdout_stream, u8"Failed to listen for incoming connections");
				mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
				return 2;
			}

			if (mgl_tcp_accept(&listener, &socket) != MGL_ERROR_NONE)
			{
				mgl_print(mgl_stdout_stream, u8"Failed to accept incoming connection");
				mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
				return 3;
			}

			mgl_print(mgl_stdout_stream, u8"Client connected\n");

			mgl_destroy_tcp_listener(&listener);
		}
		else
		{
			// Connect
			mgl_print(mgl_stdout_stream, u8"Enter the IPV4 address: ");
			mgl_ipv4_address_t ip;
			{
				mgl_chr8_t str[64] = { 0 };
				mgl_read_chars_until(mgl_stdin_stream, str, sizeof(str), NULL, u8"\n");
				if (mgl_create_ipv4_address(&ip, str) != MGL_ERROR_NONE)
				{
					mgl_print(mgl_stdout_stream, u8"Invalid address");
					mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
					return 4;
				}
				mgl_print(mgl_stdout_stream, u8"Connecting to server\n");
			}

			if (mgl_create_tcp_socket(&socket) != MGL_ERROR_NONE)
			{
				mgl_print(mgl_stdout_stream, u8"Failed to create socket");
				mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
				return 5;
			}

			mgl_error_t err = mgl_tcp_connect_ipv4(&socket, &ip, SERVER_PORT, 0);
			if (err == MGL_ERROR_NOT_READY)
			{
				mgl_selector_t selector;
				if (mgl_create_selector(&selector) != MGL_ERROR_NONE)
				{
					mgl_print(mgl_stdout_stream, u8"Failed to create selector");
					mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
					return 6;
				}

				if (mgl_selector_add_tcp_socket(&selector, &socket) != MGL_ERROR_NONE)
				{
					mgl_print(mgl_stdout_stream, u8"Failed to add socket to selector");
					mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
					return 7;
				}

				if (!mgl_selector_wait(&selector, 5000))
				{
					mgl_print(mgl_stdout_stream, u8"Connection timed out");
					mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
					return 8;
				}
			}
			else if (err != MGL_ERROR_NONE)
			{
				mgl_print(mgl_stdout_stream, u8"Couldn't connect to server");
				mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
				return 9;
			}

			mgl_print(mgl_stdout_stream, u8"Connected to server\n");
		}
	}

	mgl_thread_t thread;
	mgl_store_atomic_i8(&running, MGL_TRUE);
	if (mgl_create_thread(&thread, &send_message_thread, &socket) != MGL_ERROR_NONE)
	{
		mgl_print(mgl_stdout_stream, u8"Failed to create thread");
		mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
		return 10;
	}

	receive_message_thread(&socket);

	mgl_wait_for_thread(&thread, 0);
	mgl_destroy_thread(&thread);

	mgl_print(mgl_stdout_stream, u8"Enter any input to close application...");
	mgl_read_chars_until(mgl_stdin_stream, NULL, 0, NULL, u8"\n");
	mgl_terminate();
	return 0;
}
