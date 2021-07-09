#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void DriveSubsystem::Init()
{

    dbLM.RestoreFactoryDefaults();
    dbRM.RestoreFactoryDefaults();

    dbLS.RestoreFactoryDefaults();
    dbRS.RestoreFactoryDefaults();

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

    //used for pid testing
    //rev::CANSparkMaxLowLevel::EnableExternalUSBControl(true);

    dbLMPID.SetP(0.00027);
    dbLMPID.SetI(0);
    dbLMPID.SetD(0.008);
    dbLMPID.SetFF(0.00019);

    dbRMPID.SetP(0.00027);
    dbRMPID.SetI(0);
    dbRMPID.SetD(0.008);
    dbRMPID.SetFF(0.00019);


    //again, used for pid testing
    dbLM.BurnFlash();
    dbRM.BurnFlash();
    dbLS.BurnFlash();
    dbRS.BurnFlash();

    //gyro
    gyro.Calibrate();
    


}

void DriveSubsystem::Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData)
{
    updateData(robotData);

    // frc::SmartDashboard::PutNumber("driveMode", robotData.driveMode);
    // frc::SmartDashboard::PutNumber("GetGyroAngleZ", gyro.GetGyroAngleZ());
    // frc::SmartDashboard::PutNumber("getAngle", gyro.GetAngle());


    //determines how the drivebase will be controlled
    switch (robotData.driveMode)
    {
    case driveMode_teleop:
        teleopControl(robotData);
        break;
    case driveMode_potato:
        potato(robotData);
        setVelocity(robotData);
        break;
    case driveMode_initDriveStraight:
        initDriveStraight(robotData);
        setVelocity(robotData);
        break;
    case driveMode_driveStraight:
        driveStraight(robotData);
        setVelocity(robotData);
        break;
    case driveMode_initArc:
        initArc(robotData);
        setVelocity(robotData);
        break;
    case driveMode_arc:
        turnInPlace(robotData);
        // arc(robotData);
        setVelocity(robotData);
        break;
    default:
        potato(robotData);
        setVelocity(robotData);
        break;
    }

    //updateDiagnostics(diagnosticsData);
}

void DriveSubsystem::Disabled()
{
    dbLM.Set(0);
    dbRM.Set(0);
    dbRM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    dbLM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}



// updates encoder and gyro values
void DriveSubsystem::updateData(RobotData &robotData)
{
    // converts from tank to arcade drive
    double frontBack = cStraight*(robotData.pLYStick + robotData.pRYStick)/2;
    double leftRight = cTurn*(robotData.pRYStick - robotData.pLYStick)/2;

    // we may use arcarde drive for something in the future

    // converts from arcade back to tank drive
    robotData.Rdrive = (frontBack + leftRight);
    robotData.Ldrive = (frontBack - leftRight);



    //add back wheel encoders at some point
    robotData.currentRDBPos = dbRMEncoder.GetPosition();
    robotData.currentLDBPos = dbLMEncoder.GetPosition();

    robotData.LdriveVel = dbRMEncoder.GetVelocity();
    robotData.RdriveVel = dbLMEncoder.GetVelocity();

    // gyro.SetYawAxis(frc::ADIS16448_IMU::IMUAxis::kZ);

    //this is the direction that the robot is facing
    //add negative sign for comp bot, remove for test db
    // robotData.rawAngle = gyro.GetAngle();
    // double tempRobotAngle = gyro.GetAngle();
    robotData.rawAngle = -gyro.GetGyroAngleZ();
    double tempRobotAngle = -gyro.GetGyroAngleZ();

    //calculates the non continuous angle
    while(tempRobotAngle >= 360){
        tempRobotAngle -= 360;
    }
    while(tempRobotAngle <= 0){
        tempRobotAngle += 360;
    }
    robotData.robotAngle = tempRobotAngle;
    
    robotData.robotTiltAngle = gyro.GetGyroAngleX();

    frc::SmartDashboard::PutNumber("CURRENT RAW ANGLE", robotData.rawAngle);
}

