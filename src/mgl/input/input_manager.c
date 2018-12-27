#include <mgl/input/input_manager.h>
#include <mgl/string/manipulation.h>

void MGL_API mgl_init_input_manager(mgl_input_manager_t* manager)
{
    MGL_DEBUG_ASSERT(manager != NULL);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_BUTTON_COUNT; ++i)
        manager->buttons[i].id = MGL_NULL_BUTTON;
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_AXIS_COUNT; ++i)
        manager->axes[i].id = MGL_NULL_AXIS;
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_ACTION_COUNT; ++i)
        manager->actions[i].id = MGL_NULL_ACTION;
}

mgl_error_t MGL_API mgl_add_button(mgl_input_manager_t* manager, mgl_button_t** button, const mgl_chr8_t* name)
{
    MGL_DEBUG_ASSERT(manager != NULL && button != NULL);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_BUTTON_COUNT; ++i)
    {
        if (manager->buttons[i].id != MGL_NULL_BUTTON)
            continue;
        manager->buttons[i].id = i;
        if (name == NULL)
            mgl_str_copy(u8"[null]", manager->buttons[i].name, MGL_MAX_BUTTON_NAME_SIZE);
        else
            mgl_str_copy(name, manager->buttons[i].name, MGL_MAX_BUTTON_NAME_SIZE);
        manager->buttons[i].pressed = MGL_FALSE;
        *button = &manager->buttons[i];
        return MGL_ERROR_NONE;
    }
    return MGL_ERROR_OVERFLOW;
}

mgl_error_t MGL_API mgl_add_axis(mgl_input_manager_t* manager, mgl_axis_t** axis, const mgl_chr8_t* name)
{
    MGL_DEBUG_ASSERT(manager != NULL && axis != NULL && name != NULL);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_AXIS_COUNT; ++i)
    {
        if (manager->axes[i].id != MGL_NULL_AXIS)
            continue;
        manager->axes[i].id = i;
        if (name == NULL)
            mgl_str_copy(u8"[null]", manager->axes[i].name, MGL_MAX_AXIS_NAME_SIZE);
        else
            mgl_str_copy(name, manager->axes[i].name, MGL_MAX_AXIS_NAME_SIZE);
        manager->axes[i].desired_value = 0.0f;
        manager->axes[i].value = 0.0f;
        manager->axes[i].speed = 1.0f;
        manager->axes[i].min_value = -1.0f;
        manager->axes[i].max_value = 1.0f;
        *axis = &manager->axes[i];
        return MGL_ERROR_NONE;
    }
    return MGL_ERROR_OVERFLOW;
}

mgl_error_t MGL_API mgl_add_action(mgl_input_manager_t* manager, mgl_action_t** action, mgl_enum_t type, const mgl_chr8_t* name)
{
    MGL_DEBUG_ASSERT(manager != NULL && action != NULL && name != NULL);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_ACTION_COUNT; ++i)
    {
        if (manager->actions[i].id != MGL_NULL_ACTION)
            continue;
        switch (type)
        {
			case MGL_ACTION_EMPTY: break;
            case MGL_ACTION_BUTTON:
            {
                manager->actions[i].button.id = MGL_NULL_BUTTON;
                manager->actions[i].button.alt = MGL_NULL_BUTTON;
                break;
            }
            case MGL_ACTION_BUTTON_GROUP:
            {
                for (mgl_u32_t j = 0; j < MGL_MAX_BUTTON_GROUP_SIZE; ++j)
                    manager->actions[i].group.buttons[j] = MGL_NULL_BUTTON;
                manager->actions[i].group.button_count = 0;
                manager->actions[i].group.pressed_buttons = 0;
                break;
            }
            case MGL_ACTION_BUTTON_SEQUENCE:
            {
                for (mgl_u32_t j = 0; j < MGL_MAX_BUTTON_SEQUENCE_SIZE; ++j)
                    manager->actions[i].sequence.buttons[j] = MGL_NULL_BUTTON;
                for (mgl_u32_t j = 0; j < MGL_MAX_INTERFERING_BUTTONS; ++j)
                    manager->actions[i].sequence.interfering_buttons[j] = MGL_NULL_BUTTON;
                manager->actions[i].sequence.button_count = 0;
                manager->actions[i].sequence.next_button = 0;
                manager->actions[i].sequence.whitelist = MGL_FALSE;
                break;
            }
            case MGL_ACTION_AXIS_RANGE:
            {
                manager->actions[i].axis_range.id = MGL_NULL_AXIS;
                manager->actions[i].axis_range.range_min = -INFINITY;
                manager->actions[i].axis_range.range_max = +INFINITY;
                break;
            }
            default:
                return MGL_ERROR_INVALID_PARAMS;
        }
        manager->actions[i].id = i;
        if (name == NULL)
            mgl_str_copy(u8"[null]", manager->actions[i].name, MGL_MAX_ACTION_NAME_SIZE);
        else
            mgl_str_copy(name, manager->actions[i].name, MGL_MAX_ACTION_NAME_SIZE);
        for (mgl_u32_t j = 0; j < MGL_MAX_ACTION_CALLBACKS; ++j)
            manager->actions[i].callbacks[j] = NULL;
        manager->actions[i].type = type;
        *action = &manager->actions[i];
        return MGL_ERROR_NONE;
    }
    return MGL_ERROR_OVERFLOW;
}

