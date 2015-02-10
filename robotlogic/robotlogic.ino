#include "robotlogic.h"
#include "states.h"
#include "robot.h"

// Enable Bluetooth serial control (SoftwareSerial).
// If disabled, then standard Arduino Serial will be used.
//#define BT

String buffer = "";
char c;

int autopilot = 0;

#ifdef BT
#include <SoftwareSerial.h>
#define TxD 2
#define RxD 3
SoftwareSerial btSerial(RxD, TxD);
#endif /* BT */

/*
 * Converts String to int.
 */
int stringToInt(String s) {
    char buf[100];
    s.toCharArray(buf, 100);
    return atoi(buf);
}

/*
 * Performs one-time initialization.
 * Setups pin modes and serial communication.
 */
void setup() {
  pinMode(leftM1, OUTPUT);
  pinMode(rightM2, OUTPUT);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  initialize_serialcontrol();
}

void initialize_serialcontrol()
{
  Serial.begin(9600);

  // Setup Bluetooth
  #ifdef BT
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  btSerial.begin(9600);

  btSerial.print("AT");
  delay(1000);
  btSerial.print("AT+NAMEPahviloota");
  delay(1000);
  btSerial.flush();
  #endif // BT
}

int streamAvailable()
{
  #ifdef BT
  return btSerial.available();
  #else
  return Serial.available();
  #endif // BT
}

char streamRead()
{
  #ifdef BT
  return btSerial.read();
  #else
  return Serial.read();
  #endif // BT
}

void streamWriteChar(char c)
{
  #ifdef BT
  btSerial.print(c);
  #else
  Serial.print(c);
  #endif // BT
}

void streamWriteInt(int i)
{
  #ifdef BT
  btSerial.print(i);
  #else
  Serial.print(i);
  #endif // BT
}

void streamWriteFloat(float f)
{
  #ifdef BT
  btSerial.print(f);
  #else
  Serial.print(f);
  #endif // BT
}

inline void setMotorL(int value)
{
  setMotor(E1, leftM1, value);
}

inline void setMotorR(int value)
{
  setMotor(E2, rightM2, value);
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

    // Direct control commands
    if (autopilot == 0) {
      if (cmd[0] == "ML") {
        int x = stringToInt(cmd[1]);
        setMotorL(x);
      }
      else if (cmd[0] == "MR") {
        int x = stringToInt(cmd[1]);
        setMotorR(x);
      }
      else if (cmd[0] == "M") {
        int left = stringToInt(cmd[1]);
        int right = stringToInt(cmd[2]);
        setMotorL(left);
        setMotorR(right);
      }
      else if (cmd[0] == "A") {
        autopilot = 1;
      }
    }
    // Autopilot commands
    else {
      if (cmd[0] == "A") {
        autopilot = 0;
      }
      else if (cmd[0] == "ST") {
        streamWriteChar('<');
        streamWriteChar('S');
        streamWriteChar('T');
        streamWriteChar(':');
        streamWriteInt(state);
        streamWriteChar('>');
      }
    }
}

void readStream() {
  while (streamAvailable() > 0) {
    c = streamRead();

    if (c == '<') {
      buffer = "";
      // Accumulate buffer until c == '>'
      while (c != '>') {
        if (streamAvailable() > 0) {
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
  // Read input from sensors.
  robot_input_t input;
  input.front_sensor = read_distance(frontTrigPin, frontEchoPin);
  input.left_sensor = read_distance(leftTrigPin, leftEchoPin);
  input.right_sensor = read_distance(rightTrigPin,rightEchoPin);

  if (autopilot == 1) {
    // Feed input to the state machine.
    robot_output_t output = think(input);

    // Control motors based on state machine output.
    setMotorL((int)(output.left * maxSpeed));
    setMotorR((int)(output.right * maxSpeed));
  }

  // Listen to commands.
  readStream();

  // Send sensor data.
  streamWriteChar('<');
  streamWriteChar('S');
  streamWriteChar(':');
  streamWriteFloat(input.front_sensor);
  streamWriteChar(':');
  streamWriteFloat(input.left_sensor);
  streamWriteChar(':');
  streamWriteFloat(input.right_sensor);
  streamWriteChar('>');

  delay(10);
}
