// encoder.h
#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

// External references to encoder counters
extern volatile int posi1;
extern volatile int posi2;

// Function declarations for encoder ISRs
void readEncoder1();
void readEncoder2();

#endif