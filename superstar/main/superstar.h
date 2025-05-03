#ifndef SUPERSTAR_H
#define SUPERSTAR_H

#include "motor.h"
#include "sensor.h"
#include "servoControl.h"

/**
 * @enum State
 * @brief Defines the possible states of the robot
 * 
 * @value RUN - Normal line following operation
 * @value STOP - Temporary stop state (when obstacle detected)
 * @value DANCE - Special movement sequence with servo
 */
enum State {
    RUN,
    STOP,
    DANCE
};

/**
 * @class Superstar
 * @brief Main controller class for the robot
 * 
 * Coordinates the behavior of motors, sensors, and servo
 * based on the current state and sensor inputs
 */
class Superstar {
public:
    /**
     * @brief Constructor for Superstar
     * 
     * @param motor Reference to Motor object for movement control
     * @param sensor Reference to Sensor object for environmental detection
     * @param servo Reference to ServoControl object for servo movements
     */
    Superstar(Motor &motor, Sensor &sensor, ServoControl &servo);
    
    /**
     * @brief Main function to execute robot behavior
     * 
     * Implements the state machine and coordinates all robot functions
     */
    void run();

private:
    Motor &motor;       ///< Reference to motor controller
    Sensor &sensor;     ///< Reference to sensor controller
    ServoControl &servo; ///< Reference to servo controller
    State currentState; ///< Current state of the robot
    
    /**
     * @brief Line following function
     * 
     * Reads IR sensors and adjusts motor direction to follow a line
     */
    void suivreLigne();
};

#endif
