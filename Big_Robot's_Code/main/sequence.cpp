// sequence.cpp
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoLog.h>
#include "sequence.h"
#include "signal.h"
#include "pid_control.h"
#include "motor_control.h"
#include "constants.h"

extern LiquidCrystal_I2C lcd;
extern bool ultrasonicsActive;

void executeInitialSequence(bool isBlueZone) {
  if (isBlueZone) {
    Log.notice("Blue zone detected. Executing sequence...");
  } else {
    Log.notice("Orange zone detected. Executing sequence...");
  }

  ultrasonicsActive = false;
  lcd.print("Score : 20");
  delay(2000);

  Log.notice("Signal 1");
  sendSignal();
  pid(isBlueZone ? 14.0 : -14.0);
  Stop();
  delay(100);

  Log.notice("Signal 2");
  sendSignal();
  pid(isBlueZone ? 14.0 : -14.0);
  Stop();
  delay(100);

  Log.notice("Signal 3");
  sendSignal();
  rotate(isBlueZone ? 1100 : 1350, true);

  pid(isBlueZone ? 115.0 : 100.0);
  Stop();

}
