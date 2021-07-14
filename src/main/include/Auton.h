#pragma once

#include <frc/Timer.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "RobotData.h"

class Auton
{
public:
    void RobotInit(RobotData &robotData);
    void AutonomousPeriodic(AutonSelect autonSelect, RobotData &robotData);
    
    void AutonomousInit(RobotData &robotData);

private:
    void startDelay(double duration, RobotData &robotData);
    void checkDelay(RobotData &robotData);
    void updateTimer(RobotData &robotData);
    void checkEarlyShooting(RobotData &robotData);
    void endAllTasks(RobotData &robotData);

    frc::Timer timer{};
    frc::SendableChooser<AutonSelect> autonChooser;
    double delayFinal;
    double duration;
    
};