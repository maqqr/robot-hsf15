#include "robotlogic.h"
#include <stdio.h>

ROBOT_API robot_output_t think(robot_input_t input)
{
    printf("rev. 2\n");
    robot_output_t output;
    output.left  = 0.0f;
    output.right = 0.0f;

    if (input.front_sensor < 40.0f)
    {
        //output.right = 0.0f;
    }

    return output;
}

