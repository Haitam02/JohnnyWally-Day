// motor_control.cpp
#include <Arduino.h>
#include <ArduinoLog.h>
#include <NewPing.h>
#include "constants.h"
#include "globals.h"
#include "infrared.h"
#include "motor_control.h"
#include "sonar.h"

// Initialize motor shield and motor objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1); // Motor 1 on M1 port
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2); // Motor 2 on M2 port

// Turn to the left
void turnLeft()
{
  leftMotor->run(RELEASE);
  rightMotor->run(FORWARD);
}

// Turn to the right
void turnRight()
{
  leftMotor->run(FORWARD);
  rightMotor->run(RELEASE);
}
