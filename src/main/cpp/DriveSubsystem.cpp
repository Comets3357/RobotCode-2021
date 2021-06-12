#include "Robot.h"
#include "DriveSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>


void DriveSubsystem::Init(){

    dbLM.RestoreFactoryDefaults();
    dbRM.RestoreFactoryDefaults();

    dbLS.RestoreFactoryDefaults();
    dbRS.RestoreFactoryDefaults();


    //we inverted the right side and set motors to follow each other
    dbLM.SetInverted(true);
    dbRM.SetInverted(false);

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

    dbLM.BurnFlash();
    dbRM.BurnFlash();
    dbLS.BurnFlash();
    dbRS.BurnFlash();

    //gyro
    gyro.Calibrate();
    gyro.SetYawAxis(frc::ADIS16448_IMU::IMUAxis::kZ);
    


}

void DriveSubsystem::Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData)
{
    updateData(robotData);
    frc::SmartDashboard::PutNumber("driveMode", robotData.driveMode);

    // wpi::outs() << robotData.robotAngle << '\n';
    /* 
    wpi::outs() << "\nGetGyroAngleZ" <<gyro.GetGyroAngleZ();
    wpi::outs() << "\nGetAngle"<< gyro.GetAngle();
    wpi::outs() << "\nGetYawAxis"<< gyro.GetYawAxis(); */

    frc::SmartDashboard::PutNumber("GetGyroAngleZ", gyro.GetGyroAngleZ());
    frc::SmartDashboard::PutNumber("getAngle", gyro.GetAngle());




    switch (robotData.driveMode)
    {
    case driveMode_teleop:
        break;
    case driveMode_potato:
        potato(robotData);
        break;
    case driveMode_initDriveForward:
        initDriveForward(robotData);
        break;
    case driveMode_driveForward:
        driveForward(robotData);
        break;
    case driveMode_initArc:
        initArc(robotData);
        break;
    case driveMode_arc:
        arc(robotData);
        break;
    default:
        potato(robotData);
        break;
    }

    // teleop and multiple auton driveModes will use this
    //slows down the speed to 0.3 of the total
    lDrive = robotData.pLYStick * .3;
    rDrive = robotData.pRYStick * .3;

    //setting the motor speed, tank drive
    setDrive(lDrive, rDrive);
}




void DriveSubsystem::Disabled(){
    setDrive(0, 0);
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



    gyro.SetYawAxis(frc::ADIS16448_IMU::IMUAxis::kZ);
    //this is the direction that the robot is facing
    robotData.rawAngle = -gyro.GetAngle();
    double tempRobotAngle = -gyro.GetAngle();


    //calculates the non continuous angle
    while(tempRobotAngle >= 360){
        tempRobotAngle -= 360;
    }

    while(tempRobotAngle <= 0){
        tempRobotAngle += 360;
    }

    robotData.robotAngle = tempRobotAngle;
    frc::SmartDashboard::PutNumber("robotAngle", robotData.robotAngle);
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
    wpi::outs() << "initDriveForward" << '\n';
    robotData.autonStep++;
}

void DriveSubsystem::driveForward(RobotData &robotData)
{
    wpi::outs() << "driveForward" << '\n';
    // get current orientation of bot


    // pid for velocity

    double avgCurrentPos = (robotData.currentLDBPos + robotData.currentRDBPos) / 2;
    frc::SmartDashboard::PutNumber("avgCurrentPos", avgCurrentPos);

    double lDistLeft = robotData.desiredDBDist - (robotData.currentLDBPos - robotData.initialLDBPos);
    double rDistLeft = robotData.desiredDBDist - (robotData.currentRDBPos - robotData.initialRDBPos);

    frc::SmartDashboard::PutNumber("currentLDBPos", robotData.currentLDBPos);
    frc::SmartDashboard::PutNumber("currentRDBPos", robotData.currentRDBPos);

    frc::SmartDashboard::PutNumber("initialLDBPos", robotData.initialLDBPos);
    frc::SmartDashboard::PutNumber("initialRDBPos", robotData.initialLDBPos);

    frc::SmartDashboard::PutNumber("lDistLeft", lDistLeft);
    frc::SmartDashboard::PutNumber("rDistLeft", rDistLeft);

    if (lDistLeft > (robotData.desiredDBDist * 0.2)) {
        robotData.pLYStick = 0.5;
    }
    else if (lDistLeft > (robotData.desiredDBDist * 0.1)) {
        robotData.pLYStick = 0.4;
    }
    else if (lDistLeft > (robotData.desiredDBDist * 0.03)) {
        robotData.pLYStick = 0.2;
    }
    else {
        robotData.pLYStick = 0;
    }

    if (rDistLeft > (robotData.desiredDBDist * 0.2)) {
        robotData.pRYStick = 0.5;
    }
    else if (rDistLeft > (robotData.desiredDBDist * 0.1)) {
        robotData.pRYStick = 0.4;
    }
    else if (rDistLeft > (robotData.desiredDBDist * 0.03)) {
        robotData.pRYStick = 0.2;
    }
    else {
        robotData.pRYStick = 0;
    }

    if (lDistLeft <= (robotData.desiredDBDist * 0.03) && (rDistLeft <= (robotData.desiredDBDist * 0.03))) {
        wpi::outs() << "FINISHED DRIVE_FORWARD" << '\n';
        robotData.autonStep++;
    }
}

