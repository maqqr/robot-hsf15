#include "robotlogic.h"

const int E1 = 4;
const int E2 = 7;
const int leftM1 = 5;
const int rightM2 = 6;

const int frontTrigPin = 13;
const int frontEchoPin = 12;

const int leftTrigPin = 11;
const int leftEchoPin = 10;

const int rightTrigPin = 9;
const int rightEchoPin = 8;

const int maxSpeed = 255;


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

void setup() {
  Serial.begin(9600);
  Serial.begin (9600);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
}

void loop() {
  robot_input_t input;
  input.front_sensor = read_distance(frontTrigPin, frontEchoPin);
  input.left_sensor = read_distance(leftTrigPin, leftEchoPin);
  input.right_sensor = read_distance(rightTrigPin,rightEchoPin);

  robot_output_t output = think(input);
  analogWrite(leftM1, output.left);
  analogWrite(rightM2, output.right);
}

