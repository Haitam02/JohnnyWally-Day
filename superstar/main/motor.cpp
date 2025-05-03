#include "motor.h"
#include <Arduino.h>
#include <ArduinoLog.h>

/**
 * @brief Constructor implementation
 * 
 * Initializes the Motor object with pointers to the left and right
 * DC motor objects from the motor shield
 * 
 * @param leftMotor Pointer to left DC motor
 * @param rightMotor Pointer to right DC motor
 */
Motor::Motor(Adafruit_DCMotor *leftMotor, Adafruit_DCMotor *rightMotor)
    : moteurGauche(leftMotor), moteurDroit(rightMotor) {}

/**
 * @brief Makes the robot move forward
 * 
 * Sets the speed of both motors and runs them in forward direction
 * 
 * @param speed Motor speed value (0-255)
 */
void Motor::avancer(int speed) {
    Log.notice(F("Motor: Moving forward at speed %d" CR), speed);
    
    moteurGauche->setSpeed(speed);
    moteurDroit->setSpeed(speed);
    moteurGauche->run(FORWARD);
    moteurDroit->run(FORWARD);
}

/**
 * @brief Makes the robot turn left
 * 
 * Stops the left motor and runs the right motor forward
 */
void Motor::tournerGauche() {
    Log.notice(F("Motor: Turning left" CR));
    
    moteurGauche->run(RELEASE);
    moteurDroit->run(FORWARD);
}

/**
 * @brief Makes the robot turn right
 * 
 * Stops the right motor and runs the left motor forward
 */
void Motor::tournerDroite() {
    Log.notice(F("Motor: Turning right" CR));
    
    moteurGauche->run(FORWARD);
    moteurDroit->run(RELEASE);
}

/**
 * @brief Stops both motors
 * 
 * Releases both motors to halt movement
 */
void Motor::stop() {
    Log.notice(F("Motor: Stopping all motors" CR));
    
    moteurGauche->run(RELEASE);
    moteurDroit->run(RELEASE);
}
