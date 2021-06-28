#include "Robot.h"
#include "Controller.h"
#include <frc/Timer.h>


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

bool Controller::getShiftFactor(){
    if(secondary.GetRawButton(5)){
        return true;
    } else {
        return false;
    }
}

bool Controller::limelightMode(bool shift){
    if (secondary.GetRawButtonPressed(8) && shift){
        limelightOn = !limelightOn;
    }

    return limelightOn;
}

bool Controller::shootingMode(int pov){
    //probably definitely wrong pov button index
    if(secondary.GetPOV(1) == pov){
        return true;
    }else{
        return false;
    }
}

// bool Controller::climbMode(){

// }

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
    robotData.manualMode = getManual();
    robotData.shift = getShiftFactor();
    robotData.shootingMode = shootingMode(robotData.shootingBtn);
    robotData.limelightOn = limelightMode(robotData.shift);




    //used for driving
    robotData.pLYStick = -getAxis(0, 1);
    robotData.pRYStick = -getAxis(0, 5);

    robotData.pABtn = getButton(0,1);
    robotData.pBBtn = getButton(0,2);
    robotData.pXBtn = getButton(0,3);
    robotData.pYBtn = getButton(0,4);

    robotData.pLBumper = getButton(0, 5); // controls indexer in auto
    robotData.pRBumper = getButton(0, 6); // manual

    //secondary controls 
        // indexes are NOT all right yet
    //robotData.sLCenterBtn = getAxis(1, 8); //only used within controller class
    robotData.sDPad = getPOV(1, 0); //secondaryPOVArrayInput in auto

    robotData.sLYStick = -getAxis(1, 1); //turret control in auto
    robotData.sRYStick = -getAxis(1, 5); //turret control in auto

    robotData.sLTrigger = getAxis(1, 2); //manual
    robotData.sRTrigger = getAxis(1, 3); // manual


    robotData.sABtn = getButton(1, 1); //controls omni wheel indexer in auto
    robotData.sBBtn = getButton (1, 2); // controls intake in auto
    robotData.sXBtn = getButton(1, 3); // controls  intake in auto
    robotData.sYBtn = getButton(1, 4); // controls intake in auto
    robotData.sLBumper = getButton(1, 5); // controls indexer in auto
    robotData.sRBumper = getButton(1, 6); // manual

}
