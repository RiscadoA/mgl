#include <mgl/input/window.h>

const mgl_chr8_t *MGL_API mgl_get_window_type(void * window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_type(window);
}

mgl_u32_t MGL_API mgl_get_window_width(void * window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_width(window);
}

mgl_u32_t MGL_API mgl_get_window_height(void * window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_height(window);
}

mgl_enum_t MGL_API mgl_get_window_mode(void * window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_mode(window);
}

void MGL_API mgl_poll_window_events(void * window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	window_base->functions->poll_events(window);
}

void MGL_API mgl_wait_for_window_events(void * window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	window_base->functions->wait_for_events(window);
}

mgl_u32_t MGL_API mgl_get_window_key_button(void* window, mgl_enum_t key_code)
{
    MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_key_button(window, key_code);
}

mgl_u32_t MGL_API mgl_get_window_mouse_button(void* window, mgl_enum_t mouse_button)
{
    MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_mouse_button(window, mouse_button);
}

mgl_u32_t MGL_API mgl_get_window_mouse_axis(void * window, mgl_enum_t mouse_axis)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_mouse_axis(window, mouse_axis);
}

mgl_u32_t MGL_API mgl_get_window_action(void * window, mgl_enum_t window_action)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	return window_base->functions->get_action(window, window_action);
}
