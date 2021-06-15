#include <frc/smartdashboard/SmartDashboard.h>

#include "Auton.h"
#include "Robot.h"

void Auton::Init()
{
    timer.Reset();
    timer.Start();
}

void Auton::Periodic(AutonSelect autonSelect, RobotData &robotData)
{
    frc::SmartDashboard::PutNumber("autonSelect", autonSelect);
    // robotData.autonSelect = autonSelect;    // currently not using the robotData.autonSelect

    updateTimer(robotData);
    frc::SmartDashboard::PutNumber("timer", robotData.seconds);


    switch (autonSelect)
    {

    case autonSelect_potato:
        robotData.driveMode = driveMode_potato;
        break;

    case autonSelect_exitInitLine:
        frc::SmartDashboard::PutNumber("desiredDBDist", robotData.desiredDBDist);
        frc::SmartDashboard::PutNumber("autonStep", robotData.autonStep);

        switch (robotData.autonStep)
        {
        case 0:
            robotData.desiredDBDist = 10;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 1:
            robotData.driveMode = driveMode_driveForward;
            break;
        /* case 2:
            robotData.desiredDBDist = 15;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 3:
            robotData.driveMode = driveMode_driveForward;
            break; */
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        
        break;
    
    case autonSelect_shootAndDrive:

        switch (robotData.autonStep)
        {
        case 0:
            startDelay(7, robotData);
            robotData.sDPad = 90;
            robotData.autonStep++;
            break;
        case 1:
            //shoot and check delay
            checkDelay(robotData);
            break;
        case 2:
            //turn shooter off before driving away
            robotData.sDPad = -1;
            robotData.autonStep++;
            break;
        case 3:
            robotData.desiredDBDist = 15;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 4:
            robotData.driveMode = driveMode_driveForward;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        
        break;

    case autonSelect_shootAndCollectBalls:
        switch (robotData.autonStep)
        {
        case 0:
            startDelay(7, robotData);
            robotData.sDPad = 90;
            robotData.autonStep++;
            break;
        case 1:
            //shoot and check delay
            checkDelay(robotData);
            break;
        case 2:
            //turn shooter off before driving away
            robotData.sDPad = -1;
            robotData.autonStep++;
            break;
        case 3:
            robotData.desiredDBDist = 15;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 4:
            //bring intake down and indexer into intaking mode while driving
            robotData.sABtn = true;
            robotData.driveMode = driveMode_driveForward;
            break;
        default:
            robotData.sABtn = false;
            robotData.driveMode = driveMode_potato;
            break;
        }
        break;

    // case autonSelect_arcTest:
    //     switch(robotData.autonStep)
    //     {
    //     case 0:
    //         robotData.desiredAngleDiff = -90;
    //         robotData.arcRadius = -1;
    //         robotData.driveMode = driveMode_initArc;
    //         break;
    //     case 1:
    //         robotData.driveMode = driveMode_arc;
    //         break;
    //     /* case 2:
    //         robotData.desiredAngleDiff = 180;
    //         robotData.arcRadius = 3;
    //         robotData.driveMode = driveMode_initArc;
    //         break;
    //     case 3:
    //         robotData.driveMode = driveMode_arc;
    //         break; */
    //     default:
    //         robotData.driveMode = driveMode_potato;
    //         break;
    //     }

        // break;

    // original goofy
    /* case autonSelect_goofy:
        switch(robotData.autonStep) {
        case 0:
            robotData.desiredAngleDiff = 180;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 1:
            robotData.driveMode = driveMode_arc;
            break;
        case 2:
            robotData.desiredDBDist = 15;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 3:
            robotData.driveMode = driveMode_driveForward;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        
        break; */

    /* case autonSelect_goofy:
        switch(robotData.autonStep) {
        case 0:
            robotData.desiredAngleDiff = -90;
            robotData.arcRadius = 5;
            robotData.driveMode = driveMode_initArc;
            break;
        case 1:
            robotData.driveMode = driveMode_arc;
            break;
        case 2:
            robotData.desiredDBDist = 15;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 3:
            robotData.driveMode = driveMode_driveForward;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        
        break; */

    /* case autonSelect_goofy:
        switch(robotData.autonStep) {
        case 0:
            robotData.desiredAngleDiff = -30;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 1:
            robotData.driveMode = driveMode_arc;
            break;
        case 2:
            robotData.desiredDBDist = 15;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 3:
            robotData.driveMode = driveMode_driveForward;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        
        break; */

    case autonSelect_goofy:
        switch(robotData.autonStep) {
        case 0:
            robotData.desiredAngleDiff = -180;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 1:
            robotData.driveMode = driveMode_arc;
            break;
        /* case 2:
            startDelay(3, robotData);
            robotData.autonStep++;
            break;
        case 3:
            robotData.driveMode = driveMode_potato;
            checkDelay(robotData);
            break;
        case 4:
            robotData.desiredDBDist = 10;
            robotData.driveMode = driveMode_initDriveForward;
            break;
        case 5:
            robotData.driveMode = driveMode_driveForward;
            break; */
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        break;


    default:
        robotData.driveMode = driveMode_potato;
        break;
    }
}


//returns the amount of time that has passed since the Timer object started keeping track of time
void Auton::updateTimer(RobotData &robotData) {
    robotData.seconds = timer.Get();

}

//starts the delay function by recording when the delay should end
//duration is how long you want the delay to be in seconds
void Auton::startDelay(double duration, RobotData &robotData)
{
    delayFinal = robotData.seconds + duration;
}

void Auton::checkDelay(RobotData &robotData)
{
    if (robotData.seconds > delayFinal)
    {
        //wpi::outs() << "moving on";
        robotData.autonStep++;
    }
    
}