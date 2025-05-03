// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

// Encoder's pins
extern const int encoder1PinA; // Before it was 18 but changed based on Soraya's excel;
extern const int encoder2PinA;

// Encoder's variable
extern volatile int encoder1Position;

// Servo's pin
extern const int startPosition;

// Start rope's pin
extern const int startRope;

// State of the FSM
enum RobotState
{
    START,
    GO,
    STOP,
    BACK,
    LEFT,
    RIGHT,
    OBSTACLE_DETECTED
};

extern RobotState currentState;

#endif