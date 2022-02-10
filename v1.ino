
//////////////////////////////////////////////////
// Arduino Ultrasonic™ - Version 1              //
// Copyright 2022, Larry Studios                //
// Version 1.2.0                                //
// Last Updated 10 February 2022                //
//////////////////////////////////////////////////


#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myServo;

#define MF_1 4
#define MB_1 5
#define MF_2 6
#define MB_2 7

int state = 0;
int maxSensor = 20;
void setup() {
  Serial.begin(9600);
  myServo.attach(3);
  pinMode(MF_1, OUTPUT); pinMode(MB_1, OUTPUT); pinMode(MF_2, OUTPUT); pinMode(MF_2, OUTPUT);
  myServo.write(90);
}

void front()
{
  digitalWrite(MF_1, 1);
  digitalWrite(MB_1, 0);
  digitalWrite(MF_2, 1);
  digitalWrite(MB_2, 0);
}

void back()
{
  digitalWrite(MF_1, 1);
  digitalWrite(MB_1, 0);
  digitalWrite(MF_2, 1);
  digitalWrite(MB_2, 0);
}

void left()
{
  digitalWrite(MF_1, 1);
  digitalWrite(MB_1, 0);
  digitalWrite(MF_2, 0);
  digitalWrite(MB_2, 1);
}

void right()
{
  digitalWrite(MF_1, 0);
  digitalWrite(MB_1, 1);
  digitalWrite(MF_2, 1);
  digitalWrite(MB_2, 0);
}

void stop()
{
  digitalWrite(MF_1, 0);
  digitalWrite(MB_1, 0);
  digitalWrite(MF_2, 0);
  digitalWrite(MB_2, 0);
}

void loop()
{
  int Sonar = sonar.ping_cm();
  if (Sonar == 0) {
    Sonar = 1;
  }
  Serial.print(Sonar);
  Serial.print(" ");
  Serial.println(state);
  if (state == 0) {
    if (Sonar > maxSensor) {
      front();
    } else if (Sonar <= maxSensor) {
      stop();
      delay(500);
      myServo.write(0);
      delay(1000);
      state = 1;
    }
  }
  else if (state == 1) {
    if (Sonar >= maxSensor) {
      state = 2;
    } else {
      myServo.write(100);
      delay(1000);
      state = 3;
    }
  } else if (state = 2) {
    if (Sonar >= maxSensor) {
      back();
      delay(200);
      right();
      delay(200);
      myServo.write(90);
      state = 0;
    }
  } else if (state = 3) {
    if (Sonar >= maxSensor) {
      back();
      delay(200);
      left();
      delay(200);
      myServo.write(90);
      state = 0;
    } else {
      myServo.write(90);
      back();
      delay(1000);
      state = 0;
    }
  }
}
