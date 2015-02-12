//#include "robot.h"

// Motor control pins.
const int E1 = 5;       // Left motor direction control.
const int E2 = 6;       // Right motor direction control.
const int M1 = 4;   // Left motor speed control.
const int M2 = 7;  // Right motor speed control.

// Sensor pins.
const int frontTrigPin = 13;
const int frontEchoPin = 12;
const int leftTrigPin = 11;
const int leftEchoPin = 10;
const int rightTrigPin = 9;
const int rightEchoPin = 8;

/*
 * Performs one-time initialization.
 * Setups pin modes and serial communication.
 */
void setup() {  
  Serial.begin(9600);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
}

/*
 * Main loop.
 */
void loop() {
  goForward();
 //readInputs();
  
}

void readInputs(){   
  // Read input from sensors.
  //float front_sensor = read_distances(frontTrigPin, frontEchoPin);
  float left_sensor = read_distances(leftTrigPin, leftEchoPin);
  float right_sensor = read_distances(rightTrigPin,rightEchoPin);
  
  //Serial.print(front_sensor);
  //Serial.print(",");
  Serial.print(left_sensor);
  Serial.print(",");
  Serial.println(right_sensor);
  
  goForward();
  if(left_sensor < 7) goRight();
  if(right_sensor < 7) goLeft();
  if(left_sensor > 100) goRight();
  if(right_sensor > 100) goLeft();
  //if(left_sensor + right_sensor < 35) goForward();
  //else goStop();
  //if(left_sensor + right_sensor > 250) goStop();
}

void goLeft() {
 digitalWrite(M1, HIGH);  
 digitalWrite(M2, LOW);      
//analogWrite(E2, -1);   
 analogWrite(E1, 1);   
} 
void goRight() {
 digitalWrite(M1, LOW);  
 digitalWrite(M2, HIGH);      
 analogWrite(E2, 1);   
 //analogWrite(E2, 1); 
}
void goForward() {
 digitalWrite(M1,LOW);  
 digitalWrite(M2, LOW);      //Arduino PWM Speed Control：
 analogWrite(E2, 1);   
 analogWrite(E2, 1); 
}
 
void goStop() {
  digitalWrite(M1,LOW);  
  digitalWrite(M2, LOW); 
}

/*
 * Reads distance sensor value.
 */
float read_distances(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  float distance = (duration / 2.0) / 29.1;
  return distance;
}
