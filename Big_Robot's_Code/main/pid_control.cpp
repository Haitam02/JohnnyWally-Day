// pid_control.cpp
#include <Arduino.h>
#include <ArduinoLog.h>
#include "pid_control.h"
#include "motor_control.h"
#include "encoder.h"
#include "signal.h"
#include "constants.h"
#include "globals.h"

void pid(float target) {
  posi1 = 0;  // Reset encoder position for Motor 1
  posi2 = 0;  // Reset encoder position for Motor 2
  Log.notice("Starting PID to target %.2f cm", target);

  float currentDistance1 = 0;  // Current distance traveled by Motor 1 (cm)
  float currentDistance2 = 0;  // Current distance traveled by Motor 2 (cm)

  // Loop until both motors reach the target distance
  while (abs(currentDistance1) <= abs(target) || abs(currentDistance2) <= abs(target)) {
    // Calculate distance using encoder steps and wheel circumference
    currentDistance1 = (posi1 / stepsPerRevolution) * wheelCircumference;
    currentDistance2 = (posi2 / stepsPerRevolution) * wheelCircumference;
    Log.verbose("Distances - Motor1: %.2f, Motor2: %.2f", currentDistance1, currentDistance2);

    // Compute error (difference between target and current position)
    float error1 = target > 0 ? target - currentDistance1 : -target - currentDistance1;
    float error2 = target > 0 ? target - currentDistance2 : -target - currentDistance2;

    // Set motor direction based on target sign (forward/backward)
    if (target > 0) {
      myMotor1->run(FORWARD);
      myMotor2->run(FORWARD);
    } else {
      myMotor1->run(BACKWARD);
      myMotor2->run(BACKWARD);
    }

    // Adjust speeds to minimize error difference between motors
    int adjustedSpeed1 = maxspeed;
    int adjustedSpeed2 = maxspeed;

    if (abs(error1 - error2) > 0) {
      adjustedSpeed1 = (error1 > error2) ? maxspeed * 0.8 : maxspeed * 0.9;
      adjustedSpeed2 = (error1 > error2) ? maxspeed * 0.9 : maxspeed * 0.85;
    } else {
      adjustedSpeed1 = adjustedSpeed2 = maxspeed * 0.8;
    }

    // Apply PID control to each motor
    updateMotorPID(myMotor1, error1, kp1, ki1, kd1, adjustedSpeed1);
    updateMotorPID(myMotor2, error2, kp2, ki2, kd2, adjustedSpeed2);

    delay(100);  // Small delay to avoid overwhelming the system

    // Stop if an obstacle is detected
    if (sensorMesure()) {
      Stop();
      delay(6000);  // Wait 6 seconds before resuming
    }
  }

  Stop();
  Log.notice("Target %.2f cm reached.", target);
}