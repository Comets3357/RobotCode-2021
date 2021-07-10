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
    auton.AutonomousInit(robotData);
    // wpi::outs() << "auton init";
    // frc::SmartDashboard::PutNumber("this is the auton", robotData.autonSelect);
    
}

void Robot::AutonomousPeriodic() {
    if (!IsDisabled()) {
        // wpi::outs() << "running auton";
        auton.AutonomousPeriodic(robotData.autonSelect, robotData);
    }
}

void Robot::TeleopPeriodic()
{
    control.TeleopPeriodic(robotData);
}

void Robot::DisabledInit()
{
    db.DisabledInit();
    indexer.DisabledInit();
    intake.DisabledInit();
    shooter.DisabledInit();
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
