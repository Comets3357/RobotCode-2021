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

void IndexerSubsystem::Periodic(RobotData &robotData){
    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

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
        indexerBelt.Set(-0.3);
    }

}
void IndexerSubsystem::Reset(){
    indexerBeltPOS.SetPosition(0);
}

double IndexerSubsystem::getPOS(){
    return indexerBeltPOS.GetPosition();

}

bool IndexerSubsystem::getGoBack(){
    return goBack;
}

bool IndexerSubsystem::IntakeRun(){
    return intakeRun;
}
//returns GoBack(if the balls are being pushed out of the intake)
void IndexerSubsystem::setGoBack(bool GoBack){
    goBack = GoBack;
}

void IndexerSubsystem::Periodic(frc::Joystick &sStick){
    if (!goBack){
        if (!indexSensor.Get() || !indexSensor2.Get()){
            if (powerCells <= 3){
                indexerBelt.Set(.36);
                if (!ballIn){
                    powerCells += 1;
                }
                ballIn = true;
            } else if (powerCells == 3 && ball3 == 2){
                ball4 = true;
                intakeRun = false;
                powerCells += 1;
            // indexerBelt.Set(sStick.GetRawAxis(1));
            } else if (powerCells == 4 && ball4 == 2){
                powerCells += 1;
                ball5 = true;
                intakeRun = false;

            }

            
            
            

        } else if (powerCells == 3 && ball3 == 0 && !ballIn){
                ball3 = 1;
                indexerBeltPOS.SetPosition(0);
                intakeRun = false;

        }else{

        
            indexerBelt.Set(sStick.GetRawAxis(1));
            ballIn = false;
        }
    }
    //sets the goback variable
    if (sStick.GetRawButton(4)){
        goBack = true;
    } else if (sStick.GetRawButton(2)){
        goBack = false;
    }

    
    




    //this section of the code controls the pivot
    //currently plainly manual
    frc::SmartDashboard::PutNumber("powercells", powerCells);
    frc::SmartDashboard::PutNumber("indexer sensor",indexSensor.Get());


}