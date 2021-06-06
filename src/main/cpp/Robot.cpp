#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {

    intake.Init();
    db.Init();
    indexer.Init();
    shooter.Init();
    auton.Init(robotData);
    limelight.Init();


}



void Robot::RobotPeriodic(){
    db.Periodic(robotData);
    /* intake.Periodic(robotData);
    indexer.Periodic(robotData);
    shooter.Periodic(robotData);
    limelight.Periodic(robotData); */
}

void Robot::AutonomousPeriodic() {
    auton.Periodic(autonSelect_exitInitLine, robotData);
}

void Robot::TeleopPeriodic() {
    control.Periodic(robotData);
}

void Robot::DisabledInit(){
    db.Disabled();
}



#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
