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

    rev::CANSparkMaxLowLevel::EnableExternalUSBControl(true);


    //values from testing on a weighted db
    //have yet to be tested on the comp bot
    dbLMPID.SetP(0.00027);
    dbLMPID.SetI(0);
    dbLMPID.SetD(0.008);
    dbLMPID.SetFF(0.00019);

    dbRMPID.SetP(0.00027);
    dbRMPID.SetI(0);
    dbRMPID.SetD(0.008);
    dbRMPID.SetFF(0.00019);


    dbLM.BurnFlash();
    dbRM.BurnFlash();
    dbLS.BurnFlash();
    dbRS.BurnFlash();

    //gyro
    gyro.Calibrate();
    gyro.SetYawAxis(frc::ADIS16448_IMU::IMUAxis::kZ);
    


}

void DriveSubsystem::Periodic(RobotData &robotData)
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
        teleopControl(robotData);
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
    /* case driveMode_PIDtest:
        courseCorrectedDrive(robotData);
        break; */
    default:
        potato(robotData);
        break;
    }

    setDrive(robotData);

    frc::SmartDashboard::PutNumber("autonStep", robotData.autonStep);


    // teleop and multiple auton driveModes will use this
    // lDrive = robotData.pLYStick*3000;
    // rDrive = robotData.pRYStick*3000;


    
    //setting the motor speed, tank drive
    // setDrive(robotData);

    
    /* wpi::outs() << "js input left" << robotData.pLYStick;
    wpi::outs() << "set velocity left" << lDrive; */
}

