#include "robotlogic.h"

ROBOT_API robot_output_t think(robot_input_t input)
{
    robot_output_t output;
    output.move = 1;
    output.turn = 0;

    /* Stop if near a wall. */
    if (input.test_sensor_1 < 30.0f)
    {
        output.move = 0;
    }

    return output;
}
