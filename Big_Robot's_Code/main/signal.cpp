// signal.cpp
#include <Arduino.h>
#include <ArduinoLog.h>
#include "signal.h"
#include "constants.h"

// Global flag to enable/disable ultrasonic obstacle detection
bool ultrasonicsActive = true;  


void sendSignal() {
  digitalWrite(SIGNAL_PIN2, HIGH);  // Activate signal
  delay(50);                        // Hold signal for 50ms
  digitalWrite(SIGNAL_PIN2, LOW);   // Deactivate signal
  Log.notice("Signal sent to banner");
  delay(10000);                     // 10-second delay before next signal
}


bool sensorMesure() {  
  if (!ultrasonicsActive) {
    Log.trace("Ultrasonic detection disabled.");
    return false;  // Skip detection if ultrasonics are disabled
  }

  // Read digital input 
  if (digitalRead(SIGNAL_PIN) == HIGH) {
    Log.warning("Obstacle detected!");
    return true;  // Obstacle detected
  } else {
    Log.verbose("No obstacle detected.");
    return false;  // No obstacle
  }
}