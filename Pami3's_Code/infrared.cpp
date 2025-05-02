// infrared.cpp
#include <Arduino.h>
#include <ArduinoLog.h>
#include <NewPing.h>
#include "constants.h"
#include "globals.h"
#include "infrared.h"
#include "motor_control.h"
#include "sonar.h"

RobotState currentState = START;  // Définition ici uniquement

// Test the infrared sensor
void lineFollower()
{
    int leftSensorState = digitalRead(LEFT_SENSOR);   // 1 = black et 0 = white
    int rightSensorState = digitalRead(RIGHT_SENSOR); // 1 = black et 0 = white

    // Go forward if left and right sensors detects white
    if (!leftSensorState && !rightSensorState)
    {
        Log.notice("white white");
        currentState = GO;
    }

    // Turn right if left sensor detects black and right sensor detects white
    else if (leftSensorState && !rightSensorState)
    {
        Log.notice("black white");
        currentState = RIGHT;
    }

    // Turn left if left sensor detects white and right sensor detects black
    else if (!leftSensorState && rightSensorState)
    {
        Log.notice("white black");
        currentState = LEFT;
    }

    // Do nothing if left and right sensors detects black
    else
    {
        Log.notice("black black");
    }
}
