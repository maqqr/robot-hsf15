#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "Arduino.h"

// Motor control pins.
const int E1 = 4;       // Left motor direction control.
const int E2 = 7;       // Right motor direction control.
const int leftM1 = 5;   // Left motor speed control.
const int rightM2 = 6;  // Right motor speed control.

// Sensor pins.
const int frontTrigPin = 13;
const int frontEchoPin = 12;
const int leftTrigPin = 11;
const int leftEchoPin = 10;
const int rightTrigPin = 9;
const int rightEchoPin = 8;

const int maxSpeed = 255; // Must be between 0-255.

/*
 * Reads distance sensor value.
 */
float read_distance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  float distance = (duration / 2.0) / 29.1;
  return distance;
}

/*
 * Controls motor speed and direction.
 * value must be in range [-255, 255].
 */
void setMotor(int E, int M, int value)
{
  if (value < 0) {
    digitalWrite(M, LOW);
    value = abs(value);
  }
  else {
    digitalWrite(M, HIGH);
  }
  Serial.print("motor ");
  Serial.println(value);
  analogWrite(E, value);
}

#endif /* _ROBOT_H_ */
