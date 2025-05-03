#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <ArduinoLog.h>
#include "sensor.h"
#include "motor.h"
#include "servoControl.h"
#include "superstar.h"

/**
 * @brief Main motor shield object for controlling motors
 */
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

/**
 * @brief Pointer to left DC motor (connected to M1 on shield)
 */
Adafruit_DCMotor *moteurGauche = AFMS.getMotor(1);

/**
 * @brief Pointer to right DC motor (connected to M2 on shield)
 */
Adafruit_DCMotor *moteurDroit = AFMS.getMotor(2);

/**
 * @brief Sensor controller for ultrasonic and IR sensors
 */
Sensor sensor(TRIG_PIN, ECHO_PIN, MAX_DISTANCE, CAPTEUR_PIN7, CAPTEUR_PIN8);

/**
 * @brief Motor controller for robot movement
 */
Motor motor(moteurGauche, moteurDroit);

/**
 * @brief Servo controller for auxiliary movements
 */
ServoControl servo(9);

/**
 * @brief Main robot controller that coordinates all functions
 */
Superstar superstar(motor, sensor, servo);

/**
 * @brief Timestamp when the program started running
 */
unsigned long startMillis;

/**
 * @brief Current timestamp for timing calculations
 */
unsigned long currentMillis; 

/**
 * @brief Runtime in seconds - used for logging
 */
unsigned long runtimeSeconds = 0;

/**
 * @brief Last time runtime was logged
 */
unsigned long lastRuntimeUpdate = 0;

/**
 * @brief Arduino setup function - runs once at startup
 * 
 * Initializes motor shield, serial communication, and start time
 */
void setup() {
    // Initialize Serial with higher baud rate for better log performance
    Serial.begin(115200);
    
    // Initialize ArduinoLog
    // Log level: LOG_LEVEL_VERBOSE (most detailed) to LOG_LEVEL_FATAL (least detailed)
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    
    Log.notice(F("=======================================" CR));
    Log.notice(F("        SUPERSTAR ROBOT STARTUP       " CR));
    Log.notice(F("=======================================" CR));
    
    Log.notice(F("Initializing motor shield..." CR));
    AFMS.begin();
    
    Log.notice(F("All components initialized" CR));
    Log.notice(F("Runtime limit: 15 seconds" CR));
    Log.notice(F("=======================================" CR));
    
    startMillis = millis();
    lastRuntimeUpdate = startMillis;
}

/**
 * @brief Arduino main loop - runs continuously
 * 
 * Runs the robot's main functionality for 15 seconds,
 * then stops all motors. This time-limited operation
 * prevents the robot from running indefinitely.
 */
void loop() {
    currentMillis = millis();
    
    // Log runtime every second
    if (currentMillis - lastRuntimeUpdate >= 1000) {
        runtimeSeconds++;
        lastRuntimeUpdate = currentMillis;
        Log.verbose(F("Runtime: %l seconds elapsed" CR), runtimeSeconds);
        
        // Log remaining time
        int remainingTime = 15 - runtimeSeconds;
        if (remainingTime > 0) {
            Log.verbose(F("Remaining time: %d seconds" CR), remainingTime);
        }
    }
    
    if(currentMillis - startMillis < 15000){
        superstar.run();
    } else {
        if (currentMillis - startMillis < 15100) {
            // Only print shutdown message once
            Log.notice(F("=======================================" CR));
            Log.notice(F("Runtime limit reached (15s)" CR));
            Log.notice(F("Shutting down motors" CR));
            Log.notice(F("=======================================" CR));
        }
        moteurGauche->run(RELEASE);
        moteurDroit->run(RELEASE);
    }
}
