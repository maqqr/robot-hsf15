// Using single ultrasound distance sensor;
// Go forward and stay stile when there's an obstacle in front.
int E1 = 4;
int vasenM1 = 5; //vasen
int E2 = 7;
int oikeaM2 = 6; //oikea

int frontTrigPin = 13;
int frontEchoPin = 12;

int leftTrigPin = 11;
int leftEchoPin = 10;

int rightTrigPin = 9;
int rightEchoPin = 8;

int motorValRight;
int motorValLeft;
int distanceFront;
int distanceLeft;
int distanceRight;
int initialSpeed = 255;
int maxSpeed = 255;
int turnSpeed = 255;

int distanceToStop = 20;


int turningSteps = 0; // plus arvot on oikea käännös ja minus on vasen käännös
int defaultTurningSteps = 8;

void setup()
{
  // Motor shield
  // http://www.dfrobot.com/wiki/index.php?title=Arduino_Motor_Shield_(L298N)_(SKU:DRI0009)
  pinMode(vasenM1, OUTPUT);
  pinMode(oikeaM2, OUTPUT);

  // Distance sensor
  // http://www.micropik.com/PDF/HCSR04.pdf
  Serial.begin (9600);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  motorValRight = initialSpeed;
  motorValLeft = initialSpeed;
}

// Calculate current distance from obstacle
float current_distance(int trig,int echo){
  long duration;
  float distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2.0) / 29.1;

  return distance;
}

void nextMove() {
  
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);

  analogWrite(vasenM1, motorValRight);
  analogWrite(oikeaM2, motorValLeft);

  Serial.print("Left: ");
  Serial.print(motorValLeft);
  Serial.print("Right: ");
  Serial.println(motorValRight); 
}

void printLog() {
   
  Serial.print("Front: ");
  Serial.print( distanceFront);
  Serial.print(" Left: ");
  Serial.print(distanceLeft);
  Serial.print(" Right: ");
  Serial.println(distanceRight);
}

void updateDistance() {
  distanceFront = current_distance(frontTrigPin,frontEchoPin);
  distanceLeft = current_distance(leftTrigPin,leftEchoPin);
  distanceRight = current_distance(rightTrigPin,rightEchoPin);
  
  printLog();
}

void processTurn () {
  if(turningSteps > 0 ){
     turningSteps--;
     motorValLeft = turnSpeed;
  }
  else {
     turningSteps++; 
     motorValRight = turnSpeed;
  }
  
}

void process(){
  
  if(turningSteps != 0) {
    processTurn();
    return;  
  }
  
  if (distanceFront < distanceToStop){
    motorValRight = 0;
    motorValLeft = 0;
    if(distanceRight > 30) {
      // turn right
      turningSteps = defaultTurningSteps;
    }
    else if (distanceLeft > 30) {
      // turn left
      turningSteps = -defaultTurningSteps;
    }
    else {
      // advance a lil forward
      motorValLeft = 255;
      motorValRight = 255;
    }
    
  } else {
    motorValLeft = maxSpeed;
    motorValRight = maxSpeed;
  }
}

void loop()
{
  updateDistance();
  
  process();
  
  nextMove();
  
  delay(250);
}

