// Using single ultrasound distance sensor;
// Go forward and stay stile when there's an obstacle in front.
int E1 = 4;
int M1 = 5;
int E2 = 7;
int M2 = 6;
int trigPin = 13;
int echoPin = 12;

int motorVal;
int distance;

void setup()
{
  // Motor shield
  // http://www.dfrobot.com/wiki/index.php?title=Arduino_Motor_Shield_(L298N)_(SKU:DRI0009)
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  // Distance sensor
  // http://www.micropik.com/PDF/HCSR04.pdf
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motorVal = 255;
}

// Calculate current distance from obstacle
float current_distance(){
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2.0) / 29.1;

  return distance;
}

void loop()
{
  distance = current_distance();

  if (distance < 30){
    motorVal = 0;
  } else {
    motorVal = 255;
  }

  delay(100);

  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);

  analogWrite(M1, motorVal);
  analogWrite(M2, motorVal);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm - ");
  Serial.print("setting motorVal to ");
  Serial.println(motorVal);
}
