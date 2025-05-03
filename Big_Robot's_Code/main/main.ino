// main.ino
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <Adafruit_MotorShield.h>
#include <ArduinoLog.h>

#include "constants.h"
#include "motor_control.h"
#include "encoder.h"
#include "pid_control.h"
#include "sequence.h"
#include "signal.h"
#include "globals.h"



// LCD display object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin and state variables
const int REED_PIN = 5;         // Magnetic reed switch pin
bool start = false;             // Start flag
bool endSequenceExecuted = false;    // Completion flag for final sequence
bool initialSequenceCompleted = false;  // Completion flag for initial sequence
unsigned long startTime;        // Timestamp for timing operations

void setup() {
  Serial.begin(9600);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.notice("Robot initialized. Waiting for start signal...");

  AFMS.begin();  // Initialize motor shield

  // Configure pins
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(SIGNAL_PIN2, OUTPUT);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  // Attach encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA2), readEncoder2, RISING);
}

void loop() {
  int proximity = digitalRead(REED_PIN);  // Check switch

  if (proximity == LOW) {
    Log.notice("Magnet detected. Waiting...");
  } else {
    if (!start) {
      startTime = millis();  // Record start time
      start = true;
      Log.notice("Start signal received. Beginning operations...");
    }

    int switchState = digitalRead(SWITCH_PIN);

    // Execute initial sequence if not done
    if (!initialSequenceCompleted) {
      executeInitialSequence(switchState == LOW);
      initialSequenceCompleted = true;
    }

    // Execute final PID sequence after 95 seconds
    if (!endSequenceExecuted && millis() - startTime >= 95000) {
      Log.notice("95 seconds elapsed. Executing final PID sequence.");
      pid(60);  // Move forward 60 cm
      endSequenceExecuted = true;
      ultrasonicsActive = true;
      Stop();
      while (true);  // Halt after completion
    } else if (!endSequenceExecuted) {
      Stop();  // Ensure motors are stopped
    }
  }
}