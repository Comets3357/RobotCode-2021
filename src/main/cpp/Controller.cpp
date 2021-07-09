#include "Robot.h"
#include "Controller.h"
#include <frc/Timer.h>
#include <frc/DriverStation.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Controller::Init(RobotData &robotData){

    //stuff for auton
    //timer.Reset();

    //initializing struct values
    robotData.pLYStick = 0;
    robotData.pRYStick = 0;

    robotData.pABtn = false;
    robotData.pBBtn = false;
    robotData.pXBtn = false;
    robotData.pYBtn = false;

    robotData.sDPad = -1; 

    robotData.sLYStick = 0; 
    robotData.sRYStick = 0; 

    robotData.sLTrigger = 0; 
    robotData.sRTrigger = 0; 


    robotData.sABtn = false; 
    robotData.sBBtn = false; 
    robotData.sXBtn = false; 
    robotData.sYBtn = false; 
    robotData.sLBumper = false; 
    robotData.sRBumper = false;
    
}

void Controller::Auton(RobotData &robotData){
}



void Controller::Periodic(RobotData &robotData){
    updateTeleopData(robotData);
    frc::SmartDashboard::PutBoolean("Manual mode", robotData.manualMode);
}

/**
 * allows more button options and control
 */
bool Controller::getShiftFactor(){
    if(secondary.GetRawButton(5)){
        return true;
    } else {
        return false;
    }
}


bool Controller::shootingMode(int pov){
    //probably definitely wrong pov button index
    if(secondary.GetRawButton(3)){
        return true;
    }else{
        return false;
    }
}

/**
 * uses left and right POV input
 * @return moves the turret a little to the left or right in order for the limelight to see the target
 */
int Controller::roughShooting(){
    if(secondary.GetPOV(0) == 90){
        return 1;
    }else if(secondary.GetPOV(0) == 270){
        return -1;
    }else{
        return 0;
    }
}

/**
 * uses up and down POV input
 * @return the offset of the hood based on controller input 
 */
int Controller::roughHood(){
    static int pow = 0;
    if(secondary.GetPOV(0) == 180){
        pow += 1;
    }else if(secondary.GetPOV(0) == 0){
        pow -= 1;
    }
    return pow;
}

bool Controller::climbMode(RobotData &robotData){
    if (secondary.GetRawButtonPressed(7)){
        robotData.climbMode = !robotData.climbMode;
    }

    return robotData.climbMode;
}

bool Controller::getManual(){
    if (secondary.GetRawButtonPressed(8)){
        inManualMode = !inManualMode;
    }

    return inManualMode;
}

bool Controller::getButton(int js, int index){
    if(js == 1){
        return secondary.GetRawButton(index);
    } else {
        return primary.GetRawButton(index);
    }
}

int Controller::getPOV(int js, int index){
    if(js == 1){
        return secondary.GetPOV(index);
    } else {
        return primary.GetPOV(index);
    }
}

double Controller::getAxis(int js, int index){
    if(js == 1){
        return secondary.GetRawAxis(index);
    } else {
        return primary.GetRawAxis(index);
    }
}

void Controller::updateTeleopData(RobotData &robotData){

    //modes
    robotData.manualMode = getManual();
    robotData.shift = getShiftFactor();
    robotData.shootingMode = shootingMode(robotData.shootingBtn);
    climbMode(robotData);

    //used for driving
    if(frc::DriverStation::GetInstance().GetJoystickName(0) == "FrSky Taranis Joystick"){
        robotData.pLYStick = getAxis(0, 0);
        robotData.pRYStick = getAxis(0, 2);
    }else{
        robotData.pLYStick = -getAxis(0, 1);
        robotData.pRYStick = -getAxis(0, 5);
    }
    
    //primary button control
    robotData.pABtn = getButton(0,1);
    robotData.pBBtn = getButton(0,2);
    robotData.pXBtn = getButton(0,3);
    robotData.pYBtn = getButton(0,4);

    robotData.pLBumper = getButton(0, 5); 
    robotData.pRBumper = getButton(0, 6); 

    //secondary controls 
        // indexes are NOT all right yet
    //robotData.sLCenterBtn = getAxis(1, 8); //only used within controller class
    robotData.sDPad = getPOV(1, 0); 

    robotData.sLYStick = -getAxis(1, 1); 
    robotData.sRYStick = -getAxis(1, 5); 

    robotData.sLTrigger = getAxis(1, 2); 
    robotData.sRTrigger = getAxis(1, 3); 


    robotData.sABtn = getButton(1, 1); 
    robotData.sBBtn = getButton (1, 2); 
    robotData.sXBtn = getButton(1, 3); 
    robotData.sYBtn = getButton(1, 4); 
    robotData.sLBumper = getButton(1, 5); 
    robotData.sRBumper = getButton(1, 6); 

    //shooting 
    robotData.roughAim = roughShooting();
    robotData.roughHood = roughHood();

}
