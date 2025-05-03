// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

// PID tuning parameters (extern for global access)
extern float kp1, ki1, kd1;
extern float kp2, ki2, kd2;
extern float maxspeed;

// Constants for wheel movement calculations
extern const float stepsPerRevolution;
extern const float wheelDiameter;
extern const float wheelCircumference;

#endif