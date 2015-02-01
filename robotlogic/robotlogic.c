#include "robotlogic.h"
#include "states.h"
#include <stdio.h>


/* Initial robot state. */
robot_output_t state_init_func(robot_input_t input)
{
    return zerooutput;
}


/* Enumeration of all possible states. */
enum STATE
{
    state_init = 0,
    state_forward,
    state_left,
    state_right,
    state_error,
    num_states
} state = state_init;


/* Array of function pointers pointing to state functions. */
statefunc states[] = {
    state_init_func,
    state_forward_func
};


/* Selects which state function to call. */
ROBOT_API robot_output_t think(robot_input_t input)
{
    return states[state](input);

    /*
    printf("rev. 3\n");
    robot_output_t output;
    output.left  = 1.0f;
    output.right = 1.0f;

    if (input.front_sensor < 40.0f)
    {
        output.right = 0.0f;
        output.left = 0.0f;
    }

    return output;
    */
}

