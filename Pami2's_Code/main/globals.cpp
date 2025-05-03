// globals.cpp
#include <Arduino.h>
#include "globals.h"

// Encoder's pins
const int encoder1PinA = 3;
const int encoder2PinA = 2;

// Encoder's variable
volatile int encoder1Position = 0;

// Servo's pin
const int startPosition = 180;

// Start rope's pin
const int startRope = 11;