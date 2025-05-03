// encoder.cpp
#include "encoder.h"
#include <Arduino.h>
#include "constants.h"

// Encoder position counters (volatile for interrupt safety)
volatile int posi1 = 0;  // Tracks steps for Motor 1
volatile int posi2 = 0;  // Tracks steps for Motor 2

// Interrupt service routine for Motor 1 encoder
void readEncoder1() {
  int b = digitalRead(ENCB1);
  posi1 += (b > 0) ? 1 : -1;  // Increment/decrement based on encoder B state
}

// Interrupt service routine for Motor 2 encoder
void readEncoder2() {
  int c = digitalRead(ENCB2);
  posi2 += (c > 0) ? 1 : -1;
}