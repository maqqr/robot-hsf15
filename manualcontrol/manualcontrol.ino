#include <SoftwareSerial.h>

String buffer = "";
char c;

SoftwareSerial btSerial(2, 3); // RX, TX

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
 * Converts String to int.
 */
int stringToInt(String s) {
    char buf[100];
    s.toCharArray(buf, 100);
    return atoi(buf);
}

char streamRead()
{
  return btSerial.read();
}

/*
 * Performs one-time initialization.
 * Setups pin modes and serial communication.
 */
void setup() {  
  Serial.begin(9600);
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  btSerial.begin(9600);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
}

void parseCommand(String raw_cmd) {
    String cmd[5];
    for (int ii=0; ii<5; ii++) cmd[ii] = String("");

    int j = 0;
    for (int i=0; i < raw_cmd.length(); i++) {
        char c = raw_cmd.charAt(i);
        if (c == ':')
            j++;
        else
            cmd[j] += String(c);
    }

    if (cmd[0] == "F") {
      int speedd = stringToInt(cmd[1]);
      goForward(speedd / 256.0f);
     //goForward(1);
    }
    else if (cmd[0] == "B") {
      int speedd = stringToInt(cmd[1]);
      goBackward(speedd / 256.0f);
    }
    else if (cmd[0] == "L") {
      int speedd = stringToInt(cmd[1]);
      goLeft(speedd / 256.0f);
    }
    else if (cmd[0] == "R") {
      int speedd = stringToInt(cmd[1]);
      goRight(speedd / 256.0f);
    }
}

void readStream() {
  while (btSerial.available() > 0) {
    c = streamRead();

    if (c == '<') {
      Serial.println("Alkoi");
      buffer = "";
      // Accumulate buffer until c == '>'
      while (c != '>') {
        if (btSerial.available() > 0) {
          c = streamRead();
          if (c != '>') {
            buffer += c;
          }
        }
      }

      // Parse command
      //Serial.print("cmd: ");
      //Serial.println(buffer);
      parseCommand(buffer);
    }
  }
}

/*
 * Main loop.
 */
void loop() {
  //readInputs();  
  //goForward(0.7);
  readStream();
  delay(10);
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

int balanced = 135;
int full = 255;

void goLeft(float x) {
 digitalWrite(M1, LOW);  
 digitalWrite(M2, HIGH);      
 analogWrite(E2, (int)(full * x)); 
 analogWrite(E1, (int)(255 * x));
}

void goRight(float x) {
 digitalWrite(M2, LOW);  
 digitalWrite(M1, HIGH);      
 analogWrite(E2, (int)(full * x)); 
 analogWrite(E1, (int)(255 * x));
}

void goForward(float x) {
 digitalWrite(M1,LOW);
 digitalWrite(M2, LOW);
 analogWrite(E1, 255 * x);
 analogWrite(E2, full * x);
}
 
void goBackward(float x) {
  digitalWrite(M1,HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255 * x);
  analogWrite(E2, full * x);
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
