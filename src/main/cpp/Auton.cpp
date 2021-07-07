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
    // frc::SmartDashboard::PutNumber("timer", robotData.seconds);
    frc::SmartDashboard::PutNumber("autonStep", robotData.autonStep);
    frc::SmartDashboard::PutNumber("desired angle", robotData.desiredAngleDiff);
    frc::SmartDashboard::PutNumber("initial angle", robotData.initialAngle);


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
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        break;
    
    case autonSelect_shootAndDrive:

        switch (robotData.autonStep)
        {
        case 0:
            robotData.manualMode = false;
            startDelay(4.5, robotData);
            robotData.shootingMode = true;
            robotData.driveMode = driveMode_potato;
            robotData.autonStep++;
            break;
        case 1:
            //shoot and check delay
            checkDelay(robotData);
            robotData.driveMode = driveMode_potato;
            break;
        case 2:
            //turn shooter off before driving away
            robotData.shootingMode = false;
            robotData.driveMode = driveMode_potato;
            robotData.autonStep++;
            break;
        case 3:
            robotData.desiredDBDist = 30;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 4:
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        break;

    // has not been tested with intake control
    // like trench run but bad
    case autonSelect_shootAndCollectBalls:
        switch (robotData.autonStep)
        {
        case 0:
            startDelay(7, robotData);
            robotData.shootingMode = true;
            robotData.autonStep++;
            break;
        case 1:
            //shoot and check delay
            checkDelay(robotData);
            break;
        case 2:
            //turn shooter off before driving away
            robotData.shootingMode = false;
            robotData.autonStep++;
            break;
        case 3:
            robotData.desiredDBDist = 15;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 4:
            //bring intake down and indexer into intaking mode while driving
            robotData.sRTrigger = true;
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.sRTrigger = false;
            robotData.driveMode = driveMode_potato;
            break;
        }
        break;

    //has not been tested with balls
    case autonSelect_trenchRun:
        switch (robotData.autonStep)
        {
        case 0:
            //spin up flywheel
            robotData.shootingMode = false;
            robotData.sBBtn = true;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //start delay to give time to intake
            startDelay(1.5, robotData);
            //init drive forward
            robotData.desiredDBDist = 50;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            //wait for intake to come down
            robotData.driveMode = driveMode_potato;
            checkDelay(robotData);
            break;
        case 2:
            //drive forward
            robotData.driveMode = driveMode_driveStraight;
            //spin up flywheel
            robotData.sBBtn = true;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //move on when two balls have been collected (in encoder values)
            break;
        case 3:
            //start delay and go into shooting mode
            startDelay(4.5, robotData);
            robotData.shootingMode = true;
            robotData.sBBtn = false;
            //intake in shooting mode/not collecting balls
            robotData.sRTrigger = false; 
            robotData.driveMode = driveMode_potato;
            robotData.autonStep++;
            break;
        case 4:
            //check delay, shoot
            checkDelay(robotData);
            robotData.shootingMode = true;
            robotData.driveMode = driveMode_potato;
            break;
        case 5:
            //turn shooting off, drive to collect more balls
            robotData.shootingMode = false;
            robotData.sRTrigger = true;
            //wait for intake to come down 
            startDelay(1.5, robotData);
            robotData.desiredDBDist = 40;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 6:
            robotData.driveMode = driveMode_potato;
            checkDelay(robotData);
            break;
        case 7:
            robotData.driveMode = driveMode_driveStraight;
            break;
        
        default:
            // robotData.sABtn = false;
            robotData.driveMode = driveMode_potato;
            break;
        }
        break; 

    case autonSelect_stealBallsAndShootFar:
        // switch (robotData.autonStep)
        // {
        // case 0:
        //     //spin up flywheel
        //     robotData.sDPad = -1;
        //     robotData.sBBtn = true;
        //     //intake and indexer in intaking mode 
        //     robotData.sRTrigger = true;
        //     //start delay to give time to intake
        //     startDelay(1.5, robotData);
        //     //init drive forward
        //     robotData.desiredDBDist = 33;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 1:
        //     //wait for intake to come down
        //     robotData.driveMode = driveMode_potato;
        //     checkDelay(robotData);
        //     break;
        // case 2:
        //     //drive forward to grab two balls
        //     robotData.driveMode = driveMode_driveStraight;
        //     //spin up flywheel
        //     robotData.sDPad = -1;
        //     robotData.sBBtn = true;
        //     //intake and indexer in intaking mode 
        //     robotData.sRTrigger = true;
        //     //move on when two balls have been collected (in encoder values)
        //     break;
        // case 3:
        //     // bring intake up
        //     robotData.sRTrigger = false;
        //     //drive
        //     robotData.desiredDBDist = -15;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 4:
        //     robotData.driveMode = driveMode_driveStraight;
        //     break;
        // case 5:
        //     // turn
        //     robotData.desiredAngleDiff = 90;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 6:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 7:
        //     robotData.desiredDBDist = -70;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 8:
        //     //spin up flywheel
        //     robotData.sDPad = -1;
        //     robotData.sBBtn = true;
        //     // drive
        //     robotData.driveMode = driveMode_driveStraight;
        //     break;
        // case 9:
        //     robotData.desiredAngleDiff = -90;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 10:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 11:
        //     //start delay and go into shooting mode
        //     startDelay(4.5, robotData);
        //     robotData.sBBtn = false; //spin up flywheel button
        //     robotData.sDPad = 90; //shooting button
        //     robotData.driveMode = driveMode_potato;
        //     robotData.autonStep++;
        //     break;
        // case 12:
        //     //check delay, shoot
        //     checkDelay(robotData);
        //     robotData.sDPad = 90;
        //     robotData.driveMode = driveMode_potato;
        //     break;
        // default:
        //     // robotData.sABtn = false;
        //     robotData.driveMode = driveMode_potato;
        //     break;
        // }

        // switch (robotData.autonStep)
        // {
        // case 0:
        //     //spin up flywheel
        //     robotData.shootingMode = false;
        //     robotData.sBBtn = true;
        //     //intake and indexer in intaking mode 
        //     robotData.sRTrigger = true;
        //     //start delay to give time to intake
        //     startDelay(1, robotData);
        //     //init drive forward
        //     robotData.desiredDBDist = 18;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 1:
        //     //wait for intake to come down
        //     robotData.driveMode = driveMode_potato;
        //     checkDelay(robotData);
        //     break;
        // case 2:
        //     //drive forward to grab two balls
        //     robotData.driveMode = driveMode_driveStraight;
        //     //spin up flywheel
        //     robotData.sBBtn = true;
        //     //intake and indexer in intaking mode 
        //     robotData.sRTrigger = true;
        //     //move on when two balls have been collected (in encoder values)
        //     break;
        // case 3:
        //     //turn to 45 degrees
        //     robotData.desiredAngleDiff = 53 - robotData.rawAngle;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 4:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 5:
        //     //drive to intake balls
        //     robotData.desiredDBDist = 50;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 6:
        //     robotData.driveMode = driveMode_driveStraight;
        //     break;
        // case 7:
        //     //turn to 0 degrees
        //     robotData.desiredAngleDiff = 0 - robotData.rawAngle;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 8:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 9:
        //     // bring intake up
        //     robotData.sRTrigger = false;
        //     //drive
        //     robotData.desiredDBDist = -15;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 10:
        //     robotData.driveMode = driveMode_driveStraight;
        //     break;
        // case 11:
        //     // turn
        //     robotData.desiredAngleDiff = 90 - robotData.rawAngle;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 12:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 13:
        //     robotData.desiredDBDist = -70;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 14:
        //     //spin up flywheel
        //     robotData.shootingMode = -1;
        //     robotData.sBBtn = true;
        //     // drive
        //     robotData.driveMode = driveMode_driveStraight;
        //     break;
        // case 15:
        //     robotData.desiredAngleDiff = -90;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 16:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 17:
        //     //start delay and go into shooting mode
        //     startDelay(4.5, robotData);
        //     robotData.sBBtn = false; //spin up flywheel button
        //     robotData.shootingMode = true; //shooting button
        //     robotData.driveMode = driveMode_potato;
        //     robotData.autonStep++;
        //     break;
        // case 18:
        //     //check delay, shoot
        //     checkDelay(robotData);
        //     robotData.shootingMode = true;
        //     robotData.driveMode = driveMode_potato;
        //     break;
        // default:
        //     robotData.driveMode = driveMode_potato;
        //     break;
        // }


        switch (robotData.autonStep)
        {
        case 0:
            //spin up flywheel
            robotData.shootingMode = false;
            robotData.sBBtn = true;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //start delay to give time for intake to drop
            startDelay(.7, robotData);
            //init drive forward
            robotData.desiredDBDist = 65;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            //wait for intake to come down
            robotData.driveMode = driveMode_potato;
            checkDelay(robotData);
            break;
        case 2:
            //drive forward to grab two balls
            robotData.driveMode = driveMode_driveStraight;
            //spin up flywheel
            robotData.sBBtn = true;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //move on when two balls have been collected (in encoder values)
            break;
        case 3:
            // bring intake up
            robotData.sRTrigger = false;
            //drive
            robotData.desiredDBDist = -30;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 4:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 5:
            robotData.desiredAngleDiff = 45;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 6:
            robotData.driveMode = driveMode_arc;
            break;
        case 7:
            robotData.desiredDBDist = -35;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 8:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 9:
            // turn
            robotData.desiredAngleDiff = -90;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 10:
            robotData.driveMode = driveMode_arc;
            break;
        case 11:
            startDelay(4.5, robotData);
            robotData.sBBtn = false; //spin up flywheel button
            robotData.shootingMode = true; //shooting button
            robotData.driveMode = driveMode_potato;
            robotData.autonStep++;
            break;
        case 12:
            checkDelay(robotData);
            robotData.shootingMode = true;
            robotData.driveMode = driveMode_potato;
            break;

        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        break;

    case autonSelect_stealBallsAndShootClose:
        // switch (robotData.autonStep)
        // {
        // case 0:
        //     //spin up flywheel
        //     robotData.sDPad = -1;
        //     robotData.sBBtn = true;
        //     //intake and indexer in intaking mode 
        //     robotData.sABtn = true;
        //     //start delay to give time to intake
        //     startDelay(1.5, robotData);
        //     //init drive forward
        //     robotData.desiredDBDist = 33;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 1:
        //     //wait for intake to come down
        //     robotData.driveMode = driveMode_potato;
        //     checkDelay(robotData);
        //     break;
        // case 2:
        //     //drive forward to grab two balls
        //     robotData.driveMode = driveMode_driveStraight;
        //     //spin up flywheel
        //     robotData.sDPad = -1;
        //     robotData.sBBtn = true;
        //     //intake and indexer in intaking mode 
        //     robotData.sABtn = true;
        //     //move on when two balls have been collected (in encoder values)
        //     break;
        // case 3:
        //     // not intaking balls anymore
        //     robotData.sABtn = false;
        //     //drive
        //     robotData.desiredDBDist = -60;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 4:
        //     robotData.driveMode = driveMode_driveStraight;
        //     break;
        // case 5:
        //     // turn
        //     robotData.desiredAngleDiff = 90;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 6:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 7:
        //     robotData.desiredDBDist = -70;
        //     robotData.driveMode = driveMode_initDriveStraight;
        //     break;
        // case 8:
        //     // spin up flywheel
        //     // robotData.sDPad = -1;
        //     robotData.sBBtn = true;
        //     // drive
        //     robotData.driveMode = driveMode_driveStraight;
        //     break;
        // case 9:
        //     robotData.desiredAngleDiff = -90;
        //     robotData.arcRadius = -1;
        //     robotData.driveMode = driveMode_initArc;
        //     break;
        // case 10:
        //     robotData.driveMode = driveMode_arc;
        //     break;
        // case 11:
        //     //start delay and go into shooting mode
        //     startDelay(4.5, robotData);
        //     robotData.sBBtn = false;
        //     robotData.sDPad = 90;
        //     //intake in shooting mode/not collecting balls
        //     //robotData.sABtn = false; 
        //     robotData.driveMode = driveMode_potato;
        //     robotData.autonStep++;
        //     break;
        // case 12:
        //     //check delay, shoot
        //     checkDelay(robotData);
        //     robotData.sDPad = 90;
        //     robotData.driveMode = driveMode_potato;
        //     break;
        
        // default:
        //     // robotData.sABtn = false;
        //     robotData.driveMode = driveMode_potato;
        //     break;
        // }
        switch (robotData.autonStep)
        {
        case 0:
            //spin up flywheel
            robotData.shootingMode = false;
            robotData.sBBtn = true;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //start delay to give time to intake
            startDelay(1, robotData);
            //init drive forward
            robotData.desiredDBDist = 25;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            //wait for intake to come down
            robotData.driveMode = driveMode_potato;
            checkDelay(robotData);
            break;
        case 2:
            //drive forward to grab two balls
            robotData.driveMode = driveMode_driveStraight;
            //spin up flywheel
            robotData.sBBtn = true;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //move on when two balls have been collected (in encoder values)
            break;
        case 3:
            //turn to 45 degrees
            robotData.desiredAngleDiff = 45 - robotData.rawAngle;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 4:
            robotData.driveMode = driveMode_arc;
            break;
        case 5:
            //drive to intake balls
            robotData.desiredDBDist = 10;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 6:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 7:
            //turn to 0 degrees
            robotData.desiredAngleDiff = 0 - robotData.rawAngle;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 8:
            robotData.driveMode = driveMode_arc;
            break;
        case 9:
            // bring intake up
            robotData.sRTrigger = false;
            //drive
            robotData.desiredDBDist = -60;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 10:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 11:
            // turn
            robotData.desiredAngleDiff = 90 - robotData.rawAngle;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 12:
            robotData.driveMode = driveMode_arc;
            break;
        case 13:
            robotData.desiredDBDist = -70;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 14:
            //spin up flywheel
            robotData.shootingMode = -1;
            robotData.sBBtn = true;
            // drive
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 15:
            robotData.desiredAngleDiff = -90;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 16:
            robotData.driveMode = driveMode_arc;
            break;
        case 17:
            //start delay and go into shooting mode
            startDelay(4.5, robotData);
            robotData.sBBtn = false; //spin up flywheel button
            robotData.shootingMode = true; //shooting button
            robotData.driveMode = driveMode_potato;
            robotData.autonStep++;
            break;
        case 18:
            //check delay, shoot
            checkDelay(robotData);
            robotData.shootingMode = true;
            robotData.driveMode = driveMode_potato;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }

        break;
    case autonSelect_goofy:
        switch(robotData.autonStep) {
       /*  case 0:
            robotData.desiredAngleDiff = 90;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initArc;
            break;
        case 1:
            robotData.driveMode = driveMode_arc;
            break; */
        case 0:
            robotData.desiredDBDist = -50;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            break;
        }
        break;

    default:
        robotData.driveMode = driveMode_potato;
        break;
    }

    // only for updating diagnostics
    robotData.autonSelect = autonSelect;
}


// updates the struct with the amount of time that has passed since the Timer object started keeping track of time
void Auton::updateTimer(RobotData &robotData)
{
    robotData.seconds = timer.Get();
}

// starts the delay function by recording when the delay should end
// duration is how long you want the delay to be in seconds
void Auton::startDelay(double duration, RobotData &robotData)
{
    delayFinal = robotData.seconds + duration;
}

// checks if the delay you started is over yet
// increments autonStep once your delay is done
void Auton::checkDelay(RobotData &robotData)
{
    if (robotData.seconds > delayFinal)
    {
        //wpi::outs() << "moving on";
        robotData.autonStep++;
    }
    
}