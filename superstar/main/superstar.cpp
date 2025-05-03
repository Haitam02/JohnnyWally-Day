#include "superstar.h"
#include <Arduino.h>
#include <ArduinoLog.h>

/**
 * @brief Constructor implementation
 * 
 * Initializes the Superstar object with references to motor, sensor, 
 * and servo controllers. Sets initial state to RUN.
 * 
 * @param m Reference to Motor object
 * @param s Reference to Sensor object
 * @param sv Reference to ServoControl object
 */
Superstar::Superstar(Motor &m, Sensor &s, ServoControl &sv)
  : motor(m), sensor(s), servo(sv), currentState(RUN) {}

/**
 * @brief Main state machine implementation
 * 
 * Executes the appropriate behavior based on current state:
 * - RUN: Follow line and check for obstacles
 * - STOP: Stop motors, wait, then resume movement
 * - DANCE: Stop motors and perform servo movement
 */
void Superstar::run() {
  switch (currentState) {
    case RUN:
      suivreLigne();
      if (sensor.detectObstacle()) {
        Log.notice(F("Obstacle detected, changing state: RUN -> STOP" CR));
        currentState = STOP;
      }
      break;
    case STOP:
      Log.notice(F("Motors stopped due to obstacle" CR));
      motor.stop();
      delay(1000);
      Log.notice(F("Changing state: STOP -> RUN" CR));
      currentState = RUN;
      break;
    case DANCE:
      Log.notice(F("Starting dance sequence" CR));
      motor.stop();
      servo.bougerMotor();
      Log.notice(F("Dance sequence completed" CR));
      break;
  }
}

/**
 * @brief Line following algorithm implementation
 * 
 * Reads IR sensor values and controls motors to follow a line:
 * - If only right sensor detects a line: turn right
 * - If only left sensor detects a line: turn left
 * - If neither sensor detects a line: move forward
 */
void Superstar::suivreLigne() {
  bool ligneGauche = sensor.detectLineLeft();
  bool ligneDroite = sensor.detectLineRight();

  Log.verbose(F("Line sensors - Left: %T, Right: %T" CR), ligneGauche, ligneDroite);

  if (ligneDroite == 0 && ligneGauche == 1) {
    Log.verbose(F("Turning right" CR));
    motor.tournerDroite();
  } else if (ligneDroite == 1 && ligneGauche == 0) {
    Log.verbose(F("Turning left" CR));
    motor.tournerGauche();
  } else if (ligneDroite == 0 && ligneGauche == 0) {
    Log.verbose(F("Moving forward" CR));
    motor.avancer(55);
  }
}
