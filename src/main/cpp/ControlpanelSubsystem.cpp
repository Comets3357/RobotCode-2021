#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>


void ControlpanelSubsystem::Init(){

    cpManipulator.RestoreFactoryDefaults();
    //we inverted the right side and set motors to follow each other
    cpManipulator.SetInverted(false);

    cpManipulator.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    cpManipulator.SetSmartCurrentLimit(45);

    cpManipulator.Set(0);

}

void ControlpanelSubsystem::Periodic(RobotData &robotData){
    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

} 

void ControlpanelSubsystem::semiAutoMode(RobotData &robotData){

    /**
     * use the color sensor to find the color
     * 
     * cpManipulator.Set(0.2);
     * 
     * 
     * 
     * 
     */

}

void ControlpanelSubsystem::manualMode(RobotData &robotData){ 
    if(robotData.shift && robotData.sRBumper){
        cpManipulator.Set(0.2);
    }
}

void ControlpanelSubsystem::Disabled(){
    cpManipulator.Set(0);

}

