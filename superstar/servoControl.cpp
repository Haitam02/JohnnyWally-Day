#include "servoControl.h"
#include <Arduino.h>
#include <ArduinoLog.h>

/**
 * @brief Constructor implementation
 * 
 * Initializes the ServoControl object by attaching the servo
 * to the specified pin and setting it to 90 degrees (center position)
 * 
 * @param pin Arduino pin connected to the servo signal wire
 */
ServoControl::ServoControl(int pin) {
    Log.notice(F("Servo initialized on pin %d" CR), pin);
    
    servo.attach(pin);
    servo.write(90);
    Log.notice(F("Servo set to center position (90°)" CR));
}

/**
 * @brief Performs a sweeping motion with the servo
 * 
 * Moves the servo from 180 degrees to 0 degrees with a 
 * short delay between each position
 */
void ServoControl::bougerMotor() {
    Log.notice(F("Servo: Starting sweep from 180° to 0°" CR));
    
    for (int angle = 180; angle >= 0; angle--) {
        servo.write(angle);
        
        // Log every 45 degrees to reduce log output
        if (angle % 45 == 0) {
            Log.verbose(F("Servo position: %d°" CR), angle);
        }
        
        delay(10);
    }
    
    Log.notice(F("Servo: Sweep complete" CR));
}
