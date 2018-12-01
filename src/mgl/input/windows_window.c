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


static mgl_enum_t mgl_windows_key_to_mgl_key(int key)
{
	switch (key)
	{
		case 'Q': return MGL_KEYBOARD_Q;
		case 'W': return MGL_KEYBOARD_W;
		case 'E': return MGL_KEYBOARD_E;
		case 'R': return MGL_KEYBOARD_R;
		case 'T': return MGL_KEYBOARD_T;
		case 'Y': return MGL_KEYBOARD_Y;
		case 'U': return MGL_KEYBOARD_U;
		case 'I': return MGL_KEYBOARD_I;
		case 'O': return MGL_KEYBOARD_O;
		case 'P': return MGL_KEYBOARD_P;
		case 'A': return MGL_KEYBOARD_A;
		case 'S': return MGL_KEYBOARD_S;
		case 'D': return MGL_KEYBOARD_D;
		case 'F': return MGL_KEYBOARD_F;
		case 'G': return MGL_KEYBOARD_G;
		case 'H': return MGL_KEYBOARD_H;
		case 'J': return MGL_KEYBOARD_J;
		case 'K': return MGL_KEYBOARD_K;
		case 'L': return MGL_KEYBOARD_L;
		case 'Z': return MGL_KEYBOARD_Z;
		case 'X': return MGL_KEYBOARD_X;
		case 'C': return MGL_KEYBOARD_C;
		case 'V': return MGL_KEYBOARD_V;
		case 'B': return MGL_KEYBOARD_B;
		case 'N': return MGL_KEYBOARD_N;
		case 'M': return MGL_KEYBOARD_M;

		case '1': return MGL_KEYBOARD_NUM1;
		case '2': return MGL_KEYBOARD_NUM2;
		case '3': return MGL_KEYBOARD_NUM3;
		case '4': return MGL_KEYBOARD_NUM4;
		case '5': return MGL_KEYBOARD_NUM5;
		case '6': return MGL_KEYBOARD_NUM6;
		case '7': return MGL_KEYBOARD_NUM7;
		case '8': return MGL_KEYBOARD_NUM8;
		case '9': return MGL_KEYBOARD_NUM9;
		case '0': return MGL_KEYBOARD_NUM0;

		case VK_F1: return MGL_KEYBOARD_F1;
		case VK_F2: return MGL_KEYBOARD_F2;
		case VK_F3: return MGL_KEYBOARD_F3;
		case VK_F4: return MGL_KEYBOARD_F4;
		case VK_F5: return MGL_KEYBOARD_F5;
		case VK_F6: return MGL_KEYBOARD_F6;
		case VK_F7: return MGL_KEYBOARD_F7;
		case VK_F8: return MGL_KEYBOARD_F8;
		case VK_F9: return MGL_KEYBOARD_F9;
		case VK_F10: return MGL_KEYBOARD_F10;
		case VK_F11: return MGL_KEYBOARD_F11;
		case VK_F12: return MGL_KEYBOARD_F12;

		case VK_ESCAPE: return MGL_KEYBOARD_ESCAPE;
		case VK_TAB: return MGL_KEYBOARD_TAB;
		case VK_CAPITAL: return MGL_KEYBOARD_CAPS;
		case VK_LSHIFT: return MGL_KEYBOARD_LSHIFT;
		case VK_RSHIFT: return MGL_KEYBOARD_RSHIFT;
		case VK_LCONTROL: return MGL_KEYBOARD_LCONTROL;
		case VK_RCONTROL: return MGL_KEYBOARD_RCONTROL;
		case VK_LMENU: return MGL_KEYBOARD_ALT;
		case VK_RMENU: return MGL_KEYBOARD_ALTGR;
		case VK_SPACE: return MGL_KEYBOARD_SPACE;
		case VK_RETURN: return MGL_KEYBOARD_ENTER;
		case VK_BACK: return MGL_KEYBOARD_BACKSPACE;
		case VK_INSERT: return MGL_KEYBOARD_INSERT;
		case VK_DELETE: return MGL_KEYBOARD_DELETE;
		case VK_HOME: return MGL_KEYBOARD_HOME;
		case VK_END: return MGL_KEYBOARD_END;
		case VK_PRIOR: return MGL_KEYBOARD_PAGEUP;
		case VK_NEXT: return MGL_KEYBOARD_PAGEDOWN;

		case VK_LEFT: return MGL_KEYBOARD_LEFT;
		case VK_RIGHT: return MGL_KEYBOARD_RIGHT;
		case VK_UP: return MGL_KEYBOARD_UP;
		case VK_DOWN: return MGL_KEYBOARD_DOWN;

		default: return -1;
	}
}

