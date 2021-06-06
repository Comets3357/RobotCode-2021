#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "IntakeSubsystem.h"



void IntakeSubsystem::Init(){
    //just the basics to start off
    wheels.RestoreFactoryDefaults();

    wheels.SetInverted(true);

    wheels.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

/*     intakePivot_pidController.SetP(pkP);
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

    wheels.SetSmartCurrentLimit(45);



}

void IntakeSubsystem::setPiston(bool direction){
    if (direction){
        solenoidOne.Set(frc::DoubleSolenoid::Value::kForward);
    } else {
        solenoidOne.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    
}

void IntakeSubsystem::setIntakeWheels(double power){
    wheels.Set(power);
}


