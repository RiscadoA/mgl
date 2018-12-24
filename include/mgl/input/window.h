#ifndef MGL_INPUT_WINDOW_H
#define MGL_INPUT_WINDOW_H

#include <mgl/error.h>
#include <mgl/input/input_manager.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/*
		When a window is opened, it registers buttons, axes and actions in the chosen input manager.
		The following names are the default names for each button, axis and action:

		Buttons:
		"mouse_l": Left mouse button
		"mouse_r": Right mouse button
		"mouse_m": Middle mouse button
		"mouse_x1": Extra mouse button 1
		"mouse_x2": Extra mouse button 2

		Axes:
		"mouse_x": X mouse coordinate [0; 1]
		"mouse_y": Y mouse coordinate [0; 1]
		"mouse_w": Mouse wheel delta [-1; 1]

		Actions:
		"window_close": Fired when the window close button is pressed
		"mouse_enter": Fired when the mouse enters the window
		"mouse_leave": Fired when the mouse leaves the window

		The keyboard key button names are not the same between each platform.
		To get a keyboard key button you must use mgl_get_window_key_button with the
		key code (defined on mgl/input/keyboard.h) as a parameter.
		A mouse button may also be gotten using mgl_get_window_mouse_button with the
		button code (defined on mgl/input/mouse.h) as a parameter.

		It is not recommended to get the buttons/axes/actions using the string names when using multiple windows,
		since the name for the actions of the multiple windows will be the same.
		Instead one should use the getter specific to that button/axis/action.
	*/

	enum
	{
		MGL_WINDOW_CLOSE,
		MGL_WINDOW_MOUSE_ENTER,
		MGL_WINDOW_MOUSE_LEAVE,

		MGL_WINDOW_ACTION_COUNT
	};

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
		mgl_u32_t(*get_mouse_axis)(void* window, mgl_enum_t mouse_axis);
		mgl_u32_t(*get_action)(void* window, mgl_enum_t window_action);
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
	/// <returns>Button ID</returns>
	mgl_u32_t MGL_API mgl_get_window_key_button(void* window, mgl_enum_t key_code);

	/// <summary>
	///		Gets the button ID of a certain mouse button.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <param name="mouse_button">Mouse button</param>
	/// <returns>Button ID</returns>
	mgl_u32_t MGL_API mgl_get_window_mouse_button(void* window, mgl_enum_t mouse_button);

	/// <summary>
	///		Gets the ID of a certain mouse axis.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <param name="mouse_axis">Mouse axis</param>
	/// <returns>Axis ID</returns>
	mgl_u32_t MGL_API mgl_get_window_mouse_axis(void* window, mgl_enum_t mouse_axis);

	/// <summary>
	///		Gets the action ID of a certain window action.
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <param name="window_action">Window action</param>
	/// <returns>Action ID</returns>
	mgl_u32_t MGL_API mgl_get_window_action(void* window, mgl_enum_t window_action);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_WINDOW_H
