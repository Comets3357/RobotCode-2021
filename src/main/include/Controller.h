#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <frc/Timer.h>
#include "RobotData.h"
#include <frc/DriverStation.h>


class Controller {
    
public:

    void Periodic(RobotData &robotData);
    void Init(RobotData &robotData);
    void Auton(RobotData &robotData);

private:
    
    void updateTeleopData(RobotData &robotData);


    bool getShiftFactor();
    bool shootingMode(int pov);
    bool getManual();
    int roughShooting();
    bool limelightMode(bool shift);
    int roughHood();


    bool getButton(int js, int index);
    int getPOV(int js, int index);
    double getAxis(int js, int index);
    bool climbMode(RobotData &robotData);


    frc::Joystick secondary{1};
    frc::Joystick primary{0};


    //this is necessary actually for the getManual() function
    bool inManualMode = false;
    bool limelightOn = false;


}; 

