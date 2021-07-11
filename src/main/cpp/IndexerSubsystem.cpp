#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>


void IndexerSubsystem::RobotInit(){
    centerSpindle.RestoreFactoryDefaults();
    centerSpindle.SetInverted(false);
    centerSpindle.SetInverted(true);

    centerSpindle.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    centerSpindle.SetSmartCurrentLimit(45);
}


void IndexerSubsystem::Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData){
    if(!robotData.climbMode){
        if(robotData.manualMode){
            manualMode(robotData);
        } else {
            semiAutoMode(robotData);
        }
    }else{
        setOmniWheel(0);
        setCenterSpindle(0);
    }
    

    updateDiagnostics(diagnosticsData);

}

void IndexerSubsystem::semiAutoMode(RobotData &robotData){

    //if shooting
    if(robotData.shootingMode){

        //if the limelight can see a target
        if(robotData.targetValue != 0){

            //retrieve data from shooter for when shooting wheel is up to speed etc.
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

        if(robotData.sRTrigger){ //when intaking balls, spin the indexer
            setOmniWheel(0.15);
            setCenterSpindle(0.1);
        }else {
            setOmniWheel(0);
            setCenterSpindle(0);
        }

    }
}

void IndexerSubsystem::manualMode(RobotData &robotData){
    //if you're using the shift button reverse the indexer
    if(robotData.shift){
        if(robotData.sABtn){
            setCenterSpindle(-0.2);
            setOmniWheel(-0.2);
        }else if(robotData.sLTrigger){ //takes ball out of shooter?
            setCenterSpindle(-robotData.sLTrigger);
            setOmniWheel(robotData.sLTrigger); 
        }else{
            setOmniWheel(0);
            setCenterSpindle(0);
        }
    }else{ 
        //otherwise run the indexer based on trigger power
        setCenterSpindle(robotData.sLTrigger);
        setOmniWheel(robotData.sLTrigger);

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

void IndexerSubsystem::DisabledInit(){
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