#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>

#include "RobotData.h"


class Controller : frc2::SubsystemBase {
    
public:

    void Init();
    void Periodic(RobotData &robotData);

private:
    
    void updateData(RobotData &robotData);
    int getShiftFactor();
    bool shootingMode();
    bool getManual();
    bool getButton(int js, int index);
    int getPOV(int js, int index);
    double getAxis(int js, int index);
    // bool climbMode();
    frc::Joystick secondary{1};
    frc::Joystick primary{0};

    bool inManualMode = false;


}; 

