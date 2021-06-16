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
    shooterWheelM.SetInverted(true);
    shooterTurret.SetInverted(false);
    shooterHood.SetInverted(true);
    /**
     * note:
     * the shooter hood isn't inverted the right way
     * a positive set value moves the hood down rather than up
     * but don't change it because it'll mess up the limit switch 
     * easier to just do it this way then rewiring the entire limitswitch
     */


    shooterWheelS.Follow(shooterWheelM);


    shooterWheelM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooterWheelS.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooterHood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    shooterTurret.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);


    setShooterPID(shooterWheelMPID, 0.0012, 0, 0.02, 0.0002);
    setShooterPID(shooterHoodPID, 0.1, 0, 0, 0);
    setShooterPID(shooterTurretPID, 0.0439, 0,0.9,0);

    shooterWheelM.SetSmartCurrentLimit(30);
    shooterWheelS.SetSmartCurrentLimit(30);
    shooterHood.SetSmartCurrentLimit(45);
    shooterTurret.SetSmartCurrentLimit(45);

    shooterHoodPOS.SetPosition(0);
    shooterTurretPOS.SetPosition(0);
    shooterWheelMPOS.SetPosition(0);
    shooterWheelSPOS.SetPosition(0);

    shooterWheelM.BurnFlash();
    shooterWheelS.BurnFlash();
    shooterHood.BurnFlash();
    shooterTurret.BurnFlash();

    setHood(-0.1);
    if(getHoodLimitSwitch()){
        setHoodPos(0);
        setHood(0);
    }
}

void ShooterSubsystem::Periodic(RobotData &robotData){

    frc::SmartDashboard::PutNumber("hood Position",  getHoodPos()); 
    frc::SmartDashboard::PutNumber("turret Position",  getTurretPos()); 
    frc::SmartDashboard::PutNumber("calc hood pos",  robotData.calcHoodPos); 

    updateData(robotData);

    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

}

//updates the robotData struct with the flywheel velocity, turret position, and hood position
void ShooterSubsystem::updateData(RobotData &robotData){
    robotData.flywheelVelocity = getWheelVel();
    robotData.turretPosition = getTurretPos();
    robotData.hoodPosition = getHoodPos();
}

void ShooterSubsystem::semiAutoMode(RobotData &robotData){
   
   //retreive controller input
    shootPOV = robotData.sDPad;
    frc::SmartDashboard::PutNumber("pov", shootPOV);
    frc::SmartDashboard::PutNumber("x", robotData.xOffset);
    frc::SmartDashboard::PutNumber("Wheel vel", getWheelVel());
    frc::SmartDashboard::PutBoolean("hoodlimit", getHoodLimitSwitch());
    frc::SmartDashboard::PutNumber("target velocity", robotData.targetVelocity);


    //if you're pressing the shooting button
    if (shootPOV == robotData.shootingBtn){ 

        //if we're close to the target the velocity doesn't need to be as high, gets us shooting faster
        if(robotData.yOffset > 5){
            robotData.targetVelocity = 2400;
        }else{
            robotData.targetVelocity = 3000;
        }
    
        //Use PID to set Hood
        shooterHoodPID.SetReference(robotData.calcHoodPos, rev::ControlType::kPosition);
        if((getHoodPos() > robotData.calcHoodPos-1) && (getHoodPos() < robotData.calcHoodPos+1)){

            //moves turret until in range
            if(robotData.xOffset > 1 ){ 
                setTurret(0.02);
            }else if(robotData.xOffset < -1){
                setTurret(-0.02);
            }else{
                setTurret(0);
                //uses PID to get the shooter wheel up to speed and stay there
                shooterWheelMPID.SetReference(3400, rev::ControlType::kVelocity);

                //once the shooter has high enough velocity tell robot to begin shooting
                if ((getWheelVel() > robotData.targetVelocity)){
                    robotData.readyShoot = true;
                }else{
                    robotData.readyShoot = false;
                }

            }

        }

    } else {  //not shooting

        if(robotData.sBBtn){
            shooterWheelMPID.SetReference(3400, rev::ControlType::kVelocity);
        }else{
            setWheel(0);
        }
        
        robotData.readyShoot = false;

        //zeros the hood after
        setHood(-0.1);
        if(getHoodLimitSwitch()){
            setHoodPos(0);
            setHood(0);
            //robotData.isZero = true;
        }
        

    }

}

void ShooterSubsystem::manualMode(RobotData &robotData){
    //make hood and turret moveable by joystick
    setTurret(robotData.sLYStick*.1);

    //zeros hood using limitswitch
    if(robotData.sBBtn){
        setHood(-0.1);     
        if(getHoodLimitSwitch()){
            setHoodPos(0);
            setHood(0);
        }
    }else{
        setHood(robotData.sRYStick*.1);
    }

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

/**
 * Sets all the PID values for specific motor
 * @param motor name of the PID controller
 */
void ShooterSubsystem::setShooterPID(rev::CANPIDController motor, double p, double i, double d, double ff){
    motor.SetP(p);
    motor.SetI(i);
    motor.SetD(d);
    motor.SetFF(ff);

}

// void ShooterSubsystem::Disabled(){
//     setHood(0);
//     setTurret(0);
//     setWheel(0);
// }
