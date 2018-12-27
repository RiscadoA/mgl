#ifndef MGL_INPUT_MOUSE_H
#define MGL_INPUT_MOUSE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

enum
{
	MGL_MOUSE_LEFT,
	MGL_MOUSE_RIGHT,
	MGL_MOUSE_MIDDLE,
	MGL_MOUSE_EXTRA_1,
	MGL_MOUSE_EXTRA_2,

	MGL_MOUSE_BUTTON_COUNT
};

enum
{
	MGL_MOUSE_X, // X mouse coordinate axis
	MGL_MOUSE_Y, // Y mouse coordinate axis
	MGL_MOUSE_WHEEL, // Mouse wheel delta axis

	MGL_MOUSE_AXES_COUNT
};

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_MOUSE_H