static const mgl_chr8_t* mgl_windows_window_get_type(void* window)
{
	MGL_DEBUG_ASSERT(window != NULL);
	return u8"windows";
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

static mgl_window_functions_t mgl_windows_window_functions =
{
	&mgl_windows_window_get_type,
	&mgl_windows_window_get_width,
	&mgl_windows_window_get_height,
	&mgl_windows_window_get_mode,
	&mgl_windows_window_poll_events,
	&mgl_windows_window_wait_for_events
};

mgl_error_t MGL_API mgl_open_windows_window(mgl_windows_window_t * window, const mgl_windows_window_settings_t * settings)
{
	MGL_DEBUG_ASSERT(window != NULL && settings != NULL);

	window->width = settings->width;
	window->height = settings->height;
	window->mode = settings->mode;

	window->base.functions = &mgl_windows_window_functions;
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
	return MGL_ERROR_NONE;
}

void MGL_API mgl_close_windows_window(mgl_windows_window_t * window)
{
	MGL_DEBUG_ASSERT(window != NULL);
}

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
			if (window->base.close_callback != NULL)
				window->base.close_callback(window);
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

			if (window->base.mouse_move_callback != NULL)
				window->base.mouse_move_callback(window, (mgl_f32_t)GET_X_LPARAM(lparam), (mgl_f32_t)GET_Y_LPARAM(lparam));
			break;
		}

		case WM_MOUSEHOVER:
		{
			if (window->base.mouse_enter_callback != NULL)
				window->base.mouse_enter_callback(window);
			break;
		}

		case WM_MOUSELEAVE:
		{
			window->tracking = MGL_FALSE;
			if (window->base.mouse_leave_callback != NULL)
				window->base.mouse_leave_callback(window);
			break;
		}
		
		case WM_MOUSEWHEEL:
		{
			if (window->base.mouse_scroll_callback != NULL)
				window->base.mouse_scroll_callback(window, GET_WHEEL_DELTA_WPARAM(wparam) > 0 ? 1.0f : -1.0f);
			break;
		}

		case WM_KEYDOWN:
		{
			if (wparam == VK_LSHIFT || wparam == VK_RSHIFT)
				window->shift = MGL_TRUE;
			else if (wparam == VK_MENU)
				window->alt = MGL_TRUE;
			else if (wparam == VK_LCONTROL || wparam == VK_RCONTROL)
				window->control = MGL_TRUE;
			else if (wparam == VK_LWIN || wparam == VK_RWIN)
				window->system = MGL_TRUE;

			if (window->base.key_down_callback != NULL)
			{
				mgl_enum_t mods = MGL_KEY_MOD_NONE;
				if (window->shift) mods |= MGL_KEY_MOD_SHIFT;
				if (window->alt) mods |= MGL_KEY_MOD_ALT;
				if (window->control) mods |= MGL_KEY_MOD_CONTROL;
				if (window->system) mods |= MGL_KEY_MOD_SYSTEM;

				window->base.key_down_callback(window, mgl_windows_key_to_mgl_key((int)wparam), mods);
			}
		}

		case WM_KEYUP:
		{
			if (wparam == VK_LSHIFT || wparam == VK_RSHIFT)
				window->shift = MGL_FALSE;
			else if (wparam == VK_MENU)
				window->alt = MGL_FALSE;
			else if (wparam == VK_LCONTROL || wparam == VK_RCONTROL)
				window->control = MGL_FALSE;
			else if (wparam == VK_LWIN || wparam == VK_RWIN)
				window->system = MGL_FALSE;

			if (window->base.key_up_callback != NULL)
			{
				mgl_enum_t mods = MGL_KEY_MOD_NONE;
				if (window->shift) mods |= MGL_KEY_MOD_SHIFT;
				if (window->alt) mods |= MGL_KEY_MOD_ALT;
				if (window->control) mods |= MGL_KEY_MOD_CONTROL;
				if (window->system) mods |= MGL_KEY_MOD_SYSTEM;

				window->base.key_up_callback(window, mgl_windows_key_to_mgl_key((int)wparam), mods);
			}
		}

		case WM_LBUTTONDOWN:
		{
			if (window->base.mouse_down_callback != NULL)
				window->base.mouse_down_callback(window, MGL_MOUSE_LEFT);
			break;
		}

		case WM_RBUTTONDOWN:
		{
			if (window->base.mouse_down_callback != NULL)
				window->base.mouse_down_callback(window, MGL_MOUSE_RIGHT);
			break;
		}

		case WM_MBUTTONDOWN:
		{
			if (window->base.mouse_down_callback != NULL)
				window->base.mouse_down_callback(window, MGL_MOUSE_MIDDLE);
			break;
		}

		case WM_XBUTTONDOWN:
		{
			if (window->base.mouse_down_callback != NULL)
			{
				if (GET_XBUTTON_WPARAM(wparam) == XBUTTON1)
					window->base.mouse_down_callback(window, MGL_MOUSE_EXTRA_0);
				else if (GET_XBUTTON_WPARAM(wparam) == XBUTTON2)
					window->base.mouse_down_callback(window, MGL_MOUSE_EXTRA_1);
			}
			break;
		}

		case WM_LBUTTONUP:
		{
			if (window->base.mouse_up_callback != NULL)
				window->base.mouse_up_callback(window, MGL_MOUSE_LEFT);
			break;
		}

		case WM_RBUTTONUP:
		{
			if (window->base.mouse_up_callback != NULL)
				window->base.mouse_up_callback(window, MGL_MOUSE_RIGHT);
			break;
		}

		case WM_MBUTTONUP:
		{
			if (window->base.mouse_up_callback != NULL)
				window->base.mouse_up_callback(window, MGL_MOUSE_MIDDLE);
			break;
		}

		case WM_XBUTTONUP:
		{
			if (window->base.mouse_up_callback != NULL)
			{
				if (GET_XBUTTON_WPARAM(wparam) == XBUTTON1)
					window->base.mouse_up_callback(window, MGL_MOUSE_EXTRA_0);
				else if (GET_XBUTTON_WPARAM(wparam) == XBUTTON2)
					window->base.mouse_up_callback(window, MGL_MOUSE_EXTRA_1);
			}
			break;
		}

		default:
			return DefWindowProc(hwnd, message, wparam, lparam);
	}

	return 0;
}

#endif
