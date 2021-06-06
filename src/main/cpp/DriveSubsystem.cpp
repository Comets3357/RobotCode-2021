#include "Robot.h"
#include "DriveSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>


void DriveSubsystem::Init(){

    dbLM.RestoreFactoryDefaults();
    dbRM.RestoreFactoryDefaults();

    dbLS.RestoreFactoryDefaults();
    dbRS.RestoreFactoryDefaults();


    //we inverted the right side and set motors to follow each other
    dbLM.SetInverted(false);
    dbRM.SetInverted(true);

    dbLS.Follow(dbLM);
    dbRS.Follow(dbRM);

    dbRM.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    dbLM.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    dbLM.SetSmartCurrentLimit(45);
    dbRM.SetSmartCurrentLimit(45);
    dbLS.SetSmartCurrentLimit(45);
    dbRS.SetSmartCurrentLimit(45);

    dbLM.Set(0);
    dbRM.Set(0);

}

void DriveSubsystem::Periodic(RobotData &robotData)
{
    updateData(robotData);

    switch (robotData.driveMode)
    {
    case driveMode_potato:
        potato(robotData);
    case driveMode_driveForward:
        driveForward(robotData);
    default:    // teleop and multiple auton driveModes will use this
        //slows down the speed to 0.3 of the total
        lDrive = robotData.pLYStick * .3;
        rDrive = robotData.pRYStick * .3;

        //setting the motor speed, tank drive
        setDrive(lDrive, rDrive);
    }
}


void DriveSubsystem::updateData(RobotData &robotData)
{
    robotData.currentRDBPos = dbRMEncoder.GetPosition();
    robotData.currentLDBPos = dbLMEncoder.GetPosition();
}


// will be deleted
/* void DriveSubsystem::Auton(int select, RobotData &robotData)
{
    if (select == 0) {potato(robotData);}
    else
    {
        
        driveForward(robotData);
    }
} */

void DriveSubsystem::Disabled(){
    dbRM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    dbLM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void DriveSubsystem::setDrive(double lDrive, double rDrive)
{
    dbLM.Set(lDrive);
    dbRM.Set(rDrive);
}


// auton functions:

void DriveSubsystem::potato(RobotData &robotData)
{
    robotData.pLYStick = 0;
    robotData.pRYStick = 0;

}

void DriveSubsystem::driveForward(RobotData &robotData)
{
    // get current orientation of bot


    // pid for velocity

    double avgCurrentPos = (robotData.currentLDBPos + robotData.currentRDBPos) / 2;

    frc::SmartDashboard::PutNumber("avgCurrentPos", avgCurrentPos);

    double lDistLeft = robotData.desiredDBDist - (robotData.currentLDBPos - robotData.initialLDBPos);
    double rDistLeft = robotData.desiredDBDist - (robotData.currentRDBPos - robotData.initialRDBPos);

    frc::SmartDashboard::PutNumber("lDistLeft", lDistLeft);
    frc::SmartDashboard::PutNumber("rDistLeft", rDistLeft);

    if (lDistLeft > (robotData.desiredDBDist * 0.2))
    {
        robotData.pLYStick = 0.5;
    }
    else if (lDistLeft > (robotData.desiredDBDist * 0.1))
    {
        robotData.pLYStick = 0.4;
    }
    else if (lDistLeft > (robotData.desiredDBDist * 0.03))
    {
        robotData.pLYStick = 0.2;
    }
    else
    {
        robotData.pLYStick = 0;
    }

    if (rDistLeft > (robotData.desiredDBDist * 0.2))
    {
        robotData.pRYStick = 0.5;
    }
    else if (rDistLeft > (robotData.desiredDBDist * 0.1))
    {
        robotData.pRYStick = 0.4;
    }
    else if (rDistLeft > (robotData.desiredDBDist * 0.03))
    {
        robotData.pRYStick = 0.2;
    }
    else
    {
        robotData.pRYStick = 0;
    }
}