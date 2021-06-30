#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{
    intake.Init();
    db.Init();
    intake.Init();
    indexer.Init();
    shooter.Init();
    limelight.Init();
    // diagnostics.LogInit();
    // controlpanel.Init();
    // climb.Init();

}



void Robot::RobotPeriodic(){
    if (!IsDisabled()) {
        db.Periodic(robotData);
        intake.Periodic(robotData);
        indexer.Periodic(robotData);
        limelight.Periodic(robotData);
        // diagnostics.LogPeriodic(robotData, diagnosticsData);
        // controlpanel.Periodic(robotData);
        // climb.Periodic(robotData);
        shooter.Periodic(robotData);
        controlpanel.Periodic(robotData);
    }
}

void Robot::AutonomousInit()
{
    auton.Init();
    wpi::outs() << "auton init";
    
}

void Robot::AutonomousPeriodic() {
    if (!IsDisabled()) {
        wpi::outs() << "running auton";
        auton.Periodic(autonSelect_goofy, robotData);
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
    // indexer.Disabled();
    // intake.Disabled();
    // shooter.Disabled();
}

void Robot::TestInit()
{
    //diagnostics.TestInit();
}

void Robot::TestPeriodic()
{
    if (IsEnabled())
    {
        //diagnostics.TestPeriodic(diagnosticsData);
    }
}


#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
