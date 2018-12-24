#include <mgl/input/windows_window.h>
#include <mgl/input/keyboard.h>
#include <mgl/input/mouse.h>

#ifdef _WIN32
#include <Windows.h>
#include <windowsx.h>

static LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT message,
	WPARAM wparam,
	LPARAM lparam);

static const mgl_chr8_t* mgl_windows_window_get_type(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	return u8"win32";
}

static mgl_u32_t mgl_windows_window_get_width(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* windows_window = (mgl_windows_window_t*)window;
	return windows_window->width;
}

static mgl_u32_t mgl_windows_window_get_height(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* windows_window = (mgl_windows_window_t*)window;
	return windows_window->height;
}

static mgl_enum_t mgl_windows_window_get_mode(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* windows_window = (mgl_windows_window_t*)window;
	return windows_window->mode;
}

static void mgl_windows_window_poll_events(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* windows_window = (mgl_windows_window_t*)window;
	MSG msg;
	while (PeekMessage(&msg, (HWND)windows_window->hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

static void mgl_windows_window_wait_for_events(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* windows_window = (mgl_windows_window_t*)window;
	MSG msg;
	GetMessage(&msg, (HWND)windows_window->hwnd, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}


static mgl_u32_t mgl_windows_window_get_key_button(void* window, mgl_enum_t key_code)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* win_window = (mgl_windows_window_t*)window;

#define TEST_KEY(key_test, keycode) case key_test: return win_window->keyboard_buttons[keycode]->id
	switch (key_code)
	{
		TEST_KEY(MGL_KEYBOARD_Q, 'Q');
		TEST_KEY(MGL_KEYBOARD_W, 'W');
		TEST_KEY(MGL_KEYBOARD_E, 'E');
		TEST_KEY(MGL_KEYBOARD_R, 'R');
		TEST_KEY(MGL_KEYBOARD_T, 'T');
		TEST_KEY(MGL_KEYBOARD_Y, 'Y');
		TEST_KEY(MGL_KEYBOARD_U, 'U');
		TEST_KEY(MGL_KEYBOARD_I, 'I');
		TEST_KEY(MGL_KEYBOARD_O, 'O');
		TEST_KEY(MGL_KEYBOARD_P, 'P');
		TEST_KEY(MGL_KEYBOARD_A, 'A');
		TEST_KEY(MGL_KEYBOARD_S, 'S');
		TEST_KEY(MGL_KEYBOARD_D, 'D');
		TEST_KEY(MGL_KEYBOARD_F, 'F');
		TEST_KEY(MGL_KEYBOARD_G, 'G');
		TEST_KEY(MGL_KEYBOARD_H, 'H');
		TEST_KEY(MGL_KEYBOARD_J, 'J');
		TEST_KEY(MGL_KEYBOARD_K, 'K');
		TEST_KEY(MGL_KEYBOARD_L, 'L');
		TEST_KEY(MGL_KEYBOARD_Z, 'Z');
		TEST_KEY(MGL_KEYBOARD_X, 'X');
		TEST_KEY(MGL_KEYBOARD_C, 'C');
		TEST_KEY(MGL_KEYBOARD_V, 'V');
		TEST_KEY(MGL_KEYBOARD_B, 'B');
		TEST_KEY(MGL_KEYBOARD_N, 'N');
		TEST_KEY(MGL_KEYBOARD_M, 'M');

		TEST_KEY(MGL_KEYBOARD_NUM1, '1');
		TEST_KEY(MGL_KEYBOARD_NUM2, '2');
		TEST_KEY(MGL_KEYBOARD_NUM3, '3');
		TEST_KEY(MGL_KEYBOARD_NUM4, '4');
		TEST_KEY(MGL_KEYBOARD_NUM5, '5');
		TEST_KEY(MGL_KEYBOARD_NUM6, '6');
		TEST_KEY(MGL_KEYBOARD_NUM7, '7');
		TEST_KEY(MGL_KEYBOARD_NUM8, '8');
		TEST_KEY(MGL_KEYBOARD_NUM9, '9');
		TEST_KEY(MGL_KEYBOARD_NUM0, '0');

		TEST_KEY(MGL_KEYBOARD_F1, VK_F1);
		TEST_KEY(MGL_KEYBOARD_F2, VK_F2);
		TEST_KEY(MGL_KEYBOARD_F3, VK_F3);
		TEST_KEY(MGL_KEYBOARD_F4, VK_F4);
		TEST_KEY(MGL_KEYBOARD_F5, VK_F5);
		TEST_KEY(MGL_KEYBOARD_F6, VK_F6);
		TEST_KEY(MGL_KEYBOARD_F7, VK_F7);
		TEST_KEY(MGL_KEYBOARD_F8, VK_F8);
		TEST_KEY(MGL_KEYBOARD_F9, VK_F9);
		TEST_KEY(MGL_KEYBOARD_F10, VK_F10);
		TEST_KEY(MGL_KEYBOARD_F11, VK_F11);
		TEST_KEY(MGL_KEYBOARD_F12, VK_F12);

		TEST_KEY(MGL_KEYBOARD_ESCAPE, VK_ESCAPE);
		TEST_KEY(MGL_KEYBOARD_TAB, VK_TAB);
		TEST_KEY(MGL_KEYBOARD_CAPS, VK_CAPITAL);
		TEST_KEY(MGL_KEYBOARD_LSHIFT, VK_LSHIFT);
		TEST_KEY(MGL_KEYBOARD_RSHIFT, VK_RSHIFT);
		TEST_KEY(MGL_KEYBOARD_CONTROL, VK_CONTROL);
		TEST_KEY(MGL_KEYBOARD_ALT, VK_LMENU);
		TEST_KEY(MGL_KEYBOARD_ALTGR, VK_RMENU);
		TEST_KEY(MGL_KEYBOARD_SPACE, VK_SPACE);
		TEST_KEY(MGL_KEYBOARD_BACKSPACE, VK_BACK);
		TEST_KEY(MGL_KEYBOARD_INSERT, VK_INSERT);
		TEST_KEY(MGL_KEYBOARD_DELETE, VK_DELETE);
		TEST_KEY(MGL_KEYBOARD_HOME, VK_HOME);
		TEST_KEY(MGL_KEYBOARD_END, VK_END);
		TEST_KEY(MGL_KEYBOARD_PAGEUP, VK_PRIOR);
		TEST_KEY(MGL_KEYBOARD_PAGEDOWN, VK_NEXT);

		TEST_KEY(MGL_KEYBOARD_LEFT, VK_LEFT);
		TEST_KEY(MGL_KEYBOARD_RIGHT, VK_RIGHT);
		TEST_KEY(MGL_KEYBOARD_UP, VK_UP);
		TEST_KEY(MGL_KEYBOARD_DOWN, VK_DOWN);

		default:
			return MGL_NULL_BUTTON;
	}
#undef TEST_KEY
}

static mgl_u32_t mgl_windows_window_get_mouse_button(void* window, mgl_enum_t mouse_button)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* win_window = (mgl_windows_window_t*)window;

	if (mouse_button == MGL_MOUSE_LEFT)
		return win_window->mouse_buttons[0]->id;
	else  if (mouse_button == MGL_MOUSE_MIDDLE)
		return win_window->mouse_buttons[1]->id;
	else  if (mouse_button == MGL_MOUSE_RIGHT)
		return win_window->mouse_buttons[2]->id;
	else  if (mouse_button == MGL_MOUSE_EXTRA_1)
		return win_window->mouse_buttons[3]->id;
	else  if (mouse_button == MGL_MOUSE_EXTRA_2)
		return win_window->mouse_buttons[4]->id;
	else
		return MGL_NULL_BUTTON;
}

static mgl_u32_t mgl_windows_window_get_mouse_axis(void* window, mgl_enum_t mouse_axis)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* win_window = (mgl_windows_window_t*)window;

	if (mouse_axis == MGL_MOUSE_X)
		return win_window->mouse_x_axis->id;
	else  if (mouse_axis == MGL_MOUSE_Y)
		return win_window->mouse_y_axis->id;
	else  if (mouse_axis == MGL_MOUSE_WHEEL)
		return win_window->mouse_wheel_axis->id;
	else
		return MGL_NULL_BUTTON;
}

static mgl_u32_t mgl_windows_window_get_action(void* window, mgl_enum_t window_action)
{
	MGL_DEBUG_ASSERT(window != NULL);
	mgl_windows_window_t* win_window = (mgl_windows_window_t*)window;

	if (window_action == MGL_WINDOW_CLOSE)
		return win_window->close->id;
	else  if (window_action == MGL_WINDOW_MOUSE_ENTER)
		return win_window->mouse_enter->id;
	else  if (window_action == MGL_WINDOW_MOUSE_LEAVE)
		return win_window->mouse_leave->id;
	else
		return MGL_NULL_BUTTON;
}

static mgl_window_functions_t mgl_windows_window_functions =
{
	&mgl_windows_window_get_type,
	&mgl_windows_window_get_width,
	&mgl_windows_window_get_height,
	&mgl_windows_window_get_mode,
	&mgl_windows_window_poll_events,
	&mgl_windows_window_wait_for_events,
	&mgl_windows_window_get_key_button,
	&mgl_windows_window_get_mouse_button,
	&mgl_windows_window_get_mouse_axis,
	&mgl_windows_window_get_action,
};

mgl_error_t MGL_API mgl_open_windows_window(mgl_windows_window_t * window, const mgl_windows_window_settings_t * settings)
{
	MGL_DEBUG_ASSERT(window != NULL && settings != NULL);

	window->width = settings->width;
	window->height = settings->height;
	window->mode = settings->mode;
	window->input_manager = settings->input_manager;

	window->base.functions = &mgl_windows_window_functions;

	window->tracking = MGL_FALSE;

	HWND hwnd;
	HINSTANCE instance = GetModuleHandle(NULL);

	// Open window
	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = instance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = "mgl_windows_window_t_windowed";
		RegisterClassEx(&wc);
	}

	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = instance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = "mgl_windows_window_t_fullscreen";
		RegisterClassEx(&wc);
	}

	switch (window->mode)
	{
		case MGL_WINDOW_MODE_WINDOWED:
		{
			RECT window_rect;
			window_rect.left = 0;
			window_rect.top = 0;
			window_rect.right = window->width;
			window_rect.bottom = window->height;
			AdjustWindowRect(&window_rect, WS_OVERLAPPED | WS_MINIMIZE | WS_SYSMENU | WS_CAPTION, FALSE);
			hwnd = CreateWindowEx(
				0,
				"mgl_windows_window_t_windowed",
				settings->title,
				WS_OVERLAPPED | WS_MINIMIZE | WS_SYSMENU | WS_CAPTION,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				window_rect.right - window_rect.left,
				window_rect.bottom - window_rect.top,
				NULL,
				NULL,
				instance,
				NULL);
			break;
		}

		case MGL_WINDOW_MODE_FULLSCREEN:
		{
			RECT window_rect;
			window_rect.left = 0;
			window_rect.top = 0;
			window_rect.right = window->width;
			window_rect.bottom = window->height;
			AdjustWindowRect(&window_rect, WS_EX_TOPMOST | WS_POPUP, FALSE);
			hwnd = CreateWindowEx(
				0,
				"mgl_windows_window_t_fullscreen",
				settings->title,
				WS_EX_TOPMOST | WS_POPUP,
				0,
				0,
				window_rect.right - window_rect.left,
				window_rect.bottom - window_rect.top,
				NULL,
				NULL,
				instance,
				NULL);
			break;
		}

		default:
			return MGL_ERROR_INVALID_PARAMS;
	}

	if (hwnd == NULL)
		return MGL_ERROR_EXTERNAL;

	
	ShowWindow(hwnd, SW_SHOWNORMAL);
	SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)window);
	
	window->hwnd = hwnd;

	// Init buttons of the input manager
	mgl_input_manager_t* im = window->input_manager;
	for (mgl_u32_t i = 0; i < 256; ++i)
	{
		mgl_chr8_t name[MGL_MAX_BUTTON_NAME_SIZE];
		mgl_error_t e;

		LONG code = MapVirtualKey(i, 0);
		if (!code || !GetKeyNameTextA(code << 16, name, MGL_MAX_BUTTON_NAME_SIZE))
			e = mgl_add_button(im, &window->keyboard_buttons[i], NULL);
		else
			e = mgl_add_button(im, &window->keyboard_buttons[i], name);
		if (e != MGL_ERROR_NONE)
			return e;
	}

	mgl_error_t e = mgl_add_button(im, &window->mouse_buttons[0], u8"mouse_l");
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_add_button(im, &window->mouse_buttons[1], u8"mouse_m");
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_add_button(im, &window->mouse_buttons[2], u8"mouse_r");
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_add_button(im, &window->mouse_buttons[3], u8"mouse_x1");
	if (e != MGL_ERROR_NONE)
		return e;
	e = mgl_add_button(im, &window->mouse_buttons[4], u8"mouse_x2");
	if (e != MGL_ERROR_NONE)
		return e;

	// Init mouse axes
	e = mgl_add_axis(im, &window->mouse_x_axis, u8"mouse_x");
	if (e != MGL_ERROR_NONE)
		return e;
	window->mouse_x_axis->min_value = 0.0f;
	window->mouse_x_axis->max_value = 1.0f;
	window->mouse_x_axis->speed = INFINITY;
	e = mgl_add_axis(im, &window->mouse_y_axis, u8"mouse_y");
	if (e != MGL_ERROR_NONE)
		return e;
	window->mouse_y_axis->min_value = 0.0f;
	window->mouse_y_axis->max_value = 1.0f;
	window->mouse_y_axis->speed = INFINITY;
	e = mgl_add_axis(im, &window->mouse_wheel_axis, u8"mouse_w");
	if (e != MGL_ERROR_NONE)
		return e;
	window->mouse_wheel_axis->min_value = -1.0f;
	window->mouse_wheel_axis->max_value = 1.0f;
	window->mouse_wheel_axis->speed = 0.1f;

	e = mgl_add_action(im, &window->close, MGL_ACTION_EMPTY, u8"window_close");
	if (e != MGL_ERROR_NONE)
		return e;
	window->close->data = window;
	e = mgl_add_action(im, &window->mouse_enter, MGL_ACTION_EMPTY, u8"mouse_enter");
	if (e != MGL_ERROR_NONE)
		return e;
	window->mouse_enter->data = window;
	e = mgl_add_action(im, &window->mouse_leave, MGL_ACTION_EMPTY, u8"mouse_leave");
	if (e != MGL_ERROR_NONE)
		return e;
	window->mouse_leave->data = window;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_close_windows_window(mgl_windows_window_t * window)
{
	MGL_DEBUG_ASSERT(window != NULL);

	mgl_input_manager_t* im = window->input_manager;
	for (mgl_u32_t i = 0; i < 256; ++i)
		mgl_remove_button(im, window->keyboard_buttons[i]->id);
	for (mgl_u32_t i = 0; i < 5; ++i)
		mgl_remove_button(im, window->mouse_buttons[i]->id);
	mgl_remove_axis(im, window->mouse_x_axis->id);
	mgl_remove_axis(im, window->mouse_y_axis->id);
	mgl_remove_axis(im, window->mouse_wheel_axis->id);
	mgl_remove_action(im, window->close->id);
	mgl_remove_action(im, window->mouse_enter->id);
	mgl_remove_action(im, window->mouse_leave->id);

	CloseWindow(window->hwnd);
}

