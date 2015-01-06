#include "robotlogic.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    robot_input_t input;
    // TODO: read values from real sensors.
    input.test_sensor_1 = 70.0f;

    robot_output_t output = think(input);
    Serial.println(output.move);
    // TODO: move motors based on output.
}
