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
    //setPiston(true);
}


void IntakeSubsystem::semiAutoMode(RobotData &robotData){

    shootPOV = robotData.sDPad;

    //if in shooting mode then you want manual control of the intake
    if (shootPOV == robotData.shootingBtn){
        setPiston(true);
        //manualMode(robotData);

    } else {
        //Intake balls
        if(robotData.sABtn){
            if(!getPiston()){ //if the piston is up put it down
                setPiston(true);
            }
            setIntakeRollers((robotData.Rdrive+robotData.Ldrive)/2);
        }else{
            if(getPiston()){ //if the piston is down put it up
                setPiston(false);
            }
            setIntakeRollers(0);
        }


    }

    
}

void IntakeSubsystem::manualMode(RobotData &robotData){

    if(robotData.sXBtn){ //if the piston is extended take it in, if its in take it out
        setPiston(!getPiston());
    }

    //if the shift is pressed reverse the intake roller
    if(robotData.shift){
        if(robotData.sYBtn){
            setIntakeRollers((robotData.Rdrive+robotData.Ldrive)/2);
        } else {
            setIntakeRollers(0);
        }

    //else run the intake roller
    }else{
        if(robotData.sYBtn){
            setIntakeRollers((robotData.Rdrive+robotData.Ldrive)/2);
        } else {
            setIntakeRollers(0);
        }
    }
   

}

/**
 * @param direction true is retracted and false is extended
 */

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

void IntakeSubsystem::setIntakeRollers(double avgDrive){

    double pow = -0.4;

    if(avgDrive > 0.7){
        pow = -0.8;
    }else if(avgDrive > 0.6){
        pow = -0.7;
    }else if(avgDrive > 0.5){
        pow = -0.6;
    }else if(avgDrive > 0.4){
        pow = -0.5;
    }else{
        pow = -0.4;
    }
    rollers.Set(pow);
}

void IntakeSubsystem::Disabled(){
    setIntakeRollers(0);
    setPiston(false);
}



