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

mgl_window_on_close_callback_t MGL_API mgl_set_window_on_close_callback(void * window, mgl_window_on_close_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_close_callback_t old = window_base->close_callback;
	window_base->close_callback = callback;
	return old;
}

mgl_window_on_mouse_enter_callback_t MGL_API mgl_set_window_on_mouse_enter_callback(void * window, mgl_window_on_mouse_enter_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_close_callback_t old = window_base->close_callback;
	window_base->close_callback = callback;
	return old;
}

mgl_window_on_mouse_leave_callback_t MGL_API mgl_set_window_on_mouse_leave_callback(void * window, mgl_window_on_mouse_leave_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_mouse_leave_callback_t old = window_base->mouse_leave_callback;
	window_base->mouse_leave_callback = callback;
	return old;
}

mgl_window_on_mouse_move_callback_t MGL_API mgl_set_window_on_mouse_move_callback(void * window, mgl_window_on_mouse_move_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_mouse_move_callback_t old = window_base->mouse_move_callback;
	window_base->mouse_move_callback = callback;
	return old;
}

mgl_window_on_mouse_scroll_callback_t MGL_API mgl_set_window_on_mouse_scroll_callback(void * window, mgl_window_on_mouse_scroll_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_mouse_scroll_callback_t old = window_base->mouse_scroll_callback;
	window_base->mouse_scroll_callback = callback;
	return old;
}

mgl_window_on_key_down_callback_t MGL_API mgl_set_window_on_key_down_callback(void * window, mgl_window_on_key_down_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_key_down_callback_t old = window_base->key_down_callback;
	window_base->key_down_callback = callback;
	return old;
}

mgl_window_on_key_up_callback_t MGL_API mgl_set_window_on_key_up_callback(void * window, mgl_window_on_key_up_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_key_up_callback_t old = window_base->key_up_callback;
	window_base->key_up_callback = callback;
	return old;
}

mgl_window_on_mouse_down_callback_t MGL_API mgl_set_window_on_mouse_down_callback(void * window, mgl_window_on_mouse_down_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_mouse_down_callback_t old = window_base->mouse_down_callback;
	window_base->mouse_down_callback = callback;
	return old;
}

mgl_window_on_mouse_up_callback_t MGL_API mgl_set_window_on_mouse_up_callback(void * window, mgl_window_on_mouse_up_callback_t callback)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_window_base_t* window_base = (mgl_window_base_t*)window;
	mgl_window_on_mouse_up_callback_t old = window_base->mouse_up_callback;
	window_base->mouse_up_callback = callback;
	return old;
}
