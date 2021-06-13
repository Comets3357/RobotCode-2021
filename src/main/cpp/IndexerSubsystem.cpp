#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

void IndexerSubsystem::Init(){
    centerSpindle.RestoreFactoryDefaults();
    centerSpindle.SetInverted(false);
    centerSpindle.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    centerSpindle.SetSmartCurrentLimit(45);
}
//only setting power when needed according to shooter file
//not much more is needed since we'll have to change everything for the spindexer

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
    frc::SmartDashboard::PutNumber("spinner",  robotData.sRYStick);

    if(shootPOV == 0){

        if(robotData.readyShoot){
            setOmniWheel(-0.6);
        } else {
            setOmniWheel(0.3);
        }
    } else if (shootPOV == -1){

        // setSpinner(0);
        // setOmni(0);

    } else {

        if(robotData.sYBtn){
            setOmniWheel(0.2);
            setCenterSpindle(0.2);
        } else {
            setOmniWheel(0);
            setCenterSpindle(0);
        }

        frc::SmartDashboard::PutNumber("side", robotData.sLYStick);
        frc::SmartDashboard::PutNumber("spinner",  robotData.sRYStick);

        if(robotData.sLBumper){
            // setOmni(robotData.sLYStick);
            // setSpinner(robotData.sRYStick);
        } else if (robotData.sLBumper){
            // setOmni(0);
            // setSpinner(0);
        }
    }

}

void IndexerSubsystem::manualMode(RobotData &robotData){
    if(robotData.sRTrigger > 0.5){
        setCenterSpindle(.5 * robotData.shift);
    } else {
        if(robotData.shootingMode){
            setCenterSpindle(.5);
            setOmniWheel(.5);
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

    diagnosticsData.mControlCurrents.at(12) = centerSpindle.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(12) = centerSpindle.GetBusVoltage();
    diagnosticsData.mControlTemps.at(12) = centerSpindle.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(12) = centerSpindlePOS.GetPosition();
    diagnosticsData.mControlVelocities.at(12) = centerSpindlePOS.GetVelocity();
}