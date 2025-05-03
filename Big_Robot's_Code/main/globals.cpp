// globals.cpp
#include <Arduino.h>
#include "globals.h"

// PID tuning parameters for Motor 1
float kp1 = 80.0;  // Proportional gain
float ki1 = 10.0;  // Integral gain
float kd1 = 1.0;   // Derivative gain

// PID tuning parameters for Motor 2
float kp2 = 80.0;
float ki2 = 10.0;
float kd2 = 1.0;

float maxspeed = 130;  // Maximum motor speed (0-255)

// Constants for wheel movement calculations
extern const float stepsPerRevolution = 1400.0;  // Encoder steps per full wheel rotation
extern const float wheelDiameter = 6.8;          // Wheel diameter in cm
extern const float wheelCircumference = PI * wheelDiameter;  // Wheel circumference in cm