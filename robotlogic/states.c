#include "states.h"


/* Initial robot state. */
robot_output_t state_init_func(robot_input_t input)
{
  state = state_forward;
  return zerooutput;
}

robot_output_t state_forward_func(robot_input_t input)
{
  robot_output_t output;
  output.left = 1.0f;
  output.right = 1.0f;
  
  if (input.front_sensor < 40.0f)
  {
    output.left = 0.0f;
    output.right = 0.0f;
  }

  return output;
}

robot_output_t state_left_func(robot_input_t input)
{
  return zerooutput;
}

robot_output_t state_right_func(robot_input_t input)
{
  return zerooutput;
}

robot_output_t state_error_func(robot_input_t input)
{
  return zerooutput;
}
