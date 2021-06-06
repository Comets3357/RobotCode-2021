#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>


class Controller : frc2::SubsystemBase {
    
public:

    void Init();
    int getShiftFactor();
    bool shootingMode();
    bool getManual();
    // bool climbMode();

private:
    int toggle;
    frc::Joystick sStick{1};
    frc::Joystick mainStick{0};
}; 

