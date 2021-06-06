#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Auto.h"


void Auto::Init(){
    

}

void Auto::Periodic(frc::Joystick &sStick, IndexerSubsystem &index, ShooterSubsystem &shooter, IntakeSubsystem &intake){
    //intake
    if(sStick.GetRawButton(4)){
        intake.setPiston(true);
        intake.setIntakeWheels(0.2);
        index.SetSide(0.2);
    }else{
        intake.setPiston(false);
        intake.setIntakeWheels(0);
        index.SetSpinner(0);
        index.SetSide(0);
    }

    //shooter
    secondaryPOVArrayInput = sStick.GetPOV(0);
    
    //shooting from the line
    if (secondaryPOVArrayInput == 90){
        if (shooter.getHoodPos() > 12.5){
            shooter.setHood(-0.15);
        } else if (shooter.getHoodPos() < 10.5){
            shooter.setHood(0.15);
        } else {
            shooter.setHood(0);
        }

        if (shooter.getHoodPos() > 10.5 && shooter.getHoodPos() < 12.5){
            index.SetSpinner(0.5); //change speed need faster 
            index.SetSide(0.5);
            if (shooter.getWheelVel() > 2900 && shooter.getWheelVel() < 3150){
                shooter.setWheel(0.74);

            } else if (shooter.getWheelPos() > 3150){
                shooter.setWheel(0.74);
            } else if (shooter.getWheelPos() > 1750){
                shooter.setWheel(0.74);
            } else{
                shooter.setWheel(0.74);
            }
            if (index.getSpinnerVel() > 2850 && index.getSpinnerVel() < 3150){
                index.SetSpinner(0.65);
                index.SetSide(0.65*sideWheelDirection); //
            } else if (index.getSpinnerVel() > 3150){
                index.SetSpinner(0.63);
                index.SetSide(0.63*sideWheelDirection);
            } else if (index.getSpinnerVel() > 1750){
                index.SetSpinner(0.69);
                index.SetSide(0.69*sideWheelDirection);
            } else{
                index.SetSpinner(0.76);
                index.SetSide(0.76*sideWheelDirection);
            }
        }
        if (shooter.getWheelVel() > 2900 && shooter.getWheelVel() < 3150){
            sideWheelDirection = -1;
        }else{
            sideWheelDirection = 1;
        }
    //Automatic shooting (secondary)
    } else if (secondaryPOVArrayInput == 0){
        if (shooter.getHoodPos() > 12.5){
            shooter.setHood(-0.15);
        } else if (shooter.getHoodPos() < 10.5){
            shooter.setHood(0.15);
        } else {
            shooter.setHood(0);
        }

        if (shooter.getHoodPos() > 10.5 && shooter.getHoodPos() < 12.5){
            index.SetSpinner(0.5); //change speed need faster 
            index.SetSide(0.5);
            if (shooter.getWheelVel() > 2900 && shooter.getWheelVel() < 3150){
                shooter.setWheel(0.74);

            } else if (shooter.getWheelPos() > 3150){
                shooter.setWheel(0.74);
            } else if (shooter.getWheelPos() > 1750){
                shooter.setWheel(0.74);
            } else{
                shooter.setWheel(0.74);
            }
            if (index.getSpinnerVel() > 2850 && index.getSpinnerVel() < 3150){
                index.SetSpinner(0.65);
                index.SetSide(0.65*sideWheelDirection); //
            } else if (index.getSpinnerVel() > 3150){
                index.SetSpinner(0.63);
                index.SetSide(0.63*sideWheelDirection);
            } else if (index.getSpinnerVel() > 1750){
                index.SetSpinner(0.69);
                index.SetSide(0.69*sideWheelDirection);
            } else{
                index.SetSpinner(0.76);
                index.SetSide(0.76*sideWheelDirection);
            }
        }
        if (shooter.getWheelVel() > 2900 && shooter.getWheelVel() < 3150){
            sideWheelDirection = -1;
        }else{
            sideWheelDirection = 1;
        }
        
    //Not shooting
    } else if (secondaryPOVArrayInput == -1){
        shooter.setWheel(0);
        index.SetSpinner(0);
        index.SetSide(0);
        if (shooter.getHoodPos() > .5){
            shooter.setHood(-0.05);
        } else if (shooter.getHoodPos() < -.5) {
            shooter.setHood(0.05);
        } else {
            shooter.setHood(0);
        }
        if (shooter.getTurretPos() > .5){
            shooter.setTurret(-0.05);
        } else if (shooter.getTurretPos() < -.5) {
           shooter.setTurret(0.05);
        } else {
            shooter.setTurret(0);
        }
        
        
    }
    

}
