#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>


void IndexerSubsystem::Init(){
    centerSpindle.RestoreFactoryDefaults();
    centerSpindle.SetInverted(false);
    centerSpindle.SetInverted(true);

    centerSpindle.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    centerSpindle.SetSmartCurrentLimit(45);
    frc::SmartDashboard::PutNumber("Set Speed", 0);

}


void IndexerSubsystem::Periodic(RobotData &robotData){
    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

}

void IndexerSubsystem::semiAutoMode(RobotData &robotData){

    shootPOV = robotData.sDPad;

    //if shooting
    if(shootPOV == robotData.shootingBtn){

        //set indexer to set spe
    
        //retrieve data from shooter for when shooting wheel is up to speed
        if(robotData.readyShoot){
            setCenterSpindle(0.47);

            //reverse direction for omniwheel to bring balls into shooter
            setOmniWheel(-0.7);
        }else{  
            setOmniWheel(0.3);
            setCenterSpindle(0.47);
        }


    }else{

        if(robotData.sABtn){ //when intaking balls, spin the indexer
            setOmniWheel(0.1);
            setCenterSpindle(0.075);
        }else {
            setOmniWheel(0);
            setCenterSpindle(0);
        }

    }
}

void IndexerSubsystem::manualMode(RobotData &robotData){ 
    double speed = frc::SmartDashboard::GetNumber("Set Speed", 0);
    //^^^ for setting speed after deployed


    //if you're using the shift button reverse the indexer
    if(robotData.shift){
        if(robotData.sABtn){
            setCenterSpindle(-0.1);
            setOmniWheel(-0.1);
        } else {
            setOmniWheel(0);
            setCenterSpindle(0);
        }
    //otherwise run the indexer
    }else{
       if(robotData.sABtn){
            setCenterSpindle(0.1);
            setOmniWheel(0.1);
        } else {
            setOmniWheel(0);
            setCenterSpindle(0);
        } 
    }
    
}



void IndexerSubsystem::setCenterSpindle(double power){

    centerSpindle.Set(power);
}

void IndexerSubsystem::setOmniWheel(double power){
    omniWheel.Set(power);
}

double IndexerSubsystem::getSpinnerVel(){
    return centerSpindlePOS.GetVelocity();
}

// void IndexerSubsystem::Disabled(){
//     setOmniWheel(0);
//     setCenterSpindle(0);
// }





