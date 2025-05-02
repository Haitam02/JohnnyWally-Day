#include <Wire.h>
#include <Arduino.h>
#include <ArduinoLog.h>
#include <Adafruit_MotorShield.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>

#include "constants.h"
#include "globals.h"
#include "infrared.h"
#include "motor_control.h"
#include "sonar.h"
Servo myServo;

long temps;
unsigned long startMillis;
unsigned long currentMillis;
bool start = false;

void setup()
{
    // Initialize the Shield
    AFMS.begin();
    // Set the initial speed of the motors (values between 0 and 255)
    leftMotor->setSpeed(90);
    rightMotor->setSpeed(90);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    pinMode(LEFT_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);

    pinMode(encoder1PinA, INPUT);
    pinMode(encoder2PinA, INPUT);

    myServo.attach(6);
    myServo.write(startPosition);

    pinMode(startRope, INPUT_PULLUP);

    Log.notice("Start program...");
}

void loop()
{

    int rope = digitalRead(startRope);
    // Test if the rope is closed or not.
    // Wait until the rope is open to start.
    if (rope == LOW)
    {
        Log.notice("Switch Closed");
    }
    else
    {
        if (start == false)
        {
            startMillis = millis();
            start = true;
        }
        currentMillis = millis();
        if (currentMillis - startMillis >= 92000)
        { // Chek the life time to stop after 92 seconds
            currentState = STOP;
        }
        if (checkObstacle())
        {
            currentState = OBSTACLE_DETECTED;
        }
        else
        {
            switch (currentState)
            {

            // Wait 89 seconds before the start of the pami
            case START:
                delay(85000);
                leftMotor->run(FORWARD);
                rightMotor->run(FORWARD);
                lineFollower();
                break;

            // Go forward
            case GO:
                leftMotor->run(FORWARD);
                rightMotor->run(FORWARD);
                lineFollower();
                break;

            // Go backward
            case BACK:
                leftMotor->run(BACKWARD);
                rightMotor->run(BACKWARD);
                lineFollower();
                break;

            // Stop the pami and move the servo
            case STOP:
                leftMotor->run(RELEASE);
                rightMotor->run(RELEASE);

                myServo.write(-15);
                for (int pos = -15; pos <= 40; pos++)
                {
                    myServo.write(pos);
                    delay(10); // Pause to smooth the movement
                }
                for (int pos = 40; pos >= -15; pos--)
                {
                    myServo.write(pos);
                    delay(10);
                }
                break;

            // Turn left
            case LEFT:
                turnLeft();
                lineFollower();
                break;

            // Turn right
            case RIGHT:
                turnRight();
                lineFollower();
                break;

            // If an obstacle is detected the pami stop for 500 ms
            case OBSTACLE_DETECTED:
                leftMotor->run(RELEASE);
                rightMotor->run(RELEASE);
                delay(500);
                // Check the life time.
                if (currentMillis - startMillis >= 92000)
                {
                    currentState = STOP;
                }
                else
                {
                    currentState = GO;
                }
                break;

            default:
                Log.notice("Unknown state");
                break;
            }
        }
    }
}
