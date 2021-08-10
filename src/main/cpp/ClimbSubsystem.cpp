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

void ClimbSubsystem::RobotInit(){
    climbArmLPos.SetPosition(0);
    climbArmRPos.SetPosition(0);

    climbArmR.RestoreFactoryDefaults();
    climbArmR.SetInverted(true);
    climbArmR.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    climbArmR.SetSmartCurrentLimit(45);
    climbArmR.Set(0);
    
    climbArmL.RestoreFactoryDefaults();
    climbArmL.SetInverted(false);
    climbArmL.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    climbArmL.SetSmartCurrentLimit(45);
    climbArmL.Set(0);
    
    // imu.Reset();
}

void ClimbSubsystem::Periodic(RobotData &robotData){


    frc::SmartDashboard::PutNumber("left",  climbArmLLimit.Get());
    frc::SmartDashboard::PutNumber("right",  climbArmRLimit.Get());

    frc::SmartDashboard::PutNumber("climb mode",  robotData.climbMode);

    frc::SmartDashboard::PutNumber("climbArmL",  climbArmL.Get());
    frc::SmartDashboard::PutNumber("climbArmR",  climbArmR.Get());

    // frc::SmartDashboard::PutNumber("isZero",  robotData);

    //manualMode(robotData);

    /* if (robotData.sBBtn) {
        solenoidArm.Set(solenoidArm.kForward);
    }
    if (robotData.sABtn) {
        solenoidArm.Set(solenoidArm.kReverse);
    } */


    if (!robotData.climbZeroing){
        
        if(robotData.manualMode){
            if (robotData.climbMode){
                climbing = false;
                climbArmL.Set(0);
                climbArmR.Set(0);
                manualMode(robotData);
            }
        } else {
            if (robotData.climbMode){
                
                semiAutoMode(robotData);
            }
        }
    } else {
        zeroLoop += 1;
        if (robotData.sLYStickBtn){
            climbArmLPos.SetPosition(0);
            climbArmRPos.SetPosition(0);
            climbArmL.Set(0);
            climbArmR.Set(0);
            robotData.climbZeroing = false;
        } else if (zeroLoop > 75 && robotData.autonEnabled){
            climbArmL.Set(0);
            climbArmR.Set(0);
        } else {
            if (climbArmLLimit.Get()) {
                climbArmL.Set(0);
            }
            else {
                climbArmL.Set(0.1);
            }
            if (climbArmRLimit.Get()) {
                climbArmR.Set(0);
            } else {
                climbArmR.Set(0.1);
            }
            if (climbArmLLimit.Get() && climbArmRLimit.Get()) {
                climbArmLPos.SetPosition(0);
                climbArmRPos.SetPosition(0);
                solenoidLockL.Set(false);
                solenoidLockR.Set(false);
                solenoidArm.Set(solenoidArm.kForward);
                robotData.climbZeroing = false;
            }
        }
        
        
    }
}

void ClimbSubsystem::manualMode(RobotData &robotData){

    if (robotData.sLYStick > 0.1 || robotData.sLYStick < -0.1) {
        climbArmL.Set(robotData.sLYStick*0.3);
    } else {
        climbArmL.Set(0);
    }

    if (robotData.sRYStick > 0.1 || robotData.sRYStick < -0.1) {
        climbArmR.Set(robotData.sRYStick*0.3);
    } else {
        climbArmR.Set(0);
    }

    if (climbArmLPos.GetPosition() < -10 || climbArmRPos.GetPosition() < -10) {
        solenoidArm.Set(solenoidArm.kReverse);
    } else {
        solenoidArm.Set(solenoidArm.kForward);
    }
}

void ClimbSubsystem::semiAutoMode(RobotData &robotData){

    if (robotData.armUpOnRequest && climbing == false && !initiated && !initiationRunning) {
        if (robotData.armUpOnRequest) {
            if (robotData.lastArmUp) {
                solenoidArm.Set(solenoidArm.kForward);
            } else {
                solenoidArm.Set(solenoidArm.kReverse);
            }
        }
        robotData.armUpOnRequest = false;
    } else {
        robotData.armUpOnRequest = false;
    }

    // Climb inititation

    if(robotData.sRBumper){
        if (!initiationRunning){
            initiationRunning = true;
        }
    }


    if (initiationRunning && !initiated) {
        if (climbArmRPos.GetPosition() > -80 || climbArmLPos.GetPosition() > -80) {//i dont know the exact numbers yet
        //raises arms for the beggining of arm initiation
            solenoidArm.Set(solenoidArm.kReverse);
            //starts to raise the climb arms
            climbRunToPosition(-80, -0.3);
        } else {
            //sets the motors to 0 and changes initiation toggle and up/down variables
            climbArmR.Set(0);
            climbArmL.Set(0);

            initiated = true;
            initiationRunning = false;
        }
    } else if (initiationRunning && initiated) {
        if (climbArmRPos.GetPosition() < -5 || climbArmLPos.GetPosition() < -5) {
            //lowers the climb arms
            climbRunToPosition(-5, 0.3);

        } else {
            //sets the motors to 0 and changes the initiation toggle and up/down variable
            climbArmR.Set(0);
            climbArmL.Set(0);

            solenoidArm.Set(solenoidArm.kForward);

            initiated = false;
            initiationRunning = false;
            robotData.climbZeroing = true;

        }
    }

    // Climb start

    if (robotData.sYBtn && !climbing) {
        
        climbing = true;;
    }

   
    if (climbing) {
        if (climbArmLPos.GetPosition() < -30 || climbArmRPos.GetPosition() < -30){
             if (robotData.robotTiltAngle < 4 && robotData.robotTiltAngle > -4){
                climbArmR.Set(0.3);
                climbArmL.Set(0.3);
            } else {
                climbLevel(robotData.robotTiltAngle,4);
            }
        } else{
            climbArmR.Set(0);
            climbArmL.Set(0);
            climbLevel(robotData.robotTiltAngle,4);
        }
    }

}


void ClimbSubsystem::climbRunToPosition(double pos, double pow) {
    if (climbArmRPos.GetPosition() > pos || climbArmLPos.GetPosition() > pos) {
        if (climbArmRPos.GetPosition() > pos) {
            climbArmR.Set(pow);
        } else {
            climbArmR.Set(0);
        }
        if (climbArmLPos.GetPosition() > pos) {
            climbArmL.Set(pow);
        } else {
            climbArmL.Set(0);
        }
    }
}

void ClimbSubsystem::climbLevel(double degree, double degreeRange) {
    if (degree > degreeRange) {
        climbArmR.Set(0);
        climbArmL.Set(0.3);
    } else if (degree < -degreeRange) {
        climbArmR.Set(0.3);
        climbArmL.Set(0);
    }
}