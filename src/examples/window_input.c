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

void sequence_callback(const mgl_action_t* action, mgl_enum_t state)
{
    mgl_print(mgl_stdout_stream, u8"QWE sequence detected\n");
}

void group_callback(const mgl_action_t* action, mgl_enum_t state)
{
    if (state == MGL_ACTION_PRESSED)
        mgl_print(mgl_stdout_stream, u8"ZXCV group pressed\n");
    else if (state == MGL_ACTION_RELEASED)
        mgl_print(mgl_stdout_stream, u8"ZXCV group released\n");
}

void axis_range_callback(const mgl_action_t* action, mgl_enum_t state)
{
    if (state == MGL_ACTION_ENTERED)
        mgl_print(mgl_stdout_stream, u8"Axis range entered\n");
    else if (state == MGL_ACTION_LEFT)
        mgl_print(mgl_stdout_stream, u8"Axis range left\n");
}

void mouse_action_callback(const mgl_action_t* action, mgl_enum_t state)
{
    mgl_print(mgl_stdout_stream, action->name);
    if (state == MGL_ACTION_PRESSED)
        mgl_print(mgl_stdout_stream, u8" pressed\n");
    else if (state == MGL_ACTION_RELEASED)
        mgl_print(mgl_stdout_stream, u8" released\n");
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

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON_SEQUENCE, u8"sequence") == MGL_ERROR_NONE);
        action->sequence.button_count = 3;
        action->sequence.buttons[0] = mgl_get_window_key_button(&window, MGL_KEYBOARD_Q);
        action->sequence.buttons[1] = mgl_get_window_key_button(&window, MGL_KEYBOARD_W);
        action->sequence.buttons[2] = mgl_get_window_key_button(&window, MGL_KEYBOARD_E);
        action->sequence.interfering_buttons[0] = mgl_get_window_key_button(&window, MGL_KEYBOARD_SPACE);
        action->sequence.whitelist = MGL_FALSE;
        action->sequence.can_release = MGL_TRUE;

        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &sequence_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON_GROUP, u8"group") == MGL_ERROR_NONE);
        action->group.button_count = 4;
        action->group.buttons[0] = mgl_get_window_key_button(&window, MGL_KEYBOARD_Z);
        action->group.buttons[1] = mgl_get_window_key_button(&window, MGL_KEYBOARD_X);
        action->group.buttons[2] = mgl_get_window_key_button(&window, MGL_KEYBOARD_C);
        action->group.buttons[3] = mgl_get_window_key_button(&window, MGL_KEYBOARD_V);
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &group_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_AXIS_RANGE, u8"axis_range") == MGL_ERROR_NONE);
        action->axis_range.id = mgl_get_axis(&input_manager, u8"Mouse X");
        action->axis_range.range_min = 0.5f;
        action->axis_range.range_max = 1.0f;
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &axis_range_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON, u8"mouse left") == MGL_ERROR_NONE);
        action->button.id = mgl_get_button(&input_manager, u8"Mouse Left");
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &mouse_action_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON, u8"mouse right") == MGL_ERROR_NONE);
        action->button.id = mgl_get_button(&input_manager, u8"Mouse Right");
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &mouse_action_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON, u8"mouse middle") == MGL_ERROR_NONE);
        action->button.id = mgl_get_button(&input_manager, u8"Mouse Middle");
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &mouse_action_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON, u8"mouse extra 1") == MGL_ERROR_NONE);
        action->button.id = mgl_get_button(&input_manager, u8"Mouse Extra 1");
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &mouse_action_callback) == MGL_ERROR_NONE);
    }

    {
        mgl_action_t* action;
        MGL_ASSERT(mgl_add_action(&input_manager, &action, MGL_ACTION_BUTTON, u8"mouse extra 2") == MGL_ERROR_NONE);
        action->button.id = mgl_get_button(&input_manager, u8"Mouse Extra 2");
        MGL_ASSERT(mgl_add_action_callback(&input_manager, action->id, &mouse_action_callback) == MGL_ERROR_NONE);
    }

    while (running)
    {
        mgl_poll_window_events(&window);
        mgl_update_input_manager(&input_manager, 1.0f / 1000.0f);

        /*mgl_print_f32(mgl_stdout_stream, input_manager.axes[window.mouse_x_axis->id].value, 10, 4);
        mgl_put_char(mgl_stdout_stream, ' ');*/
        //mgl_print_f32(mgl_stdout_stream, input_manager.axes[window.mouse_wheel_axis->id].value, 10, 2);
        //mgl_put_char(mgl_stdout_stream, '\n');
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
