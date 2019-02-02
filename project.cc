#include <Servo.h>

// ---- Input Variable ----
int throttlePin = 13;
int rudderPin = 10;
int aileronPin = 12;
int elevatorPin = 11;
int dropPin = 10;

// ---- Vars ----
int throttle;
int rudder;
int aileron;
int elevator;
int drop;

int rudderVal;

// ---- servo initialization ----
Servo Nservo;
Servo Eservo;
Servo Sservo;
Servo Wservo;
Servo Dropservo;

void writeServo(int val, Servo s)
{
  val /= 10;
  val *= 10;
  s.write(val);
}

void setup()
{
  pinMode(throttlePin, INPUT);
  pinMode(rudderPin, INPUT);
  pinMode(aileronPin, INPUT);
  pinMode(elevatorPin, INPUT);
  pinMode(dropPin, INPUT);

  // ---- Servos ----
  Nservo.attach(1);
  Eservo.attach(2);
  Sservo.attach(3);
  Wservo.attach(4);
  Dropservo.attach(5);

  Serial.begin(9600);
}

void loop()
{
  // ---- reads all of the inputs ----
  throttle = pulseIn(throttlePin, HIGH);
  rudder = pulseIn(rudderPin, HIGH);
  aileron = pulseIn(aileronPin, HIGH);
  elevator = pulseIn(elevatorPin, HIGH);
  drop = pulseIn(dropPin, HIGH);

  // ---- mapping values ----

  throttle = map(throttle, 1088, 1888, 0, 255);
  if (rudder > 1495 || rudder < 1475)
  {
    rudderVal = map(rudder, 1485, 1888, 0, 90) + 90;
    Serial.println(rudderVal);
    writeServo(rudderVal, Nservo);
    writeServo(rudderVal, Eservo);
    writeServo(rudderVal, Wservo);
    writeServo(rudderVal, Sservo);
  }

  // throttle between 1088 and 1888
  // rudder center 1485 - left 1888 - right 1888
}