// you need to set a desiredAngleDiff and arcRadius beforehand
void DriveSubsystem::initArc(RobotData &robotData)
{
    robotData.initialAngle = robotData.rawAngle;
    // sideRatio is the factor to determine the smaller side
    robotData.sideRatio = robotData.arcRadius / (robotData.arcRadius + 2);
    frc::SmartDashboard::PutNumber("finalAngle", robotData.finalAngle);
    frc::SmartDashboard::PutNumber("sideRatio", robotData.sideRatio);
    wpi::outs() << "initArc" << '\n';
    robotData.autonStep++;
}

/**
 * makes the robot turn a desired angle
 * @param robotData struct from which you are retrieving necessary data
 */ 
void DriveSubsystem::arc(RobotData &robotData){
    //when called record initial angle. calculate final angle by adding the robotData.desiredAngleDiff to it. 

    double angleLeft = robotData.desiredAngleDiff - (robotData.rawAngle - robotData.initialAngle);
    // double angleLeft = robotData.finalAngle - robotData.rawAngle;
    frc::SmartDashboard::PutNumber("angleLeft", angleLeft);

    wpi::outs() << "arc" << '\n';
    
    if (angleLeft < -10)
    {
        // 0.3 for now because we can
        robotData.pLYStick = 0.55 * robotData.sideRatio;
        robotData.pRYStick = 0.55;
    }
    else if (angleLeft < -1)
    {
        robotData.pLYStick = 0.1 * robotData.sideRatio;
        robotData.pRYStick = 0.1;
    }
    /* else if (angleLeft < -2)
    {
        robotData.pLYStick = 0.05 * robotData.sideRatio;
        robotData.pRYStick = 0.05;
    } */
    else if (angleLeft > 10)
    {
        // 0.3 for now because we can
        robotData.pLYStick = 0.55;
        robotData.pRYStick = 0.55 * robotData.sideRatio;
    }
    else if (angleLeft > 1)
    {
        robotData.pLYStick = 0.1;
        robotData.pRYStick = 0.1 * robotData.sideRatio;
    }
    /* else if (angleLeft > 2)
    {
        robotData.pLYStick = 0.05;
        robotData.pRYStick = 0.05 * robotData.sideRatio;
    } */
    else {
        // you done gud
        robotData.pLYStick = 0;
        robotData.pRYStick = 0;
        robotData.autonStep++;
        wpi::outs() << "FINISHED ARC" << '\n';
    }

}

void DriveSubsystem::updateDiagnostics(DiagnosticsData &diagnosticsData)
{
    // accelerometer
    diagnosticsData.accelX = accelerometer.GetX();
    diagnosticsData.accelY = accelerometer.GetY();
    diagnosticsData.accelZ = accelerometer.GetZ();

    // pdp
    diagnosticsData.pdpTotalVoltage = pdp.GetVoltage();
    diagnosticsData.pdpTotalCurrent = pdp.GetTotalCurrent();
    diagnosticsData.pdpTotalPower = pdp.GetTotalPower();
    diagnosticsData.pdpTotalEnergy = pdp.GetTotalEnergy();
    diagnosticsData.pdpTemp = pdp.GetTemperature();
    for (int i = 0; i < 16; i++)
    {
        diagnosticsData.pdpCurrents.at(i) = pdp.GetCurrent(i);
    }

    // compressor


    // db motor controllers
    diagnosticsData.mControlCurrents.at(leftLeadDeviceID) = dbLM.GetOutputCurrent();
    diagnosticsData.mControlCurrents.at(rightLeadDeviceID) = dbRM.GetOutputCurrent();
    diagnosticsData.mControlCurrents.at(leftFollowDeviceID) = dbLS.GetOutputCurrent();
    diagnosticsData.mControlCurrents.at(rightFollowDeviceID) = dbRS.GetOutputCurrent();

    diagnosticsData.mControlVoltages.at(leftLeadDeviceID) = dbLM.GetBusVoltage();
    diagnosticsData.mControlVoltages.at(rightLeadDeviceID) = dbRM.GetBusVoltage();
    diagnosticsData.mControlVoltages.at(leftFollowDeviceID) = dbLS.GetBusVoltage();
    diagnosticsData.mControlVoltages.at(rightFollowDeviceID) = dbRS.GetBusVoltage();

    diagnosticsData.mControlTemps.at(leftLeadDeviceID) = dbLM.GetMotorTemperature();
    diagnosticsData.mControlTemps.at(rightLeadDeviceID) = dbRM.GetMotorTemperature();
    diagnosticsData.mControlTemps.at(leftFollowDeviceID) = dbLS.GetMotorTemperature();
    diagnosticsData.mControlTemps.at(rightFollowDeviceID) = dbRS.GetMotorTemperature();
}