#include "robotlogic.h"
#include <stdio.h>

ROBOT_API robot_output_t think(robot_input_t input)
{
    /* printf("rev. 1\n"); */
    robot_output_t output;
    output.left  = 1.0f;
    output.right = 1.0f;

    if (input.test_sensor_1 < 40.0f)
    {
        output.right = 0.0f;
    }

    return output;
}

