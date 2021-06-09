#pragma once

#include <frc/Timer.h>

#include "RobotData.h"

class Auton
{
public:
    void Init();
    void Periodic(AutonSelect autonSelect, RobotData &robotData);
private:
    void startDelay(double duration, RobotData &robotData);
    void checkDelay(RobotData &robotData);
    void updateTimer(RobotData &robotData);
    frc::Timer timer{};

    double delayFinal;
    double duration;
};