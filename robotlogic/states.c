#include "states.h"

#define FAST 0.80f
#define SLOW 0.60f

#define SLOW_LIMIT 45.0f
#define WALL_LIMIT 25.0f

#define LR_WALL_LIMIT 10.0f

#define TURN_SPEED 0.6f


int check_error(robot_input_t input)
{
  if (input.front_sensor < 5.0f)
  {
    state = state_error;
    return 1;
  }
  return 0;
}

/* Initial robot state. */
robot_output_t state_init_func(robot_input_t input)
{
  /* TODO: is this state useless? */
  state = state_forward; /* Change immediately into forward state. */
  return zerooutput;
}

robot_output_t state_forward_func(robot_input_t input)
{
  if (check_error(input))
  {
    return zerooutput;
  }

  robot_output_t output;
  output.left = FAST;
  output.right = FAST;

  // Slow down near a wall.
  if (input.front_sensor < SLOW_LIMIT)
  {
    output.left = SLOW;
    output.right = SLOW;
  }
  
  // Turn when too close to a wall.
  if (input.front_sensor < WALL_LIMIT ||
      input.left_sensor < LR_WALL_LIMIT ||
      input.right_sensor < LR_WALL_LIMIT)
  {
    state = input.left_sensor > input.right_sensor? state_left : state_right;
  }

  return output;
}

robot_output_t state_left_func(robot_input_t input)
{
  robot_output_t output;
  output.left = -TURN_SPEED;
  output.right = TURN_SPEED;

  // Continue forwards when there is enough space.
  if (input.front_sensor < WALL_LIMIT + 30.0f)
  {
    state = state_forward;
  }

  return output;
}

robot_output_t state_right_func(robot_input_t input)
{
  robot_output_t output;
  output.left = TURN_SPEED;
  output.right = -TURN_SPEED;

  // Continue forwards when there is enough space.
  if (input.front_sensor < WALL_LIMIT + 10.0f)
  {
    state = state_forward;
  }

  return output;
}

robot_output_t state_error_func(robot_input_t input)
{
  // Something is wrong, go backwards.
  robot_output_t output;
  output.left = -FAST;
  output.right = -FAST;

  if (input.front_sensor > 30.0f)
  {
    state = state_forward;
  }

  return output;
}
