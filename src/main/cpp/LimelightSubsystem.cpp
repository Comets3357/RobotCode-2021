#include <frc/smartdashboard/Smartdashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "Robot.h"
#include <cmath>


//web interface: http://limelight:5801/ 



void LimelightSubsystem::Init(){}

/**
 * calculates hood position needed 
 * @param verticalOffset vertical offset from the target from limelight in degrees
 * @return desired encoder position of Shooter Hood
 */
double LimelightSubsystem::calcHoodPOS(double verticalOffset){ 
    double x = verticalOffset;
    return ((-0.000729167*std::pow(x,4.0))+(.0186908*std::pow(x,3.0))+(-0.0374669*std::pow(x,2.0))+(-2.01681*x) + 78.2293);
}

/**
 * @return horizontal offset angle from limelight
 */
double LimelightSubsystem::getHorizontalOffset(){
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the table
    return (table->GetNumber("tx",0.0)) + 0.5; //offset
}

/**
 * @return vertical offset angle from limelight
 */
double LimelightSubsystem::getVerticalOffset(){
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the table
    return table->GetNumber("ty",0.0);
}


void LimelightSubsystem::Periodic(RobotData &robotData){

    robotData.xOffset = getHorizontalOffset();
    robotData.yOffset = getVerticalOffset();
    robotData.calcHoodPos = calcHoodPOS(robotData.yOffset);

    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the networktable
    table->PutNumber("pipeline", 0); //set the pipeline

}




