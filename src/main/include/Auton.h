#pragma once

#include <frc/Timer.h>
#include "RobotData.h"

#include "DriveSubsystem.h"

class Auton
{
public:
    void Init(RobotData &robotData);
    void Periodic(AutonSelect autonSelect, RobotData &robotData);

private:
    frc::Timer timer{};
};