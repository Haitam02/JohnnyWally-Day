#include "servo_controller.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Signal detection variables
volatile int signalCount = 0;
unsigned long lastTrigger = 0;

// System state variables
int currentState = 0;

void setupServoController() {
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize PWM controller
  pwm.begin();
  pwm.setPWMFreq(60); // Set PWM frequency to 60Hz

  // Configure signal pin and interrupt
  pinMode(SIGNAL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_PIN), onSignalReceived, RISING);

  // Set initial servo positions
  setServoAngle(SERVO1, 120);
  setServoAngle(SERVO2, 120);
  setServoAngle(SERVO3, 120);
  setServoAngle(SERVO4, 120);
  setServoAngle(SERVO5, 0);
  setServoAngle(SERVO6, 50);
  setServoAngle(SERVO9, 100);
  setServoAngle(SERVO11, 125);
  setServoAngle(SERVO12, 125);
  setServoAngle(SERVO13, 75);
  setServoAngle(SERVO14, 75);
  setServoAngle(SERVO15, 75);
  setServoAngle(SERVO16, 75);
}

/**
 * Interrupt service routine for signal detection
 * Implements basic debouncing (500ms)
 */
void onSignalReceived() {
  unsigned long now = millis();
  if (now - lastTrigger > 500) { // Debounce check
    signalCount++;
    lastTrigger = now;
  }
}

/**
 * Sequence for part 1 of banner deployment
 * Controls servos 5,6,9,11,12
 */
void runPart1() {
  setServoAngle(SERVO9, 10);
  delay(5000);
  setServoAngle(SERVO11, 0);
  setServoAngle(SERVO6, 180);
  delay(1000);
  setServoAngle(SERVO9, 100);
  delay(200);
  setServoAngle(SERVO12, 0);
  setServoAngle(SERVO5, 180);
  delay(5000);
}

/**
 * Sequence for part 2 of banner deployment
 * Controls servos 3,4,5,6,9,11,12,13,15
 */
void runPart2() {
  setServoAngle(SERVO9, 10);
  delay(100);
  setServoAngle(SERVO13, 0);
  setServoAngle(SERVO4, 180);
  delay(1000);
  setServoAngle(SERVO13, 125);
  setServoAngle(SERVO4, 50);
  setServoAngle(SERVO12, 125);
  setServoAngle(SERVO5, 50);
  setServoAngle(SERVO11, 125);
  setServoAngle(SERVO6, 50);
  setServoAngle(SERVO9, 100);
  delay(500);
  setServoAngle(SERVO15, 0);
  setServoAngle(SERVO3, 170);
  delay(500);
  setServoAngle(SERVO13, 0);
  setServoAngle(SERVO4, 180);
  delay(500);
  setServoAngle(SERVO12, 0);
  setServoAngle(SERVO5, 180);
  delay(500);
  setServoAngle(SERVO11, 0);
  setServoAngle(SERVO6, 180);
  delay(5000);
}

/**
 * Sequence for part 3 of banner deployment (final sequence)
 * Controls servos 1,2,3,4,9,13,14,15,16
 */
void runPart3() {
  setServoAngle(SERVO9, 10);
  delay(100);
  setServoAngle(SERVO16, 125);
  setServoAngle(SERVO2, 50);
  setServoAngle(SERVO15, 125);
  setServoAngle(SERVO3, 30);
  setServoAngle(SERVO13, 125);
  setServoAngle(SERVO4, 50);
  delay(500);
  setServoAngle(SERVO16, 0);
  setServoAngle(SERVO2, 180);
  delay(500);
  setServoAngle(SERVO16, 125);
  setServoAngle(SERVO2, 50);
  setServoAngle(SERVO14, 0);
  setServoAngle(SERVO1, 180);
  delay(500);
  setServoAngle(SERVO15, 0);
  setServoAngle(SERVO3, 170);
  delay(500);
  setServoAngle(SERVO15, 125);
  setServoAngle(SERVO3, 50);
  setServoAngle(SERVO16, 0);
  setServoAngle(SERVO2, 180);
  delay(500);
  setServoAngle(SERVO9, 10);
  setServoAngle(SERVO13, 0);
  setServoAngle(SERVO4, 180);
  delay(500);
  setServoAngle(SERVO9, 100);
  setServoAngle(SERVO15, 0);
  setServoAngle(SERVO3, 170);
  delay(500);
}

/**
 * Sets servo to specified angle
 * @param servoNum PWM channel number (0-15)
 * @param angle Desired angle (0-180 degrees)
 */
void setServoAngle(uint8_t servoNum, uint8_t angle) {
  uint16_t pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(servoNum, 0, pulse);
}