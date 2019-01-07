#include <mgl/entry.h>
#include <mgl/stream/stream.h>
#include <mgl/input/input_manager.h>
#include <mgl/input/keyboard.h>

#ifdef MGL_SYSTEM_UNIX
#include <mgl/input/x_window.h>
#elif defined(MGL_SYSTEM_WINDOWS)
#include <mgl/input/windows_window.h>
#else
#error Unsupported platform
#endif

mgl_bool_t running = MGL_TRUE;

void quit_callback(const mgl_action_t* action, mgl_enum_t state)
{
    running = MGL_FALSE;
}

int main(int argc, char** argv)
{
    if (mgl_init() != MGL_ERROR_NONE)
        return 1;

    mgl_input_manager_t input_manager;
    mgl_init_input_manager(&input_manager);

#ifdef MGL_SYSTEM_UNIX
    mgl_x_window_settings_t settings;
    settings.width = 400;
    settings.height = 300;
    settings.mode = MGL_WINDOW_MODE_WINDOWED;
    settings.title = u8"MGL Test Window 1 (Xlib)";
    settings.input_manager = &input_manager;

    mgl_x_window_t window_1, window_2;
    MGL_ASSERT(mgl_open_x_window(&window_1, &settings) == MGL_ERROR_NONE);
    settings.title = u8"MGL Test Window 2 (Xlib)";
    MGL_ASSERT(mgl_open_x_window(&window_2, &settings) == MGL_ERROR_NONE);
#elif defined(MGL_SYSTEM_WINDOWS)
    mgl_windows_window_settings_t settings;
    settings.width = 400;
    settings.height = 300;
    settings.mode = MGL_WINDOW_MODE_WINDOWED;
    settings.title = u8"MGL Test Window 1 (Win32)";
    settings.input_manager = &input_manager;

    mgl_windows_window_t window_1, window_2;
    MGL_ASSERT(mgl_open_windows_window(&window_1, &settings) == MGL_ERROR_NONE);
    settings.title = u8"MGL Test Window 2 (Win32)";
    MGL_ASSERT(mgl_open_windows_window(&window_2, &settings) == MGL_ERROR_NONE);
#else
#error Unsupported platform
#endif

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON_SEQUENCE, u8"quit_1") == MGL_ERROR_NONE);
        action->sequence.button_count = 2;
        action->sequence.buttons[0] = mgl_get_window_key_button(&window_1, MGL_KEYBOARD_CONTROL);
        action->sequence.buttons[1] = mgl_get_window_key_button(&window_1, MGL_KEYBOARD_Q);
        action->sequence.can_release = MGL_FALSE;
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &quit_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON_SEQUENCE, u8"quit_2") == MGL_ERROR_NONE);
        action->sequence.button_count = 2;
        action->sequence.buttons[0] = mgl_get_window_key_button(&window_2, MGL_KEYBOARD_CONTROL);
        action->sequence.buttons[1] = mgl_get_window_key_button(&window_2, MGL_KEYBOARD_Q);
        action->sequence.can_release = MGL_FALSE;
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &quit_callback) == MGL_ERROR_NONE);
    }

    while (running)
    {
        mgl_poll_window_events(&window_1);
        mgl_poll_window_events(&window_2);
        mgl_update_input_manager(&input_manager, 1.0f);
    }

#ifdef MGL_SYSTEM_UNIX
    mgl_close_x_window(&window_1);
    mgl_close_x_window(&window_2);
#elif defined(MGL_SYSTEM_WINDOWS)
    mgl_close_windows_window(&window_1);
    mgl_close_windows_window(&window_2);
#else
#error Unsupported platform
#endif

    mgl_terminate();
    return 0;
}
