#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Manual.h"

//extern bool MANUAL;


void Manual::Init(){
    
}

//indexes are correct, speeds are not. 
//this code has not been testsed on neowise
void Manual::Periodic(Controller &control, frc::Joystick &sStick, IndexerSubsystem &index, ShooterSubsystem &shooter, IntakeSubsystem &intake){
    int shift = control.getShiftFactor();
    
    if(sStick.GetRawAxis(3) > .5){
        intake.setPiston(true);
    } else {
        intake.setPiston(false);
    }

    if(sStick.GetRawButton(6)){
        intake.setIntakeWheels(shift*.3);
    } else {
        intake.setIntakeWheels(0);

    }

    if(sStick.GetRawAxis(2) > .5){
        index.SetSpinner(.5*shift);
    } else {
        if(control.shootingMode()){
            index.SetSpinner(.5);
            index.SetSide(.5);
        }
    }
}
