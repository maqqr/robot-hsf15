
// Motor control pins.
const int E1 = 5;       // R
const int E2 = 6;       // L
const int M1 = 4;   // Right
const int M2 = 7;   // L

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
  //readInputs();  
  goRight();
}

void readInputs(){   
  float left_sensor = read_distances(leftTrigPin, leftEchoPin);
  float right_sensor = read_distances(rightTrigPin,rightEchoPin);
  
  //Serial.print(front_sensor);
  //Serial.print(",");
  Serial.print(left_sensor);
  Serial.print(",");
  Serial.println(right_sensor);
}

void goLeft(float x) {
 digitalWrite(M1, LOW);  
 digitalWrite(M2, HIGH);      
 analogWrite(E2, (int)(135 * x)); 
 analogWrite(E1, (int)(255 * x));
}

void goRight(float x) {
 digitalWrite(M2, LOW);  
 digitalWrite(M1, HIGH);      
 analogWrite(E2, (int)(135 * x)); 
 analogWrite(E1, (int)(255 * x));
}


void goForward(float x) {
 digitalWrite(M1,LOW);
 digitalWrite(M2, LOW);
 analogWrite(E1, 255 * x);
 analogWrite(E2, 135 * x);
}
 
void goBackward(float x) {
  digitalWrite(M1,HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255 * x);
  analogWrite(E2, 135 * x);
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
