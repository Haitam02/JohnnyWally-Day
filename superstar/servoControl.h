#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Servo.h>

/**
 * @class ServoControl
 * @brief Controls the servo motor for auxiliary movements
 * 
 * Provides methods to control a servo motor for special
 * movements like the dance sequence
 */
class ServoControl {
public:
    /**
     * @brief Constructor for ServoControl
     * 
     * @param pin Arduino pin connected to the servo signal wire
     */
    ServoControl(int pin);
    
    /**
     * @brief Perform a sweeping motion with the servo
     * 
     * Moves the servo from 180 degrees to 0 degrees
     */
    void bougerMotor();
    
private:
    Servo servo; ///< Servo motor object
};

#endif
