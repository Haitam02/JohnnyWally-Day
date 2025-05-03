#ifndef SENSOR_H
#define SENSOR_H

#include <NewPing.h>

/** 
 * @def TRIG_PIN
 * @brief Ultrasonic sensor trigger pin number
 */
#define TRIG_PIN 9

/** 
 * @def ECHO_PIN
 * @brief Ultrasonic sensor echo pin number
 */
#define ECHO_PIN 10

/** 
 * @def MAX_DISTANCE
 * @brief Maximum detection distance in centimeters for ultrasonic sensor
 */
#define MAX_DISTANCE 20  // Distance maximum pour les mesures

/** 
 * @def CAPTEUR_PIN8
 * @brief Left IR sensor pin number
 */
#define CAPTEUR_PIN8 8   // Capteur IR gauche

/** 
 * @def CAPTEUR_PIN7
 * @brief Right IR sensor pin number
 */
#define CAPTEUR_PIN7 7   // Capteur IR droit

/**
 * @class Sensor
 * @brief Manages all sensors on the robot
 * 
 * Handles ultrasonic distance sensor for obstacle detection
 * and IR sensors for line detection
 */
class Sensor {
public:
    /**
     * @brief Constructor for Sensor class
     * 
     * @param trigPin Ultrasonic sensor trigger pin
     * @param echoPin Ultrasonic sensor echo pin
     * @param maxDistance Maximum detection distance in cm
     * @param capteurGauche Left IR sensor pin
     * @param capteurDroit Right IR sensor pin
     */
    Sensor(int trigPin, int echoPin, int maxDistance, int capteurGauche, int capteurDroit);
    
    /**
     * @brief Detects if an obstacle is present
     * 
     * @return true if obstacle detected within MAX_DISTANCE
     * @return false if no obstacle detected
     */
    bool detectObstacle();
    
    /**
     * @brief Gets current distance to nearest object
     * 
     * @return int Distance in centimeters
     */
    int getDistance();
    
    /**
     * @brief Detects if left IR sensor sees a line
     * 
     * @return true if line detected
     * @return false if no line detected
     */
    bool detectLineLeft();
    
    /**
     * @brief Detects if right IR sensor sees a line
     * 
     * @return true if line detected
     * @return false if no line detected
     */
    bool detectLineRight();

private:
    NewPing sonar;  ///< Ultrasonic sensor object
    int pinGauche;  ///< Left IR sensor pin
    int pinDroit;   ///< Right IR sensor pin
};

#endif
