#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Servo channel definitions (PWM controller channels)
// Note: Channels are numbered to match physical board numbering (1-16)
// but use 0-15 addressing for the PWM controller
#define SERVO1 0   // Physical servo 1
#define SERVO2 1   // Physical servo 2
#define SERVO3 2   // Physical servo 3
#define SERVO4 3   // Physical servo 4
#define SERVO5 4   // Physical servo 5
#define SERVO6 5   // Physical servo 6
#define SERVO9 8   // Physical servo 9 
#define SERVO11 10 // Physical servo 11
#define SERVO12 11 // Physical servo 12
#define SERVO13 12 // Physical servo 13
#define SERVO14 13 // Physical servo 14
#define SERVO15 14 // Physical servo 15
#define SERVO16 15 // Physical servo 16

// Servo pulse width limits (in microseconds)
#define SERVOMIN 150 // Minimum pulse length
#define SERVOMAX 600 // Maximum pulse length

// Signal pin from main robot controller
#define SIGNAL_PIN 2  // Interrupt pin for receiving signals

// Signal detection variables
extern volatile int signalCount;       // Counts received signals (currently not used)
extern unsigned long lastTrigger;      // Last signal detection time (for debouncing)

// System state variables
extern int currentState;     // 0 = idle, 1 = part 1, 2 = part 2, 3 = part 3

// Function declarations
void setupServoController();
void setServoAngle(uint8_t servoNum, uint8_t angle);
void runPart1();
void runPart2();
void runPart3();
void onSignalReceived();

#endif