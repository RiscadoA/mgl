#ifndef MGL_INPUT_WINDOWS_WINDOW_H
#define MGL_INPUT_WINDOWS_WINDOW_H

#include <mgl/input/window.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_window_base_t base;
		mgl_input_manager_t* input_manager;
		void* hwnd;
		mgl_u32_t width, height;
		mgl_enum_t mode;
		mgl_bool_t tracking;
		mgl_button_t* keyboard_buttons[256];
		mgl_button_t* mouse_buttons[5];
		mgl_axis_t* mouse_x_axis;
		mgl_axis_t* mouse_y_axis;
		mgl_axis_t* mouse_wheel_axis;
		mgl_action_t *close, *mouse_enter, *mouse_leave;
	} mgl_windows_window_t;

	typedef struct
	{
		const mgl_chr8_t* title;
		mgl_u32_t width, height;
		mgl_enum_t mode;
		mgl_input_manager_t* input_manager;
	} mgl_windows_window_settings_t;

	/// <summary>
	///		Opens a Windows API window.
	///		The window type name is "win32".
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <param name="settings">Settings pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_open_windows_window(mgl_windows_window_t* window, const mgl_windows_window_settings_t* settings);

	/// <summary>
	///		Closes a Windows API window.
	/// </summary>
	/// <param name="window">Window pointer</param>
	void MGL_API mgl_close_windows_window(mgl_windows_window_t* window);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_WINDOWS_WINDOW_H
