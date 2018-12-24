#ifndef MGL_INPUT_INPUT_MANAGER_H
#define MGL_INPUT_INPUT_MANAGER_H

#include <mgl/input/button.h>
#include <mgl/input/axis.h>
#include <mgl/input/action.h>
#include <mgl/error.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_INPUT_MANAGER_MAX_BUTTON_COUNT 2048
#define MGL_INPUT_MANAGER_MAX_AXIS_COUNT 256
#define MGL_INPUT_MANAGER_MAX_ACTION_COUNT 2048

typedef struct
{
    mgl_button_t buttons[MGL_INPUT_MANAGER_MAX_BUTTON_COUNT];
    mgl_axis_t axes[MGL_INPUT_MANAGER_MAX_AXIS_COUNT];
    mgl_action_t actions[MGL_INPUT_MANAGER_MAX_ACTION_COUNT];
} mgl_input_manager_t;

void MGL_API mgl_init_input_manager(mgl_input_manager_t* manager);

mgl_error_t MGL_API mgl_add_button(mgl_input_manager_t* manager, mgl_button_t** button, const mgl_chr8_t* name);

mgl_error_t MGL_API mgl_add_axis(mgl_input_manager_t* manager, mgl_axis_t** axis, const mgl_chr8_t* name);

mgl_error_t MGL_API mgl_add_action(mgl_input_manager_t* manager, mgl_action_t** action, mgl_enum_t type, const mgl_chr8_t* name);

void MGL_API mgl_remove_button(mgl_input_manager_t* manager, mgl_u32_t id);

void MGL_API mgl_remove_axis(mgl_input_manager_t* manager, mgl_u32_t id);

void MGL_API mgl_remove_action(mgl_input_manager_t* manager, mgl_u32_t id);

void MGL_API mgl_feed_button(mgl_input_manager_t* manager, mgl_u32_t id, mgl_bool_t pressed);

void MGL_API mgl_feed_axis(mgl_input_manager_t* manager, mgl_u32_t id, mgl_f32_t value);

void MGL_API mgl_feed_axis_instant(mgl_input_manager_t* manager, mgl_u32_t id, mgl_f32_t instant_value, mgl_f32_t desired_value);

mgl_error_t MGL_API mgl_add_action_callback(mgl_input_manager_t* manager, mgl_u32_t id, mgl_action_callback_t callback);

void MGL_API mgl_remove_action_callback(mgl_input_manager_t* manager, mgl_u32_t id, mgl_action_callback_t callback);

void MGL_API mgl_update_input_manager(mgl_input_manager_t* manager, mgl_f32_t step);

mgl_u32_t MGL_API mgl_get_button(mgl_input_manager_t* manager, const mgl_chr8_t* name);

mgl_u32_t MGL_API mgl_get_axis(mgl_input_manager_t* manager, const mgl_chr8_t* name);

mgl_u32_t MGL_API mgl_get_action(mgl_input_manager_t* manager, const mgl_chr8_t* name);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_INPUT_MANAGER_H
