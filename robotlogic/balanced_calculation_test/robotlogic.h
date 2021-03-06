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
    float front_sensor;
    float left_sensor;
    float right_sensor;
} robot_input_t;

/*
 * Robot output.
 * Contains commands for actuators.
 */
typedef struct
{
    /* 1.0 = forwards, -1.0 = backwards */
    float left;  /* Left wheel.  */
    float right; /* Right wheel. */
} robot_output_t;

/* Predefined robot_output_t value. Both wheels are stopped. */
static const robot_output_t zerooutput = { 0.0f, 0.0f };

/* --------- Robot API --------- */

/* Function pointer for state functions. */
typedef robot_output_t (*statefunc)(robot_input_t input);

/* Executes one step in the state machine. */
ROBOT_API robot_output_t think(robot_input_t input);

#ifdef __cplusplus
}
#endif

#endif /* _ROBOTLOGIC_H_ */

