#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "IntakeSubsystem.h"



void IntakeSubsystem::Init(){
    
    rollers.RestoreFactoryDefaults();
    rollers.SetInverted(true);
    rollers.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    rollers.SetSmartCurrentLimit(45);
    setPiston(false);

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
    //tananya thought: as long as you're not shooting you can choose whether or not to intake balls
    if (shootPOV == robotData.shootingBtn){
        setPiston(true);
        //manualMode(robotData);

    } else {

        //Intake balls
        if(robotData.sABtn){
            if(!getPiston()){ //if the piston is up put it down
                setPiston(true);
            }
            setIntakeRollers(-0.4);
        }else{ //don't intake balls
            if(getPiston()){ //if the piston is down put it up
                setPiston(false);
            }
            setIntakeRollers(0);
        }


    }

    
}

void IntakeSubsystem::manualMode(RobotData &robotData){

    if(robotData.sXBtn){
        if(!getPiston()){ //if the piston is up put it down
            setPiston(true);
        }
    }else{
        if(getPiston()){ //if the piston is down put it up
            setPiston(false);
        }
    }

    //if the shift is pressed reverse the intake roller
    if(robotData.shift){
        if(robotData.sYBtn){
            setIntakeRollers(0.3);
        } else {
            setIntakeRollers(0);
        }

    //else run the intake roller
    }else{
        if(robotData.sYBtn){
            setIntakeRollers(-0.3);
        } else {
            setIntakeRollers(0);
        }
    }
   

}


void IntakeSubsystem::setPiston(bool direction){  
    if (direction){
        solenoidOne.Set(true);
    } else {
        solenoidOne.Set(false);
    }
    
}

bool IntakeSubsystem::getPiston(){
    if(solenoidOne.Get() == true){
        return true;
    }else{
        return false;
    }
}

void IntakeSubsystem::setIntakeRollers(double power){
    rollers.Set(power);
}


