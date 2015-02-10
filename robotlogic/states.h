#ifndef _STATES_H_
#define _STATES_H_

#include "robotlogic.h"

/* Enumeration of all possible states. */
typedef enum
{
    state_init = 0,
    state_forward,
    state_left,
    state_right,
    state_error,
    num_states
} STATE;

/* Global state variable. */
#ifdef __cplusplus
extern "C" {
#endif
extern STATE state;
#ifdef __cplusplus
}
#endif

/* State function forward declarations. */
#define STATE_FUNC(name) robot_output_t name(robot_input_t input);

STATE_FUNC(state_init_func)
STATE_FUNC(state_forward_func)
STATE_FUNC(state_left_func)
STATE_FUNC(state_right_func)
STATE_FUNC(state_error_func)

#endif /* _STATES_H_ */
