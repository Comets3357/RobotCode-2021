#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void IndexerSubsystem::Init(){
    centerSpindle.RestoreFactoryDefaults();
    centerSpindle.SetInverted(false);
    centerSpindle.SetInverted(true);

    centerSpindle.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    centerSpindle.SetSmartCurrentLimit(45);
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
    if(shootPOV == robotData.shootingButton){

        //set indexer to set speed 
        setOmniWheel(0.4);
        setCenterSpindle(0.3);

        //retrieve data from shooter for when shooting wheel is up to speed
        if(robotData.readyShoot){
            //reverse direction for omniwheel to bring balls into shooter
            setOmniWheel(-0.7);
        }else{
            setOmniWheel(0.4);
        }


    }else{

        if(robotData.sABtn){ //when intaking balls, spin the indexer
            setOmniWheel(0.3);
            setCenterSpindle(0.2);
        }else {
            setOmniWheel(0);
            setCenterSpindle(0);
        }
    }
}

void IndexerSubsystem::manualMode(RobotData &robotData){ 
    if(robotData.sABtn){
        setCenterSpindle(.2);
        setOmniWheel(0.3);
    } else {
        setOmniWheel(0);
        setCenterSpindle(0);
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


