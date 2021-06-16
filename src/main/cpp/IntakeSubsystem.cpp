#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "IntakeSubsystem.h"



void IntakeSubsystem::Init(){
    //just the basics to start off
    rollers.RestoreFactoryDefaults();
    rollers.SetInverted(true);
    rollers.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

/*  intakePivot_pidController.SetP(pkP);
    intakePivot_pidController.SetI(pkI);
    intakePivot_pidController.SetD(pkD);
    intakePivot_pidController.SetIZone(pkIz);
    intakePivot_pidController.SetFF(pkFF);
    intakePivot_pidController.SetOutputRange(pkMinOutput, pkMaxOutput);

    wheels_pidController.SetP(wkP);
    wheels_pidController.SetI(wkI);
    wheels_pidController.SetD(wkD);
    wheels_pidController.SetIZone(wkIz);
    wheels_pidController.SetFF(wkFF);
    wheels_pidController.SetOutputRange(wkMinOutput, wkMaxOutput);
 */

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

    if (shootPOV == 90){

    } else {

        if(robotData.sABtn){
            setIntakeRollers(-0.4);
        }else{
            setIntakeRollers(0);
        }

        if(robotData.sLBumper){ //in
            setPiston(true);
            //setIntakeWheels(0.2);

        }else if(robotData.sRBumper){ //out (reverse is out)
            setPiston(false);
            //setIntakeWheels(0);
        }

    }

    
}

void IntakeSubsystem::manualMode(RobotData &robotData){

    if(robotData.sLTrigger){
        setPiston(true);
    } else {
        setPiston(false);
    }

    if(robotData.sLBumper){
        setIntakeRollers(0.3*robotData.shift);
    } else {
        setIntakeRollers(0);
    }

}


void IntakeSubsystem::setPiston(bool direction){
    if (direction){
        solenoidOne.Set(true);
    } else {
        solenoidOne.Set(false);
    }
    
}

void IntakeSubsystem::setIntakeRollers(double power){
    rollers.Set(power);
}



