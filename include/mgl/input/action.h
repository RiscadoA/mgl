#ifndef MGL_INPUT_ACTION_H
#define MGL_INPUT_ACTION_H

#include <mgl/type.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_NULL_ACTION MGL_U32_MAX
#define MGL_MAX_ACTION_NAME_SIZE 64
#define MGL_MAX_BUTTON_GROUP_SIZE 4
#define MGL_MAX_BUTTON_SEQUENCE_SIZE 4
#define MGL_MAX_ACTION_CALLBACKS 16

#define MGL_MAX_INTERFERING_BUTTONS 32

// Action types
enum
{
	MGL_ACTION_EMPTY, // Empty action (triggered manually)
	MGL_ACTION_BUTTON, // Triggered when a button is pressed or released (MGL_ACTION_PRESSED or MGL_ACTION_RELEASED)
	MGL_ACTION_BUTTON_GROUP, // Triggered when a group of buttons are pressed or released (MGL_ACTION_PRESSED or MGL_ACTION_RELEASED)
	MGL_ACTION_BUTTON_SEQUENCE, // Triggered when a sequence of buttons is pressed (MGL_ACTION_PRESSED)
    MGL_ACTION_AXIS_RANGE, // Triggered when an axis enters or leaves a certain range of values (MGL_ACTION_ENTERED or MGL_ACTION_LEFT)
};

// Action states
enum
{
	MGL_ACTION_FIRED,
    MGL_ACTION_PRESSED,
    MGL_ACTION_RELEASED,
    MGL_ACTION_ENTERED,
    MGL_ACTION_LEFT,
};

typedef struct mgl_action_t mgl_action_t;

typedef void(*mgl_action_callback_t)(const mgl_action_t* action, mgl_enum_t state);

struct mgl_action_t
{
    mgl_chr8_t name[MGL_MAX_ACTION_NAME_SIZE];
    mgl_u32_t id;
    mgl_action_callback_t callbacks[MGL_MAX_ACTION_CALLBACKS];
    mgl_enum_t type;
	void* data; // User data

    // Action type specific data
    union
    {
        // MGL_ACTION_BUTTON
        struct
        {
            mgl_u32_t id;
            mgl_u32_t alt;
        } button;

        // MGL_ACTION_BUTTON_GROUP
        struct
        {
            mgl_u32_t buttons[MGL_MAX_BUTTON_GROUP_SIZE];
            mgl_u32_t button_count;
            mgl_u32_t pressed_buttons;
        } group;

        // MGL_ACTION_BUTTON_SEQUENCE
        struct
        {
            mgl_u32_t interfering_buttons[MGL_MAX_INTERFERING_BUTTONS];
            mgl_u32_t buttons[MGL_MAX_BUTTON_SEQUENCE_SIZE];
            mgl_u32_t next_button; // Next button to be pressed
            mgl_u32_t button_count; // Number of buttons in the sequence
            mgl_bool_t whitelist; // Are the interfering buttons whitelisted or blacklisted on the sequence
            mgl_bool_t can_release; // Can the buttons be released during the sequence
        } sequence;

        // MGL_ACTION_AXIS_RANGE
        struct
        {
            mgl_u32_t id;
            mgl_f32_t range_min;
            mgl_f32_t range_max;
        } axis_range;
    };
};

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_ACTION_H
