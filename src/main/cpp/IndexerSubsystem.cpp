#include "Robot.h"
#include "IndexerSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

void IndexerSubsystem::Init(){
    //just the basics to start off
    centerSpindle.RestoreFactoryDefaults();

    centerSpindle.SetInverted(false);

    centerSpindle.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

    centerSpindle.SetSmartCurrentLimit(45);


}
//only setting power when needed according to shooter file
//not much more is needed since we'll have to change everything for the spindexer

void IndexerSubsystem::SetSpinner(double power){
    centerSpindle.Set(power);
}

void IndexerSubsystem::SetSide(double power){
    sideWheel.Set(power);
}

double IndexerSubsystem::getSpinnerVel(){
    return centerSpindlePOS.GetVelocity();
}
