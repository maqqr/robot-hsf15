#ifndef _ROBOTLOGIC_H_
#define _ROBOTLOGIC_H_

/* DLL export definition. */
#define ROBOT_API __declspec(dllexport)

/* --------- Structs --------- */

/*
 * Sensor inputs for robot logic.
 */
typedef struct
{
    float test_sensor_1;
    float test_sensor_2;
    float test_sensor_3;
} robot_input_t;

/*
 * Robot output.
 * Contains commands for actuators.
 */
typedef struct
{
    int move; /*  1 = forwards, -1 = backwards */
    int turn; /* -1 = left,      1 = right */
} robot_output_t;

/* --------- Robot API --------- */

/* Converts sensor inputs into actuator outputs. */
ROBOT_API robot_output_t think(robot_input_t input);


#endif /* _ROBOTLOGIC_H_ */
