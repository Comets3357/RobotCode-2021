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

    setShooterPID(shooterWheelMPID, 0.0012, 0, 0.02, 0.0002);
    setShooterPID(shooterWheelSPID, 0.0012, 0, 0.02, 0.0002);
    setShooterPID(shooterHoodPID, 0.1, 0, 0, 0);
    setShooterPID(shooterHoodPID, 0.1, 0, 0, 0);
    setShooterPID(shooterTurretPID, 0.0535, 0,0,0);



    shooterWheelM.SetSmartCurrentLimit(30);
    shooterWheelS.SetSmartCurrentLimit(30);
    shooterHood.SetSmartCurrentLimit(45);
    shooterTurret.SetSmartCurrentLimit(45);

    shooterHoodPOS.SetPosition(0);
    shooterTurretPOS.SetPosition(0);
    shooterWheelMPOS.SetPosition(0);
    shooterWheelSPOS.SetPosition(0);
    shooterHood.Set(0);

    shooterWheelM.BurnFlash();
    shooterWheelS.BurnFlash();
    shooterHood.BurnFlash();
    shooterTurret.BurnFlash();

    

    
}

void ShooterSubsystem::Periodic(RobotData &robotData){
    frc::SmartDashboard::PutNumber("hood Position",  getHoodPos()); //horizontal offset
    frc::SmartDashboard::PutNumber("turret Position",  getTurretPos()); //horizontal offset
    frc::SmartDashboard::PutNumber("calc hood pos",  robotData.calcHoodPos); //horizontal offset

    // if(!robotData.isZero){
    //     setHood(0.1);
    //     if(getHoodLimitSwitch()){
    //         setHoodPos(0);
    //         setHood(0);
    //         robotData.isZero = true;
    //     }
    // }
   



    updateData(robotData);

    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

}

void ShooterSubsystem::updateData(RobotData &robotData){
    robotData.flywheelVelocity = getWheelVel();
    robotData.turretPosition = getTurretPos();
    robotData.hoodPosition = getHoodPos();
}

void ShooterSubsystem::semiAutoMode(RobotData &robotData){

    shootPOV = robotData.sDPad;
    frc::SmartDashboard::PutNumber("sStick", robotData.sRYStick);
    frc::SmartDashboard::PutNumber("pov", shootPOV);
    frc::SmartDashboard::PutNumber("x", robotData.xOffset);
    frc::SmartDashboard::PutNumber("Wheel vel", getWheelVel());


    if(getHoodLimitSwitch()){
        setHoodPos(0);
    }

    // if(robotData.sBBtn){
    //     setHood(-0.1);


    //     if(getHoodLimitSwitch()){
    //         setHood(0);
    //         setHoodPos(0);

    //     }

    // }

    

    setHood(robotData.sRYStick*.1);
    setTurret(robotData.sLYStick*.2);





    //shooting from the line
    if (shootPOV == 90){

        // if(!robotData.isZero){
        //     setHood(0.1);
        //     if(getHoodLimitSwitch()){
        //         setHoodPos(0);
        //         setHood(0);
        //         robotData.isZero = true;
        //     }

        // }



        
        

        // if(getHoodPos() < robotData.calcHoodPos-2){
        //     setHood(0.1);
        // }else if(getHoodPos() > robotData.calcHoodPos+2){
        //     setHood(-0.1);
        // }else{
        //     setHood(0);
        // }



        if(robotData.xOffset > 1 ){
            setTurret(0.02);
        }else if(robotData.xOffset < -1){
            setTurret(-0.02);
        }else{
            setTurret(0);
        }

        
        // if (getWheelVel() > 2900 && getWheelVel() < 3150){
        //     setWheel(0.74);
        // } else if (getWheelVel() > 3150){
        //     setWheel(0.68);
        // } else if (getWheelVel() > 1750){
        //     setWheel(0.77);
        // } else{
        //     setWheel(0.83);
        // }

        shooterWheelMPID.SetReference(3400, rev::ControlType::kVelocity);


        //add varibale to tell omni to switch directions
        //&& getWheelVel() < 3150

        
        if ((getWheelVel() > 2900 )){
            robotData.readyShoot = true;
        }else{
            robotData.readyShoot = false;
        }
        
    } else {
        // setHood(0);
        // setTurret(0);
        setWheel(0);
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

void ShooterSubsystem::setShooterPID(rev::CANPIDController motor, double p, double i, double d, double ff){
    motor.SetP(p);
    motor.SetI(i);
    motor.SetD(d);
    motor.SetFF(ff);

}
