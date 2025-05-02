#include "servo_controller.h"

// Signal processing variables
unsigned long lastSignalTime = 0;    // Last valid signal reception time
bool signalReceived = false;         // Signal received flag
const unsigned long resetDelay = 5000; // 5 second reset delay after sequence
bool lastSignal = LOW;    // Previous signal state (for edge detection)

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Initialize servo controller
  setupServoController();
}

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