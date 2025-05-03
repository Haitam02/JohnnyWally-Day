# PAMI's code
We used 2 pami with a similar code. Both use a rope, two ultrasound sensors to detect obstacles and two infrared to follow the lines. This is how they got to the playground.

The code works with a FSM containing the states START, GO, STOP, BACK, LEFT, RIGHT and OBSTACLE_DETECTED. 
The code starts (state START) when the rope is open (state high). The PAMI starts only when the first delay is reached (85 seconds min rule) and stops once the second delay (its end-of-life delay) is reached. At this point, the FSM is in the STOP state and it’s the end of the code. For the PAMI to reach their right zone, each has an adjusted speed and end-of-life delay.

The differences between the two codes are the initial position of the servo motor. The PAMI number 2 has its servo initialized with ```const int positionInitiale = -15;```. This is due to its placement in the starting zone, placing the servomotor like this allow to not disturb the superstar. The speed and life-time delay are also different depending on the PAMI. These are parameters that we used to adjust the position of the PAMIs into the final area.

### Requirements
To use the code, you will need all the libraries listed below:
- Wire.h
- Adafruit_MotorShield.h           
- SoftwareSerial.h 
- Servo.h 
- NewPing.h
- ArduinoLog.h

### Pin used
#### List of the pin for the PAMI 2 & 3
| Sensors   | Side  |Pin   | Pin   |
|-----------|-------|------|-------|
|Ultrasound | Left  |Trg-12|Echo-13|
|Ultrasound | Right |Trg-8 |Echo-9 |
|Infrared   | Left  |   5  |   /   |
|Infrared   | Right |   4  |   /   |
|Rope| /|  11|/|
|Servomotor|/|6|/|
|Encoder|Left|2 |/|
|Encoder| Right| 3|/|