void MGL_API mgl_remove_button(mgl_input_manager_t* manager, mgl_u32_t id)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_BUTTON_COUNT);
    manager->buttons[id].id = MGL_NULL_BUTTON;
}

void MGL_API mgl_remove_axis(mgl_input_manager_t* manager, mgl_u32_t id)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_AXIS_COUNT);
    manager->axes[id].id = MGL_NULL_AXIS;
}

void MGL_API mgl_remove_action(mgl_input_manager_t* manager, mgl_u32_t id)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_ACTION_COUNT);
    manager->actions[id].id = MGL_NULL_ACTION;
}

void MGL_API mgl_feed_button(mgl_input_manager_t* manager, mgl_u32_t id, mgl_bool_t pressed)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_BUTTON_COUNT && manager->buttons[id].id != MGL_NULL_BUTTON);
    mgl_bool_t old_state = manager->buttons[id].pressed;
    manager->buttons[id].pressed = pressed;

    mgl_enum_t state;
    if (pressed == MGL_TRUE && old_state == MGL_FALSE)
        state = MGL_ACTION_PRESSED;
    else if (pressed == MGL_FALSE && old_state == MGL_TRUE)
        state = MGL_ACTION_RELEASED;
    else
        return;

    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_ACTION_COUNT; ++i)
    {
        mgl_action_t* action = &manager->actions[i];

        if (action->id == MGL_NULL_ACTION || action->type == MGL_ACTION_AXIS_RANGE)
            continue;

        if (action->type == MGL_ACTION_BUTTON)
        {
            if (action->button.id == id)
                for (mgl_u32_t j = 0; j < MGL_MAX_ACTION_CALLBACKS; ++j)
                    if (action->callbacks[j] != NULL)
                        action->callbacks[j](action, state);
        }
        else if (manager->actions[i].type == MGL_ACTION_BUTTON_GROUP)
        {
            mgl_bool_t in = MGL_FALSE;
            for (mgl_u32_t i = 0; i < MGL_MAX_BUTTON_GROUP_SIZE; ++i)
                if (action->group.buttons[i] == id)
                {
                    in = MGL_TRUE;
                    break;
                }
            if (!in)
                continue;

            if (state == MGL_ACTION_PRESSED)
            {
                action->group.pressed_buttons += 1;
                if (action->group.pressed_buttons == action->group.button_count)
                    for (mgl_u32_t j = 0; j < MGL_MAX_ACTION_CALLBACKS; ++j)
                        if (action->callbacks[j] != NULL)
                            action->callbacks[j](action, MGL_ACTION_PRESSED);
            }
            else
            {
                if (action->group.pressed_buttons == action->group.button_count)
                    for (mgl_u32_t j = 0; j < MGL_MAX_ACTION_CALLBACKS; ++j)
                        if (action->callbacks[j] != NULL)
                            action->callbacks[j](action, MGL_ACTION_RELEASED);
                action->group.pressed_buttons -= 1;
            }
        }
        else if (manager->actions[i].type == MGL_ACTION_BUTTON_SEQUENCE)
        {
            mgl_bool_t interfering = MGL_FALSE;
            for (mgl_u32_t i = 0; i < MGL_MAX_INTERFERING_BUTTONS; ++i)
                if (action->sequence.interfering_buttons[i] == id)
                {
                    interfering = MGL_TRUE;
                    break;
                }
            if (interfering && action->sequence.whitelist)
                continue;
            else if (interfering && !action->sequence.whitelist)
            {
                action->sequence.next_button = 0;
                continue;
            }

            mgl_bool_t in = MGL_FALSE;
            for (mgl_u32_t i = 0; i < MGL_MAX_BUTTON_SEQUENCE_SIZE; ++i)
                if (action->sequence.buttons[i] == id)
                {
                    in = MGL_TRUE;
                    break;
                }

            if (state == MGL_ACTION_PRESSED)
            {
                if (in)
                {
                    if (action->sequence.buttons[action->sequence.next_button] == id)
                        action->sequence.next_button += 1;
                    else
                    {
                        action->sequence.next_button = 0;
                        continue;
                    }

                    if (action->sequence.next_button == action->sequence.button_count)
                    {
                        action->sequence.next_button = 0;
                        for (mgl_u32_t j = 0; j < MGL_MAX_ACTION_CALLBACKS; ++j)
                            if (action->callbacks[j] != NULL)
                                action->callbacks[j](action, MGL_ACTION_PRESSED);
                    }
                }
                else if (action->sequence.whitelist)
                {
                    action->sequence.next_button = 0;
                    continue;
                }
            }
            else if (!action->sequence.can_release && in)
            {
                action->sequence.next_button = 0;
                continue;
            }
        }
    }
}

