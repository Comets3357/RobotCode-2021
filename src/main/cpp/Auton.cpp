#include <frc/smartdashboard/SmartDashboard.h>

#include "Auton.h"

void Auton::Init(RobotData &robotData)
{
    //stuff for auton
    timer.Reset();
}

void Auton::Periodic(AutonSelect autonSelect, RobotData &robotData)
{
    switch (autonSelect)
    {
    case autonSelect_potato:
        robotData.driveMode = driveMode_potato;
        break;
    case autonSelect_exitInitLine:
        switch (robotData.autonStep)
        {
        case 0:
            robotData.desiredDBDist = 30;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 1:
            robotData.driveMode = driveMode_driveForward;
            break;
        // case 2:
        //     robotData.desiredDBDist = 15;
        //     robotData.driveMode = driveMode_initDriveForward;
        //     break;
        // case 3:
        //     robotData.driveMode = driveMode_driveForward;
        //     break;
        
        default:
            robotData.driveMode = driveMode_potato;
        break;
        }
    default:
        robotData.driveMode = driveMode_potato;
        break;
    }
}