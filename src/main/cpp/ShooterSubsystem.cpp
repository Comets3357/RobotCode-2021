#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>
#include "ShooterSubsystem.h"


void ShooterSubsystem::RobotInit(){
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
     * 
     * update:: could now be false i dont know anymore
     */


    shooterWheelS.Follow(shooterWheelM);


    shooterWheelM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooterWheelS.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooterHood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    shooterTurret.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);


    setShooterPID(shooterWheelMPID, 0, 0.0012, 0, 0.02, 0.0002); //first pid for high velocity shooting
    setShooterPID(shooterWheelMPID, 1, 0, 0, 0, 0.0002); //second pid for low constant velocity 
    setShooterPID(shooterHoodPID, 0, 0.1, 0, 0, 0);
    setShooterPID(shooterTurretPID, 0, 0.09, 0, 1, 0);

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

    //rev::CANSparkMaxLowLevel::EnableExternalUSBControl(true);

    //zeros hood at the begining
    setHood(-0.1);
    if(getHoodLimitSwitch()){
        setHoodPos(0);
        setHood(0);
    }
}

void ShooterSubsystem::Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData){

    // frc::SmartDashboard::PutNumber("hood Position",  getHoodPos()); 
    // frc::SmartDashboard::PutNumber("turret Position",  getTurretPos()); 
    // frc::SmartDashboard::PutNumber("calc hood pos",  robotData.calcHoodPos); 

    updateData(robotData);

    if(!robotData.climbMode){
        if(robotData.manualMode){
            manualMode(robotData);
        } else {
            semiAutoMode(robotData);
        }
    }else{
        setHood(0);
        setTurret(0);
        setWheel(0);
    }

    updateDiagnostics(diagnosticsData);

}

//updates the robotData struct with the flywheel velocity, turret position, and hood position
void ShooterSubsystem::updateData(RobotData &robotData){
    robotData.flywheelVelocity = getWheelVel();
    robotData.turretPosition = getTurretPos();
    robotData.hoodPosition = getHoodPos();
}

void ShooterSubsystem::semiAutoMode(RobotData &robotData){

   //retreive controller input
    // frc::SmartDashboard::PutNumber("x", robotData.xOffset);
    // frc::SmartDashboard::PutNumber("Wheel vel", getWheelVel());
    // frc::SmartDashboard::PutNumber("turret pos", getTurretPos());
    // frc::SmartDashboard::PutNumber("calc hood", robotData.calcHoodPos);

    // frc::SmartDashboard::PutBoolean("hoodlimit", getHoodLimitSwitch());
    // frc::SmartDashboard::PutBoolean("turret limit", getTurretLimitSwitch());


    //if you're shooting 
    if(getTurretLimitSwitch()){ //for the beginning of the math zero the turret 
        setTurretPos(0);
        robotData.isZero = true;
    }else if(!robotData.isZero){
        setTurret(-0.1);
    }else if(robotData.isZero){
        
        //adding the two left/right pov buttons to turn the turret left/right
        

        if (robotData.shootingMode){ 
            turretSnapshot = getTurretPos();

            //if we're close to the target the velocity doesn't need to be as high, gets us shooting faster
            if(robotData.yOffset > 5){
                robotData.targetVelocity = 2400;
            }else{
                robotData.targetVelocity = 3000;
            }
        
            //if the bot can see a target
            if(robotData.targetValue != 0){

                //Use PID to set Hood and Turret based off limelight values
                shooterHoodPID.SetReference(robotData.calcHoodPos, rev::ControlType::kPosition);
                shooterTurretPID.SetReference(robotData.calcTurretPos + getTurretPos(), rev::ControlType::kPosition);
                
                //uses PID to get the shooter wheel up to speed and stay there
                shooterWheelMPID.SetReference(3400, rev::ControlType::kVelocity);
                
                if (getWheelVel() > robotData.targetVelocity - 300)
                {
                    robotData.stopAntiJam = true;
                }
                else {
                    robotData.stopAntiJam = false;
                }

                //once the shooter has high enough velocity and is aimed correctly tell robot to begin shooting (start indexer)
                if ((getWheelVel() > robotData.targetVelocity) && (std::abs(getTurretPos() - (turretSnapshot + robotData.calcTurretPos)) <= 1) && (std::abs(getHoodPos() - robotData.calcHoodPos) <= 2) ){
                    robotData.readyShoot = true;
                }else{
                    robotData.readyShoot = false;
                }

            }
            //robotData.isZero = false;
            

        } else {  //not shooting

            //set the turret to face forward
            shooterTurretPID.SetReference(12 + (robotData.roughAim*4.5), rev::ControlType::kPosition);
            //spins up flywheel beforehand
            if(robotData.sBBtn){
                shooterWheelMPID.SetReference(3400, rev::ControlType::kVelocity);
            }else{
                if(getWheelVel() < 1200){ //once the flywheel reaches a low enough velocity begin constant velociy
                    shooterWheelMPID.SetReference(1000, rev::ControlType::kVelocity, 1); //uses second pid
                }else{
                    setWheel(0); //starts the shooting wheel slowing down
                }


            }

            

            robotData.readyShoot = false;

            //zeros the hood after
            setHood(-0.2);
            if(getHoodLimitSwitch()){
                setHoodPos(0);
                setHood(0);
            }

        }



    }
    

    

}

