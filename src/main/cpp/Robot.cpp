#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {

    db.Init();
    indexer.Init();
    shooter.Init();
    limelight.Init();
    controlpanel.Init();

}



void Robot::RobotPeriodic(){
    if (!IsDisabled()) {
        db.Periodic(robotData);
        intake.Periodic(robotData);
        indexer.Periodic(robotData);
        shooter.Periodic(robotData);
        limelight.Periodic(robotData);
        controlpanel.Periodic(robotData);
    }
}

void Robot::AutonomousInit() {
    auton.Init();
}

void Robot::AutonomousPeriodic() {
    if (!IsDisabled()) {
        auton.Periodic(autonSelect_trenchRun, robotData);
    }
}

void Robot::TeleopPeriodic() {
    control.Periodic(robotData);
    robotData.driveMode = driveMode_teleop;
}

void Robot::DisabledInit(){
   db.Disabled();
}




#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
