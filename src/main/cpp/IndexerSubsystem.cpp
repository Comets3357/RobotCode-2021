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


void IndexerSubsystem::Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData){
    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

    updateDiagnostics(diagnosticsData);

}

void IndexerSubsystem::semiAutoMode(RobotData &robotData){

    shootPOV = robotData.sDPad;

    //if shooting
    if(shootPOV == robotData.shootingBtn){

        //set indexer to set speed
        if(robotData.targetValue != 0){
            //retrieve data from shooter for when shooting wheel is up to speed
            if(robotData.readyShoot){
                setCenterSpindle(0.47);

                //reverse direction for omniwheel to bring balls into shooter
                setOmniWheel(-0.7);
            }else{  
                setOmniWheel(0.3);
                setCenterSpindle(0.47);
            }
        }   
        


    }else{

        if(robotData.sABtn){ //when intaking balls, spin the indexer
            setOmniWheel(0.15);
            setCenterSpindle(0.1);
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
        if(robotData.sLTrigger){
            setCenterSpindle(-robotData.sRTrigger);
            setOmniWheel(robotData.sRTrigger);
        }else if(robotData.sABtn){
            setCenterSpindle(-0.2);
            setOmniWheel(-0.2);
        } else {
            setOmniWheel(0);
            setCenterSpindle(0);
        }
    //otherwise run the indexer
    }else{ 
        setCenterSpindle(robotData.sRTrigger);
        setOmniWheel(robotData.sRTrigger);
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

void IndexerSubsystem::Disabled(){
    setOmniWheel(0);
    setCenterSpindle(0);
}





void IndexerSubsystem::updateDiagnostics(DiagnosticsData &diagnosticsData)
{
    /**
     * center spindle/kick 11
     * omni wheel 12
     * 
     * center spindle encoder
     * omni wheel encoder
     */

    diagnosticsData.mControlCurrents.at(11) = centerSpindle.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(11) = centerSpindle.GetBusVoltage();
    diagnosticsData.mControlTemps.at(11) = centerSpindle.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(11) = centerSpindlePOS.GetPosition();
    diagnosticsData.mControlVelocities.at(11) = centerSpindlePOS.GetVelocity();

    diagnosticsData.mControlFaults.at(11) = centerSpindle.GetFaults();

    diagnosticsData.mControlCurrents.at(12) = omniWheel.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(12) = omniWheel.GetBusVoltage();
    diagnosticsData.mControlTemps.at(12) = omniWheel.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(12) = omniWheelPOS.GetPosition();
    diagnosticsData.mControlVelocities.at(12) = omniWheelPOS.GetVelocity();

    diagnosticsData.mControlFaults.at(12) = omniWheel.GetFaults();
}