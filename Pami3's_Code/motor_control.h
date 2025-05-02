// motor_control.h
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Adafruit_MotorShield.h>

// External references to motor shield and motor objects
extern Adafruit_MotorShield AFMS;
extern Adafruit_DCMotor *leftMotor;
extern Adafruit_DCMotor *rightMotor;

// Function declarations
void turnLeft();  // Turn to the left
void turnRight(); // Turn to the right

#endif