// driving functions:

// adjusts for the deadzone and converts joystick input to velocity values for PID
void DriveSubsystem::teleopControl(RobotData &robotData)
{
    // converts from tank to arcade drive
    double frontBack = cStraight*(robotData.pLYStick + robotData.pRYStick)/2;
    double leftRight = cTurn*(robotData.pRYStick - robotData.pLYStick)/2;
    
    //deadzone NOT needed for drone controller
    if(robotData.pLYStick <= -.08 || robotData.pLYStick >= .08){
        lDrive = (frontBack - leftRight);
    } else {
       lDrive = 0;
    }
    if(robotData.pRYStick <= -.08 || robotData.pRYStick >= .08){
        rDrive = (frontBack + leftRight);
    } else {
       rDrive = 0;
    }

    //set as percent vbus
    dbLM.Set(lDrive);
    dbRM.Set(rDrive);

}

// sets the drive base velocity for auton
void DriveSubsystem::setVelocity(RobotData &robotData)
{
    dbLMPID.SetReference(lDrive, rev::ControlType::kVelocity);
    dbRMPID.SetReference(rDrive, rev::ControlType::kVelocity);    
}

// this function is currently written so that the robot tries to stay at an angle of zero
// was only used for pid testing
void DriveSubsystem::courseCorrectedDrive(RobotData &robotData)
{
    //if left is behind right / if robotAngle (non continuous) is between 180 and 360
        //give speed to left side 
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

//initializes the driveStraight process
//you need to set a desired distance beforehand
void DriveSubsystem::initDriveStraight(RobotData &robotData)
{
    robotData.initialLDBPos = robotData.currentLDBPos;
    robotData.initialRDBPos = robotData.currentRDBPos;

    robotData.initialAngle = robotData.rawAngle; //for course correction
    

    //wpi::outs() << "initDriveStraight" << '\n';
    // frc::SmartDashboard::PutNumber("initialLDBPos", robotData.initialLDBPos);
    // frc::SmartDashboard::PutNumber("initialRDBPos", robotData.initialLDBPos);

    robotData.autonStep++;
}

//drives the robot forwards. the intake is the front of the robot
void DriveSubsystem::driveStraight(RobotData &robotData)
{
    // wpi::outs() << "driveStraight" << '\n';
    // double avgCurrentPos = (robotData.currentLDBPos + robotData.currentRDBPos) / 2;
    // frc::SmartDashboard::PutNumber("avgCurrentPos", avgCurrentPos);

    double lDistLeft = robotData.desiredDBDist - (robotData.currentLDBPos - robotData.initialLDBPos);
    double rDistLeft = robotData.desiredDBDist - (robotData.currentRDBPos - robotData.initialRDBPos);

    // frc::SmartDashboard::PutNumber("currentLDBPos", robotData.currentLDBPos);
    // frc::SmartDashboard::PutNumber("currentRDBPos", robotData.currentRDBPos);
    frc::SmartDashboard::PutNumber("lDistLeft", lDistLeft);
    frc::SmartDashboard::PutNumber("rDistLeft", rDistLeft);


    if (robotData.desiredDBDist > 0){
        if(lDistLeft > 0){
            if(lDistLeft * 170 < 5000){
                lDrive = lDistLeft * 170;
            } else {
                lDrive = 5000;
            }
            if (lDrive < 200)
            {
                lDrive = 200;
            }
        } else {
            lDrive = 0;
        }

        if(rDistLeft > 0){
            if(rDistLeft * 170 < 5000){
                rDrive = rDistLeft * 170;
            } else {
                rDrive = 5000;
            } 
            if (rDrive < 200)
            {
                rDrive = 200;
            }
        } else {
            rDrive = 0;
        }

        courseCorrection(true, robotData);

        if (lDistLeft <= .5 && rDistLeft <= .5) {
            robotData.autonStep++;
        }
    } else {
         if(lDistLeft < 0){
            if(lDistLeft * 170 > -5000){
                lDrive = lDistLeft * 170;
            } else {
                lDrive = -5000;
            } 
            if (lDrive > -200)
            {
                lDrive = -200;
            }
        } else {
            lDrive = 0;
        }

        if(rDistLeft < 0){
            if(rDistLeft * 170 > -5000){
                rDrive = rDistLeft * 170;
            } else {
                rDrive = -5000;
            }
            if (rDrive > -200)
            {
                rDrive = -200;
            }
        } else {
            rDrive = 0;
        }

        courseCorrection(false, robotData);

        if (lDistLeft >= -.5 && rDistLeft >= -.5) {
            robotData.autonStep++;
        }
    }


    
}

// you need to set a desiredAngleDiff and arcRadius beforehand
void DriveSubsystem::initArc(RobotData &robotData)
{
    robotData.initialAngle = robotData.rawAngle;
    // sideRatio is the factor to determine the smaller side
    robotData.sideRatio = robotData.arcRadius / (robotData.arcRadius + 2);
    // frc::SmartDashboard::PutNumber("finalAngle", robotData.finalAngle);
    // frc::SmartDashboard::PutNumber("sideRatio", robotData.sideRatio);
    // wpi::outs() << "initArc" << '\n';
    robotData.autonStep++;
}

// THIS DOES NOT WORK
void DriveSubsystem::arc(RobotData &robotData)
{
    //when called record initial angle. calculate final angle by adding the robotData.desiredAngleDiff to it. 

    double angleLeft = robotData.desiredAngleDiff - (robotData.rawAngle - robotData.initialAngle);

    // frc::SmartDashboard::PutNumber("angleLeft", angleLeft);
    // wpi::outs() << "arc" << '\n';

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

// turns the robot in place around its center
void DriveSubsystem::turnInPlace(RobotData &robotData)
{

    //for radius = -1 in arc pretty much
    robotData.angleLeft = robotData.desiredAngleDiff - (robotData.rawAngle - robotData.initialAngle);

    frc::SmartDashboard::PutNumber("current angle", robotData.rawAngle);
    frc::SmartDashboard::PutNumber("angleLeft", robotData.angleLeft);

    if (robotData.angleLeft > 1){
        lDrive = -100 * robotData.angleLeft * robotData.sideRatio;
        rDrive = -100 * robotData.angleLeft;
        wpi::outs() << "turn in place" << '\n';
    } else if (robotData.angleLeft < -1){
        lDrive = 100 * robotData.angleLeft;
        rDrive = 100 * robotData.angleLeft * robotData.sideRatio;
        wpi::outs() << "turn in place" << '\n';
    } else {
        lDrive = 0;
        rDrive = 0;
        robotData.autonStep++;
        // wpi::outs() << "FINISHED TURN IN PLACE" << '\n';
    }

}

/** 
 *  @param angle is the CONTINUOUS angle that you want it to go to
 * 
 */

/* void DriveSubsystem::turnToAngle(RobotData &robotData){
    robotData.initialAngle = robotData.rawAngle;
    robotData.arcRadius = -1;
    robotData.sideRatio = robotData.arcRadius / (robotData.arcRadius + 2);

    robotData.desiredAngleDiff = angle - robotData.initialAngle;

    turnInPlace(robotData);



} */

void DriveSubsystem::courseCorrection(bool isForward, RobotData &robotData){
    
    // if you're going forward 
        // current angle > initial - slow down left side
        // else slow down right side
    // else (going back)
        // current angle > initial - slow down right side
        // else slow down left side

    frc::SmartDashboard::PutNumber("rawAngle", robotData.rawAngle);
    frc::SmartDashboard::PutNumber("intiialAngle", robotData.initialAngle);

    if(isForward){
        if(robotData.rawAngle > robotData.initialAngle){

            if(robotData.rawAngle - robotData.initialAngle > 10){
                lDrive *= .7;
                rDrive *= 1.1;
            } else if(robotData.rawAngle - robotData.initialAngle > 5){
                lDrive *= .8;
                rDrive *= 1.05;
            } else if (robotData.rawAngle - robotData.initialAngle > 2){
                lDrive *= .8;
            } else {
                lDrive *= .9;
            }
        } else if (robotData.rawAngle < robotData.initialAngle) {
            if(robotData.initialAngle - robotData.rawAngle > 10){
                rDrive *= .7;
                lDrive *= 1.1;
            } else if(robotData.rawAngle - robotData.initialAngle > 5){
                rDrive *= .8;
                lDrive *= 1.05;
            } else if (robotData.rawAngle - robotData.initialAngle > 2){
                rDrive *= .8;
            } else {
                rDrive *= .9;
            }
        }
    } else {
        if(robotData.rawAngle > robotData.initialAngle){

            if(robotData.rawAngle - robotData.initialAngle > 10){
                rDrive *= .7;
                lDrive *= 1.1;
            } else if(robotData.rawAngle - robotData.initialAngle > 5){
                rDrive *= .8;
                lDrive *= 1.05;
            } else if (robotData.rawAngle - robotData.initialAngle > 2){
                rDrive *= .8;
            } else {
                rDrive *= .9;
            }
        } else if (robotData.rawAngle < robotData.initialAngle) {
            if(robotData.initialAngle - robotData.rawAngle > 10){
                lDrive *= .7;
                rDrive *= 1.1;
            } else if(robotData.rawAngle - robotData.initialAngle > 5){
                lDrive *= .8;
                rDrive *= 1.05;
            } else if (robotData.rawAngle - robotData.initialAngle > 2){
                lDrive *= .8;
            } else {
                lDrive *= .9;
            }
        }
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
    diagnosticsData.compEnabled = compressor.Enabled();
    diagnosticsData.compPressureSwitchVal = compressor.GetPressureSwitchValue();
    diagnosticsData.compCurrent = compressor.GetCompressorCurrent();

    diagnosticsData.compCurrentHighFault = compressor.GetCompressorCurrentTooHighFault();
    diagnosticsData.compShortedFault = compressor.GetCompressorShortedFault();
    diagnosticsData.compNotConnectedFault = compressor.GetCompressorNotConnectedFault();

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

    diagnosticsData.mControlPositions.at(leftLeadDeviceID) = dbLMEncoder.GetPosition();
    diagnosticsData.mControlPositions.at(rightLeadDeviceID) = dbRMEncoder.GetPosition();
    diagnosticsData.mControlPositions.at(leftFollowDeviceID) = dbLSEncoder.GetPosition();
    diagnosticsData.mControlPositions.at(rightFollowDeviceID) = dbRSEncoder.GetPosition();

    diagnosticsData.mControlVelocities.at(leftLeadDeviceID) = dbLMEncoder.GetVelocity();
    diagnosticsData.mControlVelocities.at(rightLeadDeviceID) = dbRMEncoder.GetVelocity();
    diagnosticsData.mControlVelocities.at(leftFollowDeviceID) = dbLSEncoder.GetVelocity();
    diagnosticsData.mControlVelocities.at(rightFollowDeviceID) = dbRSEncoder.GetVelocity();

    diagnosticsData.mControlFaults.at(leftLeadDeviceID) = dbLM.GetFaults();
    diagnosticsData.mControlFaults.at(rightLeadDeviceID) = dbRM.GetFaults();
    diagnosticsData.mControlFaults.at(leftFollowDeviceID) = dbLS.GetFaults();
    diagnosticsData.mControlFaults.at(rightFollowDeviceID) = dbRS.GetFaults();
}