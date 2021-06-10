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

} 

void ControlpanelSubsystem::Disabled(){
   
}

