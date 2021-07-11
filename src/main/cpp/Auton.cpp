#include <frc/smartdashboard/SmartDashboard.h>

#include "Auton.h"
#include "Robot.h"

void Auton::RobotInit(RobotData &robotData)
{
    timer.Reset();
    timer.Start();

    autonChooser.AddOption("Potato", AutonSelect::autonSelect_potato);
    autonChooser.AddOption("Exit Init Line Towards Driver Station", AutonSelect::autonSelect_exitInitLineDriverStation);
    autonChooser.AddOption("Exit Init Line Towards Rendezvous", AutonSelect::autonSelect_exitInitLineRendezvous);
    autonChooser.AddOption("Shoot and Drive Towards Driver Station", AutonSelect::autonSelect_shootAndDriveToDriverStation);
    autonChooser.AddOption("Shoot and Drive Towards Rendezvous", AutonSelect::autonSelect_shootAndDriveToRendezvous);
    autonChooser.AddOption("Full Trench Run", AutonSelect::autonSelect_trenchRunFull);
    autonChooser.AddOption("Half Trench Run", AutonSelect::autonSelect_trenchRunHalf);
    autonChooser.AddOption("Thief Run Short", AutonSelect::autonSelect_stealBallsAndShoot);
    autonChooser.AddOption("Thief Run With Detour", AutonSelect::autonSelect_stealBallsAndShootDetour);
    autonChooser.SetDefaultOption("Potato", AutonSelect::autonSelect_potato);

    frc::SmartDashboard::PutData("Auto", &autonChooser);

    
}

