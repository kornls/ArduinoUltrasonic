
//////////////////////////////////////////////////
// Arduino Ultrasonic™ - Version 2              //
// Copyright 2022, Larry Studios                //
// Parts of this code are generated by mBlock 5 //
// Version 2.0.0 Beta 2                         //
// Last Updated 10 February 2022                //
//////////////////////////////////////////////////



///////////////////////////////////
//            PART 1             //
///////////////////////////////////


#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

float Status = 0;
float Loop = 0;

Servo servo_3;

void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void _loop() {
}


///////////////////////////////////
//            PART 2             //
///////////////////////////////////

#include <NewPing.h>
#include <Servo.h>
#define TRIGGER_PIN  12  // ขา Trig Ultra
#define ECHO_PIN     11  // ขา Echo Ultra
#define MAX_DISTANCE 200 // ระยะการมองเห็น Ultra
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;
#define MF_1 4 // ขาควบคุม มอเตอร์
#define MB_1 5
#define MF_2 6
#define MB_2 7
int state = 0;
int maxSensor = 20; // ตั้งระยะการมองเห็นหุ่นยนต์ 20cm
void setup() {
  pinMode(7,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  servo_3.attach(3);
  // Back Wheels
  analogWrite(7,200);
  analogWrite(5,200);
  _delay(5);
  analogWrite(7,0);
  analogWrite(5,0);
  _delay(1);
  // Front Wheels
  analogWrite(6,200);
  analogWrite(4,200);
  _delay(5);
  analogWrite(6,0);
  analogWrite(4,0);
  _delay(1);
  // Spin
  servo_3.write(90);
  _delay(1);
  servo_3.write(50);
  _delay(1);
  _loop();
  
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(MF_1, OUTPUT); pinMode(MB_1, OUTPUT); pinMode(MF_2, OUTPUT); pinMode(MB_2, OUTPUT);
  myservo.write(90);// Servo หมุน 90 องศา
}
void front() // เดินหน้า
{
  digitalWrite(MF_1, 1);
  digitalWrite(MB_1, 0);
  digitalWrite(MF_2, 1);
  digitalWrite(MB_2, 0);
}
void back() //ถอยหลัง
{
  digitalWrite(MF_1, 0);
  digitalWrite(MB_1, 1);
  digitalWrite(MF_2, 0);
  digitalWrite(MB_2, 1);
}
void left() //เลี้ยวซ้าย
{
  digitalWrite(MF_1, 1);
  digitalWrite(MB_1, 0);
  digitalWrite(MF_2, 0);
  digitalWrite(MB_2, 1);
}
void right() // เลี้ยวขวา
{
  digitalWrite(MF_1, 0);
  digitalWrite(MB_1, 1);
  digitalWrite(MF_2, 1);
  digitalWrite(MB_2, 0);
}
void stop() // หยุด
{
  digitalWrite(MF_1, 0);
  digitalWrite(MB_1, 0);
  digitalWrite(MF_2, 0);
  digitalWrite(MB_2, 0);
}

void loop() {
  int Sonar = sonar.ping_cm();
  if (Sonar == 0) {
    Sonar = 1;
  }
  Serial.print(Sonar);
  Serial.print(" ");
  Serial.println(state);
  if (state == 0) {
    if (Sonar > maxSensor) { //20
      front();
    }
    else if (Sonar <= maxSensor) {
      stop();
      delay(500);
      myservo.write(0);
      delay(1000);
      state = 1;
    }
  }
  else if (state == 1) {
    if (Sonar >= maxSensor) {
      state = 2;
    }
    else {
      myservo.write(180);
      delay(1000);
      state = 3;
    }
  }
  else if (state == 2) {
    if (Sonar >= maxSensor) {
      back();
      delay(200);
      right();
      delay(200);
      myservo.write(90);
      state = 0;
    }
  }
  else if (state == 3) {
    if (Sonar >= maxSensor) {
      back();
      delay(200);
      left();
      delay(200);
      myservo.write(90);
      state = 0;
    } else {
      myservo.write(90);
      back();
      delay(1000);
      state = 0;
    }
  }
}