void DriveSubsystem::Disabled(){
    //setDrive(0, 0);
    dbLM.Set(0);
    dbRM.Set(0);
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
    //add negative sign for comp bot, remove for test db
    robotData.rawAngle = gyro.GetAngle();
    double tempRobotAngle = gyro.GetAngle();

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

//not in use bc it didn't work for some reason
/* void DriveSubsystem::setDrivePID(rev::CANPIDController &motor, int p, int i, int d, int ff){
    motor.SetP(p);
    motor.SetI(i);
    motor.SetD(d);
    motor.SetFF(ff);
} */

//adjusts for the deadzone and converts joystick input to velocity values
void DriveSubsystem::teleopControl(RobotData &robotData){
    if(robotData.pLYStick <= -.08 || robotData.pLYStick >= .08){
            lDrive = robotData.pLYStick*5650;
        } else {
            lDrive = 0;
        }
        if(robotData.pRYStick <= -.08 || robotData.pRYStick >= .08){
            rDrive = robotData.pRYStick*5650;
        } else {
            rDrive = 0;
        }
}

void DriveSubsystem::setDrive(RobotData &robotData)
{
    

    //velocity goes from -5650 to 5650, joystick inputs go from -1 to 1
    dbLMPID.SetReference(lDrive, rev::ControlType::kVelocity);
    dbRMPID.SetReference(rDrive, rev::ControlType::kVelocity);

    /* frc::SmartDashboard::PutNumber("js input left" , robotData.pLYStick);
    frc::SmartDashboard::PutNumber("set velocity left" , lDrive);
    frc::SmartDashboard::PutNumber("js input right" , robotData.pRYStick);
    frc::SmartDashboard::PutNumber("set velocity right" , rDrive); */
    
    
}


//this function is currently written so that the robot tries to stay at an angle of zero
void DriveSubsystem::courseCorrectedDrive(RobotData &robotData){
    //if left is behind right / if robotAngle (non continuous) is between 180 and 360
        //give speed to left side + vice versa
        double setPoint;

        if(robotData.robotAngle > 180){
            setPoint = (360-robotData.robotAngle) * 30;
        } else {
            setPoint = 0;
        }
        
        dbLMPID.SetReference(setPoint, rev::ControlType::kVelocity);
    
    
}




// auton functions:

//sets drive velocity values to 0
void DriveSubsystem::potato(RobotData &robotData)
{
    lDrive = 0;
    rDrive = 0;

}

//initializes the driveForward process
//you need to set a desired distance beforehand
void DriveSubsystem::initDriveForward(RobotData &robotData)
{
    robotData.initialLDBPos = robotData.currentLDBPos;
    robotData.initialRDBPos = robotData.currentRDBPos;
    wpi::outs() << "initDriveForward" << '\n';
    robotData.autonStep++;
}

//drives the robot backwards
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

    /* if (lDistLeft > (robotData.desiredDBDist * 0.2)) {
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
    } */


    if (lDistLeft > 0) {
        if(lDistLeft * 170 < 5000){
            lDrive = lDistLeft * 170;
        } else {
            lDrive = 5000;
        }
    } else {
        lDrive = 0;
    }

    

    if (rDistLeft > 0){
        if(rDistLeft * 170 < 5000){
            rDrive = rDistLeft * 170;
        } else {
            rDrive = 5000;
        }
    } else {
        rDrive = 0;
    }

    /* if (lDistLeft <= (robotData.desiredDBDist * 0.03) && (rDistLeft <= (robotData.desiredDBDist * 0.03))) {
        wpi::outs() << "FINISHED DRIVE_FORWARD" << '\n';
        robotData.autonStep++;
    } */

    if (lDistLeft <= .5 && (rDistLeft <= .5)) {
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
    
    /* if (angleLeft < -20)
    {
        // 0.3 for now because we can
        robotData.pLYStick = 0.55 * robotData.sideRatio;
        robotData.pRYStick = 0.55;
    }
    else if (angleLeft < -10)
    {
        robotData.pLYStick = 0.1 * robotData.sideRatio;
        robotData.pRYStick = 0.1;
    }
    else if (angleLeft < -2)
    {
        robotData.pLYStick = 0.07 * robotData.sideRatio;
        robotData.pRYStick = 0.07;
    }
    
    else if (angleLeft > 20)
    {
        // 0.3 for now because we can
        robotData.pLYStick = 0.55;
        robotData.pRYStick = 0.55 * robotData.sideRatio;
    }
    else if (angleLeft > 10)
    {
        robotData.pLYStick = 0.1;
        robotData.pRYStick = 0.1 * robotData.sideRatio;
    }
    else if (angleLeft > 2)
    {
        robotData.pLYStick = 0.07;
        robotData.pRYStick = 0.07 * robotData.sideRatio;
    }
    
    else {
        // you done gud
        robotData.pLYStick = 0;
        robotData.pRYStick = 0;
        robotData.autonStep++;
        wpi::outs() << "FINISHED ARC" << '\n';
    } */

    if (angleLeft < -1){
        lDrive = -80 * angleLeft * robotData.sideRatio;
        rDrive = -80 * angleLeft;
    } else if (angleLeft > 1){
        lDrive = 80 * angleLeft;
        rDrive = 80 * angleLeft * robotData.sideRatio;
    } else {
        lDrive = 0;
        rDrive = 0;
        robotData.autonStep++;
        wpi::outs() << "FINISHED ARC" << '\n';
    }

}

void DriveSubsystem::turnInPlace(RobotData &robotData){

    //for radius = -1

    double angleLeft = robotData.desiredAngleDiff - (robotData.rawAngle - robotData.initialAngle);
    // double angleLeft = robotData.finalAngle - robotData.rawAngle;
    frc::SmartDashboard::PutNumber("angleLeft", angleLeft);

    wpi::outs() << "turn in place" << '\n';

    if (angleLeft < -1){
        lDrive = -100 * angleLeft * robotData.sideRatio;
        rDrive = -100 * angleLeft;
    } else if (angleLeft > 1){
        lDrive = 100 * angleLeft;
        rDrive = 100 * angleLeft * robotData.sideRatio;
    } else {
        lDrive = 0;
        rDrive = 0;
        robotData.autonStep++;
        wpi::outs() << "FINISHED TURN IN PLACE" << '\n';
    }

}