#ifndef _ROBOTLOGIC_H_
#define _ROBOTLOGIC_H_

/* Compiler defines NOTARDUINO, when not
 * compiling on Arduino. */
#ifdef NOTARDUINO
/* DLL export definition. */
#ifdef _WIN32
#define ROBOT_API __declspec(dllexport)
#else
#define ROBOT_API __attribute__((visibility("default")))
#endif /* _WIN32 */
#else
/* On Arduino, ROBOT_API means nothing. */
#define ROBOT_API
#endif /* NOTARDUINO */

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* _ROBOTLOGIC_H_ */
