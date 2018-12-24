#include <mgl/input/x_window.h>
#include <mgl/input/keyboard.h>
#include <mgl/input/mouse.h>
#include <mgl/string/manipulation.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>

#ifdef __unix__

static const mgl_chr8_t* mgl_x_window_get_type(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	return u8"xlib";
}

static mgl_u32_t mgl_x_window_get_width(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_x_window_t* x_window = (mgl_x_window_t*)window;
	return x_window->width;
}

static mgl_u32_t mgl_x_window_get_height(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_x_window_t* x_window = (mgl_x_window_t*)window;
	return x_window->height;
}

static mgl_enum_t mgl_x_window_get_mode(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_x_window_t* x_window = (mgl_x_window_t*)window;
	return x_window->mode;
}

static mgl_u32_t mgl_x_window_get_key_button(void* window, mgl_enum_t key_code)
{
    MGL_DEBUG_ASSERT(window != NULL);
    mgl_x_window_t* x_window = (mgl_x_window_t*)window;

#define TEST_KEY(key_test, keysym) case key_test: return x_window->keyboard_buttons[XKeysymToKeycode(x_window->display, keysym)]->id
    switch (key_code)
    {
        TEST_KEY(MGL_KEYBOARD_Q, XK_q);
        TEST_KEY(MGL_KEYBOARD_W, XK_w);
        TEST_KEY(MGL_KEYBOARD_E, XK_e);
        TEST_KEY(MGL_KEYBOARD_R, XK_r);
        TEST_KEY(MGL_KEYBOARD_T, XK_t);
        TEST_KEY(MGL_KEYBOARD_Y, XK_y);
        TEST_KEY(MGL_KEYBOARD_U, XK_u);
        TEST_KEY(MGL_KEYBOARD_I, XK_i);
        TEST_KEY(MGL_KEYBOARD_O, XK_o);
        TEST_KEY(MGL_KEYBOARD_P, XK_p);
        TEST_KEY(MGL_KEYBOARD_A, XK_a);
        TEST_KEY(MGL_KEYBOARD_S, XK_s);
        TEST_KEY(MGL_KEYBOARD_D, XK_d);
        TEST_KEY(MGL_KEYBOARD_F, XK_f);
        TEST_KEY(MGL_KEYBOARD_G, XK_g);
        TEST_KEY(MGL_KEYBOARD_H, XK_h);
        TEST_KEY(MGL_KEYBOARD_J, XK_j);
        TEST_KEY(MGL_KEYBOARD_K, XK_k);
        TEST_KEY(MGL_KEYBOARD_L, XK_l);
        TEST_KEY(MGL_KEYBOARD_Z, XK_z);
        TEST_KEY(MGL_KEYBOARD_X, XK_x);
        TEST_KEY(MGL_KEYBOARD_C, XK_c);
        TEST_KEY(MGL_KEYBOARD_V, XK_v);
        TEST_KEY(MGL_KEYBOARD_B, XK_b);
        TEST_KEY(MGL_KEYBOARD_N, XK_n);
        TEST_KEY(MGL_KEYBOARD_M, XK_m);

        TEST_KEY(MGL_KEYBOARD_NUM1, XK_1);
        TEST_KEY(MGL_KEYBOARD_NUM2, XK_2);
        TEST_KEY(MGL_KEYBOARD_NUM3, XK_3);
        TEST_KEY(MGL_KEYBOARD_NUM4, XK_4);
        TEST_KEY(MGL_KEYBOARD_NUM5, XK_5);
        TEST_KEY(MGL_KEYBOARD_NUM6, XK_6);
        TEST_KEY(MGL_KEYBOARD_NUM7, XK_7);
        TEST_KEY(MGL_KEYBOARD_NUM8, XK_8);
        TEST_KEY(MGL_KEYBOARD_NUM9, XK_9);
        TEST_KEY(MGL_KEYBOARD_NUM0, XK_0);

        TEST_KEY(MGL_KEYBOARD_F1, XK_F1);
        TEST_KEY(MGL_KEYBOARD_F2, XK_F2);
        TEST_KEY(MGL_KEYBOARD_F3, XK_F3);
        TEST_KEY(MGL_KEYBOARD_F4, XK_F4);
        TEST_KEY(MGL_KEYBOARD_F5, XK_F5);
        TEST_KEY(MGL_KEYBOARD_F6, XK_F6);
        TEST_KEY(MGL_KEYBOARD_F7, XK_F7);
        TEST_KEY(MGL_KEYBOARD_F8, XK_F8);
        TEST_KEY(MGL_KEYBOARD_F9, XK_F9);
        TEST_KEY(MGL_KEYBOARD_F10, XK_F10);
        TEST_KEY(MGL_KEYBOARD_F11, XK_F11);
        TEST_KEY(MGL_KEYBOARD_F12, XK_F12);

        TEST_KEY(MGL_KEYBOARD_ESCAPE, XK_Escape);
        TEST_KEY(MGL_KEYBOARD_TAB, XK_Tab);
        TEST_KEY(MGL_KEYBOARD_CAPS, XK_Caps_Lock);
        TEST_KEY(MGL_KEYBOARD_LSHIFT, XK_Shift_L);
        TEST_KEY(MGL_KEYBOARD_RSHIFT, XK_Shift_R);
        TEST_KEY(MGL_KEYBOARD_LCONTROL, XK_Control_L);
        TEST_KEY(MGL_KEYBOARD_RCONTROL, XK_Control_R);
        TEST_KEY(MGL_KEYBOARD_ALT, XK_Alt_L);
        TEST_KEY(MGL_KEYBOARD_ALTGR, XK_Menu);
        TEST_KEY(MGL_KEYBOARD_SPACE, XK_space);
        TEST_KEY(MGL_KEYBOARD_BACKSPACE, XK_BackSpace);
        TEST_KEY(MGL_KEYBOARD_INSERT, XK_Insert);
        TEST_KEY(MGL_KEYBOARD_DELETE, XK_Delete);
        TEST_KEY(MGL_KEYBOARD_HOME, XK_Home);
        TEST_KEY(MGL_KEYBOARD_END, XK_End);
        TEST_KEY(MGL_KEYBOARD_PAGEUP, XK_Page_Up);
        TEST_KEY(MGL_KEYBOARD_PAGEDOWN, XK_Page_Down);

        TEST_KEY(MGL_KEYBOARD_LEFT, XK_Left);
        TEST_KEY(MGL_KEYBOARD_RIGHT, XK_Right);
        TEST_KEY(MGL_KEYBOARD_UP, XK_Up);
        TEST_KEY(MGL_KEYBOARD_DOWN, XK_Down);

        default:
            return MGL_NULL_BUTTON;
    }
#undef TEST_KEY
}

