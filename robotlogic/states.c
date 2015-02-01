#include "states.h"

robot_output_t state_forward_func(robot_input_t input)
{
  robot_output_t output;
  output.left = 1.0f;
  output.right = 1.0f;
  
  if (input.front_sensor < 40.0f)
  {
    output.left = 0.0f;
    output.right = 0.0f;
    
    // TODO: fix compile error
    // Move state stuff to this file.    
    state = state_init;
  }

  return output;
}

