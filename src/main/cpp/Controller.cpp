#include "Robot.h"
#include "Controller.h"
#include <frc/smartdashboard/SmartDashboard.h>



void Init(){
    int toggle = 0;
    
}

int Controller::getShiftFactor(){
    if (sStick.GetRawButton(5)){
        return -1;
    } else {
        return 1;
    }
}

bool Controller::shootingMode(){
    //probably definitely wrong pov button index
    if(sStick.GetPOV(1) == 0||sStick.GetPOV(1) == 90||sStick.GetPOV(1) == 180||sStick.GetPOV(1) == 270){
        return true;
    }else{
        return false;
    }
}

// bool Controller::climbMode(){

// }

bool Controller::getManual(){
    if(sStick.GetRawButton(8)){
        toggle++;
    }

    if(toggle%2 == 0){
        return true;
    } else {
        return false;
    }
}

