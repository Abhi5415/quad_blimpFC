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

// ---- servo initialization ----
Servo Nservo;
Servo Eservo;
Servo Sservo;
Servo Wservo;
Servo Dropservo;

// ---- motor initialization ----

int nMotorPin = 10;
int eMotorPin = 11;
int sMotorPin = 12;
int wMotorPin = 13;

void throttleControl(int val)
{
  analogWrite(nMotorPin, val);
  analogWrite(eMotorPin, val);
  analogWrite(sMotorPin, val);
  analogWrite(wMotorPin, val);
}

void writeServo(int val, Servo s)
{
  val /= 10;
  val *= 10;
  s.write(val);
}

void setup()
{
  // ---- Reciever ----
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

  // ---- Motors ----
  pinMode(nMotorPin, OUTPUT);
  pinMode(eMotorPin, OUTPUT);
  pinMode(sMotorPin, OUTPUT);
  pinMode(wMotorPin, OUTPUT);

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

  throttleControl(map(throttle, 1088, 1888, 0, 255)); // all throttle controls
  if (rudder > 1495 || rudder < 1475)
  {
    rudder = map(rudder, 1485, 1888, 0, 90) + 90;
    Serial.println(rudder);
    writeServo(rudder, Nservo);
    writeServo(rudder, Eservo);
    writeServo(rudder, Wservo);
    writeServo(rudder, Sservo);
  }
  else
  {
    aileron = map(aileron, 1485, 1888, 0, 90) + 90;
    elevator = map(elevator, 1485, 1888, 0, 90) + 90;
    Serial.println(elevator);
    writeServo(aileron, Nservo);
    writeServo(aileron, Sservo);
    writeServo(elevator, Eservo);
    writeServo(elevator, Wservo);
  }

  if (drop > 1850)
  {
    writeServo(180, Dropservo);
  }
  else
  {
    writeServo(0, Dropservo);
  }
}