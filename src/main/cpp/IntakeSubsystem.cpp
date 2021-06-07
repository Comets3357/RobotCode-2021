#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "IntakeSubsystem.h"



void IntakeSubsystem::Init(){

    rollers.RestoreFactoryDefaults();
    rollers.SetInverted(true);
    rollers.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    rollers.SetSmartCurrentLimit(45);

}

void IntakeSubsystem::Periodic(RobotData &robotData){
    //decide if in manual mode or auto mode
    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }
}


void IntakeSubsystem::semiAutoMode(RobotData &robotData){

    shootPOV = robotData.sDPad;

    //if in shooting mode then you want manual control of the intake
    if (shootPOV == robotData.shootingButton){
        manualMode(robotData);

    } else {

        //Intake balls
        if(robotData.sABtn){
            if(getPiston()){ //if the piston is up put it down
                setPiston(false);
            }
            setIntakeRollers(-0.4);
        }else{
            if(!getPiston()){ //if the piston is down put it up
                setPiston(true);
            }
            setIntakeRollers(0);
        }

        // if(robotData.sLBumper){ //in
        //     setPiston(true);

        // }else if(robotData.sRBumper){ //out (reverse is out)
        //     setPiston(false);
        // }

    }

    
}

void IntakeSubsystem::manualMode(RobotData &robotData){

    if(robotData.sRBumper){
        setPiston(true);
    } else if(robotData.sLBumper){
        setPiston(false);
    }

    if(robotData.sYBtn){
        setIntakeRollers(0.3);
    } else {
        setIntakeRollers(0);
    }

}

/**
 * @param direction true is retracted and false is extended
 */

void IntakeSubsystem::setPiston(bool direction){  
    if (direction){
        solenoidOne.Set(frc::DoubleSolenoid::Value::kForward);
    } else {
        solenoidOne.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    
}

bool IntakeSubsystem::getPiston(){
    if(solenoidOne.Get() == frc::DoubleSolenoid::Value::kForward){
        return true;
    }else{
        return false;
    }
}

void IntakeSubsystem::setIntakeRollers(double power){
    rollers.Set(power);
}



