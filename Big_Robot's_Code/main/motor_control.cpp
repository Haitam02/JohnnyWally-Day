// motor_control.cpp
#include <Arduino.h>
#include <ArduinoLog.h>
#include <Adafruit_MotorShield.h>
#include "motor_control.h"
#include "encoder.h"

// Initialize motor shield and motor objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);  // Motor 1 on M1 port
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);  // Motor 2 on M2 port

// Stops both motors and releases them
void Stop() {
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  Log.notice("Motors stopped.");
}

// Rotates the robot for a specified duration (left or right)
void rotate(int durationMs, bool toLeft) {
  if (toLeft) {
    myMotor1->run(BACKWARD);
    myMotor2->run(FORWARD);
  } else {
    myMotor1->run(FORWARD);
    myMotor2->run(BACKWARD);
  }
  delay(durationMs);
  Stop();
  posi1 = 0;  // Reset encoder counts
  posi2 = 0;
  Log.notice("Rotation complete. Encoders reset.");
  delay(500);  // Brief pause after rotation
}

// Updates motor speed using PID control
void updateMotorPID(Adafruit_DCMotor *motor, float error, float kp, float ki, float kd, float maxspeed) {
  static float integral = 0.0;  // Accumulated error over time
  static float lastError = 0.0; // Previous error for derivative term

  integral += error;
  float derivative = error - lastError;
  float output = kp * error + ki * integral + kd * derivative;
  int adjustedSpeed = constrain(abs((int)output), 0, maxspeed);
  motor->setSpeed(adjustedSpeed);
  lastError = error;
}