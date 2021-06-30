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
    return ((-0.000729167*std::pow(x,4.0))+(.0186908*std::pow(x,3.0))+(-0.0374669*std::pow(x,2.0))+(-2.01681*x) + 78.2293)+3;
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


/**
 * @param verticalOffset y offset from limelight
 * @return needed pipeline based off how close to the target the bot is
 * 
 * pipeline 0 = off
 * pipeline 1 = 40 power
 * pipeline 2 = 60 power
 * pipeline 3 = 80 power
 * pipeline 4 = 100 power
 */
int LimelightSubsystem::getPipeline(double verticalOffset){

    int pipeline;
    if(verticalOffset > 14){
        pipeline = 1;
    }else if(verticalOffset > 9){
        pipeline = 2;
    }else if(verticalOffset > 6){
        pipeline = 3;
    }else if(verticalOffset > 1){
        pipeline = 4;
    }else{
        pipeline = 1;

    }

    //basically if you can see the target turn on the limelight otherwise don't

    return pipeline;
}


void LimelightSubsystem::Periodic(RobotData &robotData){
   
   std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //opens up the networktable

    robotData.xOffset = getHorizontalOffset();
    robotData.yOffset = getVerticalOffset();
    robotData.calcHoodPos = calcHoodPOS(robotData.yOffset);
    

    if(robotData.manualMode){
        if(robotData.limelightOn){
            table->PutNumber("pipeline", getPipeline(robotData.yOffset));        
        }else{
            table->PutNumber("pipeline", 0);
        }
    }else{
        table->PutNumber("pipeline", getPipeline(robotData.yOffset));        

    }

    
    //prints all the values to dashboard:
    frc::SmartDashboard::PutNumber("tx",  table->GetNumber("tx",0.0)); //horizontal offset
    frc::SmartDashboard::PutNumber("ty",  table->GetNumber("ty",0.0)); //vertical offset
    frc::SmartDashboard::PutNumber("ts",  table->GetNumber("ts",0.0)); //skew offset
    frc::SmartDashboard::PutNumber("tv",  table->GetNumber("tv",0.0)); //valid target

    robotData.validTarget = table->GetNumber("tv", 0.0);
    //if the button to shoot is pressed, turn on the limelight led
    // if(robotData.shootingMode){
    //     table->PutNumber("pipeline", getPipeline(robotData.yOffset)); //set the pipeline based on y offset
    // }else{
    //     table->PutNumber("pipeline",0); //set the limelight to off
    // }

}