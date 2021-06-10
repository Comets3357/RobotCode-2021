#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <frc/Timer.h>
#include "RobotData.h"


class Controller {
    
public:

    void Periodic(RobotData &robotData);


private:
    
    void updateTeleopData(RobotData &robotData);


    int getShiftFactor();
    bool shootingMode();
    bool getManual();


    bool getButton(int js, int index);
    int getPOV(int js, int index);
    double getAxis(int js, int index);
    // bool climbMode();


    frc::Joystick secondary{1};
    frc::Joystick primary{0};


    //this is necessary actually for the getManual() function
    bool inManualMode = false;


}; 

