#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{
    intake.Init();
    db.Init();
    indexer.Init();
    shooter.Init();
    limelight.Init();
    diagnostics.LogInit();
}

void Robot::RobotPeriodic()
{
    if (IsEnabled())
    {
        db.Periodic(robotData, diagnosticsData);
        intake.Periodic(robotData, diagnosticsData);
        indexer.Periodic(robotData, diagnosticsData);
        shooter.Periodic(robotData, diagnosticsData);
        limelight.Periodic(robotData, diagnosticsData);
        diagnostics.LogPeriodic(robotData, diagnosticsData);
    }
}

void Robot::AutonomousInit()
{
    auton.Init();
}

void Robot::AutonomousPeriodic()
{
    if (IsEnabled())
    {
        auton.Periodic(autonSelect_goofy, robotData);
    }
}

void Robot::TeleopPeriodic()
{
    control.Periodic(robotData);
}

void Robot::DisabledInit()
{
    db.Disabled();
}

void Robot::TestInit()
{
    diagnostics.TestInit();
}

void Robot::TestPeriodic()
{
    if (IsEnabled())
    {
        diagnostics.TestPeriodic(diagnosticsData);
    }
}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
