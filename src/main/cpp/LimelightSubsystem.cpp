#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "Robot.h"
#include <cmath>

//web interface: http://limelight:5801/

void LimelightSubsystem::RobotInit() {}

/**
 * calculates hood position needed 
 * @param verticalOffset vertical offset from the target from limelight in degrees
 * @return desired encoder position of Shooter Hood
 */
double LimelightSubsystem::calcHoodPOS(double verticalOffset, RobotData &robotData)
{
    double x = verticalOffset;

    if (verticalOffset == 0)
    {
        return 0;
    }
    else
    {
        // can't extend hood if above certain db speed
        if (((std::abs(robotData.LdriveVel) + std::abs(robotData.RdriveVel)) / 2) < 600)
        {
            return ((-0.000729167 * std::pow(x, 4.0)) + (.0186908 * std::pow(x, 3.0)) + (-0.0374669 * std::pow(x, 2.0)) + (-2.01681 * x) + 78.2293) + -15 + robotData.roughHood;
        }
        else
        {
            return 0;
        }
    }
}

/**
 * calculates turret position needed 
 * @param horOffset horizontal offset from the target from limelight in degrees
 * @return desired encoder position of Shooter turret
 */
double LimelightSubsystem::calcTurretPOS(double horOffset)
{
    double x = horOffset;
    return (x * 0.144034);
}

/**
 * @return horizontal offset angle from limelight
 */
double LimelightSubsystem::getHorizontalOffset()
{
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the table
    return (table->GetNumber("tx", 0.0)) + 0.5;                                                         //offset
}

/**
 * @return vertical offset angle from limelight
 */
double LimelightSubsystem::getVerticalOffset()
{
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the table
    return table->GetNumber("ty", 0.0);
}

/**
 * @return if a target is seen or not 0 or 1
 */
int LimelightSubsystem::getTarget()
{
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the table
    return table->GetNumber("tv", 0.0);
}

/**
 * @param verticalOffset y offset from limelight
 * @return needed pipeline based off how close to the target the bot is
 * 
 * pipeline 0 = off
 * pipeline 1 = 40 power
 * pipeline 2 = 60 power
 * pipeline 3 = 80 power
 * pipeline 4 = 100 power
 * at indiana below
 * pipline 5 = backup for 1
 * pipeline 6 = backup for 2
 * pipeline 7 = backup for 3
 * pipeline 8 = backup for 4
 */
int LimelightSubsystem::getPipeline(double verticalOffset)
{

    int pipeline;

    if (verticalOffset > 14)
    {
        // pipeline = 1;
        pipeline = 5;
    }
    else if (verticalOffset > 9)
    {
        // pipeline = 2;
        pipeline = 6;
    }
    else if (verticalOffset > 6)
    {
        // pipeline = 3;
        pipeline = 7;
    }
    else if (verticalOffset > 1)
    {
        // pipeline = 4;
        pipeline = 8;
    }
    else
    {
        pipeline = 1;
    }

    //basically if you can see the target turn on the limelight otherwise don't
    return pipeline;
}

void LimelightSubsystem::Periodic(RobotData &robotData)
{

    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the networktable

    //updating data
    robotData.xOffset = getHorizontalOffset();
    robotData.yOffset = getVerticalOffset();
    robotData.targetValue = getTarget();
    robotData.calcHoodPos = calcHoodPOS(robotData.yOffset, robotData);

    robotData.calcTurretPos = calcTurretPOS(robotData.xOffset);
    robotData.validTarget = table->GetNumber("tv", 0.0);

    if (robotData.shootingMode)
    {
        table->PutNumber("pipeline", getPipeline(robotData.yOffset)); //set the pipeline based on y offset
        // frc::SmartDashboard::PutBoolean("shooting", true);
    }
    else
    {
        table->PutNumber("pipeline", 0); //set the limelight to off
        // frc::SmartDashboard::PutBoolean("shooting", false);
    }
}