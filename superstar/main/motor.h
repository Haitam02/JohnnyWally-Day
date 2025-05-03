#ifndef MOTOR_H
#define MOTOR_H

#include <Adafruit_MotorShield.h>

/**
 * @class Motor
 * @brief Controls the robot's movement via two DC motors
 * 
 * Provides methods for basic movement operations including
 * moving forward, turning and stopping
 */
class Motor {
public:
    /**
     * @brief Constructor for Motor class
     * 
     * @param leftMotor Pointer to the left DC motor object
     * @param rightMotor Pointer to the right DC motor object
     */
    Motor(Adafruit_DCMotor *leftMotor, Adafruit_DCMotor *rightMotor);
    
    /**
     * @brief Makes the robot move forward
     * 
     * @param speed Motor speed value (0-255)
     */
    void avancer(int speed);
    
    /**
     * @brief Makes the robot turn left
     * 
     * Stops the left motor and runs the right motor forward
     */
    void tournerGauche();
    
    /**
     * @brief Makes the robot turn right
     * 
     * Stops the right motor and runs the left motor forward
     */
    void tournerDroite();
    
    /**
     * @brief Stops both motors
     * 
     * Releases both motors to halt movement
     */
    void stop();

private:
    Adafruit_DCMotor *moteurGauche; ///< Pointer to left motor object
    Adafruit_DCMotor *moteurDroit;  ///< Pointer to right motor object
};

#endif
