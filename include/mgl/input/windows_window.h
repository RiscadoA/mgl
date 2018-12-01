#ifndef MGL_INPUT_WINDOWS_WINDOW_H
#define MGL_INPUT_WINDOWS_WINDOW_H

#include <mgl/input/window.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct
	{
		mgl_window_base_t base;
		void* hwnd;
		mgl_u32_t width, height;
		mgl_enum_t mode;
		mgl_bool_t tracking, alt, control, system, shift;
	} mgl_windows_window_t;

	typedef struct
	{
		const mgl_chr8_t* title;
		mgl_u32_t width, height;
		mgl_enum_t mode;
	} mgl_windows_window_settings_t;

	/// <summary>
	///		Opens a Windows API window.
	///		The window type name is "windows".
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