void ShooterSubsystem::manualMode(RobotData &robotData){
    
    // frc::SmartDashboard::PutNumber("turret pos", getTurretPos());

    //make hood and turret moveable by joystick
    setTurret(robotData.sLYStick*.1);

    if(robotData.sBBtn){
        //spins the flywheel up beforehand
        shooterWheelMPID.SetReference(3400, rev::ControlType::kVelocity);
    }else{
        setWheel(0);
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





void ShooterSubsystem::updateDiagnostics(DiagnosticsData &diagnosticsData)
{
    /**
     * turret rotate 23
     * hood 22
     * shooter m 20
     * shooter s 21
     * 
     * limit switches
     */

    diagnosticsData.mControlCurrents.at(23) = shooterTurret.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(23) = shooterTurret.GetBusVoltage();
    diagnosticsData.mControlTemps.at(23) = shooterTurret.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(23) = shooterTurretPOS.GetPosition();
    diagnosticsData.mControlVelocities.at(23) = shooterTurretPOS.GetVelocity();

    diagnosticsData.mControlFaults.at(23) = shooterTurret.GetFaults();


    diagnosticsData.mControlCurrents.at(22) = shooterHood.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(22) = shooterHood.GetBusVoltage();
    diagnosticsData.mControlTemps.at(22) = shooterHood.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(22) = shooterHoodPOS.GetPosition();
    diagnosticsData.mControlVelocities.at(22) = shooterHoodPOS.GetVelocity();

    diagnosticsData.mControlFaults.at(22) = shooterHood.GetFaults();


    diagnosticsData.mControlCurrents.at(20) = shooterWheelM.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(20) = shooterWheelM.GetBusVoltage();
    diagnosticsData.mControlTemps.at(20) = shooterWheelM.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(20) = shooterWheelMPOS.GetPosition();
    diagnosticsData.mControlVelocities.at(20) = shooterWheelMPOS.GetVelocity();

    diagnosticsData.mControlFaults.at(20) = shooterWheelM.GetFaults();


    diagnosticsData.mControlCurrents.at(21) = shooterWheelS.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(21) = shooterWheelS.GetBusVoltage();
    diagnosticsData.mControlTemps.at(21) = shooterWheelS.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(21) = shooterWheelSPOS.GetPosition();
    diagnosticsData.mControlVelocities.at(21) = shooterWheelSPOS.GetVelocity();

    diagnosticsData.mControlFaults.at(21) = shooterWheelS.GetFaults();


    diagnosticsData.turretLSwitch = getTurretLimitSwitch();
    diagnosticsData.hoodLSwitch = getHoodLimitSwitch();
}

/**
 * Sets all the PID values for specific motor
 * @param motor name of the PID controller
 */
void ShooterSubsystem::setShooterPID(rev::CANPIDController motor, int pidSlot, double p, double i, double d, double ff){
    motor.SetP(p, pidSlot);
    motor.SetI(i, pidSlot);
    motor.SetD(d, pidSlot);
    motor.SetFF(ff, pidSlot);

}

void ShooterSubsystem::DisabledInit(){
    setHood(0);
    setTurret(0);
    setWheel(0);
}
