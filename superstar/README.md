# Superstar Robot

## Overview

Superstar is a line-following robot with obstacle detection capabilities. The robot follows a line on the ground using IR sensors and can detect obstacles in its path using an ultrasonic sensor. It also includes a servo motor for auxiliary movements.

## Features

- Line following using dual IR sensors
- Obstacle detection and avoidance
- State-based behavior control system
- Servo motor for additional movements
- Comprehensive logging system using ArduinoLog library

## Hardware Requirements

- Arduino board
- Adafruit Motor Shield V2
- 2 DC motors (connected to M1 and M2 on the shield)
- Ultrasonic sensor (HC-SR04)
- 2 IR line detection sensors
- Servo motor
- Power supply

## Pin Configuration

### Motors

| Component   | Connection         | Description                   |
| ----------- | ------------------ | ----------------------------- |
| Left Motor  | M1 on Motor Shield | Controls left wheel movement  |
| Right Motor | M2 on Motor Shield | Controls right wheel movement |

### Sensors

| Sensor             | Pin | Description                        |
| ------------------ | --- | ---------------------------------- |
| Ultrasonic Trigger | 9   | Sends trigger signal to HC-SR04    |
| Ultrasonic Echo    | 10  | Receives echo signal from HC-SR04  |
| Left IR Sensor     | 8   | Detects line on the left side      |
| Right IR Sensor    | 7   | Detects line on the right side     |
| Servo Motor        | 9   | Controls auxiliary servo movements |

### Operation Modes

The robot operates in three states:

1. **RUN**: Normal line following mode, follows a line and checks for obstacles
2. **STOP**: Temporary halt when an obstacle is detected (stops for 1 second)
3. **DANCE**: Special mode where the robot stops and the servo performs a sweeping motion

## Software Architecture

The software is organized into several modules:

- `Motor`: Controls robot movement (forward, turning, stopping)
- `Sensor`: Handles line detection and obstacle detection
- `ServoControl`: Controls servo motor movements
- `Superstar`: Main controller that coordinates the robot's behavior

## Logging System

The robot uses the ArduinoLog library to provide detailed operational logs. The logs are formatted with different levels to help with debugging and monitoring:

- **VERBOSE**: Detailed information for debugging, includes sensor readings and motor actions
- **NOTICE**: Normal but significant events like state changes and initializations
- **WARNING**: Important events like obstacle detection
- **ERROR**: Critical issues that may require intervention

To view the logs:

1. Connect the Arduino to your computer
2. Open the Serial Monitor in the Arduino IDE
3. Set the baud rate to 115200
4. Power on the robot

The logs provide real-time information about what the robot is doing, helping you diagnose issues and understand the robot's behavior.

## Usage

1. Install the ArduinoLog library (Sketch > Include Library > Manage Libraries)
2. Upload the code to your Arduino board
3. Connect to the Serial monitor (115200 baud) to view logs
4. Place the robot on a line
5. Power on the robot
6. The robot will automatically follow the line and avoid obstacles for 15 seconds before stopping

## Library Dependencies

- Wire.h
- Adafruit_MotorShield.h
- ArduinoLog.h
- NewPing.h
- Servo.h

## Project Structure

```
superstar/
├── superstar.ino      # Main Arduino sketch
├── superstar.h        # Main controller class header
├── superstar.cpp      # Main controller class implementation
├── motor.h            # Motor control header
├── motor.cpp          # Motor control implementation
├── sensor.h           # Sensor interface header
├── sensor.cpp         # Sensor interface implementation
├── servoControl.h     # Servo controller header
├── servoControl.cpp   # Servo controller implementation
└── README.md          # This file
```

## Notes

- The robot runs for 15 seconds after power-up, then automatically stops
- The obstacle detection range is set to 20cm by default
- The line following sensors are expected to return HIGH (1) when they detect a line
- All String constants use F() macro to save RAM by storing strings in flash memory
- The CR macro in the logs ensures proper line endings in the Serial monitor