void Auton::AutonomousPeriodic(AutonSelect autonSelect, RobotData &robotData)
{
    

    // frc::SmartDashboard::PutNumber("autonSelect", autonSelect);
    // robotData.autonSelect = autonSelect;    // currently not using the robotData.autonSelect

    updateTimer(robotData);
    // frc::SmartDashboard::PutNumber("timer", robotData.seconds);
    frc::SmartDashboard::PutNumber("autonStep", robotData.autonStep);
    // frc::SmartDashboard::PutNumber("desired angle", robotData.desiredAngleDiff);
    // frc::SmartDashboard::PutNumber("initial angle", robotData.initialAngle);

    robotData.manualMode = false;
    robotData.sLTrigger = false;

    switch (autonSelect)
    {

    case autonSelect_potato:
        robotData.driveMode = driveMode_potato;
        break;

    case autonSelect_exitInitLineDriverStation:

        switch (robotData.autonStep)
        {
        case 0:
            robotData.desiredDBDist = -20;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            break;
        }
        break;
    
    case autonSelect_exitInitLineRendezvous:

        switch (robotData.autonStep)
        {
        case 0:
            robotData.desiredDBDist = 20;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            break;
        }
        break;
    
    case autonSelect_shootAndDriveToDriverStation:

        robotData.sBBtn = true;
        switch (robotData.autonStep)
        {
        case 0:
            startDelay(6, robotData);
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
            robotData.desiredDBDist = -20;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 4:
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            break;
        }
        break;
    
    case autonSelect_shootAndDriveToRendezvous:

        switch (robotData.autonStep)
        {
        case 0:
            robotData.sBBtn = true;
            startDelay(6, robotData);
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
            robotData.desiredDBDist = 20;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 4:
            robotData.driveMode = driveMode_driveStraight;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            robotData.sBBtn = false;
            break;
        }
        break;

    // has not been tested with intake control
    // like trench run but bad
    case autonSelect_shootAndCollectBalls:
        switch (robotData.autonStep)
        {
        case 0:
            startDelay(4.5, robotData);
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
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            break;
        }
        break;

    //has not been tested with balls
    case autonSelect_trenchRunHalf:

        switch (robotData.autonStep)
        {
        case 0:
            //spin up flywheel
            robotData.shootingMode = false;
            robotData.sBBtn = true;
            //intake and indexer in intaking mode
            robotData.sRTrigger = true;
            //start delay to give time to intake
            // startDelay(1, robotData);
            //init drive forward
            robotData.desiredDBDist = 50;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            //wait for intake to come down
            robotData.driveMode = driveMode_potato;
            // checkDelay(robotData);
            robotData.autonStep++;  // gonna remove delay if possible
            break;
        case 2:
            //drive forward
            robotData.driveMode = driveMode_driveStraight;
            //spin up flywheel
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //move on when two balls have been collected (in encoder values)
            // starts shooting when almost at stop
            break;
        case 3:
            // robotData.sRTrigger = false; 
            robotData.desiredAngleDiff = -10;
            // robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initTurnInPlace;
            break;
        case 4:
            robotData.driveMode = driveMode_turnInPlace;
            break;
        case 5:
            robotData.desiredDBDist = -30;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 6:
            robotData.driveMode = driveMode_driveStraight;
            startDelay(3.5, robotData);
            break;
        case 7:
            //check delay, shoot
            robotData.shootingMode = true;
            checkDelay(robotData);
            robotData.driveMode = driveMode_potato;
            break;
        default:
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            robotData.sBBtn = false;
            break;
        }
        break; 

    case autonSelect_trenchRunFull:

        
        switch (robotData.autonStep)
        {
        case 0:
            //spin up flywheel
            robotData.shootingMode = false;
            robotData.sBBtn = true;
            //intake and indexer in intaking mode
            robotData.sRTrigger = true;
            //start delay to give time to intake
            // startDelay(1, robotData);
            //init drive forward
            robotData.desiredDBDist = 50;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 1:
            //wait for intake to come down
            robotData.driveMode = driveMode_potato;
            // checkDelay(robotData);
            robotData.autonStep++;  // gonna remove delay if possible
            break;
        case 2:
            //drive forward
            robotData.driveMode = driveMode_driveStraight;
            //spin up flywheel
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //move on when two balls have been collected (in encoder values)
            // starts shooting when almost at stop
            checkEarlyShooting(robotData);
            break;
        case 3:
            //start delay and go into shooting mode
            startDelay(3.5, robotData);
            robotData.shootingMode = true;
            //intake in shooting mode/not collecting balls
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
            robotData.desiredDBDist = 40;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 6:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 7:
            // drive back from under control panel
            robotData.desiredDBDist = -40;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 8:
            robotData.driveMode = driveMode_driveStraight;
            // not shooting early so we don't clip cp with hood
            // checkEarlyShooting(robotData);
            // so we fire up flywheel
            startDelay(3.5, robotData);
            break;
        case 9:
            robotData.shootingMode = true;
            robotData.driveMode = driveMode_potato;
            checkDelay(robotData);
            break;
        case 10:
            robotData.shootingMode = false;
            robotData.driveMode = driveMode_potato;
            robotData.sBBtn = false;
            robotData.autonStep++;

        defaults:
            // robotData.sABtn = false;
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            break;
        }
        break; 

    //doesn't go in front of the init line at all
    case autonSelect_stealBallsAndShoot:

        robotData.sBBtn = true;
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
            robotData.driveMode = driveMode_initTurnInPlace;
            break;
        case 6:
            robotData.driveMode = driveMode_turnInPlace;
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
            robotData.driveMode = driveMode_initTurnInPlace;
            break;
        case 10:
            robotData.driveMode = driveMode_turnInPlace;
            // later test adding checkEarlyShooting?
            break;
        case 11:
            startDelay(4.5, robotData);
            robotData.shootingMode = true; //shooting button
            robotData.driveMode = driveMode_potato;
            robotData.autonStep++;
            break;
        case 12:
            checkDelay(robotData);
            robotData.driveMode = driveMode_potato;
            break;

        default:
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            break;
        }
        break;

    // goes around any possible robots on init line
    case autonSelect_stealBallsAndShootDetour:
        
        robotData.sBBtn = true;
        switch (robotData.autonStep)
        {
        case 0:
            //spin up flywheel
            robotData.shootingMode = false;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //start delay to give time for intake to drop
            startDelay(.25, robotData);
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
            robotData.driveMode = driveMode_driveStraight;
            //intake and indexer in intaking mode 
            robotData.sRTrigger = true;
            //move on when two balls have been collected (in encoder values)
            break;
        case 3:
            // bring intake up
            robotData.sRTrigger = false;
            //drive
            robotData.desiredDBDist = -10;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 4:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 5:
            robotData.desiredAngleDiff = -45;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initTurnInPlace;
            break;
        case 6:
            robotData.driveMode = driveMode_turnInPlace;
            break;
        case 7:
            robotData.desiredDBDist = -50;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 8:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 9:
            // turn
            robotData.desiredAngleDiff = 90;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initTurnInPlace;
            break;
        case 10:
            robotData.driveMode = driveMode_turnInPlace;
            break;
        case 11:
            robotData.desiredDBDist = -50;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 12:
            robotData.driveMode = driveMode_driveStraight;
            break;
        case 13:
            robotData.desiredAngleDiff = -90;
            robotData.arcRadius = -1;
            robotData.driveMode = driveMode_initTurnInPlace;
            break;
        case 14:
            robotData.driveMode = driveMode_turnInPlace;
            break;
        case 15:
            robotData.desiredDBDist = 30;
            robotData.driveMode = driveMode_initDriveStraight;
            break;
        case 16:
            robotData.driveMode = driveMode_driveStraight;
            checkEarlyShooting(robotData);
            startDelay(4.5, robotData);
            break;
        case 17:
            robotData.driveMode = driveMode_potato;
            checkDelay(robotData);
            break;
        default:
            robotData.driveMode = driveMode_potato;
            robotData.shootingMode = false;
            robotData.sRTrigger = false;
            break;
        }
        break;
    
    default:
        robotData.driveMode = driveMode_potato;
        robotData.shootingMode = false;
        robotData.sRTrigger = false;
        break;
    }

    robotData.autonSelect = autonSelect;
}

void Auton::AutonomousInit(RobotData &robotData){
    robotData.autonStep = 0;
    robotData.autonSelect = autonChooser.GetSelected();
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

// checks to see if db moving slowly enough to start up shooting
void Auton::checkEarlyShooting(RobotData &robotData)
{
    if (((robotData.Ldrive + robotData.Rdrive) / 2) < 1600)
    {
        robotData.shootingMode = true;
    }
    else
    {
        robotData.shootingMode = false;
    }
}