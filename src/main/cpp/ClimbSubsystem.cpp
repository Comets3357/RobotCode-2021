#include <frc/smartdashboard/SmartDashboard.h>

#include "ClimbSubsystem.h"
#include "Robot.h"

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
    //zeroing encoders
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

void ClimbSubsystem::Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData){


    frc::SmartDashboard::PutNumber("left",  climbArmLLimit.Get());
    frc::SmartDashboard::PutNumber("right",  climbArmRLimit.Get());

    frc::SmartDashboard::PutNumber("climb mode",  robotData.climbMode);

    frc::SmartDashboard::PutNumber("climbArmL",  climbArmL.Get());
    frc::SmartDashboard::PutNumber("climbArmR",  climbArmR.Get());


    if (!robotData.climbZeroing){
        
        if(robotData.manualMode){
            if (robotData.climbMode){
                climbing = false;
                setClimbArmPowers(0,0);
                manualMode(robotData);
            }
        } else {
            if (robotData.climbMode){
                
                semiAutoMode(robotData);
            }
        }
    } else {
        zeroLoop += 1;
        //testing
        if (robotData.sLYStickBtn){
            //zeroing encoders
            climbArmLPos.SetPosition(0);
            climbArmRPos.SetPosition(0);

            setClimbArmPowers(0,0);

            robotData.climbZeroing = false;
        } else if (zeroLoop > 75 && robotData.autonEnabled){
            setClimbArmPowers(0,0);
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
                //zeroing encoders
                climbArmLPos.SetPosition(0);
                climbArmRPos.SetPosition(0);

                solenoidArm.Set(solenoidArm.kForward);
                robotData.climbZeroing = false;
            }
        }
        
        
    }

    updateDiagnostics(diagnosticsData);
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
            setClimbArmPowers(0,0);

            initiated = true;
            initiationRunning = false;
        }
    } else if (initiationRunning && initiated) {
        if (climbArmRPos.GetPosition() < -5 || climbArmLPos.GetPosition() < -5) {
            //lowers the climb arms
            climbRunToPosition(-5, 0.3);

        } else {
            //sets the motors to 0 and changes the initiation toggle and up/down variable
            setClimbArmPowers(0,0);

            solenoidArm.Set(solenoidArm.kForward);

            initiated = false;
            initiationRunning = false;

        }
    }

    // Climb start

    if (robotData.sYBtn && !climbing) {
        
        climbing = true;
    }

   
    if (climbing) {
        if (climbArmLPos.GetPosition() < -30 || climbArmRPos.GetPosition() < -30){
            //if the robot is level and
            if (robotData.robotTiltAngle < 4 && robotData.robotTiltAngle > -4){
                setClimbArmPowers(0.3,0.3);
            } else {
                //if the robot isnt level it will try to level it while going up
                if (robotData.robotTiltAngle > 4) {
                    setClimbArmPowers(0.3,0);
                } else if (robotData.robotTiltAngle < -4) {
                    setClimbArmPowers(0,0.3);
                }
            }
        } else{ // if the climb is at the desired height it will level without raising

            //if the robot isnt level it will try to level it
            if (robotData.robotTiltAngle > 4) {
                climbArmL.Set(0.2);
            } else if (robotData.robotTiltAngle < -4) {
                climbArmL.Set(-0.2);
            } else {
                setClimbArmPowers(0,0);
            }
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

void ClimbSubsystem::setClimbArmPowers(double left, double right) {
    climbArmL.Set(left);
    climbArmR.Set(right);
}


void ClimbSubsystem::updateDiagnostics(DiagnosticsData &diagnosticsData)
{
    diagnosticsData.mControlCurrents.at(34) = climbArmL.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(34) = climbArmL.GetBusVoltage();
    diagnosticsData.mControlTemps.at(34) = climbArmL.GetMotorTemperature();
    diagnosticsData.mControlPositions.at(34) = climbArmLPos.GetPosition();
    diagnosticsData.mControlVelocities.at(34) = climbArmLPos.GetVelocity();
    diagnosticsData.mControlFaults.at(34) = climbArmL.GetFaults();

    diagnosticsData.mControlCurrents.at(35) = climbArmR.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(35) = climbArmR.GetBusVoltage();
    diagnosticsData.mControlTemps.at(35) = climbArmR.GetMotorTemperature();
    diagnosticsData.mControlPositions.at(35) = climbArmRPos.GetPosition();
    diagnosticsData.mControlVelocities.at(35) = climbArmRPos.GetVelocity();
    diagnosticsData.mControlFaults.at(35) = climbArmR.GetFaults();

    diagnosticsData.solenoidArm = solenoidArm.Get();
    diagnosticsData.solenoidArm = solenoidLockL.Get();
    diagnosticsData.solenoidArm = solenoidLockR.Get();
}