static void mgl_check_axis_events(mgl_input_manager_t* manager, mgl_u32_t id, mgl_f32_t old_value)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_AXIS_COUNT);
    mgl_f32_t value = manager->axes[id].value;

    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_ACTION_COUNT; ++i)
    {
        if (manager->actions[i].id == MGL_NULL_ACTION ||
            manager->actions[i].type != MGL_ACTION_AXIS_RANGE ||
            manager->actions[i].axis_range.id != id)
            continue;

        mgl_bool_t old_in = old_value >= manager->actions[i].axis_range.range_min &&
                            old_value <= manager->actions[i].axis_range.range_max;

        mgl_bool_t in = value >= manager->actions[i].axis_range.range_min &&
                        value <= manager->actions[i].axis_range.range_max;

        // Entered axis range
        if (!old_in && in)
        {
            for (mgl_u32_t j = 0; j < MGL_MAX_ACTION_CALLBACKS; ++j)
                if (manager->actions[i].callbacks[j] != NULL)
                    manager->actions[i].callbacks[j](&manager->actions[i], MGL_ACTION_ENTERED);
        }
        // Left axis range
        else if (old_in && !in)
        {
            for (mgl_u32_t j = 0; j < MGL_MAX_ACTION_CALLBACKS; ++j)
                if (manager->actions[i].callbacks[j] != NULL)
                    manager->actions[i].callbacks[j](&manager->actions[i], MGL_ACTION_LEFT);
        }
    }
}

void MGL_API mgl_feed_axis(mgl_input_manager_t* manager, mgl_u32_t id, mgl_f32_t value)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_AXIS_COUNT);
    manager->axes[id].desired_value = value;
}

void MGL_API mgl_feed_axis_instant(mgl_input_manager_t* manager, mgl_u32_t id, mgl_f32_t instant_value, mgl_f32_t desired_value)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_AXIS_COUNT);
    mgl_f32_t old_value = manager->axes[id].value;
    manager->axes[id].value = instant_value;
    manager->axes[id].desired_value = desired_value;
    mgl_check_axis_events(manager, id, old_value);
}

