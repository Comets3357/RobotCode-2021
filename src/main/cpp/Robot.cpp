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
    controlpanel.Init();
    climb.Init();
    auton.Init(robotData);
}



void Robot::RobotPeriodic(){
    if (!IsDisabled()) {
        db.Periodic(robotData, diagnosticsData);
        
        intake.Periodic(robotData, diagnosticsData);
        indexer.Periodic(robotData, diagnosticsData);
        shooter.Periodic(robotData, diagnosticsData);
        limelight.Periodic(robotData);
        // diagnostics.LogPeriodic(robotData, diagnosticsData);
        controlpanel.Periodic(robotData);
        climb.Periodic(robotData);
        
    }
}

void Robot::AutonomousInit()
{
    // auton.Init(robotData);
    auton.AutonomousInit(robotData);
    wpi::outs() << "auton init";
    frc::SmartDashboard::PutNumber("this is the auton", robotData.autonSelect);
    
}

void Robot::AutonomousPeriodic() {
    if (!IsDisabled()) {
        wpi::outs() << "running auton";
        auton.Periodic(robotData.autonSelect, robotData);
        // auton.Periodic(autonSelect_stealBallsAndShootFar, robotData);
    }
}

void Robot::TeleopPeriodic()
{
    control.Periodic(robotData);
    robotData.driveMode = driveMode_teleop;
}

void Robot::DisabledInit()
{
    db.Disabled();
    indexer.Disabled();
    intake.Disabled();
    // shooter.Disabled();
}

void Robot::TestInit()
{
    // diagnostics.TestInit();
}

void Robot::TestPeriodic()
{
    if (IsEnabled())
    {
        // diagnostics.TestPeriodic(diagnosticsData);
    }
}


#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
