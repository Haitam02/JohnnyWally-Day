# Big Robot's Code - Banner Deployment

The banner deployment is an action that the Big Robot had to perform during its lifetime. However, it was designed independently so that work could be done in parallel on both the Big Robot and the deployment system without interference—aside from a few measurements taken.

This section will explain how to achieve the banner deployment from scratch, covering the following aspects:

- Components and Concept Explanation
- Wiring and Design
- Dependencies and Code Explanation

### *Components and Concept Explanation*

The necessary materials include:

- 2 x 9V batteries
- 1 x Arduino UNO
- 1 x PCA9685 (to control the servos via I2C)
- 1 x LM7805 (to regulate voltage and protect the PCA9685 from overvoltage)
- 13 x Servo motors
- 2 x Small hinges (to connect the hatch to the board)
- 3 x Pieces of fabric
- 3 x Light round bars and 3 x Heavy round bars

With all this material, the idea for the banner deployment is as follows:

After setting up the Arduino UNO, the LM7805, the PCA9685, and the 13 servos on the back of the board (with their arms extending outside to allow movement), and after setting up the hatch and wiring everything, we can proceed to place the light and heavy bars, paired with fabric in between.

The process is as follows:

1. The Big Robot sends a signal.
2. It receives the signal.
3. The hatch opens.
4. The light bar is released outside the field, deploying the fabric.
5. The hatch closes.
6. The heavy bar is released inside the field, counterbalancing the fabric.
7. The Big Robot moves forward to ensure no gap between the fabrics.
8. The cycle repeats.

After performing this three times, the banner is fully deployed, and the Big Robot can continue its journey.

### *Wiring and Design*

For a better understanding of the wiring and design, it is recommended to refer to the visual schematic:

#### Wiring Schematic
<img src="Big_Robot's_Code-Banner_Deployment/Images/Wiring_schematic.png" alt="Wiring schematic" width="600"/>

#### Board Design Schematic (Back of the Board)
<img src="Big_Robot's_Code-Banner_Deployment/Images/Back_board.png" alt="Back board" width="400"/>

#### Board Design Photo (Front of the Board)
<img src="Big_Robot's_Code-Banner_Deployment/Images/Front_Board.jpg" alt="Front board" width="400"/>

### *Dependencies and Code Explanation*

For the dependencies, the following libraries are required:

- Adafruit PWM Servo Driver Library
- Wire Library (included with Arduino)
- ArduinoLog.h

Regarding the code organization, the project has been structured into three modular files for better maintainability and clarity:

- servo_controller.h - Contains all constant definitions, pin declarations, and function prototypes

- servo_controller.cpp - Implements all servo control logic and sequence functions

- main.ino - Handles the primary program flow and signal processing

The code is well-commented to explain the function of each part in detail, but here's an overall summary for better understanding.

At the beginning (as shown in the wiring schematic), I define the servo channels based on where I connected them. In the `setupServoController()` function (in servo_controller.cpp), I set initial positions to reset the servo arms so that the bars can be placed on top of them.

In the `loop()` function (in main.ino), I address an issue where the Big Robot's reset sends a "false" signal to my receiving pin (pin 2) due to the reset pulse. To solve this, I ignore any signals sent during the first few moments. After this delay, I call `runPart1`, `runPart2`, and then `runPart3`, one after the other, after receiving each signal.

The logic is as follows:

- `runPart1` releases the first part by lowering the servos that hold it

- `runPart2` raises the servos from the previous part to lower the fabric one level and then drop it, as in `runPart1`

- `runPart3` raises the servos from `runPart2` to lower the fabric one more level and let it drop again

This process allows the sequential deployment of the banner as described.
