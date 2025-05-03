// sonar.cpp
#include <Arduino.h>
#include <ArduinoLog.h>
#include <NewPing.h>
#include "constants.h"
#include "globals.h"
#include "infrared.h"
#include "motor_control.h"
#include "sonar.h"

unsigned int distance;
unsigned int distance_left;

NewPing sonar(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);
NewPing sonar_left(TRIG_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);

bool checkObstacle()
{
  // Measure the distance with the right sensor
  distance = sonar.ping_cm();
  // Measure the distance with the left sensor
  distance_left = sonar_left.ping_cm();

  // If one of the distances is non-zero and less than the threshold
  if ((distance > 0 && distance <= MAX_DISTANCE) ||
      (distance_left > 0 && distance_left <= MAX_DISTANCE))
  {
    Log.notice("Obstacle detected! Distance right:");
    Log.notice("distance = %d\n", distance);
    Log.notice(" cm, Left distance: ");
    Log.notice("distance_left = %d\n", distance_left);
    return true;
  }
  return false;
}
