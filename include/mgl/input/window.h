#ifndef MGL_INPUT_WINDOW_H
#define MGL_INPUT_WINDOW_H

#include <mgl/error.h>
#include <mgl/input/input_manager.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	enum
	{
		MGL_WINDOW_MODE_WINDOWED,
		MGL_WINDOW_MODE_FULLSCREEN,
		MGL_WINDOW_MODE_COUNT
	};

	typedef struct
	{
		const mgl_chr8_t*(*get_type)(void* window);
		mgl_u32_t(*get_width)(void* window);
		mgl_u32_t(*get_height)(void* window);
		mgl_enum_t(*get_mode)(void* window);
		void(*poll_events)(void* window);
		void(*wait_for_events)(void* window);
		mgl_u32_t(*get_key_button)(void* window, mgl_enum_t key_code);
		mgl_u32_t(*get_mouse_button)(void* window, mgl_enum_t mouse_button);
	} mgl_window_functions_t;

	typedef struct
	{
		mgl_window_functions_t* functions;
	} mgl_window_base_t;

	/// <summary>
	///		Gets a window's type.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <returns>The window's type name</returns>
	const mgl_chr8_t* MGL_API mgl_get_window_type(void* window);

	/// <summary>
	///		Gets a window's width.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <returns>The window's width</returns>
	mgl_u32_t MGL_API mgl_get_window_width(void* window);

	/// <summary>
	///		Gets a window's height.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <returns>The window's height</returns>
	mgl_u32_t MGL_API mgl_get_window_height(void* window);

	/// <summary>
	///		Gets a window's mode.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <returns>Window's mode</returns>
	mgl_enum_t MGL_API mgl_get_window_mode(void* window);

	/// <summary>
	///		Polls the window events.
	/// </summary>
	/// <param name="window">Window pointer</param>
	void MGL_API mgl_poll_window_events(void* window);

	/// <summary>
	///		Waits for events to happen and then polls them.
	/// </summary>
	/// <param name="window">Window pointer</param>
	void MGL_API mgl_wait_for_window_events(void* window);

    /// <summary>
	///		Gets the button ID of a certain keyboard key.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <param name="key_code">Key code</param>
	mgl_u32_t MGL_API mgl_get_window_key_button(void* window, mgl_enum_t key_code);

	/// <summary>
	///		Gets the button ID of a certain mouse button.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <param name="mouse_button">Mouse button</param>
	mgl_u32_t MGL_API mgl_get_window_mouse_button(void* window, mgl_enum_t mouse_button);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_WINDOW_H
