#ifndef MGL_INPUT_AXIS_H
#define MGL_INPUT_AXIS_H

#include <mgl/type.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_NULL_AXIS MGL_U32_MAX
#define MGL_MAX_AXIS_NAME_SIZE 64

typedef struct
{
    mgl_chr8_t name[MGL_MAX_AXIS_NAME_SIZE]; // Axis name
    mgl_u32_t id; // Axis ID
    mgl_f32_t min_value; // Minimum calculated axis value
    mgl_f32_t max_value; // Maximum calculated axis value
    mgl_f32_t value; // Calculated axis value
    mgl_f32_t desired_value; // The 'real' input axis value
    mgl_f32_t speed; // ]0; +inf]; 1 -> value = desired_value in 1 second; 0 -> value doesn't change
} mgl_axis_t;

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_AXIS_H
