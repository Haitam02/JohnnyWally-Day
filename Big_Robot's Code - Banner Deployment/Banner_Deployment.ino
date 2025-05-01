#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

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
volatile int signalCount = 0;       // Counts received signals (currently not used)
unsigned long lastTrigger = 0;      // Last signal detection time (for debouncing)

// System state variables
int currentState = 0;     // 0 = idle, 1 = part 1, 2 = part 2, 3 = part 3
bool lastSignal = LOW;    // Previous signal state (for edge detection)

void setup() {
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize PWM controller
  pwm.begin();
  pwm.setPWMFreq(60); // Set PWM frequency to 60Hz
  
  // Start serial communication for debugging
  Serial.begin(9600);

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

// Signal processing variables
unsigned long lastSignalTime = 0;    // Last valid signal reception time
bool signalReceived = false;         // Signal received flag
const unsigned long resetDelay = 5000; // 5 second reset delay after sequence

void loop() {
  bool signal = digitalRead(SIGNAL_PIN);

  // Ignore signals during reset period (5 seconds after last signal)
  if (millis() - lastSignalTime < resetDelay) {
    return; // Wait during reset period
  }

  // Detect rising edge (LOW -> HIGH transition)
  if (signal == HIGH && lastSignal == LOW) {
    lastSignalTime = millis(); // Update last signal time
    currentState++; // Advance to next state
    Serial.print("Signal received. Transitioning to state ");
    Serial.println(currentState);

    delay(1000); // Small debounce delay

    // Execute appropriate sequence based on current state
    if (currentState == 1) {
      delay(1000); // Initial delay before starting
    } else if (currentState == 2) {
      runPart1(); // Execute part 1 sequence
    } else if (currentState == 3) {
      runPart2(); // Execute part 2 sequence
    } else if (currentState == 4) {
      runPart3(); // Execute part 3 sequence
      while (true); // Stop program after final sequence
    }
  }

  // Update previous signal state
  lastSignal = signal;
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