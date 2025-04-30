# JohnnyWally-Day
Add a global description of the project

## PAMI's code
We used 2 pami with a similar code. Both use a rope, two ultrasound sensors to detect obstacles and two infrared to follow the lines. This is how they got to the playground.

The code works with a FSM containing the states START, Go, STOP, BACK, LEFT, RIGHT and OBSTACLE_DETECTED. 
The code start (state START) when the rope is open (state high) and when the delay is reached (state STOP). For the PAMI to reach their right zone, each has a speed and an adjusted end-of-life delay.

The differences between the two codes are the initial position of the servo motor. The PAMI number 2 has its servo initialized with ```const int positionInitiale = -15;```. This is due to its placement in the starting zone, placing the servomotor like this allow to not disturb the superstar. The speed and life-time delay are also different depending on the PAMI.

### Requirement
Add all the library needed
### Pin used


