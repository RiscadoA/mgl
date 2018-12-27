#ifndef MGL_INPUT_BUTTON_H
#define MGL_INPUT_BUTTON_H

#include <mgl/type.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MGL_NULL_BUTTON MGL_U32_MAX
#define MGL_MAX_BUTTON_NAME_SIZE 64

typedef struct
{
    mgl_chr8_t name[MGL_MAX_BUTTON_NAME_SIZE]; // Button name
    mgl_u32_t id; // Button ID
    mgl_bool_t pressed; // Button state (MGL_TRUE = pressed; MGL_FALSE = released)
} mgl_button_t;

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_INPUT_BUTTON_H