void MGL_API mgl_fire_action(mgl_input_manager_t * manager, mgl_u32_t id, mgl_enum_t state)
{
	MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_ACTION_COUNT);
	for (mgl_u32_t i = 0; i < MGL_MAX_ACTION_CALLBACKS; ++i)
		if (manager->actions[id].callbacks[i] != NULL)
			manager->actions[id].callbacks[i](&manager->actions[id], state);
}

mgl_error_t MGL_API mgl_add_action_callback(mgl_input_manager_t* manager, mgl_u32_t id, mgl_action_callback_t callback)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_ACTION_COUNT && manager->actions[id].id != MGL_NULL_ACTION);
    for (mgl_u32_t i = 0; i < MGL_MAX_ACTION_CALLBACKS; ++i)
        if (manager->actions[id].callbacks[i] == NULL)
        {
            manager->actions[id].callbacks[i] = callback;
            return MGL_ERROR_NONE;
        }
    return MGL_ERROR_OVERFLOW;
}

void MGL_API mgl_remove_action_callback(mgl_input_manager_t* manager, mgl_u32_t id, mgl_action_callback_t callback)
{
    MGL_DEBUG_ASSERT(manager != NULL && id < MGL_INPUT_MANAGER_MAX_ACTION_COUNT && manager->actions[id].id != MGL_NULL_ACTION);
    for (mgl_u32_t i = 0; i < MGL_MAX_ACTION_CALLBACKS; ++i)
        if (manager->actions[id].callbacks[i] == callback)
        {
            manager->actions[id].callbacks[i] = NULL;
            return;
        }
}

void MGL_API mgl_update_input_manager(mgl_input_manager_t* manager, mgl_f32_t step)
{
    MGL_DEBUG_ASSERT(manager != NULL && step > 0.0f);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_AXIS_COUNT; ++i)
    {
        if (manager->axes[i].id == MGL_NULL_AXIS)
            continue;

        mgl_f32_t old_value = manager->axes[i].value;
        mgl_f32_t delta = manager->axes[i].desired_value - manager->axes[i].value;
        mgl_f32_t real_delta = delta * step * manager->axes[i].speed;
        if ((delta >= 0 && real_delta > delta) ||
            (delta < 0 && real_delta < delta) ||
            manager->axes[i].speed == INFINITY)
            real_delta = delta;
        mgl_f32_t value = old_value + real_delta;
        if (value > manager->axes[i].max_value)
            value = manager->axes[i].max_value;
        else if (value < manager->axes[i].min_value)
            value = manager->axes[i].min_value;
        manager->axes[i].value = value;
        mgl_check_axis_events(manager, i, old_value);
    }
}

mgl_u32_t MGL_API mgl_get_button(mgl_input_manager_t* manager, const mgl_chr8_t* name)
{
    MGL_DEBUG_ASSERT(manager != NULL && name != NULL);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_BUTTON_COUNT; ++i)
        if (manager->buttons[i].id != MGL_NULL_BUTTON && mgl_str_equal(name, manager->buttons[i].name))
            return i;
    return MGL_NULL_BUTTON;
}

mgl_u32_t MGL_API mgl_get_axis(mgl_input_manager_t* manager, const mgl_chr8_t* name)
{
    MGL_DEBUG_ASSERT(manager != NULL && name != NULL);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_AXIS_COUNT; ++i)
        if (manager->axes[i].id != MGL_NULL_AXIS && mgl_str_equal(name, manager->axes[i].name))
            return i;
    return MGL_NULL_AXIS;
}

mgl_u32_t MGL_API mgl_get_action(mgl_input_manager_t* manager, const mgl_chr8_t* name)
{
    MGL_DEBUG_ASSERT(manager != NULL && name != NULL);
    for (mgl_u32_t i = 0; i < MGL_INPUT_MANAGER_MAX_ACTION_COUNT; ++i)
        if (manager->actions[i].id != MGL_NULL_ACTION && mgl_str_equal(name, manager->actions[i].name))
            return i;
    return MGL_NULL_ACTION;
}
