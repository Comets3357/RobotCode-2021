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

    //gyro
    gyro.Calibrate();

}

void DriveSubsystem::Periodic(RobotData &robotData)
{
    updateData(robotData);

    switch (robotData.driveMode)
    {
    case driveMode_potato:
        potato(robotData);
    case driveMode_initDriveForward:
        initDriveForward(robotData);
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



/** 
 * updates encoder and gyro values
 * @param robotData the struct in which these values are stored
 */ 
void DriveSubsystem::updateData(RobotData &robotData)
{
    //add back encoders at some point
    robotData.currentRDBPos = dbRMEncoder.GetPosition();
    robotData.currentLDBPos = dbLMEncoder.GetPosition();

    //this is the direction that the robot is facing
    robotData.rawAngle = gyro.GetAngle();
    robotData.robotAngle = gyro.GetAngle();


    //calculates the non continuous angle
    while(robotData.robotAngle > 360){
        robotData.robotAngle -= 360;
    }

    while(robotData.robotAngle < 360){
        robotData.robotAngle += 360;
    }
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

void DriveSubsystem::initDriveForward(RobotData &robotData)
{
    robotData.initialLDBPos = robotData.currentLDBPos;
    robotData.initialRDBPos = robotData.currentRDBPos;
    robotData.autonStep++;
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

    if ((robotData.pLYStick = 0) && (robotData.pRYStick = 0)) {
        robotData.autonStep++;
    }
}

/**
 * makes the robot turn a desired angle
 * @param target the amount that you want the robot to turn. positive for right, negative for left
 * @param robotData struct from which you are retrieving necessary data
 */ 
void DriveSubsystem::turn(double target, RobotData &robotData){
    
    //when called record initial angle. calculate final angle by adding the target to it. 
    robotData.initialAngle = robotData.rawAngle;
    robotData.finalAngle = robotData.initialAngle + target;

    //jank, gotta fix this, but this is the basic concept
    //untested
    while(robotData.finalAngle > robotData.rawAngle){
        setDrive(.3, 0);
        return;
    }

    while(robotData.finalAngle > robotData.rawAngle){
        setDrive(0, .3);
    }

    



}
