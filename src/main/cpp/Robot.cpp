#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {

    intake.Init();
    db.Init();
    indexer.Init();
    shooter.Init();
    autoo.Init();
    manual.Init();
    //controller.Init();


}

void Robot::TeleopPeriodic() {
    

    if(control.getManual()){
        manual.Periodic(control, sStick, indexer, shooter, intake);
    }else{
        autoo.Periodic(sStick, indexer, shooter, intake);
    }
    

}




#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
