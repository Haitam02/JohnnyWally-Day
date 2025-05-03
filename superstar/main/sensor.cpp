#include "sensor.h"
#include <Arduino.h>
#include <ArduinoLog.h>

/**
 * @brief Constructor implementation
 * 
 * Initializes the Sensor object with ultrasonic and IR sensor pins.
 * Sets up IR sensor pins as inputs.
 * 
 * @param trigPin Ultrasonic sensor trigger pin
 * @param echoPin Ultrasonic sensor echo pin
 * @param maxDistance Maximum detection distance in cm
 * @param capteurGauche Left IR sensor pin
 * @param capteurDroit Right IR sensor pin
 */
Sensor::Sensor(int trigPin, int echoPin, int maxDistance, int capteurGauche, int capteurDroit)
    : sonar(trigPin, echoPin, maxDistance), pinGauche(capteurGauche), pinDroit(capteurDroit) {
    pinMode(pinGauche, INPUT);
    pinMode(pinDroit, INPUT);
    Log.notice(F("Sensors initialized: US Trig=%d, Echo=%d, MaxDist=%d, IR Left=%d, Right=%d" CR), 
               trigPin, echoPin, maxDistance, capteurGauche, capteurDroit);
}

/**
 * @brief Detects if an obstacle is present
 * 
 * Uses ultrasonic sensor to check if an object is within MAX_DISTANCE.
 * Outputs detection status to Serial monitor.
 * 
 * @return true if obstacle detected within MAX_DISTANCE
 * @return false if no obstacle detected or too far
 */
bool Sensor::detectObstacle() {
    int distance = sonar.ping_cm();
    if (distance > 0 && distance < MAX_DISTANCE) {
        Log.warning(F("OBSTACLE DETECTED at %d cm" CR), distance);
        return true;
    }
    return false;
}

/**
 * @brief Gets current distance to nearest object
 * 
 * @return int Distance in centimeters from ultrasonic sensor
 */
int Sensor::getDistance() {
    int distance = sonar.ping_cm();
    Log.verbose(F("Distance measurement: %d cm" CR), distance);
    return distance;
}

/**
 * @brief Detects if left IR sensor sees a line
 * 
 * @return true if line detected (digital HIGH)
 * @return false if no line detected (digital LOW)
 */
bool Sensor::detectLineLeft() {
    return digitalRead(pinGauche);
}

/**
 * @brief Detects if right IR sensor sees a line
 * 
 * @return true if line detected (digital HIGH)
 * @return false if no line detected (digital LOW)
 */
bool Sensor::detectLineRight() {
    return digitalRead(pinDroit);
}
