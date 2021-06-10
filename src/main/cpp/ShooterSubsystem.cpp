#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>
#include "ShooterSubsystem.h"


void ShooterSubsystem::Init(){

    shooterWheelM.RestoreFactoryDefaults();
    shooterWheelS.RestoreFactoryDefaults();
    shooterHood.RestoreFactoryDefaults();
    shooterTurret.RestoreFactoryDefaults();

    shooterWheelS.SetInverted(true);


    shooterWheelS.Follow(shooterWheelM);


    shooterWheelM.SetInverted(true);
    shooterHood.SetInverted(true);
    shooterTurret.SetInverted(false);


    shooterWheelM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooterWheelS.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooterHood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    shooterTurret.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    /* shooterFlywheelM_pidController.SetP(fkP);
    shooterFlywheelM_pidController.SetI(fkI);
    shooterFlywheelM_pidController.SetD(fkD);
    shooterFlywheelM_pidController.SetIZone(fkIz);
    shooterFlywheelM_pidController.SetFF(fkFF);
    shooterFlywheelM_pidController.SetOutputRange(fkMinOutput, fkMaxOutput);

    shooterFlywheelS_pidController.SetP(fkP);
    shooterFlywheelS_pidController.SetI(fkI);
    shooterFlywheelS_pidController.SetD(fkD);
    shooterFlywheelS_pidController.SetIZone(fkIz);
    shooterFlywheelS_pidController.SetFF(fkFF);
    shooterFlywheelS_pidController.SetOutputRange(fkMinOutput, fkMaxOutput);

    shooterHood_pidController.SetP(hkP);
    shooterHood_pidController.SetI(hkI);
    shooterHood_pidController.SetD(hkD);
    shooterHood_pidController.SetIZone(hkIz);
    shooterHood_pidController.SetFF(hkFF);
    shooterHood_pidController.SetOutputRange(hkMinOutput, hkMaxOutput);

    shooterTurret_pidController.SetP(tkP);
    shooterTurret_pidController.SetI(tkI);
    shooterTurret_pidController.SetD(tkD);
    shooterTurret_pidController.SetIZone(tkIz);
    shooterTurret_pidController.SetFF(tkFF);
    shooterTurret_pidController.SetOutputRange(tkMinOutput, tkMaxOutput);

    shooterKick_pidController.SetP(kkP);
    shooterKick_pidController.SetI(kkI);
    shooterKick_pidController.SetD(kkD);
    shooterKick_pidController.SetIZone(kkIz);
    shooterKick_pidController.SetFF(kkFF);
    shooterKick_pidController.SetOutputRange(kkMinOutput, kkMaxOutput); */

    shooterWheelM.SetSmartCurrentLimit(30);
    shooterWheelS.SetSmartCurrentLimit(30);
    shooterHood.SetSmartCurrentLimit(45);
    shooterTurret.SetSmartCurrentLimit(45);

    shooterHoodPOS.SetPosition(0);
    shooterTurretPOS.SetPosition(0);
    shooterWheelMPOS.SetPosition(0);
    shooterWheelSPOS.SetPosition(0);
    shooterHood.Set(0);

    
}

void ShooterSubsystem::Periodic(RobotData &robotData){
    updateData(robotData);

    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

}

void ShooterSubsystem::Disabled(){
    
}

void ShooterSubsystem::updateData(RobotData &robotData){
    robotData.flywheelVelocity = getWheelVel();
    robotData.turretPosition = getTurretPos();
    robotData.hoodPosition = getHoodPos();
}

void ShooterSubsystem::semiAutoMode(RobotData &robotData){

    shootPOV = robotData.sDPad;
    setHood(robotData.sRYStick*.1);
    setTurret(robotData.sLYStick*.2);

    frc::SmartDashboard::PutNumber("shootPOV",  shootPOV);
    frc::SmartDashboard::PutNumber("sRYStick",  robotData.sRYStick);
    frc::SmartDashboard::PutNumber("sLYStick",  robotData.sLYStick);

    //shooting from the line
    if (shootPOV == 0){

        if(!robotData.isZero){
            setHood(0.1);
            if(getHoodLimitSwitch()){
                setHoodPos(0);
                setHood(0);
                robotData.isZero = true;
            }

        }
        
        

        // if (getHoodPos() > 12.5){
        //     setHood(-0.15);
        // } else if (getHoodPos() < 10.5){
        //     setHood(0.15);
        // } else {
        //     setHood(0);
        // }

        if(getHoodPos() < robotData.calcHoodPos-2){
            setHood(0.1);
        }else if(getHoodPos() > robotData.calcHoodPos+2){
            setHood(-0.1);
        }else{
            setHood(0);
        }

        if(robotData.xOffset > 5 ){
            setTurret(0.1);
        }else if(robotData.xOffset < -5){
            setTurret(-0.1);
        }else{
            setTurret(0);
        }

        
        if (getWheelVel() > 2900 && getWheelVel() < 3150){
            setWheel(0.74);
        } else if (getWheelVel() > 3150){
            setWheel(0.68);
        } else if (getWheelVel() > 1750){
            setWheel(0.77);
        } else{
            setWheel(0.83);
        }



        //add varibale to tell omni to switch directions
        
        if ((getWheelVel() > 2900 && getWheelVel() < 3150)){
            robotData.readyShoot = true;
        }else{
            robotData.readyShoot = false;
        }
        
    } else {
        setTurret(0);
        setWheel(0);
        setHood(0);
        robotData.isZero = false;
    }

}

void ShooterSubsystem::manualMode(RobotData &robotData){

}


void ShooterSubsystem::setHoodPos(double pos){
    shooterHoodPOS.SetPosition(pos);
}

void ShooterSubsystem::setTurretPos(double pos){
    shooterTurretPOS.SetPosition(pos);
}

double ShooterSubsystem::getHoodPos(){
    return shooterHoodPOS.GetPosition();
}
double ShooterSubsystem::getTurretPos(){
    return shooterTurretPOS.GetPosition();
}
double ShooterSubsystem::getWheelPos(){
    return shooterWheelMPOS.GetPosition();
} 

bool ShooterSubsystem::getTurretLimitSwitch(){
    return turretReverseLimit.Get();
}

bool ShooterSubsystem::getHoodLimitSwitch(){
    return hoodReverseLimit.Get();
}

void ShooterSubsystem::setHood(double power){
    shooterHood.Set(power);
}
void ShooterSubsystem::setTurret(double power){
    shooterTurret.Set(power);
}
void ShooterSubsystem::setWheel(double power){
    shooterWheelM.Set(power);
}
double ShooterSubsystem::getWheelVel(){
    return shooterWheelMPOS.GetVelocity();
}