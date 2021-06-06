#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {

    intake.Init();
    db.Init();
    indexer.Init();
    shooter.Init();
    //controller.Init();


}

void Robot::RobotPeriodic(){
    db.Periodic(robotData);
    intake.Periodic(robotData);
    indexer.Periodic(robotData);
    shooter.Periodic(robotData);
}

void Robot::TeleopPeriodic() {
    control.Periodic(robotData);
}




#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
