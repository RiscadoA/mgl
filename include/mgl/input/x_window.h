#ifndef MGL_INPUT_X_WINDOW_H
#define MGL_INPUT_X_WINDOW_H

#include <mgl/input/window.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __unix__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#endif // __unix__

	typedef struct
	{
		mgl_window_base_t base;
		mgl_u32_t width, height;
		mgl_enum_t mode;
        mgl_input_manager_t* input_manager;
        mgl_button_t* keyboard_buttons[256];
        mgl_button_t* mouse_buttons[5];
        mgl_axis_t* mouse_x_axis;
        mgl_axis_t* mouse_y_axis;
        mgl_axis_t* mouse_wheel_axis;
#ifdef __unix__
		Display* display;
        int screen;
        Window window;
        GC gc;
#endif // __unix__
	} mgl_x_window_t;

	typedef struct
	{
		const mgl_chr8_t* title;
		mgl_u32_t width, height;
		mgl_enum_t mode;
		mgl_input_manager_t* input_manager;
	} mgl_x_window_settings_t;

	/// <summary>
	///		Opens a Xlib window.
	///		The window type name is "xlib".
	/// </summary>
	/// <param name="window">Window pointer</param>
	/// <param name="settings">Settings pointer</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_open_x_window(mgl_x_window_t* window, const mgl_x_window_settings_t* settings);

	/// <summary>
	///		Closes a X11 window.
	/// </summary>
	/// <param name="window">Window pointer</param>
	void MGL_API mgl_close_x_window(mgl_x_window_t* window);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_X_WINDOW_H
