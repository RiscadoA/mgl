#include <mgl/entry.h>
#include <mgl/stream/stream.h>
#include <mgl/input/input_manager.h>
#include <mgl/input/keyboard.h>

#ifdef __unix__
#include <mgl/input/x_window.h>
#elif defined(_WIN32)
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

#ifdef __unix__
    mgl_x_window_settings_t settings;
    settings.width = 800;
    settings.height = 600;
    settings.mode = MGL_WINDOW_MODE_WINDOWED;
    settings.title = u8"MGL Test Window (Xlib)";
    settings.input_manager = &input_manager;

    mgl_x_window_t window;
    MGL_ASSERT(mgl_open_x_window(&window, &settings) == MGL_ERROR_NONE);
#elif defined(_WIN32)
    mgl_windows_window_settings_t settings;
    settings.width = 800;
    settings.height = 600;
    settings.mode = MGL_WINDOW_MODE_WINDOWED;
    settings.title = u8"MGL Test Window (Win32)";
    settings.input_manager = &input_manager;

    mgl_windows_window_t window;
    MGL_ASSERT(mgl_open_windows_window(&window, &settings) == MGL_ERROR_NONE);
#else
#error Unsupported platform
#endif

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON_SEQUENCE, u8"quit") == MGL_ERROR_NONE);
        action->sequence.button_count = 2;
        action->sequence.buttons[0] = mgl_get_window_key_button(&window, MGL_KEYBOARD_CONTROL);
        action->sequence.buttons[1] = mgl_get_window_key_button(&window, MGL_KEYBOARD_Q);
        action->sequence.can_release = MGL_FALSE;
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &quit_callback) == MGL_ERROR_NONE);
    }

    while (running)
    {
        mgl_poll_window_events(&window);
        mgl_update_input_manager(&input_manager, 1.0f);
    }

#ifdef __unix__
    mgl_close_x_window(&window);
#elif defined(_WIN32)
    mgl_close_windows_window(&window);
#else
#error Unsupported platform
#endif

    mgl_terminate();
    return 0;
}
