#include "robotlogic.h"
#include "states.h"
#include <stdio.h>

STATE state = state_init;

/* An array of function pointers pointing to state functions. */
statefunc states[] = {
    state_init_func,
    state_forward_func,
    state_left_func,
    state_right_func,
    state_error_func
};

/* Executes one step in the state machine. */
ROBOT_API robot_output_t think(robot_input_t input)
{
    /* printf("rev. 3\n"); */
    return states[state](input);
}
