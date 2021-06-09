#include <cmath>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"
#include "ClimbSubsystem.h"

/** 
 * Controls:
 * 1 - Control panel button
 *      - Use to control the left arm actuator piston
 * 2 - Climb initiation button
 *      - Use to initialize the climb 
 *      - Make this toggleable
 * 3 - Climb start button
 *      - Begin the climb
 *      - Start automated sequence for climb leveling
**/

/**
 * Libraries:
 * Gyro
 * Pistons
**/

/** 
 * Variables:
 * Boolean lock right
 * Boolean lock left
 * Boolean right arm climb actuator
 * Boolean left arm climb actuator
 * Boolean level 
 * 
 * Double right arm motor
 * Double left arm motor
**/ 

/**
 * Components:
 * x4 pistons
 *  - One each for controlling the gear lock.
 *  - One each for controlling the arm initiation. 
 * x2 motors
 *  - One each for extending and retracting the climb arms.
 * x1 gyro
 *  - Provide level information for the climb. 
**/

/**
 * Pseudo:
 * Start of match
 *  - Zero gyro
 *  - Zero encoders
 * 
 * Control panel
 *  - Move up left arm
 * 
 * Start of climb
 *  When initiation button pressed
 *  - Actuate lock pistons (pull out of gear)
 *  - Actuate both climb actuator pistons to max length
 *  - Initialize motors to extend climb arms semi-slowly
 *  - Once arms are at desired extension
 *      - Stop motors
 *  When start button pressed
 *      - Compare currents of both motors (check to see if similar)
 *      - Start detecting increase in current of both motors
 *          - If left is higher, stop left and continue right
 *          - If right is higher, stop right and continur left
 *          - Continue whichever motors until both show higher current
 *      - Initiate both motors to begin climb
 *      - If climb is already level
 *          - Just keep climbing on both arms until climb height is reached
 *      - If climb is not level
 *          - Get gyro data and change climb motors actuations based on level
 *          - Make sure that climb doesnt retract or extend past limits
 *          - If limit is reached, start adjusting in opposite direction
 *      - If climb is complete and level
 *          - Set lock pistons to default position (push into gear)
 *  Climb deactivation
 *      - Actuate lock pistons (pull out of gear)
 *      - Start motors to reset climb until limit switches/ prox sensors are intiated
 *      - Set lock pistons to default position (push into gear)
**/