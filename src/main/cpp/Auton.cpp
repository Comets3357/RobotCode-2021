#include <frc/smartdashboard/SmartDashboard.h>

#include "Auton.h"

void Auton::Init(RobotData &robotData)
{
    //stuff for auton
    timer.Reset();
}

void Auton::Periodic(AutonSelect autonSelect, RobotData &robotData)
{
    // ONLY SPOOFING ROBOTDATA VALUES
    /* if (select == 0)    // potato
    {
        robotData.driveMode = driveMode_potato;
    }
    else if (select == 1)   // test drive forward
    {
        robotData.driveMode = driveMode_driveForward;
    }
    else {} */

    switch(autonSelect)
    {
    case autonSelect_potato:

        break;
    case autonSelect_exitInitLine:
        break;
    default:
        // also potato for default
        break;
    }
}