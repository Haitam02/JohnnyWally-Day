// motor_control.h
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Adafruit_MotorShield.h>

// External references to motor shield and motor objects
extern Adafruit_MotorShield AFMS;
extern Adafruit_DCMotor *myMotor1;
extern Adafruit_DCMotor *myMotor2;

// Function declarations
void Stop();  // Stops both motors
void rotate(int durationMs, bool toLeft);  // Rotates robot for a given duration
void updateMotorPID(Adafruit_DCMotor *motor, float error, float kp, float ki, float kd, float maxspeed);  // PID speed adjustment

#endif