static mgl_u32_t mgl_x_window_get_mouse_button(void* window, mgl_enum_t mouse_button)
{
    MGL_DEBUG_ASSERT(window != NULL);
    mgl_x_window_t* x_window = (mgl_x_window_t*)window;

    if (mouse_button == MGL_MOUSE_LEFT)
        return x_window->mouse_buttons[0]->id;
    else  if (mouse_button == MGL_MOUSE_MIDDLE)
        return x_window->mouse_buttons[1]->id;
    else  if (mouse_button == MGL_MOUSE_RIGHT)
        return x_window->mouse_buttons[2]->id;
    else  if (mouse_button == MGL_MOUSE_EXTRA_1)
        return x_window->mouse_buttons[3]->id;
    else  if (mouse_button == MGL_MOUSE_EXTRA_2)
        return x_window->mouse_buttons[4]->id;
    else
        return MGL_NULL_BUTTON;
}

static void mgl_x_window_handle_event(mgl_x_window_t* window, const XEvent* e)
{
    switch (e->type)
    {
        case KeyPress:
        {
            mgl_button_t* button = window->keyboard_buttons[e->xkey.keycode];
            mgl_feed_button(window->input_manager, button->id, MGL_TRUE);
            break;
        }

        case KeyRelease:
        {
            mgl_button_t* button = window->keyboard_buttons[e->xkey.keycode];
            mgl_feed_button(window->input_manager, button->id, MGL_FALSE);
            break;
        }

        case ButtonPress:
        {
            mgl_button_t* button = NULL;
            if (e->xbutton.button == 1)
                button = window->mouse_buttons[0];
            else if (e->xbutton.button == 2)
                button = window->mouse_buttons[1];
            else if (e->xbutton.button == 3)
                button = window->mouse_buttons[2];
            else if (e->xbutton.button == 8)
                button = window->mouse_buttons[3];
            else if (e->xbutton.button == 9)
                button = window->mouse_buttons[4];
            else if (e->xbutton.button == 4)
            {
                mgl_feed_axis_instant(window->input_manager, window->mouse_wheel_axis->id, 1.0f, 0.0f);
                break;
            }
            else if (e->xbutton.button == 5)
            {
                mgl_feed_axis_instant(window->input_manager, window->mouse_wheel_axis->id, -1.0f, 0.0f);
                break;
            }
            else
                break;
            mgl_feed_button(window->input_manager, button->id, MGL_TRUE);
            break;
        }

        case ButtonRelease:
        {
            mgl_button_t* button = NULL;
            if (e->xbutton.button == 1)
                button = window->mouse_buttons[0];
            else if (e->xbutton.button == 2)
                button = window->mouse_buttons[1];
            else if (e->xbutton.button == 3)
                button = window->mouse_buttons[2];
            else if (e->xbutton.button == 8)
                button = window->mouse_buttons[3];
            else if (e->xbutton.button == 9)
                button = window->mouse_buttons[4];
            else
                break;
            mgl_feed_button(window->input_manager, button->id, MGL_FALSE);
            break;
        }

        case MotionNotify:
        {
            mgl_feed_axis(window->input_manager, window->mouse_x_axis->id,  (mgl_f32_t)e->xmotion.x / window->width);
            mgl_feed_axis(window->input_manager, window->mouse_y_axis->id,  (mgl_f32_t)e->xmotion.y / window->height);
            break;
        }
    }
}