#include <mgl/stream/stream.h>

static LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT message,
	WPARAM wparam,
	LPARAM lparam)
{
	mgl_windows_window_t* window = (mgl_windows_window_t*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);

	switch (message)
	{
		case WM_CLOSE:
		{
			mgl_fire_action(window->input_manager, window->close->id, MGL_ACTION_FIRED);
			break;
		}

		case WM_QUIT:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_MOUSEMOVE:
		{
			if (!window->tracking)
			{
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.dwFlags = TME_HOVER | TME_LEAVE;
				tme.dwHoverTime = 1;
				tme.hwndTrack = hwnd;
				TrackMouseEvent(&tme);
				window->tracking = MGL_TRUE;
			}

			mgl_feed_axis(window->input_manager, window->mouse_x_axis->id, (mgl_f32_t)GET_X_LPARAM(lparam) / (mgl_f32_t)window->width);
			mgl_feed_axis(window->input_manager, window->mouse_y_axis->id, (mgl_f32_t)GET_Y_LPARAM(lparam) / (mgl_f32_t)window->height);

			break;
		}

		case WM_MOUSEHOVER:
		{
			mgl_fire_action(window->input_manager, window->mouse_enter->id, MGL_ACTION_FIRED);
			break;
		}

		case WM_MOUSELEAVE:
		{
			window->tracking = MGL_FALSE;
			mgl_fire_action(window->input_manager, window->mouse_leave->id, MGL_ACTION_FIRED);
			break;
		}
		
		case WM_MOUSEWHEEL:
		{
			mgl_feed_axis_instant(window->input_manager, window->mouse_wheel_axis->id, GET_WHEEL_DELTA_WPARAM(wparam) > 0 ? 1.0f : -1.0f, 0.0f);
			break;
		}

		case WM_KEYDOWN:
		{
			if (lparam & 0x40000000)
				break;

			mgl_button_t* button = window->keyboard_buttons[wparam];
			mgl_feed_button(window->input_manager, button->id, MGL_TRUE);
			break;
		}

		case WM_KEYUP:
		{
			mgl_button_t* button = window->keyboard_buttons[wparam];
			mgl_feed_button(window->input_manager, button->id, MGL_FALSE);
			break;
		}

		case WM_LBUTTONDOWN:
		{
			mgl_feed_button(window->input_manager, window->mouse_buttons[0]->id, MGL_TRUE);
			break;
		}

		case WM_RBUTTONDOWN:
		{
			mgl_feed_button(window->input_manager, window->mouse_buttons[2]->id, MGL_TRUE);
			break;
		}

		case WM_MBUTTONDOWN:
		{
			mgl_feed_button(window->input_manager, window->mouse_buttons[1]->id, MGL_TRUE);
			break;
		}

		case WM_XBUTTONDOWN:
		{
			if (GET_XBUTTON_WPARAM(wparam) == XBUTTON1)
				mgl_feed_button(window->input_manager, window->mouse_buttons[3]->id, MGL_TRUE);
			else if (GET_XBUTTON_WPARAM(wparam) == XBUTTON2)
				mgl_feed_button(window->input_manager, window->mouse_buttons[4]->id, MGL_TRUE);
			break;
		}

		case WM_LBUTTONUP:
		{
			mgl_feed_button(window->input_manager, window->mouse_buttons[0]->id, MGL_FALSE);
			break;
		}

		case WM_RBUTTONUP:
		{
			mgl_feed_button(window->input_manager, window->mouse_buttons[2]->id, MGL_FALSE);
			break;
		}

		case WM_MBUTTONUP:
		{
			mgl_feed_button(window->input_manager, window->mouse_buttons[1]->id, MGL_FALSE);
			break;
		}

		case WM_XBUTTONUP:
		{
			if (GET_XBUTTON_WPARAM(wparam) == XBUTTON1)
				mgl_feed_button(window->input_manager, window->mouse_buttons[3]->id, MGL_FALSE);
			else if (GET_XBUTTON_WPARAM(wparam) == XBUTTON2)
				mgl_feed_button(window->input_manager, window->mouse_buttons[4]->id, MGL_FALSE);
			break;
		}

		default:
			return DefWindowProc(hwnd, message, wparam, lparam);
	}

	return 0;
}

#endif
