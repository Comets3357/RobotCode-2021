#include <frc/smartdashboard/Smartdashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "Robot.h"
#include <cmath>


//web interface: http://10.33.57.16:5801/ 



void LimelightSubsystem::Init(){}

/**
 * calculates hood position needed 
 * @param verticalOffset vertical offset from the target from limelight in degrees
 * @return desired encoder position of Shooter Hood
 */
double LimelightSubsystem::calcHoodPOS(double verticalOffset){ 
    //currently should be changed, equation isn't working. 
    double x = verticalOffset;
    //return ((-0.000113724*std::pow(x,4.0))+(0.00324167*std::pow(x,3.0))+(-0.0268368*std::pow(x,2.0))+(0.-0.092227*x) + 15.058);
    //return ((-0.000112298*std::pow(x,4.0))+(.00325782*std::pow(x,3.0))+(-0.0251726*std::pow(x,2.0))+(-0.178706*x) + 15.7186);
    return ((-0.0000680977*std::pow(x,4.0))+(.00141765*std::pow(x,3.0))+(-0.00521063*std::pow(x,2.0))+(-0.170811*x) + 15.1117);
    //return ((-0.000211515*std::pow(x,4.0))+(0.00824168*std::pow(x,3.0))+(-0.110289*std::pow(x,2.0))+(0.385964*x) + 14.5673);
}

/**
 * @return horizontal offset angle from limelight
 */
double LimelightSubsystem::getHorizontalOffset(){
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the table
    return table->GetNumber("tx",0.0);
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