static void mgl_x_window_poll_events(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_x_window_t* x_window = (mgl_x_window_t*)window;

	mgl_feed_axis(x_window->input_manager, x_window->mouse_wheel_axis->id, 0.0f);

	XEvent e;
	while (XPending(x_window->display))
    {
        XNextEvent(x_window->display, &e);
        mgl_x_window_handle_event(x_window, &e);
    }
}

static void mgl_x_window_wait_for_events(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_x_window_t* x_window = (mgl_x_window_t*)window;

    XEvent e;
	XNextEvent(x_window->display, &e);
    mgl_x_window_handle_event(x_window, &e);
    while (XPending(x_window->display))
    {
        XNextEvent(x_window->display, &e);
        mgl_x_window_handle_event(x_window, &e);
    }
}

static mgl_window_functions_t mgl_x_window_functions =
{
	&mgl_x_window_get_type,
	&mgl_x_window_get_width,
	&mgl_x_window_get_height,
	&mgl_x_window_get_mode,
	&mgl_x_window_poll_events,
	&mgl_x_window_wait_for_events,
	&mgl_x_window_get_key_button,
	&mgl_x_window_get_mouse_button,
};

mgl_error_t MGL_API mgl_open_x_window(mgl_x_window_t * window, const mgl_x_window_settings_t * settings)
{
	MGL_DEBUG_ASSERT(window != NULL && settings != NULL);

	window->width = settings->width;
	window->height = settings->height;
	window->mode = settings->mode;

	window->base.functions = &mgl_x_window_functions;
	window->base.close_callback = NULL;
	window->base.key_down_callback = NULL;
	window->base.key_up_callback = NULL;
	window->base.mouse_down_callback = NULL;
	window->base.mouse_up_callback = NULL;
	window->base.mouse_enter_callback = NULL;
	window->base.mouse_leave_callback = NULL;
	window->base.mouse_move_callback = NULL;
	window->base.mouse_scroll_callback = NULL;

	window->tracking = MGL_FALSE;
	window->alt = MGL_FALSE;
	window->control = MGL_FALSE;
	window->system = MGL_FALSE;
	window->shift = MGL_FALSE;

	window->display = XOpenDisplay(NULL);
	if (window->display == NULL)
        return MGL_ERROR_EXTERNAL;

    window->input_manager = settings->input_manager;

    // Open Xlib window
    window->screen = DefaultScreen(window->display);
    unsigned long black = BlackPixel(window->display, window->screen);
    unsigned long white = WhitePixel(window->display, window->screen);
    window->window = XCreateSimpleWindow(window->display, DefaultRootWindow(window->display), 0, 0, window->width, window->height, 5, white, black);
    XSetStandardProperties(window->display, window->window, settings->title, settings->title, None, NULL, 0, NULL);
    XSelectInput(window->display, window->window, ButtonReleaseMask | ButtonPressMask | KeyPressMask | KeyReleaseMask | PointerMotionMask);
    window->gc = XCreateGC(window->display, window->window, 0, NULL);
    XSetBackground(window->display, window->gc, white);
    XSetForeground(window->display, window->gc, black);
    XClearWindow(window->display, window->window);
    XMapRaised(window->display, window->window);
    XAutoRepeatOff(window->display);

     // Init buttons of the input manager
    mgl_input_manager_t* im = window->input_manager;
    for (mgl_u32_t i = 0; i < 256; ++i)
    {

        KeySym sim = XkbKeycodeToKeysym(window->display, i, 0, 0);
        char* str = XKeysymToString(sim);
        mgl_error_t e = mgl_add_button(im, &window->keyboard_buttons[i], str);
        if (e != MGL_ERROR_NONE)
            return e;
    }

    mgl_error_t e = mgl_add_button(im, &window->mouse_buttons[0], u8"Mouse Left");
    if (e != MGL_ERROR_NONE)
        return e;
    e = mgl_add_button(im, &window->mouse_buttons[1], u8"Mouse Middle");
    if (e != MGL_ERROR_NONE)
        return e;
    e = mgl_add_button(im, &window->mouse_buttons[2], u8"Mouse Right");
    if (e != MGL_ERROR_NONE)
        return e;
    e = mgl_add_button(im, &window->mouse_buttons[3], u8"Mouse Extra 1");
    if (e != MGL_ERROR_NONE)
        return e;
    e = mgl_add_button(im, &window->mouse_buttons[4], u8"Mouse Extra 2");
    if (e != MGL_ERROR_NONE)
        return e;

    // Init mouse axes
    e = mgl_add_axis(im, &window->mouse_x_axis, u8"Mouse X");
    if (e != MGL_ERROR_NONE)
        return e;
    window->mouse_x_axis->min_value = 0.0f;
    window->mouse_x_axis->max_value = 1.0f;
    window->mouse_x_axis->speed = INFINITY;
    e = mgl_add_axis(im, &window->mouse_y_axis, u8"Mouse Y");
    if (e != MGL_ERROR_NONE)
        return e;
    window->mouse_y_axis->min_value = 0.0f;
    window->mouse_y_axis->max_value = 1.0f;
    window->mouse_y_axis->speed = INFINITY;
    e = mgl_add_axis(im, &window->mouse_wheel_axis, u8"Mouse Wheel");
    if (e != MGL_ERROR_NONE)
        return e;
    window->mouse_wheel_axis->min_value = -1.0f;
    window->mouse_wheel_axis->max_value = 1.0f;
    window->mouse_wheel_axis->speed = 0.1f;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_close_x_window(mgl_x_window_t * window)
{
	MGL_DEBUG_ASSERT(window != NULL);

	mgl_input_manager_t* im = window->input_manager;
    for (mgl_u32_t i = 0; i < 256; ++i)
        mgl_remove_button(im, window->keyboard_buttons[i]->id);
    for (mgl_u32_t i = 0; i < 5; ++i)
        mgl_remove_button(im, window->mouse_buttons[i]->id);
    mgl_remove_axis(im, window->mouse_x_axis->id);
    mgl_remove_axis(im, window->mouse_y_axis->id);

	XFreeGC(window->display, window->gc);
	XDestroyWindow(window->display, window->window);
	XCloseDisplay(window->display);
}

#endif // __unix__
