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

    if(shootPOV == 90){
        setSpinner(0.3); //need faster
        setOmni(0.3);

        // if (getSpinnerVel() > 2850 && getSpinnerVel() < 3150){
        //     setSpinner(0.65);
        //     setOmni(0.65);
        // } else if (getSpinnerVel() > 3150){
        //     setSpinner(0.63);
        //     setOmni(0.63);
        // } else if (getSpinnerVel() > 1750){
        //     setSpinner(0.69);
        //     setOmni(0.69);
        // } else{
        //     setSpinner(0.76);
        //     setOmni(0.76);
        // }

        bool f = false;
        // if(robotData.flywheelVelocity > 2900 && robotData.flywheelVelocity < 3150){
        //     f = true;
        // } else {
        //     f = false;
        // }

        //raw index for this button is 1, find what that is
        if(robotData.sXBtn){
            setOmni(-0.6);
        } else {
            setOmni(0.3);
        }

        // if(f){
        //     if(robotData.sXBtn){
        //         setOmni(-0.7);
        //     } else {
        //         setOmni(0.7);
        //     }
        // }

    } else if (shootPOV == 0) { //automatic shooting
        // if(robotData.hoodPosition > 10.5 && robotData.hoodPosition < 12.5){
        //     setSpinner(0.5); // need faster
        //     setOmni(0.5);

        //     if (getSpinnerVel() > 2850 && getSpinnerVel() < 3150){
        //         setSpinner(0.65);
        //         setOmni(0.65*omniDir); //
        //     } else if (getSpinnerVel() > 3150){
        //         setSpinner(0.63);
        //         setOmni(0.63*omniDir);
        //     } else if (getSpinnerVel() > 1750){
        //         setSpinner(0.69);
        //         setOmni(0.69*omniDir);
        //     } else{
        //         setSpinner(0.76);
        //         setOmni(0.76*omniDir);
        //     }
        // }

        // if(robotData.flywheelVelocity > 2900 && robotData.flywheelVelocity < 3150){
        //     omniDir = -1;
        // } else {
        //     omniDir = 1;
        // }

    } else if (shootPOV == -1){

        // setSpinner(0);
        // setOmni(0);

    } else {

        if(robotData.sYBtn){
            setOmni(0.2);
            setSpinner(0.2);
        } else {
            setOmni(0);
            setSpinner(0);
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
        setSpinner(.5 * robotData.shift);
    } else {
        if(robotData.shootingMode){
            setSpinner(.5);
            setOmni(.5);
        }
    }
}

void IndexerSubsystem::setSpinner(double power){
    centerSpindle.Set(power);
}

void IndexerSubsystem::setOmni(double power){
    omniWheel.Set(power);
}

double IndexerSubsystem::getSpinnerVel(){
    return centerSpindlePOS.GetVelocity();
}


